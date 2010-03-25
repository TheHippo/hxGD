/*
 *      hxGD.Animation.hx
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

class Animation {
	
	private var filename:String;
	private var delay:Int;
	private var loop:Bool;
	private var optimise:Bool;
	private var globalCM:Bool;
	//private var images:Array<Dynamic>;
	
	private var data:Void;

	public function new(filename:String,delay:Int,?loop:Bool=true,?optimise:Bool=true,globalCM:Bool=true) {
		//this.images = new Array<Image>();
		data = gd_initAnim();
		this.filename = filename;
		this.delay = delay;
		this.loop = loop;
		this.optimise = optimise;
		this.globalCM = globalCM;
	}
	
	public function addImage(image:Image):Void {
		//this.images.push(image.img);
		gd_addImage(data,image.img);
	}
	
	public function render():Void {
		//trace(images.length);
		//try {
			var gi:Dynamic = untyped Lib.haxeToNeko(images);
			var gf:Dynamic = untyped Lib.haxeToNeko(filename);	
			gd_renderGifAnimation(gi,loop,gf,globalCM,delay,optimise);	
		//}
		//catch (e:Dynamic) {
//			trace(e);
	//	}
	}
	
	private static var gd_renderGifAnimation = Lib.load("nGD","RenderGifAnimation",-1);
	private static var gd_initAnim = Lib.load("nGD","InitAnimation",0);
	private static var gd_addImage = Lib.load("nGD","AddImage",2);
	//value InitAnimation();
	//value AddImage(value list,value image);
	//value RenderGifAnimation(value images,value loop,value filename,value globalCM,value delay,value optimise) {
}
