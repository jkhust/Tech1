//
//  Vector.c++
//  Tech1
//
//  Created by Justin Hust on 12/29/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <math.h>
#include "Vector.h"

// ----------------------------------------------
Vec3::Vec3(void) {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;

}

// ----------------------------------------------
Vec3::Vec3(float x_, float y_, float z_) {
  x = x_;
  y = y_;
  z = z_;

}
  
// ----------------------------------------------
Vec3::Vec3(float v[]) {
  x = v[0];
  y = v[1];
  z = v[2];

}

// ----------------------------------------------
Vec3::Vec3(const Vec3 &v) {
  x = v.x;
  y = v.y;
  z = v.z;

}

// ----------------------------------------------
Vec3 & Vec3::operator = (const Vec3 &v) {
  x = v.x;
  y = v.y;
  z = v.z;
  
  return *this;

}

// ----------------------------------------------
void Vec3::operator += (const Vec3 &v) {
  x += v.x;
  y += v.y;
  z += v.z;

}

// ----------------------------------------------
void Vec3::operator -= (const Vec3 &v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;

}

// ----------------------------------------------
void Vec3::operator *= (float f) {
  x *= f;
  y *= f;
  z *= f;

}

// ----------------------------------------------
void Vec3::operator /= (float f) {
  x /= f;
  y /= f;
  z /= f;

}

// ----------------------------------------------
Vec3 Vec3::operator + (const Vec3 &v) const {
  return Vec3( x + v.x, y + v.y, z + v.z );

}

// ----------------------------------------------
Vec3 Vec3::operator - (const Vec3 &v) const {
  return Vec3( x - v.x, y - v.y, z - v.z );

}

// ----------------------------------------------
Vec3 Vec3::operator * (float f) const {
  return Vec3( x * f, y * f, z * f );

}

// ----------------------------------------------
Vec3 Vec3::operator / (float f) const {
  return Vec3( x / f, y / f, z / f );

}

// ----------------------------------------------
bool Vec3::operator == (const Vec3 &v) const {
  return( (x == v.x) &&
          (y == v.y) &&
          (z == v.z) );

}
 
// ----------------------------------------------
bool Vec3::operator != (const Vec3 &v) const {
  return( (x != v.x) ||
          (y != v.y) ||
          (z != v.z) );

}
   
// ----------------------------------------------
float Vec3::mag(void) const {
  return sqrt( x*x + y*y + z*z );

}

// ----------------------------------------------
void Vec3::normalize(void) {
  float len = this->mag();

  x /= len;
  y /= len;
  z /= len;

}

// ----------------------------------------------
float Vec3::operator [] (unsigned int i) const {
  assert(i >= 0);
  assert(i <= 2);
  
  if(i == 0)
    return x;
  else if(i == 1)
    return y;
  else
    return z;

}