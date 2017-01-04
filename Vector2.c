//
//  Vector2.c
//  Lelouch
//
//  Created by  潘易  on 16/10/8.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

#include "Vector2.h"

//创建一个二维向量
Vector2 *vector2Create(real x,real y)
{
    Vector2 *p = (Vector2 *)malloc(sizeof(Vector2));
    
    if(p == NULL)
        return NULL;
    
    memset(p,0,sizeof(Vector2));
    
    p->x = x;
    p->y = y;
    
    return p;
}

void vector2Free(Vector2 *pVector2)
{
    free(pVector2);
}

void vector2Print(Vector2 *p)
{
    printf("< %.4f, %.4f >\n",p->x,p->y);
}

void vector2Invert(Vector2 *this)
{
    this->x = -this->x;
    this->y = -this->y;
}

//向量长度
real vector2Magnitude(Vector2 *self)
{
    return real_sqrt(self->x * self->x + self->y * self->y);
}

real vector2SquareMagnitude(Vector2 *self)
{
    return self->x * self->x + self->y * self->y;
}

//向量标准化
void vector2Normalize(Vector2 *self)
{
    real magnitude = vector2Magnitude(self);
    if(magnitude<=0.0000000001f)
    {
        self->x *= 1;
        self->y *= 0;
        return;
    }
    real lenInverse = 1 / vector2Magnitude(self);
    self->x *= lenInverse;
    self->y *= lenInverse;
}

//乘以常数
void vector2scalar(Vector2 *self,real value)
{
    self->x *= value;
    self->y *= value;
}

//向量加法
void vector2Add(Vector2 *self,const Vector2 *pAddVect)
{
    self->x += pAddVect->x;
    self->y += pAddVect->y;
}

//向量减法
void vector2Minus(Vector2 *self,const Vector2 *pVect)
{
    self->x -= pVect->x;
    self->y -= pVect->y;
}

void vector2AddScaled(Vector2 *self,const Vector2 *pVect,real scale)
{
    self->x += (pVect->x * scale);
    self->y += (pVect->y * scale);
}

Vector2 *vector2ComponentProduct(Vector2 *self,const Vector2 *pVect)
{
    return vector2Create(self->x * pVect->x, self->y * pVect->y);
}


void vector2ComponentProductUpdate(Vector2 *self,const Vector2 *pVect)
{
    self->x *= pVect->x;
    self->y *= pVect->y;
}

//向量点乘运算
real vector2Dot(Vector2 *self,const Vector2 *pVect)
{
    return self->x * pVect->x + self->y * pVect->y;
}

//叉乘  在z轴方向上的数值
real vector2Cross(Vector2 *self,const Vector2 *pVect)
{
    return self->x * pVect->y - self->y *pVect->x;
}