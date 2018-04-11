//----------------------------------------------
// Purpose: Definition and implementation of the
//    Point3D, Vector3D, Ray3D and Sphere3D classes.
//
//    These classes have no private variables and
//    they have "inline" method implementations
//    so they should be used with care (since there
//    is no data hiding provided).
//    
// Author:  John Gauch
// Modified by: Blake Boswell
//----------------------------------------------
#include <iostream>
#include <cmath>
using namespace std;

//----------------------------------------------
class Point3D
{
   public:
    float px, py, pz;

    void set(float x, float y, float z) 
        { px = x; py = y; pz = z; }

    void print() 
        { cout << "(" << px << "," << py << "," << pz << ")"; }

    // TO BE ADDED
    float distance(Point3D p) {
        float deltaXSquared = ((this->px - p.px) * (this->px - p.px));
        float deltaYSquared = ((this->py - p.py) * (this->py - p.py));
        float deltaZSquared = ((this->pz - p.pz) * (this->pz - p.pz));
        return sqrt(deltaXSquared + deltaYSquared + deltaZSquared);
    }

    Point3D operator-(const Point3D& p) {
        Point3D point;
        point.px = this->px - p.px;
        point.py = this->py - p.py;
        point.pz = this->pz - p.pz;
        return point;
    }
};

//----------------------------------------------
class Vector3D
{
   public:
    float vx, vy, vz;

    void set(float x, float y, float z) 
        { vx = x; vy = y; vz = z; }

    void print() 
        { cout << "(" << vx << "," << vy << "," << vz << ")"; }

      // TO BE ADDED
    void normalize() {
        float vectorMagnitude = this->magnitude();
        this->vx = this->vx / vectorMagnitude;
        this->vy = this->vy / vectorMagnitude;
        this->vz = this->vz / vectorMagnitude;
    }

    float magnitude() {
        float squareSum = (this->vx * this->vx) + (this->vy * this->vy) + (this->vz * this->vz);
        return sqrt(squareSum);
    }

    float dot(Vector3D v) {
        float dotResult = (this->vx * v.vx) + (this->vy * v.vy) + (this->vz * v.vz);
        return dotResult;
    }

    Vector3D operator*(const Vector3D& v) {
        Vector3D vector;
        vector.vx = this->vx * v.vx;
        vector.vy = this->vy * v.vy;
        vector.vz = this->vz * v.vz;
        return vector;
    }

    Vector3D operator*(const int& n) {
        Vector3D vector;
        vector.vx = this->vx * n;
        vector.vy = this->vy * n;
        vector.vz = this->vz * n;
        return vector;
    }
};

//----------------------------------------------
class Ray3D
{
   public:
    Point3D point;
    Vector3D dir;

    void set(Point3D p, Vector3D d) 
        { point = p; dir = d; }

    void set(Point3D p1, Point3D p2) 
        { point = p1; dir.set(p2.px-p1.px, p2.py-p1.py, p2.pz-p1.pz); }

    void print() 
        { point.print(); cout << " "; dir.print(); }

    // TO BE ADDED
    Point3D get_sample(float t) {
        Point3D location;
        float locationX = this->point.px + (t * this->dir.vx);
        float locationY = this->point.px + (t * this->dir.vy);
        float locationZ = this->point.pz + (t * this->dir.vz);
        location.set(locationX, locationY, locationZ);
        return location;
    }
};

//----------------------------------------------
class Sphere3D
{
   public:
    Point3D center;
    float radius;

    void set(Point3D p, float r) 
        { center = p; radius = r; }

    void print() 
        { center.print(); cout << " " << radius; }

    // TO BE ADDED
    bool get_intersection(Ray3D ray, Point3D &point, Vector3D &normal) {
        // Get distance from ray origin to center of sphere
        float length = ray.point.distance(center);
        // Use the direction of the ray dotted with the magnitude of L to get the ray vector that intersects (if it does)
        float rayPointToCenter = length * ray.dir.vx + length * ray.dir.vy + length * ray.dir.vz;
        if(rayPointToCenter < 0) {
            // ray doesn't intersect with the circle
            return false;
        }

        float d = sqrt((length * length) - (rayPointToCenter * rayPointToCenter));
        if(d > this->radius) {
            // ray doesn't intersect with the circle
            return false;
        }
        float lengthFromIntersectToCenter = sqrt((this->radius * this->radius) - (d * d));
        float lengthFromRayPointToIntersect = rayPointToCenter - lengthFromIntersectToCenter;

        point = ray.get_sample(lengthFromRayPointToIntersect);

        // Calculate normal
        normal.vx = point.px - this->center.px;
        normal.vy = point.py - this->center.py;
        normal.vz = point.pz - this->center.pz;
        normal.normalize();
        return true;


    }
};


