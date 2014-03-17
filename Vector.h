//
//  Vector.h
//  Tech1
//
//  Created by Justin Hust on 12/29/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Vector_h
#define Tech1_Vector_h

class Vec3 {
public:
  // DATA
    float x;
    float y;
    float z;

  // CREATORS
    Vec3(void);
    Vec3(float x_, float y_, float z_);
    Vec3(float v[]);
    Vec3(const Vec3 &v);

  // MANIPULATORS
    Vec3 & operator = (const Vec3 &v);
    void operator += (const Vec3 &v);
    void operator -= (const Vec3 &v);
    void operator *= (float f);
    void operator /= (float f);
    
    Vec3 operator + (const Vec3 &v) const;
    Vec3 operator - (const Vec3 &v) const;
    Vec3 operator * (float f) const;
    Vec3 operator / (float f) const;
    
    void normalize(void);
  
  // ACCESSORS
    float mag(void) const;
    bool operator == (const Vec3 &v) const;
    bool operator != (const Vec3 &v) const;
    float operator [] (unsigned int i) const;
    
};

#endif
