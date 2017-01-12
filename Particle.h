//
//  Particle.h
//  Lelouch
//
//  Created by  潘易  on 16/10/8.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

#ifndef __Lelouch__Particle__
#define __Lelouch__Particle__

#include <stdio.h>
#include <stdlib.h>
#include "Vector2.h"

struct _Particle
{
    Vector2 position;//位置
    Vector2 velocity;//速度
    Vector2 acceleration;//加速度
    Vector2 forceAccum;//粒子所受合力
    real damping;//阻尼系数   0~1  d = 1 无阻尼   d = 0 阻尼最大
    real inverseMass;//质量的倒数
    real mass;//质量
};

typedef struct _Particle Particle;

Particle *particleCreate();

void particleFree(Particle *self);

void particleSetMass(Particle *self,real mass);//设置质量

void particleSetMassInfinte(Particle *self);//设置为无穷大质量

void particleIntegrate(Particle *self,real duration);//积分运算

void particlePrintLog(Particle *self);

void particleClearAccmulator(Particle *self);//清除合力

void particleAddForce(Particle *self, Vector2 *force);//添加作用力

void particleAddForce2(Particle *particle,real force_x,real force_y);//添加作用力

void particleGetVelocity(Particle *self,Vector2 *pVelocity);//获取速度向量

void particleGetPosition(Particle *self,Vector2 *pPosition);//获取位置向量

boolean particleHasFiniteMass(Particle *self);//存在有限质量

#endif /* defined(__Lelouch__Particle__) */
