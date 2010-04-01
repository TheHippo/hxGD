/*
 *      nGDDraw.c
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
#include <stdlib.h>
#include "nGDImage.h"

// setting a single pixel with the drawing color
value SetPixel(value img,value x,value y) {
	ImageData _img = getImage(img);
	int _x = val_int(x);
	int _y = val_int(y);
	gdImageSetPixel(imageImage(_img),_x,_y,imageColor(_img));
	return val_null;	
}

// draws a line (solid or styled)
value ImageLine(value img,value x1,value y1, value x2, value y2) {
	ImageData _img = getImage(img);
	int _x1 = val_int(x1);
	int _y1 = val_int(y1);
	int _x2 = val_int(x2);
	int _y2 = val_int(y2);
	gdImageLine(imageImage(_img),_x1,_y1,_x2,_y2,imageColor(_img));
	return val_null;
}


// draws a dashed line
value ImageDashedLine(value img,value x1,value y1, value x2, value y2) {
	ImageData _img = getImage(img);
	int _x1 = val_int(x1);
	int _y1 = val_int(y1);
	int _x2 = val_int(x2);
	int _y2 = val_int(y2);
	gdImageDashedLine(imageImage(_img),_x1,_y1,_x2,_y2,imageColor(_img));
	return val_null;
}

// polygon transformation
gdPoint* pointsHaxeToGd (value *x, value *y,int nPoints) {
	gdPoint *points = (gdPoint*)malloc(sizeof(gdPoint)*nPoints);
	int i;
	for (i=0; i<nPoints; i++) {
		points[i].x = val_int(x[i]);
		points[i].y = val_int(y[i]);
	}
	return points;	
}

// draws a polygon
value ImagePolygon(value img,value x,value y, value open, value filled) {
	ImageData _img = getImage(img);
	int _nPoints = val_array_size(x);
	if ((val_array_size(y)==_nPoints) && (_nPoints>2)) { //need same amount of y and x value and at least 3
		value *_x = val_array_ptr(x);
		value *_y = val_array_ptr(y);
		gdPoint *points = pointsHaxeToGd(_x,_y,_nPoints);
		int _open = val_bool(open);
		int _filled = val_bool(filled);
		
		if (_open==1)
			gdImageOpenPolygon(imageImage(_img),points,_nPoints,imageColor(_img));
		else
			if (_filled == 1) //only closed polygon could be filled
				gdImageFilledPolygon(imageImage(_img),points,_nPoints,imageColor(_img));
			else
				gdImagePolygon(imageImage(_img),points,_nPoints,imageColor(_img));
				
		free(points);
		return val_true;
	}
	return val_false;	
}

//value ImageRectangle(value img,value x,value y, value width, value height, value filled) {
value ImageRectangle(value *args, int nargs) {
	enum {eImg,eX,eY,eWidth,eHeight,eFilled,eSize};
	if (nargs != eSize)
		neko_error();
	ImageData _img = getImage(args[eImg]);
	int _x1 = val_int(args[eX]);
	int _y1 = val_int(args[eY]);
	int _x2 = _x1 + val_int(args[eWidth]);
	int _y2 = _y1 + val_int(args[eHeight]);
	int _filled = val_bool(args[eFilled]);
	if (_filled == 1)
		gdImageFilledRectangle(imageImage(_img),_x1,_y1,_x2,_y2,imageColor(_img));
	else
		gdImageRectangle(imageImage(_img),_x1,_y1,_x2,_y2,imageColor(_img));
	return val_null;	
}

//value ImageArc(value img, value x,value y,value width, value height,value start, value end) {
value ImageArc(value *args, int nargs) {
	enum {eImg,eX,eY,eWidth,eHeight,eStart,eEnd,eSize};
	if (nargs != eSize)
		neko_error();
	ImageData _img = getImage(args[eImg]);
	int _x = val_int(args[eX]);
	int _y = val_int(args[eY]);
	int _w = val_int(args[eWidth]);
	int _h = val_int(args[eHeight]);
	int _start = val_int(args[eStart]);
	int _end = val_int(args[eEnd]);
	gdImageArc(imageImage(_img),_x,_y,_w,_h,_start,_end,imageColor(_img));
	return val_null;
}

//value ImageFilledArc(value img, value x,value y,value width, value height,value start, value end, value style) {	
value ImageFilledArc(value *args, int nargs) {
	enum {eImg,eX,eY,eWidth,eHeight,eStart,eEnd,eStyle,eSize};
	if (nargs!=eSize)
		neko_error();
	ImageData _img = getImage(args[eImg]);
	int _x = val_int(args[eX]);
	int _y = val_int(args[eY]);
	int _w = val_int(args[eWidth]);
	int _h = val_int(args[eHeight]);
	int _start = val_int(args[eStart]);
	int _end = val_int(args[eEnd]);
	int _style = val_int(args[eStyle]);
	gdImageFilledArc(imageImage(_img),_x,_y,_w,_h,_start,_end,imageColor(_img),_style);
	return val_null;
}

value ImageFilledEllipse(value img, value x, value y, value w, value h) {
	ImageData _img = getImage(img);
	int _x = val_int(x);
	int _y = val_int(y);
	int _w = val_int(w);
	int _h = val_int(h);
	gdImageFilledEllipse(imageImage(_img),_x,_y,_w,_h,imageColor(_img));
	return val_null;
}

value ImageFillToBorder(value img, value x, value y, value border) {
	ImageData _img = getImage(img);
	int _x = val_int(x);
	int _y = val_int(y);
	int _border = initColor(_img,border);
	gdImageFillToBorder(imageImage(_img),_x,_y,_border,imageColor(_img));
	return val_null;	
}

value ImageFill(value img, value x, value y) {
	ImageData _img = getImage(img);
	int _x = val_int(x);
	int _y = val_int(y);
	gdImageFill(imageImage(_img),_x,_y,imageColor(_img));
	return val_null;	
}
