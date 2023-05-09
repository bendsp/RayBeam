/*
** EPITECH PROJECT, 2022
** B-OOP-400-BER-4-1-raytracer-paul.thiebault
** File description:
** primitives.hpp
*/

#pragma once

#include "raytracer.hpp"
#include <iostream>

namespace RayTracer {
    typedef struct RGB {
        int r;
        int g;
        int b;
    } RGB;

    enum Axis {
        X = 1,
        Y,
        Z
    };

    class IPrimitive {
        public:
            IPrimitive() = default;
            virtual ~IPrimitive() = default;

            virtual RayTracer::RGB getColor() const = 0;
            virtual void displayPrimitive() const = 0;
            virtual bool hits(const Ray &ray) const = 0;
            virtual double getIntersectionDistance(const Ray &ray) const = 0;
            virtual Math::Point3D getIntersectionPoint(const Ray &ray) const = 0;
            virtual void translate(const Math::Vector3D &translation) = 0;
            // virtual void rotate(const Axis &axis, const double &angle) = 0;
    };

    class APrimitive : public IPrimitive {
        public:
            APrimitive() : _color({0, 0, 0}) {};
            APrimitive(RGB color) : _color(color) {};
            virtual ~APrimitive() = default;

            //* Getters
            RGB getColor() const{
                return _color;
            }

            //* Setters
            void setColor(RGB color){
                _color = color;
            }

        protected:
            RGB _color;
    };

    class Cone: public APrimitive {
        public:
            //* Attributes
            Math::Point3D _base;
            Math::Point3D _head;
            double _radius;

            //* Constructors
            Cone() : _base(), _head(), _radius(0), APrimitive({0, 0 ,0}) {}

            Cone(Math::Point3D base, Math::Point3D head, double radius, RGB color) : _base(base), _head(head), _radius(radius), APrimitive(color) {}

            Cone(const Cone &c) : _base(c._base), _head(c._head), _radius(c._radius), APrimitive(c._color) {}

            Cone(Cone &&c) : _base(c._base), _head(c._head), _radius(c._radius), APrimitive(c._color) {
                c._base = Math::Point3D();
                c._head = Math::Point3D();
                c._radius = 0;
                c._color = {0, 0, 0};
            }

            //* Destructor

            ~Cone() = default;

            //* Operators

            Cone &operator=(const Cone &c){
                if (this != &c) {
                    _base = c._base;
                    _head = c._head;
                    _radius = c._radius;
                    _color = c._color;
                }
                return *this;
            }

            Cone &operator=(Cone &&c) noexcept{
                if (this != &c) {
                    _base = c._base;
                    _head = c._head;
                    _radius = c._radius;
                    _color = c._color;
                    c._base = Math::Point3D();
                    c._head = Math::Point3D();
                    c._radius = 0;
                    c._color = {0, 0, 0};
                }
                return *this;
            }

            //* Methods

            bool hits(const Ray &ray) const{
                const double height = (_head - _base).length();
                const double slope = _radius / height;
                const Math::Point3D O = ray.getOrigin();
                const Math::Vector3D D = ray.getDirection();
                const double a = (D.x * D.x) + (D.z * D.z) - (slope * slope * D.y * D.y);
                const double b = 2 * (O.x * D.x + O.y * D.y - slope * slope * O.z * D.z);
                const double c = (O.x * O.x) + (O.y * O.y) - (slope * slope * O.z * O.z);

                const double discriminant = b * b - 4 * a * c;
                if (discriminant < 0) {
                    return false;
                }

                const double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
                const double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

                const Math::Point3D intersection1 = O + (D * t1);
                const Math::Point3D intersection2 = O + (D * t2);

                const double dist1 =(intersection1 - _base).length();
                const double dist2 =(intersection2 - _base).length();

                if (dist1 < height && dist2 < height) {
                    return true;
                } else if (dist1 < height && dist2 > height) {
                    return true;
                } else if (dist1 > height && dist2 < height) {
                    return true;
                }
                return false;
            }

