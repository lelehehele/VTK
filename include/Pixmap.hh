/*=========================================================================

  Program:   Visualization Toolkit
  Module:    Pixmap.hh
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

This file is part of the Visualization Toolkit. No part of this file
or its contents may be copied, reproduced or altered in any way
without the express written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994 

=========================================================================*/
// .NAME vtkPixmap - scalar data in RGB (color) form
// .SECTION Description
// vtkPixmap is a concrete implementation of vtkScalars. Scalars are
// represented using three values for color (red, green, blue). Each of
// r,g,b ranges from (0,255) (i.e., an unsigned char value).

#ifndef __vtkPixmap_h
#define __vtkPixmap_h

#include "CoScalar.hh"
#include "CArray.hh"

class vtkPixmap : public vtkColorScalars 
{
public:
  vtkPixmap() {};
  ~vtkPixmap() {};
  vtkPixmap(const vtkPixmap& fs) {this->S = fs.S;};
  vtkPixmap(const int sz, const int ext=1000):S(3*sz,3*ext){};
  int Allocate(const int sz, const int ext=1000) {return this->S.Allocate(3*sz,3*ext);};
  void Initialize() {this->S.Initialize();};
  char *GetClassName() {return "vtkPixmap";};

  // vtkScalar interface
  vtkScalars *MakeObject(int sze, int ext=1000);
  int GetNumberOfScalars() {return (this->S.GetMaxId()+1)/3;};
  void Squeeze() {this->S.Squeeze();};
  int GetNumberOfValuesPerScalar() {return 3;};

  // miscellaneous
  vtkPixmap &operator=(const vtkPixmap& fs);
  void operator+=(const vtkPixmap& fs) {this->S += fs.S;};
  void Reset() {this->S.Reset();};
  unsigned char *GetPtr(const int id);
  unsigned char *WritePtr(const int id, const int number);
  void WrotePtr();

  // vtkColorScalar interface.
  unsigned char *GetColor(int id);
  void GetColor(int id, unsigned char rgba[4]);
  void SetColor(int id, unsigned char rgba[4]);
  void InsertColor(int id, unsigned char rgba[4]);
  int InsertNextColor(unsigned char rgba[4]);

protected:
  vtkCharArray S;
};

// Description:
// Set a rgba color value at a particular array location. Does not do range 
// checking.
inline void vtkPixmap::SetColor(int i, unsigned char rgba[4]) 
{
  i *= 3; 
  this->S[i] = rgba[0]; 
  this->S[i+1] = rgba[1]; 
  this->S[i+2] = rgba[2];
}

// Description:
// Insert a rgba color value at a particular array location. Does range 
// checking and will allocate additional memory if necessary.
inline void vtkPixmap::InsertColor(int i, unsigned char rgba[4]) 
{
  this->S.InsertValue(3*i+2, rgba[2]);
  this->S[3*i] = rgba[0];
  this->S[3*i+1] = rgba[1];
}

// Description:
// Insert a rgba value at the next available slot in the array. Will allocate
// memory if necessary.
inline int vtkPixmap::InsertNextColor(unsigned char *rgba) 
{
  int id = this->S.GetMaxId() + 3;
  this->S.InsertValue(id,rgba[2]);
  this->S[id-2] = rgba[0];
  this->S[id-1] = rgba[1];
  return id/3;
}

// Description:
// Get pointer to array of data starting at data position "id".
inline unsigned char *vtkPixmap::GetPtr(const int id)
{
  return this->S.GetPtr(3*id);
}

// Description:
// Get pointer to data array. Useful for direct writes of data. MaxId is 
// bumped by number (and memory allocated if necessary). Id is the 
// location you wish to write into; number is the number of scalars to 
// write. Use the method WrotePtr() to mark completion of write.
inline unsigned char *vtkPixmap::WritePtr(const int id, const int number)
{
  return this->S.WritePtr(3*id,3*number);
}

// Description:
// Terminate direct write of data. Although dummy routine now, reserved for
// future use.
inline void vtkPixmap::WrotePtr() {}

#endif
