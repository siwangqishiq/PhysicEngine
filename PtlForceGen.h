//
//  ParticleForceGen.h
//  PhyicDemo
//
//  Created by  潘易  on 17/1/9.
//  Copyright (c) 2017年 xinlan. All rights reserved.
//

#ifndef __Lelouch__PtlForceGen__
#define __Lelouch__PtlForceGen__

#include "Core.h"
#include "Particle.h"
#include "linkedlist.h"

typedef void (*FunPtrUpdate)(Particle *particle,real duration,void *params);

struct _PtlForceGen{
    void *params;//参数
    FunPtrUpdate updateForce;//更新函数
};

typedef struct _PtlForceGen PtlForceGen;

struct _PtlFGenNode{
    Particle *particle;
    PtlForceGen *forceGen;
};

typedef struct _PtlFGenNode PtlFGenNode;

STATUS ptlAddForceGenNode(Linkedlist *list,Particle *particle,PtlForceGen *gen);

STATUS ptlRemoveForceGenNode(Linkedlist *list,Particle *particle,PtlForceGen *gen);

void ptlClearForceGenList(Linkedlist *list);

void ptlUpdateForce(Linkedlist *list,real delta_time);

#endif /* defined(__PhyicDemo__ParticleForceGen__) */
