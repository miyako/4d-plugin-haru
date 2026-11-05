#include "4DPluginAPI.h"
#include "4DPlugin.h"

#include "functions_hpdf.h"

// --- Font
void PDF_Font_GetFontName(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_GetEncodingName(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_GetUnicodeWidth(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_GetBBox(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_GetAscent(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_GetDescent(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_GetXHeight(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_GetCapHeight(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_TextWidth(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Font_MeasureText(sLONG_PTR *pResult, PackagePtr pParams);
