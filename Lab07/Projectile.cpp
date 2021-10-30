#include "helper.h"
#include "Projectile.h"

const bool DEBUG = false;

Projectile::Projectile() {}
Projectile::~Projectile() {}

/// <summary>
/// Initialize the projectile with default values and specified angle
/// </summary>
/// <param name="angle">Angle of gun</param>
void Projectile::initialize(double angle) {
    diameter = 0.15489;
    mass = 46.7;
    initial_speed = 827.0;
    pos.set(0.0, 0.0);
    vel.set(initial_speed * sin(deg2rad(angle)),
            initial_speed * cos(deg2rad(angle)));
    surfaceArea = PI * pow(diameter / 2, 2);
}

/// <summary>
/// Run test to see the distance and hangtime of the projectile
/// </summary>
void Projectile::runTest() {
    string testAgain = "n";
    do {
        double ang;
        cout << "What is the angle of the howitzer where 0 is up? ";
        cin >> ang;
        initialize(ang);

        double hangtime = 0.0;
        double prevDistance = 0.0;
        double totalDistance = 0.0;
        double prevAltitude = 0.0;
        double timeToHit = 0.0;

        do {
            if (DEBUG) {
                cout << endl << "x, y: " << pos.x << ", " << pos.y << endl;
                cout << "vx, vy: " << vel.x << ", " << vel.y << endl;
            }
            prevDistance = pos.x;
            prevAltitude = pos.y;
            updatePosition();
            updateVelocity();
            hangtime += INTERVAL;
        } while (this->pos.y > 0);

        timeToHit = interpolate(0, prevAltitude, hangtime - INTERVAL, pos.y, hangtime);
        totalDistance = interpolate(timeToHit, hangtime - INTERVAL, prevDistance, hangtime, pos.x);

        cout << "Distance:     " << round(totalDistance * 100) / 100
             << "m       Hang Time:     " << round(timeToHit * 100) / 100 << "s" << endl;

        cout << endl << "Would you like to test again? (y/n) ";
        cin >> testAgain;
        cout << endl << endl;
    } while (testAgain == "y" || testAgain == "Y");
}

/// <summary>
/// Get acceleration of gravity based on the altitude
/// </summary>
/// <param name="altitude">Current altitude</param>
/// <returns>Acceleration of gravity for current altitude</returns>
double Projectile::getGravity(double altitude) {
    int i = closestIndex(accelerationsOfGravity, 14, altitude);
    return interpolate(altitude, accelerationsOfGravity[i][0], accelerationsOfGravity[i][1], accelerationsOfGravity[i - 1][0], accelerationsOfGravity[i - 1][1]);
}

/// <summary>
/// Get density of air based on the altitude
/// </summary>
/// <param name="altitude">Current altitude</param>
/// <returns>Density of air for current altitude</returns>
double Projectile::getDensity(double altitude) {
    int i = closestIndex(densities, 20, altitude);
    return interpolate(altitude, densities[i][0], densities[i][1], densities[i - 1][0], densities[i - 1][1]);
}

/// <summary>
/// Get drag coefficient based on the speed in mach
/// </summary>
/// <param name="mach">Current speed in mach</param>
/// <returns>Drag coefficient for current speed</returns>
double Projectile::getDragCoefficient(double mach) {
    int i = closestIndex(dragCoeffs, 16, mach);
    return interpolate(mach, dragCoeffs[i][0], dragCoeffs[i][1], dragCoeffs[i - 1][0], dragCoeffs[i - 1][1]);
}

/// <summary>
/// Calculate the force due to drag
/// </summary>
/// <param name="c">Drag coefficient</param>
/// <param name="p">Density</param>
/// <param name="v">Velocity</param>
/// <param name="a">Surface area</param>
/// <returns></returns>
double Projectile::getDragForce(double c, double p, double v, double a) {
    return (0.5 * c * p * pow(v, 2) * a);
}

/// <summary>
/// Get the angle based on the speed
/// </summary>
/// <returns>Current angle in radians</returns>
double Projectile::getAngle() {
    return atan2(vel.x, vel.y);
}

/// <summary>
/// Move the position based on the current velocity and time interval
/// </summary>
void Projectile::updatePosition() {
    PVector temp = vel.copy();
    temp.mult(INTERVAL);
    pos.add(temp);
}

/// <summary>
/// Change the velocity based on gravity and drag
/// </summary>
void Projectile::updateVelocity() {
    double angle = getAngle();
    double mach = calcMach(pos.y, vel.mag());
    double dragCoeff = getDragCoefficient(mach);
    double density = getDensity(pos.y);
    double dragForce = getDragForce(dragCoeff, density, vel.mag(), surfaceArea);

    if (DEBUG) {
        cout << "Angle: " << rad2deg(angle) << endl
             << "Mach: " << mach << endl
             << "Drag c: " << dragCoeff << endl
             << "Density: " << density << endl
             << "Velocity: " << vel.mag() << endl
             << "Surface area: " << surfaceArea << endl
             << "Drag force: " << dragForce << endl;
    }

    PVector acc = PVector(sin(angle), cos(angle));
    acc.mult(dragForce);
    acc.div(mass);
    acc.add(0, getGravity(pos.y));
    acc.mult(INTERVAL);
    vel.sub(acc);
}
