/*
 *      hxGD.Polygon.hx
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

typedef PolygonPoint = {
	x : Int,
	y : Int
}

class Polygon {
	
	/**
	 * x values, needed to access gd functions
	 */
	public var x(getX, null):Array<Int>;
	/**
	 * y values, needed to access gd functions
	 */
	public var y(getY,null):Array<Int>;
	
	private var _x:Array<Int>;
	private var _y:Array<Int>;

	/**
	 * creates a new polygon, please remember that you need at least 3 point to draw a polygon
	 */
	public function new() {
		_x = new Array<Int>();
		_y = new Array<Int>();
	}
	
	/**
	 * adds a new point to the polygon
	 * @param	x
	 * @param	y
	 */
	public inline function addPoint(x:Int,y:Int):Void {
		_x.push(x);
		_y.push(y);	
	}
	
	/**
	 * adds a PolygonPoint the the polygon
	 * @param	p
	 */
	public inline function addPolygonPoint(p:PolygonPoint):Void {
		_x.push(p.x);
		_y.push(p.y);
	}
	
	private inline function getX():Array<Int> {
		return Lib.haxeToNeko(_x);
	}
	
	private inline function getY():Array<Int> {
		return Lib.haxeToNeko(_y);	
	}

}
