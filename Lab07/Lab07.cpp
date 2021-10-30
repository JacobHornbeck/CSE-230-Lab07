/*************************************************************
 * 1. Name:
 *      Jacob Hornbeck and Julie Cowley
 * 2. Assignment Name:
 *      Lab 07: Artillery Prototype
 * 3. Assignment Description:
 *      Simulate a projectile landing
 * 4. What was the hardest part? Be as specific as possible.
 *      I think the hardest parts were writing a function to
 *      find the values from the tables to use with linear
 *      interpolation and getting the values for the example
 *      to be closer to the output of the example.
 * 5. How long did it take for you to complete the assignment?
 *      We worked on this lab 2 different days for about 2 hours
 *      each day, and then I (Jacob) worked on it about 5 hours.
 *****************************************************************/

#include "Projectile.h"

int main() {
    Projectile missile = Projectile();
    missile.runTest();

    return 0;
}
