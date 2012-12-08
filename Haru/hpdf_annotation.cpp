#include "hpdf_annotation.h"

// ---------------------------------- Annotation ----------------------------------

void PDF_MarkupAnnot_SetPopup(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_Annotation popup = (HPDF_Annotation)_fromHex(Param2);
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetPopup(annot, popup));
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetIntent(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_AnnotIntent intent = (HPDF_AnnotIntent)Param2.getIntValue();
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetIntent(annot, intent));
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetAlpha(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_REAL value = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetTransparency(annot, value));
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetDate(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_DATE Param2;
	C_TIME Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	C_LONGINT Param6;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_Date value;

	value.year = Param2.getYear();
	value.month = Param2.getMonth();
	value.day = Param2.getDay();
	value.hour = Param3.getHour();
	value.minutes = Param3.getMinutes();		
	value.seconds = Param3.getSeconds();	
	
	switch (Param4.getIntValue()){
		case 1://HPDF_UTC_OFFSET_POSITIVE
			value.ind = '+';
			break;	
		case 2://HPDF_UTC_OFFSET_NEGATIVE
			value.ind = '-';
			break;	
		case 3://HPDF_UTC_OFFSET_ZERO
			value.ind = 'Z';
			break;					
		default://HPDF_UTC_OFFSET_NONE
			value.ind = ' ';
			break;	
	}
	
	value.off_hour = Param5.getIntValue();
	value.off_minutes = Param6.getIntValue();
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetCreationDate(annot, value));
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetSubject(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);

	CUTF8String u;
	Param2.copyUTF8String(&u);
	const char *name = (const char *)u.c_str();

	if(Param2.getUTF16Length())
	{
		returnValue.setIntValue(HPDF_MarkupAnnot_SetSubject(annot, name));		
	}
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetTitle(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	
	CUTF8String u;
	Param2.copyUTF8String(&u);
	const char *name = (const char *)u.c_str();
	
	if(Param2.getUTF16Length())
	{
		returnValue.setIntValue(HPDF_MarkupAnnot_SetTitle(annot, name));		
	}
	
	returnValue.setReturn(pResult);
}

void PDF_Annot_SetNoColor(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_Annot_SetNoColor(annot));
	
	returnValue.setReturn(pResult);
}

void PDF_Annot_SetGrayColor(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_REAL color = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Annot_SetGrayColor(annot, color));
	
	returnValue.setReturn(pResult);
}

void PDF_Annot_SetCMYKColor(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_CMYKColor color;
	color.c = (HPDF_REAL)Param2.getDoubleValue();
	color.m = (HPDF_REAL)Param3.getDoubleValue();
	color.y = (HPDF_REAL)Param4.getDoubleValue();
	color.k = (HPDF_REAL)Param5.getDoubleValue();

	returnValue.setIntValue(HPDF_Annot_SetCMYKColor(annot, color));	
	
	returnValue.setReturn(pResult);
}

void PDF_Annot_SetRGBColor(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_RGBColor color;
	color.r = (HPDF_REAL)Param2.getDoubleValue();
	color.g = (HPDF_REAL)Param3.getDoubleValue();
	color.b = (HPDF_REAL)Param4.getDoubleValue();
	
	returnValue.setIntValue(HPDF_Annot_SetRGBColor(annot, color));	
	
	returnValue.setReturn(pResult);
}

void PDF_Annotation_SetBorderStyle(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_REAL Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	C_LONGINT Param6;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_BSSubtype subtype = (HPDF_BSSubtype)Param2.getIntValue();	
	HPDF_REAL width = (HPDF_REAL)Param3.getDoubleValue();		
	HPDF_UINT16 dash_on = (HPDF_UINT16)Param4.getIntValue();	
	HPDF_UINT16 dash_off = (HPDF_UINT16)Param5.getIntValue();	
	HPDF_UINT16 dash_phase = (HPDF_UINT16)Param6.getIntValue();	
	
	returnValue.setIntValue(HPDF_Annotation_SetBorderStyle(annot, subtype, width, dash_on, dash_off, dash_phase));		
	
	returnValue.setReturn(pResult);
}

void PDF_TextAnnot_SetOpened(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_BOOL opened = (HPDF_BOOL)Param2.getIntValue();		
	
	returnValue.setIntValue(HPDF_TextAnnot_SetOpened(annot, opened));		
	
	returnValue.setReturn(pResult);
}

