#ifndef POINTROTATER_H
#define POINTROTATER_H

#include <math.h>

#include "Quaternion.h"

// Used for finding a point inside the transformed space relative to the original space
void rotateTo(double par_dYaw, double par_dPitch, double& par_dX, double& par_dY, double& par_dZ);

// Used for finding a point inside the original space relative to the transformed space
void rotateFrom(double par_dYaw, double par_dPitch, double& par_dX, double& par_dY, double& par_dZ);

#endif // POINTROTATER_H