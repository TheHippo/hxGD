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



value ImageCreateFromJpeg(value filename);

value ImageCreateFromPng(value filename);

value ImageCreateFromGif(value filename);

value ImageCreateFromGd(value filename);

value ImageCreateFromGd2(value filename);

value ImageCreateFromGd2Part(value filename, value srcX, value srcY, value width, value height);

value ImageCreateFromWBMP(value filename);

value ImageJpeg(value img,value filename,value quality);

value ImageJpegData(value img,value quality);

value ImageGif(value img,value filename);

value ImageGifData(value img);

value ImagePng(value img,value filename);

value ImagePngData(value img);

value ImageGd (value img,value filename);

value ImageGd2 (value img,value filename,value compressed,value chunksize);
