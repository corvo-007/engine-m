# EngineM

This is a math engine containing classes for the following:

* [Vector (2D and 3D)](#vector-2d-and-3d)
* [Matrix (3x3)](#matrix-3x3)
* [Quaternion](#quaternion)
* [Curves](#curves)

## Vector (2D and 3D)

- Addition/subtraction
- Scalar multiplication/division
- Dot product
- Cross product
- Magnitude
- Normalisation
- Rotation

## Matrix (3x3)

- Addition/subtraction
- Scalar multiplication/division
- Product
- Vector multiplication
- Inverse
- Transpose

## Quaternion

- Addition/subtraction
- Scalar multiplication/division
- Product
- Norm
- Normalisation
- Conjugate
- Inverse

## Curves
* ### Bezier Curve
  * Evaluation at parameter t
  * De Casteljau Algorithm
  * Tangent, acceleration and normal at parameter t
  * Curve splitting
  * Frenet and Rotation Minimising frames
  * Arc length - Legendre-Gauss Quadrature
* ### Hermite Curve
  * Evaluation at parameter t
  * Tangent, acceleration and normal at parameter t
  * Curve splitting
  * Frenet and Rotation Minimising frames
  * Arc length - Legendre-Gauss Quadrature

## Build

To generate Makefile, run

> cmake -B build -S .

To build the project, run

> cmake --build build
