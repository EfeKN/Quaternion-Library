#include "Quaternion.h"
#include "PointRotater.h"

// Used for finding a point inside the transformed space relative to the original space
// Enter as radians
void rotateTo(double par_dYaw, double par_dPitch, double& par_dX, double& par_dY, double& par_dZ) {
  Quaternion qy(par_dPitch, 0, 1, 0);
  Quaternion qz(par_dYaw, 0, 0, 1);
  
  Quaternion q = qy * qz;
  
  Quaternion q_conj = q.conjugate();

  Quaternion p(0, par_dX, par_dY, par_dZ, InitType::Components);

  Quaternion res = q_conj * p * q;

  res.print();

  par_dX = res.getX();
  par_dY = res.getY();
  par_dZ = res.getZ();
}

// Used for finding a point inside the original space relative to the transformed space
void rotateFrom(double par_dYaw, double par_dPitch, double& par_dX, double& par_dY, double& par_dZ) {
  Quaternion qy(par_dPitch, 0, 1, 0);
  Quaternion qz(par_dYaw, 0, 0, 1);

  Quaternion q = qy * qz;

  Quaternion q_conj = q.conjugate();

  Quaternion p(0, par_dX, par_dY, par_dZ, InitType::Components);

  Quaternion res = q * p * q_conj;

  res.print();

  par_dX = res.getX();
  par_dY = res.getY();
  par_dZ = res.getZ();
}