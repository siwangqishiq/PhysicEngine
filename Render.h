//
//  Render.h
//  Lelouch
//
//  Created by  潘易  on 16/9/25.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

#ifndef __Lelouch__Render__
#define __Lelouch__Render__

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
//#include <GL/glew.h>

#define SCREEN_WIDTH       1000
#define SCREEN_HEIGHT      800

#define WORLD_WIDTH   100000
#define WORLD_HEIGHT  100000

#define PI 3.1415926f

struct _Color{
    int r;
    int g;
    int b;
};
typedef struct _Color Color;

struct _Rect{
    float left;
    float top;
    float width;
    float height;
};

typedef struct _Rect Rect;

void drawPoint(float x, float y, const Color color);//

void drawLine(float x1, float y1, float x2, float y2, const Color color);//

void drawRect(float left,float top,float width,float height,const Color color);//

void drawRect2(Rect *pRect,Color color);

void drawPolygon(float x[],float  y[],int size,const Color color);//

void drawCircle(float x,float y,float radius,const Color color);//

void setCameraPos(float x,float y);//设置摄像机位置

void rotatePolygon(float x[],float y[],int size,const Color color,float dtheta);//

void drawSolidCircle(float x, float y, float radius,const Color color);//绘制实心圆

#endif /* defined(__Lelouch__Render__) */
