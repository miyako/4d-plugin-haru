#include "4DPluginAPI.h"
#include "4DPlugin.h"

#include "functions_hpdf.h"

// --- Image
void PDF_Image_GetSize(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Image_GetWidth(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Image_GetHeight(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Image_GetBitsPerComponent(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Image_GetColorSpace(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Image_SetColorMask(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Image_SetMaskImage(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Image_AddSMask(sLONG_PTR *pResult, PackagePtr pParams);
