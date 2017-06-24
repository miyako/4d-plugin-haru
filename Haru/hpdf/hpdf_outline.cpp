#include "hpdf_outline.h"

// ------------------------------------ Outline -----------------------------------

void PDF_Outline_SetDestination(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Outline outline = (HPDF_Outline)_fromHex(Param1);
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param2);
	
	returnValue.setIntValue(HPDF_Outline_SetDestination(outline, dst));
	
	returnValue.setReturn(pResult);
}

void PDF_Outline_SetOpened(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Outline outline = (HPDF_Outline)_fromHex(Param1);
	HPDF_BOOL opened = (HPDF_BOOL)Param2.getIntValue();
	
	returnValue.setIntValue(HPDF_Outline_SetOpened(outline, opened));
	
	returnValue.setReturn(pResult);
}