            double getIntersectionDistance(const Ray &ray) const{
                // Calcul de la hauteur et de la pente du cône
                // const double height = sqrt(pow(_head.x - _base.x, 2) + pow(_head.y - _base.y, 2) + pow(_head.z - _base.z, 2));
                // const double slope = (_base.y - _head.y) / height;

                // // Paramétrage du rayon
                // const Math::Point3D O = ray._origin - _base;
                // const Math::Vector3D D = ray._direction.normalized();

                // // Calcul des coefficients de l'équation quadratique
                // const double a = pow(D.x, 2) + pow(D.z, 2) - pow(D.y, 2) * pow(slope, 2);
                // const double b = 2 * (O.x * D.x + O.z * D.z - O.y * pow(slope, 2) * pow(height - O.y, 2));
                // const double c = pow(O.x, 2) + pow(O.z, 2) - pow(O.y, 2) * pow(slope, 2) * pow(height - O.y, 2);

                // // Résolution de l'équation quadratique
                // const double discriminant = pow(b, 2) - 4 * a * c;
                // if (discriminant == 0) {
                //     // Un seul point d'intersection
                //     const double t = -b / (2 * a);
                //     const Math::Point3D P = O + D * t;
                //     const double dist = (P - _head).length();
                //     if (t >= 0 && dist <= height && dist >= 0) {
                //         // Le point d'intersection est dans le bon intervalle de distance
                //         return t;
                //     }
                // } else {
                //     // Deux points d'intersection
                //     const double t1 = (-b + sqrt(discriminant)) / (2 * a);
                //     const double t2 = (-b - sqrt(discriminant)) / (2 * a);
                //     const Math::Point3D P1 = O + D * t1;
                //     const Math::Point3D P2 = O + D * t2;
                //     const double dist1 = (P1 - _head).length();
                //     const double dist2 = (P2 - _head).length();
                //     if (t1 >= 0 && dist1 <= height && dist1 >= 0) {
                //         // Le premier point d'intersection est dans le bon intervalle de distance
                //         return t1;
                //     } else if (t2 >= 0 && dist2 <= height && dist2 >= 0) {
                //         // Le deuxième point d'intersection est dans le bon intervalle de distance
                //         return t2;
                //     }
                // }
                return 0;
            }

            Math::Point3D getIntersectionPoint(const Ray &ray) const{
                return Math::Point3D();
            }

            void translate(const Math::Vector3D &translation) {
                _base += translation;
                _head += translation;
            }

            // void rotate(const Axis &axis, const double &angle) {
            // }

            void displayPrimitive() const{
                std::cout << "[CONE]" << std::endl;
                std::cout << "Base : {" << _base.x << ", " << _base.y << ", " << _base.z << "}" << std::endl;
                std::cout << "Head : {" << _head.x << ", " << _head.y << ", " << _head.z << "}" << std::endl;
                std::cout << "Radius: " << _radius << std::endl;
                std::cout << "Color : {" << _color.r << ", " << _color.g << ", " << _color.b << "}" << std::endl;
            }

            //* Getters

            const Math::Point3D &getBase() const{
                return _base;
            }

            const Math::Point3D &getHead() const{
                return _head;
            }

            double getRadius() const{
                return _radius;
            }

            //* Setters

            void setBase(const Math::Point3D &base){
                _base = base;
            }

            void setHead(const Math::Point3D &head){
                _head = head;
            }

            void setRadius(double radius){
                _radius = radius;
            }
    };

    class Sphere : public APrimitive{
        public:
            //* Attributes
            Math::Point3D _center;
            double _radius;

            //* Constructors
            Sphere() : _center(), _radius(0), APrimitive({0, 0, 0}) {}

            Sphere(const Math::Point3D &center, double radius, RGB color)
                : _center(center), _radius(radius), APrimitive(color) {}

            Sphere(const Sphere &s)
                : _center(s._center), _radius(s._radius), APrimitive(s._color) {}

            Sphere(Sphere &&s) : _center(s._center), _radius(s._radius), APrimitive(s._color){
                s._center = Math::Point3D();
                s._radius = 0;
                s._color = {0, 0, 0};
            }

            //* Destructor
            ~Sphere() = default;

            //* Operators
            Sphere &operator=(const Sphere &s){
                if (this != &s) {
                    _center = s._center;
                    _radius = s._radius;
                    _color = s._color;
                }
                return *this;
            }

