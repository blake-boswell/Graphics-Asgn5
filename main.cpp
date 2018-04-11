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
        // Calculate Euclidian distance between 2 3D points
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
    Point3D get_sample(float t);
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
    bool get_intersection(Ray3D ray, Point3D &point, Vector3D &normal);
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

   cout << "\nTest vector class\n";
   Vector3D v;
   v.set(2,1,0);
   cout << "v = ";
   v.print();
   cout << endl;

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

   cout << "\nTest sphere class\n";
   Sphere3D s;
   s.set(p1, 2);
   cout << "s = ";
   s.print();
   cout << endl;

   // TO BE ADDED
   return 0;
}