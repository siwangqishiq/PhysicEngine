//
//  SpringTest.c
//  Lelouch
//
//  Created by  潘易  on 16/10/17.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include "Render.h"
#include "Vector2.h"
#include "Particle.h"
#include "ParticleForceList.h"
#include "GameInstance.h"

//GLboolean Large = GL_FALSE; //坐标单位变大或变小

//GameInstance *createGravityGameInstance();

extern GameInstance *createGravityGameInstance();

GameInstance *gameInstance;

float camera_x,camera_y;

//Rect r = {300,200,50,100};

void init();

void drawBgView();

void doMainLoop(float duration);

void onDestory();

long thisTime = 0;

long systemTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec * 1000 + tv.tv_usec/1000;
}



//显示 回调函数
void OnDisplay(void)
{
    long currentTime = systemTime();
    long duration = currentTime - thisTime;
    thisTime = currentTime;
    
    //printf("duration = %ld\n",duration);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST); //启用深度检测
    
    //draw bg
    doMainLoop((float)duration/1000);
    
    glutSwapBuffers();
    glutPostRedisplay();//redraw image on screen
}

void drawBgView()
{
    
    Color bg_color={0,0,0};
    
    int pad = 100;
    for(float x = -WORLD_WIDTH;x <= WORLD_WIDTH;x+=pad){
        drawLine(x, -WORLD_HEIGHT, x, WORLD_HEIGHT, bg_color);
    }//end for x
    
    for(float x = -WORLD_HEIGHT;x <= WORLD_HEIGHT;x+=pad){
        drawLine(-WORLD_WIDTH, x, WORLD_WIDTH, x, bg_color);
    }//end for x
    
    //drawLine(100, 100, WORLD_WIDTH, SCREEN_HEIGHT, bg_color);
}

void handleKeyInput(unsigned char key, int x, int y){
    //printf("key down = %c\n",key);
    switch ((int)key)
    {
        case 27://exit
            onDestory();
            exit(0);
            break;
        default:
            break;
    }
    
    if(gameInstance->onKeyDown){
        gameInstance->onKeyDown(key);
    }
    
    glutPostRedisplay();//redraw image on screen
}

void handleKeyUp(unsigned char key, int x, int y){
    
    //printf("key up = %c\n",key);
    
    if(gameInstance->onKeyUp){
        gameInstance->onKeyUp(key);
    }
}



int main(int argc,char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Lelouch");
    glutInitWindowPosition(100,400);
    
    //glutReshapeFunc(OnReShape);
    glutDisplayFunc(OnDisplay);
    glutKeyboardFunc(handleKeyInput);
    glutKeyboardUpFunc(handleKeyUp);
    
    glClearColor (1.0, 1.0, 1.0, 1.0); //背景白色
    
    camera_x = SCREEN_WIDTH / 2;
    camera_y = SCREEN_HEIGHT / 2;
    setCameraPos(camera_x,camera_y);
    
    thisTime = systemTime();
    
    gameInstance = createGravityGameInstance();
    
    init();
    
    glutMainLoop();
    
    return 0;
}

void init(){
    gameInstance->gameInit();
}



void doMainLoop(float duration){
    gameInstance->gameMainLoop(duration);
    drawBgView();
}

void onDestory(){
    gameInstance->gameFree();
    free(gameInstance);
}
