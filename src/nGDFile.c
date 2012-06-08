/*
 *      nGDFile.c
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

// loading and saving from files, really straight

FILE* openFileRead(value filename) {
	val_check(filename, string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename, "r");
	if (_file == NULL) failure("file not found / could not be loaded");
	return _file;
}

FILE* openFileWrite(value filename) {
	val_check(filename, string);
	char *_filename = val_string(filename);
	FILE *_file = fopen(_filename, "wb");
	if (_file == NULL) failure("file not found / could not be loaded");
	return _file;
}

value ImageCreateFromJpeg(value filename) {
	FILE *_file = openFileRead(filename);
	gdImagePtr img = gdImageCreateFromJpeg(_file);
	fclose(_file);
	if (img == NULL) failure("image file could not be loaded: probably wrong format");
	value ret = alloc_gc_image(img);
	return ret;
}

value ImageCreateFromPng(value filename) {
	FILE *_file = openFileRead(filename);
	gdImagePtr img = gdImageCreateFromPng(_file);
	fclose(_file);
	if (img == NULL) failure("image file could not be loaded: probably wrong format");
	return alloc_gc_image(img);
}

value ImageCreateFromGif(value filename) {
	FILE *_file = openFileRead(filename);
	gdImagePtr img = gdImageCreateFromGif(_file);
	fclose(_file);
	if (img == NULL) failure("image file could not be loaded: probably wrong format");
	return alloc_gc_image(img);
}

value ImageCreateFromGd(value filename) {
	FILE *_file = openFileRead(filename);
	gdImagePtr img = gdImageCreateFromGd(_file);
	fclose(_file);
	return alloc_gc_image(img);
}

value ImageCreateFromGd2(value filename) {
	FILE *_file = openFileRead(filename);
	gdImagePtr img = gdImageCreateFromGd2(_file);
	fclose(_file);
	return alloc_gc_image(img);
}

value ImageCreateFromGd2Part(value filename, value srcX, value srcY, value width, value height) {
	FILE *_file = openFileRead(filename);
	int _srcX = val_int(srcX);
	int _srcY = val_int(srcY);
	int _width = val_int(width);
	int _height = val_int(height);
	gdImagePtr img = gdImageCreateFromGd2Part(_file,_srcX,_srcY,_width,_height);
	fclose(_file);
	return alloc_gc_image(img);
}

value ImageCreateFromWBMP(value filename) {
	FILE *_file = openFileRead(filename);
	gdImagePtr img = gdImageCreateFromWBMP(_file);
	fclose(_file);
	return alloc_gc_image(img);
}


value ImageJpeg(value img,value filename,value quality) {
	int _quality = val_int(quality);
	ImageData _img = getImage(img);
	FILE *_file = openFileWrite(filename);
	gdImageJpeg(imageImage(_img),_file,_quality);
	fclose(_file);	
	return val_null;
}

value ImageJpegData(value img, value quality) {
	ImageData _img = getImage(img);
	int _quality = val_int(quality);
	int size;
	void *ptr = gdImageJpegPtr(imageImage(_img),&size,_quality);
	buffer ret = alloc_buffer(NULL);
	buffer_append_sub(ret,ptr,size);
	gdFree(ptr);
	return buffer_to_string(ret);
}

value ImageGif(value img,value filename) {
	ImageData _img = getImage(img);
	FILE *_file = openFileWrite(filename);
	gdImageGif(imageImage(_img),_file);
	fclose(_file);	
	return val_null;
}

value ImageGifData(value img) {
	ImageData _img = getImage(img);
	int size;
	void *ptr = gdImageGifPtr(imageImage(_img),&size);
	buffer ret = alloc_buffer(NULL);
	buffer_append_sub(ret,ptr,size);
	gdFree(ptr);
	return buffer_to_string(ret);
}

value ImagePng(value img,value filename) {
	ImageData _img = getImage(img);
	FILE *_file = openFileWrite(filename);
	gdImagePng(imageImage(_img),_file);
	fclose(_file);	
	return val_null;
}

value ImagePngData(value img) {
	ImageData _img = getImage(img);
	int size;
	void *ptr = gdImagePngPtr(imageImage(_img),&size);
	buffer ret = alloc_buffer(NULL);
	buffer_append_sub(ret,ptr,size);
	gdFree(ptr);
	return buffer_to_string(ret);
}

value ImageGd (value img,value filename) {
	ImageData _img = getImage(img);
	FILE *_file = openFileWrite(filename);
	gdImageGd(imageImage(_img),_file);
	fclose(_file);	
	return val_null;
}

value ImageGd2 (value img,value filename,value compressed,value chunksize) {
	ImageData _img = getImage(img);
	int _compressed = val_int(compressed);
	int _chunksize = val_int(chunksize);
	FILE *_file = openFileWrite(filename);
	gdImageGd2(imageImage(_img),_file,_chunksize,_compressed);
	fclose(_file);	
	return val_null;
}
