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

#define listImage(list)	(list->img)
#define animationLength(anim) (anim->length)

AnimationData GetAnimation(value anim) {
	val_check_kind(anim,AnimationPtr);
	return val_data(anim);
}

value FreeAnim(value anim) {
	AnimationData _anim = GetAnimation(anim);
	ImageList cur = _anim->list;
	while (cur!=NULL) {
		ImageList del = cur;
		cur = del->next;
		gdImageDestroy(listImage(del));
	}
	return val_null;
}

void finalizeAnim(value v) {
	FreeAnim(v);
}

value InitAnimation() {
	AnimationData anim = (AnimationData)alloc(sizeof(AnimationData));
	anim->length = 0;
	anim->list = NULL;
	value ret = alloc_abstract(AnimationPtr,anim);
	val_gc(ret,finalizeAnim);
	return ret;
}

ImageList newImageListElement(gdImagePtr img) {
	ImageList ret = (ImageList)alloc(sizeof(ImageList));
	ret->img = img;
	ret->next = NULL;
	return ret;	
}

value AddImage(value animdata,value image) {
	ImageData img = getImage(image);
	AnimationData anim = GetAnimation(animdata);
	gdImagePtr oldimg = imageImage(img);
	gdImagePtr newimg;
	if (gdImageTrueColor(oldimg))
		newimg = gdImageCreateTrueColor(gdImageSX(oldimg),gdImageSY(oldimg));
	else
		newimg = gdImageCreate(gdImageSX(oldimg),gdImageSY(oldimg));  
	gdImageCopy(newimg,oldimg,0,0,0,0,gdImageSX(oldimg),gdImageSY(oldimg)); 
	
	ImageList addImg = newImageListElement(newimg);
	if (anim->list==NULL) {
		anim->list = addImg;
	}
	else {
		ImageList cur = anim->list;
		while (cur->next!=NULL)
			cur = cur->next;
		cur->next = addImg;	
	} 
		
	anim->length++;
	
	return val_null;
}

//value RenderGifAnimation(value images,value loop,value filename,value globalCM,value delay,value optimise) {
value RenderGifAnimation(value *args,int nargs) {
	enum {eImages,eLoop,eFilename,eGlobalCM,eDelay,eOptimise,eSize};
	if (nargs!=eSize)
		neko_error();
	
	AnimationData anim = GetAnimation(args[eImages]);	
	if (animationLength(anim)<1)
		val_throw(alloc_string("no images in animation"));
	
	//getting config
	int _loop = (val_bool(args[eLoop]))-1;
	char *_filename = val_string(args[eFilename]);
	int _globalCM = val_bool(args[eGlobalCM]);
	int _localCM = (_globalCM?0:1);
	int _optimise = val_bool(args[eOptimise]);
	int _delay = val_int(args[eDelay])/10;
	FILE *file = fopen(_filename,"wb");
	
	
	// doing the palette handling....
	if (_localCM) { // just make sure every thing is palette based image
		ImageList cur = anim->list;
		while (cur->next!=NULL) {
			if (gdImageTrueColor(cur->img)) { //somehow it works for me only this way (making a temporary copy)
				gdImagePtr temp = gdImageCreatePaletteFromTrueColor(cur->img,1,256);
				gdImageCopy(cur->img,temp,0,0,0,0,gdImageSX(temp),gdImageSY(temp));
				gdImageDestroy(temp);
			}			
			cur = cur->next;
		}
	}
	else { //make sure all images have the same palette
		// for better quality we make the palette out of all images
		gdImagePtr temp;
		int i;
		ImageList cur;
		int w = gdImageSX(anim->list->img);
		int h = gdImageSY(anim->list->img);			
		
		temp = gdImageCreateTrueColor(w,(animationLength(anim)-1)*h);
		cur = anim->list;
		i = 0;
		while (cur->next != NULL) {
			gdImageCopy(temp,cur->img,0,i*h,0,0,w,h);
			i++;
			cur = cur->next;
		}		
		temp = gdImageCreatePaletteFromTrueColor(temp,1,256);
		
		cur = anim->list;
		i=0;
		int trans;
		while (cur->next != NULL) {
			cur->img = gdImageCreate(w,h);
			gdImageCopy(cur->img,temp,0,0,0,i*h,w,h);
			if (cur!=anim->list) {
				gdImagePaletteCopy(cur->img,anim->list->img);
				gdImageColorTransparent(cur->img,trans);
			}
			else
				trans = gdImageColorAllocate(cur->img,1,1,1);
			i++;
			cur = cur->next;
		}
		
		gdImageDestroy(temp);
	}
	
	gdImageGifAnimBegin(anim->list->img,file,_globalCM,_loop);
	
	ImageList cur = anim->list;
	gdImagePtr last;
	while (cur->next!=NULL) {
		gdImageGifAnimAdd(cur->img,file,_localCM ,0,0,_delay,gdDisposalNone,((_optimise && _globalCM)?last:NULL));	
		last = cur->img;
		cur = cur->next;
	}
	gdImageGifAnimEnd(file);
	
	fclose(file);
	
	return val_null;	
}