//----------------------------------------------
int main()
{
    cout << "\nTest point class\n";
    Point3D p1;
    p1.set(1,2,3);
    cout << "p1 = ";
    p1.print();
    cout << endl;
    Point3D p2;
    p2.set(3,4,5);
    cout << "p2 = ";
    p2.print();
    cout << endl;
    Point3D p3;
    p3.set(4,2,6);
    cout << "p3 = ";
    p3.print();
    cout << endl;
    cout << "The distance btwn p1 and p2 is " << p1.distance(p2) << "\t\t(should be 3.464)" << endl;
    cout << "The distance btwn p2 and p3 is " << p2.distance(p3) << "\t\t(should be 2.449)" << endl;
    cout << "The distance btwn p1 and p3 is " << p1.distance(p3) << "\t\t(should be 4.2426)" << endl;

    cout << "\nTest vector class\n";
    Vector3D v;
    v.set(2,1,0);
    cout << "v = ";
    v.print();
    cout << endl;
    v.normalize();
    cout << "Normalized v = ";
    v.print();
    cout << endl;
    cout << "Proof: Magnitude should be 1. Magnitude of v: " << v.magnitude() << endl;
    Vector3D v1;
    v1.set(2,4,3);
    cout << "v1 = ";
    v1.print();
    cout << endl;
    Vector3D v2;
    v2.set(5,3,9);
    cout << "v2 = ";
    v2.print();
    cout << endl;
    cout << "v1 dot v2: " << v1.dot(v2) << "\t\t(should be 49)" << endl;

    cout << "\nTest ray class\n";
    Ray3D r1;
    r1.set(p1, v);
    cout << "r1 = ";
    r1.print();
    cout << endl;
    Ray3D r2;
    r2.set(p1, p2);
    cout << "r2 = ";
    r2.print();
    cout << endl;
    Ray3D ray;
    ray.set(p1, v1);
    cout << "ray = ";
    ray.print();
    cout << endl;
    cout << "ray get_sample test\n";
    cout << "(should be from 1,2,3 all the way to 3, 5, 6 increasing linearly)" << endl;
    const int numSamples = 10;
    for(int i = 0; i <= numSamples; i++) {
        ray.get_sample((float)i/numSamples).print();
        cout << endl;
    }

    cout << "\nTest sphere class\n";
    Sphere3D s;
    s.set(p1, 2);
    cout << "s = ";
    s.print();
    cout << endl;
    r1.set(p1,v2);
    cout << "r1 = ";
    r1.print();
    cout << endl;
    cout << "r2 = ";
    r2.print();
    cout << endl;
    ray.set(p2,v1);
    cout << "ray = ";
    ray.print();
    cout << endl;
        
    cout << "\nTest get_intersection\n";
    Point3D point;
    Vector3D normal;

    if(s.get_intersection(r1, point, normal)) {
        cout << "r1 has an intersection at ";
        point.print();
        cout << ". The spheres normal is ";
        normal.print();
        cout << endl;
    } else {
        cout << "r1 does not intersect s" << endl;
    }

    if(s.get_intersection(r2, point, normal)) {
        cout << "r2 has an intersection at ";
        point.print();
        cout << ". The spheres normal is ";
        normal.print();
        cout << endl;
    } else {
        cout << "r2 does not intersect s" << endl;
    }

    if(s.get_intersection(ray, point, normal)) {
        cout << "ray has an intersection at ";
        point.print();
        cout << ". The spheres normal is ";
        normal.print();
        cout << endl;
    } else {
        cout << "ray does not intersect s" << endl;
    }
    // TO BE ADDED
    return 0;
}