            Sphere &operator=(Sphere &&s) noexcept{
                if (this != &s) {
                    _center = s._center;
                    _radius = s._radius;
                    _color = s._color;
                    s._center = Math::Point3D();
                    s._radius = 0;
                    s._color = {0, 0, 0};
                }
                return *this;
            }

            //* Methods
            bool hits(const Ray &ray) const {
                //printf("Ray origin : %f %f %f\n", ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z);
                Math::Vector3D oc = ray.getOrigin() - _center;
                double a = ray.getDirection().dot(ray.getDirection());
                double b = 2.0 * oc.dot(ray.getDirection());
                double c = oc.dot(oc) - _radius * _radius;
                double discriminant = b * b - 4 * a * c;

				// No solution when d < 0 (ray misses sphere)
				if (discriminant >= 0) {
                    // Distance to nearest intersection point (from quadratic formula)
					float dst = (-b - sqrt(discriminant)) / (2 * a);
					if (dst <=0)
                        return true;
				}
				return false;
			}

            double getIntersectionDistance(const Ray &ray) const{
                double a = ray.getDirection().dot(ray.getDirection());
                double b = 2 * ray.getDirection().dot(ray.getOrigin() - _center);
                double c = (_center - ray.getOrigin()).dot(_center - ray.getOrigin()) - _radius * _radius;
                double discriminant = b * b - 4 * a * c;

                double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
                double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
                return abs((std::min(t1, t2)));
            }

            Math::Point3D getIntersectionPoint(const Ray &ray) const{
                double t = getIntersectionDistance(ray);
                Math::Point3D point = ray.getOrigin() + ray.getDirection() * t;
                return point;
            }

            void translate(const Math::Vector3D &translation) {
                _center += translation;
            }

            // void rotate(const Axis &axis, double angle) {
            // }

            void displayPrimitive() const{
                std::cout << "[SPHERE]" << std::endl;
                std::cout << "Center : {" << _center.x << ", " << _center.y << ", " << _center.z << "}" << std::endl;
                std::cout << "Radius: " << _radius << std::endl;
                std::cout << "Color : {" << _color.r << ", " << _color.g << ", " << _color.b << "}" << std::endl;
            }

            //* Getters
            const Math::Point3D &getCenter() const{
                return _center;
            }

            double getRadius() const{
                return _radius;
            }

            //* Setters
            void setCenter(const Math::Point3D &center){
                _center = center;
            }

            void setRadius(double radius){
                _radius = radius;
            }
    };

    class Plane : public APrimitive {
        public:
            //* Attributes
            int _position;
            Axis _axis;

            //* Constructors
            Plane() : _position(0), _axis(X), APrimitive({0, 0, 0}) {}

            Plane(int position, Axis axis, RGB color)
                : _position(position), _axis(axis), APrimitive(color) {}

            Plane(const Plane &p)
                : _position(p._position), _axis(p._axis), APrimitive(p._color) {}

            Plane(Plane &&p) : _position(p._position), _axis(p._axis), APrimitive(p._color){
                p._position = 0;
                p._axis = X;
                p._color = {0, 0, 0};
            }

            //* Destructor
            ~Plane() = default;

            //* Operators
            Plane &operator=(const Plane &p)
            {
                if (this != &p) {
                    _position = p._position;
                    _axis = p._axis;
                    _color = p._color;
                }
                return *this;
            }

            Plane &operator=(Plane &&p) noexcept
            {
                if (this != &p) {
                    _position = p._position;
                    _axis = p._axis;
                    _color = p._color;
                    p._position = 0;
                    p._axis = X;
                    p._color = {0, 0, 0};
                }
                return *this;
            }
            //* Methods
            Math::Vector3D getNormal() const {
                Math::Vector3D axisVector(0, 0, 0);
                if (_axis == Axis::X) {
                    axisVector = Math::Vector3D(1, 0, 0);
                } else if (_axis == Axis::Y) {
                    axisVector = Math::Vector3D(0, 1, 0);
                } else if (_axis == Axis::Z) {
                    axisVector = Math::Vector3D(0, 0, 1);
                }

                Math::Vector3D orthoVector(0, 0, 0);
                if (_axis == Axis::X) {
                    orthoVector = Math::Vector3D(0, 1, 1);
                } else if (_axis == Axis::Y) {
                    orthoVector = Math::Vector3D(1, 0, 1);
                } else if (_axis == Axis::Z) {
                    orthoVector = Math::Vector3D(1, 1, 0);
                }

                return Math::Vector3D(axisVector.y * orthoVector.z - axisVector.z * orthoVector.y,
                          axisVector.z * orthoVector.x - axisVector.x * orthoVector.z,
                          axisVector.x * orthoVector.y - axisVector.y * orthoVector.x).normalized();
            }

