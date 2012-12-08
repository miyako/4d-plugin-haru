#include "hpdf_page.h"

// ------------------------------------- Page -------------------------------------

#pragma mark -
#pragma mark annotation
#pragma mark -

void PDF_Page_CreateTextAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
	
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateTextAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateFreeTextAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);	
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
		
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateFreeTextAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateLineAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT Param3;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	std::string ansi_str;
	_convertFromUnicode(Param2, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param3);	
	
	if(Param2.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateLineAnnot(page, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateLinkAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
		
	HPDF_Destination dst = (HPDF_Destination)_documentGet(Param6);	
	
	HPDF_Annotation annot = HPDF_Page_CreateLinkAnnot(page, rect, dst);
	if(annot)
		_toHex(annot, returnValue);
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateURILinkAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
	
	CUTF8String u;
	Param6.copyUTF8String(&u);
	const char *uri = (const char *)u.c_str();
		
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateURILinkAnnot(page, rect, uri);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateHighlightAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
		
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateHighlightAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateUnderlineAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
		
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateUnderlineAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateSquigglyAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
		
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateSquigglyAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateStrikeOutAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;		
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
	
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateStrikeOutAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreatePopupAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
		
	HPDF_Annotation parent = (HPDF_Annotation)_fromHex(Param6);	
	
	HPDF_Annotation annot = HPDF_Page_CreatePopupAnnot(page, rect, parent);
	if(annot)
		_toHex(annot, returnValue);

	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateStampAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_LONGINT Param6;
	C_TEXT Param7;
	C_TEXT Param8;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	Param8.fromParamAtIndex(pParams, 8);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
	HPDF_StampAnnotName name = (HPDF_StampAnnotName)Param6.getIntValue();
	
	std::string ansi_str;
	_convertFromUnicode(Param7, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param8);	
	
	if(Param7.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateStampAnnot(page, rect, name, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateProjectionAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
		
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateProjectionAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateSquareAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
	
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateSquareAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateCircleAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
	
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateCircleAnnot(page, rect, text, encoder);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CreateTextMarkupAnnot(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_TEXT Param7;
	C_LONGINT Param8;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	Param8.fromParamAtIndex(pParams, 8);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
		
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();	
	
	HPDF_Encoder encoder = (HPDF_Encoder)_documentGet(Param7);	
	HPDF_AnnotType subType = (HPDF_AnnotType)Param8.getIntValue();
	
	if(Param6.getUTF16Length())
	{
		HPDF_Annotation annot = HPDF_Page_CreateTextMarkupAnnot(page, rect, text, encoder, subType);
		if(annot)
			_toHex(annot, returnValue);
	}
	
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark page
#pragma mark -

void PDF_Page_SetWidth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetWidth(page, value));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetHeight(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetHeight(page, value));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetSize(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_PageSizes size = (HPDF_PageSizes)Param2.getIntValue();
	HPDF_PageDirection direction = (HPDF_PageDirection)Param3.getIntValue();	
	
	returnValue.setIntValue(HPDF_Page_SetSize(page, size, direction));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetRotate(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_UINT16 angle = (HPDF_UINT16)Param2.getIntValue();
	
	returnValue.setIntValue(HPDF_Page_SetRotate(page, angle));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetZoom(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL zoom = Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetZoom(page, zoom));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetWidth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetWidth(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetHeight(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetHeight(page));
	
	returnValue.setReturn(pResult);
}
							
#pragma mark -

void PDF_Page_CreateDestination(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Destination destination = HPDF_Page_CreateDestination(page);
	if(destination)
		_toHex(destination, returnValue);
	
	returnValue.setReturn(pResult);
}

void PDF_Page_TextWidth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	std::string ansi_str;
	_convertFromUnicode(Param2, ansi_str);
	const char *text = ansi_str.c_str();	
	
	if(Param2.getUTF16Length())
	   returnValue.setDoubleValue(HPDF_Page_TextWidth(page, text));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_MeasureText(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_REAL Param3;	
	C_LONGINT Param4;	
	C_REAL Param5;		
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	std::string ansi_str;
	_convertFromUnicode(Param2, ansi_str);
	const char *text = ansi_str.c_str();
	
	HPDF_REAL width = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_BOOL wordwrap = (HPDF_BOOL)Param4.getIntValue();	
	HPDF_REAL real_width;
	
	if(Param2.getUTF16Length())
	{
		returnValue.setIntValue(HPDF_Page_MeasureText(page, text, width, wordwrap, &real_width));
		Param5.setDoubleValue(real_width);
	}
	
	Param5.toParamAtIndex(pParams, 5);
	returnValue.setReturn(pResult);
}

void PDF_Page_GetGMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_GetGMode(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetCurrentPos(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	HPDF_Point pos;
	returnValue.setIntValue(HPDF_Page_GetCurrentPos2(page, &pos));
	
	Param2.setDoubleValue(pos.x);
	Param3.setDoubleValue(pos.y);	
	
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
							
	returnValue.setReturn(pResult);								
}

void PDF_Page_GetCurrentTextPos(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	HPDF_Point pos;
	returnValue.setIntValue(HPDF_Page_GetCurrentTextPos2(page, &pos));
	
	Param2.setDoubleValue(pos.x);
	Param3.setDoubleValue(pos.y);
		
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	
	returnValue.setReturn(pResult);	
}

void PDF_Page_GetCurrentFont(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	HPDF_Font font = HPDF_Page_GetCurrentFont(page);
	if(font)
		_toHex(font, returnValue);
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetCurrentFontSize(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setDoubleValue(HPDF_Page_GetCurrentFontSize(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetTransMatrix(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	HPDF_TransMatrix tm = HPDF_Page_GetTransMatrix(page);
	
	Param2.setDoubleValue(tm.a);	
	Param3.setDoubleValue(tm.b);	
	Param4.setDoubleValue(tm.c);
	Param5.setDoubleValue(tm.d);	
	Param6.setDoubleValue(tm.x);	
	Param7.setDoubleValue(tm.y);	
	
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
	Param5.toParamAtIndex(pParams, 5);
	Param6.toParamAtIndex(pParams, 6);
	Param7.toParamAtIndex(pParams, 7);
}


#pragma mark -

void PDF_Page_GetLineWidth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetLineWidth(page));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetLineCap(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_GetLineCap(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetLineJoin(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_GetLineJoin(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetMiterLimit(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetMiterLimit(page));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetDash(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	ARRAY_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;	
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	HPDF_DashMode dm = HPDF_Page_GetDash(page);
	
	if(dm.num_ptn)
		Param2.setSize(1);
	
	for(unsigned int i=0; i < dm.num_ptn; ++i)
	{
		Param2.appendIntValue(dm.ptn[i]);
	}
	
	Param3.setIntValue(dm.num_ptn);
	Param4.setIntValue(dm.phase);
	
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetFlat(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetFlat(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetCharSpace(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetCharSpace(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetWordSpace(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetWordSpace(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetHorizontalScalling(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetHorizontalScalling(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetTextLeading(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetTextLeading(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetTextRenderingMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_GetTextRenderingMode(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetTextRise(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setDoubleValue(HPDF_Page_GetTextRise(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetRGBFill(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_RGBColor rgb = HPDF_Page_GetRGBFill(page);
	
	Param2.setDoubleValue(rgb.r);
	Param3.setDoubleValue(rgb.g);
	Param4.setDoubleValue(rgb.b);		

	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
}

void PDF_Page_GetRGBStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_RGBColor rgb = HPDF_Page_GetRGBStroke(page);
	
	Param2.setDoubleValue(rgb.r);
	Param3.setDoubleValue(rgb.g);
	Param4.setDoubleValue(rgb.b);		
	
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
}

void PDF_Page_GetCMYKFill(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_CMYKColor cmyk = HPDF_Page_GetCMYKFill(page);
	
	Param2.setDoubleValue(cmyk.c);
	Param3.setDoubleValue(cmyk.m);
	Param4.setDoubleValue(cmyk.y);	
	Param5.setDoubleValue(cmyk.k);			
	
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
	Param5.toParamAtIndex(pParams, 5);
}

void PDF_Page_GetCMYKStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_CMYKColor cmyk = HPDF_Page_GetCMYKStroke(page);
	
	Param2.setDoubleValue(cmyk.c);
	Param3.setDoubleValue(cmyk.m);
	Param4.setDoubleValue(cmyk.y);	
	Param5.setDoubleValue(cmyk.k);	
	
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
	Param5.toParamAtIndex(pParams, 5);
}

void PDF_Page_GetGrayFill(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setDoubleValue(HPDF_Page_GetGrayFill(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetGrayStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setDoubleValue(HPDF_Page_GetGrayStroke(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetStrokingColorSpace(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setIntValue(HPDF_Page_GetStrokingColorSpace(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetFillingColorSpace(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setIntValue(HPDF_Page_GetFillingColorSpace(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GetTextMatrix(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_TransMatrix matrix = HPDF_Page_GetTextMatrix(page);
	
	Param2.setDoubleValue(matrix.a);
	Param3.setDoubleValue(matrix.b);
	Param4.setDoubleValue(matrix.c);	
	Param5.setDoubleValue(matrix.d);
	Param6.setDoubleValue(matrix.x);	
	Param7.setDoubleValue(matrix.y);
	
	Param2.toParamAtIndex(pParams, 2);
	Param3.toParamAtIndex(pParams, 3);
	Param4.toParamAtIndex(pParams, 4);
	Param5.toParamAtIndex(pParams, 5);
	Param6.toParamAtIndex(pParams, 6);
	Param7.toParamAtIndex(pParams, 7);
}

void PDF_Page_GetGStateDepth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setIntValue(HPDF_Page_GetGStateDepth(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetSlideShow(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_REAL Param3;
	C_REAL Param4;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_TransitionStyle type = (HPDF_TransitionStyle)Param2.getIntValue();
	HPDF_REAL disp_time = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL trans_time = (HPDF_REAL)Param4.getDoubleValue();	
	
	HPDF_Page_SetSlideShow(page, type, disp_time, trans_time);
	
}

// ----------------------------------- Graphics -----------------------------------

#pragma mark -
#pragma mark general graphics state
#pragma mark -

void PDF_Page_SetLineWidth(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL line_width = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetLineWidth(page, line_width));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetLineCap(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_LineCap line_cap = (HPDF_LineCap)Param2.getIntValue();	
	
	returnValue.setIntValue(HPDF_Page_SetLineCap(page, line_cap));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetLineJoin(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_LineJoin line_join = (HPDF_LineJoin)Param2.getIntValue();	
	
	returnValue.setIntValue(HPDF_Page_SetLineJoin(page, line_join));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetMiterLimit(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL miter_limit = (HPDF_REAL)Param2.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_SetMiterLimit(page, miter_limit));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetDash(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	ARRAY_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	std::vector<HPDF_UINT16> dash_ptn; 
	
	for(unsigned int i = 1; i <= Param2.getSize(); ++i)
	{
		dash_ptn.push_back(Param2.getIntValueAtIndex(i));
	}
	
	HPDF_UINT num_param = (HPDF_UINT)Param3.getIntValue();	
	HPDF_UINT flatness = (HPDF_UINT)Param4.getIntValue();
	
	returnValue.setIntValue(HPDF_Page_SetDash(page, &dash_ptn[0], num_param, flatness));		
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetFlat(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL flatness = (HPDF_REAL)Param2.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_SetFlat(page, flatness));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetExtGState(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_ExtGState ext_gstate = (HPDF_ExtGState)_fromHex(Param2);
	
	returnValue.setIntValue(HPDF_Page_SetExtGState(page, ext_gstate));	
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark special graphic state
#pragma mark -

void PDF_Page_GSave(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_GSave(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_GRestore(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_GRestore(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_Concat(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL a = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL b = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL c = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL d = (HPDF_REAL)Param5.getDoubleValue();
	HPDF_REAL x = (HPDF_REAL)Param6.getDoubleValue();
	HPDF_REAL y = (HPDF_REAL)Param7.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_Concat(page, a, b, c, d, x, y));	
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark path
#pragma mark -

void PDF_Page_MoveTo(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	float x = Param2.getDoubleValue();
	float y = Param3.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_MoveTo(page, x, y));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_LineTo(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x = Param2.getDoubleValue();
	HPDF_REAL y = Param3.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_LineTo(page, x, y));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CurveTo(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x1 = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL y1 = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL x2 = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL y2 = (HPDF_REAL)Param5.getDoubleValue();
	HPDF_REAL x3 = (HPDF_REAL)Param6.getDoubleValue();
	HPDF_REAL y3 = (HPDF_REAL)Param7.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_CurveTo(page, x1, y1, x2, y2, x3, y3));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CurveTo2(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x2 = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL y2 = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL x3 = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL y3 = (HPDF_REAL)Param5.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_CurveTo2(page, x2, y2, x3, y3));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_CurveTo3(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x1 = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL y1 = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL x3 = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL y3 = (HPDF_REAL)Param5.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_CurveTo3(page, x1, y1, x3, y3));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_ClosePath(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_ClosePath(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_Rectangle(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL y = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL width = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL height = (HPDF_REAL)Param5.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_Rectangle(page, x, y, width, height));
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark path presentation
#pragma mark -

void PDF_Page_Stroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_Stroke(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_ClosePathStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_ClosePathStroke(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_Fill(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_Fill(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_Eofill(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_Eofill(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_FillStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_FillStroke(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_EofillStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_EofillStroke(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_ClosePathFillStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_ClosePathFillStroke(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_ClosePathEofillStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_ClosePathEofillStroke(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_EndPath(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_EndPath(page));
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark clipping path
#pragma mark -

void PDF_Page_Clip(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_Clip(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_Eoclip(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Page_Eoclip(page));
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark text
#pragma mark -

void PDF_Page_BeginText(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setIntValue(HPDF_Page_BeginText(page));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_EndText(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setIntValue(HPDF_Page_EndText(page));
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark text state
#pragma mark -

void PDF_Page_SetCharSpace(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetCharSpace(page, value));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetWordSpace(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetWordSpace(page, value));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetHorizontalScalling(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetHorizontalScalling(page, value));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetTextLeading(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetTextLeading(page, value));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetFontAndSize(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_REAL Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Font font = (HPDF_Font)_fromHex(Param2);	
	HPDF_REAL size = (HPDF_REAL)Param3.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetFontAndSize(page, font, size));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetTextRenderingMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_TextRenderingMode mode = (HPDF_TextRenderingMode)Param2.getIntValue();
	
	returnValue.setIntValue(HPDF_Page_SetTextRenderingMode(page, mode));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetTextRise(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetTextRise(page, value));	
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark text positioning
#pragma mark -

void PDF_Page_MoveTextPos(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x = Param2.getDoubleValue();
	HPDF_REAL y = Param3.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_MoveTextPos2(page, x, y));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetTextMatrix(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL a = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL b = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL c = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL d = (HPDF_REAL)Param5.getDoubleValue();
	HPDF_REAL x = (HPDF_REAL)Param6.getDoubleValue();
	HPDF_REAL y = (HPDF_REAL)Param7.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetTextMatrix(page, a, b, c, d, x, y));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_MoveToNextLine(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	returnValue.setIntValue(HPDF_Page_MoveToNextLine(page));
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark text display
#pragma mark -

void PDF_Page_ShowText(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	std::string ansi_str;
	_convertFromUnicode(Param2, ansi_str);
	const char *text = ansi_str.c_str();	
	
	if(Param2.getUTF16Length())
		returnValue.setIntValue(HPDF_Page_ShowText(page, text));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_ShowTextNextLine(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	
	std::string ansi_str;
	_convertFromUnicode(Param2, ansi_str);
	const char *text = ansi_str.c_str();	
	
	if(Param2.getUTF16Length())
		returnValue.setIntValue(HPDF_Page_ShowTextNextLine(page, text));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_ShowTextNextLineEx(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_TEXT Param4;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL word_space = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL char_space = (HPDF_REAL)Param3.getDoubleValue();
	
	std::string ansi_str;
	_convertFromUnicode(Param4, ansi_str);
	const char *text = ansi_str.c_str();	
	
	if(Param4.getUTF16Length())
		returnValue.setIntValue(HPDF_Page_ShowTextNextLineEx(page, word_space, char_space, text));
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark color
#pragma mark -

void PDF_Page_SetGrayFill(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;	
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL gray = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetGrayFill(page, gray));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetGrayStroke(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;	
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL gray = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_SetGrayStroke(page, gray));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetRGBFill(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL r = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL g = (HPDF_REAL)Param3.getDoubleValue();	
	HPDF_REAL b = (HPDF_REAL)Param4.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_SetRGBFill(page, r, g, b));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetRGBStroke(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL r = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL g = (HPDF_REAL)Param3.getDoubleValue();	
	HPDF_REAL b = (HPDF_REAL)Param4.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_SetRGBStroke(page, r, g, b));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetCMYKFill(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL c = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL m = (HPDF_REAL)Param3.getDoubleValue();	
	HPDF_REAL y = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL k = (HPDF_REAL)Param5.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_SetCMYKFill(page, c, m, y, k));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_SetCMYKStroke(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL c = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL m = (HPDF_REAL)Param3.getDoubleValue();	
	HPDF_REAL y = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL k = (HPDF_REAL)Param5.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_SetCMYKStroke(page, c, m, y, k));	
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark compatibility
#pragma mark -

void PDF_Page_DrawImage(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_Image image = (HPDF_Image)_fromHex(Param2);
	HPDF_REAL x = (HPDF_REAL)Param3.getDoubleValue();	
	HPDF_REAL y = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL width = (HPDF_REAL)Param5.getDoubleValue();	
	HPDF_REAL height = (HPDF_REAL)Param6.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_DrawImage(page, image, x, y, width, height));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_Circle(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x = (HPDF_REAL)Param2.getDoubleValue();	
	HPDF_REAL y = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL ray = (HPDF_REAL)Param4.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_Circle(page, x, y, ray));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_Ellipse(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x = (HPDF_REAL)Param2.getDoubleValue();	
	HPDF_REAL y = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL xray = (HPDF_REAL)Param4.getDoubleValue();	
	HPDF_REAL yray = (HPDF_REAL)Param5.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_Page_Ellipse(page, x, y, xray, yray));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_Arc(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL x = (HPDF_REAL)Param2.getDoubleValue();	
	HPDF_REAL y = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_REAL ray = (HPDF_REAL)Param4.getDoubleValue();	
	HPDF_REAL ang1 = (HPDF_REAL)Param5.getDoubleValue();	
	HPDF_REAL ang2 = (HPDF_REAL)Param6.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Page_Arc(page, x, y, ray, ang1, ang2));	
	
	returnValue.setReturn(pResult);
}

void PDF_Page_TextOut(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_TEXT Param4;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL xpos = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL ypos = (HPDF_REAL)Param3.getDoubleValue();	
	
	std::string ansi_str;
	_convertFromUnicode(Param4, ansi_str);
	const char *text = ansi_str.c_str();	
	
	if(Param4.getUTF16Length())
		returnValue.setIntValue(HPDF_Page_TextOut(page, xpos, ypos, text));
	
	returnValue.setReturn(pResult);
}

void PDF_Page_TextRect(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_TEXT Param6;
	C_LONGINT Param7;
	C_LONGINT Param8;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	Param8.fromParamAtIndex(pParams, 8);
	
	HPDF_Page page = (HPDF_Page)_fromHex(Param1);
	HPDF_REAL left = (HPDF_REAL)Param2.getDoubleValue();
	HPDF_REAL top = (HPDF_REAL)Param3.getDoubleValue();	
	HPDF_REAL right = (HPDF_REAL)Param4.getDoubleValue();
	HPDF_REAL bottom = (HPDF_REAL)Param5.getDoubleValue();	
		
	std::string ansi_str;
	_convertFromUnicode(Param6, ansi_str);
	const char *text = ansi_str.c_str();		
	
	HPDF_TextAlignment align = (HPDF_TextAlignment)Param7.getIntValue();
	HPDF_UINT len = (HPDF_UINT)Param8.getIntValue();		
	
	if(Param6.getUTF16Length())
	{
		returnValue.setIntValue(HPDF_Page_TextRect(page, left, top, right, bottom, text, align, &len));
		Param8.toParamAtIndex(pParams, 8);
	}
	
	returnValue.setReturn(pResult);
}
