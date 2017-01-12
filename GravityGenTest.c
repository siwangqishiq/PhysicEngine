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

void gravity_game_init(){
    printf("game init \n");
}

void gravity_game_mainLoop(real delta_time){
    //printf("main loop during = %f\n",delta_time);
}

void gravity_game_free(){
    printf("free\n");
}

void gravity_game_onkeydown(unsigned char key){
    printf("on %c key down\n",key);
}

void gravity_game_onkeyup(unsigned char key){
    printf("on %c key up \n",key);
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
