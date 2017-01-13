//
//  Particle.c
//  Lelouch
//
//  Created by  潘易  on 16/10/8.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//
//粒子
#include "Particle.h"

//创建
Particle *particleCreate()
{
    Particle *p = (Particle *)malloc(sizeof(Particle));
    if(p == NULL)
        return NULL;
    memset(p, 0, sizeof(Particle));
    
    p->damping = 1;
    particleSetMass(p,1);
    
    return p;
}

//回收
void particleFree(Particle *self)
{
    free(self);
}

void particlePrintLog(Particle *self)
{
    printf("pos = <%f,%f>  velocity = <%f,%f>  acclerate = <%f,%f> \n",
           self->position.x,self->position.y,
           self->velocity.x,self->velocity.y,
           self->acceleration.x,self->acceleration.y);
}

void particleSetMass(Particle *self,real mass)
{
    if(mass == 0)
    {
        self->mass = 0;
        return;
    }
    self->inverseMass = 1 / mass;
    self->mass = mass;
}

void particleSetMassInfinte(Particle *self)
{
    self->inverseMass = 0;
}

//运行时做积分运算
void particleIntegrate(Particle *self,real duration)
{
    if(duration < 0)
        return;
    
    //更新位置
    vector2AddScaled(&self->position, &self->velocity, duration);
    
    //计算加速度 a = F/m
    Vector2 resultAcc = self->acceleration;
    //Vector2 forceAccum = {10,0};//粒子所受合力
    
    //vector2Print(&self->forceAccum);
    vector2AddScaled(&resultAcc, &self->forceAccum, self->inverseMass);
    //更新速度
    vector2AddScaled(&self->velocity, &resultAcc, duration);
    //速度受阻尼影响减少
    vector2scalar(&self->velocity, real_pow(self->damping,duration));
    
    particleClearAccmulator(self);//清除合力  下一轮重新计算
}

void particleClearAccmulator(Particle *self)
{
    self->forceAccum.x = 0;
    self->forceAccum.y = 0;
}

void particleAddForce(Particle *self, Vector2 *force){
    vector2Add(&self->forceAccum, force);
}

//添加作用力
void particleAddForce2(Particle *particle,real force_x,real force_y){
    vector2AddByVal(&particle->forceAccum, force_x, force_y);
}

void particleGetVelocity(Particle *self,Vector2 *pVelocity)//获取速度向量
{
    if(pVelocity == NULL)
        return;
    pVelocity->x = self->velocity.x;
    pVelocity->y = self->velocity.y;
}

void particleGetPosition(Particle *self,Vector2 *pPosition)
{
    if(pPosition == NULL)
        return;
    pPosition->x = self->position.x;
    pPosition->y = self->position.y;
}

boolean particleHasFiniteMass(Particle *self)//存在有限质量
{
    return self->mass <= 0.0000000001f ? NO: YES;
}
