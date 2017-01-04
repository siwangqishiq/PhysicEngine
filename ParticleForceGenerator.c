//
//  ParticleForceGenerator.c
//  Lelouch
//
//  Created by  潘易  on 16/10/10.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

#include "ParticleForceGenerator.h"

//施加重力
void gravityUpdateForce(Particle *particle,real duration,void *params)
{
    Vector2 gravityForce = {0,-9.8f};

    //printf("粒子<%f,%f> 施加重力\n", particle->position.x,particle->position.y);
    particleAddForce(particle, &gravityForce);
}

ParticleForceGen *particleForceGenCreateGravity()//创建一个重力发生器
{
    ParticleForceGen *p = (ParticleForceGen *)malloc(sizeof(ParticleForceGen));
    if(p == NULL)
        return NULL;
    memset(p,0,sizeof(ParticleForceGen));
    p->updateForce = gravityUpdateForce;
    return p;
}

void particleForceGenGravityFree(ParticleForceGen *p)
{
    free(p);
}

void normalUpdateForce(Particle *pParticle,real duration,void *params)
{
    
}

ParticleForceGen *particleForceGenCreateNormalForce(float force_x,float force_y)//恒定作用力发生器
{
    ParticleForceGen *p = (ParticleForceGen *)malloc(sizeof(ParticleForceGen));
    if(p == NULL)
        return NULL;
    memset(p,0,sizeof(ParticleForceGen));
    
    NormalForceParams params = {force_x,force_y};
    p->params = (void *)&params;
    
    p->updateForce = normalUpdateForce;
    
    return p;
}

void particleForceGenNormalForceFree(ParticleForceGen *p)
{
    free(p);
}

//施加阻力
void dragUpdateForce(Particle *particle,real duration,void *params)
{
    ParticleDragGenParams *drag_params = (ParticleDragGenParams *)params;
    
    printf("施加阻力 k1 = %f , k2 = %f\n",drag_params->k1,drag_params->k2);
    Vector2 force={0,0};
    particleGetVelocity(particle, &force);
    
    printf("force11 = %f %f\n",force.x,force.y);
    
    real dragCoeff = vector2Magnitude(&force);//速度大小
    dragCoeff = drag_params->k1 * dragCoeff + drag_params->k2 * dragCoeff * dragCoeff;
    vector2Normalize(&force);
    
    
    vector2scalar(&force, -dragCoeff);
    
    printf("force = %f %f\n",force.x,force.y);
    
    particleAddForce(particle, &force);
}

ParticleForceGen *particleDragGenCreate(real k1,real k2)
{
    ParticleForceGen *p = (ParticleForceGen *)malloc(sizeof(ParticleForceGen));
    if(p == NULL)
        return NULL;
    memset(p,0,sizeof(ParticleForceGen));
    
    ParticleDragGenParams *params = (ParticleDragGenParams *)malloc(sizeof(ParticleDragGenParams));
    if(params == NULL)
        return NULL;
    memset(params,0,sizeof(ParticleDragGenParams));
    
    params->k1 = k1;
    params->k2 = k2;
    
    p->params = params;
    
    p->updateForce = dragUpdateForce;
    
    return p;
}

void particleDragGenFree(ParticleForceGen *p)
{
    if(p==NULL)
        return;
    ParticleDragGenParams *p_params = (ParticleDragGenParams *)p->params;
    if(p_params!=NULL)
        free(p_params);
    free(p);
}

void springUpdateForce(Particle *particle,real duration,void *params);

//弹力发生器创建
ParticleForceGen *particleForceGenSpringCreate(Particle *particle,real springConstant,real restLen)
{
    ParticleForceGen *p = (ParticleForceGen *)malloc(sizeof(ParticleForceGen));
    if(p == NULL)
        return NULL;
    memset(p,0,sizeof(ParticleForceGen));
    
    ParticleSpringParams *p_params = (ParticleSpringParams *)malloc(sizeof(ParticleSpringParams));
    if(p_params == NULL)
        return NULL;
    
    p_params->other = particle;
    p_params->springConstant = springConstant;
    p_params->restLength = restLen;
    
    p->params = p_params;
    
    p->updateForce = springUpdateForce;
    
    return p;
}

