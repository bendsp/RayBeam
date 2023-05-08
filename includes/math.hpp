/*
** EPITECH PROJECT, 2022
** bootstrapRaytracer
** File description:
** vector.hpp
*/

#pragma once

#include <cmath>

class Math {
    public:
        class Vector3D;
        class Point3D;

    // * Methods
    Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2)
    {
        return Vector3D(v1.y * v2.z - v1.z * v2.y,
                        v1.z * v2.x - v1.x * v2.z,
                        v1.x * v2.y - v1.y * v2.x);
    }

    double degToRadians(double degrees)
    {
        return degrees * (M_PI / 180.0);
    }

    // * Classes
    class Vector3D {
        public:
            //* Attributes
            double x, y, z;

            //* Constructors
            Vector3D() : x(0), y(0), z(0) {}

            Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

            Vector3D(const Vector3D &v) : x(v.x), y(v.y), z(v.z) {}

            Vector3D(Vector3D &&v) : x(v.x), y(v.y), z(v.z) {
                v.x = 0;
                v.y = 0;
                v.z = 0;
            }

            Vector3D(const Point3D& point) : x(point.x), y(point.y), z(point.z) {}

            //* Destructor
            ~Vector3D() = default;

            //* Operators
            Vector3D &operator=(const Vector3D &v) {
                if (this != &v) {
                    x = v.x;
                    y = v.y;
                    z = v.z;
                }
                return *this;
            }

            Vector3D &operator=(Vector3D &&v) noexcept {
                if (this != &v) {
                    x = v.x;
                    y = v.y;
                    z = v.z;
                    v.x = 0;
                    v.y = 0;
                    v.z = 0;
                }
                return *this;
            }

            Vector3D operator+(const Vector3D &v) const {
                return Vector3D(x + v.x, y + v.y, z + v.z);
            }

            Vector3D &operator+=(const Vector3D &v) {
                x += v.x;
                y += v.y;
                z += v.z;
                return *this;
            }

            Vector3D operator-(const Vector3D &v) const {
                return Vector3D(x - v.x, y - v.y, z - v.z);
            }



            Vector3D &operator-=(const Vector3D &v) {
                x -= v.x;
                y -= v.y;
                z -= v.z;
                return *this;
            }

            Vector3D operator*(const Vector3D &v) const {
                return Vector3D(x * v.x, y * v.y, z * v.z);
            }

            Vector3D &operator*=(const Vector3D &v){
                x *= v.x;
                y *= v.y;
                z *= v.z;
                return *this;
            }

            Vector3D operator/(const Vector3D &v) const {
                return Vector3D(x / v.x, y / v.y, z / v.z);
            }

            Vector3D &operator/=(const Vector3D &v) {
                x /= v.x;
                y /= v.y;
                z /= v.z;
                return *this;
            }
            
            Vector3D operator=(const Point3D &p) {
                return Vector3D(p.x, p.y, p.z);
            }

            Vector3D operator*(double f) const {
                return Vector3D(x * f, y * f, z * f);
            }

            Vector3D &operator*=(double f) {
                x *= f;
                y *= f;
                z *= f;
                return *this;
            }

            Vector3D operator/(double f) const {
                return Vector3D(x / f, y / f, z / f);
            }

            Vector3D &operator/=(double f) {
                x /= f;
                y /= f;
                z /= f;
                return *this;
            }

            Vector3D operator-(const Math::Point3D &p) {
                return Vector3D(x - p.x, y - p.y, z - p.z);
            }


            //* Methods
            double dot(const Vector3D &v) const {
                return x * v.x + y * v.y + z * v.z;
            }

            double length() const {
                return sqrt(x * x + y * y + z * z);
            }

            Vector3D normalized() const {
                double magnitude = std::sqrt(x * x + y * y + z * z);
                if (magnitude == 0)
                    return Vector3D(0.5, 0, 0);
                return Vector3D(x / magnitude, y / magnitude, z / magnitude);
            }

            Point3D toPoint() const {
                return Point3D(x, y, z);
            }

            //* Getters
            double getX() const {
                return x;
            }

            double getY() const {
                return y;
            }

            double getZ() const {
                return z;
            }

            //* Setters
            void setX(double x) {
                this->x = x;
            }

            void setY(double y) {
                this->y = y;
            }

            void setZ(double z) {
                this->z = z;
            }
    };
    class Point3D {
        public:
            //* Attributes
            double x, y, z;

            //* Constructors
            Point3D() : x(0), y(0), z(0) {}

            Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

            Point3D(const Point3D &p) : x(p.x), y(p.y), z(p.z) {}

            Point3D(Point3D &&p) noexcept : x(p.x), y(p.y), z(p.z) {
                p.x = 0;
                p.y = 0;
                p.z = 0;
            }

            //* Destructor
            ~Point3D() = default;

            //* Operators
            Point3D &operator=(const Point3D &p) {
                if (this != &p) {
                    x = p.x;
                    y = p.y;
                    z = p.z;
                }
                return *this;
            }

            Point3D &operator=(Point3D &&p) noexcept {
                if (this != &p) {
                    x = p.x;
                    y = p.y;
                    z = p.z;
                    p.x = 0;
                    p.y = 0;
                    p.z = 0;
                }
                return *this;
            }

            Point3D operator+(const Vector3D& vec) const {
                return Point3D(x + vec.x, y + vec.y, z + vec.z);
            }

            Point3D operator-(const Point3D &p1) {
                return Point3D(x - p1.x, y - p1.y, z - p1.z);
            }

            Point3D operator+(const Point3D &p1) {
                return Point3D(x + p1.x, y + p1.y, z + p1.z);
            }

            Point3D &operator=(const Vector3D &v) {
                x = v.x;
                y = v.y;
                z = v.z;
                return *this;
            }

            Point3D &operator+=(const Vector3D &v) {
                x += v.x;
                y += v.y;
                z += v.z;
                return *this;
            }

            Point3D &operator-=(const Vector3D &v) {
                x -= v.x;
                y -= v.y;
                z -= v.z;
                return *this;
            }

            friend Vector3D operator-(const Point3D p1, const Point3D p2) {
                return Vector3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
            }

            //* Getters
            double getX() const {
                return x;
            }

            double getY() const {
                return y;
            }

            double getZ() const {
                return z;
            }

            //* Setters
            void setX(double x) {
                this->x = x;
            }

            void setY(double y) {
                this->y = y;
            }

            void setZ(double z) {
                this->z = z;
            }
    };

};