void PDF_TextAnnot_SetIcon(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_AnnotIcon icon = (HPDF_AnnotIcon)Param2.getIntValue();		
	
	returnValue.setIntValue(HPDF_TextAnnot_SetIcon(annot, icon));	
	
	returnValue.setReturn(pResult);
}

void PDF_LinkAnnot_SetBorderStyle(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_REAL width = (HPDF_REAL)Param2.getDoubleValue();	
	HPDF_UINT16 dash_on = (HPDF_UINT16)Param3.getIntValue();		
	HPDF_UINT16 dash_off = (HPDF_UINT16)Param4.getIntValue();	
	
	returnValue.setIntValue(HPDF_LinkAnnot_SetBorderStyle(annot, width, dash_on, dash_off));		
	
	returnValue.setReturn(pResult);
}

void PDF_LinkAnnot_SetHighlightMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_AnnotHighlightMode mode = (HPDF_AnnotHighlightMode)Param2.getIntValue();	
	
	returnValue.setIntValue(HPDF_LinkAnnot_SetHighlightMode(annot, mode));		
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetRectDiff(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_Rect rect;
	rect.left = Param2.getDoubleValue();
	rect.bottom = Param3.getDoubleValue();
	rect.right = Param4.getDoubleValue();
	rect.top = Param5.getDoubleValue();	
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetRectDiff(annot, rect));
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetCloudEffect(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_INT cloudIntensity = (HPDF_INT)Param2.getIntValue();
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetCloudEffect(annot, cloudIntensity));
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetRGBColor(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_RGBColor color;
	color.r = (HPDF_REAL)Param2.getDoubleValue();
	color.g = (HPDF_REAL)Param3.getDoubleValue();
	color.b = (HPDF_REAL)Param4.getDoubleValue();
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetInteriorRGBColor(annot, color));	
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetCMYKColor(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_CMYKColor color;
	color.c = (HPDF_REAL)Param2.getDoubleValue();
	color.m = (HPDF_REAL)Param3.getDoubleValue();
	color.y = (HPDF_REAL)Param4.getDoubleValue();
	color.k = (HPDF_REAL)Param5.getDoubleValue();
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetInteriorCMYKColor(annot, color));	
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetGrayColor(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_REAL color = (HPDF_REAL)Param2.getDoubleValue();
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetInteriorGrayColor(annot, color));
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetNoColor(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	
	returnValue.setIntValue(HPDF_MarkupAnnot_SetInteriorTransparent(annot));
	
	returnValue.setReturn(pResult);
}

void PDF_LineAnnot_SetLeader(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_INT leaderLen = (HPDF_INT)Param2.getIntValue();
	HPDF_INT leaderExtLen = (HPDF_INT)Param3.getIntValue();
	HPDF_INT leaderOffsetLen = (HPDF_INT)Param4.getIntValue();
	
	returnValue.setIntValue(HPDF_LineAnnot_SetLeader(annot, leaderLen, leaderExtLen, leaderOffsetLen));
	
	returnValue.setReturn(pResult);
}

void PDF_LineAnnot_SetCaption(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_BOOL showCaption = (HPDF_BOOL)Param2.getIntValue();
	HPDF_LineAnnotCapPosition position = (HPDF_LineAnnotCapPosition)Param3.getIntValue();
	HPDF_INT horzOffset = (HPDF_INT)Param4.getIntValue();
	HPDF_INT vertOffset = (HPDF_INT)Param5.getIntValue();
	
	returnValue.setIntValue(HPDF_LineAnnot_SetCaption(annot, showCaption, position, horzOffset, vertOffset));
	
	returnValue.setReturn(pResult);
}

void PDF_LineAnnot_SetPosition(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_LONGINT Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_LONGINT Param7;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_Point startPoint, endPoint;
	startPoint.x = (HPDF_REAL)Param2.getDoubleValue();
	startPoint.y = (HPDF_REAL)Param3.getDoubleValue();
	HPDF_LineAnnotEndingStyle startStyle = (HPDF_LineAnnotEndingStyle)Param4.getIntValue();
	endPoint.x = (HPDF_REAL)Param5.getDoubleValue();
	endPoint.y = (HPDF_REAL)Param6.getDoubleValue();
	HPDF_LineAnnotEndingStyle endStyle = (HPDF_LineAnnotEndingStyle)Param7.getIntValue();
	
	returnValue.setIntValue(HPDF_LineAnnot_SetPosition(annot, startPoint, startStyle, endPoint, endStyle));
	
	returnValue.setReturn(pResult);
}