//模拟弹簧受力情况
void springUpdateForce(Particle *particle,real duration,void *params)
{
    ParticleSpringParams *p_params = (ParticleSpringParams *)params;
    
    Vector2 force = {0,0};
    particleGetPosition(particle, &force);
    vector2Minus(&force, &p_params->other->position);
    
    real magnitude = vector2Magnitude(&force);
    magnitude = real_abs(magnitude - p_params->restLength);
    vector2scalar(&force, p_params->springConstant);
    
    vector2Normalize(&force);
    vector2scalar(&force, -magnitude);
    
    particleAddForce(particle, &force);
}

//弹力发生器释放
void particleForceGenSpringFree(ParticleForceGen *forceGen)
{
    if(forceGen != NULL)
    {
        ParticleSpringParams *p_params = (ParticleSpringParams *)forceGen->params;
        if(p_params != NULL)
            free(p_params);
        
        free(forceGen);
    }
}



//模拟固定点弹簧受力情况
void springAnchoredUpdateForce(Particle *particle,real duration,void *params)
{
    AnchorSpringParams *p_params = (AnchorSpringParams *)params;
    
    Vector2 force;
    memset(&force,0,sizeof(Vector2));
    particleGetPosition(particle, &force);
    
    vector2Minus(&force, p_params->anchor);
    
    real magnitude = vector2Magnitude(&force);
    magnitude = real_abs(magnitude - p_params->restLength);
    magnitude *= p_params->springConstant;
    
    vector2Normalize(&force);
    vector2scalar(&force, -magnitude);
    
    particleAddForce(particle, &force);
}

ParticleForceGen *particleForceGenAnchorSpringCreate(real anchor_point_x,real anchor_point_y,
                                                     real springConstant,real restLen)
{
    ParticleForceGen *p = (ParticleForceGen *)malloc(sizeof(ParticleForceGen));
    if(p == NULL)
        return NULL;
    memset(p,0,sizeof(ParticleForceGen));
    
    AnchorSpringParams  *p_params = (AnchorSpringParams *)malloc(sizeof(AnchorSpringParams));
    if(p_params == NULL)
        return NULL;
    Vector2 *anchor = (Vector2 *)malloc(sizeof(Vector2));
    if(anchor == NULL)
        return NULL;
    
    anchor->x = anchor_point_x;
    anchor->y = anchor_point_y;
    
    p_params->anchor = anchor;
    p_params->springConstant = springConstant;
    p_params->restLength = restLen;
    
    p->params = p_params;
    
    p->updateForce = springAnchoredUpdateForce;
    
    return p;
}

void particleForceGenAnchorSpringFree(ParticleForceGen *forceGen)
{
    if(forceGen != NULL)
    {
        AnchorSpringParams *params = (AnchorSpringParams *)forceGen->params;
        if(params != NULL)
        {
            if(params->anchor != NULL)
            {
                free(params->anchor);
            }
            free(params);
        }
        
        free(forceGen);
    }
}

//模拟固定点弹簧受力情况
void springBungeeUpdateForce(Particle *particle,real duration,void *params)
{
    BungeeSpringParams *p_params = (BungeeSpringParams *)params;
    Vector2 force;
    particleGetPosition(particle, &force);
    vector2Minus(&force, &p_params->other->position);
    
    real magnitude = vector2Magnitude(&force);
    
    if(magnitude <= p_params->restLength)
        return;
    
    magnitude *= p_params->springConstant * real_abs(p_params->restLength - magnitude);
    
    vector2Normalize(&force);
    vector2scalar(&force, -magnitude);
    
    particleAddForce(particle, &force);
}


