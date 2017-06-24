#include "hpdf_font.h"

// ------------------------------------- Font -------------------------------------

void PDF_Font_GetFontName(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);

	CUTF8String u = CUTF8String((const uint8_t *)HPDF_Font_GetFontName(font));
	returnValue.setUTF8String(&u);	
	
	returnValue.setReturn(pResult);
}

void PDF_Font_GetEncodingName(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	
	CUTF8String u = CUTF8String((const uint8_t *)HPDF_Font_GetEncodingName(font));
	returnValue.setUTF8String(&u);
	
	returnValue.setReturn(pResult);
}

void PDF_Font_GetUnicodeWidth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	HPDF_UNICODE code = (HPDF_UNICODE)Param2.getIntValue();
	
	returnValue.setIntValue(HPDF_Font_GetUnicodeWidth(font, code));
	
	returnValue.setReturn(pResult);
}

void PDF_Font_GetBBox(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	
	HPDF_Box bbox = HPDF_Font_GetBBox(font);
	
	Param2.setDoubleValue(bbox.left);
	Param3.setDoubleValue(bbox.bottom);
	Param4.setDoubleValue(bbox.right);
	Param5.setDoubleValue(bbox.top);	

	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
	Param5.toParamAtIndex(pParams, 5);
}

void PDF_Font_GetAscent(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Font_GetAscent(font));	
	
	returnValue.setReturn(pResult);
}

void PDF_Font_GetDescent(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Font_GetDescent(font));	
	
	returnValue.setReturn(pResult);
}

void PDF_Font_GetXHeight(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Font_GetXHeight(font));	
	
	returnValue.setReturn(pResult);
}

void PDF_Font_GetCapHeight(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Font_GetCapHeight(font));	
	
	returnValue.setReturn(pResult);
}

void PDF_Font_TextWidth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	CUTF8String u;
	Param2.copyUTF8String(&u);
	const HPDF_BYTE *text = (const HPDF_BYTE *)u.c_str();
	HPDF_UINT len = (HPDF_UINT)u.length();
	
	if(Param2.getUTF16Length())
	{
		HPDF_TextWidth width = HPDF_Font_TextWidth(font, text, len);
		Param3.setIntValue(width.numchars);
		Param4.setIntValue(width.width);		
		Param5.setIntValue(width.numspace);		
	}
	
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
	Param5.toParamAtIndex(pParams, 5);
}

void PDF_Font_MeasureText(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_LONGINT Param7;
	C_REAL Param8;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Font font = (HPDF_Font)_fromHex(Param1);
	CUTF8String u;
	Param2.copyUTF8String(&u);
	const HPDF_BYTE *text = (const HPDF_BYTE *)u.c_str();	
	HPDF_UINT len = (HPDF_UINT)u.length();
	HPDF_REAL width = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL font_size = (HPDF_REAL)Param4.getDoubleValue();		
	HPDF_REAL char_space = (HPDF_REAL)Param5.getDoubleValue();		
	HPDF_REAL word_space = (HPDF_REAL)Param6.getDoubleValue();	
	HPDF_BOOL wordwrap = (HPDF_BOOL)Param7.getIntValue();	
	HPDF_REAL real_width;
	
	if(Param2.getUTF16Length())
	{	
		returnValue.setIntValue(HPDF_Font_MeasureText(font, text, len, width, font_size, char_space, word_space, wordwrap, &real_width));
		Param8.setDoubleValue(real_width);
	}
	
	Param8.toParamAtIndex(pParams, 8);
	returnValue.setReturn(pResult);
}