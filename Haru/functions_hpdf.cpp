#include "functions_hpdf.h"

std::map<HPDF_Doc, PA_4DCharSet> _documents;

int globalEncoding = eVTC_ODBC_DEFAULT;

void _hpdf_err (HPDF_STATUS error_no,HPDF_STATUS detail_no, void *user_data){
	
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
	throw std::exception();
}

void _toHex(void *n, C_TEXT &hex){
	
	CUTF8String u;
	size_t len = (sizeof(size_t)*2);
	std::vector<uint8_t> buf(len+3);//on mac, we get the 0x prefix
	
	sprintf((char *)&buf[0], "%p", n);
#if VERSIONMAC
	u.append(&buf[2], len);		
#else	
	u.append(&buf[0], len);	
#endif	
	hex.setUTF8String(&u);	
}

void *_fromHex(C_TEXT &hex){
	
	void *p = NULL;
	CUTF8String u;
	hex.copyUTF8String(&u);
	
	sscanf((const char *)u.c_str(), "%p", &p);	
	
	return p;
}

HPDF_Doc _documentGet(C_TEXT &hex){
	
	HPDF_Doc d = (HPDF_Doc)_fromHex(hex);
	
	std::map<HPDF_Doc, PA_4DCharSet>::iterator pos = _documents.find(d);
	
	if(pos != _documents.end())
		return d;
	
	return 0;
}

void _documentDelete(C_TEXT &hex){
	
	HPDF_Doc d = (HPDF_Doc)_fromHex(hex);
		
	std::map<HPDF_Doc, PA_4DCharSet>::iterator pos = _documents.find(d);
	
	if(pos != _documents.end()){
		_documents.erase(pos);
		HPDF_Free(d);
	}
	
}

void _documentCreate(C_TEXT &hex){
	
	HPDF_Doc d = HPDF_New(_hpdf_err, NULL);
	
	if(d){
		_documents.insert(std::map<HPDF_Doc, PA_4DCharSet>::value_type(d, eVTC_StdLib_char));
		_toHex(d, hex);
	}
	
}

PA_4DCharSet _documentGetEncoding(C_TEXT &hex){
	
	HPDF_Doc d = (HPDF_Doc)_fromHex(hex);
	
	std::map<HPDF_Doc, PA_4DCharSet>::iterator pos = _documents.find(d);
	
	if(pos != _documents.end())
		return pos->second;
	
	return eVTC_StdLib_char;
}

void _documentSetEncoding(C_TEXT &hex, PA_4DCharSet encoding){
	
	HPDF_Doc d = (HPDF_Doc)_fromHex(hex);
	
	std::map<HPDF_Doc, PA_4DCharSet>::iterator pos = _documents.find(d);
	
	if(pos != _documents.end())
		pos->second = encoding;

}



void _convertFromUnicode(C_TEXT &fromStr, std::string &toStr)
{
	uint32_t size = ((uint32_t)fromStr.getUTF16Length() * 4) + sizeof(uint8_t);
	std::vector<uint8_t> buf(size);
	
	uint32_t len = PA_ConvertCharsetToCharset((char *)fromStr.getUTF16StringPtr(), 
							   (fromStr.getUTF16Length() * sizeof(PA_Unichar)), 
							   eVTC_UTF_16, 
							   (char *)&buf[0], 
							   size, 
							   (PA_4DCharSet)globalEncoding);
	
	toStr = std::string((const char *)&buf[0], len);
}

#pragma mark -
#pragma mark global
#pragma mark -

void PDF_Global_GetEncoding(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT returnValue;
	
	returnValue.setIntValue(globalEncoding);
	
	returnValue.setReturn(pResult);
}

void PDF_Global_SetEncoding(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_LONGINT Param1;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	globalEncoding = Param1.getIntValue();
	
}
