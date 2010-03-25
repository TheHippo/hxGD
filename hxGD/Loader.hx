/*
 *      hxGD.Loader.hx
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

class Loader {
	
	/**
	 * loads a jpeg image
	 * @param	filename
	 * @return Image
	 */	
	public static inline function createFromJpeg (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromJpeg(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	/**
	 * loads a png image
	 * @param	filename
	 * @return Image
	 */
	public static inline function createFromPng (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromPng(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	/**
	 * loads a gif image, if animated just the first frame
	 * @param	filename
	 * @return Image
	 */
	public static inline function createFromGif (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromGif(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	/**
	 * loads a gd 1 image
	 * @param	filename
	 * @return Image
	 */
	public static inline function createFromGd (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromGd(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	/**
	 * loads a gd 2 image
	 * @param	filename
	 * @return Image
	 */
	public static inline function createFromGd2 (filename:String):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromGd2(Lib.haxeToNeko(filename));
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	/**
	 * loads just a part of a gd 2 image
	 * @param	filename
	 * @param	srcX
	 * @param	srcY
	 * @param	width
	 * @param	height
	 * @return Image
	 */
	public static inline function createFromGd2Part (filename:String,srcX:Int,srcY:Int,width:Int,height:Int):Image {
		var ret:Image = Type.createEmptyInstance(Image);
		ret.img = gd_imageCreateFromGd2Part(Lib.haxeToNeko(filename),srcX,srcY,width,height);
		ret.graphics = new Graphics(ret.img);
		return ret;
	}
	
	/**
	 * loads a bitmap image
	 * @param	filename
	 * @return Image
	 */
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
