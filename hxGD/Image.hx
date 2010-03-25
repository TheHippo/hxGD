package hxGD;

import neko.Lib;


enum FileType {
  Png;
  Jpeg (quality:Int);
  Gif;
  Gd;
  Gd2 (compressed:Bool, chunkSize:Int);	
}


class Image {
	
	public static var defaultBackgroundColor:Color = Color.ofRGB(0xFFFFFF);
	
	public var img:Void;	
	
	public var trueColor(isTrueColor,null):Bool;
	public var width(getWidth,null):Int;
	public var height(getHeight,null):Int;
	
	public var graphics:Graphics;

	public function new (width:Int,height:Int,?color:Color,trueColor:Bool=true) {
		if (img!=null)
			gd_freeImage(img);
		if (!trueColor) {
			img = gd_imageCreate(width,height,(color==null?Image.defaultBackgroundColor.gd:color.gd));
			//gd_setColor(img,(color==null?Image.defaultBackgroundColor.gd:color.gd));
			//gd_imageFill(0,0);
			graphics = new Graphics(img);		
		}
		else {
			img = gd_imageCreateTrueColor(width,height,(color==null?Image.defaultBackgroundColor.gd:color.gd));
			//gd_setColor(img,(color==null?Image.defaultBackgroundColor.gd:color.gd));
			graphics = new Graphics(img);
		}
		//trace("new image "+trueColor);
	}
	
	public inline function saveImage(filename:String,type:FileType):Void {
		var file:Dynamic = Lib.haxeToNeko(filename);
		switch (type) {
			case Png:			gd_imagePng(img,file);
			case Jpeg(q):		gd_imageJpeg(img,file,q);
			case Gif:			gd_imageGif(img,file);
			case Gd:			gd_imageGd(img,file);
			case Gd2(comp,ch):	gd_imageGd2(img,file,comp,ch);
		}			
	}
	
	public inline function make256Colors(?dithering:Bool=true,?anzColors:Int=255):Void {
		gd_makeImageToPalette(img,dithering,(Math.abs(anzColors)<256?Math.abs(anzColors):255));
	}
	
	public inline function cloneTo256Colors(?dithering:Bool,?anzColors:Int=255):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_cloneImageToPalette(img,dithering,(Math.abs(anzColors)<256?Math.abs(anzColors):255));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	private function isTrueColor():Bool {
		return gd_imageTrueColor(img);
	}
	
	private inline function getWidth():Int {
		return gd_imageX(img);	
	}
	
	private inline function getHeight():Int {
		return gd_imageY(img);
	}
	
	private static var gd_imageFill = Lib.load("nGD","ImageFill",3);
	private static var gd_setColor = Lib.load("nGD","SetColor",2);
	private static var gd_freeImage = Lib.load("nGD","FreeImage",1);
	private static var gd_imageCreate = Lib.load("nGD","ImageCreate",3);
	private static var gd_imageCreateTrueColor = Lib.load("nGD","ImageCreateTrueColor",3);
	private static var gd_imageJpeg = Lib.load("nGD","ImageJpeg",3);
	private static var gd_imageGif = Lib.load("nGD","ImageGif",2);
	private static var gd_imagePng = Lib.load("nGD","ImagePng",2);
	private static var gd_imageGd = Lib.load("nGD","ImageGd",2);
	private static var gd_imageGd2 = Lib.load("nGD","ImageGd2",4);
	private static var gd_makeImageToPalette = Lib.load("nGD","MakeImageToPalette",3);
	private static var gd_cloneImageToPalette = Lib.load("nGD","CloneImageToPalette",3);
	private static var gd_imageX = Lib.load("nGD","ImageX",1);
	private static var gd_imageY = Lib.load("nGD","ImageY",1);
	private static var gd_imageTrueColor = Lib.load("nGD","ImageTrueColor",1);	

}
