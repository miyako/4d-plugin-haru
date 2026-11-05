# 4d-plugin-haru

4D implementation of [libharu](https://github.com/libharu/libharu).

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
||<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

### Version

<img width="32" height="32" src="https://user-images.githubusercontent.com/1725068/73986501-15964580-4981-11ea-9ac1-73c5cee50aae.png"> <img src="https://user-images.githubusercontent.com/1725068/73987971-db2ea780-4984-11ea-8ada-e25fb9c3cf4e.png" width="32" height="32" />

[Releases](https://github.com/miyako/4d-plugin-haru/releases). See [examples](examples) for PDF output of the worked examples.

---

Haru creates PDF documents from 4D code. Each command is a thin wrapper around the libharu C function of (almost) the same name: `PDF_Page_ShowText` calls `HPDF_Page_ShowText`, and so on, so the [libharu documentation](https://github.com/libharu/libharu/wiki/API%3A-Page) describes the drawing model in more depth. You create a document with [PDF_New](#pdf_new), add pages, draw paths, text and images on them, save the result with [PDF_SaveToFile](#pdf_savetofile) (a file) or [PDF_SaveToStream](#pdf_savetostream) (a `Blob`), and release it with [PDF_Free](#pdf_free). Documents, pages, fonts, images, annotations, outlines and destinations are all passed around as **`Text` handles**; most other commands return a `Longint` libharu status.

The plugin bundles libharu 2.3.0 (RC2 headers) with libpng and zlib. On macOS these are built from source: libharu 2.3.0 and libpng 1.6.59, with the system zlib. See [Building from source](#building-from-source).

**Platforms:** macOS 11.5 or later (Apple silicon and Intel), Windows 64-bit.

---

## Command summary

### Document

| Command | Returns | Purpose |
|---|---|---|
| [PDF_AddPage](#pdf_addpage) | Text | Appends a new page to the document and returns its handle. |
| [PDF_AddPageLabel](#pdf_addpagelabel) | Longint | Adds a page-label range. |
| [PDF_CreateExtGState](#pdf_createextgstate) | Text | Creates an extended graphics state and returns its handle (use with [PDF_Page_SetExtGState](#pdf_page_setextgstate)). |
| [PDF_CreateOutline](#pdf_createoutline) | Text | Creates an outline (bookmark) entry and returns its handle. |
| [PDF_Free](#pdf_free) |  | Frees a document created with [PDF_New](#pdf_new), with all its pages, fonts, images and other objects. |
| [PDF_FreeDoc](#pdf_freedoc) |  | Discards the current document content (keeps loaded fonts and encodings). |
| [PDF_FreeDocAll](#pdf_freedocall) |  | Discards the current document content and every loaded font and encoding. |
| [PDF_GetCurrentEncoder](#pdf_getcurrentencoder) | Text | Returns the handle of the document's current encoder. |
| [PDF_GetCurrentPage](#pdf_getcurrentpage) | Text | Returns the handle of the current page. |
| [PDF_GetEncoder](#pdf_getencoder) | Text | Returns the handle of an encoder by name. |
| [PDF_GetFont](#pdf_getfont) | Text | Returns a font handle for a built-in or loaded font name and an optional encoding. |
| [PDF_GetInfoAttr](#pdf_getinfoattr) | Text | Returns a text field of the document information dictionary. |
| [PDF_GetPageByIndex](#pdf_getpagebyindex) | Text | Returns the handle of a page by index. |
| [PDF_GetPageLayout](#pdf_getpagelayout) | Longint | Returns the page layout (`HPDF_PAGE_LAYOUT_*`). |
| [PDF_GetPageMode](#pdf_getpagemode) | Longint | Returns the page mode (`HPDF_PAGE_MODE_*`). |
| [PDF_GetTTFontDefFromFile](#pdf_getttfontdeffromfile) | Text | Loads a TrueType font definition and returns its handle. |
| [PDF_GetViewerPreference](#pdf_getviewerpreference) | Longint | Returns the viewer preference flags. |
| [PDF_HasDoc](#pdf_hasdoc) | Longint | Returns 1 if the document object currently holds a document, else 0. |
| [PDF_InsertPage](#pdf_insertpage) | Text | Inserts a new page before an existing page and returns the new page handle. |
| [PDF_LoadJpegImageFromFile](#pdf_loadjpegimagefromfile) | Text | Loads a JPEG file and returns an image handle. |
| [PDF_LoadJpegImageFromMem](#pdf_loadjpegimagefrommem) | Text | Loads JPEG data from a BLOB and returns an image handle. |
| [PDF_LoadPngImageFromFile](#pdf_loadpngimagefromfile) | Text | Loads a PNG file and returns an image handle. |
| [PDF_LoadPngImageFromMem](#pdf_loadpngimagefrommem) | Text | Loads PNG data from a BLOB and returns an image handle. |
| [PDF_LoadRaw1BitImageFromMem](#pdf_loadraw1bitimagefrommem) | Text | Loads 1-bit monochrome pixel data from a BLOB and returns an image handle. |
| [PDF_LoadRawImageFromFile](#pdf_loadrawimagefromfile) | Text | Loads uncompressed pixel data from a file and returns an image handle. |
| [PDF_LoadRawImageFromMem](#pdf_loadrawimagefrommem) | Text | Loads uncompressed pixel data from a BLOB and returns an image handle. |
| [PDF_LoadTTFontFromFile](#pdf_loadttfontfromfile) | Text | Loads a TrueType font (or one font from a `.ttc` collection) and returns its font name. |
| [PDF_LoadType1FontFromFile](#pdf_loadtype1fontfromfile) | Text | Loads a Type 1 font and returns its font name (pass it to [PDF_GetFont](#pdf_getfont)). |
| [PDF_LoadU3DFromFile](#pdf_loadu3dfromfile) | Text | Loads a U3D 3D-model file and returns its handle. |
| [PDF_New](#pdf_new) | Text | Creates a new PDF document object and returns its handle. |
| [PDF_NewDoc](#pdf_newdoc) | Longint | Discards the current document content and starts a new, empty document in the same document object. |
| [PDF_ResetError](#pdf_reseterror) |  | Clears the error state of the document. |
| [PDF_SaveToFile](#pdf_savetofile) | Longint | Writes the document to a file. |
| [PDF_SaveToStream](#pdf_savetostream) | Longint | Writes the document into a BLOB. |
| [PDF_SetCompressionMode](#pdf_setcompressionmode) | Longint | Sets which streams are compressed. |
| [PDF_SetCurrentEncoder](#pdf_setcurrentencoder) | Longint | Sets the document's current encoder by name. |
| [PDF_SetEncryptionMode](#pdf_setencryptionmode) | Longint | Sets the encryption revision and key length. |
| [PDF_SetInfoAttr](#pdf_setinfoattr) | Longint | Sets a text field of the document information dictionary. |
| [PDF_SetInfoDateAttr](#pdf_setinfodateattr) | Longint | Sets the creation or modification date of the document. |
| [PDF_SetOpenAction](#pdf_setopenaction) | Longint | Sets the destination shown when the document is opened. |
| [PDF_SetPageLayout](#pdf_setpagelayout) | Longint | Sets how pages are laid out when the document is opened. |
| [PDF_SetPageMode](#pdf_setpagemode) | Longint | Sets what the viewer shows when the document is opened. |
| [PDF_SetPagesConfiguration](#pdf_setpagesconfiguration) | Longint | Sets how many pages a page-tree node holds (libharu `HPDF_SetPagesConfiguration`); only needed for very large documents. |
| [PDF_SetPassword](#pdf_setpassword) | Longint | Sets the owner and user passwords and turns on encryption. |
| [PDF_SetPermission](#pdf_setpermission) | Longint | Sets the permission flags of an encrypted document. |
| [PDF_SetViewerPreference](#pdf_setviewerpreference) | Longint | Sets the viewer preference flags. |
| [PDF_UseCNSEncodings](#pdf_usecnsencodings) | Longint | Enables the Simplified Chinese encodings. |
| [PDF_UseCNSFonts](#pdf_usecnsfonts) | Longint | Enables the built-in Simplified Chinese fonts. |
| [PDF_UseCNTEncodings](#pdf_usecntencodings) | Longint | Enables the Traditional Chinese encodings. |
| [PDF_UseCNTFonts](#pdf_usecntfonts) | Longint | Enables the built-in Traditional Chinese fonts. |
| [PDF_UseJPEncodings](#pdf_usejpencodings) | Longint | Enables the Japanese encodings (`90ms-RKSJ-H`, `EUC-H`, ...). |
| [PDF_UseJPFonts](#pdf_usejpfonts) | Longint | Enables the built-in Japanese fonts (`MS-Mincho`, `MS-Gothic`, ...). |
| [PDF_UseKREncodings](#pdf_usekrencodings) | Longint | Enables the Korean encodings. |
| [PDF_UseKRFonts](#pdf_usekrfonts) | Longint | Enables the built-in Korean fonts. |

### Page

| Command | Returns | Purpose |
|---|---|---|
| [PDF_Page_Arc](#pdf_page_arc) | Longint | Appends an arc to the current path. |
| [PDF_Page_BeginText](#pdf_page_begintext) | Longint | Begins a text object. |
| [PDF_Page_Circle](#pdf_page_circle) | Longint | Appends a circle to the current path. |
| [PDF_Page_Clip](#pdf_page_clip) | Longint | Intersects the clipping path with the current path (nonzero winding rule). |
| [PDF_Page_ClosePath](#pdf_page_closepath) | Longint | Closes the current subpath. |
| [PDF_Page_ClosePathEofillStroke](#pdf_page_closepatheofillstroke) | Longint | Closes, fills and strokes the current path (even-odd rule). |
| [PDF_Page_ClosePathFillStroke](#pdf_page_closepathfillstroke) | Longint | Closes, fills and strokes the current path (nonzero winding rule). |
| [PDF_Page_ClosePathStroke](#pdf_page_closepathstroke) | Longint | Closes and strokes the current path. |
| [PDF_Page_Concat](#pdf_page_concat) | Longint | Concatenates a transformation matrix to the current one. |
| [PDF_Page_CreateCircleAnnot](#pdf_page_createcircleannot) | Text | Creates a circle annotation and returns its handle. |
| [PDF_Page_CreateDestination](#pdf_page_createdestination) | Text | Creates a destination that points to this page and returns its handle. |
| [PDF_Page_CreateFreeTextAnnot](#pdf_page_createfreetextannot) | Text | Creates a free-text annotation and returns its handle. |
| [PDF_Page_CreateHighlightAnnot](#pdf_page_createhighlightannot) | Text | Creates a highlight annotation and returns its handle. |
| [PDF_Page_CreateLineAnnot](#pdf_page_createlineannot) | Text | Creates a line annotation and returns its handle. |
| [PDF_Page_CreateLinkAnnot](#pdf_page_createlinkannot) | Text | Creates a link annotation that jumps to a destination in the document. |
| [PDF_Page_CreatePopupAnnot](#pdf_page_createpopupannot) | Text | Creates a popup annotation and returns its handle. |
| [PDF_Page_CreateProjectionAnnot](#pdf_page_createprojectionannot) | Text | Creates a projection annotation and returns its handle. |
| [PDF_Page_CreateSquareAnnot](#pdf_page_createsquareannot) | Text | Creates a square annotation and returns its handle. |
| [PDF_Page_CreateSquigglyAnnot](#pdf_page_createsquigglyannot) | Text | Creates a squiggly-underline annotation and returns its handle. |
| [PDF_Page_CreateStampAnnot](#pdf_page_createstampannot) | Text | Creates a stamp annotation and returns its handle. |
| [PDF_Page_CreateStrikeOutAnnot](#pdf_page_createstrikeoutannot) | Text | Creates a strike-out annotation and returns its handle. |
| [PDF_Page_CreateTextAnnot](#pdf_page_createtextannot) | Text | Creates a text (sticky note) annotation and returns its handle. |
| [PDF_Page_CreateTextMarkupAnnot](#pdf_page_createtextmarkupannot) | Text | Creates a text-markup annotation of a given subtype and returns its handle. |
| [PDF_Page_CreateUnderlineAnnot](#pdf_page_createunderlineannot) | Text | Creates an underline annotation and returns its handle. |
| [PDF_Page_CreateURILinkAnnot](#pdf_page_createurilinkannot) | Text | Creates a link annotation that opens a URI and returns its handle. |
| [PDF_Page_CurveTo](#pdf_page_curveto) | Longint | Appends a Bezier curve with two control points. |
| [PDF_Page_CurveTo2](#pdf_page_curveto2) | Longint | Appends a Bezier curve whose first control point is the current point. |
| [PDF_Page_CurveTo3](#pdf_page_curveto3) | Longint | Appends a Bezier curve whose second control point is the end point. |
| [PDF_Page_DrawImage](#pdf_page_drawimage) | Longint | Draws an image. |
| [PDF_Page_Ellipse](#pdf_page_ellipse) | Longint | Appends an ellipse to the current path. |
| [PDF_Page_EndPath](#pdf_page_endpath) | Longint | Ends the current path without painting it (used after a clip). |
| [PDF_Page_EndText](#pdf_page_endtext) | Longint | Ends a text object. |
| [PDF_Page_Eoclip](#pdf_page_eoclip) | Longint | Intersects the clipping path with the current path (even-odd rule). |
| [PDF_Page_Eofill](#pdf_page_eofill) | Longint | Fills the current path (even-odd rule). |
| [PDF_Page_EofillStroke](#pdf_page_eofillstroke) | Longint | Fills and strokes the current path (even-odd rule). |
| [PDF_Page_Fill](#pdf_page_fill) | Longint | Fills the current path (nonzero winding rule). |
| [PDF_Page_FillStroke](#pdf_page_fillstroke) | Longint | Fills and strokes the current path (nonzero winding rule). |
| [PDF_Page_GetCharSpace](#pdf_page_getcharspace) | Real | Returns the character spacing. |
| [PDF_Page_GetCMYKFill](#pdf_page_getcmykfill) |  | Returns the fill color in CMYK. |
| [PDF_Page_GetCMYKStroke](#pdf_page_getcmykstroke) |  | Returns the stroke color in CMYK. |
| [PDF_Page_GetCurrentFont](#pdf_page_getcurrentfont) | Text | Returns the handle of the current font, or `""` if none is set. |
| [PDF_Page_GetCurrentFontSize](#pdf_page_getcurrentfontsize) | Real | Returns the current font size. |
| [PDF_Page_GetCurrentPos](#pdf_page_getcurrentpos) |  | Returns the current point of the path. |
| [PDF_Page_GetCurrentTextPos](#pdf_page_getcurrenttextpos) |  | Returns the current text position. |
| [PDF_Page_GetDash](#pdf_page_getdash) | Longint | Returns the dash pattern. |
| [PDF_Page_GetFillingColorSpace](#pdf_page_getfillingcolorspace) | Longint | Returns the filling color space (libharu `HPDF_ColorSpace`). |
| [PDF_Page_GetFlat](#pdf_page_getflat) | Real | Returns the flatness. |
| [PDF_Page_GetGMode](#pdf_page_getgmode) | Longint | Returns the current graphics mode (page description, path object or text object) as a libharu `HPDF_GMODE_*` bit value. |
| [PDF_Page_GetGrayFill](#pdf_page_getgrayfill) | Real | Returns the fill gray level. |
| [PDF_Page_GetGrayStroke](#pdf_page_getgraystroke) | Real | Returns the stroke gray level. |
| [PDF_Page_GetGStateDepth](#pdf_page_getgstatedepth) | Longint | Returns how many graphics states are saved. |
| [PDF_Page_GetHeight](#pdf_page_getheight) | Real | Returns the page height in points. |
| [PDF_Page_GetHorizontalScalling](#pdf_page_gethorizontalscalling) | Real | Returns the horizontal text scaling. |
| [PDF_Page_GetLineCap](#pdf_page_getlinecap) | Longint | Returns the line cap style. |
| [PDF_Page_GetLineJoin](#pdf_page_getlinejoin) | Longint | Returns the line join style. |
| [PDF_Page_GetLineWidth](#pdf_page_getlinewidth) | Real | Returns the line width. |
| [PDF_Page_GetMiterLimit](#pdf_page_getmiterlimit) | Real | Returns the miter limit. |
| [PDF_Page_GetRGBFill](#pdf_page_getrgbfill) |  | Returns the fill color in RGB. |
| [PDF_Page_GetRGBStroke](#pdf_page_getrgbstroke) |  | Returns the stroke color in RGB. |
| [PDF_Page_GetStrokingColorSpace](#pdf_page_getstrokingcolorspace) | Longint | Returns the stroking color space (libharu `HPDF_ColorSpace`). |
| [PDF_Page_GetTextLeading](#pdf_page_gettextleading) | Real | Returns the text leading. |
| [PDF_Page_GetTextMatrix](#pdf_page_gettextmatrix) |  | Returns the current text matrix. |
| [PDF_Page_GetTextRenderingMode](#pdf_page_gettextrenderingmode) | Longint | Returns the text rendering mode. |
| [PDF_Page_GetTextRise](#pdf_page_gettextrise) | Real | Returns the text rise. |
| [PDF_Page_GetTransMatrix](#pdf_page_gettransmatrix) |  | Returns the current transformation matrix. |
| [PDF_Page_GetWidth](#pdf_page_getwidth) | Real | Returns the page width in points. |
| [PDF_Page_GetWordSpace](#pdf_page_getwordspace) | Real | Returns the word spacing. |
| [PDF_Page_GRestore](#pdf_page_grestore) | Longint | Restores the graphics state saved by [PDF_Page_GSave](#pdf_page_gsave). |
| [PDF_Page_GSave](#pdf_page_gsave) | Longint | Saves the graphics state. |
| [PDF_Page_LineTo](#pdf_page_lineto) | Longint | Appends a straight line to the current path. |
| [PDF_Page_MeasureText](#pdf_page_measuretext) | Longint | Returns how many bytes of a text fit in a width. |
| [PDF_Page_MoveTextPos](#pdf_page_movetextpos) | Longint | Moves the text position. |
| [PDF_Page_MoveTo](#pdf_page_moveto) | Longint | Starts a new subpath at a point. |
| [PDF_Page_MoveToNextLine](#pdf_page_movetonextline) | Longint | Moves the text position to the start of the next line. |
| [PDF_Page_Rectangle](#pdf_page_rectangle) | Longint | Appends a rectangle to the current path. |
| [PDF_Page_SetCharSpace](#pdf_page_setcharspace) | Longint | Sets the character spacing. |
| [PDF_Page_SetCMYKFill](#pdf_page_setcmykfill) | Longint | Sets the fill color in CMYK. |
| [PDF_Page_SetCMYKStroke](#pdf_page_setcmykstroke) | Longint | Sets the stroke color in CMYK. |
| [PDF_Page_SetDash](#pdf_page_setdash) | Longint | Sets the dash pattern for lines. |
| [PDF_Page_SetExtGState](#pdf_page_setextgstate) | Longint | Applies an extended graphics state to the page. |
| [PDF_Page_SetFontAndSize](#pdf_page_setfontandsize) | Longint | Sets the font and size for text. |
| [PDF_Page_SetGrayFill](#pdf_page_setgrayfill) | Longint | Sets the fill color in gray. |
| [PDF_Page_SetGrayStroke](#pdf_page_setgraystroke) | Longint | Sets the stroke color in gray. |
| [PDF_Page_SetHeight](#pdf_page_setheight) | Longint | Sets the page height. |
| [PDF_Page_SetHorizontalScalling](#pdf_page_sethorizontalscalling) | Longint | Sets the horizontal text scaling. |
| [PDF_Page_SetLineCap](#pdf_page_setlinecap) | Longint | Sets the line cap style. |
| [PDF_Page_SetLineJoin](#pdf_page_setlinejoin) | Longint | Sets the line join style. |
| [PDF_Page_SetLineWidth](#pdf_page_setlinewidth) | Longint | Sets the line width. |
| [PDF_Page_SetMiterLimit](#pdf_page_setmiterlimit) | Longint | Sets the miter limit. |
| [PDF_Page_SetRGBFill](#pdf_page_setrgbfill) | Longint | Sets the fill color in RGB. |
| [PDF_Page_SetRGBStroke](#pdf_page_setrgbstroke) | Longint | Sets the stroke color in RGB. |
| [PDF_Page_SetRotate](#pdf_page_setrotate) | Longint | Sets the page rotation. |
| [PDF_Page_SetSize](#pdf_page_setsize) | Longint | Sets the page to a standard size. |
| [PDF_Page_SetSlideShow](#pdf_page_setslideshow) |  | Sets the page transition for presentation mode. |
| [PDF_Page_SetTextLeading](#pdf_page_settextleading) | Longint | Sets the text leading (line spacing). |
| [PDF_Page_SetTextMatrix](#pdf_page_settextmatrix) | Longint | Sets the text matrix. |
| [PDF_Page_SetTextRenderingMode](#pdf_page_settextrenderingmode) | Longint | Sets the text rendering mode. |
| [PDF_Page_SetTextRise](#pdf_page_settextrise) | Longint | Sets the text rise (superscript/subscript offset). |
| [PDF_Page_SetWidth](#pdf_page_setwidth) | Longint | Sets the page width. |
| [PDF_Page_SetWordSpace](#pdf_page_setwordspace) | Longint | Sets the word spacing. |
| [PDF_Page_SetZoom](#pdf_page_setzoom) | Longint | Sets the page zoom. |
| [PDF_Page_ShowText](#pdf_page_showtext) | Longint | Draws text at the current text position. |
| [PDF_Page_ShowTextNextLine](#pdf_page_showtextnextline) | Longint | Moves to the next line and draws text. |
| [PDF_Page_ShowTextNextLineEx](#pdf_page_showtextnextlineex) | Longint | Sets word and character spacing, moves to the next line and draws text. |
| [PDF_Page_Stroke](#pdf_page_stroke) | Longint | Strokes the current path. |
| [PDF_Page_TextOut](#pdf_page_textout) | Longint | Draws text at a position (inside a text object). |
| [PDF_Page_TextRect](#pdf_page_textrect) | Longint | Draws text inside a rectangle, wrapping lines. |
| [PDF_Page_TextWidth](#pdf_page_textwidth) | Real | Returns the width of a text in the current font and size. |

### Font

| Command | Returns | Purpose |
|---|---|---|
| [PDF_Font_GetAscent](#pdf_font_getascent) | Longint | Returns the font ascent. |
| [PDF_Font_GetBBox](#pdf_font_getbbox) |  | Returns the font bounding box. |
| [PDF_Font_GetCapHeight](#pdf_font_getcapheight) | Longint | Returns the font cap height. |
| [PDF_Font_GetDescent](#pdf_font_getdescent) | Longint | Returns the font descent. |
| [PDF_Font_GetEncodingName](#pdf_font_getencodingname) | Text | Returns the encoding name of a font. |
| [PDF_Font_GetFontName](#pdf_font_getfontname) | Text | Returns the name of a font. |
| [PDF_Font_GetUnicodeWidth](#pdf_font_getunicodewidth) | Longint | Returns the width of one Unicode character in the font (in 1/1000 em). |
| [PDF_Font_GetXHeight](#pdf_font_getxheight) | Longint | Returns the font x-height. |
| [PDF_Font_MeasureText](#pdf_font_measuretext) | Longint | Returns how many bytes of a text fit in a width. |
| [PDF_Font_TextWidth](#pdf_font_textwidth) |  | Measures a text in the font. |

### Image

| Command | Returns | Purpose |
|---|---|---|
| [PDF_Image_AddSMask](#pdf_image_addsmask) | Longint | Adds a soft mask (alpha) image. |
| [PDF_Image_GetBitsPerComponent](#pdf_image_getbitspercomponent) | Longint | Returns the bits per color component. |
| [PDF_Image_GetColorSpace](#pdf_image_getcolorspace) | Text | Returns the color-space name of the image (`"DeviceRGB"`, ...). |
| [PDF_Image_GetHeight](#pdf_image_getheight) | Longint | Returns the image height in pixels. |
| [PDF_Image_GetSize](#pdf_image_getsize) | Longint | Returns the image size in pixels. |
| [PDF_Image_GetWidth](#pdf_image_getwidth) | Longint | Returns the image width in pixels. |
| [PDF_Image_SetColorMask](#pdf_image_setcolormask) | Longint | Makes a color range of the image transparent. |
| [PDF_Image_SetMaskImage](#pdf_image_setmaskimage) | Longint | Uses another image as a stencil mask. |

### Annotation

| Command | Returns | Purpose |
|---|---|---|
| [PDF_Annot_SetCMYKColor](#pdf_annot_setcmykcolor) | Longint | Sets the color of an annotation in CMYK. |
| [PDF_Annot_SetGrayColor](#pdf_annot_setgraycolor) | Longint | Sets the color of an annotation in gray. |
| [PDF_Annot_SetNoColor](#pdf_annot_setnocolor) | Longint | Removes the color of an annotation. |
| [PDF_Annot_SetRGBColor](#pdf_annot_setrgbcolor) | Longint | Sets the color of an annotation in RGB. |
| [PDF_Annotation_SetBorderStyle](#pdf_annotation_setborderstyle) | Longint | Sets the border style of an annotation. |
| [PDF_FreeAnnot_Set2PointCallout](#pdf_freeannot_set2pointcallout) | Longint | Sets a two-point callout line on a free-text annotation. |
| [PDF_FreeAnnot_Set3PointCallout](#pdf_freeannot_set3pointcallout) | Longint | Sets a three-point callout line on a free-text annotation. |
| [PDF_FreeAnnot_SetDefaultStyle](#pdf_freeannot_setdefaultstyle) | Longint | Sets the default style string of a free-text annotation. |
| [PDF_FreeAnnot_SetEndingStyle](#pdf_freeannot_setendingstyle) | Longint | Sets the line-ending styles of a free-text annotation. |
| [PDF_LineAnnot_SetCaption](#pdf_lineannot_setcaption) | Longint | Sets the caption of a line annotation. |
| [PDF_LineAnnot_SetLeader](#pdf_lineannot_setleader) | Longint | Sets the leader lines of a line annotation. |
| [PDF_LineAnnot_SetPosition](#pdf_lineannot_setposition) | Longint | Sets the end points and ending styles of a line annotation. |
| [PDF_LinkAnnot_SetBorderStyle](#pdf_linkannot_setborderstyle) | Longint | Sets the border of a link annotation. |
| [PDF_LinkAnnot_SetHighlightMode](#pdf_linkannot_sethighlightmode) | Longint | Sets how a link annotation is highlighted when clicked. |
| [PDF_MarkupAnnot_SetAlpha](#pdf_markupannot_setalpha) | Longint | Sets the opacity of a markup annotation. |
| [PDF_MarkupAnnot_SetCloudEffect](#pdf_markupannot_setcloudeffect) | Longint | Sets the cloud border effect of a markup annotation. |
| [PDF_MarkupAnnot_SetCMYKColor](#pdf_markupannot_setcmykcolor) | Longint | Sets the interior color of a markup annotation in CMYK. |
| [PDF_MarkupAnnot_SetDate](#pdf_markupannot_setdate) | Longint | Sets the creation date of a markup annotation. |
| [PDF_MarkupAnnot_SetGrayColor](#pdf_markupannot_setgraycolor) | Longint | Sets the interior color of a markup annotation in gray. |
| [PDF_MarkupAnnot_SetIntent](#pdf_markupannot_setintent) | Longint | Sets the intent of a markup annotation. |
| [PDF_MarkupAnnot_SetNoColor](#pdf_markupannot_setnocolor) | Longint | Makes the interior of a markup annotation transparent. |
| [PDF_MarkupAnnot_SetPopup](#pdf_markupannot_setpopup) | Longint | Attaches a popup annotation to a markup annotation. |
| [PDF_MarkupAnnot_SetQuadPoints](#pdf_markupannot_setquadpoints) | Longint | Sets the quadrilateral of a text-markup annotation (highlight, underline, ...). |
| [PDF_MarkupAnnot_SetRectDiff](#pdf_markupannot_setrectdiff) | Longint | Sets the inner rectangle offsets of a markup annotation. |
| [PDF_MarkupAnnot_SetRGBColor](#pdf_markupannot_setrgbcolor) | Longint | Sets the interior color of a markup annotation in RGB. |
| [PDF_MarkupAnnot_SetSubject](#pdf_markupannot_setsubject) | Longint | Sets the subject of a markup annotation. |
| [PDF_MarkupAnnot_SetTitle](#pdf_markupannot_settitle) | Longint | Sets the title (author) of a markup annotation. |
| [PDF_PopupAnnot_SetOpened](#pdf_popupannot_setopened) | Longint | Sets whether a popup annotation is initially open. |
| [PDF_TextAnnot_SetIcon](#pdf_textannot_seticon) | Longint | Sets the icon of a text annotation. |
| [PDF_TextAnnot_SetOpened](#pdf_textannot_setopened) | Longint | Sets whether a text annotation is initially open. |

### Outline

| Command | Returns | Purpose |
|---|---|---|
| [PDF_Outline_SetDestination](#pdf_outline_setdestination) | Longint | Sets the destination an outline entry jumps to. |
| [PDF_Outline_SetOpened](#pdf_outline_setopened) | Longint | Sets whether an outline entry is initially expanded. |

### Destination

| Command | Returns | Purpose |
|---|---|---|
| [PDF_Destination_SetFit](#pdf_destination_setfit) | Longint | Fits the whole page in the window. |
| [PDF_Destination_SetFitB](#pdf_destination_setfitb) | Longint | Fits the page bounding box in the window. |
| [PDF_Destination_SetFitBH](#pdf_destination_setfitbh) | Longint | Fits the bounding-box width, with the given top coordinate at the top. |
| [PDF_Destination_SetFitBV](#pdf_destination_setfitbv) | Longint | Fits the bounding-box height, with the given left coordinate at the left. |
| [PDF_Destination_SetFitH](#pdf_destination_setfith) | Longint | Fits the page width, with the given top coordinate at the top of the window. |
| [PDF_Destination_SetFitR](#pdf_destination_setfitr) | Longint | Fits a rectangle in the window. |
| [PDF_Destination_SetFitV](#pdf_destination_setfitv) | Longint | Fits the page height, with the given left coordinate at the left of the window. |
| [PDF_Destination_SetXYZ](#pdf_destination_setxyz) | Longint | Shows the page at a position and zoom. |

### Extended Graphics State

| Command | Returns | Purpose |
|---|---|---|
| [PDF_ExtGState_SetAlphaFill](#pdf_extgstate_setalphafill) | Longint | Sets the fill opacity of an extended graphics state. |
| [PDF_ExtGState_SetAlphaStroke](#pdf_extgstate_setalphastroke) | Longint | Sets the stroke opacity of an extended graphics state. |
| [PDF_ExtGState_SetBlendMode](#pdf_extgstate_setblendmode) | Longint | Sets the blend mode of an extended graphics state. |

### Global

| Command | Returns | Purpose |
|---|---|---|
| [PDF_Global_GetEncoding](#pdf_global_getencoding) | Longint | Returns the character set set by [PDF_Global_SetEncoding](#pdf_global_setencoding) (default `HPDF_DEFAULT`, -2). |
| [PDF_Global_SetEncoding](#pdf_global_setencoding) |  | Sets the character set the plugin converts drawn text to, for every document in the 4D session. |

---

## Requirements & platform notes

- **Handles are `Text`.** Store them in `Text` variables and pass them back unchanged. Only the document handle is checked: the plugin keeps a list of documents created by [PDF_New](#pdf_new) and ignores a document handle it does not know. **Every other handle (page, font, image, annotation, outline, destination, encoder, graphics state) is used as a raw memory address.** A handle from a freed document, a handle of the wrong kind, or a mistyped string can crash 4D. Never use a handle after [PDF_Free](#pdf_free) of its document.
- **Always call [PDF_Free](#pdf_free)** for every [PDF_New](#pdf_new). Documents are not freed when the process ends.
- **Trailing parameters.** The plugin reads every declared parameter; the sample code omits trailing ones (`PDF_GetFont ($pdf;"Helvetica")`, `PDF_CreateOutline ($pdf;$root;$title)`), which then read as empty values (inferred from the samples). To be explicit, pass `""` for an unused handle or name (for example `parent` or `encoder` of [PDF_CreateOutline](#pdf_createoutline)).
- **Text encoding.** Text drawn on a page or put in an annotation (`PDF_Page_ShowText`, `PDF_Page_TextOut`, `PDF_Page_TextRect`, `PDF_Page_Create...Annot`, `PDF_Page_TextWidth`, `PDF_Page_MeasureText`) is converted from 4D Unicode to the character set set by [PDF_Global_SetEncoding](#pdf_global_setencoding). That character set must match the encoding of the font in use: for Japanese, `PDF_Global_SetEncoding (HPDF_SHIFT_JIS)` with a font loaded as `PDF_GetFont ($pdf;"MS-Mincho";"90ms-RKSJ-H")`. The default is `HPDF_DEFAULT` (-2); what 4D converts to for that value is not defined by the plugin, so set it explicitly when you draw non-ASCII text. All other text parameters (titles, info fields, passwords, font and encoding names, URIs, outline titles, `PDF_Font_TextWidth`/`PDF_Font_MeasureText` text) are passed as UTF-8.
- **The encoding setting is global**: one value for all documents and all processes.
- **File paths.** **On macOS**, pass a 4D system path (as returned by `System folder` or `Get 4D folder`); the plugin converts it to a POSIX path. **On Windows**, the path is passed to libharu as UTF-16. The original sample comments note that on Windows the path could only contain characters of the system ANSI code page; that has not been re-checked.
- **Coordinates** are PDF points (1/72 inch) with the origin at the bottom-left of the page, as in libharu.
- **Preemptive processes.** Every command is declared thread-safe. Different processes may each work on their own document. Do not use the same document from two processes at the same time, and note that [PDF_Global_SetEncoding](#pdf_global_setencoding) affects all processes. The list of documents is protected by a lock **from this release on**; before, creating or freeing documents in two preemptive processes at once could corrupt it.
- **Constants.** The plugin installs a constant theme `Haru` with libharu values (`HPDF_PAGE_SIZE_A4`, `HPDF_COMP_ALL`, `HPDF_TALIGN_LEFT`, ...); see [Constants](#constants).

---

## Document commands

Create, configure, save and free documents; load fonts and images; create pages and outlines.

---

## PDF_AddPage

### Syntax

```4d
$result:=PDF_AddPage ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Appends a new page to the document and returns its handle.

Wraps libharu `HPDF_AddPage`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_AddPageLabel

### Syntax

```4d
$result:=PDF_AddPageLabel ( pdf ; page_num ; style ; first_page ; prefix )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `page_num` | Longint | First page of the range (libharu counts from 0). |
| `style` | Longint | An `HPDF_NUM_STYLE_*` constant. |
| `first_page` | Longint | Number shown on the first page of the range. |
| `prefix` | Text | Label prefix (UTF-8). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Adds a page-label range.

**The prefix must not be empty**: with `""` the command does nothing and returns `0`.

Wraps libharu `HPDF_AddPageLabel`.

---

## PDF_CreateExtGState

### Syntax

```4d
$result:=PDF_CreateExtGState ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates an extended graphics state and returns its handle (use with [PDF_Page_SetExtGState](#pdf_page_setextgstate)).

Wraps libharu `HPDF_CreateExtGState`.

---

## PDF_CreateOutline

### Syntax

```4d
$result:=PDF_CreateOutline ( pdf ; parent ; title ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `parent` | Text | Parent outline handle, or `""` for a top-level entry. |
| `title` | Text | Title, passed as UTF-8. |
| `encoder` | Text | Encoder handle, or `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates an outline (bookmark) entry and returns its handle.

An empty title returns `""`. The title bytes are UTF-8 while libharu reads them in the given encoder (PDFDocEncoding when none), so non-ASCII titles may display wrongly (inferred from the code, not tested).

Wraps libharu `HPDF_CreateOutline`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_Free

### Syntax

```4d
PDF_Free ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle. |
| Result | | None. |

### Description

Frees a document created with [PDF_New](#pdf_new), with all its pages, fonts, images and other objects.

After this call every handle that came from the document is invalid. An unknown handle is ignored.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_FreeDoc

### Syntax

```4d
PDF_FreeDoc ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | | None. |

### Description

Discards the current document content (keeps loaded fonts and encodings).

Wraps libharu `HPDF_FreeDoc`.

---

## PDF_FreeDocAll

### Syntax

```4d
PDF_FreeDocAll ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | | None. |

### Description

Discards the current document content and every loaded font and encoding.

Wraps libharu `HPDF_FreeDocAll`.

---

## PDF_GetCurrentEncoder

### Syntax

```4d
$result:=PDF_GetCurrentEncoder ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Returns the handle of the document's current encoder.

Wraps libharu `HPDF_GetCurrentEncoder`.

---

## PDF_GetCurrentPage

### Syntax

```4d
$result:=PDF_GetCurrentPage ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Returns the handle of the current page.

Wraps libharu `HPDF_GetCurrentPage`.

---

## PDF_GetEncoder

### Syntax

```4d
$result:=PDF_GetEncoder ( pdf ; encoding_name )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `encoding_name` | Text | Encoding name. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Returns the handle of an encoder by name.

Wraps libharu `HPDF_GetEncoder`.

---

## PDF_GetFont

### Syntax

```4d
$result:=PDF_GetFont ( pdf ; font_name ; encoding_name )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `font_name` | Text | Font name, e.g. `"Helvetica"`, `"MS-Mincho"`, or a name returned by a load command. |
| `encoding_name` | Text | Encoding name, e.g. `"90ms-RKSJ-H"`. Pass `""` for the font's default. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Returns a font handle for a built-in or loaded font name and an optional encoding.

When an encoding is given, the Japanese names `MS-Mincho`/`MS-PMincho` and `MS-Mincyo`/`MS-PMincyo` are treated as the same font: the plugin rewrites the name to the spelling libharu expects on each platform (`h` on macOS, `y` on Windows).

Wraps libharu `HPDF_GetFont`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_GetInfoAttr

### Syntax

```4d
$result:=PDF_GetInfoAttr ( pdf ; type )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `type` | Longint | An `HPDF_INFO_*` constant. |
| Result | Text | Field value, `""` if unset. |

### Description

Returns a text field of the document information dictionary.

Returns `""` for a field that was never set. **Before this release that case crashed 4D** (fixed in the review commit).

Wraps libharu `HPDF_GetInfoAttr`.

---

## PDF_GetPageByIndex

### Syntax

```4d
$result:=PDF_GetPageByIndex ( pdf ; index )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `index` | Longint | Page index (libharu counts from 0). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Returns the handle of a page by index.

Wraps libharu `HPDF_GetPageByIndex`.

---

## PDF_GetPageLayout

### Syntax

```4d
$result:=PDF_GetPageLayout ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | Layout constant. |

### Description

Returns the page layout (`HPDF_PAGE_LAYOUT_*`).

Wraps libharu `HPDF_GetPageLayout`.

---

## PDF_GetPageMode

### Syntax

```4d
$result:=PDF_GetPageMode ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | Mode constant. |

### Description

Returns the page mode (`HPDF_PAGE_MODE_*`).

Wraps libharu `HPDF_GetPageMode`.

---

## PDF_GetTTFontDefFromFile

### Syntax

```4d
$result:=PDF_GetTTFontDefFromFile ( pdf ; path ; embedding )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `path` | Text | Path of the `.ttf` file. |
| `embedding` | Longint | `HPDF_TRUE` to embed. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads a TrueType font definition and returns its handle.

No other command takes a font-definition handle, so this is of limited use from 4D.

Wraps libharu `HPDF_GetTTFontDefFromFile`.

---

## PDF_GetViewerPreference

### Syntax

```4d
$result:=PDF_GetViewerPreference ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | Flags. |

### Description

Returns the viewer preference flags.

Wraps libharu `HPDF_GetViewerPreference`.

---

## PDF_HasDoc

### Syntax

```4d
$result:=PDF_HasDoc ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | `1` if a document exists, else `0`. |

### Description

Returns 1 if the document object currently holds a document, else 0.

Wraps libharu `HPDF_HasDoc`.

---

## PDF_InsertPage

### Syntax

```4d
$result:=PDF_InsertPage ( pdf ; target )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `target` | Text | Handle of the page to insert before. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Inserts a new page before an existing page and returns the new page handle.

Wraps libharu `HPDF_InsertPage`.

---

## PDF_LoadJpegImageFromFile

### Syntax

```4d
$result:=PDF_LoadJpegImageFromFile ( pdf ; path )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `path` | Text | JPEG file path. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads a JPEG file and returns an image handle.

Wraps libharu `HPDF_LoadJpegImageFromFile`.

---

## PDF_LoadJpegImageFromMem

### Syntax

```4d
$result:=PDF_LoadJpegImageFromMem ( pdf ; data )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `data` | Blob | JPEG bytes. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads JPEG data from a BLOB and returns an image handle.

Wraps libharu `HPDF_LoadJpegImageFromMem`.

---

## PDF_LoadPngImageFromFile

### Syntax

```4d
$result:=PDF_LoadPngImageFromFile ( pdf ; path )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `path` | Text | PNG file path. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads a PNG file and returns an image handle.

Wraps libharu `HPDF_LoadPngImageFromFile`.

---

## PDF_LoadPngImageFromMem

### Syntax

```4d
$result:=PDF_LoadPngImageFromMem ( pdf ; data )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `data` | Blob | PNG bytes. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads PNG data from a BLOB and returns an image handle.

Wraps libharu `HPDF_LoadPngImageFromMem`.

---

## PDF_LoadRaw1BitImageFromMem

### Syntax

```4d
$result:=PDF_LoadRaw1BitImageFromMem ( pdf ; data ; width ; height ; line_width ; black_is1 ; top_is_first )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `data` | Blob | Pixel bytes. |
| `width` | Longint | Width in pixels. |
| `height` | Longint | Height in pixels. |
| `line_width` | Longint | Bytes per row. |
| `black_is1` | Longint | `HPDF_TRUE` if 1 bits are black. |
| `top_is_first` | Longint | `HPDF_TRUE` if the first row is the top row. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads 1-bit monochrome pixel data from a BLOB and returns an image handle.

The BLOB must hold at least `line_width` x `height` bytes; a shorter one returns `""` (**after this release**; before, it was read past its end).

Wraps libharu `HPDF_Image_LoadRaw1BitImageFromMem`.

---

## PDF_LoadRawImageFromFile

### Syntax

```4d
$result:=PDF_LoadRawImageFromFile ( pdf ; path ; width ; height ; color_space )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `path` | Text | File path. |
| `width` | Longint | Width in pixels. |
| `height` | Longint | Height in pixels. |
| `color_space` | Longint | libharu `HPDF_ColorSpace` value (0 = DeviceGray, 1 = DeviceRGB, 2 = DeviceCMYK). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads uncompressed pixel data from a file and returns an image handle.

Wraps libharu `HPDF_LoadRawImageFromFile`.

---

## PDF_LoadRawImageFromMem

### Syntax

```4d
$result:=PDF_LoadRawImageFromMem ( pdf ; data ; width ; height ; color_space ; bits_per_component )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `data` | Blob | Pixel bytes. |
| `width` | Longint | Width in pixels. |
| `height` | Longint | Height in pixels. |
| `color_space` | Longint | libharu `HPDF_ColorSpace` value (0 = DeviceGray, 1 = DeviceRGB, 2 = DeviceCMYK). |
| `bits_per_component` | Longint | Bits per component (1, 2, 4 or 8). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads uncompressed pixel data from a BLOB and returns an image handle.

libharu reads about `width` x `height` x components x bits / 8 bytes from the BLOB. A shorter BLOB returns `""` (**after this release**; before, it was read past its end and could crash 4D).

Wraps libharu `HPDF_LoadRawImageFromMem`.

---

## PDF_LoadTTFontFromFile

### Syntax

```4d
$result:=PDF_LoadTTFontFromFile ( pdf ; path ; index ; embedding )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `path` | Text | Path of the `.ttf`/`.ttc` file. |
| `index` | Longint | Font index inside a collection (0 for a single font). |
| `embedding` | Longint | `HPDF_TRUE` to embed the font in the PDF. |
| Result | Text | Font name to pass to [PDF_GetFont](#pdf_getfont), `""` on failure. |

### Description

Loads a TrueType font (or one font from a `.ttc` collection) and returns its font name.

Uses libharu `HPDF_LoadTTFontFromFile2`. Returns `""` on failure.

Wraps libharu `HPDF_LoadTTFontFromFile2`.

---

## PDF_LoadType1FontFromFile

### Syntax

```4d
$result:=PDF_LoadType1FontFromFile ( pdf ; afm_path ; data_path )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `afm_path` | Text | Path of the `.afm` metrics file. |
| `data_path` | Text | Path of the `.pfb` font file. |
| Result | Text | Font name to pass to [PDF_GetFont](#pdf_getfont), `""` on failure. |

### Description

Loads a Type 1 font and returns its font name (pass it to [PDF_GetFont](#pdf_getfont)).

Both paths are required. Returns `""` on failure.

Wraps libharu `HPDF_LoadType1FontFromFile`.

---

## PDF_LoadU3DFromFile

### Syntax

```4d
$result:=PDF_LoadU3DFromFile ( pdf ; path )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `path` | Text | U3D file path. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Loads a U3D 3D-model file and returns its handle.

Wraps libharu `HPDF_LoadU3DFromFile`.

---

## PDF_New

### Syntax

```4d
$result:=PDF_New
```

| Parameter | Type | Description |
|---|---|---|
| Result | Text | Document handle, `""` if the document could not be created. |

### Description

Creates a new PDF document object and returns its handle.

Free every handle with [PDF_Free](#pdf_free) when you are done; nothing else releases it.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_NewDoc

### Syntax

```4d
$result:=PDF_NewDoc ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Discards the current document content and starts a new, empty document in the same document object.

Wraps libharu `HPDF_NewDoc`.

---

## PDF_ResetError

### Syntax

```4d
PDF_ResetError ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | | None. |

### Description

Clears the error state of the document.

Wraps libharu `HPDF_ResetError`.

---

## PDF_SaveToFile

### Syntax

```4d
$result:=PDF_SaveToFile ( pdf ; path )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `path` | Text | Destination file path (see Requirements for the path format). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Writes the document to a file.

The result is `0` on success. An empty path writes nothing and returns `0`.

Wraps libharu `HPDF_SaveToFile`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_SaveToStream

### Syntax

```4d
$result:=PDF_SaveToStream ( pdf ; data )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `data` | Blob | Receives the PDF bytes. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Writes the document into a BLOB.

The result is `0` on success. The previous error state of the document is reset first.

Wraps libharu `HPDF_SaveToStream`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_SetCompressionMode

### Syntax

```4d
$result:=PDF_SetCompressionMode ( pdf ; mode )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `mode` | Longint | Sum of `HPDF_COMP_*` constants, e.g. `HPDF_COMP_ALL`. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets which streams are compressed.

Wraps libharu `HPDF_SetCompressionMode`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_SetCurrentEncoder

### Syntax

```4d
$result:=PDF_SetCurrentEncoder ( pdf ; encoding_name )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `encoding_name` | Text | Encoding name. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the document's current encoder by name.

Wraps libharu `HPDF_SetCurrentEncoder`.

---

## PDF_SetEncryptionMode

### Syntax

```4d
$result:=PDF_SetEncryptionMode ( pdf ; mode ; key_length )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `mode` | Longint | `HPDF_ENCRYPT_R2` or `HPDF_ENCRYPT_R3`. |
| `key_length` | Longint | Key length in bytes (5 for R2; 5 to 16 for R3). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the encryption revision and key length.

Wraps libharu `HPDF_SetEncryptionMode`.

---

## PDF_SetInfoAttr

### Syntax

```4d
$result:=PDF_SetInfoAttr ( pdf ; type ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `type` | Longint | An `HPDF_INFO_*` constant (author, creator, title, subject, keywords, ...). |
| `value` | Text | Value (UTF-8). An empty value does nothing. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets a text field of the document information dictionary.

Wraps libharu `HPDF_SetInfoAttr`.

---

## PDF_SetInfoDateAttr

### Syntax

```4d
$result:=PDF_SetInfoDateAttr ( pdf ; type ; date ; time ; utc_offset ; offset_hours ; offset_minutes )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `type` | Longint | `HPDF_INFO_CREATION_DATE` or `HPDF_INFO_MOD_DATE`. |
| `date` | Date | Date. |
| `time` | Time | Time of day. |
| `utc_offset` | Longint | An `HPDF_UTC_OFFSET_*` constant. |
| `offset_hours` | Longint | Offset hours. |
| `offset_minutes` | Longint | Offset minutes. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the creation or modification date of the document.

Wraps libharu `HPDF_SetInfoDateAttr`.

---

## PDF_SetOpenAction

### Syntax

```4d
$result:=PDF_SetOpenAction ( pdf ; destination )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the destination shown when the document is opened.

Wraps libharu `HPDF_SetOpenAction`.

---

## PDF_SetPageLayout

### Syntax

```4d
$result:=PDF_SetPageLayout ( pdf ; layout )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `layout` | Longint | An `HPDF_PAGE_LAYOUT_*` constant. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets how pages are laid out when the document is opened.

Wraps libharu `HPDF_SetPageLayout`.

---

## PDF_SetPageMode

### Syntax

```4d
$result:=PDF_SetPageMode ( pdf ; mode )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `mode` | Longint | An `HPDF_PAGE_MODE_*` constant. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets what the viewer shows when the document is opened.

Wraps libharu `HPDF_SetPageMode`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_SetPagesConfiguration

### Syntax

```4d
$result:=PDF_SetPagesConfiguration ( pdf ; page_per_pages )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `page_per_pages` | Longint | Pages per node. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets how many pages a page-tree node holds (libharu `HPDF_SetPagesConfiguration`); only needed for very large documents.

Wraps libharu `HPDF_SetPagesConfiguration`.

---

## PDF_SetPassword

### Syntax

```4d
$result:=PDF_SetPassword ( pdf ; owner_password ; user_password )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `owner_password` | Text | Owner password (UTF-8). |
| `user_password` | Text | User password (UTF-8). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the owner and user passwords and turns on encryption.

**Both passwords must be non-empty**, otherwise the command does nothing and returns `0`. libharu requires them to differ.

Wraps libharu `HPDF_SetPassword`.

---

## PDF_SetPermission

### Syntax

```4d
$result:=PDF_SetPermission ( pdf ; permission )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `permission` | Longint | Sum of `HPDF_ENABLE_*` constants. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the permission flags of an encrypted document.

Call [PDF_SetPassword](#pdf_setpassword) first.

Wraps libharu `HPDF_SetPermission`.

---

## PDF_SetViewerPreference

### Syntax

```4d
$result:=PDF_SetViewerPreference ( pdf ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| `value` | Longint | libharu viewer-preference bit flags. No 4D constants are defined for them. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the viewer preference flags.

Wraps libharu `HPDF_SetViewerPreference`.

---

## PDF_UseCNSEncodings

### Syntax

```4d
$result:=PDF_UseCNSEncodings ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Enables the Simplified Chinese encodings.

Wraps libharu `HPDF_UseCNSEncodings`.

---

## PDF_UseCNSFonts

### Syntax

```4d
$result:=PDF_UseCNSFonts ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Enables the built-in Simplified Chinese fonts.

Wraps libharu `HPDF_UseCNSFonts`.

---

## PDF_UseCNTEncodings

### Syntax

```4d
$result:=PDF_UseCNTEncodings ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Enables the Traditional Chinese encodings.

Wraps libharu `HPDF_UseCNTEncodings`.

---

## PDF_UseCNTFonts

### Syntax

```4d
$result:=PDF_UseCNTFonts ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Enables the built-in Traditional Chinese fonts.

Wraps libharu `HPDF_UseCNTFonts`.

---

## PDF_UseJPEncodings

### Syntax

```4d
$result:=PDF_UseJPEncodings ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Enables the Japanese encodings (`90ms-RKSJ-H`, `EUC-H`, ...).

Wraps libharu `HPDF_UseJPEncodings`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_UseJPFonts

### Syntax

```4d
$result:=PDF_UseJPFonts ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Enables the built-in Japanese fonts (`MS-Mincho`, `MS-Gothic`, ...).

Wraps libharu `HPDF_UseJPFonts`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_UseKREncodings

### Syntax

```4d
$result:=PDF_UseKREncodings ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Enables the Korean encodings.

Wraps libharu `HPDF_UseKREncodings`.

---

## PDF_UseKRFonts

### Syntax

```4d
$result:=PDF_UseKRFonts ( pdf )
```

| Parameter | Type | Description |
|---|---|---|
| `pdf` | Text | Document handle from [PDF_New](#pdf_new). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Enables the built-in Korean fonts.

Wraps libharu `HPDF_UseKRFonts`.

## Page commands

Page size, graphics state, paths, text, annotations and getters. The first parameter is always a page handle.

---

## PDF_Page_Arc

### Syntax

```4d
$result:=PDF_Page_Arc ( page ; x ; y ; radius ; angle1 ; angle2 )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | Center x. |
| `y` | Real | Center y. |
| `radius` | Real | Radius. |
| `angle1` | Real | Start angle in degrees. |
| `angle2` | Real | End angle in degrees. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Appends an arc to the current path.

Wraps libharu `HPDF_Page_Arc`.

---

## PDF_Page_BeginText

### Syntax

```4d
$result:=PDF_Page_BeginText ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Begins a text object.

Wraps libharu `HPDF_Page_BeginText`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_Circle

### Syntax

```4d
$result:=PDF_Page_Circle ( page ; x ; y ; radius )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | Center x. |
| `y` | Real | Center y. |
| `radius` | Real | Radius. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Appends a circle to the current path.

Wraps libharu `HPDF_Page_Circle`.

### Example

Used in the worked examples: [text_demo2](#text_demo2).

---

## PDF_Page_Clip

### Syntax

```4d
$result:=PDF_Page_Clip ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Intersects the clipping path with the current path (nonzero winding rule).

Wraps libharu `HPDF_Page_Clip`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_ClosePath

### Syntax

```4d
$result:=PDF_Page_ClosePath ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Closes the current subpath.

Wraps libharu `HPDF_Page_ClosePath`.

---

## PDF_Page_ClosePathEofillStroke

### Syntax

```4d
$result:=PDF_Page_ClosePathEofillStroke ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Closes, fills and strokes the current path (even-odd rule).

Wraps libharu `HPDF_Page_ClosePathEofillStroke`.

---

## PDF_Page_ClosePathFillStroke

### Syntax

```4d
$result:=PDF_Page_ClosePathFillStroke ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Closes, fills and strokes the current path (nonzero winding rule).

Wraps libharu `HPDF_Page_ClosePathFillStroke`.

---

## PDF_Page_ClosePathStroke

### Syntax

```4d
$result:=PDF_Page_ClosePathStroke ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Closes and strokes the current path.

Wraps libharu `HPDF_Page_ClosePathStroke`.

---

## PDF_Page_Concat

### Syntax

```4d
$result:=PDF_Page_Concat ( page ; a ; b ; c ; d ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `a` | Real | Matrix a. |
| `b` | Real | b. |
| `c` | Real | c. |
| `d` | Real | d. |
| `x` | Real | Translation x. |
| `y` | Real | Translation y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Concatenates a transformation matrix to the current one.

Wraps libharu `HPDF_Page_Concat`.

### Example

Used in the worked examples: [text_demo2](#text_demo2).

---

## PDF_Page_CreateCircleAnnot

### Syntax

```4d
$result:=PDF_Page_CreateCircleAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a circle annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateCircleAnnot`.

---

## PDF_Page_CreateDestination

### Syntax

```4d
$result:=PDF_Page_CreateDestination ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a destination that points to this page and returns its handle.

Wraps libharu `HPDF_Page_CreateDestination`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_Page_CreateFreeTextAnnot

### Syntax

```4d
$result:=PDF_Page_CreateFreeTextAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a free-text annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateFreeTextAnnot`.

---

## PDF_Page_CreateHighlightAnnot

### Syntax

```4d
$result:=PDF_Page_CreateHighlightAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a highlight annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateHighlightAnnot`.

---

## PDF_Page_CreateLineAnnot

### Syntax

```4d
$result:=PDF_Page_CreateLineAnnot ( page ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a line annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder. Set the end points with [PDF_LineAnnot_SetPosition](#pdf_lineannot_setposition).

Wraps libharu `HPDF_Page_CreateLineAnnot`.

---

## PDF_Page_CreateLinkAnnot

### Syntax

```4d
$result:=PDF_Page_CreateLinkAnnot ( page ; left ; bottom ; right ; top ; destination )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `destination` | Text | Destination handle. **Currently not accepted** (see below). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a link annotation that jumps to a destination in the document.

**This command does not work in this release**: the plugin looks the destination up in its document registry, where a destination handle is never found, so libharu receives no destination, rejects the call, and the command returns `""`. Use an outline ([PDF_Outline_SetDestination](#pdf_outline_setdestination)) or [PDF_Page_CreateURILinkAnnot](#pdf_page_createurilinkannot) instead. Never pass a document handle as `destination`.

Wraps libharu `HPDF_Page_CreateLinkAnnot`.

---

## PDF_Page_CreatePopupAnnot

### Syntax

```4d
$result:=PDF_Page_CreatePopupAnnot ( page ; left ; bottom ; right ; top ; parent )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `parent` | Text | Handle of the annotation the popup belongs to. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a popup annotation and returns its handle.

Wraps libharu `HPDF_Page_CreatePopupAnnot`.

---

## PDF_Page_CreateProjectionAnnot

### Syntax

```4d
$result:=PDF_Page_CreateProjectionAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a projection annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateProjectionAnnot`.

---

## PDF_Page_CreateSquareAnnot

### Syntax

```4d
$result:=PDF_Page_CreateSquareAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a square annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateSquareAnnot`.

---

## PDF_Page_CreateSquigglyAnnot

### Syntax

```4d
$result:=PDF_Page_CreateSquigglyAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a squiggly-underline annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateSquigglyAnnot`.

---

## PDF_Page_CreateStampAnnot

### Syntax

```4d
$result:=PDF_Page_CreateStampAnnot ( page ; left ; bottom ; right ; top ; stamp ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `stamp` | Longint | An `HPDF_STAMP_ANNOT_*` constant. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a stamp annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateStampAnnot`.

---

## PDF_Page_CreateStrikeOutAnnot

### Syntax

```4d
$result:=PDF_Page_CreateStrikeOutAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a strike-out annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateStrikeOutAnnot`.

---

## PDF_Page_CreateTextAnnot

### Syntax

```4d
$result:=PDF_Page_CreateTextAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a text (sticky note) annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateTextAnnot`.

---

## PDF_Page_CreateTextMarkupAnnot

### Syntax

```4d
$result:=PDF_Page_CreateTextMarkupAnnot ( page ; left ; bottom ; right ; top ; text ; encoder ; subtype )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| `subtype` | Longint | An `HPDF_ANNOT_*` type constant (`HPDF_ANNOT_HIGHTLIGHT`, `HPDF_ANNOT_UNDERLINE`, ...). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a text-markup annotation of a given subtype and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateTextMarkupAnnot`.

---

## PDF_Page_CreateUnderlineAnnot

### Syntax

```4d
$result:=PDF_Page_CreateUnderlineAnnot ( page ; left ; bottom ; right ; top ; text ; encoder )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `text` | Text | Annotation text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). An empty text creates nothing. |
| `encoder` | Text | Ignored (see below). Pass `""`. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates an underline annotation and returns its handle.

**The `encoder` parameter is ignored in this release**: the plugin looks it up in its document registry, where an encoder handle is never found, so libharu always receives no encoder (its default). Pass `""`. Do not pass a document handle there: it would be handed to libharu as an encoder.

Wraps libharu `HPDF_Page_CreateUnderlineAnnot`.

---

## PDF_Page_CreateURILinkAnnot

### Syntax

```4d
$result:=PDF_Page_CreateURILinkAnnot ( page ; left ; bottom ; right ; top ; uri )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left edge of the annotation rectangle. |
| `bottom` | Real | Bottom edge. |
| `right` | Real | Right edge. |
| `top` | Real | Top edge. |
| `uri` | Text | Target URI (UTF-8). |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Creates a link annotation that opens a URI and returns its handle.

Wraps libharu `HPDF_Page_CreateURILinkAnnot`.

---

## PDF_Page_CurveTo

### Syntax

```4d
$result:=PDF_Page_CurveTo ( page ; x1 ; y1 ; x2 ; y2 ; x3 ; y3 )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x1` | Real | Control point 1 x. |
| `y1` | Real | Control point 1 y. |
| `x2` | Real | Control point 2 x. |
| `y2` | Real | Control point 2 y. |
| `x3` | Real | End x. |
| `y3` | Real | End y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Appends a Bezier curve with two control points.

Wraps libharu `HPDF_Page_CurveTo`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_CurveTo2

### Syntax

```4d
$result:=PDF_Page_CurveTo2 ( page ; x2 ; y2 ; x3 ; y3 )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x2` | Real | Control point x. |
| `y2` | Real | Control point y. |
| `x3` | Real | End x. |
| `y3` | Real | End y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Appends a Bezier curve whose first control point is the current point.

Wraps libharu `HPDF_Page_CurveTo2`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_CurveTo3

### Syntax

```4d
$result:=PDF_Page_CurveTo3 ( page ; x1 ; y1 ; x3 ; y3 )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x1` | Real | Control point x. |
| `y1` | Real | Control point y. |
| `x3` | Real | End x. |
| `y3` | Real | End y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Appends a Bezier curve whose second control point is the end point.

Wraps libharu `HPDF_Page_CurveTo3`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_DrawImage

### Syntax

```4d
$result:=PDF_Page_DrawImage ( page ; image ; x ; y ; width ; height )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `image` | Text | Image handle. |
| `x` | Real | Left. |
| `y` | Real | Bottom. |
| `width` | Real | Drawn width. |
| `height` | Real | Drawn height. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Draws an image.

Wraps libharu `HPDF_Page_DrawImage`.

---

## PDF_Page_Ellipse

### Syntax

```4d
$result:=PDF_Page_Ellipse ( page ; x ; y ; x_radius ; y_radius )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | Center x. |
| `y` | Real | Center y. |
| `x_radius` | Real | Horizontal radius. |
| `y_radius` | Real | Vertical radius. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Appends an ellipse to the current path.

Wraps libharu `HPDF_Page_Ellipse`.

---

## PDF_Page_EndPath

### Syntax

```4d
$result:=PDF_Page_EndPath ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Ends the current path without painting it (used after a clip).

Wraps libharu `HPDF_Page_EndPath`.

---

## PDF_Page_EndText

### Syntax

```4d
$result:=PDF_Page_EndText ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Ends a text object.

Wraps libharu `HPDF_Page_EndText`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_Eoclip

### Syntax

```4d
$result:=PDF_Page_Eoclip ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Intersects the clipping path with the current path (even-odd rule).

Wraps libharu `HPDF_Page_Eoclip`.

---

## PDF_Page_Eofill

### Syntax

```4d
$result:=PDF_Page_Eofill ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fills the current path (even-odd rule).

Wraps libharu `HPDF_Page_Eofill`.

---

## PDF_Page_EofillStroke

### Syntax

```4d
$result:=PDF_Page_EofillStroke ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fills and strokes the current path (even-odd rule).

Wraps libharu `HPDF_Page_EofillStroke`.

---

## PDF_Page_Fill

### Syntax

```4d
$result:=PDF_Page_Fill ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fills the current path (nonzero winding rule).

Wraps libharu `HPDF_Page_Fill`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_FillStroke

### Syntax

```4d
$result:=PDF_Page_FillStroke ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fills and strokes the current path (nonzero winding rule).

Wraps libharu `HPDF_Page_FillStroke`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_GetCharSpace

### Syntax

```4d
$result:=PDF_Page_GetCharSpace ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the character spacing.

Wraps libharu `HPDF_Page_GetCharSpace`.

---

## PDF_Page_GetCMYKFill

### Syntax

```4d
PDF_Page_GetCMYKFill ( page ; c ; m ; y ; k )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `c` | Real | Receives cyan. |
| `m` | Real | Receives magenta. |
| `y` | Real | Receives yellow. |
| `k` | Real | Receives black. |
| Result | | None. |

### Description

Returns the fill color in CMYK.

Wraps libharu `HPDF_Page_GetCMYKFill`.

---

## PDF_Page_GetCMYKStroke

### Syntax

```4d
PDF_Page_GetCMYKStroke ( page ; c ; m ; y ; k )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `c` | Real | Receives cyan. |
| `m` | Real | Receives magenta. |
| `y` | Real | Receives yellow. |
| `k` | Real | Receives black. |
| Result | | None. |

### Description

Returns the stroke color in CMYK.

Wraps libharu `HPDF_Page_GetCMYKStroke`.

---

## PDF_Page_GetCurrentFont

### Syntax

```4d
$result:=PDF_Page_GetCurrentFont ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Text | Handle (or name) of the created/requested object, `""` on failure. |

### Description

Returns the handle of the current font, or `""` if none is set.

Wraps libharu `HPDF_Page_GetCurrentFont`.

---

## PDF_Page_GetCurrentFontSize

### Syntax

```4d
$result:=PDF_Page_GetCurrentFontSize ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the current font size.

Wraps libharu `HPDF_Page_GetCurrentFontSize`.

---

## PDF_Page_GetCurrentPos

### Syntax

```4d
PDF_Page_GetCurrentPos ( page ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | Receives x. |
| `y` | Real | Receives y. |
| Result | | None. |

### Description

Returns the current point of the path.

Wraps libharu `HPDF_Page_GetCurrentPos2`.

---

## PDF_Page_GetCurrentTextPos

### Syntax

```4d
PDF_Page_GetCurrentTextPos ( page ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | Receives x. |
| `y` | Real | Receives y. |
| Result | | None. |

### Description

Returns the current text position.

Wraps libharu `HPDF_Page_GetCurrentTextPos2`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_Page_GetDash

### Syntax

```4d
$result:=PDF_Page_GetDash ( page ; pattern ; count ; phase )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `pattern` | Array longint | Receives the pattern (elements 1..n). |
| `count` | Longint | Receives the number of elements. |
| `phase` | Longint | Receives the phase. |
| Result | Longint | Always `0`. |

### Description

Returns the dash pattern.

The result is always `0`.

Wraps libharu `HPDF_Page_GetDash`.

---

## PDF_Page_GetFillingColorSpace

### Syntax

```4d
$result:=PDF_Page_GetFillingColorSpace ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | Color space. |

### Description

Returns the filling color space (libharu `HPDF_ColorSpace`).

Wraps libharu `HPDF_Page_GetFillingColorSpace`.

---

## PDF_Page_GetFlat

### Syntax

```4d
$result:=PDF_Page_GetFlat ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the flatness.

Wraps libharu `HPDF_Page_GetFlat`.

---

## PDF_Page_GetGMode

### Syntax

```4d
$result:=PDF_Page_GetGMode ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | Graphics mode. |

### Description

Returns the current graphics mode (page description, path object or text object) as a libharu `HPDF_GMODE_*` bit value.

Wraps libharu `HPDF_Page_GetGMode`.

---

## PDF_Page_GetGrayFill

### Syntax

```4d
$result:=PDF_Page_GetGrayFill ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the fill gray level.

Wraps libharu `HPDF_Page_GetGrayFill`.

---

## PDF_Page_GetGrayStroke

### Syntax

```4d
$result:=PDF_Page_GetGrayStroke ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the stroke gray level.

Wraps libharu `HPDF_Page_GetGrayStroke`.

---

## PDF_Page_GetGStateDepth

### Syntax

```4d
$result:=PDF_Page_GetGStateDepth ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | Depth. |

### Description

Returns how many graphics states are saved.

Wraps libharu `HPDF_Page_GetGStateDepth`.

---

## PDF_Page_GetHeight

### Syntax

```4d
$result:=PDF_Page_GetHeight ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the page height in points.

Wraps libharu `HPDF_Page_GetHeight`.

### Example

Used in the worked examples: [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_GetHorizontalScalling

### Syntax

```4d
$result:=PDF_Page_GetHorizontalScalling ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the horizontal text scaling.

Wraps libharu `HPDF_Page_GetHorizontalScalling`.

---

## PDF_Page_GetLineCap

### Syntax

```4d
$result:=PDF_Page_GetLineCap ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | Line cap constant. |

### Description

Returns the line cap style.

Wraps libharu `HPDF_Page_GetLineCap`.

---

## PDF_Page_GetLineJoin

### Syntax

```4d
$result:=PDF_Page_GetLineJoin ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | Line join constant. |

### Description

Returns the line join style.

Wraps libharu `HPDF_Page_GetLineJoin`.

---

## PDF_Page_GetLineWidth

### Syntax

```4d
$result:=PDF_Page_GetLineWidth ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the line width.

Wraps libharu `HPDF_Page_GetLineWidth`.

---

## PDF_Page_GetMiterLimit

### Syntax

```4d
$result:=PDF_Page_GetMiterLimit ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the miter limit.

Wraps libharu `HPDF_Page_GetMiterLimit`.

---

## PDF_Page_GetRGBFill

### Syntax

```4d
PDF_Page_GetRGBFill ( page ; r ; g ; b )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `r` | Real | Receives red. |
| `g` | Real | Receives green. |
| `b` | Real | Receives blue. |
| Result | | None. |

### Description

Returns the fill color in RGB.

Wraps libharu `HPDF_Page_GetRGBFill`.

---

## PDF_Page_GetRGBStroke

### Syntax

```4d
PDF_Page_GetRGBStroke ( page ; r ; g ; b )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `r` | Real | Receives red. |
| `g` | Real | Receives green. |
| `b` | Real | Receives blue. |
| Result | | None. |

### Description

Returns the stroke color in RGB.

Wraps libharu `HPDF_Page_GetRGBStroke`.

---

## PDF_Page_GetStrokingColorSpace

### Syntax

```4d
$result:=PDF_Page_GetStrokingColorSpace ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | Color space. |

### Description

Returns the stroking color space (libharu `HPDF_ColorSpace`).

Wraps libharu `HPDF_Page_GetStrokingColorSpace`.

---

## PDF_Page_GetTextLeading

### Syntax

```4d
$result:=PDF_Page_GetTextLeading ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the text leading.

Wraps libharu `HPDF_Page_GetTextLeading`.

---

## PDF_Page_GetTextMatrix

### Syntax

```4d
PDF_Page_GetTextMatrix ( page ; a ; b ; c ; d ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `a` | Real | Receives a. |
| `b` | Real | Receives b. |
| `c` | Real | Receives c. |
| `d` | Real | Receives d. |
| `x` | Real | Receives x. |
| `y` | Real | Receives y. |
| Result | | None. |

### Description

Returns the current text matrix.

Wraps libharu `HPDF_Page_GetTextMatrix`.

---

## PDF_Page_GetTextRenderingMode

### Syntax

```4d
$result:=PDF_Page_GetTextRenderingMode ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | Rendering mode constant. |

### Description

Returns the text rendering mode.

Wraps libharu `HPDF_Page_GetTextRenderingMode`.

---

## PDF_Page_GetTextRise

### Syntax

```4d
$result:=PDF_Page_GetTextRise ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the text rise.

Wraps libharu `HPDF_Page_GetTextRise`.

---

## PDF_Page_GetTransMatrix

### Syntax

```4d
PDF_Page_GetTransMatrix ( page ; a ; b ; c ; d ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `a` | Real | Receives a. |
| `b` | Real | Receives b. |
| `c` | Real | Receives c. |
| `d` | Real | Receives d. |
| `x` | Real | Receives x. |
| `y` | Real | Receives y. |
| Result | | None. |

### Description

Returns the current transformation matrix.

Wraps libharu `HPDF_Page_GetTransMatrix`.

---

## PDF_Page_GetWidth

### Syntax

```4d
$result:=PDF_Page_GetWidth ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the page width in points.

Wraps libharu `HPDF_Page_GetWidth`.

### Example

Used in the worked examples: [line_demo](#line_demo), [text_demo](#text_demo).

---

## PDF_Page_GetWordSpace

### Syntax

```4d
$result:=PDF_Page_GetWordSpace ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Real | Value. |

### Description

Returns the word spacing.

Wraps libharu `HPDF_Page_GetWordSpace`.

---

## PDF_Page_GRestore

### Syntax

```4d
$result:=PDF_Page_GRestore ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Restores the graphics state saved by [PDF_Page_GSave](#pdf_page_gsave).

Wraps libharu `HPDF_Page_GRestore`.

### Example

Used in the worked examples: [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_GSave

### Syntax

```4d
$result:=PDF_Page_GSave ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Saves the graphics state.

Wraps libharu `HPDF_Page_GSave`.

### Example

Used in the worked examples: [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_LineTo

### Syntax

```4d
$result:=PDF_Page_LineTo ( page ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | X. |
| `y` | Real | Y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Appends a straight line to the current path.

Wraps libharu `HPDF_Page_LineTo`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [line_demo](#line_demo).

---

## PDF_Page_MeasureText

### Syntax

```4d
$result:=PDF_Page_MeasureText ( page ; text ; width ; wordwrap ; real_width )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `text` | Text | Text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). |
| `width` | Real | Available width. |
| `wordwrap` | Longint | `HPDF_TRUE` to break only between words. |
| `real_width` | Real | Receives the width actually used. |
| Result | Longint | Number of bytes that fit. |

### Description

Returns how many bytes of a text fit in a width.

Wraps libharu `HPDF_Page_MeasureText`.

### Example

Used in the worked examples: [text_demo](#text_demo).

---

## PDF_Page_MoveTextPos

### Syntax

```4d
$result:=PDF_Page_MoveTextPos ( page ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | Horizontal offset. |
| `y` | Real | Vertical offset. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Moves the text position.

Uses libharu `HPDF_Page_MoveTextPos2`, which also sets the text leading to `-y`.

Wraps libharu `HPDF_Page_MoveTextPos2`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo).

---

## PDF_Page_MoveTo

### Syntax

```4d
$result:=PDF_Page_MoveTo ( page ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | X. |
| `y` | Real | Y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Starts a new subpath at a point.

Wraps libharu `HPDF_Page_MoveTo`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [line_demo](#line_demo).

---

## PDF_Page_MoveToNextLine

### Syntax

```4d
$result:=PDF_Page_MoveToNextLine ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Moves the text position to the start of the next line.

Wraps libharu `HPDF_Page_MoveToNextLine`.

---

## PDF_Page_Rectangle

### Syntax

```4d
$result:=PDF_Page_Rectangle ( page ; x ; y ; width ; height )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | Left. |
| `y` | Real | Bottom. |
| `width` | Real | Width. |
| `height` | Real | Height. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Appends a rectangle to the current path.

Wraps libharu `HPDF_Page_Rectangle`.

### Example

Used in the worked examples: [line_demo](#line_demo), [text_demo2](#text_demo2).

---

## PDF_Page_SetCharSpace

### Syntax

```4d
$result:=PDF_Page_SetCharSpace ( page ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `value` | Real | Spacing. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the character spacing.

Wraps libharu `HPDF_Page_SetCharSpace`.

### Example

Used in the worked examples: [text_demo](#text_demo).

---

## PDF_Page_SetCMYKFill

### Syntax

```4d
$result:=PDF_Page_SetCMYKFill ( page ; c ; m ; y ; k )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `c` | Real | Cyan, 0 to 1. |
| `m` | Real | Magenta. |
| `y` | Real | Yellow. |
| `k` | Real | Black. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the fill color in CMYK.

Wraps libharu `HPDF_Page_SetCMYKFill`.

---

## PDF_Page_SetCMYKStroke

### Syntax

```4d
$result:=PDF_Page_SetCMYKStroke ( page ; c ; m ; y ; k )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `c` | Real | Cyan, 0 to 1. |
| `m` | Real | Magenta. |
| `y` | Real | Yellow. |
| `k` | Real | Black. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the stroke color in CMYK.

Wraps libharu `HPDF_Page_SetCMYKStroke`.

---

## PDF_Page_SetDash

### Syntax

```4d
$result:=PDF_Page_SetDash ( page ; pattern ; count ; phase )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `pattern` | Array longint | ARRAY LONGINT of dash/gap lengths (elements 1..n). |
| `count` | Longint | Number of pattern elements to use: 0 for a solid line, 1, or an even number. |
| `phase` | Longint | Dash phase. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the dash pattern for lines.

`count` is capped at the size of the array (**after this release**; before, a larger `count` read past the array).

Wraps libharu `HPDF_Page_SetDash`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_SetExtGState

### Syntax

```4d
$result:=PDF_Page_SetExtGState ( page ; ext_gstate )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `ext_gstate` | Text | Handle from [PDF_CreateExtGState](#pdf_createextgstate). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Applies an extended graphics state to the page.

Wraps libharu `HPDF_Page_SetExtGState`.

---

## PDF_Page_SetFontAndSize

### Syntax

```4d
$result:=PDF_Page_SetFontAndSize ( page ; font ; size )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| `size` | Real | Size in points. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the font and size for text.

Wraps libharu `HPDF_Page_SetFontAndSize`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_SetGrayFill

### Syntax

```4d
$result:=PDF_Page_SetGrayFill ( page ; gray )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `gray` | Real | Gray level, 0 to 1. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the fill color in gray.

Wraps libharu `HPDF_Page_SetGrayFill`.

---

## PDF_Page_SetGrayStroke

### Syntax

```4d
$result:=PDF_Page_SetGrayStroke ( page ; gray )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `gray` | Real | Gray level, 0 to 1. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the stroke color in gray.

Wraps libharu `HPDF_Page_SetGrayStroke`.

### Example

Used in the worked examples: [text_demo2](#text_demo2).

---

## PDF_Page_SetHeight

### Syntax

```4d
$result:=PDF_Page_SetHeight ( page ; height )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `height` | Real | Height in points. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the page height.

Wraps libharu `HPDF_Page_SetHeight`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_Page_SetHorizontalScalling

### Syntax

```4d
$result:=PDF_Page_SetHorizontalScalling ( page ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `value` | Real | Scaling in percent (100 = normal). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the horizontal text scaling.

The spelling `Scalling` follows libharu.

Wraps libharu `HPDF_Page_SetHorizontalScalling`.

---

## PDF_Page_SetLineCap

### Syntax

```4d
$result:=PDF_Page_SetLineCap ( page ; line_cap )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `line_cap` | Longint | An `HPDF_*_END` constant. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the line cap style.

Wraps libharu `HPDF_Page_SetLineCap`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_SetLineJoin

### Syntax

```4d
$result:=PDF_Page_SetLineJoin ( page ; line_join )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `line_join` | Longint | An `HPDF_*_JOIN` constant. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the line join style.

Wraps libharu `HPDF_Page_SetLineJoin`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_SetLineWidth

### Syntax

```4d
$result:=PDF_Page_SetLineWidth ( page ; line_width )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `line_width` | Real | Width in points. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the line width.

Wraps libharu `HPDF_Page_SetLineWidth`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [line_demo](#line_demo), [text_demo](#text_demo).

---

## PDF_Page_SetMiterLimit

### Syntax

```4d
$result:=PDF_Page_SetMiterLimit ( page ; miter_limit )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `miter_limit` | Real | Miter limit. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the miter limit.

Wraps libharu `HPDF_Page_SetMiterLimit`.

---

## PDF_Page_SetRGBFill

### Syntax

```4d
$result:=PDF_Page_SetRGBFill ( page ; r ; g ; b )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `r` | Real | Red, 0 to 1. |
| `g` | Real | Green. |
| `b` | Real | Blue. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the fill color in RGB.

Wraps libharu `HPDF_Page_SetRGBFill`.

### Example

Used in the worked examples: [line_demo](#line_demo), [text_demo](#text_demo).

---

## PDF_Page_SetRGBStroke

### Syntax

```4d
$result:=PDF_Page_SetRGBStroke ( page ; r ; g ; b )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `r` | Real | Red, 0 to 1. |
| `g` | Real | Green. |
| `b` | Real | Blue. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the stroke color in RGB.

Wraps libharu `HPDF_Page_SetRGBStroke`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_SetRotate

### Syntax

```4d
$result:=PDF_Page_SetRotate ( page ; angle )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `angle` | Longint | Angle in degrees, a multiple of 90. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the page rotation.

Wraps libharu `HPDF_Page_SetRotate`.

---

## PDF_Page_SetSize

### Syntax

```4d
$result:=PDF_Page_SetSize ( page ; size ; direction )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `size` | Longint | An `HPDF_PAGE_SIZE_*` constant. |
| `direction` | Longint | `HPDF_PAGE_PORTRAIT` or `HPDF_PAGE_LANDSCAPE`. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the page to a standard size.

Wraps libharu `HPDF_Page_SetSize`.

### Example

Used in the worked examples: [text_demo2](#text_demo2).

---

## PDF_Page_SetSlideShow

### Syntax

```4d
PDF_Page_SetSlideShow ( page ; type ; display_time ; transition_time )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `type` | Longint | An `HPDF_TS_*` constant. |
| `display_time` | Real | Display duration in seconds. |
| `transition_time` | Real | Transition duration in seconds. |
| Result | | None. |

### Description

Sets the page transition for presentation mode.

Wraps libharu `HPDF_Page_SetSlideShow`.

---

## PDF_Page_SetTextLeading

### Syntax

```4d
$result:=PDF_Page_SetTextLeading ( page ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `value` | Real | Leading. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the text leading (line spacing).

Wraps libharu `HPDF_Page_SetTextLeading`.

### Example

Used in the worked examples: [line_demo](#line_demo), [text_demo2](#text_demo2).

---

## PDF_Page_SetTextMatrix

### Syntax

```4d
$result:=PDF_Page_SetTextMatrix ( page ; a ; b ; c ; d ; x ; y )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `a` | Real | a. |
| `b` | Real | b. |
| `c` | Real | c. |
| `d` | Real | d. |
| `x` | Real | x. |
| `y` | Real | y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the text matrix.

Wraps libharu `HPDF_Page_SetTextMatrix`.

### Example

Used in the worked examples: [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_SetTextRenderingMode

### Syntax

```4d
$result:=PDF_Page_SetTextRenderingMode ( page ; mode )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `mode` | Longint | An `HPDF_FILL`, `HPDF_STROKE`, ... `HPDF_CLIPPING` constant. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the text rendering mode.

Wraps libharu `HPDF_Page_SetTextRenderingMode`.

### Example

Used in the worked examples: [text_demo](#text_demo).

---

## PDF_Page_SetTextRise

### Syntax

```4d
$result:=PDF_Page_SetTextRise ( page ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `value` | Real | Rise. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the text rise (superscript/subscript offset).

Wraps libharu `HPDF_Page_SetTextRise`.

---

## PDF_Page_SetWidth

### Syntax

```4d
$result:=PDF_Page_SetWidth ( page ; width )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `width` | Real | Width in points. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the page width.

Wraps libharu `HPDF_Page_SetWidth`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_Page_SetWordSpace

### Syntax

```4d
$result:=PDF_Page_SetWordSpace ( page ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `value` | Real | Spacing. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the word spacing.

Wraps libharu `HPDF_Page_SetWordSpace`.

### Example

Used in the worked examples: [text_demo](#text_demo).

---

## PDF_Page_SetZoom

### Syntax

```4d
$result:=PDF_Page_SetZoom ( page ; zoom )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `zoom` | Real | Zoom factor. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the page zoom.

Wraps libharu `HPDF_Page_SetZoom`.

---

## PDF_Page_ShowText

### Syntax

```4d
$result:=PDF_Page_ShowText ( page ; text )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `text` | Text | Text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Draws text at the current text position.

An empty text does nothing and returns `0`.

Wraps libharu `HPDF_Page_ShowText`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [font_demo](#font_demo), [line_demo](#line_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_ShowTextNextLine

### Syntax

```4d
$result:=PDF_Page_ShowTextNextLine ( page ; text )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `text` | Text | Text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Moves to the next line and draws text.

Wraps libharu `HPDF_Page_ShowTextNextLine`.

### Example

Used in the worked examples: [line_demo](#line_demo).

---

## PDF_Page_ShowTextNextLineEx

### Syntax

```4d
$result:=PDF_Page_ShowTextNextLineEx ( page ; word_space ; char_space ; text )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `word_space` | Real | Word spacing. |
| `char_space` | Real | Character spacing. |
| `text` | Text | Text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets word and character spacing, moves to the next line and draws text.

Wraps libharu `HPDF_Page_ShowTextNextLineEx`.

---

## PDF_Page_Stroke

### Syntax

```4d
$result:=PDF_Page_Stroke ( page )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Strokes the current path.

Wraps libharu `HPDF_Page_Stroke`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo), [line_demo](#line_demo), [text_demo2](#text_demo2).

---

## PDF_Page_TextOut

### Syntax

```4d
$result:=PDF_Page_TextOut ( page ; x ; y ; text )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `x` | Real | X. |
| `y` | Real | Y. |
| `text` | Text | Text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Draws text at a position (inside a text object).

Wraps libharu `HPDF_Page_TextOut`.

### Example

Used in the worked examples: [font_demo](#font_demo), [text_demo](#text_demo), [text_demo2](#text_demo2).

---

## PDF_Page_TextRect

### Syntax

```4d
$result:=PDF_Page_TextRect ( page ; left ; top ; right ; bottom ; text ; align ; length )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `left` | Real | Left. |
| `top` | Real | Top. |
| `right` | Real | Right. |
| `bottom` | Real | Bottom. |
| `text` | Text | Text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). |
| `align` | Longint | An `HPDF_TALIGN_*` constant. |
| `length` | Longint | Receives the number of bytes (in the converted encoding) that fit. |
| Result | Longint | libharu status. |

### Description

Draws text inside a rectangle, wrapping lines.

When the text does not fit, libharu returns a non-zero status (`HPDF_PAGE_INSUFFICIENT_SPACE`, per libharu's documentation; not traced here) and `length` tells how much was drawn.

Wraps libharu `HPDF_Page_TextRect`.

### Example

Used in the worked examples: [text_demo2](#text_demo2).

---

## PDF_Page_TextWidth

### Syntax

```4d
$result:=PDF_Page_TextWidth ( page ; text )
```

| Parameter | Type | Description |
|---|---|---|
| `page` | Text | Page handle. |
| `text` | Text | Text. Converted from Unicode with the global encoding (see [PDF_Global_SetEncoding](#pdf_global_setencoding)). |
| Result | Real | Value. |

### Description

Returns the width of a text in the current font and size.

Wraps libharu `HPDF_Page_TextWidth`.

## Font commands

Font metrics. The first parameter is a font handle.

---

## PDF_Font_GetAscent

### Syntax

```4d
$result:=PDF_Font_GetAscent ( font )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| Result | Longint | Ascent. |

### Description

Returns the font ascent.

Wraps libharu `HPDF_Font_GetAscent`.

---

## PDF_Font_GetBBox

### Syntax

```4d
PDF_Font_GetBBox ( font ; left ; bottom ; right ; top )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| `left` | Real | Receives left. |
| `bottom` | Real | Receives bottom. |
| `right` | Real | Receives right. |
| `top` | Real | Receives top. |
| Result | | None. |

### Description

Returns the font bounding box.

Wraps libharu `HPDF_Font_GetBBox`.

---

## PDF_Font_GetCapHeight

### Syntax

```4d
$result:=PDF_Font_GetCapHeight ( font )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| Result | Longint | Cap height. |

### Description

Returns the font cap height.

Wraps libharu `HPDF_Font_GetCapHeight`.

---

## PDF_Font_GetDescent

### Syntax

```4d
$result:=PDF_Font_GetDescent ( font )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| Result | Longint | Descent. |

### Description

Returns the font descent.

Wraps libharu `HPDF_Font_GetDescent`.

---

## PDF_Font_GetEncodingName

### Syntax

```4d
$result:=PDF_Font_GetEncodingName ( font )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| Result | Text | Encoding name. |

### Description

Returns the encoding name of a font.

Returns `""` for an invalid handle. **Before this release an empty handle crashed 4D.**

Wraps libharu `HPDF_Font_GetEncodingName`.

---

## PDF_Font_GetFontName

### Syntax

```4d
$result:=PDF_Font_GetFontName ( font )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| Result | Text | Font name. |

### Description

Returns the name of a font.

Returns `""` for an invalid handle. **Before this release an empty handle crashed 4D.**

Wraps libharu `HPDF_Font_GetFontName`.

---

## PDF_Font_GetUnicodeWidth

### Syntax

```4d
$result:=PDF_Font_GetUnicodeWidth ( font ; code )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| `code` | Longint | Unicode code point. |
| Result | Longint | Width. |

### Description

Returns the width of one Unicode character in the font (in 1/1000 em).

Wraps libharu `HPDF_Font_GetUnicodeWidth`.

---

## PDF_Font_GetXHeight

### Syntax

```4d
$result:=PDF_Font_GetXHeight ( font )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| Result | Longint | x-height. |

### Description

Returns the font x-height.

Wraps libharu `HPDF_Font_GetXHeight`.

---

## PDF_Font_MeasureText

### Syntax

```4d
$result:=PDF_Font_MeasureText ( font ; text ; width ; font_size ; char_space ; word_space ; wordwrap ; real_width )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| `text` | Text | Text, passed as **UTF-8** (not the global encoding). |
| `width` | Real | Available width. |
| `font_size` | Real | Font size. |
| `char_space` | Real | Character spacing. |
| `word_space` | Real | Word spacing. |
| `wordwrap` | Longint | `HPDF_TRUE` to break only between words. |
| `real_width` | Real | Receives the width used. |
| Result | Longint | Number of bytes that fit. |

### Description

Returns how many bytes of a text fit in a width.

Same UTF-8 caveat as [PDF_Font_TextWidth](#pdf_font_textwidth); prefer [PDF_Page_MeasureText](#pdf_page_measuretext).

Wraps libharu `HPDF_Font_MeasureText`.

---

## PDF_Font_TextWidth

### Syntax

```4d
PDF_Font_TextWidth ( font ; text ; num_chars ; width ; num_spaces )
```

| Parameter | Type | Description |
|---|---|---|
| `font` | Text | Font handle from [PDF_GetFont](#pdf_getfont). |
| `text` | Text | Text, passed as **UTF-8** (not the global encoding). |
| `num_chars` | Longint | Receives the number of characters. |
| `width` | Longint | Receives the width (1/1000 em units). |
| `num_spaces` | Longint | Receives the number of spaces. |
| Result | | None. |

### Description

Measures a text in the font.

Because the text is passed as UTF-8, results for non-ASCII text do not match what the drawing commands draw; use [PDF_Page_TextWidth](#pdf_page_textwidth) instead.

Wraps libharu `HPDF_Font_TextWidth`.

## Image commands

Image properties and masks. The first parameter is an image handle.

---

## PDF_Image_AddSMask

### Syntax

```4d
$result:=PDF_Image_AddSMask ( image ; smask )
```

| Parameter | Type | Description |
|---|---|---|
| `image` | Text | Image handle from one of the `PDF_Load...Image...` commands. |
| `smask` | Text | Gray image handle used as alpha. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Adds a soft mask (alpha) image.

Wraps libharu `HPDF_Image_AddSMask`.

---

## PDF_Image_GetBitsPerComponent

### Syntax

```4d
$result:=PDF_Image_GetBitsPerComponent ( image )
```

| Parameter | Type | Description |
|---|---|---|
| `image` | Text | Image handle from one of the `PDF_Load...Image...` commands. |
| Result | Longint | Bits per component. |

### Description

Returns the bits per color component.

Wraps libharu `HPDF_Image_GetBitsPerComponent`.

---

## PDF_Image_GetColorSpace

### Syntax

```4d
$result:=PDF_Image_GetColorSpace ( image )
```

| Parameter | Type | Description |
|---|---|---|
| `image` | Text | Image handle from one of the `PDF_Load...Image...` commands. |
| Result | Text | Color-space name. |

### Description

Returns the color-space name of the image (`"DeviceRGB"`, ...).

Returns `""` for an empty handle. **Before this release that crashed 4D.**

Wraps libharu `HPDF_Image_GetColorSpace`.

---

## PDF_Image_GetHeight

### Syntax

```4d
$result:=PDF_Image_GetHeight ( image )
```

| Parameter | Type | Description |
|---|---|---|
| `image` | Text | Image handle from one of the `PDF_Load...Image...` commands. |
| Result | Longint | Height in pixels. |

### Description

Returns the image height in pixels.

Wraps libharu `HPDF_Image_GetHeight`.

---

## PDF_Image_GetSize

### Syntax

```4d
$result:=PDF_Image_GetSize ( image ; width ; height )
```

| Parameter | Type | Description |
|---|---|---|
| `image` | Text | Image handle from one of the `PDF_Load...Image...` commands. |
| `width` | Real | Receives the width. |
| `height` | Real | Receives the height. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Returns the image size in pixels.

Wraps libharu `HPDF_Image_GetSize2`.

---

## PDF_Image_GetWidth

### Syntax

```4d
$result:=PDF_Image_GetWidth ( image )
```

| Parameter | Type | Description |
|---|---|---|
| `image` | Text | Image handle from one of the `PDF_Load...Image...` commands. |
| Result | Longint | Width in pixels. |

### Description

Returns the image width in pixels.

Wraps libharu `HPDF_Image_GetWidth`.

---

## PDF_Image_SetColorMask

### Syntax

```4d
$result:=PDF_Image_SetColorMask ( image ; rmin ; rmax ; gmin ; gmax ; bmin ; bmax )
```

| Parameter | Type | Description |
|---|---|---|
| `image` | Text | Image handle from one of the `PDF_Load...Image...` commands. |
| `rmin` | Longint | Red min. |
| `rmax` | Longint | Red max. |
| `gmin` | Longint | Green min. |
| `gmax` | Longint | Green max. |
| `bmin` | Longint | Blue min. |
| `bmax` | Longint | Blue max. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Makes a color range of the image transparent.

Wraps libharu `HPDF_Image_SetColorMask`.

---

## PDF_Image_SetMaskImage

### Syntax

```4d
$result:=PDF_Image_SetMaskImage ( image ; mask_image )
```

| Parameter | Type | Description |
|---|---|---|
| `image` | Text | Image handle from one of the `PDF_Load...Image...` commands. |
| `mask_image` | Text | Mask image handle (1 bit per component). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Uses another image as a stencil mask.

Wraps libharu `HPDF_Image_SetMaskImage`.

## Annotation commands

Properties of annotations created with the `PDF_Page_Create...Annot` commands.

---

## PDF_Annot_SetCMYKColor

### Syntax

```4d
$result:=PDF_Annot_SetCMYKColor ( annot ; c ; m ; y ; k )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `c` | Real | Cyan, 0 to 1. |
| `m` | Real | Magenta. |
| `y` | Real | Yellow. |
| `k` | Real | Black. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the color of an annotation in CMYK.

Wraps libharu `HPDF_Annot_SetCMYKColor`.

---

## PDF_Annot_SetGrayColor

### Syntax

```4d
$result:=PDF_Annot_SetGrayColor ( annot ; gray )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `gray` | Real | Gray level, 0 to 1. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the color of an annotation in gray.

Wraps libharu `HPDF_Annot_SetGrayColor`.

---

## PDF_Annot_SetNoColor

### Syntax

```4d
$result:=PDF_Annot_SetNoColor ( annot )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Removes the color of an annotation.

Wraps libharu `HPDF_Annot_SetNoColor`.

---

## PDF_Annot_SetRGBColor

### Syntax

```4d
$result:=PDF_Annot_SetRGBColor ( annot ; r ; g ; b )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `r` | Real | Red, 0 to 1. |
| `g` | Real | Green, 0 to 1. |
| `b` | Real | Blue, 0 to 1. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the color of an annotation in RGB.

Wraps libharu `HPDF_Annot_SetRGBColor`.

---

## PDF_Annotation_SetBorderStyle

### Syntax

```4d
$result:=PDF_Annotation_SetBorderStyle ( annot ; subtype ; width ; dash_on ; dash_off ; dash_phase )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `subtype` | Longint | An `HPDF_BS_*` constant. |
| `width` | Real | Border width. |
| `dash_on` | Longint | Dash length. |
| `dash_off` | Longint | Gap length. |
| `dash_phase` | Longint | Dash phase. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the border style of an annotation.

Wraps libharu `HPDF_Annotation_SetBorderStyle`.

---

## PDF_FreeAnnot_Set2PointCallout

### Syntax

```4d
$result:=PDF_FreeAnnot_Set2PointCallout ( annot ; start_x ; start_y ; end_x ; end_y )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `start_x` | Real | Start x. |
| `start_y` | Real | Start y. |
| `end_x` | Real | End x. |
| `end_y` | Real | End y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets a two-point callout line on a free-text annotation.

Wraps libharu `HPDF_FreeTextAnnot_Set2PointCalloutLine`.

---

## PDF_FreeAnnot_Set3PointCallout

### Syntax

```4d
$result:=PDF_FreeAnnot_Set3PointCallout ( annot ; start_x ; start_y ; knee_x ; knee_y ; end_x ; end_y )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `start_x` | Real | Start x. |
| `start_y` | Real | Start y. |
| `knee_x` | Real | Knee x. |
| `knee_y` | Real | Knee y. |
| `end_x` | Real | End x. |
| `end_y` | Real | End y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets a three-point callout line on a free-text annotation.

Wraps libharu `HPDF_FreeTextAnnot_Set3PointCalloutLine`.

---

## PDF_FreeAnnot_SetDefaultStyle

### Syntax

```4d
$result:=PDF_FreeAnnot_SetDefaultStyle ( annot ; style )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `style` | Text | Style string (UTF-8). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the default style string of a free-text annotation.

Wraps libharu `HPDF_FreeTextAnnot_SetDefaultStyle`.

---

## PDF_FreeAnnot_SetEndingStyle

### Syntax

```4d
$result:=PDF_FreeAnnot_SetEndingStyle ( annot ; start_style ; end_style )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `start_style` | Longint | An `HPDF_LINE_ANNOT_*` ending style. |
| `end_style` | Longint | An `HPDF_LINE_ANNOT_*` ending style. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the line-ending styles of a free-text annotation.

Uses libharu `HPDF_FreeTextAnnot_SetLineEndingStyle`.

Wraps libharu `HPDF_FreeTextAnnot_SetLineEndingStyle`.

---

## PDF_LineAnnot_SetCaption

### Syntax

```4d
$result:=PDF_LineAnnot_SetCaption ( annot ; show_caption ; position ; horizontal_offset ; vertical_offset )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `show_caption` | Longint | `HPDF_TRUE` to show the caption. |
| `position` | Longint | `HPDF_LINE_ANNOT_CAP_INLINE` or `HPDF_LINE_ANNOT_CAP_TOP`. |
| `horizontal_offset` | Longint | Horizontal offset. |
| `vertical_offset` | Longint | Vertical offset. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the caption of a line annotation.

Wraps libharu `HPDF_LineAnnot_SetCaption`.

---

## PDF_LineAnnot_SetLeader

### Syntax

```4d
$result:=PDF_LineAnnot_SetLeader ( annot ; leader_length ; leader_ext_length ; leader_offset )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `leader_length` | Longint | Leader length. |
| `leader_ext_length` | Longint | Leader extension. |
| `leader_offset` | Longint | Leader offset. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the leader lines of a line annotation.

Wraps libharu `HPDF_LineAnnot_SetLeader`.

---

## PDF_LineAnnot_SetPosition

### Syntax

```4d
$result:=PDF_LineAnnot_SetPosition ( annot ; start_x ; start_y ; start_style ; end_x ; end_y ; end_style )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `start_x` | Real | Start x. |
| `start_y` | Real | Start y. |
| `start_style` | Longint | An `HPDF_LINE_ANNOT_*` ending style. |
| `end_x` | Real | End x. |
| `end_y` | Real | End y. |
| `end_style` | Longint | An `HPDF_LINE_ANNOT_*` ending style. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the end points and ending styles of a line annotation.

Wraps libharu `HPDF_LineAnnot_SetPosition`.

---

## PDF_LinkAnnot_SetBorderStyle

### Syntax

```4d
$result:=PDF_LinkAnnot_SetBorderStyle ( annot ; width ; dash_on ; dash_off )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `width` | Real | Border width. |
| `dash_on` | Longint | Dash length. |
| `dash_off` | Longint | Gap length. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the border of a link annotation.

Wraps libharu `HPDF_LinkAnnot_SetBorderStyle`.

---

## PDF_LinkAnnot_SetHighlightMode

### Syntax

```4d
$result:=PDF_LinkAnnot_SetHighlightMode ( annot ; mode )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `mode` | Longint | An `HPDF_ANNOT_*` highlight constant (`HPDF_ANNOT_NO_HIGHTLIGHT`, `HPDF_ANNOT_INVERT_BOX`, ...). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets how a link annotation is highlighted when clicked.

Wraps libharu `HPDF_LinkAnnot_SetHighlightMode`.

---

## PDF_MarkupAnnot_SetAlpha

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetAlpha ( annot ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `value` | Real | Opacity, 0 to 1. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the opacity of a markup annotation.

Uses libharu `HPDF_MarkupAnnot_SetTransparency`.

Wraps libharu `HPDF_MarkupAnnot_SetTransparency`.

---

## PDF_MarkupAnnot_SetCloudEffect

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetCloudEffect ( annot ; intensity )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `intensity` | Longint | Cloud intensity (0 to 2). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the cloud border effect of a markup annotation.

Wraps libharu `HPDF_MarkupAnnot_SetCloudEffect`.

---

## PDF_MarkupAnnot_SetCMYKColor

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetCMYKColor ( annot ; c ; m ; y ; k )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `c` | Real | Cyan, 0 to 1. |
| `m` | Real | Magenta. |
| `y` | Real | Yellow. |
| `k` | Real | Black. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the interior color of a markup annotation in CMYK.

Wraps libharu `HPDF_MarkupAnnot_SetInteriorCMYKColor`.

---

## PDF_MarkupAnnot_SetDate

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetDate ( annot ; date ; time ; utc_offset ; offset_hours ; offset_minutes )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `date` | Date | Date. |
| `time` | Time | Time of day. |
| `utc_offset` | Longint | An `HPDF_UTC_OFFSET_*` constant. |
| `offset_hours` | Longint | Offset hours. |
| `offset_minutes` | Longint | Offset minutes. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the creation date of a markup annotation.

Wraps libharu `HPDF_MarkupAnnot_SetCreationDate`.

---

## PDF_MarkupAnnot_SetGrayColor

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetGrayColor ( annot ; gray )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `gray` | Real | Gray level, 0 to 1. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the interior color of a markup annotation in gray.

Wraps libharu `HPDF_MarkupAnnot_SetInteriorGrayColor`.

---

## PDF_MarkupAnnot_SetIntent

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetIntent ( annot ; intent )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `intent` | Longint | An intent constant (`HPDF_ANNOT_FREETEXTCALLOUT`, `HPDF_ANNOT_LINEARROW`, ...). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the intent of a markup annotation.

Wraps libharu `HPDF_MarkupAnnot_SetIntent`.

---

## PDF_MarkupAnnot_SetNoColor

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetNoColor ( annot )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Makes the interior of a markup annotation transparent.

Wraps libharu `HPDF_MarkupAnnot_SetInteriorTransparent`.

---

## PDF_MarkupAnnot_SetPopup

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetPopup ( annot ; popup )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `popup` | Text | Popup annotation handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Attaches a popup annotation to a markup annotation.

Wraps libharu `HPDF_MarkupAnnot_SetPopup`.

---

## PDF_MarkupAnnot_SetQuadPoints

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetQuadPoints ( annot ; lb_x ; lb_y ; rb_x ; rb_y ; rt_x ; rt_y ; lt_x ; lt_y )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `lb_x` | Real | Left-bottom x. |
| `lb_y` | Real | Left-bottom y. |
| `rb_x` | Real | Right-bottom x. |
| `rb_y` | Real | Right-bottom y. |
| `rt_x` | Real | Right-top x. |
| `rt_y` | Real | Right-top y. |
| `lt_x` | Real | Left-top x. |
| `lt_y` | Real | Left-top y. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the quadrilateral of a text-markup annotation (highlight, underline, ...).

Uses libharu `HPDF_TextMarkupAnnot_SetQuadPoints`.

Wraps libharu `HPDF_TextMarkupAnnot_SetQuadPoints`.

---

## PDF_MarkupAnnot_SetRectDiff

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetRectDiff ( annot ; left ; bottom ; right ; top )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `left` | Real | Left offset. |
| `bottom` | Real | Bottom offset. |
| `right` | Real | Right offset. |
| `top` | Real | Top offset. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the inner rectangle offsets of a markup annotation.

Wraps libharu `HPDF_MarkupAnnot_SetRectDiff`.

---

## PDF_MarkupAnnot_SetRGBColor

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetRGBColor ( annot ; r ; g ; b )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `r` | Real | Red, 0 to 1. |
| `g` | Real | Green. |
| `b` | Real | Blue. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the interior color of a markup annotation in RGB.

Wraps libharu `HPDF_MarkupAnnot_SetInteriorRGBColor`.

---

## PDF_MarkupAnnot_SetSubject

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetSubject ( annot ; subject )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `subject` | Text | Subject (UTF-8). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the subject of a markup annotation.

Wraps libharu `HPDF_MarkupAnnot_SetSubject`.

---

## PDF_MarkupAnnot_SetTitle

### Syntax

```4d
$result:=PDF_MarkupAnnot_SetTitle ( annot ; title )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `title` | Text | Title (UTF-8). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the title (author) of a markup annotation.

Wraps libharu `HPDF_MarkupAnnot_SetTitle`.

---

## PDF_PopupAnnot_SetOpened

### Syntax

```4d
$result:=PDF_PopupAnnot_SetOpened ( annot ; opened )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `opened` | Longint | `HPDF_TRUE` or `HPDF_FALSE`. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets whether a popup annotation is initially open.

Wraps libharu `HPDF_PopupAnnot_SetOpened`.

---

## PDF_TextAnnot_SetIcon

### Syntax

```4d
$result:=PDF_TextAnnot_SetIcon ( annot ; icon )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `icon` | Longint | An `HPDF_ANNOT_ICON_*` constant. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the icon of a text annotation.

Wraps libharu `HPDF_TextAnnot_SetIcon`.

---

## PDF_TextAnnot_SetOpened

### Syntax

```4d
$result:=PDF_TextAnnot_SetOpened ( annot ; opened )
```

| Parameter | Type | Description |
|---|---|---|
| `annot` | Text | Annotation handle. |
| `opened` | Longint | `HPDF_TRUE` or `HPDF_FALSE`. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets whether a text annotation is initially open.

Wraps libharu `HPDF_TextAnnot_SetOpened`.

## Outline commands

Outline (bookmark) properties.

---

## PDF_Outline_SetDestination

### Syntax

```4d
$result:=PDF_Outline_SetDestination ( outline ; destination )
```

| Parameter | Type | Description |
|---|---|---|
| `outline` | Text | Outline handle from [PDF_CreateOutline](#pdf_createoutline). |
| `destination` | Text | Destination handle. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the destination an outline entry jumps to.

Wraps libharu `HPDF_Outline_SetDestination`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## PDF_Outline_SetOpened

### Syntax

```4d
$result:=PDF_Outline_SetOpened ( outline ; opened )
```

| Parameter | Type | Description |
|---|---|---|
| `outline` | Text | Outline handle from [PDF_CreateOutline](#pdf_createoutline). |
| `opened` | Longint | `HPDF_TRUE` or `HPDF_FALSE`. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets whether an outline entry is initially expanded.

Wraps libharu `HPDF_Outline_SetOpened`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

## Destination commands

How a destination displays its page. The first parameter is a destination handle.

---

## PDF_Destination_SetFit

### Syntax

```4d
$result:=PDF_Destination_SetFit ( destination )
```

| Parameter | Type | Description |
|---|---|---|
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fits the whole page in the window.

Wraps libharu `HPDF_Destination_SetFit`.

---

## PDF_Destination_SetFitB

### Syntax

```4d
$result:=PDF_Destination_SetFitB ( destination )
```

| Parameter | Type | Description |
|---|---|---|
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fits the page bounding box in the window.

Wraps libharu `HPDF_Destination_SetFitB`.

---

## PDF_Destination_SetFitBH

### Syntax

```4d
$result:=PDF_Destination_SetFitBH ( destination ; top )
```

| Parameter | Type | Description |
|---|---|---|
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| `top` | Real | Top coordinate. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fits the bounding-box width, with the given top coordinate at the top.

Wraps libharu `HPDF_Destination_SetFitBH`.

---

## PDF_Destination_SetFitBV

### Syntax

```4d
$result:=PDF_Destination_SetFitBV ( destination ; left )
```

| Parameter | Type | Description |
|---|---|---|
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| `left` | Real | Left coordinate. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fits the bounding-box height, with the given left coordinate at the left.

Wraps libharu `HPDF_Destination_SetFitBV`.

---

## PDF_Destination_SetFitH

### Syntax

```4d
$result:=PDF_Destination_SetFitH ( destination ; top )
```

| Parameter | Type | Description |
|---|---|---|
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| `top` | Real | Top coordinate. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fits the page width, with the given top coordinate at the top of the window.

Wraps libharu `HPDF_Destination_SetFitH`.

---

## PDF_Destination_SetFitR

### Syntax

```4d
$result:=PDF_Destination_SetFitR ( destination ; left ; bottom ; right ; top )
```

| Parameter | Type | Description |
|---|---|---|
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| `left` | Real | Left. |
| `bottom` | Real | Bottom. |
| `right` | Real | Right. |
| `top` | Real | Top. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fits a rectangle in the window.

Wraps libharu `HPDF_Destination_SetFitR`.

---

## PDF_Destination_SetFitV

### Syntax

```4d
$result:=PDF_Destination_SetFitV ( destination ; left )
```

| Parameter | Type | Description |
|---|---|---|
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| `left` | Real | Left coordinate. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Fits the page height, with the given left coordinate at the left of the window.

Wraps libharu `HPDF_Destination_SetFitV`.

---

## PDF_Destination_SetXYZ

### Syntax

```4d
$result:=PDF_Destination_SetXYZ ( destination ; left ; top ; zoom )
```

| Parameter | Type | Description |
|---|---|---|
| `destination` | Text | Destination handle from [PDF_Page_CreateDestination](#pdf_page_createdestination). |
| `left` | Real | Left coordinate. |
| `top` | Real | Top coordinate. |
| `zoom` | Real | Zoom factor (1 = 100%). |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Shows the page at a position and zoom.

Wraps libharu `HPDF_Destination_SetXYZ`.

## Extended Graphics State commands

Transparency and blend mode, applied with [PDF_Page_SetExtGState](#pdf_page_setextgstate).

---

## PDF_ExtGState_SetAlphaFill

### Syntax

```4d
$result:=PDF_ExtGState_SetAlphaFill ( ext_gstate ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `ext_gstate` | Text | Extended graphics state handle from [PDF_CreateExtGState](#pdf_createextgstate). |
| `value` | Real | Opacity, 0 to 1. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the fill opacity of an extended graphics state.

Wraps libharu `HPDF_ExtGState_SetAlphaFill`.

---

## PDF_ExtGState_SetAlphaStroke

### Syntax

```4d
$result:=PDF_ExtGState_SetAlphaStroke ( ext_gstate ; value )
```

| Parameter | Type | Description |
|---|---|---|
| `ext_gstate` | Text | Extended graphics state handle from [PDF_CreateExtGState](#pdf_createextgstate). |
| `value` | Real | Opacity, 0 to 1. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the stroke opacity of an extended graphics state.

Wraps libharu `HPDF_ExtGState_SetAlphaStroke`.

---

## PDF_ExtGState_SetBlendMode

### Syntax

```4d
$result:=PDF_ExtGState_SetBlendMode ( ext_gstate ; mode )
```

| Parameter | Type | Description |
|---|---|---|
| `ext_gstate` | Text | Extended graphics state handle from [PDF_CreateExtGState](#pdf_createextgstate). |
| `mode` | Longint | libharu `HPDF_BlendMode` value (0 = normal). No 4D constants are defined for it. |
| Result | Longint | libharu status: `0` (`HPDF_OK`) on success. See [Error handling](#error-handling--troubleshooting) for why failures usually also return `0`. |

### Description

Sets the blend mode of an extended graphics state.

Wraps libharu `HPDF_ExtGState_SetBlendMode`.

## Global commands

Plugin-wide settings.

---

## PDF_Global_GetEncoding

### Syntax

```4d
$result:=PDF_Global_GetEncoding
```

| Parameter | Type | Description |
|---|---|---|
| Result | Longint | 4D character-set number. |

### Description

Returns the character set set by [PDF_Global_SetEncoding](#pdf_global_setencoding) (default `HPDF_DEFAULT`, -2).

---

## PDF_Global_SetEncoding

### Syntax

```4d
PDF_Global_SetEncoding ( charset )
```

| Parameter | Type | Description |
|---|---|---|
| `charset` | Longint | A 4D character-set number; the `HPDF_*` encoding constants (`HPDF_SHIFT_JIS`, `HPDF_ISO_8859_1`, ...) are those numbers. |
| Result | | None. |

### Description

Sets the character set the plugin converts drawn text to, for every document in the 4D session.

It applies to the text of the drawing and annotation commands (`PDF_Page_ShowText`, `PDF_Page_TextOut`, `PDF_Page_TextRect`, `PDF_Page_TextWidth`, `PDF_Page_MeasureText`, the `PDF_Page_Create...Annot` texts). It is one value shared by all processes, not stored per document. Pick the character set that matches the encoding of the font you draw with, e.g. `HPDF_SHIFT_JIS` with `"90ms-RKSJ-H"`.

### Example

Used in the worked examples: [jpfont_demo](#jpfont_demo).

---

## Constants

Installed by the plugin in the `Haru` constant theme (from `constants.xlf`):

| Constants | Values |
|---|---|
| `HPDF_TALIGN_LEFT`, `HPDF_TALIGN_RIGHT`, `HPDF_TALIGN_CENTER`, `HPDF_TALIGN_JUSTIFY` | 0, 1, 2, 3 |
| `HPDF_FILL`, `HPDF_STROKE`, `HPDF_FILL_THEN_STROKE`, `HPDF_INVISIBLE`, `HPDF_FILL_CLIPPING`, `HPDF_STROKE_CLIPPING`, `HPDF_FILL_STROKE_CLIPPING`, `HPDF_CLIPPING` | 0, 1, 2, 3, 4, 5, 6, 7 |
| `HPDF_MITER_JOIN`, `HPDF_ROUND_JOIN`, `HPDF_BEVEL_JOIN` | 0, 1, 2 |
| `HPDF_BUTT_END`, `HPDF_ROUND_END`, `HPDF_PROJECTING_SQUARE_END` | 0, 1, 2 |
| `HPDF_BS_SOLID`, `HPDF_BS_DASHED`, `HPDF_BS_BEVELED`, `HPDF_BS_INSET`, `HPDF_BS_UNDERLINED` | 0, 1, 2, 3, 4 |
| `HPDF_ANNOT_ICON_COMMENT`, `HPDF_ANNOT_ICON_KEY`, `HPDF_ANNOT_ICON_NOTE`, `HPDF_ANNOT_ICON_HELP`, `HPDF_ANNOT_ICON_NEW_PARAGRAPH`, `HPDF_ANNOT_ICON_PARAGRAPH`, `HPDF_ANNOT_ICON_INSERT`, `HPDF_ANNOT_ICON_EOF` | 0, 1, 2, 3, 4, 5, 6, 7 |
| `HPDF_ANNOT_NO_HIGHTLIGHT`, `HPDF_ANNOT_INVERT_BOX`, `HPDF_ANNOT_INVERT_BORDER`, `HPDF_ANNOT_DOWN_APPEARANCE` | 0, 1, 2, 3 |
| `HPDF_DEFAULT`, `HPDF_MAC_ROMAN`, `HPDF_SHIFT_JIS`, `HPDF_BIG5`, `HPDF_EUC_KR`, `HPDF_KOI8R`, `HPDF_ISO_8859_1`, `HPDF_ISO_8859_2`, `HPDF_ISO_8859_4`, `HPDF_ISO_8859_5`, `eVTC_ISO_8859_6`, `HPDF_ISO_8859_7`, `HPDF_ISO_8859_8`, `HPDF_ISO_8859_9`, `HPDF_GB2312`, `HPDF_GB2312_80`, `HPDF_ISO_8859_15` | -2, 100, 1000, 1002, 1003, 1004, 1005, 1006, 1008, 1009, 1010, 1011, 1012, 1013, 1016, 1017, 1018 |
| `HPDF_FALSE`, `HPDF_TRUE` | 0, 1 |
| `HPDF_PAGE_MODE_USE_NONE`, `HPDF_PAGE_MODE_USE_OUTLINE`, `HPDF_PAGE_MODE_USE_THUMBS`, `HPDF_PAGE_MODE_FULL_SCREEN` | 0, 1, 2, 3 |
| `HPDF_PAGE_LAYOUT_SINGLE`, `HPDF_PAGE_LAYOUT_1COLUMN`, `HPDF_PAGE_LAYOUT_2COLUMN_LEFT`, `HPDF_PAGE_LAYOUT_2COLUMN_RIGHT`, `HPDF_PAGE_LAYOUT_2PAGE_LEFT`, `HPDF_PAGE_LAYOUT_2PAGE_RIGHT` | 0, 1, 2, 3, 4, 5 |
| `HPDF_COMP_NONE`, `HPDF_COMP_TEXT`, `HPDF_COMP_IMAGE`, `HPDF_COMP_METADATA`, `HPDF_COMP_ALL` | 0, 1, 2, 4, 15 |
| `HPDF_ENCRYPT_R2`, `HPDF_ENCRYPT_R3` | 2, 3 |
| `HPDF_ENABLE_READ`, `HPDF_ENABLE_PRINT`, `HPDF_ENABLE_EDIT_ALL`, `HPDF_ENABLE_COPY`, `HPDF_ENABLE_EDIT` | 0, 4, 8, 16, 32 |
| `HPDF_INFO_CREATION_DATE`, `HPDF_INFO_MOD_DATE` | 0, 1 |
| `HPDF_UTC_OFFSET_NONE`, `HPDF_UTC_OFFSET_POSITIVE`, `HPDF_UTC_OFFSET_NEGATIVE`, `HPDF_UTC_OFFSET_ZERO` | 0, 1, 2, 3 |
| `HPDF_INFO_AUTHOR`, `HPDF_INFO_CREATOR`, `HPDF_INFO_PRODUCER`, `HPDF_INFO_TITLE`, `HPDF_INFO_SUBJECT`, `HPDF_INFO_KEYWORDS`, `HPDF_INFO_TRAPPED`, `HPDF_INFO_GTS_PDFX` | 2, 3, 4, 5, 6, 7, 8, 9 |
| `HPDF_TS_WIPE_RIGHT`, `HPDF_TS_WIPE_UP`, `HPDF_TS_WIPE_LEFT`, `HPDF_TS_WIPE_DOWN`, `HPDF_TS_BARN_DOORS_H_OUT`, `HPDF_TS_BARN_DOORS_H_IN`, `HPDF_TS_BARN_DOORS_V_OUT`, `HPDF_TS_BARN_DOORS_V_IN`, `HPDF_TS_BOX_OUT`, `HPDF_TS_BOX_IN`, `HPDF_TS_BLINDS_HORIZONTAL`, `HPDF_TS_BLINDS_VERTICAL`, `HPDF_TS_DISSOLVE`, `HPDF_TS_GLITTER_RIGHT`, `HPDF_TS_GLITTER_DOWN`, `HPDF_TS_GLITTER_TL_TO_BR`, `HPDF_TS_REPLACE` | 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 |
| `HPDF_PAGE_SIZE_LETTER`, `HPDF_PAGE_SIZE_LEGAL`, `HPDF_PAGE_SIZE_A3`, `HPDF_PAGE_SIZE_A4`, `HPDF_PAGE_SIZE_A5`, `HPDF_PAGE_SIZE_B4`, `HPDF_PAGE_SIZE_B5`, `HPDF_PAGE_SIZE_EXECUTIVE`, `HPDF_PAGE_SIZE_US4x6`, `HPDF_PAGE_SIZE_US4x8`, `HPDF_PAGE_SIZE_US5x7`, `HPDF_PAGE_SIZE_COMM10` | 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 |
| `HPDF_PAGE_PORTRAIT`, `HPDF_PAGE_LANDSCAPE` | 0, 1 |
| `HPDF_NUM_STYLE_DECIMAL`, `HPDF_NUM_STYLE_UPPER_ROMAN`, `HPDF_NUM_STYLE_LOWER_ROMAN`, `HPDF_NUM_STYLE_UPPER_LETTERS`, `HPDF_NUM_STYLE_LOWER_LETTERS` | 0, 1, 2, 3, 4 |
| `HPDF_ANNOT_TEXT_NOTES`, `HPDF_ANNOT_STRIKE_OUT`, `HPDF_ANNOT_LINK`, `HPDF_ANNOT_SOUND`, `HPDF_ANNOT_FREE_TEXT`, `HPDF_ANNOT_STAMP`, `HPDF_ANNOT_SQUARE`, `HPDF_ANNOT_CIRCLE`, `HPDF_ANNOT_HIGHTLIGHT`, `HPDF_ANNOT_UNDERLINE`, `HPDF_ANNOT_INK`, `HPDF_ANNOT_FILE_ATTACHMENT`, `HPDF_ANNOT_POPUP`, `HPDF_ANNOT_3D`, `HPDF_ANNOT_SQUIGGLY`, `HPDF_ANNOT_LINE`, `HPDF_ANNOT_PROJECTION` | 0, 7.0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16 |
| `HPDF_STAMP_ANNOT_APPROVED`, `HPDF_STAMP_ANNOT_EXPERIMENTAL`, `HPDF_STAMP_ANNOT_NOTAPPROVED`, `HPDF_STAMP_ANNOT_ASIS`, `HPDF_STAMP_ANNOT_EXPIRED`, `HPDF_STAMP_ANNOT_NOTFORPUBLIC`, `HPDF_STAMP_ANNOT_CONFIDENTIAL`, `HPDF_STAMP_ANNOT_FINAL`, `HPDF_STAMP_ANNOT_SOLD`, `HPDF_STAMP_ANNOT_DEPARTMENTAL`, `HPDF_STAMP_ANNOT_FORCOMMENT`, `HPDF_STAMP_ANNOT_TOPSECRET`, `HPDF_STAMP_ANNOT_DRAFT`, `HPDF_STAMP_ANNOT_FORPUBLIC` | 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 |
| `HPDF_ANNOT_FREETEXTCALLOUT`, `HPDF_ANNOT_FREETEXTTYPEWRITER`, `HPDF_ANNOT_LINEARROW`, `HPDF_ANNOT_LINEDIMENSION`, `HPDF_ANNOT_POLYGONCLOUD`, `HPDF_ANNOT_POLYLINEDIMENSION`, `HPDF_ANNOT_POLYGONDIMENSION` | 0, 1, 2, 3, 4, 5, 6 |
| `HPDF_LINE_ANNOT_CAP_INLINE`, `HPDF_LINE_ANNOT_CAP_TOP` | 0, 1 |
| `HPDF_LINE_ANNOT_NONE`, `HPDF_LINE_ANNOT_SQUARE`, `HPDF_LINE_ANNOT_CIRCLE`, `HPDF_LINE_ANNOT_DIAMOND`, `HPDF_LINE_ANNOT_OPENARROW`, `HPDF_LINE_ANNOT_CLOSEDARROW`, `HPDF_LINE_ANNOT_BUTT`, `HPDF_LINE_ANNOT_ROPENARROW`, `HPDF_LINE_ANNOT_RCLOSEDARROW`, `HPDF_LINE_ANNOT_SLASH` | 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 |

Two names deviate from the libharu pattern and are listed as installed: `eVTC_ISO_8859_6` (1010, ISO 8859-6) and `HPDF_ANNOT_STRIKE_OUT` (declared with the value `7.0`). `HPDF_ANNOT_HIGHTLIGHT` and `HPDF_ANNOT_NO_HIGHTLIGHT` keep libharu's spelling.

---

## Worked examples

These methods come from the previous version of this README; they port libharu's demo programs to 4D. They call project methods of the sample database that are not reproduced here (`print_margin`, `print_title`, `draw_line`, `draw_rect`, `show_description`, `show_stripe_pattern`); those only draw labels and frames with the commands documented above. The test database `Haru.4dbase` is a binary database, so its methods are not quoted here.

### jpfont_demo

```4d
  //based on sample code found at:
  //http://libharu.org/demo/jpfont_demo.c

$page_title:="JP font demo"

$U30A2:=Char(0x30A2)
$U30E1:=Char(0x30E1)
$U30F3:=Char(0x30F3)
$U30DC:=Char(0x30DC)
$U8D64:=Char(0x8D64)
$U3044:=Char(0x3044)
$U306A:=Char(0x306A)
$U3042:=Char(0x3042)
$U3046:=Char(0x3046)
$U3048:=Char(0x3048)
$U304A:=Char(0x304A)
$U3002:=Char(0x3002)
$U6D6E:=Char(0x6D6E)
$U304D:=Char(0x304D)
$U85FB:=Char(0x85FB)
$U306B:=Char(0x306B)
$U5C0F:=Char(0x5C0F)
$U30A8:=Char(0x30A8)
$U30D3:=Char(0x30D3)
$U3082:=Char(0x3082)
$U3088:=Char(0x3088)
$U3067:=Char(0x3067)
$U308B:=Char(0x308B)
$samp_text:=$U30A2+$U30E1+$U30F3+$U30DC+$U8D64+$U3044+$U306A+$U3042+$U3044+$U3046+$U3048+$U304A+$U3002+$U6D6E+$U304D+$U85FB+$U306B+$U5C0F+$U30A8+$U30D3+$U3082+$U304A+$U3088+$U3044+$U3067+$U308B+$U3002

ARRAY TEXT($font_names;8)
  //Mincho on Mac, Mincyo on Windows; the plugin absorbs the difference
  //on Windows, Mincho/Mincyo (notP) seems to default to Meiryo in Edge browser
$font_names{1}:="MS-Mincho"
$font_names{2}:="MS-Mincho,Bold"
$font_names{3}:="MS-PMincho"
$font_names{4}:="MS-PMincho,Bold"
$font_names{5}:="MS-Gothic"
$font_names{6}:="MS-Gothic,Bold"
$font_names{7}:="MS-PGothic"
$font_names{8}:="MS-PGothic,Bold"

ARRAY TEXT($font_encodings;8)
$font_encodings{1}:="90ms-RKSJ-H"
$font_encodings{2}:="90ms-RKSJ-H"
$font_encodings{3}:="90msp-RKSJ-H"
$font_encodings{4}:="90msp-RKSJ-H"
$font_encodings{5}:="90ms-RKSJ-H"
$font_encodings{6}:="90ms-RKSJ-H"
$font_encodings{7}:="90msp-RKSJ-H"
$font_encodings{8}:="90msp-RKSJ-H"

$pdf:=PDF_New 

PDF_Global_SetEncoding (HPDF_SHIFT_JIS)  //4D plugin sdk font number
PDF_UseJPEncodings ($pdf)
PDF_UseJPFonts ($pdf)

PDF_SetCompressionMode ($pdf;HPDF_COMP_ALL)

PDF_SetPageMode ($pdf;HPDF_PAGE_MODE_USE_OUTLINE)

$root:=PDF_CreateOutline ($pdf;"";"JP font demo";"")
PDF_Outline_SetOpened ($root;HPDF_TRUE)

For ($i;1;Size of array($font_names))
	
	$page:=PDF_AddPage ($pdf)
	
	$outline:=PDF_CreateOutline ($pdf;$root;$font_names{$i})
	$dst:=PDF_Page_CreateDestination ($page)
	PDF_Outline_SetDestination ($outline;$dst)
	
	$title_font:=PDF_GetFont ($pdf;"Helvetica")
	PDF_Page_SetFontAndSize ($page;$title_font;10)
	
	PDF_Page_BeginText ($page)
	
	PDF_Page_MoveTextPos ($page;10;190)
	PDF_Page_ShowText ($page;$font_names{$i})
	
	$font:=PDF_GetFont ($pdf;$font_names{$i};$font_encodings{$i})
	
	PDF_Page_SetFontAndSize ($page;$font;15)
	PDF_Page_MoveTextPos ($page;10;-20)
	PDF_Page_ShowText ($page;"abcdefghijklmnopqrstuvwxyz")
	PDF_Page_MoveTextPos ($page;0;-20)
	PDF_Page_ShowText ($page;"ABCDEFGHIJKLMNOPQRSTUVWXYZ")
	PDF_Page_MoveTextPos ($page;0;-20)
	PDF_Page_ShowText ($page;"1234567890")
	PDF_Page_MoveTextPos ($page;0;-20)
	
	PDF_Page_SetFontAndSize ($page;$font;10)
	PDF_Page_ShowText ($page;$samp_text)
	PDF_Page_MoveTextPos ($page;0;-18)
	
	PDF_Page_SetFontAndSize ($page;$font;16)
	PDF_Page_ShowText ($page;$samp_text)
	PDF_Page_MoveTextPos ($page;0;-27)
	
	PDF_Page_SetFontAndSize ($page;$font;23)
	PDF_Page_ShowText ($page;$samp_text)
	PDF_Page_MoveTextPos ($page;0;-36)
	
	PDF_Page_SetFontAndSize ($page;$font;30)
	PDF_Page_ShowText ($page;$samp_text)
	
	C_REAL($x;$y)
	PDF_Page_GetCurrentTextPos ($page;$x;$y)
	
	PDF_Page_EndText ($page)
	
	PDF_Page_SetLineWidth ($page;0.5)
	
	$x_pos:=20
	
	For ($j;0;Length($samp_text)/2;30)
		
		PDF_Page_MoveTo ($page;$x_pos;$y-10)
		PDF_Page_LineTo ($page;$x_pos;$y-12)
		PDF_Page_Stroke ($page)
		
	End for 
	
	PDF_Page_SetWidth ($page;$x+20)
	PDF_Page_SetHeight ($page;210)
	
	PDF_Page_MoveTo ($page;10;210-25)
	PDF_Page_LineTo ($page;$x+10;210-25)
	PDF_Page_Stroke ($page)
	
	PDF_Page_MoveTo ($page;10;210-85)
	PDF_Page_LineTo ($page;$x+10;210-85)
	PDF_Page_Stroke ($page)
	
	PDF_Page_MoveTo ($page;10;$y-12)
	PDF_Page_LineTo ($page;$x+10;$y-12)
	PDF_Page_Stroke ($page)
	
End for 

  //note: on windows, this path can only contain ANSI-for-locale characters
$filePath:=System folder(Desktop)+"jpfont_demo.pdf"
PDF_SaveToFile ($pdf;$filePath)
  //PDF_SaveToStream ($pdf;$pdfData)

PDF_Free ($pdf)

OPEN URL($filePath)
```

### font_demo

```4d
  //based on sample code found at:
  //http://libharu.org/demo/font_demo.c

ARRAY TEXT($font_list;14)
$font_list{1}:="Courier"
$font_list{2}:="Courier-Bold"
$font_list{3}:="Courier-Oblique"
$font_list{4}:="Courier-BoldOblique"
$font_list{5}:="Helvetica"
$font_list{6}:="Helvetica-Bold"
$font_list{7}:="Helvetica-Oblique"
$font_list{8}:="Helvetica-BoldOblique"
$font_list{9}:="Times-Roman"
$font_list{10}:="Times-Bold"
$font_list{11}:="Times-Italic"
$font_list{12}:="Times-BoldItalic"
$font_list{13}:="Symbol"
$font_list{14}:="ZapfDingbats"

$page_title:="Font Demo"
$samp_text:="abcdefgABCDEFG12345!#$%&+-@?"

$pdf:=PDF_New 

PDF_SetCompressionMode ($pdf;HPDF_COMP_ALL)

$page:=PDF_AddPage ($pdf)

print_margin ($pdf;$page)

print_title ($pdf;$page;$page_title)

  //output subtitle.
$def_font:=PDF_GetFont ($pdf;"Helvetica")
$height:=PDF_Page_GetHeight ($page)
$err:=PDF_Page_BeginText ($page)
$err:=PDF_Page_SetFontAndSize ($page;$def_font;16)
$err:=PDF_Page_TextOut ($page;60;$height-80;"<Standerd Type1 fonts samples>")
$err:=PDF_Page_EndText ($page)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;60;$height-105)

For ($i;1;Size of array($font_list))
	$font:=PDF_GetFont ($pdf;$font_list{$i})
	  //print a label of text. 
	PDF_Page_SetFontAndSize ($page;$def_font;9)
	PDF_Page_ShowText ($page;$font_list{$i})
	PDF_Page_MoveTextPos ($page;0;-18)
	  //print a sample text.
	PDF_Page_SetFontAndSize ($page;$font;20)
	PDF_Page_ShowText ($page;$samp_text)
	PDF_Page_MoveTextPos ($page;0;-20)
End for 

  //note: on windows, this path can only contain ANSI-for-locale characters
$filePath:=System folder(Desktop)+"font_demo.pdf"
PDF_SaveToFile ($pdf;$filePath)
  //PDF_SaveToStream ($pdf;$pdfData)

PDF_Free ($pdf)

OPEN URL($filePath)
```

### line_demo

```4d
  //based on sample code found at:
  //http://libharu.org/demo/line_demo.c

$page_title:="Line Demo"
$samp_text:="abcdefgABCDEFG12345!#$%&+-@?"

$pdf:=PDF_New 

$font:=PDF_GetFont ($pdf;"Helvetica")

$page:=PDF_AddPage ($pdf)

PDF_Page_SetLineWidth ($page;1)
PDF_Page_Rectangle ($page;50;50;PDF_Page_GetWidth ($page)-100;PDF_Page_GetHeight ($page)-110)
PDF_Page_Stroke ($page)

print_title ($pdf;$page;$page_title)

PDF_Page_SetFontAndSize ($page;$font;10)

PDF_Page_SetLineWidth ($page;0)
draw_line ($page;60;770;"line width = 0")

PDF_Page_SetLineWidth ($page;1)
draw_line ($page;60;740;"line width = 1.0")

PDF_Page_SetLineWidth ($page;2)
draw_line ($page;60;710;"line width = 2.0")

PDF_Page_SetLineWidth ($page;1)

ARRAY LONGINT($DASH_MODE0;0)

ARRAY LONGINT($DASH_MODE1;1)
$DASH_MODE1{1}:=3

PDF_Page_SetDash ($page;$DASH_MODE1;1;1)
draw_line ($page;60;680;"dash_ptn=[3], phase=1 -- 2 on, 3 off, 3 on...")

ARRAY LONGINT($DASH_MODE2;2)
$DASH_MODE2{1}:=3
$DASH_MODE2{2}:=7

PDF_Page_SetDash ($page;$DASH_MODE2;2;2)
draw_line ($page;60;650;"dash_ptn=[7, 3], phase=2 -- 5 on 3 off, 7 on,...")

ARRAY LONGINT($DASH_MODE3;4)
$DASH_MODE3{1}:=8
$DASH_MODE3{2}:=7
$DASH_MODE3{3}:=2
$DASH_MODE3{4}:=7

PDF_Page_SetDash ($page;$DASH_MODE3;4;0)
draw_line ($page;60;620;"dash_ptn=[8, 7, 2, 7], phase=0")

PDF_Page_SetDash ($page;$DASH_MODE0;0;0)

PDF_Page_SetLineWidth ($page;30)
PDF_Page_SetRGBStroke ($page;0;0.5;0)

PDF_Page_SetLineCap ($page;HPDF_BUTT_END)
draw_line2 ($page;60;570;"PDF_BUTT_END")

PDF_Page_SetLineCap ($page;HPDF_ROUND_END)
draw_line2 ($page;60;505;"PDF_ROUND_END")

PDF_Page_SetLineCap ($page;HPDF_PROJECTING_SQUARE_END)
draw_line2 ($page;60;440;"PDF_PROJECTING_SQUARE_END")

PDF_Page_SetLineWidth ($page;30)
PDF_Page_SetRGBStroke ($page;0;0;0.5)

PDF_Page_SetLineJoin ($page;HPDF_MITER_JOIN)
PDF_Page_MoveTo ($page;120;300)
PDF_Page_LineTo ($page;160;340)
PDF_Page_LineTo ($page;200;300)
PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;60;360)
PDF_Page_ShowText ($page;"PDF_MITER_JOIN")
PDF_Page_EndText ($page)

PDF_Page_SetLineJoin ($page;HPDF_ROUND_JOIN)
PDF_Page_MoveTo ($page;120;195)
PDF_Page_LineTo ($page;160;235)
PDF_Page_LineTo ($page;200;195)
PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;60;255)
PDF_Page_ShowText ($page;"PDF_ROUND_JOIN")
PDF_Page_EndText ($page)

PDF_Page_SetLineJoin ($page;HPDF_BEVEL_JOIN)
PDF_Page_MoveTo ($page;120;90)
PDF_Page_LineTo ($page;160;130)
PDF_Page_LineTo ($page;200;90)
PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;60;150)
PDF_Page_ShowText ($page;"PDF_BEVEL_JOIN")
PDF_Page_EndText ($page)

PDF_Page_SetLineWidth ($page;2)
PDF_Page_SetRGBStroke ($page;0;0;0)
PDF_Page_SetRGBFill ($page;0.75;0;0)

draw_rect ($page;300;770;"Stroke")
PDF_Page_Stroke ($page)

draw_rect ($page;300;720;"Fill")
PDF_Page_Fill ($page)

draw_rect ($page;300;670;"Fill then Stroke")
PDF_Page_FillStroke ($page)

PDF_Page_GSave ($page)
draw_rect ($page;300;620;"Clip Rectangle")
PDF_Page_Clip ($page)
PDF_Page_Stroke ($page)
PDF_Page_SetFontAndSize ($page;$font;13)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;290;600)
PDF_Page_SetTextLeading ($page;12)
PDF_Page_ShowText ($page;"Clip Clip Clip Clip Clip Clipi Clip Clip Clip")
PDF_Page_ShowTextNextLine ($page;"Clip Clip Clip Clip Clip Clip Clip Clip Clip")
PDF_Page_ShowTextNextLine ($page;"Clip Clip Clip Clip Clip Clip Clip Clip Clip")
PDF_Page_EndText ($page)
PDF_Page_GRestore ($page)

$x:=330
$y:=440
$x1:=430
$y1:=530
$x2:=480
$y2:=470
$x3:=480
$y3:=90

PDF_Page_SetRGBFill ($page;0;0;0)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;300;540)
PDF_Page_ShowText ($page;"CurveTo2(x1, y1, x2. y2)")
PDF_Page_EndText ($page)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;$x+5;$y-5)
PDF_Page_ShowText ($page;"Current point")
PDF_Page_MoveTextPos ($page;$x1-$x;$y1-$y)
PDF_Page_ShowText ($page;"(x1, y1)")
PDF_Page_MoveTextPos ($page;$x2-$x1;$y2-$y1)
PDF_Page_ShowText ($page;"(x2, y2)")
PDF_Page_EndText ($page)

PDF_Page_SetDash ($page;$DASH_MODE1;1;0)

PDF_Page_SetLineWidth ($page;0.5)
PDF_Page_MoveTo ($page;$x1;$y1)
PDF_Page_LineTo ($page;$x2;$y2)
PDF_Page_Stroke ($page)

PDF_Page_SetDash ($page;$DASH_MODE0;0;0)

PDF_Page_SetLineWidth ($page;1.5)

PDF_Page_MoveTo ($page;$x;$y)
PDF_Page_CurveTo2 ($page;$x1;$y1;$x2;$y2)
PDF_Page_Stroke ($page)

$y:=$y-150
$y1:=$y1-150
$y2:=$y2-150

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;300;390)
PDF_Page_ShowText ($page;"CurveTo3(x1, y1, x2. y2)")
PDF_Page_EndText ($page)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;$x+5;$y-5)
PDF_Page_ShowText ($page;"Current point")
PDF_Page_MoveTextPos ($page;$x1-$x;$y1-$y)
PDF_Page_ShowText ($page;"(x1, y1)")
PDF_Page_MoveTextPos ($page;$x2-$x1;$y2-$y1)
PDF_Page_ShowText ($page;"(x2, y2)")
PDF_Page_EndText ($page)

PDF_Page_SetDash ($page;$DASH_MODE1;1;0)

PDF_Page_SetLineWidth ($page;0.5)
PDF_Page_MoveTo ($page;$x;$y)
PDF_Page_LineTo ($page;$x1;$y1)
PDF_Page_Stroke ($page)

PDF_Page_SetDash ($page;$DASH_MODE0;0;0)

PDF_Page_SetLineWidth ($page;1.5)
PDF_Page_MoveTo ($page;$x;$y)
PDF_Page_CurveTo3 ($page;$x1;$y1;$x2;$y2)
PDF_Page_Stroke ($page)

$y:=$y-150
$y1:=$y1-160
$y2:=$y2-130
$x2:=$x2+10

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;300;240)
PDF_Page_ShowText ($page;"CurveTo(x1, y1, x2. y2, x3, y3)")
PDF_Page_EndText ($page)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;$x+5;$y-5)
PDF_Page_ShowText ($page;"Current point")
PDF_Page_MoveTextPos ($page;$x1-$x;$y1-$y)
PDF_Page_ShowText ($page;"(x1, y1)")
PDF_Page_MoveTextPos ($page;$x2-$x1;$y2-$y1)
PDF_Page_ShowText ($page;"(x2, y2)")
PDF_Page_MoveTextPos ($page;$x3-$x2;$y3-$y2)
PDF_Page_ShowText ($page;"(x3, y3)")
PDF_Page_EndText ($page)

PDF_Page_SetDash ($page;$DASH_MODE1;1;0)

PDF_Page_SetLineWidth ($page;0.5)
PDF_Page_MoveTo ($page;$x;$y)
PDF_Page_LineTo ($page;$x1;$y1)
PDF_Page_Stroke ($page)
PDF_Page_MoveTo ($page;$x2;$y2)
PDF_Page_LineTo ($page;$x3;$y3)
PDF_Page_Stroke ($page)

PDF_Page_SetDash ($page;$DASH_MODE0;0;0)

PDF_Page_SetLineWidth ($page;1.5)
PDF_Page_MoveTo ($page;$x;$y)
PDF_Page_CurveTo ($page;$x1;$y1;$x2;$y2;$x3;$y3)
PDF_Page_Stroke ($page)

  //note: on windows, this path can only contain ANSI-for-locale characters
$filePath:=System folder(Desktop)+"line_demo.pdf"
PDF_SaveToFile ($pdf;$filePath)
  //PDF_SaveToStream ($pdf;$pdfData)

PDF_Free ($pdf)

OPEN URL($filePath)
```

### text_demo

```4d
  //based on sample code found at:
  //http://libharu.org/demo/text_demo.c

$page_title:="Text Demo"
$samp_text:="abcdefgABCDEFG12345!#$%&+-@?"
$samp_text2:="The quick brown fox jumps over the lazy dog."

$pdf:=PDF_New 

PDF_SetCompressionMode ($pdf;HPDF_COMP_ALL)

$page:=PDF_AddPage ($pdf)

  //print_grid ($pdf;$page)

print_margin ($pdf;$page)

print_title ($pdf;$page;$page_title)

PDF_Page_BeginText ($page)
PDF_Page_MoveTextPos ($page;60;PDF_Page_GetHeight ($page)-60)

  //font size

$fsize:=8

$font:=PDF_GetFont ($pdf;"Helvetica")

While ($fsize<60)
	
	PDF_Page_SetFontAndSize ($page;$font;$fsize)
	PDF_Page_MoveTextPos ($page;0;-5-$fsize)
	$len:=PDF_Page_MeasureText ($page;$samp_text;PDF_Page_GetWidth ($page)-120;0;0)
	
	PDF_Page_ShowText ($page;Substring($samp_text;1;$len))
	
	PDF_Page_MoveTextPos ($page;0;-10)
	PDF_Page_SetFontAndSize ($page;$font;8)
	PDF_Page_ShowText ($page;"Fontsize="+String($fsize))
	
	$fsize:=$fsize*1.5
	
End while 

  //font color

PDF_Page_SetFontAndSize ($page;$font;8)
PDF_Page_MoveTextPos ($page;0;-30)
PDF_Page_ShowText ($page;"Font color")

PDF_Page_SetFontAndSize ($page;$font;18)
PDF_Page_MoveTextPos ($page;0;-20)

$len:=Length($samp_text)

For ($i;1;$len)
	
	$r:=($i-1)/$len
	$g:=1-(($i-1)/$len)
	
	PDF_Page_SetRGBFill ($page;$r;$g;0)
	PDF_Page_ShowText ($page;$samp_text[[$i]])
	
End for 

PDF_Page_MoveTextPos ($page;0;-25)

For ($i;1;$len)
	
	$r:=($i-1)/$len
	$b:=1-(($i-1)/$len)
	
	PDF_Page_SetRGBFill ($page;$r;0;$b)
	PDF_Page_ShowText ($page;$samp_text[[$i]])
	
End for 

PDF_Page_MoveTextPos ($page;0;-25)

For ($i;1;$len)
	
	$b:=($i-1)/$len
	$g:=1-(($i-1)/$len)
	
	PDF_Page_SetRGBFill ($page;0;$g;$b)
	PDF_Page_ShowText ($page;$samp_text[[$i]])
	
End for 

PDF_Page_EndText ($page)

$ypos:=450

  //Font rendering mode

$err:=PDF_Page_SetFontAndSize ($page;$font;32)
PDF_Page_SetRGBFill ($page;0.5;0.5;0)
PDF_Page_SetLineWidth ($page;1.5)

  //PDF_FILL
show_description ($page;60;$ypos;"RenderingMode=PDF_FILL")

PDF_Page_SetTextRenderingMode ($page;HPDF_FILL)
PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;$ypos;"ABCabc123")
PDF_Page_EndText ($page)

  //PDF_STROKE
show_description ($page;60;$ypos-50;"RenderingMode=PDF_STROKE")

PDF_Page_SetTextRenderingMode ($page;HPDF_STROKE)
PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;$ypos-50;"ABCabc123")
PDF_Page_EndText ($page)

  //PDF_FILL_THEN_STROKE
show_description ($page;60;$ypos-100;"RenderingMode=PDF_FILL_THEN_STROKE")

PDF_Page_SetTextRenderingMode ($page;HPDF_FILL_THEN_STROKE)
PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;$ypos-100;"ABCabc123")
PDF_Page_EndText ($page)

  //PDF_FILL_CLIPPING
show_description ($page;60;$ypos-150;"RenderingMode=PDF_FILL_CLIPPING")

PDF_Page_GSave ($page)
PDF_Page_SetTextRenderingMode ($page;HPDF_FILL_CLIPPING)
PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;$ypos-150;"ABCabc123")
PDF_Page_EndText ($page)
show_stripe_pattern ($page;60;$ypos-150)
PDF_Page_GRestore ($page)

  //PDF_STROKE_CLIPPING
show_description ($page;60;$ypos-200;"RenderingMode=PDF_STROKE_CLIPPING")

PDF_Page_GSave ($page)
PDF_Page_SetTextRenderingMode ($page;HPDF_STROKE_CLIPPING)
PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;$ypos-200;"ABCabc123")
PDF_Page_EndText ($page)
show_stripe_pattern ($page;60;$ypos-200)
PDF_Page_GRestore ($page)

  //PDF_FILL_STROKE_CLIPPING
show_description ($page;60;$ypos-250;"RenderingMode=PDF_FILL_STROKE_CLIPPING")

PDF_Page_GSave ($page)
PDF_Page_SetTextRenderingMode ($page;HPDF_FILL_STROKE_CLIPPING)
PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;$ypos-250;"ABCabc123")
PDF_Page_EndText ($page)
show_stripe_pattern ($page;60;$ypos-250)
PDF_Page_GRestore ($page)

PDF_Page_SetTextRenderingMode ($page;HPDF_FILL)
PDF_Page_SetRGBFill ($page;0;0;0)
PDF_Page_SetFontAndSize ($page;$font;30)

  //Rotating text
$angle1:=30
$rad1:=$angle1/180*3.141592

show_description ($page;320;$ypos-60;"Rotating text")

PDF_Page_BeginText ($page)
PDF_Page_SetTextMatrix ($page;Cos($rad1);Sin($rad1);-Sin($rad1);Cos($rad1);330;$ypos-60)
PDF_Page_ShowText ($page;"ABCabc123")
PDF_Page_EndText ($page)

  //Skewing text

show_description ($page;320;$ypos-120;"Skewing text")

$angle1:=10
$angle2:=20
$rad1:=$angle1/180*3.141592
$rad2:=$angle2/180*3.141592

PDF_Page_BeginText ($page)
PDF_Page_SetTextMatrix ($page;1.5;Tan($rad1);Tan($rad2);1;320;$ypos-120)
PDF_Page_ShowText ($page;"ABCabc12")
PDF_Page_EndText ($page)

  //Scaling text (X direction)

show_description ($page;320;$ypos-175;"Scaling text (X direction)")

PDF_Page_BeginText ($page)
PDF_Page_SetTextMatrix ($page;1.5;0;0;1;320;$ypos-175)
PDF_Page_ShowText ($page;"ABCabc12")
PDF_Page_EndText ($page)

  //Scaling text (Y direction)

show_description ($page;320;$ypos-250;"Scaling text (Y direction)")

PDF_Page_BeginText ($page)
PDF_Page_SetTextMatrix ($page;1;0;0;2;320;$ypos-250)
PDF_Page_ShowText ($page;"ABCabc123")
PDF_Page_EndText ($page)

  //Char spacing, word spacing

show_description ($page;60;140;"char-spacing 0")
show_description ($page;60;100;"char-spacing 1.5")
show_description ($page;60;60;"char-spacing 1.5, word-spacing 2.5")

PDF_Page_SetFontAndSize ($page;$font;20)
PDF_Page_SetRGBFill ($page;0.1;0.3;0.1)

  //Char-spacing 0

PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;140;$samp_text2)
PDF_Page_EndText ($page)

  //Char-spacing 1.5
PDF_Page_SetCharSpace ($page;1.5)

PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;100;$samp_text2)
PDF_Page_EndText ($page)

  //Char-spacing 1.5, word-spacing 3.5
PDF_Page_SetWordSpace ($page;2.5)

PDF_Page_BeginText ($page)
PDF_Page_TextOut ($page;60;60;$samp_text2)
PDF_Page_EndText ($page)

  //note: on windows, this path can only contain ANSI-for-locale characters
$filePath:=System folder(Desktop)+"text_demo.pdf"
PDF_SaveToFile ($pdf;$filePath)
  //PDF_SaveToStream ($pdf;$pdfData)

PDF_Free ($pdf)

OPEN URL($filePath)
```

### text_demo2

```4d
  //based on sample code found at:
  //http://libharu.org/demo/text_demo2.c

$samp_text:="The quick brown fox jumps over the lazy dog."

$pdf:=PDF_New 

  //PDF_SetCompressionMode ($pdf;HPDF_COMP_ALL)

$page:=PDF_AddPage ($pdf)
PDF_Page_SetSize ($page;HPDF_PAGE_SIZE_A5;HPDF_PAGE_PORTRAIT)

  //print_grid ($pdf;$page)

$page_height:=PDF_Page_GetHeight ($page)

$font:=PDF_GetFont ($pdf;"Helvetica")
PDF_Page_SetTextLeading ($page;20)

$left:=25
$top:=545
$right:=200
$bottom:=$top-40
PDF_Page_Rectangle ($page;$left;$bottom;$right-$left;$top-$bottom)

PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)

PDF_Page_SetFontAndSize ($page;$font;10)
PDF_Page_TextOut ($page;$left;$top+3;"HPDF_TALIGN_LEFT")

PDF_Page_SetFontAndSize ($page;$font;13)
PDF_Page_TextRect ($page;$left;$top;$right;$bottom;$samp_text;HPDF_TALIGN_LEFT;0)

PDF_Page_EndText ($page)

$left:=220
$right:=395

PDF_Page_Rectangle ($page;$left;$bottom;$right-$left;$top-$bottom)
PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)

PDF_Page_SetFontAndSize ($page;$font;10)
PDF_Page_TextOut ($page;$left;$top+3;"HPDF_TALIGN_RIGTH")

PDF_Page_SetFontAndSize ($page;$font;13)
PDF_Page_TextRect ($page;$left;$top;$right;$bottom;$samp_text;HPDF_TALIGN_RIGHT;0)

PDF_Page_EndText ($page)

$left:=25
$top:=475
$right:=200
$bottom:=$top-40

PDF_Page_Rectangle ($page;$left;$bottom;$right-$left;$top-$bottom)
PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)

PDF_Page_SetFontAndSize ($page;$font;10)
PDF_Page_TextOut ($page;$left;$top+3;"HPDF_TALIGN_CENTER")

PDF_Page_SetFontAndSize ($page;$font;13)
PDF_Page_TextRect ($page;$left;$top;$right;$bottom;$samp_text;HPDF_TALIGN_CENTER;0)

PDF_Page_EndText ($page)

$left:=220
$right:=395

PDF_Page_Rectangle ($page;$left;$bottom;$right-$left;$top-$bottom)
PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)

PDF_Page_SetFontAndSize ($page;$font;10)
PDF_Page_TextOut ($page;$left;$top+3;"HPDF_TALIGN_JUSTIFY")

PDF_Page_SetFontAndSize ($page;$font;13)
PDF_Page_TextRect ($page;$left;$top;$right;$bottom;$samp_text;HPDF_TALIGN_JUSTIFY;0)

PDF_Page_EndText ($page)

PDF_Page_GSave ($page)

$angle1:=5
$angle2:=10
$rad1:=$angle1/180*Pi
$rad2:=$angle2/180*Pi

PDF_Page_Concat ($page;1;Tan($rad1);Tan($rad2);1;25;350)
$left:=0
$top:=40
$right:=175
$bottom:=0

PDF_Page_Rectangle ($page;$left;$bottom;$right-$left;$top-$bottom)
PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)

PDF_Page_SetFontAndSize ($page;$font;10)
PDF_Page_TextOut ($page;$left;$top+3;"Skewed coordinate system")

PDF_Page_SetFontAndSize ($page;$font;13)
PDF_Page_TextRect ($page;$left;$top;$right;$bottom;$samp_text;HPDF_TALIGN_LEFT;0)

PDF_Page_EndText ($page)

PDF_Page_GRestore ($page)

PDF_Page_GSave ($page)

$angle1:=5
$rad1:=$angle1/180*Pi

PDF_Page_Concat ($page;Cos($rad1);Sin($rad1);-Sin($rad1);Cos($rad1);220;350)
$left:=0
$top:=40
$right:=175
$bottom:=0

PDF_Page_Rectangle ($page;$left;$bottom;$right-$left;$top-$bottom)
PDF_Page_Stroke ($page)

PDF_Page_BeginText ($page)

PDF_Page_SetFontAndSize ($page;$font;10)
PDF_Page_TextOut ($page;$left;$top+3;"Rotated coordinate system")

PDF_Page_SetFontAndSize ($page;$font;13)
PDF_Page_TextRect ($page;$left;$top;$right;$bottom;$samp_text;HPDF_TALIGN_LEFT;0)

PDF_Page_EndText ($page)

PDF_Page_GRestore ($page)

PDF_Page_SetGrayStroke ($page;0)
PDF_Page_Circle ($page;210;190;145)
PDF_Page_Circle ($page;210;190;113)
PDF_Page_Stroke ($page)

$angle1:=360/(Length($samp_text))
$angle2:=180

PDF_Page_BeginText ($page)
$font:=PDF_GetFont ($pdf;"Courier-Bold")
PDF_Page_SetFontAndSize ($page;$font;30)

For ($i;1;Length($samp_text))
	
	$rad1:=($angle2-90)/180*Pi
	$rad2:=$angle2/180*Pi
	
	$x:=210+(Cos($rad2)*122)
	$y:=190+(Sin($rad2)*122)
	
	PDF_Page_SetTextMatrix ($page;Cos($rad1);Sin($rad1);-Sin($rad1);Cos($rad1);$x;$y)
	
	PDF_Page_ShowText ($page;Substring($samp_text;$i;1))
	$angle2:=$angle2-$angle1
	
End for 

PDF_Page_EndText ($page)

  //note: on windows, this path can only contain ANSI-for-locale characters
$filePath:=System folder(Desktop)+"text_demo2.pdf"
PDF_SaveToFile ($pdf;$filePath)
  //PDF_SaveToStream ($pdf;$pdfData)

PDF_Free ($pdf)

OPEN URL($filePath)
```

---

## Error handling & troubleshooting

- **A failed libharu call usually returns `0` or `""`, not an error code.** The plugin installs a libharu error handler that throws a C++ exception on every error; the plugin catches it at the top level and returns without setting the result. Status results therefore read `0` (`HPDF_OK`) even when the call failed (inferred: 4D's default result value, not traced in 4D), and handle results read `""`. **Check handles for `""`**, and after a sequence of drawing calls check the output, not the statuses.
- **An empty handle result means the object was not created**: wrong document handle, unreadable file, unsupported image, unknown font or encoding name, or an earlier error. Load commands reset the document's error state before they run, so one failure does not block the next load.
- **4D crashes after `PDF_Free` or with a typo in a handle.** Only document handles are validated; see [Requirements](#requirements--platform-notes).
- **Text shows as garbage or `?`.** The global encoding ([PDF_Global_SetEncoding](#pdf_global_setencoding)) does not match the font's encoding, or the font cannot show those characters. For CJK text, enable the fonts and encodings first (`PDF_UseJPFonts`, `PDF_UseJPEncodings`, ...).
- **Empty text does nothing.** `PDF_Page_ShowText`, `PDF_Page_TextOut`, `PDF_Page_TextRect`, the annotation creators, `PDF_SetInfoAttr`, `PDF_AddPageLabel` and `PDF_CreateOutline` skip the libharu call when the text is empty and return `0` or `""`.
- **[PDF_SetPassword](#pdf_setpassword) needs two different, non-empty passwords.**
- **The `encoder` parameter of the annotation creators is ignored**, and **[PDF_Page_CreateLinkAnnot](#pdf_page_createlinkannot) always fails** in this release; see their sections.
- **Widths from `PDF_Font_TextWidth`/`PDF_Font_MeasureText` are wrong for non-ASCII text**: they measure UTF-8 bytes. Use [PDF_Page_TextWidth](#pdf_page_textwidth) and [PDF_Page_MeasureText](#pdf_page_measuretext).
- **Crashes fixed in this release**: [PDF_GetInfoAttr](#pdf_getinfoattr) on an unset field, `PDF_Font_GetFontName`/`PDF_Font_GetEncodingName`/`PDF_Image_GetColorSpace` on an empty handle, a failed `PDF_LoadType1FontFromFile`/`PDF_LoadTTFontFromFile`, raw-image BLOBs shorter than the image, and [PDF_Page_SetDash](#pdf_page_setdash) with a `count` larger than the array.

---

## Quick reference

```4d
$pdf:=PDF_New
PDF_SetCompressionMode ($pdf;HPDF_COMP_ALL)
$page:=PDF_AddPage ($pdf)
PDF_Page_SetSize ($page;HPDF_PAGE_SIZE_A4;HPDF_PAGE_PORTRAIT)
$font:=PDF_GetFont ($pdf;"Helvetica";"")

PDF_Page_BeginText ($page)
PDF_Page_SetFontAndSize ($page;$font;24)
PDF_Page_TextOut ($page;60;PDF_Page_GetHeight ($page)-80;"Hello")
PDF_Page_EndText ($page)

PDF_Page_SetLineWidth ($page;1)
PDF_Page_Rectangle ($page;50;50;PDF_Page_GetWidth ($page)-100;PDF_Page_GetHeight ($page)-110)
PDF_Page_Stroke ($page)

$path:=System folder(Desktop)+"hello.pdf"
$err:=PDF_SaveToFile ($pdf;$path)
PDF_Free ($pdf)
```

## Building from source

The macOS static libraries are not committed. Build them once before you open the Xcode project:

```bash
scripts/build-macos-deps.sh
```

The script downloads pinned, checksummed releases of libharu 2.3.0 (tag `RELEASE_2_3_0`, which matches `include/hpdf_mac.h`) and libpng 1.6.59. It builds both universal (arm64 + x86_64, macOS 11.5) into `a/`. zlib comes from the macOS SDK. You need the Xcode command line tools and `cmake`. The release workflow runs the same script and caches the result.

The Windows build still links the prebuilt libraries in `lib/Windows64`.
