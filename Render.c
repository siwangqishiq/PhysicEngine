//
//  Render.c
//  Lelouch
//
//  Created by  潘易  on 16/9/25.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

#include "Render.h"

//在(x,y)点处  绘制颜色color
void drawPoint(float x, float y, const Color color)
{
    //glPointSize(8.0);设置点的大小
    glColor3f(color.r / 255, color.g / 255, color.b / 255);//指定点的颜色
    glBegin(GL_POINTS);//开始画点
    glVertex3f(x, y, 0); //绘制点
    glEnd();//结束画点
}

//画直线
void drawLine(float x1, float y1, float x2, float y2, const Color color)
{
    glColor3f(color.r / 255, color.g / 255, color.b / 255);//指定颜色
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0.0f);
    glVertex3f(x2, y2, 0.0f);
    glEnd();
}

//绘制矩形
void drawRect(float x,float y,float width,float height,const Color color)
{
    drawLine(x,y,x+width,y,color);
    drawLine(x+width,y,x+width,y+height,color);
    drawLine(x+width,y+height,x,y+height,color);
    drawLine(x,y+height,x,y,color);
}

//绘制多边形
void drawPolygon(float x[],float  y[],int size,const Color color)
{
    int i;
    for(i = 0;i < size ; i++)
    {
        int j = (i+1) % size ;
        drawLine( x[i], y[i], x[j], y[j],color);
    }//end for i
}


void setCameraPos(float x,float y)//设置摄像机位置
{
    
    glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式
    glLoadIdentity();
    
    //GLfloat aspect =(float)w / (float)h;
    
    glOrtho(x - SCREEN_WIDTH / 2, x + SCREEN_WIDTH/2,
            y - SCREEN_HEIGHT / 2,y + SCREEN_HEIGHT/2, 0, 100);
}

void drawRect2(Rect *pRect,Color color)
{
    drawRect(pRect->left, pRect->top, pRect->width, pRect->height, color);
}

void drawSolidCircle(float x, float y, float radius,const Color color)
{
    int count;
    int sections=200;
    
    glColor3f(color.r / 255, color.g / 255, color.b / 255);//指定点的颜色
    GLfloat TWOPI=2.0f * PI;
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    
    for(count=0; count<=sections; count++)
    {
        glVertex2f(x+radius*cos(count*TWOPI/sections), y+radius*sin(count*TWOPI/sections));
    }
    glEnd();
}
