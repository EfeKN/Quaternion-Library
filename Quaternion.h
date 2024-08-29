#ifndef QUATERNION_H
#define QUATERNION_H

enum class InitType { // Quaternions can be initialized in different ways
  Components, // Directly inputting 4 components
  AxisAngle // Defining a rotation axis and angle
};

class Quaternion {
public:
  Quaternion(double par_dW, double par_dX, double par_dY, double par_dZ, InitType type = InitType::AxisAngle);

  // Getters
  double getW() const;
  double getX() const;
  double getY() const;
  double getZ() const;

  // Setters
  void setW(double par_dW);
  void setX(double par_dX);
  void setY(double par_dY);
  void setZ(double par_dZ);

  // Testing tools
  void print();
  void testUnitQuaternion();

  // Normalization
  void normalize();

  Quaternion conjugate() const;

  // Quaternion Algebric Operations
  Quaternion operator+(const Quaternion &q) const;
  Quaternion operator-(const Quaternion &q) const;
  Quaternion operator*(const Quaternion &q) const;
  Quaternion operator/(const Quaternion &q) const;

private:
  double dW;
  double dX;
  double dY;
  double dZ;

};

#endif // QUATERNION_H