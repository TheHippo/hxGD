/*
 *      nGD.c
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

#include <gd.h>
#include <neko.h>
#include <stdio.h>
#include <stdlib.h>
#include "nGDFile.h"
#include "nGDImage.h"
#include "nGDDraw.h"
#include "nGDCopy.h"
#include "nGDText.h"
#include "nGDAnim.h"


// creates a new image a given background color
value ImageCreate(value x,value y, value back,value trueColor) {
	int _x = val_int(x);
	int _y = val_int(y);
	int _trueColor = val_bool(trueColor);
	
	value ret;
	gdImagePtr img;
	
	if (_trueColor==1) {
		img = gdImageCreateTrueColor(_x,_y);
		ret = alloc_gc_image(img);
		ImageData i = getImage(ret);
		int _c = initColor(i,back);
		gdImageFill(imageImage(i),0,0,_c);	
	}
	else {
		img = gdImageCreate(_x,_y);
		ret = alloc_gc_image(img);
		initColor(getImage(ret),back);
	}
	return ret;
}

// converts a truecolor image into a palette-based image
value MakeImageToPalette(value img,value dither,value anzColors) {
	ImageData _img = getImage(img);
	int _dither = val_bool(dither);
	int _anzColors = val_int(anzColors);
	gdImageTrueColorToPalette(imageImage(_img),_dither,_anzColors);
	return val_null;	
}

// make a copy of a of truecolor images and makes the copy palette-based
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
DEFINE_PRIM(ImageCreate,4);
DEFINE_PRIM(ImageCreateFromJpeg,1);
DEFINE_PRIM(ImageCreateFromPng,1);
DEFINE_PRIM(ImageCreateFromGif,1);
DEFINE_PRIM(ImageCreateFromGd,1);
DEFINE_PRIM(ImageCreateFromGd2,1);
DEFINE_PRIM(ImageCreateFromGd2Part,5);
DEFINE_PRIM(ImageCreateFromWBMP,1);
DEFINE_PRIM(ImageJpeg,3);
DEFINE_PRIM(ImageJpegData,2);
DEFINE_PRIM(ImageGif,2);
DEFINE_PRIM(ImageGifData,1);
DEFINE_PRIM(ImagePng,2);
DEFINE_PRIM(ImagePngData,1);
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
DEFINE_PRIM(ImagePolygon,5);
DEFINE_PRIM_MULT(ImageRectangle);
DEFINE_PRIM_MULT(ImageArc);
DEFINE_PRIM_MULT(ImageFilledArc);
DEFINE_PRIM(ImageFilledEllipse,5);
DEFINE_PRIM(ImageFillToBorder,4);
DEFINE_PRIM(ImageFill,3);
DEFINE_PRIM(SetStyle,2);
DEFINE_PRIM(CloneImage,1);
DEFINE_PRIM(GetImagePart,5);
DEFINE_PRIM(ImageResize,4);
DEFINE_PRIM(ImageRotate,2);
DEFINE_PRIM_MULT(ImageCopyMerge);
DEFINE_PRIM_MULT(ImageStringTTF);
DEFINE_PRIM_MULT(RenderGifAnimation);
DEFINE_PRIM(InitAnimation,0);
DEFINE_PRIM(AddImage,2);
