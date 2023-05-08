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
        class Rectangle3D;
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
                return Vector3D(x / magnitude, y / magnitude, z / magnitude);
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
    Vector3D cross(const Vector3D &v1, const Vector3D &v2)
    {
        return Vector3D(v1.y * v2.z - v1.z * v2.y,
                        v1.z * v2.x - v1.x * v2.z,
                        v1.x * v2.y - v1.y * v2.x);
    }
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

            Point3D operator+(const Vector3D &v) const {
                return Point3D(x + v.x, y + v.y, z + v.z);
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

    class Rectangle3D {
        public:
            //* Attributes
            Point3D _origin;
            Vector3D _bottom_side;
            Vector3D _left_side;

            //* Constructors
            Rectangle3D() : _origin(), _bottom_side(), _left_side() {}

            Rectangle3D(const Point3D &origin, const Vector3D &bottom_side, const Vector3D &left_side)
                : _origin(origin), _bottom_side(bottom_side), _left_side(left_side) {}

            Rectangle3D(const Rectangle3D &r)
                : _origin(r._origin), _bottom_side(r._bottom_side), _left_side(r._left_side) {}

            Rectangle3D(Rectangle3D &&r) noexcept : _origin(r._origin), _bottom_side(r._bottom_side), _left_side(r._left_side) {
                r._origin = Point3D();
                r._bottom_side = Vector3D();
                r._left_side = Vector3D();
            }

            //* Destructor
            ~Rectangle3D() = default;

            //* Operators
            Rectangle3D &operator=(const Rectangle3D &r) {
                if (this != &r) {
                    _origin = r._origin;
                    _bottom_side = r._bottom_side;
                    _left_side = r._left_side;
                }
                return *this;
            }

            Rectangle3D &operator=(Rectangle3D &&r) noexcept {
                if (this != &r) {
                    _origin = r._origin;
                    _bottom_side = r._bottom_side;
                    _left_side = r._left_side;
                    r._origin = Point3D();
                    r._bottom_side = Vector3D();
                    r._left_side = Vector3D();
                }
                return *this;
            }

            //* Methods
            Point3D pointAt(double u, double v) const {
                return _origin + _bottom_side * u + _left_side * v;
            }

            //* Getters
            Point3D getOrigin() const {
                return _origin;
            }

            Vector3D getBottomSide() const {
                return _bottom_side;
            }

            Vector3D getLeftSide() const {
                return _left_side;
            }

            //* Setters
            void setOrigin(const Point3D &origin) {
                _origin = origin;
            }

            void setBottomSide(const Vector3D &bottom_side) {
                _bottom_side = bottom_side;
            }

            void setLeftSide(const Vector3D &left_side) {
                _left_side = left_side;
            }
    };
    Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2)
    {
        return Vector3D(v1.y * v2.z - v1.z * v2.y,
                        v1.z * v2.x - v1.x * v2.z,
                        v1.x * v2.y - v1.y * v2.x);
    }
};
