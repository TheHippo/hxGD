/*
 *      nGDImage.h
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

//#define abs(i)	(i>0?i:-i)

#define imageAntiAliased 1
#define imageBrushed 2 //unused
#define imageTiled 4 //unused
#define imageStyled 8

struct _ImageData {
	int config;
	int color;
	int thickness;
	gdImagePtr img;
};

typedef struct _ImageData *ImageData;



#define imageIsAntiAliased(i)		((((i->config) & imageAntiAliased) == imageAntiAliased)?1:0)
#define imageIsStyled(i)			((((i->config) & imageStyled) == imageStyled)?1:0)
#define imageSetAntiAliased(i,a)	(i->config = ((a==1) ? (i->config | imageAntiAliased) : (i->config & ~imageAntiAliased)))
#define imageSetStyled(i,a)			(i->config = ((a==1) ? (i->config | imageStyled) : (i->config & ~imageStyled)))
#define imageConfig(i)				(i->config)
#define imageThickness(i)			(i->thickness)
#define imageImage(i)				(i->img)



int imageColor(ImageData img);

ImageData getImage(value img);

value FreeImage(value v);

value alloc_gc_image(gdImagePtr image);

int initColor(ImageData img,value color);

value SetStyle(value img,value colors);

//value SetBrush(value img,value brush, value flag);

//value SetTile(value img, value tile, value flag);

value SetAntiAliasing (value img, value antiAlias);

value SetThickness(value img, value thickness);

value SetColor(value img, value color);
