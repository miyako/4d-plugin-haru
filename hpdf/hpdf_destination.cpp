#include "hpdf_destination.h"

// ---------------------------------- Destination ---------------------------------

void PDF_Destination_SetXYZ(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param1);
	HPDF_REAL left = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL top = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL zoom = (HPDF_REAL)Param4.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Destination_SetXYZ(dst, left, top, zoom));
	
	returnValue.setReturn(pResult);
}

void PDF_Destination_SetFit(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Destination_SetFit(dst));
	
	returnValue.setReturn(pResult);
}

void PDF_Destination_SetFitH(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param1);
	HPDF_REAL top = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Destination_SetFitH(dst, top));	
	
	returnValue.setReturn(pResult);
}

void PDF_Destination_SetFitV(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param1);
	HPDF_REAL left = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Destination_SetFitV(dst, left));	
	
	returnValue.setReturn(pResult);
}

void PDF_Destination_SetFitR(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param1);
	HPDF_REAL left = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL bottom = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL right = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL top = (HPDF_REAL)Param5.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Destination_SetFitR(dst, left, bottom, right, top));
	
	returnValue.setReturn(pResult);
}

void PDF_Destination_SetFitB(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Destination_SetFitB(dst));
	
	returnValue.setReturn(pResult);
}

void PDF_Destination_SetFitBH(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param1);
	HPDF_REAL top = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Destination_SetFitBH(dst, top));	
	
	returnValue.setReturn(pResult);
}

void PDF_Destination_SetFitBV(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Destination dst = (HPDF_Destination)_fromHex(Param1);
	HPDF_REAL left = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Destination_SetFitBV(dst, left));	
		
	returnValue.setReturn(pResult);
}
