#include "hpdf_document.h"

// ----------------------------------- Document -----------------------------------

#pragma mark -
#pragma mark document
#pragma mark -

#if defined(_WIN32)
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif

void PDF_New(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT returnValue;
	
	_documentCreate(returnValue);
	
	returnValue.setReturn(pResult);
}

void PDF_Free(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	_documentDelete(Param1);
	
}

void PDF_NewDoc(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_NewDoc(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_FreeDoc(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		HPDF_FreeDoc(pdf);
	}
	
}

void PDF_HasDoc(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_HasDoc(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_FreeDocAll(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		HPDF_FreeDocAll(pdf);
	}
	
}

void PDF_SaveToStream(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_BLOB Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(HPDF_SaveToStream(pdf) == HPDF_OK)
		{
			HPDF_UINT32 size = HPDF_GetStreamSize(pdf);
			std::vector<char> buf(size);
			if(HPDF_ReadFromStream(pdf, (HPDF_BYTE *)&buf[0], &size) == HPDF_OK)
			{
				Param2.setBytes((const uint8_t *)&buf[0], size);
			}else{
				returnValue.setIntValue(HPDF_GetError(pdf));
			}			
		}else{
			returnValue.setIntValue(HPDF_GetError(pdf));
		}
	}
	
	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

void PDF_SaveToFile(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
#if VERSIONMAC	
	CUTF8String u;
	Param2.copyPath(&u);
	const char *file_name = (const char *)u.c_str();
#else
	const wchar_t *file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
#endif	
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getUTF16Length())
			returnValue.setIntValue(HPDF_SaveToFile(pdf, file_name));
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_ResetError(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
	}	
	
}

void PDF_SetPagesConfiguration(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_UINT page_per_pages = (HPDF_UINT)Param2.getIntValue();
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_SetPagesConfiguration(pdf, page_per_pages));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_SetInfoAttr(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_TEXT Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_InfoType type = (HPDF_InfoType)Param2.getIntValue();
	CUTF8String u;
	Param3.copyUTF8String(&u);
	const char *value = (const char *)u.c_str();	
	
	if(pdf)
	{
		if(Param3.getUTF16Length())			
			returnValue.setIntValue(HPDF_SetInfoAttr(pdf, type, value));
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_GetInfoAttr(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_InfoType type = (HPDF_InfoType)Param2.getIntValue();
	
	if(pdf)
	{
		CUTF8String u = CUTF8String((const uint8_t *)HPDF_GetInfoAttr(pdf, type));
		returnValue.setUTF8String(&u);
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_SetInfoDateAttr(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_DATE Param3;
	C_TIME Param4;
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
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_InfoType type = (HPDF_InfoType)Param2.getIntValue();
	HPDF_Date value;
	
	if(pdf)
	{
		switch (Param5.getIntValue()){
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
		
		value.year = Param3.getYear();
		value.month = Param3.getMonth();
		value.day = Param3.getDay();
		
		unsigned char    hour;
		unsigned char    minutes;
		unsigned char    seconds;
		
		Param4.getHourMinuteSecond(&hour,
															 &minutes,
															 &seconds);
		value.hour = hour;
		value.minutes = minutes;
		value.seconds = seconds;
		
		value.off_hour = Param6.getIntValue();
		value.off_minutes = Param7.getIntValue();
		
		returnValue.setIntValue(HPDF_SetInfoDateAttr(pdf, type, value));
		
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_SetPassword(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Doc pdf = _documentGet(Param1);
	CUTF8String u, v;
	Param2.copyUTF8String(&u);
	Param3.copyUTF8String(&v);	
	const char *owner_passwd = (const char *)u.c_str();
	const char *user_passwd = (const char *)v.c_str();	
	
	if(pdf)
	{
		if(Param2.getUTF16Length() && Param3.getUTF16Length())
			returnValue.setIntValue(HPDF_SetPassword(pdf, owner_passwd, user_passwd));
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_SetPermission(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_UINT permission = (HPDF_UINT)Param2.getIntValue();
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_SetPermission(pdf, permission));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_SetEncryptionMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_EncryptMode mode = (HPDF_EncryptMode)Param2.getIntValue();
	HPDF_UINT key_len = (HPDF_UINT)Param3.getIntValue();
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_SetEncryptionMode(pdf, mode, key_len));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_SetCompressionMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_UINT mode = (HPDF_UINT)Param2.getIntValue();
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_SetCompressionMode(pdf, mode));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_GetViewerPreference(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_GetViewerPreference(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_SetViewerPreference(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_UINT value = (HPDF_UINT)Param2.getIntValue();
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_SetViewerPreference(pdf, value));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_GetPageLayout(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_GetPageLayout(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_SetPageLayout(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_PageLayout layout = (HPDF_PageLayout)Param2.getIntValue();
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_SetPageLayout(pdf, layout));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_GetPageMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_GetPageMode(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_SetPageMode(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_PageMode mode = (HPDF_PageMode)Param2.getIntValue();
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_SetPageMode(pdf, mode));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_SetOpenAction(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_Destination open_action = (HPDF_Destination)_fromHex(Param2);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_SetOpenAction(pdf, open_action));
	}
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark extended graphics state
#pragma mark -

void PDF_CreateExtGState(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		HPDF_ExtGState gstate = HPDF_CreateExtGState(pdf);
		if(gstate)
			_toHex(gstate, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark image
#pragma mark -

void PDF_LoadPngImageFromMem(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_BLOB Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	const HPDF_BYTE *buf = (const HPDF_BYTE *)Param2.getBytesPtr();
	HPDF_UINT size = (HPDF_UINT)Param2.getBytesLength();
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getBytesLength())
		{
			HPDF_Image image = HPDF_LoadPngImageFromMem(pdf, buf, size);
			if(image)
				_toHex(image, returnValue);
		}
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_LoadPngImageFromFile(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);

#if VERSIONMAC	
	CUTF8String u;
	Param2.copyPath(&u);
	const char *file_name = (const char *)u.c_str();
#else
	const wchar_t *file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
#endif	

	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getUTF16Length())
		{
			HPDF_Image image = HPDF_LoadPngImageFromFile(pdf, file_name);
			if(image)
				_toHex(image, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

void PDF_LoadPngImageFromFile2(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);

#if VERSIONMAC	
	CUTF8String u;
	Param2.copyPath(&u);
	const char *file_name = (const char *)u.c_str();
#else
	const wchar_t *file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
#endif	
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getUTF16Length())
		{
			HPDF_Image image = HPDF_LoadPngImageFromFile2(pdf, file_name);
			if(image)
				_toHex(image, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

void PDF_LoadJpegImageFromFile(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);

#if VERSIONMAC	
	CUTF8String u;
	Param2.copyPath(&u);
	const char *file_name = (const char *)u.c_str();
#else
	const wchar_t *file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
#endif	
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getUTF16Length())
		{
			HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf, file_name);
			if(image)
				_toHex(image, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

void PDF_LoadJpegImageFromMem(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_BLOB Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	const HPDF_BYTE *buf = (const HPDF_BYTE *)Param2.getBytesPtr();
	HPDF_UINT size = (HPDF_UINT)Param2.getBytesLength();
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getBytesLength())
		{
			HPDF_Image image = HPDF_LoadJpegImageFromMem(pdf, buf, size);
			if(image)
				_toHex(image, returnValue);
		}
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_LoadU3DFromFile(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);

#if VERSIONMAC	
	CUTF8String u;
	Param2.copyPath(&u);
	const char *file_name = (const char *)u.c_str();
#else
	const wchar_t *file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
#endif	

	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getUTF16Length())
		{
			HPDF_Image image = HPDF_LoadU3DFromFile(pdf, file_name);
			if(image)
				_toHex(image, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

void PDF_LoadRaw1BitImageFromMem(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_BLOB Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	C_LONGINT Param6;
	C_LONGINT Param7;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);	
	Param7.fromParamAtIndex(pParams, 7);
	
	HPDF_Doc pdf = _documentGet(Param1);
	const HPDF_BYTE *buf = (const HPDF_BYTE *)Param2.getBytesPtr();
	HPDF_UINT width = (HPDF_UINT)Param3.getIntValue();
	HPDF_UINT height = (HPDF_UINT)Param4.getIntValue();
	HPDF_UINT line_width = (HPDF_UINT)Param5.getIntValue();
	HPDF_BOOL black_is1 = (HPDF_BOOL)Param6.getIntValue();	
	HPDF_BOOL top_is_first = (HPDF_BOOL)Param7.getIntValue();		
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getBytesLength())
		{
			HPDF_Image image = HPDF_Image_LoadRaw1BitImageFromMem(pdf, buf, width, height, line_width, black_is1, top_is_first);
			if(image)
				_toHex(image, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

void PDF_LoadRawImageFromFile(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	
	HPDF_Doc pdf = _documentGet(Param1);

#if VERSIONMAC	
	CUTF8String u;
	Param2.copyPath(&u);
	const char *file_name = (const char *)u.c_str();
#else
	const wchar_t *file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
#endif	

	HPDF_UINT width = Param3.getIntValue();
	HPDF_UINT height = Param4.getIntValue();	
	HPDF_ColorSpace color_space = (HPDF_ColorSpace)Param5.getIntValue();
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getUTF16Length())
		{
			HPDF_Image image = HPDF_LoadRawImageFromFile(pdf, file_name, width, height, color_space);
			if(image)
				_toHex(image, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

void PDF_LoadRawImageFromMem(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_BLOB Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_LONGINT Param5;
	C_LONGINT Param6;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	Param6.fromParamAtIndex(pParams, 6);
	
	HPDF_Doc pdf = _documentGet(Param1);
	const HPDF_BYTE *buf = (const HPDF_BYTE *)Param2.getBytesPtr();
	HPDF_UINT width = Param3.getIntValue();
	HPDF_UINT height = Param4.getIntValue();	
	HPDF_ColorSpace color_space = (HPDF_ColorSpace)Param5.getIntValue();
	HPDF_UINT bits_per_component = Param6.getIntValue();
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getBytesLength())
		{
			HPDF_Image image = HPDF_LoadRawImageFromMem(pdf, buf, width, height, color_space, bits_per_component);
			if(image)
				_toHex(image, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark page
#pragma mark -

void PDF_GetCurrentPage(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		HPDF_Page page = HPDF_GetCurrentPage(pdf);
		if(page)
			_toHex(page, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_AddPage(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		HPDF_Page page = HPDF_AddPage(pdf);
		if(page)
			_toHex(page, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_InsertPage(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_Page page = (HPDF_Page)_fromHex(Param2);
	
	if(pdf)
	{
		HPDF_Page newPage = HPDF_InsertPage(pdf, page);
		if(newPage)
			_toHex(newPage, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_GetPageByIndex(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_UINT index = Param2.getIntValue();
	
	if(pdf)
	{
		HPDF_Page page = HPDF_GetPageByIndex(pdf, index);
		if(page)
			_toHex(page, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark font
#pragma mark -

void PDF_GetFont(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT Param3;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Doc pdf = _documentGet(Param1);
	CUTF8String u, v;
	Param2.copyUTF8String(&u);
	const char *font_name = (const char *)u.c_str();
	const char  *encoding_name = NULL;
	
	if(Param3.getUTF16Length())
	{
		Param3.copyUTF8String(&v);
		encoding_name = (const char *)v.c_str();
		
#if VERSIONMAC
		if(0 == strncasecmp(font_name, "MS-Mincyo", u.length() > 8 ? 8 : u.length()))
		{
			u = u.replace(7, 1, (const uint8_t *)"h");
			font_name = (const char *)u.c_str();
		}else if(0 == strncasecmp(font_name, "MS-PMincyo", u.length() > 9 ? 9 : u.length()))
		{
			u = u.replace(8, 1, (const uint8_t *)"h");
			font_name = (const char *)u.c_str();
		}
#else
		if(0 == strncasecmp(font_name, "MS-Mincho", u.length() > 8 ? 8 : u.length()))
		{
			u = u.replace(7, 1, (const uint8_t *)"y");
			font_name = (const char *)u.c_str();
		}else if(0 == strncasecmp(font_name, "MS-PMincho", u.length() > 9 ? 9 : u.length()))
		{
			u = u.replace(8, 1, (const uint8_t *)"y");
			font_name = (const char *)u.c_str();
		}
#endif
	}
	
	if(pdf)
	{
		HPDF_Font font = HPDF_GetFont(pdf, font_name, encoding_name);
		if(font)
			_toHex(font, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_LoadType1FontFromFile(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT Param3;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Doc pdf = _documentGet(Param1);
#if VERSIONMAC	
	CUTF8String u, v;
	Param2.copyPath(&u);
	Param3.copyPath(&v);	
	const char *afm_file_name = (const char *)u.c_str();
	const char *data_file_name = (const char *)v.c_str();
#else
	const wchar_t *afm_file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
	const wchar_t *data_file_name = 	(const wchar_t *)Param3.getUTF16StringPtr();
#endif	

	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
	
		if(Param2.getUTF16Length() && Param3.getUTF16Length())
		{
			CUTF8String f = CUTF8String((const uint8_t *)HPDF_LoadType1FontFromFile(pdf, afm_file_name, data_file_name));
			returnValue.setUTF8String(&f);
		}
	}
	
	returnValue.setReturn(pResult);
}

void PDF_GetTTFontDefFromFile(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT Param3;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	
	HPDF_Doc pdf = _documentGet(Param1);

#if VERSIONMAC	
	CUTF8String u;
	Param2.copyPath(&u);
	const char *file_name = (const char *)u.c_str();
#else
	const wchar_t *file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
#endif	

	HPDF_BOOL embedding = (HPDF_BOOL)Param3.getIntValue();	
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getUTF16Length())
		{
			HPDF_FontDef def = HPDF_GetTTFontDefFromFile(pdf, file_name, embedding);
			if(def)
				_toHex(def, returnValue);
		}
	}	
	
	returnValue.setReturn(pResult);
}

void PDF_LoadTTFontFromFile(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Doc pdf = _documentGet(Param1);

#if VERSIONMAC	
	CUTF8String u;
	Param2.copyPath(&u);
	const char *file_name = (const char *)u.c_str();
#else
	const wchar_t *file_name = 	(const wchar_t *)Param2.getUTF16StringPtr();
#endif	

	HPDF_UINT index = (HPDF_UINT)Param3.getIntValue();
	HPDF_BOOL embedding = (HPDF_BOOL)Param4.getIntValue();	
	
	if(pdf)
	{
		if(HPDF_GetError(pdf) != HPDF_OK)
			HPDF_ResetError(pdf);
		
		if(Param2.getUTF16Length())
		{
			CUTF8String v = CUTF8String((const uint8_t *)HPDF_LoadTTFontFromFile2(pdf, file_name, index, embedding));
			returnValue.setUTF8String(&v);
		}
	}		
	returnValue.setReturn(pResult);
}

void PDF_AddPageLabel(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT Param3;
	C_LONGINT Param4;
	C_TEXT Param5;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	Param5.fromParamAtIndex(pParams, 5);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_UINT page_num = (HPDF_UINT)Param2.getIntValue();
	HPDF_PageNumStyle style = (HPDF_PageNumStyle)Param3.getIntValue();
	HPDF_UINT first_page = (HPDF_UINT)Param4.getIntValue();	
	CUTF8String u;
	Param5.copyUTF8String(&u);
	const char *prefix = (const char *)u.c_str();
	
	if(pdf)
	{
		if(Param5.getUTF16Length())
			returnValue.setIntValue(HPDF_AddPageLabel(pdf, page_num, style, first_page, prefix));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_UseJPFonts(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_UseJPFonts(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_UseKRFonts(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_UseKRFonts(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_UseCNSFonts(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_UseCNSFonts(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_UseCNTFonts(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_UseCNTFonts(pdf));
	}
	
	returnValue.setReturn(pResult);
}

#pragma mark -
#pragma mark outline
#pragma mark -

void PDF_CreateOutline(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_TEXT Param3;
	C_TEXT Param4;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	Param3.fromParamAtIndex(pParams, 3);
	Param4.fromParamAtIndex(pParams, 4);
	
	HPDF_Doc pdf = _documentGet(Param1);
	HPDF_Outline parent = (HPDF_Outline)_fromHex(Param2);
	CUTF8String u;
	Param3.copyUTF8String(&u);
	const char *title = (const char *)u.c_str();
	HPDF_Encoder encoder = (HPDF_Encoder)_fromHex(Param4);
	
	if(pdf)
	{
		if(Param3.getUTF16Length())
		{
			HPDF_Outline outline = HPDF_CreateOutline(pdf, parent, title, encoder);
			if(outline)
				_toHex(outline, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

// ----------------------------------- Encoding -----------------------------------


void PDF_UseCNTEncodings(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_UseCNTEncodings(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_SetCurrentEncoder(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);

	CUTF8String u;
	Param2.copyUTF8String(&u);
	const char *encoding_name = (const char *)u.c_str();
	
	if(pdf)
	{
		if(Param2.getUTF16Length())
			returnValue.setIntValue(HPDF_SetCurrentEncoder(pdf, encoding_name));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_UseCNSEncodings(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_UseCNSEncodings(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_UseKREncodings(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_UseKREncodings(pdf));
	}
	
	returnValue.setReturn(pResult);
}

void PDF_GetEncoder(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;	
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	CUTF8String u;
	Param2.copyUTF8String(&u);
	const char *encoding_name = (const char *)u.c_str();
	
	if(pdf)
	{
		if(Param2.getUTF16Length())
		{
			HPDF_Encoder encoder = HPDF_GetEncoder(pdf, encoding_name);
			_toHex(encoder, returnValue);
		}
	}
	
	returnValue.setReturn(pResult);
}

void PDF_GetCurrentEncoder(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		HPDF_Encoder encoder = HPDF_GetCurrentEncoder(pdf);
		_toHex(encoder, returnValue);
	}
	
	returnValue.setReturn(pResult);
}

void PDF_UseJPEncodings(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	HPDF_Doc pdf = _documentGet(Param1);
	
	if(pdf)
	{
		returnValue.setIntValue(HPDF_UseJPEncodings(pdf));
	}
	
	returnValue.setReturn(pResult);
}
