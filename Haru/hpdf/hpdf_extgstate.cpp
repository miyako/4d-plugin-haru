#include "hpdf_extgstate.h"

// ---------------------------- Extended Graphics State ---------------------------

void PDF_ExtGState_SetAlphaStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_ExtGState ext_gstate = (HPDF_ExtGState)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_ExtGState_SetAlphaStroke(ext_gstate, value));	
	
	returnValue.setReturn(pResult);
}

void PDF_ExtGState_SetAlphaFill(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_ExtGState ext_gstate = (HPDF_ExtGState)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_ExtGState_SetAlphaFill(ext_gstate, value));	
		
	returnValue.setReturn(pResult);
}

void PDF_ExtGState_SetBlendMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_ExtGState ext_gstate = (HPDF_ExtGState)_fromHex(Param1);
	HPDF_BlendMode mode = (HPDF_BlendMode)Param2.getIntValue();
	
	returnValue.setIntValue(HPDF_ExtGState_SetBlendMode(ext_gstate, mode));
	
	returnValue.setReturn(pResult);
}

