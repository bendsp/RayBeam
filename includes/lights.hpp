#pragma once

#include "math.hpp"
#include <iostream>

class Core;

namespace RayTracer {
    class ILight {
        public:
            ILight() = default;
            virtual ~ILight() = default;
            virtual double getBrightness() const = 0;
            virtual void setBrightness(double brightness) = 0;
            virtual double getIntensity(const Math::Point3D &point) const = 0;
            virtual Math::Point3D getPosition() const = 0;
            virtual void displayLight() const = 0;
    };

    class ALight : public ILight {
        public:
            ALight() : _ambient(0), _diffuse(0), _position({0, 0, 0}) {};
            ALight(double ambient, double diffuse, Math::Point3D position)
                : _ambient(ambient), _diffuse(diffuse), _position(position) {};
            virtual ~ALight() = default;

            //* Methods
            //TODO: write methods
            double getBrightness() const override {
                return _diffuse;
            }

            void setBrightness(double brightness) override {
            }

            double getIntensity(const Math::Point3D &point) const override {
                return 0;
            }

            //* Getters
            double getAmbient() const {
                return _ambient;
            }

            double getDiffuse() const {
                return _diffuse;
            }

            Math::Point3D getPosition() const {
                return _position;
            }

            //* Setters
            void setAmbient(double ambient) {
                _ambient = ambient;
            }

            void setDiffuse(double diffuse) {
                _diffuse = diffuse;
            }

            void setPosition(Math::Point3D position) {
                _position = position;
            }

        protected:
            double _ambient;
            double _diffuse;
            Math::Point3D _position;
    };

    class PointLight : public ALight {
        public:
            //* Constructors
            PointLight() : ALight(0, 0, {0, 0, 0}) {};

            PointLight(Math::Point3D position, double ambient, double diffuse)
                : ALight(ambient, diffuse, position) {};

            PointLight(const PointLight &l)
                : ALight(l._ambient, l._diffuse, l._position) {};

            PointLight(PointLight &&l) : ALight(l._ambient, l._diffuse, l._position) {
                l.setAmbient(0);
                l.setDiffuse(0);
                l.setPosition({0, 0, 0});
            };

            //* Destructor
            ~PointLight() = default;

            //* Operators
            PointLight &operator=(const PointLight &l) {
                if (this != &l) {
                    _position = l._position;
                    _ambient = l._ambient;
                    _diffuse = l._diffuse;
                }
                return *this;
            }

            PointLight &operator=(PointLight &&l) noexcept {
                if (this != &l) {
                    _position = l._position;
                    _ambient = l._ambient;
                    _diffuse = l._diffuse;
                    l.setPosition({0, 0, 0});
                    l.setAmbient(0);
                    l.setDiffuse(0);
                }
                return *this;
            }

            //* Methods
            void displayLight(void) const {
                std::cout << "[POINT LIGHT]" << std::endl;
                std::cout << "Position : {" << _position.x << ", " << _position.y << ", " << _position.z << "}" << std::endl;
                std::cout << "Ambient: " << _ambient << std::endl;
                std::cout << "Diffuse: " << _diffuse << std::endl;
            }
    };

    class DirectionalLight : public ALight {
        public:
            //* Attributes
            Math::Vector3D _direction;

            //* Constructors
            DirectionalLight() : ALight(0, 0, {0, 0, 0})
            {
                _direction = Math::Vector3D(0, 0, 0);
            };

            DirectionalLight(Math::Point3D position, Math::Vector3D direction, double ambient, double diffuse)
                : ALight(ambient, diffuse, position), _direction(direction) {};

            DirectionalLight(const DirectionalLight &l)
                : ALight(l._ambient, l._diffuse, l._position), _direction(l._direction) {};

            DirectionalLight(DirectionalLight &&l) : ALight(l._ambient, l._diffuse, l._position), _direction(l._direction) {
                l.setAmbient(0);
                l.setDiffuse(0);
                l.setPosition({0, 0, 0});
                l._direction = Math::Vector3D(0, 0, 0);;
            };

            //* Destructor
            ~DirectionalLight() = default;

            //* Operators
            DirectionalLight &operator=(const DirectionalLight &l) {
                if (this != &l) {
                    _position = l._position;
                    _ambient = l._ambient;
                    _diffuse = l._diffuse;
                    _direction = l._direction;
                }
                return *this;
            }

            DirectionalLight &operator=(DirectionalLight &&l) noexcept {
                if (this != &l) {
                    _position = l._position;
                    _ambient = l._ambient;
                    _diffuse = l._diffuse;
                    _direction = l._direction;
                    l.setPosition({0, 0, 0});
                    l.setAmbient(0);
                    l.setDiffuse(0);
                    l._direction = Math::Vector3D(0, 0, 0);
                }
                return *this;
            }

            //* Methods
            void displayLight(void) const {
                std::cout << "[DIRECTIONAL LIGHT]" << std::endl;
                std::cout << "Position : {" << _position.x << ", " << _position.y << ", " << _position.z << "}" << std::endl;
                std::cout << "Direction: {" << _direction.x << ", " << _direction.y << ", " << _direction.z << "}" << std::endl;
                std::cout << "Ambient: " << _ambient << std::endl;
                std::cout << "Diffuse: " << _diffuse << std::endl;
            }

            //* Getters
            Math::Vector3D getDirection() const {
                return _direction;
            }

            //* Setters
            void setDirection(Math::Vector3D direction) {
                _direction = direction;
            }
    };
}
