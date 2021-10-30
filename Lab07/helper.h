#pragma once

#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159265358979;
const double INTERVAL = 0.5;

/* {Speed (mach), Drag Coefficient} */
double dragCoeffs[16][2] = {
	{0.300, 0.1629},
	{0.500, 0.1659},
	{0.700, 0.2031},
	{0.890, 0.2597},
	{0.920, 0.3010},
	{0.960, 0.3287},
	{0.980, 0.4002},
	{1.000, 0.4258},
	{1.020, 0.4335},
	{1.060, 0.4483},
	{1.240, 0.4064},
	{1.530, 0.3663},
	{1.990, 0.2897},
	{2.870, 0.2297},
	{2.890, 0.2306},
	{5.000, 0.2656}
};

/* {Altitude (m), Density (kg/m^2)} */
double densities[20][2] = {
	{0, 1.2250000},
	{1000, 1.1120000},
	{2000, 1.0070000},
	{3000, 0.9093000},
	{4000, 0.8194000},
	{5000, 0.7364000},
	{6000, 0.6601000},
	{7000, 0.5900000},
	{8000, 0.5258000},
	{9000, 0.4671000},
	{10000, 0.4135000},
	{15000, 0.1948000},
	{20000, 0.0889100},
	{25000, 0.0400800},
	{30000, 0.0184100},
	{40000, 0.0039960},
	{50000, 0.0010270},
	{60000, 0.0003097},
	{70000, 0.0000828},
	{80000, 0.0000185}
};

/* {Altitude (m), Speed of Sound (m/s)} */
double speedsOfSound[16][2] = {
	{0, 340},
	{1000, 336},
	{2000, 332},
	{3000, 328},
	{4000, 324},
	{5000, 320},
	{6000, 316},
	{7000, 312},
	{8000, 308},
	{9000, 303},
	{10000, 299},
	{15000, 295},
	{20000, 295},
	{25000, 295},
	{30000, 305},
	{40000, 324}
};

/* {Altitude (m), Acceleration due to gravity (m/s^2)} */
double accelerationsOfGravity[14][2] = {
	{0, 9.807},
	{1000, 9.804},
	{2000, 9.801},
	{3000, 9.797},
	{4000, 9.794},
	{5000, 9.791},
	{6000, 9.788},
	{7000, 9.785},
	{8000, 9.782},
	{9000, 9.779},
	{10000, 9.776},
	{15000, 9.761},
	{20000, 9.745},
	{25000, 9.730}
};


/* Get closest index to value for linear interpolation */
int closestIndex(double dataArray[][2], int length, double compareNum) {
	int i = 0;
	while (i < length && compareNum > dataArray[i][0]) i++;
	return i;
}

/// <summary>
/// Convert angle from degrees to radians
/// </summary>
/// <param name="angle">Angle in degrees</param>
/// <returns>Angle in radians</returns>
double deg2rad(double angle) {
	return angle * PI / 180;
}

/// <summary>
/// Convert angle from radians to degrees
/// </summary>
/// <param name="angle">Angle in radians</param>
/// <returns>Angle in degrees</returns>
double rad2deg(double angle) {
	return 180 * angle / PI;
}

/// <summary>
/// Linearly interpolate values
/// </summary>
/// <param name="d">First component of middle point</param>
/// <param name="d0">First component of first point</param>
/// <param name="r0">Second component of first point</param>
/// <param name="d1">First component of second point</param>
/// <param name="r1">Second component of second point</param>
/// <returns>Second component of middle point</returns>
double interpolate(double d, double d0, double r0, double d1, double r1) {
	return ((r1 - r0) * (d - d0) / (d1 - d0)) + r0;
}

/// <summary>
/// Calculate speed in mach based on altitude
/// </summary>
/// <param name="altitude">Current altitude</param>
/// <param name="speed">Current speed in meters per second</param>
/// <returns>Speed in mach</returns>
double calcMach(double altitude, double speed) {
	int i = closestIndex(speedsOfSound, 16, altitude);
	double currentSpeedOfSound = interpolate(altitude, speedsOfSound[i - 1][0], speedsOfSound[i - 1][1], speedsOfSound[i][0], speedsOfSound[i][1]);
	return speed / currentSpeedOfSound;
}