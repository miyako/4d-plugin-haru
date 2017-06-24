#include "4DPluginAPI.h"
#include "4DPlugin.h"

#include "functions_hpdf.h"

// --- Document
void PDF_GetPageByIndex(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_CreateExtGState(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadRawImageFromFile(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadPngImageFromFile2(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadPngImageFromFile(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_CreateOutline(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_InsertPage(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_AddPage(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetCurrentPage(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetOpenAction(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetPageMode(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetPageMode(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetPageLayout(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetPageLayout(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetPagesConfiguration(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SaveToFile(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_HasDoc(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_FreeDocAll(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_FreeDoc(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_NewDoc(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Free(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_New(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadRawImageFromMem(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadPngImageFromMem(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadJpegImageFromMem(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadJpegImageFromFile(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetInfoAttr(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetInfoAttr(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetInfoDateAttr(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetPassword(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetPermission(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetEncryptionMode(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetCompressionMode(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetViewerPreference(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetViewerPreference(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SaveToStream(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetFont(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_UseCNTFonts(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_UseCNSFonts(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_UseKRFonts(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_UseJPFonts(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_AddPageLabel(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadTTFontFromFile(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetTTFontDefFromFile(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadType1FontFromFile(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_ResetError(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadU3DFromFile(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LoadRaw1BitImageFromMem(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_UseCNTEncodings(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_SetCurrentEncoder(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_UseCNSEncodings(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_UseKREncodings(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetEncoder(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_GetCurrentEncoder(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_UseJPEncodings(sLONG_PTR *pResult, PackagePtr pParams);

