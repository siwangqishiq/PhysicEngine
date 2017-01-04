//
//  Vector2.h
//  Lelouch
//
//  Created by  潘易  on 16/10/8.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

#ifndef __Lelouch__Vector2__
#define __Lelouch__Vector2__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Core.h"

struct _Vector2
{
    real x;
    real y;
};

typedef struct _Vector2 Vector2;

Vector2 *vector2Create(real x,real y);

void vector2Free(Vector2 *pVector2);

void vector2Print(Vector2 *p);

void vector2Invert(Vector2 *self);//取反

real vector2Magnitude(Vector2 *self);//向量长度

real vector2SquareMagnitude(Vector2 *self); //向量长度平方值

void vector2Normalize(Vector2 *self);//向量标准化

void vector2scalar(Vector2 *self,real value);//乘以常数

void vector2Add(Vector2 *self,const Vector2 *pAddVect);//向量相加

void vector2Minus(Vector2 *self,const Vector2 *pVect);//向量相减

void vector2AddScaled(Vector2 *self,const Vector2 *pVect,real scale);//v' = v + v2*scale

Vector2 *vector2ComponentProduct(Vector2 *self,const Vector2 *pVect);//分量 x1*x2 + y1*y2

void vector2ComponentProductUpdate(Vector2 *self,const Vector2 *pVect);//自身做分量乘法

real vector2Dot(Vector2 *self,const Vector2 *pVect);//点乘

real vector2Cross(Vector2 *self,const Vector2 *pVect);//叉乘运算

#endif /* defined(__Lelouch__Vector2__) */
