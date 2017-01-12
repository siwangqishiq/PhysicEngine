//
//  GravityGen.c
//  PhyicDemo
//
//  Created by  潘易  on 17/1/11.
//  Copyright (c) 2017年 xinlan. All rights reserved.
//

#include "GravityGen.h"

//创建重力发生器  设置重力场方向
PtlForceGen *createGravityGen(real gravity_x,real gravity_y){
    GravityGenParams *params = (GravityGenParams *)malloc(sizeof(GravityGenParams));
    if(!params)
        return NULL;
    params->g_x = gravity_x;
    params->g_y = gravity_y;
    
    PtlForceGen *gen = (PtlForceGen *)malloc(sizeof(PtlForceGen));
    if(!gen){
        free(params);
        return NULL;
    }
    
    gen->updateForce = gravityUpdate;
    gen->params = params;
    
    return gen;
}

//释放重力发生器资源
void freeGravityGen(PtlForceGen *gravity_force_gen){
    if(gravity_force_gen){
        GravityGenParams *params = gravity_force_gen->params;
        if(params){
            free(params);
        }
        free(gravity_force_gen);
    }
}


//重力更新
void gravityUpdate(Particle *particle,real duration,void *params){
    if(!particle || duration <0 || !params)
        return;
    
    GravityGenParams *gravity_params = (GravityGenParams *)params;
    particleAddForce2(particle, gravity_params->g_x, gravity_params->g_y);
}
