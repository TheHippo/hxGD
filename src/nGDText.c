/*
 *      nGDText.c
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

#include <neko.h>
#include <gd.h>
#include "nGDImage.h"

#define getAntiAliasingColor(color,anti)	((anti==0)?color:-color)


//value ImageStringTTF(value img,value fontname,value ptsize, value angle, value x, value y,value string, value align, value antiAntiAlias, value color) {
value ImageStringTTF(value *args,int nargs) {
	enum {eImg,eFontname,ePtsize,eAngle,eX,eY,eString,eAlign,eAntiAlias,eColor,eSize};
	if (nargs!=eSize)
		neko_error();
	ImageData _img = getImage(args[eImg]);
	char *_fontname = val_string(args[eFontname]);
	double _ptsize = val_float(args[ePtsize]);
	double _angle = val_float(args[eAngle]);
	int _x = val_int(args[eX]);
	int _y = val_int(args[eY]);
	char *_string = val_string(args[eString]);
	int _align = val_int(args[eAlign]);
	int _antiAliasing = val_bool(args[eAntiAlias]);

	
	//calculation size of output
	int brect[8];
	char *err;
	err = gdImageStringFT(NULL,&brect[0],0,_fontname,_ptsize,_angle,0,0,_string);
	if (err)
		val_throw(alloc_string(err));
		
	int width = brect[2] - brect[6];
	int height = brect[3] - brect[7];
	
	switch (_align) {
		case 0: // LeftTop
			break; 
		case 1: // CenterTop
			_x-=width/2;
			break;
		case 2: // RightTop
			_x-=width;
			break;
		case 3: // LeftMiddle
			_y-=height/2;
			break;
		case 4: // CenterMiddle
			_y-=height/2;
			_x-=width/2;
			break;
		case 5: // Right Middle
			_y-=height/2;
			_x-=width;
			break;
		case 6: // LeftBottom
			_y-=height;
			break;
		case 7: // CenterBottom
			_y-=height;
			_x-=width/2;
			break;
		case 8: // RightBottom
			_y-=height;
			_x-=width;
			break;
		default: //something went wrong
			val_throw(alloc_string("unknown position type"));
			break;	
	}
	
	_y+=height;

	
	//drawing
	int _color = initColor(_img,args[eColor]);
	err = gdImageStringFT(imageImage(_img),&brect[0],getAntiAliasingColor(_color,_antiAliasing),_fontname,_ptsize,_angle,_x,_y,_string);
	if (err)
		val_throw(alloc_string(err));

	return val_null;	
}
