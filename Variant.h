//
//  Variant.h
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef Tech1_Variant_h
#define Tech1_Variant_h

#include <iostream>
#include "Vector.h"

enum DataType {
  Data_None = 0,
  Data_Boolean,
  Data_Integer,
  Data_Float,
  Data_String,
  Data_Vec3

};

// ---------------------------------------------------
class Variant {
private:
  // DATA
    DataType _dt;
    
    bool _bVal;
    int _iVal;
    float _fVal;
    std::string _sVal;
    Vec3 _vecVal;
    
public:
  // CREATORS
    Variant(void);
    Variant(bool b);
    Variant(int i);
    Variant(float f);
    Variant(const char *s);
    Variant(const std::string &s);
    Variant(const Vec3 &v);
    
    Variant(const Variant &v);

  // MANIPULATORS
    void clear(void);
  
    Variant & operator = (const Variant &v);
    Variant & operator = (bool b);
    Variant & operator = (int i);
    Variant & operator = (float f);
    Variant & operator = (const char *s);
    Variant & operator = (const std::string &s);
    Variant & operator = (const Vec3 &v);
    
    void operator ++ (void);
    void operator -- (void);
        
    void operator += (const Variant &v);
    void operator -= (const Variant &v);
    void operator *= (const Variant &v);
    void operator /= (const Variant &v);
    
  // ACCESSORS
    bool operator == (const Variant &v);
    bool operator != (const Variant &v);
  
    bool isBoolean(void) const;
    bool isNumeric(void) const;
      bool isInteger(void) const;
      bool isFloat(void) const;
    bool isString(void) const;
    bool isVec3(void) const;
    DataType getType(void) const;

    float toFloat(void) const;

    bool getBoolean(void) const;
    int getInteger(void) const;
    float getFloat(void) const;
    std::string getString(void) const;
    Vec3 getVec3(void) const;
    
    float x(void) const;
    float y(void) const;
    float z(void) const;
    
  // DELEGATION
    // TO VEC3
    float mag(void) const;
    void normalize(void);
    
};

#endif
