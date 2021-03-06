/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef OdConstrainedEllipseImpl_INCLUDED
#define OdConstrainedEllipseImpl_INCLUDED

#include "OdConstrainedCurveImpl.h"
#include "Ge/GeEllipArc3d.h"

#include "TD_PackPush.h"

/** \details
  This class represents custom implementation of the constrained ellipse node in the owning constraint group. 

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdConstrainedEllipseImpl: public OdConstrainedCurveImpl 
{ 
public:
  /** \details
    Constructor creates an instance of this class.
  */
  OdConstrainedEllipseImpl();

  /** \details
    Initializes this constrained ellipse object.
  */
  virtual OdResult init(const OdDbObjectId depId);

  /** \details
    Checks whether the constrained ellipse is bounded and returns True when the it is bounded, 
    or False otherwise.
  */
  virtual bool isBounded() const;

  /** \details
    Returns the direction vector of this constrained ellipse.
  */
  OdGeVector3d direction() const; 

  /** \details
    Returns the major radius of this constrained ellipse.
  */
  double majorRadius() const; 

  /** \details
    Returns the minor radius of this constrained ellipse.
  */
  double minorRadius() const;

  /** \details
    Returns the center point of this constrained ellipse.
  */
  OdGePoint3d centerPoint() const;

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  /** \details
    Sets the direction vector for this constrained ellipse.
  */
  OdResult setDirection(const OdGeVector3d& val); 

  /** \details
    Sets the major radius for this constrained ellipse.
  */
  OdResult setMajorRadius(const double val); 

  /** \details
    Sets the minor radius for this constrained ellipse.
  */
  OdResult setMinorRadius(const double val);

  /** \details
    Sets the center point for this constrained ellipse.
  */
  OdResult setCenterPoint(const OdGePoint3d& val);

  /** \details
    Compares two constrained ellipses on equality.
  */
  virtual bool operator==(const OdConstrainedGeometryImpl& geom) const;

  /** \details
    Compares two constrained ellipses on unequality.
  */
  virtual bool operator!=(const OdConstrainedGeometryImpl& geom) const;

  /** \details
    Sets data from a given geometry dependency using transformation matrix.
  */
  virtual OdResult setDataFromGeomDependency(const OdDbObjectId geomDependencyId,
                                             const OdGeMatrix3d& matrFromWrd);

  /** \details
    Updates the database object.
  */
  virtual OdResult updateDbObject(OdDbObject *pObj, OdDbAssocGeomDependency* pDep, const OdGeMatrix3d& matrToWrd);

  /** \details
    Gets the three-dimesional point for the specified implicit point through argument.
  */
  virtual OdResult point(const OdConstrainedImplicitPointImpl* pImplicitPoint, OdGePoint3d& res) const;

  /** \details
    Sets the specified implicit point using a three-dimesional point passed through argument.
  */
  virtual OdResult setPoint(const OdConstrainedImplicitPointImpl* pImplicitPoint, const OdGePoint3d& val);

  /** \details
    Gets the three-dimesional original point for the specified implicit point through argument.
  */
  virtual OdResult getOriginalPoint(const OdConstrainedImplicitPointImpl* pImplicitPoint, OdGePoint3d& res) const;

  /** \details
    Gets the three-dimensional elliptical arc as Ge-object.
  */
  virtual const OdGeEllipArc3d getOdGeEllipArc3d() const;

  /** \details
    Gets the original three-dimensional elliptical arc as Ge-object.
  */
  virtual const OdGeEllipArc3d getOriginalOdGeEllipArc3d() const;

  /** \details
    Sets the center point, direction vector, major radius and minor radius for this constrained ellipse.
  */
  OdResult set(const OdGePoint3d centerPt, const OdGeVector3d dir, const double majorRad, const double minorRad);
protected:
  /*!DOM*/
  OdGeEllipArc3d m_geArc;
  /*!DOM*/
  OdGeEllipArc3d m_originGeArc;
};

#include "TD_PackPop.h"
#endif
