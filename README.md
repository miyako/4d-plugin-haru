4d-plugin-haru
==============

4D implementation of [libharu](https://github.com/libharu/libharu).

See [examples](https://github.com/miyako/4d-plugin-haru/tree/master/Haru/examples) for output.

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />

## Examples

* jpfont_demo

```
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

* font_demo

```
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

* line_demo

```
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

* text_demo

```
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

* text_demo2

```
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
