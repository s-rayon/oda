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

/************************************************************************/
/* IbModule.cpp: Defines the entry points for the DLL                   */
/************************************************************************/
#include "OdaCommon.h"
#include "RxSysRegistry.h"

#include "RxDynamicModule.h"

#include "DbEmbeddedRasterImage.h"
#include "DbEmbeddedRasterImageDef.h"
#include "DbEmbeddedImageData.h"


class TD_IbModule : public OdRxModule
{
public:
  void initApp()
  {
    AECIDbEmbeddedRasterImage::rxInit();
    AECIDbEmbeddedRasterImageDef::rxInit();
    AECIDbEmbeddedImageData::rxInit();
  };

  void uninitApp()
  {
    AECIDbEmbeddedRasterImage::rxUninit();
    AECIDbEmbeddedRasterImageDef::rxUninit();
    AECIDbEmbeddedImageData::rxUninit();
  };
};

ODRX_DEFINE_DYNAMIC_MODULE(TD_IbModule);
