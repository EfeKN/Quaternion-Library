# Point Rotation with Quaternions

This project provides an implementation of 3D point rotation using quaternions. The implementation consists of two main files:

- `PointRotater.cpp`: Contains functions for rotating points using quaternions.
- `Quaternion.cpp`: Implements a Quaternion class that supports various quaternion operations.

## Overview

### 1. Quaternion Class (`Quaternion.cpp`)

The `Quaternion` class provides a robust framework for quaternion operations, including initialization, conjugation, normalization, and algebraic operations (addition, subtraction, multiplication, and division). The class supports two main initialization types:

- **Components**: Directly initializes a quaternion using four components (W, X, Y, Z).
- **Axis-Angle**: Initializes a quaternion from an axis-angle representation, where the quaternion represents a rotation around a specified axis by a given angle.

#### Key Methods

- **Getters and Setters**: Accessor and mutator methods for the quaternion components (`getW()`, `getX()`, `getY()`, `getZ()`, `setW()`, `setX()`, `setY()`, `setZ()`).
- **print()**: Prints the quaternion components to the console.
- **testUnitQuaternion()**: Prints the length of the quaternion to verify if it is a unit quaternion.
- **normalize()**: Normalizes the quaternion to ensure it is a unit quaternion.
- **conjugate()**: Returns the conjugate of the quaternion.
- **Operator Overloads**: Supports addition (`+`), subtraction (`-`), multiplication (`*`), and division (`/`) of quaternions.

### 2. Point Rotater (`PointRotater.cpp`)

This file contains two main functions:

- **rotateTo(double par_dYaw, double par_dPitch, double& par_dX, double& par_dY, double& par_dZ)**: Rotates a point from the original space to the transformed space using the given yaw and pitch angles. The quaternion is constructed from the provided angles, and the point is transformed accordingly.

- **rotateFrom(double par_dYaw, double par_dPitch, double& par_dX, double& par_dY, double& par_dZ)**: Rotates a point from the transformed space back to the original space. The quaternion operations are applied in reverse to achieve the inverse rotation.

### Quaternion Operations

The quaternion multiplication is used in both functions to apply the rotation to the point in space. The conjugate of the quaternion is used to reverse the rotation, ensuring the point is correctly transformed in either direction.

## Usage

To rotate a point, you can use the `rotateTo` and `rotateFrom` functions provided in `pointrotater.cpp`. These functions take the yaw and pitch angles as inputs (in radians) along with the coordinates of the point to be rotated.

```cpp
double x = 1.0, y = 0.0, z = 0.0;
double yaw = 0.5;  // Example yaw angle in radians
double pitch = 0.5;  // Example pitch angle in radians

// Rotate point to transformed space
rotateTo(yaw, pitch, x, y, z);

// Rotate point back to original space
rotateFrom(yaw, pitch, x, y, z);
```

## License

This library is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Acknowledgments

- The implementation is based on the mathematical representation of quaternions and their operations.
- The library uses the standard C++ library for mathematical functions and input-output operations.
