//
//  ParticleForceGenerator.h
//  Lelouch
//
//  Created by  潘易  on 16/10/10.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//  粒子作用力发生器

#ifndef __Lelouch__ParticleForceGen__
#define __Lelouch__ParticleForceGen__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Core.h"
#include "Particle.h"

typedef void (*PtrUpdateForce)(Particle *pParticle,real duration,void *params);

struct _ParticleForceGen
{
    void *params;
    PtrUpdateForce updateForce;
};

typedef struct _ParticleForceGen ParticleForceGen;

struct _NormalForceParams
{
    float x;
    float y;
};

typedef struct _NormalForceParams NormalForceParams;

ParticleForceGen *particleForceGenCreateGravity();//创建一个重力发生器

void particleForceGenGravityFree(ParticleForceGen *p);

ParticleForceGen *particleForceGenCreateNormalForce(float force_x,float force_y);//恒定作用力发生器

void particleForceGenNormalForceFree(ParticleForceGen *p);

typedef struct _ParticleDragGenParams
{
    real k1;
    real k2;
} ParticleDragGenParams;

ParticleForceGen *particleDragGenCreate(real k1,real k2);

void particleDragGenFree(ParticleForceGen *p);

//弹力发生器

typedef struct _ParticleSpringParams
{
    Particle *other;//与弹簧相接粒子
    real springConstant;//弹簧弹性系数
    real restLength;//弹簧自然长度
} ParticleSpringParams;

//弹力发生器创建
ParticleForceGen *particleForceGenSpringCreate(Particle *particle,real springConstant,real restLen);

//弹力发生器释放
void particleForceGenSpringFree(ParticleForceGen *forceGen);

//-------------
struct _ParticleForceRegistry
{
    Particle *particle;
    ParticleForceGen *forceGen;
    
    struct _ParticleForceRegistry *next;
};

typedef struct _ParticleForceRegistry ParticleForceRegistery;

//-------固定点弹力发生器---- begin -------------
typedef struct _AnchorSpringParams
{
    Vector2 *anchor;//固定点
    real springConstant;//
    real restLength;
} AnchorSpringParams;


ParticleForceGen *particleForceGenAnchorSpringCreate(real anchor_point_x,real anchor_point_y,
                                                     real springConstant,real restLen);

void particleForceGenAnchorSpringFree(ParticleForceGen *forceGen);


//-------固定点弹力发生器---- end -------------

//-------橡皮筋弹力发生器---- start -------------

typedef struct _BungeeSpringParams
{
    Particle *other;//固定点
    real springConstant;//
    real restLength;
} BungeeSpringParams;


ParticleForceGen *particleForceGenBungeeSpringCreate(Particle *other,
                                                     real springConstant,real restLen);

void particleForceGenBungeeSpringFree(ParticleForceGen *forceGen);

//-------橡皮筋弹力发生器---- end -------------

//-------仿硬质弹簧 发生器---- start -------------

typedef struct _FakeSpringParams
{
    Vector2 *anchor;//固定点
    real springConstant;//
    real damping;//阻尼系数
} FakeSpringParams;

ParticleForceGen *particleForceGenFakeSpringCreate(real anchor_x,real anchor_y,
                                                     real springConstant,real damping);

void particleForceGenFakeSpringFree(ParticleForceGen *forceGen);

//-------橡皮筋弹力发生器---- end -------------

#endif /* defined(__Lelouch__ParticleForceGenerator__) */
