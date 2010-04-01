/*
 *      nGDImage.c
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

#define abs(i)	(i>0?i:-i)


DEFINE_KIND(ImagePtr);


#define imageAntiAliased 1
#define imageBrushed 2 //unused
#define imageTiled 4 //unused
#define imageStyled 8

struct _ImageData {
	int config;
	int color;
	int thickness;
	gdImagePtr img;
	//gdImagePtr brush;
};

typedef struct _ImageData *ImageData;


#define imageIsAntiAliased(i)		((((i->config) & imageAntiAliased) == imageAntiAliased)?1:0)
#define imageIsStyled(i)			((((i->config) & imageStyled) == imageStyled)?1:0)
#define imageSetAntiAliased(i,a)	(i->config = ((a==1) ? (i->config | imageAntiAliased) : (i->config & ~imageAntiAliased)))
#define imageSetStyled(i,a)			(i->config = ((a==1) ? (i->config | imageStyled) : (i->config & ~imageStyled)))
#define imageConfig(i)				(i->config)
#define imageThickness(i)			(i->thickness)
#define imageImage(i)				(i->img)

int imageColor(ImageData img) {
	if (imageIsStyled(img)==1)
		return gdStyled;
	if (imageThickness(img)==1) {
		if (imageIsAntiAliased(img)==0)
			return img->color;
		else
			return gdAntiAliased;
	}
	else {
		return img->color;
	}
}

ImageData getImage(value img) {
	val_check_kind(img,ImagePtr);
	return val_data(img);
}

/*
 * 
 * Brushing & Tiles seem to does not work with many gd versions
 * 
 * 
void setBrushImage(ImageData in,ImageData cl) {
	gdImagePtr cld;	
	if (gdImageTrueColor(imageImage(in))) {
	//	printf("clone true color\n");
		cld = gdImageCreateTrueColor(gdImageSX(imageImage(in)),gdImageSY(imageImage(in)));
	}
	else {
//		printf("clone palette\n");
		cld = gdImageCreate(gdImageSX(imageImage(in)),gdImageSY(imageImage(in)));
	}
//	printf("made copy\n");
	gdImageCopy(cld,imageImage(in),0,0,0,0,gdImageSX(imageImage(in)),gdImageSY(imageImage(in)));
	imageBrush(in)=cld;
}

value SetBrush(value img,value brush, value flag) {
	ImageData _img = getImage(img);
	if (val_bool(flag)==1) {
		imageSetTiled(_img,0);
		imageSetBrushed(_img,1);
		ImageData _brush = getImage(brush);
		//printf("before clone\n");
		setBrushImage(_img,_brush);	
		//(imageImage(_brush));	
		//printf("after clone\n");
	}
	return val_null;
}

value SetTile(value img, value tile, value flag) {
	ImageData _img = getImage(img);
	if (val_bool(flag)==1) {
		imageSetBrushed(_img,0);
		imageSetTiled(_img,1);
		ImageData _tile = getImage(tile);
		setBrushImage(_img,_tile);
	}
	return val_null;
} */

value FreeImage (value v) {
	ImageData img = getImage(v);
	gdImageDestroy(imageImage(img));
//	if (imageBrush(img)!=NULL)
//		gdImageDestroy(imageBrush(img));
	return val_null;
}

// called by the garbage collector
void finalize( value v ) {
	FreeImage(v);
}

// allocate an image that could be garbage collected
value alloc_gc_image(gdImagePtr image) {
	ImageData abstr = (ImageData)alloc_private(sizeof(ImageData));
	imageImage(abstr) = image;
	imageConfig(abstr) = 0;
	imageThickness(abstr) = 0;
	//imageBrush(abstr) = NULL;
	value ret = alloc_abstract(ImagePtr,abstr);
	val_gc(ret,finalize);
	return ret;
}

// setting current drawing color
int initColor(ImageData img,value color) {
	
	//imageSetBrushed(img,0);
	//imageSetTiled(img,0);
	imageSetStyled(img,0);	
	
	// 0xRRGGBBAA = color
	
	int _color = val_int(color);
	int alpha = (255 -(0x000000FF & _color)) >> 1; // gd alpha information is just 1 byte and reverse
	int red = 	(0xFF000000 & _color) >> 24;
	int green =	(0x00FF0000 & _color) >> 16;
	int blue =	(0x0000FF00 & _color) >> 8;
	
	int c = gdImageColorResolveAlpha(imageImage(img),red,green,blue,alpha);
	
	if (imageIsAntiAliased(img)==1) //setting back antiAliasing
		gdImageSetAntiAliased(imageImage(img),c);	
	
	return c;
	
}

// setting style of line drawing
value SetStyle(value img,value colors) {
	ImageData _img = getImage(img);
	int n = val_array_size(colors);
	value *_colors = val_array_ptr(colors);
	int style[n];
	int i;
	for (i=0;i<n;i++)
		style[i]=initColor(_img,_colors[i]);
	imageSetStyled(_img,1);
	gdImageSetStyle(imageImage(_img),style,n);
	return val_null;		
}

// toggeling antialiasing
value SetAntiAliasing (value img, value antiAlias) {
	ImageData _img = getImage(img);
	
	imageSetAntiAliased(_img,val_bool(antiAlias));

	if (imageIsAntiAliased(_img)==1)
		gdImageSetAntiAliased(imageImage(_img),imageColor(_img));

	return val_null;	
}


// setting thickness of drawing functions
value SetThickness(value img, value thickness) {
	ImageData _img = getImage(img);
	imageThickness(_img) = abs(val_int(thickness));
	gdImageSetThickness(imageImage(_img),imageThickness(_img));
	
	//this is somekind of useless, using drawing function with thickness & antialiasing
	//does not work in most GD versions, so ignored @ imageColor
	if (imageIsAntiAliased(_img)==1)
		gdImageSetAntiAliased(imageImage(_img),imageColor(_img));
	return alloc_int(imageThickness(_img));
}

// setting current drawing color
value SetColor(value img, value color) {
	ImageData _img = getImage(img);
	_img->color = initColor(_img,color);	
	return val_null;	
}
