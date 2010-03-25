/*
 *      nGDFile.c
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


#include <neko.h>
#include <gd.h>
#include "nGDImage.h"

// loading and saving from files, really straight


value ImageCreateFromJpeg(value filename) {
	val_check(filename,string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename,"r");
	gdImagePtr img = gdImageCreateFromJpeg(_file);
	fclose(_file);
	value ret = alloc_gc_image(img);
	return ret;
}

value ImageCreateFromPng(value filename) {
	val_check(filename,string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename,"r");
	gdImagePtr img = gdImageCreateFromPng(_file);
	fclose(_file);
	return alloc_gc_image(img);
}

value ImageCreateFromGif(value filename) {
	val_check(filename,string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename,"r");
	gdImagePtr img = gdImageCreateFromGif(_file);
	fclose(_file);
	return alloc_gc_image(img);
}

value ImageCreateFromGd(value filename) {
	val_check(filename,string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename,"r");
	gdImagePtr img = gdImageCreateFromGd(_file);
	fclose(_file);
	return alloc_gc_image(img);
}

value ImageCreateFromGd2(value filename) {
	val_check(filename,string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename,"r");
	gdImagePtr img = gdImageCreateFromGd2(_file);
	fclose(_file);
	return alloc_gc_image(img);
}

value ImageCreateFromGd2Part(value filename, value srcX, value srcY, value width, value height) {
	val_check(filename,string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename,"r");
	int _srcX = val_int(srcX);
	int _srcY = val_int(srcY);
	int _width = val_int(width);
	int _height = val_int(height);
	gdImagePtr img = gdImageCreateFromGd2Part(_file,_srcX,_srcY,_width,_height);
	fclose(_file);
	return alloc_gc_image(img);
}

value ImageCreateFromWBMP(value filename) {
	val_check(filename,string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename,"r");
	gdImagePtr img = gdImageCreateFromWBMP(_file);
	fclose(_file);
	return alloc_gc_image(img);
}


value ImageJpeg(value img,value filename,value quality) {
	char *_filename = val_string(filename);
	int _quality = val_int(quality);
	ImageData _img = getImage(img);
	FILE *_file = fopen(_filename,"wb");
	gdImageJpeg(imageImage(_img),_file,_quality);
	fclose(_file);	
	return val_null;
}

value ImageGif(value img,value filename) {
	char *_filename = val_string(filename);
	ImageData _img = getImage(img);
	FILE *_file = fopen(_filename,"wb");
	gdImageGif(imageImage(_img),_file);
	fclose(_file);	
	return val_null;
}

value ImagePng(value img,value filename) {
	char *_filename = val_string(filename);
	ImageData _img = getImage(img);
	FILE *_file = fopen(_filename,"wb");
	gdImagePng(imageImage(_img),_file);
	fclose(_file);	
	return val_null;
}

value ImageGd (value img,value filename) {
	char *_filename = val_string(filename);
	ImageData _img = getImage(img);
	FILE *_file = fopen(_filename,"wb");
	gdImageGd(imageImage(_img),_file);
	fclose(_file);	
	return val_null;
}

value ImageGd2 (value img,value filename,value compressed,value chunksize) {
	ImageData _img = getImage(img);
	char *_filename = val_string(filename);
	int _compressed = val_int(compressed);
	int _chunksize = val_int(chunksize);
	FILE *_file = fopen(_filename,"wb");
	gdImageGd2(imageImage(_img),_file,_chunksize,_compressed);
	fclose(_file);	
	return val_null;
}
