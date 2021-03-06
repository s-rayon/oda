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

#include "OdaCommon.h"
#include "OdFileBuf.h"
#include "RxDynamicModule.h"
#include "DynamicLinker.h"
#include "ExSystemServices.h"
#include "ExHostAppServices.h"
#include "DbDatabase.h"
#include "DbDictionary.h"
#include "DbBlockTableRecord.h"
#include "DbEntity.h"
#include "DbLine.h"
#include "DbDimAssoc.h"
#include "DbRotatedDimension.h"
#include "ExEvalWatcherModule.h"
#include "diagnostics.h"

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

void traceFn(const OdChar* debugString)
{
  printf("%ls\n", debugString);
}

class MyServices : public ExSystemServices, public ExHostAppServices
{
protected:
  ODRX_USING_HEAP_OPERATORS(ExSystemServices);
};


#ifndef _TOOLKIT_IN_DLL_

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdExEvalWatcherModule);

ODRX_BEGIN_STATIC_MODULE_MAP()
  ODRX_DEFINE_STATIC_APPLICATION(OdExEvalWatcherModuleName,  OdExEvalWatcherModule)
ODRX_END_STATIC_MODULE_MAP()

#endif


#if (defined(WIN32) || defined(WIN64))
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#ifdef OD_HAVE_CCOMMAND_FUNC
  argc = ccommand(&argv);
#endif

  OdStaticRxObject<MyServices> svcs;
#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif
  odInitialize(&svcs);

  // Set the trace function that will receive notification messages generated by 
  // example function OdExDimAssocWatcherPE::modified().
  odSetTraceFunc(&traceFn);

  //Load the EvalWatcher module, which registers watcher classes for OdDbHatch and 
  //OdDbDimAssoc.
  OdRxModulePtr m = ::odrxDynamicLinker()->loadModule(OdExEvalWatcherModuleName);

  // Create a database to work with.
  OdDbDatabasePtr pDb = svcs.createDatabase();
  printf("Created OdDbDatabase\n");

  if (!m.isNull())
  {

    // Add a line dimension to Modelspace.
    OdDbBlockTableRecordPtr pBlock = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

    OdGePoint3d point(0.0, 0.0, 0.0);
    double h = 2.0;
    double w = 3.0;
    point.y -= h;

    OdGePoint3d line1Pt, line2Pt;
    line1Pt.x  = point.x + w * 5.0 / 6.0;
    line1Pt.y  = point.y + h * 7.0 / 8.0;
    line2Pt.x  = point.x + w/8.0;
    line2Pt.y  = point.y + h/3.0;

    printf("Adding OdDbLine to database\n");
    OdDbLinePtr pLine;
    pLine = OdDbLine::createObject();
    OdDbObjectId lineId;
    lineId = pBlock->appendOdDbEntity(pLine);
    pLine->setStartPoint(line1Pt);
    pLine->setEndPoint(line2Pt);

    printf("Adding OdDbRotatedDimension to database\n");
    OdDbRotatedDimensionPtr pAD = OdDbRotatedDimension::createObject();
    OdDbObjectId dimId = pBlock->appendOdDbEntity(pAD);
    OdGePoint3d dimLinePt;
    dimLinePt.x = point.x + w/16.0;
    dimLinePt.y = point.y + 8.0*h/21.0;

    pAD->setDatabaseDefaults(pDb);
    pAD->setXLine1Point(pLine->startPoint());
    pAD->setXLine2Point(pLine->endPoint());
    pAD->setDimLinePoint(dimLinePt);
    pAD->useDefaultTextPosition();
    pAD->createExtensionDictionary();

    // Add an OdDbDimAssoc object.
    printf("Adding OdDbDimAssoc for rotated dimension\n");
    OdDbDictionaryPtr dict = pAD->extensionDictionary().safeOpenObject(OdDb::kForWrite);
    OdDbDimAssocPtr dimAssoc = OdDbDimAssoc::createObject();
    dimAssoc->setDimObjId(dimId);
    dimAssoc->setRotatedDimType(OdDbDimAssoc::kParallel);

    OdDbObjectId dimAssId = dict->setAt("ACAD_DIMASSOC", dimAssoc);

    OdDbOsnapPointRefPtr pointRef = OdDbOsnapPointRef::createObject();

    pointRef->setPoint(pLine->startPoint());
    pointRef->setOsnapType(OdDb::kOsModeStart);
    pointRef->setNearPointParam(0.0);

    pointRef->mainEntity().objectIds().append(lineId);
    pointRef->mainEntity().subentId().setType(OdDb::kEdgeSubentType);

    dimAssoc->setPointRef(OdDbDimAssoc::kXline1Point, pointRef);

    pointRef = OdDbOsnapPointRef::createObject();
    pointRef->setPoint(pLine->endPoint());
    pointRef->setOsnapType(OdDb::kOsModeEnd);
    pointRef->setNearPointParam(1.0);

    pointRef->mainEntity().objectIds().append(lineId);
    pointRef->mainEntity().subentId().setType(OdDb::kVertexSubentType);

    dimAssoc->setPointRef(OdDbDimAssoc::kXline2Point, pointRef);

    printf("Setting DIMASSOC as a reactor for the new line and dimension entities\n");
    // Make the DIMASSOC a reactor of the newly created line and dimension
    // entities, so that these entities will generate notifications for the 
    // DIMASSOC when they are modified.
    pAD->addPersistentReactor(dimAssId);
    pLine->addPersistentReactor(dimAssId);

    printf("Releasing rotated dimension\n");
    // Associated DimAssoc object will get notified during the following release
    // call, since the dimension has been modified.
    pAD.release();

    printf("Releasing line\n");
    // Associated DimAssoc object will get notified during the following release
    // call, since the line has been modified.
    pLine.release();

    // Release the eval watcher module.
    m.release();
  }

  pDb.release();
  odUninitialize();

  STD(cout) << "Press RETURN to exit..." << STD(endl);
  STD(cin).get();

	return 0;
}

