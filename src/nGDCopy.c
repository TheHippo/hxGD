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

// making a copy of the given image.
// color and setting are not copied!!
value CloneImage(value img) {
	ImageData _img = getImage(img);
	gdImagePtr cd = gdImageCreateTrueColor(gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)));
	gdImageCopy(cd,imageImage(_img),0,0,0,0,gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)));
	value ret = alloc_gc_image(cd);
	return ret;
}


// returns small part of the image as a new image
value GetImagePart(value img,value x,value y,value w,value h) {
	ImageData _img = getImage(img);
	int _x = val_int(x);
	int _y = val_int(y);	
	int _w = val_int(w);
	int _h = val_int(h);
	gdImagePtr cd = gdImageCreateTrueColor(_w,_h);
	gdImageCopy(cd,imageImage(_img),0,0,_x,_y,_w,_h);
	value ret = alloc_gc_image(cd);
	return ret;
}


// resizes an image
value ImageResize(value img, value w,value h,value resample) {
	ImageData _img = getImage(img);
	int _w = val_int(w);
	int _h = val_int(h);
	int _r = val_bool(resample);
	gdImagePtr cd;
	
	//creating new one
	if (gdImageTrueColor(imageImage(_img)))
		cd = gdImageCreateTrueColor(_w,_h);
	else
		cd = gdImageCreate(_w,_h);
	
	//copy	
	if (_r)
		gdImageCopyResampled(cd,imageImage(_img),0,0,0,0,_w,_h,gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)));
	else
		gdImageCopyResized(cd,imageImage(_img),0,0,0,0,_w,_h,gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)));
	
	//cleanup
	gdImageDestroy(imageImage(_img));
	imageImage(_img) = cd;
	
	//transfering style
	imageSetStyled(_img,0);
	initColor(_img,alloc_int(_img->color));
	return val_null;
}

//rotates an image by the given angle arround his middle
value ImageRotate(value img,value angle) {
	ImageData _img = getImage(img);
	int _angle = val_int(angle);
	gdImagePtr cd;
	
	//creating new image
	if (gdImageTrueColor(imageImage(_img)))
		cd = gdImageCreateTrueColor(gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)));
	else
		cd = gdImageCreate(gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)));
		
	//copy image
	gdImageCopyRotated(cd,imageImage(_img),(double)gdImageSX(imageImage(_img))/2,(double)gdImageSY(imageImage(_img))/2,0,0,gdImageSX(imageImage(_img)),gdImageSY(imageImage(_img)),_angle);
	
	//cleanup
	gdImageDestroy(imageImage(_img));
	imageImage(_img) = cd;
	
	//transfering style
	imageSetStyled(_img,0);
	initColor(_img,alloc_int(_img->color));	
	return val_null;
}


//copy an image into another one. blending image by a certain percentage

//value ImageCopyMerge(value img,value attach, value dstX, value dstY, value srcX, value srcY, value w, value h, value pct) {
value ImageCopyMerge(value *args, int nargs) {
	enum {eImg,eAttach,eDstX,eDstY,eSrcX,eSrcY,eW,eH,ePct,eSize};
	if (nargs!=eSize)
		neko_error();
	ImageData img = getImage(args[eImg]);
	ImageData attach = getImage(args[eAttach]);
	int dstX = val_int(args[eDstX]);
	int dstY = val_int(args[eDstY]);
	int srcX = val_int(args[eSrcX]);
	int srcY = val_int(args[eSrcY]);
	int w = val_int(args[eW]);
	int h = val_int(args[eH]);
	int pct = val_int(args[ePct]);
	
	gdImageCopyMerge(imageImage(img),imageImage(attach),dstX,dstY,srcX,srcY,w,h,pct);
	
	return val_null;
}
