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


///////////////////////////////////////////////////////////////////////////////
//
// PdfUnderlay.h - Open Design auxiliary export methods for support of snap points in Pdf Underlays.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_UNDERLAYITEMPE_INCLUDED_
#define _PDF_UNDERLAYITEMPE_INCLUDED_

#include "TD_PackPush.h"

/** \details
  Library:  Source code provided.
  <group PdfServices_Classes>
*/
class OD_DLL_EXPORT OdDbPdfUnderlayItemPE : public OdRxObject
{
public:
  ODRX_DECLARE_MEMBERS(OdDbPdfUnderlayItemPE);
};

typedef OdSmartPtr<OdDbPdfUnderlayItemPE> OdDbPdfUnderlayItemPEPtr;

#include "TD_PackPop.h"

#endif // _PDF_UNDERLAYITEMPE_INCLUDED_

