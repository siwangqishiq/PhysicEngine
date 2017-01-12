//
//  CoreTest.c
//  Lelouch
//
//  Created by  潘易  on 16/10/6.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

//#include <stdio.h>
//#include "Particle.h"
//#include "ParticleForceList.h"
//#include "ParticleForceGenerator.h"
//
//int main_1()
//{
//    Particle *p1 = particleCreate();
//    p1->position.x = 100;
//    p1->position.y = 100;
//    
//    Particle *p2 = particleCreate();
//    p2->position.x = 200;
//    p2->position.y = 200;
//    
//    Particle *p3 = particleCreate();
//    p3->position.x = 300;
//    p3->position.y = 300;
//    
//    Particle *p4 = particleCreate();
//    p4->position.x = 400;
//    p4->position.y = 400;
//    
//
//    ParticleForceGen *gravityForceGen = particleForceGenCreateGravity();
//    
//    ParticleForceGen *dragGen = particleDragGenCreate(10, 20);
//    
//    ParticleForceList *list = particleForceListCreate();
//    
//    //
////    particleForceRegisteryAdd(list, p2, gravityForceGen);
////    particleForceRegisteryAdd(list, p1, gravityForceGen);
////    particleForceRegisteryAdd(list, p2, gravityForceGen);
////    particleForceRegisteryAdd(list, p3, gravityForceGen);
//    
//    //
//    particleSetMass(p1, 1);
//    particleSetMass(p4, 1);
//    
//
//    particleForceRegisteryAdd(list, p1, dragGen);
//    particleForceRegisteryAdd(list, p4, dragGen);
//    
//    p1->velocity.x = 10;
//    p1->velocity.y = 20;
//    
//    particleIntegrate(p1, 100);
//    particleIntegrate(p4, 100);
//    
//    vector2Print(&p1->position);
//    vector2Print(&p4->position);
//    
//    particleForceRegsiteryUpdateForce(list,100);
//    
//    particleIntegrate(p1, 100);
//    particleIntegrate(p4, 100);
//    
//    vector2Print(&p1->position);
//    vector2Print(&p4->position);
//    
//    particleForceListFree(list);
//    particleDragGenFree(dragGen);
//    particleForceGenGravityFree(gravityForceGen);
//    particleFree(p1);
//    particleFree(p2);
//    particleFree(p3);
//    particleFree(p4);
//    
//    return 1;
//}
