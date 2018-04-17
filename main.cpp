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

    float dot(Point3D p) {
        float dotResult = (this->vx * p.px) + (this->vy * p.py) + (this->vz * p.pz);
        return dotResult;
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
        this->dir.normalize();
        float locationX = this->point.px + (t * this->dir.vx);
        float locationY = this->point.py + (t * this->dir.vy);
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
        // Calculate the difference betweenn the ray origin and center of the circle
        Vector3D difference;
        difference.vx = ray.point.px - this->center.px;
        difference.vy = ray.point.py - this->center.py;
        difference.vz = ray.point.pz - this->center.pz;

        // Calculate the value under the square root
        ray.dir.normalize();
        float b = ray.dir.dot(difference);
        float differenceSquared = (difference.dot(difference));
        float radiusSquared = this->radius * this->radius;
        float valueUnderSquareRt = (b * b) - differenceSquared + radiusSquared;

        if(valueUnderSquareRt < 0) {
            // Ray doesn't intersect the sphere
            return false;
        }

        float t0 = -1 * b + sqrt(valueUnderSquareRt); 
        float t1 = -1 * b - sqrt(valueUnderSquareRt);

        if(t0 < 0) {
            // Cannot get sample of a value < 0, so it does not intersect
            return false;
        }

        Point3D point1, point2;
        point1 = ray.get_sample(t0);
        point2 = ray.get_sample(t1);

        // Figure out which point to use
        if(t0 != t1) {
            // Two intersect points
            if(point1.distance(ray.point) > point2.distance(ray.point)) {
                // Other point is closer
                point = point2;
            } else {
                point = point1;
            }
        } else {
            // One intersect point
            point = point1;
        }

        // Calculate normal
        normal.vx = point.px - this->center.px;
        normal.vy = point.py - this->center.py;
        normal.vz = point.pz - this->center.pz;
        normal.normalize();
        return true;


    }
};

void testRaySphereIntersection(Ray3D ray, Sphere3D sphere) {
    Point3D point;
    Vector3D normal;
    cout << "\nray =\t\t";
    ray.print();
    cout << endl;
    if(sphere.get_intersection(ray, point, normal)) {
        cout << "point =\t\t";
        point.print();
        cout << "\nnormal =\t";
        normal.print();
        cout << endl;
    } else {
        cout << "The ray does not intersect the sphere" << endl;
    }
}

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
    cout << "The distance btwn p1 and p2 is " << p1.distance(p2) << "\t\t(should be ~3.464)" << endl;
    cout << "The distance btwn p2 and p3 is " << p2.distance(p3) << "\t\t(should be ~2.449)" << endl;
    cout << "The distance btwn p1 and p3 is " << p1.distance(p3) << "\t\t(should be ~4.2426)" << endl;

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
    cout << "\tProof: Magnitude should be 1. Magnitude of v: " << v.magnitude() << endl;
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
    const int numSamples = 10;
    for(int i = 0; i <= numSamples; i++) {
        r1.get_sample((float)i/numSamples).print();
        cout << endl;
    }

    cout << "\nTest sphere class\n";
    Point3D point1, point2, point3, point4, point5, point6, point7;
    point1.set(-3,0,0);
    point2.set(-2,0,0);
    point3.set(-1,0,0);
    point4.set(0,0,0);
    point5.set(1,0,0);
    point6.set(2,0,0);
    point7.set(3,0,0);
    Vector3D vector1;
    vector1.set(1,0,0);
    Ray3D ray1, ray2, ray3, ray4, ray5, ray6, ray7;
    Sphere3D s;
    s.set(point4, 2);
    cout << "s = ";
    s.print();
    cout << endl;
    ray1.set(point1,vector1);
   
    ray2.set(point2, vector1);
    
    ray3.set(point3,vector1);
    
    ray4.set(point4, vector1);
    
    ray5.set(point5, vector1);
    
    ray6.set(point6, vector1);
    
    ray7.set(point7, vector1);
        
    cout << "\nTest get_intersection\n";
    testRaySphereIntersection(ray1, s);
    testRaySphereIntersection(ray2, s);
    testRaySphereIntersection(ray3, s);
    testRaySphereIntersection(ray4, s);
    testRaySphereIntersection(ray5, s);
    testRaySphereIntersection(ray6, s);
    testRaySphereIntersection(ray7, s);
    return 0;
}