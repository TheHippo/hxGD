/*
 *      nGD.c
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

#include <gd.h>
#include <neko.h>
#include <stdio.h>
#include <stdlib.h>
#include "nGDFile.h"
#include "nGDImage.h"
#include "nGDDraw.h"
#include "nGDCopy.h"


value ImageCreate(value x,value y, value back) {
	int _x = val_int(x);
	int _y = val_int(y);
	gdImagePtr img = gdImageCreate(_x,_y);
	value ret = alloc_gc_image(img);
	ImageData i = getImage(ret);
	initColor(i,back);
	return ret;
}

value ImageCreateTrueColor(value x,value y,value back) {
	int _x = val_int(x);
	int _y = val_int(y);
	gdImagePtr img = gdImageCreateTrueColor(_x,_y);
	value ret = alloc_gc_image(img);
	ImageData i = getImage(ret);
	int _color = initColor(i,back);
	gdImageFill(imageImage(i),0,0,_color);
	return ret;
}

value MakeImageToPalette(value img,value dither,value anzColors) {
	ImageData _img = getImage(img);
	int _dither = val_bool(dither);
	int _anzColors = val_int(anzColors);
	gdImageTrueColorToPalette(imageImage(_img),_dither,_anzColors);
	return val_null;	
}

value CloneImageToPalette(value img,value dither, value anzColors) {
	ImageData _img = getImage(img);
	int _dither = val_bool(dither);
	int _anzColors = val_int(anzColors);
	gdImagePtr _clone = gdImageCreatePaletteFromTrueColor(imageImage(_img),_dither,_anzColors);
	return alloc_gc_image(_clone);	
}


value ImageX(value img) {
	ImageData _img = getImage(img);
	int x = gdImageSX(imageImage(_img));
	return alloc_int(x);
}

value ImageY(value img) {
	ImageData _img = getImage(img);
	int y = gdImageSY(imageImage(_img));
	return alloc_int(y);
}


value ImageTrueColor(value img) {
	ImageData _img = getImage(img);
	int tc = gdImageTrueColor(imageImage(_img));
	if (tc!=0)
		return val_true;
	else
		return val_false;
}


DEFINE_PRIM(SetAntiAliasing,2);
DEFINE_PRIM(SetThickness,2);
DEFINE_PRIM(SetColor,2);
DEFINE_PRIM(FreeImage,1);
DEFINE_PRIM(ImageCreate,3);
DEFINE_PRIM(ImageCreateTrueColor,3);
DEFINE_PRIM(ImageCreateFromJpeg,1);
DEFINE_PRIM(ImageCreateFromPng,1);
DEFINE_PRIM(ImageCreateFromGif,1);
DEFINE_PRIM(ImageCreateFromGd,1);
DEFINE_PRIM(ImageCreateFromGd2,1);
DEFINE_PRIM(ImageCreateFromGd2Part,5);
DEFINE_PRIM(ImageCreateFromWBMP,1);
DEFINE_PRIM(ImageJpeg,3);
DEFINE_PRIM(ImageGif,2);
DEFINE_PRIM(ImagePng,2);
DEFINE_PRIM(ImageGd,2);
DEFINE_PRIM(ImageGd2,4);
DEFINE_PRIM(MakeImageToPalette,3);
DEFINE_PRIM(CloneImageToPalette,3);
DEFINE_PRIM(ImageX,1);
DEFINE_PRIM(ImageY,1);
DEFINE_PRIM(ImageTrueColor,1);
DEFINE_PRIM(SetPixel,3);
DEFINE_PRIM(ImageLine,5);
DEFINE_PRIM(ImageDashedLine,5);
DEFINE_PRIM(ImagePolygon,3);
DEFINE_PRIM(ImageOpenPolygon,3);
DEFINE_PRIM(ImageRectangle,5);
DEFINE_PRIM(ImageFilledPolygon,3);
DEFINE_PRIM(ImageFilledRectangle,5);
DEFINE_PRIM_MULT(ImageArc);
DEFINE_PRIM_MULT(ImageFilledArc);
DEFINE_PRIM(ImageFilledEllipse,5);
DEFINE_PRIM(ImageFillToBorder,4);
DEFINE_PRIM(ImageFill,3);
//DEFINE_PRIM(SetBrush,3);
//DEFINE_PRIM(SetTile,3);
DEFINE_PRIM(SetStyle,2);
