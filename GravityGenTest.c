//
//  GravityGenTest.c
//  PhyicDemo
//
//  Created by  潘易  on 17/1/12.
//  Copyright (c) 2017年 xinlan. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GameInstance.h"
#include "Render.h"
#include "Particle.h"
#include "GravityGen.h"
#include "linkedlist.h"

Particle *red_ball = NULL;
Particle *green_ball = NULL;
PtlForceGen *gravity_gen = NULL;//重力发生器

Linkedlist *gen_list = NULL;
Linkedlist *particle_list = NULL;

int is_add = 0;

void gravity_game_init(){
    particle_list = linkedlist_create();
    
    //printf("game init \n");
    red_ball = particleCreate();
    red_ball->position.x = 200;
    red_ball->position.y = 500;
    
    linkedlist_add(particle_list, red_ball);
    
    gen_list = linkedlist_create();
    //init gravity
    gravity_gen = createGravityGen(10, -10.0f);
    
    
}

void gravity_game_mainLoop(real delta_time){
    //printf("main loop during = %f\n",delta_time);
    
    ptlUpdateForce(gen_list, delta_time);
    
    particleIntegrate(red_ball, delta_time);
    
    Color red_color = {255,0,0};
    //printf("%f %f\n",red_ball->position.x,red_ball->position.y);
    drawSolidCircle(red_ball->position.x, red_ball->position.y, 10, red_color);
}

void gravity_game_free(){
    //printf("free\n");
    particleFree(red_ball);
    
    linkedlist_free(gen_list);
    linkedlist_free(particle_list);
}

void gravity_game_onkeydown(unsigned char key){
    //printf("on %c key down\n",key);
    if(key == 'a'){
        if(!is_add) {
            ptlAddForceGenNode(gen_list, red_ball, gravity_gen);
            
            //printf("the list size is %d\n",gen_list->size);
            is_add = 1;
        }
    }
}

void gravity_game_onkeyup(unsigned char key){
    //printf("on %c key up \n",key);
    if(key == 's'){
        ptlRemoveForceGenNode(gen_list, red_ball, gravity_gen);
        //printf("remove code = %d\n",code);
        is_add = 0;
    }
}

GameInstance *createGravityGameInstance(){
    GameInstance *instance = (GameInstance *)malloc(sizeof(GameInstance));
    memset(instance, 0, sizeof(GameInstance));
    instance->gameInit = gravity_game_init;
    instance->gameMainLoop = gravity_game_mainLoop;
    instance->gameFree = gravity_game_free;
    
    instance->onKeyDown = gravity_game_onkeydown;
    instance->onKeyUp = gravity_game_onkeyup;
    
    return instance;
}
