#include "hpdf_image.h"

// ------------------------------------- Image ------------------------------------

void PDF_Image_AddSMask(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Image image = (HPDF_Image)_fromHex(Param1);
	HPDF_Image smask = (HPDF_Image)_fromHex(Param2);

	returnValue.setIntValue(HPDF_Image_AddSMask(image, smask));
	
	returnValue.setReturn(pResult);	
}

void PDF_Image_GetSize(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Image image = (HPDF_Image)_fromHex(Param1);
	
	HPDF_Point size;
	returnValue.setIntValue(HPDF_Image_GetSize2(image, &size));
	
	Param2.setDoubleValue(size.x);
	Param3.setDoubleValue(size.y);
	
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	
	returnValue.setReturn(pResult);		
}

void PDF_Image_GetWidth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Image image = (HPDF_Image)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Image_GetWidth(image));
	
	returnValue.setReturn(pResult);
}

void PDF_Image_GetHeight(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Image image = (HPDF_Image)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Image_GetHeight(image));
	
	returnValue.setReturn(pResult);
}

void PDF_Image_GetBitsPerComponent(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Image image = (HPDF_Image)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Image_GetBitsPerComponent(image));
	
	returnValue.setReturn(pResult);
}

void PDF_Image_GetColorSpace(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Image image = (HPDF_Image)_fromHex(Param1);
	
	CUTF8String u = CUTF8String((const uint8_t *)HPDF_Image_GetColorSpace(image));
	returnValue.setUTF8String(&u);
	
	returnValue.setReturn(pResult);
}

void PDF_Image_SetColorMask(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	C_LONGINT Param6;
	C_LONGINT Param7;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Image image = (HPDF_Image)_fromHex(Param1);
	HPDF_UINT rmin = (HPDF_UINT)Param2.getIntValue();
	HPDF_UINT rmax = (HPDF_UINT)Param3.getIntValue();
	HPDF_UINT gmin = (HPDF_UINT)Param4.getIntValue();
	HPDF_UINT gmax = (HPDF_UINT)Param5.getIntValue();
	HPDF_UINT bmin = (HPDF_UINT)Param6.getIntValue();
	HPDF_UINT bmax = (HPDF_UINT)Param7.getIntValue();	
	
	returnValue.setIntValue(HPDF_Image_SetColorMask(image, rmin, rmax, gmin, gmax, bmin, bmax));
	
	returnValue.setReturn(pResult);
}

void PDF_Image_SetMaskImage(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Image image = (HPDF_Image)_fromHex(Param1);
	HPDF_Image mask_image = (HPDF_Image)_fromHex(Param2);
	
	returnValue.setIntValue(HPDF_Image_SetMaskImage(image, mask_image));
	
	returnValue.setReturn(pResult);
}
