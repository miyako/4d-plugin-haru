#include "4DPluginAPI.h"
#include "4DPlugin.h"

#include "functions_hpdf.h"

// --- Annotation
void PDF_MarkupAnnot_SetPopup(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetIntent(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetAlpha(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetDate(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetSubject(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetTitle(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Annot_SetNoColor(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Annot_SetGrayColor(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Annot_SetCMYKColor(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Annot_SetRGBColor(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_Annotation_SetBorderStyle(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_TextAnnot_SetOpened(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_TextAnnot_SetIcon(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LinkAnnot_SetBorderStyle(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LinkAnnot_SetHighlightMode(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetRectDiff(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetCloudEffect(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetRGBColor(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetCMYKColor(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetGrayColor(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetNoColor(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LineAnnot_SetLeader(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LineAnnot_SetCaption(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_LineAnnot_SetPosition(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_PopupAnnot_SetOpened(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_MarkupAnnot_SetQuadPoints(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_FreeAnnot_SetEndingStyle(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_FreeAnnot_Set3PointCallout(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_FreeAnnot_Set2PointCallout(sLONG_PTR *pResult, PackagePtr pParams);
void PDF_FreeAnnot_SetDefaultStyle(sLONG_PTR *pResult, PackagePtr pParams);
