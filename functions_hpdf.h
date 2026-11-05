#include "4DPluginAPI.h"
#include "4DPlugin.h"

#ifndef __FUNCTIONS_HPDF_H__
#define __FUNCTIONS_HPDF_H__ 1

#if VERSIONMAC
#include "hpdf_mac.h"
#else
#include "hpdf.h"
#endif

#include "hpdf_document.h"
#include "hpdf_font.h"
#include "hpdf_image.h"
#include "hpdf_page.h"
#include "hpdf_destination.h"
#include "hpdf_annotation.h"
#include "hpdf_outline.h"
#include "hpdf_extgstate.h"

HPDF_Doc _documentGet(C_TEXT &hex);
void _documentCreate(C_TEXT &hex);
void _documentDelete(C_TEXT &hex);
void *_fromHex(C_TEXT &hex);
void _toHex(void *n, C_TEXT &hex);
void _convertFromUnicode(C_TEXT &fromStr, std::string &toStr);

// --- Global
void PDF_Global_GetEncoding(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Global_SetEncoding(sLONG_PTR *pResult, PackagePtr pParams);

#endif