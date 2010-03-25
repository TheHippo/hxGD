/*
 *      nGDCopy.c
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
#include "nGDImage.h"

value CloneImage(value img) {
	ImageData _img = getImage(img);
	gdImagePtr cd = gdImageCreateTrueColor(gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)));
	gdImageCopy(cd,imageImage(_img),0,0,0,0,gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)));
	value ret = alloc_gc_image(cd);
	return ret;
}

// void gdImageCopy(gdImagePtr dst, gdImagePtr src, int dstX, int dstY, int srcX, int srcY, int w, int h)

value GetImagePart(value img,value x,value y,value w,value h) {
	ImageData _img = getImage(img);
	int _x = abs(val_int(x));
	int _y = abs(val_int(y));	
	int _w = abs(val_int(w));
	int _h = abs(val_int(h));
	gdImagePtr cd = gdImageCreateTrueColor(_w,_h);
	gdImageCopy(cd,imageImage(_img),0,0,_x,_y,_w,_h);
	value ret = alloc_gc_image(cd);
	return ret;
}
