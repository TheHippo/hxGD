/*
 *      hxGD.Image.hx
 *      
 *      Copyright 2010 Philipp Klose <me@thehippo.de>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

package hxGD;


import neko.Lib;

enum StringAlign {
	LeftTop;
	CenterTop;
	RightTop;
	LeftMiddle;
	CenterMiddle;
	RightMiddle;
	LeftBottom;
	CenterBottom;
	RightBottom;
}

enum FileType {
  Png;
  Jpeg (quality:Int);
  Gif;
  Gd;
  Gd2 (compressed:Bool, chunkSize:Int);	
}


class Image {
	
	/**
	 * the default background color, no alpha channel!
	 */
	public static var defaultBackgroundColor:Color = Color.ofRGB(0xFFFFFF);
	
	/**
	 * neko image representation
	 */
	public var img:Void;	
	
	/**
	 * is it a trueColor image? otherwise 256 color palette based
	 */
	public var trueColor(isTrueColor, null):Bool;
	/**
	 * width
	 */
	public var width(getWidth, null):Int;
	/**
	 * height
	 */
	public var height(getHeight,null):Int;
	
	/**
	 * graphicsinterface
	 */
	public var graphics:Graphics;

	/**
	 * creates a new Image
	 * @param	width
	 * @param	height
	 * @param	?color background color
	 * @param	?trueColor true color or palette based image
	 */
	public function new (width:Int,height:Int,?color:Color,?trueColor:Bool=true) {
		if (img!=null)
			gd_freeImage(img);
		img = gd_imageCreate(width,height,(color==null?Image.defaultBackgroundColor.gd:color.gd),trueColor);
		graphics = new Graphics(img);
	}
	
	/**
	 * saves the current image to a file
	 * @param	filename
	 * @param	type see FileType
	 */
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
	
	/**
	 * returns plain image data, eg. for sending it to the browser
	 * @param type see FileTyoe
	 * @return String data
	 */
	public inline function getImageData(type:FileType):String {
		return Lib.nekoToHaxe(
			switch (type) {
				case Png: gd_imagePngData(img);
				case Gif: gd_imageGifData(img);
				case Jpeg(q): gd_imageJpegData(img,q);
				default:
					throw ("not supported");
			}		
		);
	}
	
	/**
	 * converts a truecolor image to a palette based image
	 * @param	?dithering dithering?
	 * @param	?anzColors number of colors. max: 256
	 */
	public inline function make256Colors(?dithering:Bool=true,?anzColors:Int=255):Void {
		gd_makeImageToPalette(img,dithering,(Math.abs(anzColors)<256?Math.abs(anzColors):255));
	}
	
	/**
	 * clones the image and returns it as a 256 colors palette bases image
	 * @param	?dithering dithering?
	 * @param	?anzColors number of colors. max: 256
	 * @return Image
	 */
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
	
	/**
	 * returns a copy of the current image
	 * @return Image
	 */
	public inline function cloneImage():Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_cloneImage(img);
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	/**
	 * returns a part of the current image as a new image
	 * @param	x
	 * @param	y
	 * @param	width
	 * @param	height
	 * @return Image
	 */
	public inline function getImagePart(x:Int,y:Int,width:Int,height:Int):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_getImagePart(img,x,y,width,height);
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	/**
	 * resizes the current image
	 * @param	width
	 * @param	height
	 * @param	?resample resample the image (better quality)
	 */
	public inline function resize(width:Int,height:Int,?resample:Bool=true):Void {
		gd_imageResize(img,width,height,resample);		
	}
	
	/**
	 * rotate the image
	 * @param	angle
	 */
	public inline function rotate(angle:Int) {
		gd_imageRotate(img,angle);	
	}
	
	/**
	 * attach another image to the current image
	 * @param	aimg the image to attach
	 * @param	dstX
	 * @param	dstY
	 * @param	srcX
	 * @param	srcY
	 * @param	width
	 * @param	height
	 * @param	percentage 0-100, how much should the attached image be blended?
	 */
	public inline function attach(aimg:Image,dstX:Int,dstY:Int,srcX:Int,srcY:Int,width:Int,height:Int,percentage:Int) {
		gd_imageAttach(img,aimg.img,dstX,dstY,srcX,srcY,width,height,percentage);		
	}
	
	/**
	 * prints a out a string to the image
	 * @param	fontName path/to/file/truetypefont.tff
	 * @param	size in points
	 * @param	x
	 * @param	y
	 * @param	string
	 * @param	?align see StringAling
	 * @param	?antiAliasing
	 * @param	angle
	 */
	public inline function string(fontName:String,size:Float,x:Int,y:Int,string:String,?align:StringAlign,?antiAliasing:Bool=true,?angle:Float=0):Void {
		if (align==null)
			align=StringAlign.LeftTop;
		var a:Int = alignToInt(align);
		try {
			gd_imageStringTTF(img,Lib.haxeToNeko(fontName),size,angle,x,y,Lib.haxeToNeko(string),a,antiAliasing,graphics.color.gd);
		}
		catch (e:Dynamic) {
			trace(e);
		}
	}
	
	private inline function alignToInt(a:StringAlign):Int {
		return switch (a) {
			case LeftTop:0;
			case CenterTop:1;
			case RightTop:2;
			case LeftMiddle:3;
			case CenterMiddle:4;
			case RightMiddle:5;
			case LeftBottom:6;
			case CenterBottom:7;
			case RightBottom:8;
		}
	}
	
	private static var gd_imageFill = Lib.load("nGD","ImageFill",3);
	private static var gd_setColor = Lib.load("nGD","SetColor",2);
	private static var gd_freeImage = Lib.load("nGD","FreeImage",1);
	private static var gd_imageCreate = Lib.load("nGD","ImageCreate",4);
	private static var gd_imageJpeg = Lib.load("nGD","ImageJpeg",3);
	private static var gd_imageJpegData = Lib.load("nGD","ImageJpegData",2);
	private static var gd_imageGif = Lib.load("nGD","ImageGif",2);
	private static var gd_imageGifData = Lib.load("nGD","ImageGifData",1);
	private static var gd_imagePng = Lib.load("nGD","ImagePng",2);
	private static var gd_imagePngData = Lib.load("nGD","ImagePngData",1);
	private static var gd_imageGd = Lib.load("nGD","ImageGd",2);
	private static var gd_imageGd2 = Lib.load("nGD","ImageGd2",4);
	private static var gd_makeImageToPalette = Lib.load("nGD","MakeImageToPalette",3);
	private static var gd_cloneImageToPalette = Lib.load("nGD","CloneImageToPalette",3);
	private static var gd_imageX = Lib.load("nGD","ImageX",1);
	private static var gd_imageY = Lib.load("nGD","ImageY",1);
	private static var gd_imageTrueColor = Lib.load("nGD","ImageTrueColor",1);	
	private static var gd_cloneImage = Lib.load("nGD","CloneImage",1);
	private static var gd_getImagePart = Lib.load("nGD","GetImagePart",5);
	private static var gd_imageResize = Lib.load("nGD","ImageResize",4);
	private static var gd_imageRotate = Lib.load("nGD","ImageRotate",2);
	private static var gd_imageAttach = Lib.load("nGD","ImageCopyMerge",-1);
	private static var gd_imageStringTTF = Lib.load("nGD","ImageStringTTF",-1);
	
	

}
