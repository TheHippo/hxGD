/*
 *      nGDAnim.c
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

#include <stdio.h>
#include <gd.h>
#include <neko.h>
#include "nGDImage.h"

DEFINE_KIND(AnimationPtr);


struct _ImageList {
	gdImagePtr img;
	struct _ImageList *next;
};

typedef struct _ImageList *ImageList;

struct _AnimationData {
	int length;
	ImageList list;
};

typedef struct _AnimationData *AnimationData;

#define animationLength(anim) (anim->length)	

/*
 * void gdImageGifAnimBegin(gdImagePtr im, FILE *out, int GlobalCM, int Loops)
 * settings global:
 * 		- global colorpalette
 * 		- looping
 * 		- filename pointer
 * 		- optimize previm
 * 
 * void gdImageGifAnimAdd(gdImagePtr im, FILE *out, int LocalCM, int LeftOfs, int TopOfs, int Delay, int Disposal, gdImagePtr previm)
 * frame
 * 		- delay in 1/100 s
 * 		- int Disposal = gdDisposalNone
 * 
 * void gdImageGifAnimEnd(FILE *out)
 */

#define trace(m)	printf("%s\n",m);

AnimationData GetAnimation(value anim) {
	val_check_kind(anim,AnimationPtr);
	return val_data(anim);
}

value FreeAnim(value anim) {
	trace("clear anim");
	AnimationData _anim = GetAnimation(anim);
	ImageList cur = _anim->list;
	while (cur!=NULL) {
		ImageList del = cur;
		cur = del->next;
		gdImageDestroy(del->img);
	}
	return val_null;
}

void finalizeAnim(value v) {
	FreeAnim(v);
}

value InitAnimation() {
	trace("init anim");
	AnimationData anim = (AnimationData)alloc_private(sizeof(AnimationData));
	anim->length = 0;
	anim->list = NULL;
	value ret = alloc_abstract(AnimationPtr,anim);
	val_gc(ret,finalizeAnim);
	printf("%p - %i\n",anim->list,anim->length);
	printf("returning pointer: %p\n",anim);
	return ret;
}

ImageList newImageListElement(gdImagePtr img) {
	ImageList ret = (ImageList)alloc_private(sizeof(ImageList));
	ret->img = img;
	ret->next = NULL;
	return ret;	
}

value AddImage(value animdata,value image) {
	trace("add image");
	ImageData img = getImage(image);
	AnimationData anim = GetAnimation(animdata);
	printf("%p - %i\n",anim->list,anim->length);
	printf("recieving pointer: %p\n",anim);
	gdImagePtr oldimg = imageImage(img);
	gdImagePtr newimg;
	if (gdImageTrueColor(oldimg))
		newimg = gdImageCreateTrueColor(gdImageSX(oldimg),gdImageSY(oldimg));
	else
		newimg = gdImageCreate(gdImageSX(oldimg),gdImageSY(oldimg));
	gdImageCopy(newimg,oldimg,0,0,0,0,gdImageSX(oldimg),gdImageSY(oldimg));
//	trace("made copy");
	
	ImageList add = newImageListElement(newimg);
	//trace("add to list");
	printf("length of list: %i\n",anim->length);
	if (anim->list==NULL) {
		trace("list was empty");
		anim->list = add;
	}
	else {
		trace("there was already a element in here");
		ImageList cur = anim->list;
		printf("cur: %p\n",anim->list);
		while (cur!=NULL)
			cur = cur->next;
		cur->next = add;	
	}
	trace("added to list");
		
	//anim->length++;
	
	return val_null;
}

//value RenderGifAnimation(value images,value loop,value filename,value globalCM,value delay,value optimise) {
value RenderGifAnimation(value *args,int nargs) {
	trace("start");
	enum {eImages,eLoop,eFilename,eGlobalCM,eDelay,eOptimise,eSize};
	if (nargs!=eSize)
		neko_error();
	
	trace("getting images");
	
	//getting images
	int nframes = val_array_size(args[eImages]);
	value *rawImg = val_array_ptr(args[eImages]);
	ImageData img[nframes];
	int i;
	for (i=0;i<nframes;i++)
		img[i]=getImage(rawImg[i]);
	
	trace("getting config");
	
	//getting config
	int _loop = val_bool(args[eLoop]);
	char *_filename = val_string(args[eFilename]);
	int _globalCM = val_bool(args[eGlobalCM]);
	int _localCM = (_globalCM?0:1);
	int _optimise = val_bool(args[eOptimise]);
	int _delay = val_int(args[eDelay])*10;
	FILE *file = fopen(_filename,"wb");
	
	trace("anim begin");
	printf("length: %i\n",nframes);
	printf("%p\n",imageImage(img[0]));
	gdImageGifAnimBegin(imageImage(img[0]),file,_globalCM,_loop-1);
	trace("start images");
	for (i=0;i<nframes;i++)
		gdImageGifAnimAdd(imageImage(img[0]),file,_localCM ,0,0,_delay,gdDisposalNone,((_optimise && i!=0)?imageImage(img[i-1]):NULL));	
	trace("alle images");
	gdImageGifAnimEnd(file);
	trace("done");
	
	fclose(file);
	
	trace("close");
	return val_null;	
}
