/*=========================================================================

  Program:   Visualization Toolkit
  Module:    Graymap.cc
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

This file is part of the Visualization Toolkit. No part of this file
or its contents may be copied, reproduced or altered in any way
without the express written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994 

=========================================================================*/
#include "Graymap.hh"

vtkScalars *vtkGraymap::MakeObject(int sze, int ext)
{
  return new vtkGraymap(sze,ext);
}

// Description:
// Deep copy of scalars.
vtkGraymap& vtkGraymap::operator=(const vtkGraymap& fs)
{
  this->S = fs.S;
  return *this;
}

// Description:
// Return a rgba color for a particular point id.
// (Note: gray value converted into full rgba. )
unsigned char *vtkGraymap::GetColor(int id)
{
  static unsigned char rgba[4];
  rgba[0] = rgba[1] = rgba[2] = this->S[id];
  rgba[3] = 255;
  return rgba;
}

// Description:
// Copy gray components into user provided array for specified
// point id. (Note: gray value converted into full rgba color value.)
void vtkGraymap::GetColor(int id, unsigned char rgba[4])
{
  rgba[0] = rgba[1] = rgba[2] = this->S[id];
  rgba[3] = 255;
}

// Description:
// Insert gray value into object. No range checking performed (fast!).
// (Note: rgba color value converted to grayscale).
void vtkGraymap::SetColor(int id, unsigned char rgba[4])
{
  this->S[id] = (rgba[0] > rgba[1] ? (rgba[0] > rgba[2] ? rgba[0] : rgba[2]) :
                                     (rgba[1] > rgba[2] ? rgba[1] : rgba[2]));
}

// Description:
// Insert rgba color value into object. Range checking performed and memory
// allocated as necessary. (Note: rgba converted to gray value).
void vtkGraymap::InsertColor(int id, unsigned char rgba[4])
{
  unsigned char g=(rgba[0] > rgba[1] ? (rgba[0] > rgba[2] ? rgba[0] : rgba[2]) :
                                       (rgba[1] > rgba[2] ? rgba[1] : rgba[2]));
  this->S.InsertValue(id,g);
}

// Description:
// Insert rgba color value into next available slot. Returns point id of slot.
// (Note: rgba converted to gray value).
int vtkGraymap::InsertNextColor(unsigned char rgba[4])
{
  unsigned char g=(rgba[0] > rgba[1] ? (rgba[0] > rgba[2] ? rgba[0] : rgba[2]) :
                                       (rgba[1] > rgba[2] ? rgba[1] : rgba[2]));
  int id = this->S.InsertNextValue(g);
  return id;
}

