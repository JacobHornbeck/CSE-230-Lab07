#pragma once

#include <cmath>

using namespace std;

/**********************************
 * PVector Class
 *   Auther: Jacob Hornbeck
 **********************************/
class PVector {
    public:

        /// <summary>
        /// x component
        /// </summary>
        double x;

        /// <summary>
        /// y component
        /// </summary>
        double y;


        /// <summary>
        /// Initialize a new PVector
        /// </summary>
        /// <param name="x">Initial horizontal position</param>
        /// <param name="y">Initial vertical position</param>
        PVector(double x, double y) {
            this->x = x;
            this->y = y;
        }

        /// <summary>
        /// Copy PVector values to a new PVector
        /// </summary>
        /// <returns>A copy of the original PVector</returns>
        PVector copy() {
            return PVector(this->x, this->y);
        }

        /// <summary>
        /// Adds two PVectors together
        /// </summary>
        /// <param name="v2">Another PVector</param>
        void add(PVector v2) {
            this->x += v2.x;
            this->y += v2.y;
        }

        /// <summary>
        /// Add components to original PVector
        /// </summary>
        /// <param name="x">x component</param>
        /// <param name="y">y component</param>
        void add(double x, double y) {
            this->x += x;
            this->y += y;
        }

        /// <summary>
        /// Subtract a PVector from the original
        /// </summary>
        /// <param name="v2">Another PVector</param>
        void sub(PVector v2) {
            this->x -= v2.x;
            this->y -= v2.y;
        }

        /// <summary>
        /// Subtract components from original PVector
        /// </summary>
        /// <param name="x">x component</param>
        /// <param name="y">y component</param>
        void sub(double x, double y) {
            this->x -= x;
            this->y -= y;
        }

        /// <summary>
        /// Multiply PVector by a scaler
        /// </summary>
        /// <param name="n">Scaler value</param>
        void mult(double n) {
            this->x *= n;
            this->y *= n;
        }

        /// <summary>
        /// Divide PVector by a divisor
        /// </summary>
        /// <param name="n">Divisor value</param>
        void div(double n) {
            this->x /= n;
            this->y /= n;
        }

        /// <summary>
        /// Set component values of PVector
        /// </summary>
        /// <param name="x">x component</param>
        /// <param name="y">y component</param>
        void set(double x, double y) {
            this->x = x;
            this->y = y;
        }

        /// <summary>
        /// Get the magnitude of the PVector
        /// </summary>
        /// <returns>Magnitude of the PVector</returns>
        double mag() {
            return sqrt(pow(this->x, 2) + pow(this->y, 2));
        }
};

class Projectile {

    public:
        Projectile();
       ~Projectile();

        void runTest();

    private:
        PVector vel = PVector(0.0, 0.0);
        PVector pos = PVector(0.0, 0.0);
        double  diameter = 0.0,
                mass = 0.0,
                initial_speed = 0.0,
                surfaceArea = 0.0;

        double  getGravity(double);
        double  getDensity(double);
        double  getDragCoefficient(double);
        double  getDragForce(double, double, double, double);
        double  getAngle();
        void    updatePosition();
        void    updateVelocity();
        void    initialize(double);
};

