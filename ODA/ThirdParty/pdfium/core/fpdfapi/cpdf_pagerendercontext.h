// Copyright 2016 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FPDFAPI_CPDF_PAGERENDERCONTEXT_H_
#define CORE_FPDFAPI_CPDF_PAGERENDERCONTEXT_H_

#include <memory>
#include "public/fpdfview.h"

class CFX_RenderDevice;
class CPDF_AnnotList;
class CPDF_ProgressiveRenderer;
class CPDF_RenderContext;
class CPDF_RenderOptions;

// Everything about rendering is put here: for OOM recovery
class CPDF_PageRenderContext {
 public:
  CPDF_PageRenderContext();
  ~CPDF_PageRenderContext();

  // Specific destruction order required.
  std::unique_ptr<CPDF_AnnotList> m_pAnnots;
  std::unique_ptr<CPDF_RenderOptions> m_pOptions;
  std::unique_ptr<CFX_RenderDevice> m_pDevice;
  std::unique_ptr<CPDF_RenderContext> m_pContext;
  std::unique_ptr<CPDF_ProgressiveRenderer> m_pRenderer;
};

#endif  // CORE_FPDFAPI_CPDF_PAGERENDERCONTEXT_H_
