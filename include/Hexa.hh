/*=========================================================================

  Program:   Visualization Toolkit
  Module:    Hexa.hh
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

This file is part of the Visualization Toolkit. No part of this file
or its contents may be copied, reproduced or altered in any way
without the express written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994 

=========================================================================*/
// .NAME vtkHexahedron - a cell that represents a 3D parallelpiped
// .SECTION Description
// vtkHexahedron is a concrete implementation of vtkCell to represent a 3D
// parallelpiped (a "cube" topology).

#ifndef __vtkHexahedron_h
#define __vtkHexahedron_h

#include "Cell.hh"

class vtkHexahedron : public vtkCell
{
public:
  vtkHexahedron() {};
  vtkHexahedron(const vtkHexahedron& h);
  char *GetClassName() {return "vtkHexahedron";};

  vtkCell *MakeObject() {return new vtkHexahedron(*this);};
  int GetCellType() {return vtkHEXAHEDRON;};
  int GetCellDimension() {return 3;};
  int GetNumberOfEdges() {return 12;};
  int GetNumberOfFaces() {return 6;};
  vtkCell *GetEdge(int edgeId);
  vtkCell *GetFace(int faceId);

  int CellBoundary(int subId, float pcoords[3], vtkIdList& pts);
  void Contour(float value, vtkFloatScalars *cellScalars, 
               vtkFloatPoints *points, vtkCellArray *verts, 
               vtkCellArray *lines, vtkCellArray *polys, vtkFloatScalars *s);
  int EvaluatePosition(float x[3], float closestPoint[3],
                       int& subId, float pcoords[3],
                       float& dist2, float weights[MAX_CELL_SIZE]);
  void EvaluateLocation(int& subId, float pcoords[3], float x[3],
                        float weights[MAX_CELL_SIZE]);
  int IntersectWithLine(float p1[3], float p2[3], float tol, float& t,
                        float x[3], float pcoords[3], int& subId);

  void InterpolationFunctions(float pcoords[3], float weights[8]);
  void InterpolationDerivs(float pcoords[3], float derivs[24]);

};

#endif


