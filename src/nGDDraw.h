/*
 *      nGDDraw.h
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


value SetPixel(value img,value x,value y);

value ImageLine(value img,value x1,value y1, value x2, value y2);

value ImageDashedLine(value img,value x1,value y1, value x2, value y2);

value ImagePolygon(value img,value x,value y);

value ImageOpenPolygon(value img,value x,value y,value color);

value ImageRectangle(value img,value x,value y, value width, value height);

value ImageFilledPolygon(value img,value x,value y);

value ImageFilledRectangle(value img,value x,value y, value width, value height);

//value ImageArc(value img, value x,value y,value width, value height,value start, value end) {
value ImageArc(value *args, int nargs);

//value ImageFilledArc(value img, value x,value y,value width, value height,value start, value end, value style) {	
value ImageFilledArc(value *args, int nargs);

value ImageFilledEllipse(value img, value x, value y, value w, value h);

value ImageFillToBorder(value img, value x, value y, value border);

value ImageFill(value img, value x, value y);
