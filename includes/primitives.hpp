/*
** EPITECH PROJECT, 2022
** B-OOP-400-BER-4-1-raytracer-paul.thiebault
** File description:
** primitives.hpp
*/

#pragma once

#include "raytracer.hpp"

namespace RayTracer {
    class IPrimitive {
        public:
            IPrimitive() = default;
            virtual ~IPrimitive() = default;
            virtual bool hits(const Ray &ray) const = 0;
    };
    class Sphere : public IPrimitive {
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
            bool hits(const Ray &ray) const {
                Math::Vector3D oc = ray.getOrigin() - _center;
                double a = ray.getDirection().dot(ray.getDirection());
                double b = 2.0 * oc.dot(ray.getDirection());
                double c = oc.dot(oc) - _radius * _radius;
                double discriminant = b * b - 4 * a * c;
                return (discriminant >= 0);
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
}