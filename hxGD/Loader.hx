package hxGD;

import neko.Lib;

class Loader {
	
	public static inline function createFromJpeg (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromJpeg(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	public static inline function createFromPng (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromPng(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	public static inline function createFromGif (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromGif(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	public static inline function createFromGd (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromGd(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	public static inline function createFromGd2 (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromGd2(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	public static inline function createFromGd2Part (filename:String,srcX:Int,srcY:Int,width:Int,height:Int):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromGd2Part(Lib.haxeToNeko(filename),srcX,srcY,width,height);
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	public static inline function createFromWBMP(filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromWBMP(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	


	private static var gd_imageCreateFromJpeg = Lib.load("nGD","ImageCreateFromJpeg",1);
	private static var gd_imageCreateFromPng = Lib.load("nGD","ImageCreateFromPng",1);
	private static var gd_imageCreateFromGif = Lib.load("nGD","ImageCreateFromGif",1);
	private static var gd_imageCreateFromGd = Lib.load("nGD","ImageCreateFromGd",1);
	private static var gd_imageCreateFromGd2 = Lib.load("nGD","ImageCreateFromGd2",1);
	private static var gd_imageCreateFromGd2Part = Lib.load("nGD","ImageCreateFromGd2Part",5);
	private static var gd_imageCreateFromWBMP = Lib.load("nGD","ImageCreateFromWBMP",1);
}
