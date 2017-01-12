//
//  GravityGen.h
//  PhyicDemo
//
//  Created by  潘易  on 17/1/11.
//  Copyright (c) 2017年 xinlan. All rights reserved.
//

#ifndef __Lelouch__GravityGen__
#define __Lelouch__GravityGen__

#include "PtlForceGen.h"

struct _GravityGenParams{//重力发生器参数
    real g_x;
    real g_y;
};

typedef struct _GravityGenParams GravityGenParams;

void gravityUpdate(Particle *particle,real duration,void *params);//重力更新

PtlForceGen *createGravityGen(real gravity_x,real gravity_y);//创建一个重力发生器

void freeGravityGen(PtlForceGen *gravity_force_gen);//free

#endif /* defined(__PhyicDemo__GravityGen__) */
