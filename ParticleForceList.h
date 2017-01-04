//
//  ParticleForceList.h
//  Lelouch
//
//  Created by  潘易  on 16/10/11.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

#ifndef __Lelouch__ParticleForceList__
#define __Lelouch__ParticleForceList__

#include <stdio.h>
#include "ParticleForceGenerator.h"

typedef struct _ParticleForceList
{
    ParticleForceRegistery *head;
    unsigned int size;
} ParticleForceList;

ParticleForceList *particleForceListCreate();

void particleForceListFree(ParticleForceList *p);

int particleForceRegisteryAdd(ParticleForceList *list,
                              Particle *particle,ParticleForceGen *gen);

int particleForceRegisteryRemove(ParticleForceList *list,
                                 Particle *particle,ParticleForceGen *gen);

void particleForceRegisteryClear(ParticleForceList *list);

void particleForceRegsiteryUpdateForce(ParticleForceList *list,real duration);

void particleForceRegisteryLog(ParticleForceList *list);

#endif /* defined(__Lelouch__ParticleForceList__) */
