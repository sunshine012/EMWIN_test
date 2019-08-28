/*
 * pictures.h
 *
 *  Created on: Jul 2, 2019
 *      Author: che
 */

#ifndef PICTURES_H_
#define PICTURES_H_

#include "DrvTypeDefs.h"
#include "bird.h"
#include "Doraemon.h"
#include "road.h"
#include "tree.h"

#define PICTURE_NUM		4
#define PIC_BIRD		0
#define PIC_DORAEMON	1
#define PIC_ROAD		2
#define PIC_TREE		3

typedef struct
{
	const UINT8  	*pPicData;
	UINT16 	PicDataSize;
}_Picture, *ptrPicture;

extern _Picture LoadedPics[PICTURE_NUM];

#endif /* PICTURES_H_ */