            bool hits(const Ray& ray) const {
                float denominator = 0;
                float numerator = _position; // because the plane equation is Ax + By + Cz + D = 0, D = -position here

                // Depending on the axis, we calculate the denominator differently
                switch (_axis) {
                    case Axis::X: // Plane is orthogonal to X axis, hence normal is (1, 0, 0)
                        denominator = ray._direction.x;
                        numerator += ray._origin.x;
                        break;
                    case Axis::Y: // Plane is orthogonal to Y axis, hence normal is (0, 1, 0)
                        denominator = ray._direction.y;
                        numerator += ray._origin.y;
                        break;
                    case Axis::Z: // Plane is orthogonal to Z axis, hence normal is (0, 0, 1)
                        denominator = ray._direction.z;
                        numerator += ray._origin.z;
                        break;
                }

                // If denominator is 0, the ray is parallel to the plane and they don't intersect
                if (denominator == 0) {
                    return false;
                }

                // Calculate t
                float t = numerator / denominator;

                // If t is negative, the intersection point is behind the origin of the ray
                if (t < 0) {
                    return false;
                }

                // If we've gotten this far, the ray intersects the plane
                return true;
            }

            double getIntersectionDistance(const Ray &ray) const
            {
                float denominator = 0;
                float numerator = _position; // because the plane equation is Ax + By + Cz + D = 0, D = -position here

                // Depending on the axis, we calculate the denominator differently
                switch (_axis) {
                    case Axis::X: // Plane is orthogonal to X axis, hence normal is (1, 0, 0)
                        denominator = ray._direction.x;
                        numerator += ray._origin.x;
                        break;
                    case Axis::Y: // Plane is orthogonal to Y axis, hence normal is (0, 1, 0)
                        denominator = ray._direction.y;
                        numerator += ray._origin.y;
                        break;
                    case Axis::Z: // Plane is orthogonal to Z axis, hence normal is (0, 0, 1)
                        denominator = ray._direction.z;
                        numerator += ray._origin.z;
                        break;
                }

                // If denominator is 0, the ray is parallel to the plane
                if (denominator == 0) {
                    return std::numeric_limits<double>::infinity();
                }

                // Calculate t
                double t = numerator / denominator;

                // If t is negative, the intersection point is behind the origin of the ray
                if (t < 0) {
                    return std::numeric_limits<double>::infinity();
                }
                // Return the intersection distance
                return t;
            }

            Math::Point3D getIntersectionPoint(const Ray &ray) const
            {
                // if (_axis == X)
                //     return (ray.getOrigin().x == _position);
                // else if (_axis == Y)
                //     return (ray.getOrigin().y == _position);
                // else
                //     return (ray.getOrigin().z == _position);
                return Math::Point3D();
            }

            void translate(const Math::Vector3D &translation) {
                switch (_axis) {
                    case Axis::X:
                        _position += translation.x;
                        break;
                    case Axis::Y:
                        _position += translation.y;
                        break;
                    case Axis::Z:
                        _position += translation.z;
                        break;
                }
            }

            // void rotate(const Axis &axis, const double &angle) {
            // }

            void displayPrimitive() const{
                std::cout << "[PLANE]" << std::endl;
                std::cout << "Position : " << _position << std::endl;
                std::cout << "Axis : " << _axis << std::endl;
                std::cout << "Color : {" << _color.r << ", " << _color.g << ", " << _color.b << "}" << std::endl;
            }

            //* Getters
            int getPosition() const{
                return _position;
            }

            Axis getAxis() const{
                return _axis;
            }

            //* Setters
            void setPosition(int position){
                _position = position;
            }

            void setAxis(Axis axis){
                _axis = axis;
            }
    };
}
