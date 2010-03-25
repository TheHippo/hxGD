/*
 *      hxGD.Graphics.hx
 *      
 *      Copyright 2009 Philipp Klose <hippo@byteanvil.com>
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

enum ArcFillType {
	ArcFilled;
	ArcOutline;
	ArcBorder;
	ChordFilled;
	ChordOutline;
	ChordBorder;
}

class Graphics {
	
	/**
	 * default drawing color
	 */
	public static var defaultColor:Color = Color.ofRGB(0x000000);
	/**
	 * default drawing thickness. if different from 1 antialiasing setting will be ignored
	 */
	public static var defaultThickness:Int = 1;
	/**
	 * default antialiasing settings
	 */
	public static var defaultAntiAliasing:Bool = true;
	
	
	/**
	 * stores the neko abstract image data
	 */
	private var img:Void;
	
	/**
	 * drawing color
	 */
	public var color(getColor,setColor):Color;
	private var _color:Color;

	/**
	 * Drawing thickness. If it is different from 1 antialiasing settings will be ignored
	 */
	public var thickness(getThickness,setThickness):Int;
	private var _thickness:Int;
	
	/**
	 * Should all drawing operations be antialiased? Ignored if thickness if not 1
	 */
	public var antiAliasing(getAntiAliasing,setAntiAliasing):Bool;
	private var _antiAliasing:Bool;
	

	/**
	 * creates a new graphics canvas
	 * @param	img	neko abstract data
	 */
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
	
	
	/**
	 * setting style for drawing options.
	 * Example: colors = [redColor,transparentColor] will make a red dotted line
	 * @param	colors Array with all colors
	 */
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
	
	/**
	 * draws a line on the canvas
	 * @param	x1 startpostion x
	 * @param	y1 startposition y
	 * @param	x2 endposition x
	 * @param	y2 endposition y
	 * @param	?dashed simple dashed line?
	 */
	public inline function line(x1:Int,y1:Int,x2:Int,y2:Int,?dashed:Bool=false):Void {
		if (dashed)
			gd_imageDashedLine(img,x1,y1,x2,y2);
		else
			gd_imageLine(img,x1,y1,x2,y2);
	}
	
	/**
	 * draws a polygon with at least 3 points
	 * @param	poly the polygon
	 * @param	?open open polygon
	 * @param	?filled filled polygon (only if polygon is not open!)
	 */
	public inline function polygon(poly:Polygon,?open:Bool=false,?filled:Bool=false):Void {
		gd_imagePolygon(img,poly.x,poly.y,open,filled);
	}
	
	/**
	 * draws a rectangle
	 * @param	x upper left corner x position
	 * @param	y upper left corner y position
	 * @param	width
	 * @param	height
	 * @param	?filled
	 */
	public inline function rectangle(x:Int,y:Int,width:Int,height:Int,?filled:Bool=false):Void {
		gd_imageRectangle(img,x,y,width,height,filled);
	}
	
	/**
	 * draws a ellipse
	 * @param	x center x position
	 * @param	y center y position
	 * @param	width
	 * @param	height
	 * @param	?filled
	 */
	public inline function ellipse(x:Int, y:Int, width:Int,height:Int,?filled:Bool=false):Void {
		if (filled)
			gd_imageFilledEllipse(img,x,y,width,height);
		else
			gd_imageArc(img,x,y,width,height,0,360);
	}
	
	/**
	 * draws a circle
	 * @param	x center x position
	 * @param	y center y position
	 * @param	radius
	 * @param	?filled
	 */
	public inline function circle(x:Int, y:Int, radius:Int,?filled:Bool=false):Void {
		if (filled)
			gd_imageFilledArc(img,x,y,radius*2,radius*2,0,360,0);
		else
			gd_imageArc(img,x,y,radius*2,radius*2,0,360);
	}
	
	/**
	 * draws a arc
	 * @param	x center x position
	 * @param	y center y position
	 * @param	width
	 * @param	height
	 * @param	start starting degree of arc 0-360 smaller then end
	 * @param	end ending degree of arc 0-360 larger then start
	 * @param	fillType see ArcFillType
	 */
	public inline function arc(x:Int,y:Int, width:Int,height:Int, start:Int, end:Int, fillType:ArcFillType):Void {
		switch (fillType) {
			case ArcFilled:		gd_imageFilledArc(img,x,y,width,height,start,end,0);
			case ArcOutline:	gd_imageFilledArc(img,x,y,width,height,start,end,2);
			case ArcBorder:		gd_imageFilledArc(img,x,y,width,height,start,end,6);
			case ChordFilled:	gd_imageFilledArc(img,x,y,width,height,start,end,1);
			case ChordOutline:	gd_imageFilledArc(img,x,y,width,height,start,end,3);
			case ChordBorder:	gd_imageFilledArc(img,x,y,width,height,start,end,7);
		}
	}
	
	/**
	 * start to fill the image from the given position in all directions until the borderColor is reached
	 * @param	x
	 * @param	y
	 * @param	borderColor
	 */
	public inline function fillToBorder(x:Int,y:Int, borderColor:Color):Void {
		gd_imageFillToBorder(img,x,y,borderColor.gd);		
	}
	
	/**
	 * fills the image from starting point into all directions as long the current pixel color matches the pixel color of the starting point
	 * @param	x
	 * @param	y
	 */
	public inline function fill(x:Int, y:Int) {
		gd_imageFill(img,x,y);	
	}
	
	private static var gd_setAntiAliasing = Lib.load("nGD","SetAntiAliasing",2);
	private static var gd_setThickness = Lib.load("nGD","SetThickness",2);
	private static var gd_setColor = Lib.load("nGD","SetColor",2);
	private static var gd_setPixel = Lib.load("nGD","SetPixel",3);
	private static var gd_imageLine = Lib.load("nGD","ImageLine",5);
	private static var gd_imageDashedLine = Lib.load("nGD","ImageDashedLine",5);
	private static var gd_imagePolygon = Lib.load("nGD","ImagePolygon",5);
	private static var gd_imageRectangle = Lib.load("nGD","ImageRectangle",-1);
	private static var gd_imageFilledEllipse = Lib.load("nGD","ImageFilledEllipse",5);
	private static var gd_imageArc = Lib.load("nGD","ImageArc",-1);
	private static var gd_imageFilledArc = Lib.load("nGD","ImageFilledArc",-1);
	private static var gd_imageFillToBorder = Lib.load("nGD","ImageFillToBorder",4);
	private static var gd_imageFill = Lib.load("nGD","ImageFill",3);
	//private static var gd_setBrush = Lib.load("nGD","SetBrush",3);
	//private static var gd_setTile = Lib.load("nGD","SetTile",3);
	private static var gd_setStyle = Lib.load("nGD","SetStyle",2);

}
