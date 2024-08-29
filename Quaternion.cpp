#include <iostream>
#include <cmath>

#include "Quaternion.h"

Quaternion::Quaternion(double par_dW, double par_dX, double par_dY, double par_dZ, InitType type) {
  switch (type) {
    case InitType::Components:
      // Initialize from components
      // This should not be normalized here because Quaternion structure is also used for 3D points
      dW = par_dW;
      dX = par_dX;
      dY = par_dY;
      dZ = par_dZ;

      //this->normalize();
      break;
    case InitType::AxisAngle:
      // Initialize from axis-angle (par_dW is the angle, par_dX, par_dY, par_dZ are the axis)
      double angle = par_dW;

      // Normalize the axis
      // WARNING: If the axis is a zero vector, the result is undefined, handle it accordingly
      double length = std::sqrt(par_dX * par_dX + par_dY * par_dY + par_dZ * par_dZ);

      // If you are using predefined rotation axes such as
      // (0, 0, 1) for Z, 
      // (0, 1, 0) for Y, and 
      // (1, 0, 0) for X
      // This should never occur

      // If you are using a cross product to define the rotation axis, if the components of the cross product are parallel, the above WARNING occurs. In this case check for the angle between components. It is either 0 or 180 degrees. In the 0 case do nothing, in the 180 case negate the axis. This should be handled in the PointRotater class.
      
      if(length == 0.0) {
        std::cout << "Rotation axis is a zero vector, setting quaternion parameters to (1,0,0,0)" << std::endl;
        dW = 1;
        dX = 0;
        dY = 0;
        dZ = 0;
      }

      // This is a UNIT QUATERNION
      // Angles must be given in radians
      double sinHalfAngle = std::sin(angle / 2);
      dW = std::cos(angle / 2);
      dX = (par_dX / length) * sinHalfAngle;
      dY = (par_dY / length) * sinHalfAngle;
      dZ = (par_dZ / length) * sinHalfAngle;
      break;

      // This produces unit quaternions
      // For q to be a unit quaternion
      // sqrt( w^2 + x^2 + y^2 + z^2 ) = 1
      // Since rotation axis is normalized => x^2 + y^2 + z^2 = 1 holds

      // w = cos(halfAngle)
      // x = sin(halfAngle) * rotation.x
      // y = sin(halfAngle) * rotation.y
      // z = sin(halfAngle) * rotation.z

      // sqrt( cos^2(halfAngle) + sin^2(halfAngle) * (x^2 + y^2 + z^2) )
      // sqrt( cos^2(halfAngle) + sin^2(halfAngle) ) = 1

      // Hence the returned quaternion is a unit quaternion
  }
}

// Getters
double Quaternion::getW() const { return dW; }
double Quaternion::getX() const { return dX; }
double Quaternion::getY() const { return dY; }
double Quaternion::getZ() const { return dZ; }

// Setters
void Quaternion::setW(double par_dW) { dW = par_dW; }
void Quaternion::setX(double par_dX) { dX = par_dX; }
void Quaternion::setY(double par_dY) { dY = par_dY; }
void Quaternion::setZ(double par_dZ) { dZ = par_dZ; }

void Quaternion::print() {
  std::cout << "Quaternion: (" << dW << ", " << dX << ", " << dY << ", " << dZ << ")" << std::endl;
}

// Testing for unit quaternion
void Quaternion::testUnitQuaternion() {
  std::cout << "Length: " << sqrt(dW*dW + dX*dX + dY*dY + dZ*dZ) << std::endl;
}

void Quaternion::normalize() {
  double norm = std::sqrt(dW * dW + dX * dX + dY * dY + dZ * dZ);

  if(norm == 0) {
    std::cout << "Quaternion is a zero vector, setting quaternion parameters to (1, 0, 0, 0)" << std::endl;

    this->dW = 1;
    this->dX = 0;
    this->dY = 0;
    this->dZ = 0;

    return void();
  }

  this->dW = dW / norm;
  this->dX = dX / norm;
  this->dY = dY / norm;
  this->dZ = dZ / norm;
}

Quaternion Quaternion::conjugate() const {
  // Conjugate of a quaternion is calculated this way
  return Quaternion(dW, -dX, -dY, -dZ, InitType::Components);
}

// Quaternion Algebric Operations
Quaternion Quaternion::operator+(const Quaternion &q) const {
  return Quaternion(dW + q.dW, dX + q.dX, dY + q.dY, dZ + q.dZ, InitType::Components);
}

Quaternion Quaternion::operator-(const Quaternion &q) const {
  return Quaternion(dW - q.dW, dX - q.dX, dY - q.dY, dZ - q.dZ, InitType::Components);
}

Quaternion Quaternion::operator*(const Quaternion &q) const {
  return Quaternion(dW * q.dW - dX * q.dX - dY * q.dY - dZ * q.dZ,
                    dW * q.dX + dX * q.dW + dY * q.dZ - dZ * q.dY,
                    dW * q.dY - dX * q.dZ + dY * q.dW + dZ * q.dX,
                    dW * q.dZ + dX * q.dY - dY * q.dX + dZ * q.dW,
                    InitType::Components);
}

Quaternion Quaternion::operator/(const Quaternion &q) const {
  // This is not used anywhere to calculate rotations but it may be of use later. Since it is a quaternion library, it makes sense to have all algebric operations for the structure
  
  double norm_sq = q.dW * q.dW + q.dX * q.dX + q.dY * q.dY + q.dZ * q.dZ;
  double inv_norm_sq = 1.0 / norm_sq;

  double new_w = (dW * q.dW + dX * q.dX + dY * q.dY + dZ * q.dZ) * inv_norm_sq;
  double new_x = (dX * q.dW - dW * q.dX - dZ * q.dY + dY * q.dZ) * inv_norm_sq;
  double new_y = (dY * q.dW + dZ * q.dX - dW * q.dY - dX * q.dZ) * inv_norm_sq;
  double new_z = (dZ * q.dW - dY * q.dX + dX * q.dY - dW * q.dZ) * inv_norm_sq;

  return Quaternion(new_w, new_x, new_y, new_z, InitType::Components);
}