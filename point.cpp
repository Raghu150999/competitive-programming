#include <bits/stdc++.h>

using namespace std;

struct Point
{
    double x, y, z;
    Point(double x, double y, double z): x(x), y(y), z(z) {}
    Point operator-(Point &p)
    {
        return Point(x - p.x, y - p.y, z - p.z);
    }
    Point operator+(Point &p)
    {
        return Point(x + p.x, y + p.y, z + p.z);
    }
    Point cross(Point &p)
    {
        return Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    double dot(Point &p)
    {
        return x * p.x + y * p.y + z * p.z;
    }
    void unit()
    {
        double modulus = sq(x) + sq(y) + sq(z);
        modulus = sqrt(modulus);
        x /= modulus;
        y /= modulus;
        z /= modulus;
    }
    double sq(double x)
    {
        return x * x;
    }
};

