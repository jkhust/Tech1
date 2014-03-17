//
//  Variant.c++
//  Tech1
//
//  Created by Justin Hust on 12/15/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "Variant.h"
#include <cassert>

Variant::Variant(void) {
  _dt = Data_None;

}

// ---------------------------------------------------
Variant::Variant(bool b) {
  _dt = Data_Boolean;
  _bVal = b;

}

// ---------------------------------------------------
Variant::Variant(int i) {
  _dt = Data_Integer;
  _iVal = i;

}

// ---------------------------------------------------
Variant::Variant(float f) {
  _dt = Data_Float;
  _fVal = f;
  
}

// ---------------------------------------------------
Variant::Variant(const char *s) {
  _dt = Data_String;
  _sVal = std::string(s);

}
    
// ---------------------------------------------------
Variant::Variant(const std::string &s) {
  _dt = Data_String;
  _sVal = s;

}

// ---------------------------------------------------
Variant::Variant(const Vec3 &v) {
  _dt = Data_Vec3;
  _vecVal = v;

}

// ---------------------------------------------------
Variant::Variant(const Variant &v) {
  _dt = v._dt;
  
  _bVal = v._bVal;
  _iVal = v._iVal;
  _fVal = v._fVal;
  _sVal = v._sVal;

}

// ---------------------------------------------------
void Variant::clear(void) {
  _dt = Data_None;

}

// ---------------------------------------------------
Variant & Variant::operator = (const Variant &v) {
  _dt = v._dt;
  
  _bVal = v._bVal;
  _iVal = v._iVal;
  _fVal = v._fVal;
  _sVal = v._sVal;

  return *this;

}

// ---------------------------------------------------
Variant & Variant::operator = (bool b) {
  _dt = Data_Boolean;
  _bVal = b;

  return *this;

}

// ---------------------------------------------------
Variant & Variant::operator = (int i) {
  _dt = Data_Integer;
  _iVal = i;
  
  return *this;

}

// ---------------------------------------------------
Variant & Variant::operator = (float f) {
  _dt = Data_Float;
  _fVal = f;
  
  return *this;

}

// ---------------------------------------------------
Variant & Variant::operator = (const char *s) {
  _dt = Data_String;
  _sVal = std::string(s);

  return *this;
  
}

// ---------------------------------------------------
Variant & Variant::operator = (const std::string &s) {
  _dt = Data_String;
  _sVal = s;

  return *this;
  
}

// ---------------------------------------------------
Variant & Variant::operator = (const Vec3 &v) {
  _dt = Data_Vec3;
  _vecVal = v;
  
  return *this;

}

// ---------------------------------------------------
bool Variant::operator != (const Variant &v) {
  if( this->operator ==(v) )
    return false;
  else
    return true;

}

// ---------------------------------------------------
bool Variant::operator == (const Variant &v) {
  if(_dt == Data_None && v._dt == Data_None) {
    return true;

  } else if(_dt == Data_Boolean && v._dt == Data_Boolean) {
    return( _bVal == v._bVal);

  } else if(_dt == Data_Integer && v._dt == Data_Integer) {
    return( _iVal == v._iVal);

  } else if(_dt == Data_Float && v._dt == Data_Float) {
    return( _fVal == v._fVal);

  } else if(_dt == Data_String && v._dt == Data_String) {
    return( _sVal == v._sVal);

  } else if(_dt == Data_Vec3 && v._dt == Data_Vec3) {
    return( _vecVal == v._vecVal );
  
  }
  
  return false;

}

// ---------------------------------------------------
void Variant::operator ++ (void) {
  assert(this->isInteger());

  _iVal = _iVal + 1;
  
}

// ---------------------------------------------------
void Variant::operator -- (void) {
  assert(this->isInteger());
  
  _iVal = _iVal - 1;
  
}

// ---------------------------------------------------
void Variant::operator += (const Variant &v) {
  assert(this->isNumeric());
  assert(v.isNumeric());

  if(this->isInteger() && v.isInteger()) {
    this->_iVal += v._iVal;
  
  } else if(this->isInteger() && v.isFloat()) { 
    this->_fVal = (float) (this->_iVal + v._fVal);
    this->_dt = Data_Float;
    
  } else if(this->isFloat() && v.isInteger()) {
    this->_fVal += (float) v._iVal;
  
  } else if(this->isFloat() && v.isFloat()) {
    this->_fVal += v._fVal;
  
  }

}