void PDF_PopupAnnot_SetOpened(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_BOOL opened = (HPDF_BOOL)Param2.getIntValue();
	
	returnValue.setIntValue(HPDF_PopupAnnot_SetOpened(annot, opened));
	
	returnValue.setReturn(pResult);
}

void PDF_MarkupAnnot_SetQuadPoints(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_REAL Param2;
	C_REAL Param3;
	C_REAL Param4;
	C_REAL Param5;
	C_REAL Param6;
	C_REAL Param7;
	C_REAL Param8;
	C_REAL Param9;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	Param7.fromParamAtIndex(pParams, 7);
	Param8.fromParamAtIndex(pParams, 8);
	Param9.fromParamAtIndex(pParams, 9);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_Point lb, rb, rt, lt;
	lb.x = (HPDF_REAL)Param2.getDoubleValue();
	lb.y = (HPDF_REAL)Param3.getDoubleValue();
	rb.x = (HPDF_REAL)Param4.getDoubleValue();
	rb.y = (HPDF_REAL)Param5.getDoubleValue();	
	rt.x = (HPDF_REAL)Param6.getDoubleValue();
	rt.y = (HPDF_REAL)Param7.getDoubleValue();
	lt.x = (HPDF_REAL)Param8.getDoubleValue();
	lt.y = (HPDF_REAL)Param9.getDoubleValue();
	
	returnValue.setIntValue(HPDF_TextMarkupAnnot_SetQuadPoints(annot, lb, rb, rt, lt));
	
	
	returnValue.setReturn(pResult);
}

void PDF_FreeAnnot_SetEndingStyle(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_LineAnnotEndingStyle startStyle = (HPDF_LineAnnotEndingStyle)Param2.getIntValue();
	HPDF_LineAnnotEndingStyle endStyle = (HPDF_LineAnnotEndingStyle)Param3.getIntValue();
	
	returnValue.setIntValue(HPDF_FreeTextAnnot_SetLineEndingStyle(annot, startStyle, endStyle));
	
	returnValue.setReturn(pResult);
}

void PDF_FreeAnnot_Set3PointCallout(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_Point startPoint, kneePoint, endPoint;
	startPoint.x = (HPDF_REAL)Param2.getDoubleValue();
	startPoint.y = (HPDF_REAL)Param3.getDoubleValue();
	kneePoint.x = (HPDF_REAL)Param4.getDoubleValue();
	kneePoint.y = (HPDF_REAL)Param5.getDoubleValue();	
	endPoint.x = (HPDF_REAL)Param6.getDoubleValue();
	endPoint.y = (HPDF_REAL)Param7.getDoubleValue();
	
	returnValue.setIntValue(HPDF_FreeTextAnnot_Set3PointCalloutLine(annot, startPoint, kneePoint, endPoint));
	
	returnValue.setReturn(pResult);
}

void PDF_FreeAnnot_Set2PointCallout(sLONG_PTR *pResult, PackagePtr pParams)
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
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	HPDF_Point startPoint, endPoint;
	startPoint.x = (HPDF_REAL)Param2.getDoubleValue();
	startPoint.y = (HPDF_REAL)Param3.getDoubleValue();
	endPoint.x = (HPDF_REAL)Param4.getDoubleValue();
	endPoint.y = (HPDF_REAL)Param5.getDoubleValue();
	
	returnValue.setIntValue(HPDF_FreeTextAnnot_Set2PointCalloutLine(annot, startPoint, endPoint));
	
	returnValue.setReturn(pResult);
}

void PDF_FreeAnnot_SetDefaultStyle(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Annotation annot = (HPDF_Annotation)_fromHex(Param1);
	CUTF8String u;
	Param2.copyUTF8String(&u);
	const char *style = (const char *)u.c_str();
	
	if(Param2.getUTF16Length())
	{
		returnValue.setIntValue(HPDF_FreeTextAnnot_SetDefaultStyle(annot, style));
	}
	
	returnValue.setReturn(pResult);
}
