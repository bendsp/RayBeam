/*
** EPITECH PROJECT, 2022
** bootstrapRaytracer
** File description:
** raytracer.hpp
*/

#pragma once

#include "math.hpp"

namespace RayTracer {
    class Ray {
        public:
            //* Attributes
            Math::Point3D _origin;
            Math::Vector3D _direction;

            //* Constructors
            Ray() : _origin(), _direction() {}

            Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
                : _origin(origin), _direction(direction) {}

            Ray(const Ray &r)
                : _origin(r._origin), _direction(r._direction) {}

            Ray(Ray &&r) : _origin(r._origin), _direction(r._direction) {
                r._origin = Math::Point3D();
                r._direction = Math::Vector3D();
            }

            //* Destructor
            ~Ray() = default;

            //* Operators
            Ray &operator=(const Ray &r) {
                if (this != &r) {
                    _origin = r._origin;
                    _direction = r._direction;
                }
                return *this;
            }

            Ray &operator=(Ray &&r) noexcept {
                if (this != &r) {
                    _origin = r._origin;
                    _direction = r._direction;
                    r._origin = Math::Point3D();
                    r._direction = Math::Vector3D();
                }
                return *this;
            }

            //* Getters
            const Math::Point3D &getOrigin() const {
                return _origin;
            }

            const Math::Vector3D &getDirection() const {
                return _direction;
            }

            //* Setters
            void setOrigin(const Math::Point3D &origin) {
                _origin = origin;
            }

            void setDirection(const Math::Vector3D &direction) {
                _direction = direction;
            }
    };

    class Sphere {
        public:
            //* Attributes
            Math::Point3D _center;
            double _radius;

            //* Constructors
            Sphere() : _center(), _radius(0) {}

            Sphere(const Math::Point3D &center, double radius)
                : _center(center), _radius(radius) {}

            Sphere(const Sphere &s) : _center(s._center), _radius(s._radius) {}

            Sphere(Sphere &&s) : _center(s._center), _radius(s._radius) {
                s._center = Math::Point3D();
                s._radius = 0;
            }

            //* Destructor
            ~Sphere() = default;

            //* Operators
            Sphere &operator=(const Sphere &s) {
                if (this != &s) {
                    _center = s._center;
                    _radius = s._radius;
                }
                return *this;
            }

            Sphere &operator=(Sphere &&s) noexcept {
                if (this != &s) {
                    _center = s._center;
                    _radius = s._radius;
                    s._center = Math::Point3D();
                    s._radius = 0;
                }
                return *this;
            }

            //* Methods
            bool hits (const Ray &ray) const {
                Math::Vector3D oc = ray.getOrigin() - _center;
                double a = ray.getDirection().dot(ray.getDirection());
                double b = 2.0 * oc.dot(ray.getDirection());
                double c = oc.dot(oc) - _radius * _radius;
                double discriminant = b * b - 4 * a * c;
                return (discriminant > 0);
            }

            //* Getters
            const Math::Point3D &getCenter() const {
                return _center;
            }

            double getRadius() const {
                return _radius;
            }

            //* Setters
            void setCenter(const Math::Point3D &center) {
                _center = center;
            }

            void setRadius(double radius) {
                _radius = radius;
            }
    };

    class Camera {
        public:
            //* Attributes
            Math::Point3D _origin;
            Math::Rectangle3D _screen;

            //* Constructors
            Camera() : _origin(0, 0, 0), _screen() {}

            Camera(const Math::Point3D &origin, const Math::Rectangle3D &screen)
                : _origin(origin), _screen(screen) {}

            Camera(const Camera &c)
                : _origin(c._origin), _screen(c._screen) {}

            Camera(Camera &&c) : _origin(c._origin), _screen(c._screen) {
                c._origin = Math::Point3D();
                c._screen = Math::Rectangle3D();
            }

            //* Destructor
            ~Camera() = default;

            //* Operators
            Camera &operator=(const Camera &c) {
                if (this != &c) {
                    _origin = c._origin;
                    _screen = c._screen;
                }
                return *this;
            }

            Camera &operator=(Camera &&c) noexcept {
                if (this != &c) {
                    _origin = c._origin;
                    _screen = c._screen;
                    c._origin = Math::Point3D();
                    c._screen = Math::Rectangle3D();
                }
                return *this;
            }

            //* Methods
            RayTracer::Ray ray(double u, double v) const {
                Math::Point3D pOnScreen = _screen.pointAt(u, v);
                Math::Vector3D direction = pOnScreen - _origin;
                return RayTracer::Ray(_origin, direction);
            }

            //* Getters
            const Math::Point3D &getOrigin() const {
                return _origin;
            }

            const Math::Rectangle3D &getScreen() const {
                return _screen;
            }

            //* Setters
            void setOrigin(const Math::Point3D &origin) {
                _origin = origin;
            }

            void setScreen(const Math::Rectangle3D &screen) {
                _screen = screen;
            }
    };
}