// ---------------------------------------------------
void Variant::operator -= (const Variant &v) {
  assert(this->isNumeric());
  assert(v.isNumeric());

  if(this->isInteger() && v.isInteger()) {
    this->_iVal -= v._iVal;
  
  } else if(this->isInteger() && v.isFloat()) { 
    this->_fVal = (float) (this->_iVal - v._fVal);
    this->_dt = Data_Float;
    
  } else if(this->isFloat() && v.isInteger()) {
    this->_fVal -= (float) v._iVal;
  
  } else if(this->isFloat() && v.isFloat()) {
    this->_fVal -= v._fVal;
  
  }

}

// ---------------------------------------------------
void Variant::operator *= (const Variant &v) {
  assert(this->isNumeric());
  assert(v.isNumeric());

  if(this->isInteger() && v.isInteger()) {
    this->_iVal *= v._iVal;
  
  } else if(this->isInteger() && v.isFloat()) { 
    this->_fVal = (float) (this->_iVal * v._fVal);
    this->_dt = Data_Float;
    
  } else if(this->isFloat() && v.isInteger()) {
    this->_fVal *= (float) v._iVal;
  
  } else if(this->isFloat() && v.isFloat()) {
    this->_fVal *= v._fVal;
  
  }

}

// ---------------------------------------------------
void Variant::operator /= (const Variant &v) {
  assert(this->isNumeric());
  assert(v.isNumeric());

  if(this->isInteger() && v.isInteger()) {
    this->_iVal /= v._iVal;
  
  } else if(this->isInteger() && v.isFloat()) { 
    this->_fVal = (float) (this->_iVal / v._fVal);
    this->_dt = Data_Float;
    
  } else if(this->isFloat() && v.isInteger()) {
    this->_fVal /= (float) v._iVal;
  
  } else if(this->isFloat() && v.isFloat()) {
    this->_fVal /= v._fVal;
  
  }

}

// ---------------------------------------------------
bool Variant::isBoolean(void) const  {
  return (_dt == Data_Boolean);
  
}

// ---------------------------------------------------
bool Variant::isInteger(void) const {
  return (_dt == Data_Integer);
  
}

// ---------------------------------------------------
bool Variant::isFloat(void) const  {
  return (_dt == Data_Float);
  
}

// ---------------------------------------------------
bool Variant::isNumeric(void) const {
  return( _dt == Data_Integer || _dt == Data_Float );

}

// ---------------------------------------------------
bool Variant::isString(void) const  {
  return (_dt == Data_String);
  
}

// ---------------------------------------------------
bool Variant::isVec3(void) const  {
  return (_dt == Data_Vec3);
  
}

// ---------------------------------------------------
DataType Variant::getType(void) const {
  return _dt;

}

// ---------------------------------------------------
bool Variant::getBoolean(void) const  {
  assert(_dt == Data_Boolean);
  
  return _bVal;
  
}

// ---------------------------------------------------
int Variant::getInteger(void) const  {
  assert(_dt == Data_Integer);
    
  return _iVal;
  
}

// ---------------------------------------------------
float Variant::getFloat(void) const  {
  assert(_dt == Data_Float);
    
  return _fVal;
  
}

// ---------------------------------------------------
std::string Variant::getString(void) const  {
  assert(_dt == Data_String);
  
  return _sVal;

}

// ---------------------------------------------------
Vec3 Variant::getVec3(void) const {
  assert(_dt == Data_Vec3);
  
  return _vecVal;

}

// ---------------------------------------------------
float Variant::toFloat(void) const {
  assert(_dt == Data_Integer || _dt == Data_Float);

  if(_dt == Data_Integer) {
    return static_cast<float> (_iVal);
  
  } else {
    return _fVal;
  
  }  
  
}

// ---------------------------------------------------
float Variant::x(void) const {
  assert(_dt == Data_Vec3);

  return _vecVal.x;

}

// ---------------------------------------------------
float Variant::y(void) const {
  assert(_dt == Data_Vec3);

  return _vecVal.y;

}

// ---------------------------------------------------
float Variant::z(void) const {
  assert(_dt == Data_Vec3);

  return _vecVal.z;

}

// ---------------------------------------------------
float Variant::mag(void) const {
  assert(_dt == Data_Vec3);
  
  return _vecVal.mag();

}

// ---------------------------------------------------
void Variant::normalize(void) {
  assert(_dt == Data_Vec3);
  
  _vecVal.normalize();


}