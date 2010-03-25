
package hxGD;

import neko.Lib;

enum ArcFillType {
	ArcFilled;
	ArcOutline;
	ArcBorder;
	ChordFilled;
	ChordOutline;
	ChordBorder;
}

class Graphics {
	
	public static var defaultColor:Color = Color.ofRGB(0x000000);
	public static var defaultThickness:Int = 1;
	public static var defaultAntiAliasing:Bool = true;
	
	
	private var img:Void;
	
	public var color(getColor,setColor):Color;
	private var _color:Color;

	public var thickness(getThickness,setThickness):Int;
	private var _thickness:Int;
	
	public var antiAliasing(getAntiAliasing,setAntiAliasing):Bool;
	private var _antiAliasing:Bool;
	

	public function new(img:Void) {
		this.img = img;
		setColor(Graphics.defaultColor);
		setAntiAliasing(Graphics.defaultAntiAliasing);
		setThickness(Graphics.defaultThickness);
	}
	
	/* public function setBrush(?brushImage:Image=null) {
		gd_setBrush(img,brushImage,(brushImage!=null));	
	}
	
	public function setTile(?tileImage:Image=null) {
		gd_setTile(img,tileImage,(tileImage!=null));
	} */
	
	
	public inline function setStyle(colors:Array<Color>):Void {
		var ca:Array<Int> = new Array<Int>();
		for (c in colors)
			ca.push(c.gd);
		gd_setStyle(img,Lib.haxeToNeko(ca));
	}
	
	
	private inline function getAntiAliasing():Bool {
		return _antiAliasing;
	}
	
	private inline function setAntiAliasing(aa:Bool):Bool {
		_antiAliasing = aa;
		gd_setAntiAliasing(img,aa);
		return _antiAliasing;		
	}	
	
	private inline function getThickness():Int {
		return _thickness;
	}
	
	private inline function setThickness(thickn:Int):Int {
		_thickness = gd_setThickness(img,(thickn!=0?thickn:1));
		return _thickness;
	}
	
	
	private inline function setColor(c:Color):Color {
		_color = c;
		gd_setColor(img,_color.gd);
		return color;	
	}
	
	private inline function getColor():Color {
		return _color;	
	}
	
	public inline function setPixel(x:Int,y:Int):Void {
		gd_setPixel(img,x,y);	
	}
	
	public inline function imageLine(x1:Int,y1:Int,x2:Int,y2:Int,?dashed:Bool=false):Void {
		if (dashed)
			gd_imageDashedLine(img,x1,y1,x2,y2);
		else
			gd_imageLine(img,x1,y1,x2,y2);
	}
	
	public inline function imagePolygon(poly:Polygon,?open:Bool=false,?filled:Bool=false):Void {
		if (open)
			if (filled)
				gd_imageFilledPolygon(img,poly.x,poly.y);
			else
				gd_imageOpenPolygon(img,poly.x,poly.y);
		else
			if (filled)
				gd_imageFilledPolygon(img,poly.x,poly.y);
			else
				gd_imagePolygon(img,poly.x,poly.y);
	}
	
	public inline function imageRectangle(x:Int,y:Int,width:Int,height:Int,?filled:Bool=false):Void {
		if (filled)
			gd_imageFilledRectangle(img,x,y,width,height);
		else
			gd_imageRectangle(img,x,y,width,height);
	}
	
	public inline function imageEllipse(x:Int, y:Int, width:Int,height:Int,?filled:Bool=false):Void {
		if (filled)
			gd_imageFilledEllipse(img,x,y,width,height);
		else
			gd_imageArc(img,x,y,width,height,0,360);
	}
	
	public inline function imageCircle(x:Int, y:Int, radius:Int,?filled:Bool=false):Void {
		if (filled)
			gd_imageFilledArc(img,x,y,radius*2,radius*2,0,360,0);
		else
			gd_imageArc(img,x,y,radius*2,radius*2,0,360);
	}
	
	public inline function imageArc(x:Int,y:Int, width:Int,height:Int, start:Int, end:Int, fillType:ArcFillType):Void {
		switch (fillType) {
			case ArcFilled:		gd_imageFilledArc(img,x,y,width,height,start,end,0);
			case ArcOutline:	gd_imageFilledArc(img,x,y,width,height,start,end,2);
			case ArcBorder:		gd_imageFilledArc(img,x,y,width,height,start,end,6);
			case ChordFilled:	gd_imageFilledArc(img,x,y,width,height,start,end,1);
			case ChordOutline:	gd_imageFilledArc(img,x,y,width,height,start,end,3);
			case ChordBorder:	gd_imageFilledArc(img,x,y,width,height,start,end,7);
		}
	}
	
	public inline function imageFillToBorder(x:Int,y:Int, borderColor:Color):Void {
		gd_imageFillToBorder(img,x,y,borderColor.gd);		
	}
	
	public inline function imageFill(x:Int, y:Int) {
		gd_imageFill(img,x,y);	
	}
	
	private static var gd_setAntiAliasing = Lib.load("nGD","SetAntiAliasing",2);
	private static var gd_setThickness = Lib.load("nGD","SetThickness",2);
	private static var gd_setColor = Lib.load("nGD","SetColor",2);
	private static var gd_setPixel = Lib.load("nGD","SetPixel",3);
	private static var gd_imageLine = Lib.load("nGD","ImageLine",5);
	private static var gd_imageDashedLine = Lib.load("nGD","ImageDashedLine",5);
	private static var gd_imagePolygon = Lib.load("nGD","ImagePolygon",3);
	private static var gd_imageFilledPolygon = Lib.load("nGD","ImageFilledPolygon",3);
	private static var gd_imageOpenPolygon = Lib.load("nGD","ImageOpenPolygon",3);
	private static var gd_imageRectangle = Lib.load("nGD","ImageRectangle",5);
	private static var gd_imageFilledRectangle = Lib.load("nGD","ImageFilledRectangle",5);
	private static var gd_imageFilledEllipse = Lib.load("nGD","ImageFilledEllipse",5);
	private static var gd_imageArc = Lib.load("nGD","ImageArc",-1);
	private static var gd_imageFilledArc = Lib.load("nGD","ImageFilledArc",-1);
	private static var gd_imageFillToBorder = Lib.load("nGD","ImageFillToBorder",4);
	private static var gd_imageFill = Lib.load("nGD","ImageFill",3);
	//private static var gd_setBrush = Lib.load("nGD","SetBrush",3);
	//private static var gd_setTile = Lib.load("nGD","SetTile",3);
	private static var gd_setStyle = Lib.load("nGD","SetStyle",2);

}
