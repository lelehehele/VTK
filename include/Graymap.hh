/*=========================================================================

  Program:   Visualization Toolkit
  Module:    Graymap.hh
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

This file is part of the Visualization Toolkit. No part of this file
or its contents may be copied, reproduced or altered in any way
without the express written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994 

=========================================================================*/
// .NAME vtkGraymap - scalar data in grayscale form
// .SECTION Description
// vtkGraymap is a concrete implementation of vtkScalars. Scalars are
// represented using a single unsigned char for components of gray. 
// Gray values range from (0,255) with 0 being black.

#ifndef __vtkGraymap_h
#define __vtkGraymap_h

#include "CoScalar.hh"
#include "CArray.hh"

class vtkGraymap : public vtkColorScalars 
{
public:
  vtkGraymap() {};
  ~vtkGraymap() {};
  vtkGraymap(const vtkGraymap& fs) {this->S = fs.S;};
  vtkGraymap(const int sz, const int ext=1000):S(sz,ext){};
  int Allocate(const int sz, const int ext=1000) {return this->S.Allocate(sz,ext);};
  void Initialize() {this->S.Initialize();};
  char *GetClassName() {return "vtkGraymap";};

  // vtkScalar interface
  vtkScalars *MakeObject(int sze, int ext=1000);
  int GetNumberOfScalars() {return (this->S.GetMaxId()+1);};
  void Squeeze() {this->S.Squeeze();};

  // miscellaneous
  vtkGraymap &operator=(const vtkGraymap& fs);
  void operator+=(const vtkGraymap& fs) {this->S += fs.S;};
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
// Get pointer to array of data starting at data position "id".
inline unsigned char *vtkGraymap::GetPtr(const int id)
{
  return this->S.GetPtr(id);
}

// Description:
// Get pointer to data array. Useful for direct writes of data. MaxId is 
// bumped by number (and memory allocated if necessary). Id is the 
// location you wish to write into; number is the number of scalars to 
// write. Use the method WrotePtr() to mark completion of write.
inline unsigned char *vtkGraymap::WritePtr(const int id, const int number)
{
  return this->S.WritePtr(id,number);
}

// Description:
// Terminate direct write of data. Although dummy routine now, reserved for
// future use.
inline void vtkGraymap::WrotePtr() {}

#endif