ParticleForceGen *particleForceGenBungeeSpringCreate(Particle *other,
                                                     real springConstant,real restLen)
{
    ParticleForceGen *p = (ParticleForceGen *)malloc(sizeof(ParticleForceGen));
    if(p == NULL)
        return NULL;
    memset(p,0,sizeof(ParticleForceGen));
    
    BungeeSpringParams  *p_params = (BungeeSpringParams *)malloc(sizeof(BungeeSpringParams));
    if(p_params == NULL)
        return NULL;
    
    p_params->other = other;
    p_params->springConstant = springConstant;
    p_params->restLength = restLen;
    
    p->params = p_params;
    
    p->updateForce = springBungeeUpdateForce;
    
    return p;
}

void particleForceGenBungeeSpringFree(ParticleForceGen *forceGen)
{
    if(forceGen != NULL)
    {
        BungeeSpringParams *params = (BungeeSpringParams *)forceGen->params;
        if(params != NULL)
        {
            free(params);
        }
        
        free(forceGen);
    }
}

//模拟固定点弹簧受力情况
void springFakeUpdateForce(Particle *particle,real duration,void *params)
{
    if(particleHasFiniteMass(particle) == NO)
        return;
    
    FakeSpringParams *p_params = (FakeSpringParams *)params;
    
    Vector2 position;
    memset(&position,0,sizeof(Vector2));
    particleGetPosition(particle, &position);
    vector2Minus(&position, p_params->anchor);
    
    real gama = 0.5f * real_sqrt(4 * p_params->springConstant
                                 - p_params->damping * p_params->damping);
    if(gama == 0.0f)
        return;
    
    Vector2 c = {particle->position.x,particle->position.y};
    vector2scalar(&c, p_params->damping / (2 * gama));
    Vector2 temp_vel = {0,0};
    particleGetVelocity(particle,&temp_vel);
    vector2scalar(&temp_vel, 1 / gama);
    vector2Add(&c, &temp_vel);
    
    Vector2 target = {0,0};
    particleGetPosition(particle , &target);
    vector2scalar(&target, real_cos(gama * duration));
    vector2AddScaled(&target, &c, real_sin(gama * duration));
    vector2scalar(&target,real_exp(-0.5f * duration * p_params->damping));
    
    Vector2 accel = {target.x,target.y};
    vector2Minus(&accel, &particle->position);
    vector2scalar(&accel, 1/(duration * duration));
    
    Vector2 tmp_vel = {particle->velocity.x,particle->velocity.y};
    vector2scalar(&tmp_vel, duration);
    vector2Minus(&accel, &tmp_vel);
    
    vector2scalar(&accel, particle->mass);
    particleAddForce(particle, &accel);
}

ParticleForceGen *particleForceGenFakeSpringCreate(real anchor_x,real anchor_y,
                                                   real springConstant,real damping)
{
    ParticleForceGen *p = (ParticleForceGen *)malloc(sizeof(ParticleForceGen));
    if(p == NULL)
        return NULL;
    memset(p,0,sizeof(ParticleForceGen));
    
    FakeSpringParams  *p_params = (FakeSpringParams *)malloc(sizeof(FakeSpringParams));
    if(p_params == NULL)
        return NULL;
    Vector2 *anchor = (Vector2 *)malloc(sizeof(Vector2));
    if(anchor == NULL)
        return NULL;
    
    anchor->x = anchor_x;
    anchor->y = anchor_y;
    
    p_params->anchor = anchor;
    p_params->springConstant = springConstant;
    p_params->damping = damping;
    
    p->params = p_params;
    
    p->updateForce = springFakeUpdateForce;
    
    return p;
}

void particleForceGenFakeSpringFree(ParticleForceGen *forceGen)
{
    if(forceGen != NULL)
    {
        FakeSpringParams *params = (FakeSpringParams *)forceGen->params;
        if(params != NULL)
        {
            if(params->anchor != NULL)
            {
                free(params->anchor);
            }
            free(params);
        }
        
        free(forceGen);
    }
}












