/*
 *      hxGD.Color.hx
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

class Color {

	/**
	 * internal gd representation of a color
	 */
	public var gd(gdColor, null):Int;
	/**
	 * red channel 0-255
	 */
	public var red:Int;
	/**
	 * green channel 0-255
	 */
	public var green:Int;
	/**
	 * blue channel 0-255
	 */
	public var blue:Int;
	/**
	 * alpha channel 0-255 0 = transparent; 255 = opaque
	 */
	public var alpha:Int;
	
	/**
	 * create a new color representation
	 * @param	red red channel 0-255
	 * @param	green green channel 0-255
	 * @param	blue blue channel 0-255
	 * @param	?alpha alpha channel 0-255 0 = transparent; 255 = opaque
	 */
	public function new(red:Int,green:Int,blue:Int,?alpha:Int=255) {
		this.red = red;
		this.green = green;
		this.blue = blue;
		this.alpha = alpha;
	//	trace(this);
	}
	
	/**
	 * creates a new color out of a integer (no alpha channel)
	 * @param	color 0xRRGGBB
	 * @return Color
	 */
	public static inline function ofRGB(color:Int):Color {
		//0xRRGGBB
		return new Color(((color & 0xFF0000) >> 16),((color & 0x00FF00) >> 8),(color & 0x0000FF));
	}
	
	/**
	 * creates a new color out of a integer with alpha channel
	 * @param	color 0xRRGGBBAA
	 * @return Color
	 */
	public static inline function ofRGBA(color:Int):Color {
		//0xRRGGBBAA
		return new Color(((color & 0xFF000000) >> 24),((color & 0x00FF0000) >> 16) ,((color & 0x0000FF00) >> 8),(color & 0x000000FF));
	}
	
	private function gdColor():Int {
		return ((((((red << 8) + green) << 8) + blue) << 8 ) + alpha);
	}

}
