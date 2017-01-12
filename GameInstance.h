//
//  GameInstance.h
//  PhyicDemo
//
//  Created by  潘易  on 17/1/12.
//  Copyright (c) 2017年 xinlan. All rights reserved.
//

#ifndef __Lelouch__GameInstance__
#define __Lelouch__GameInstance__

#include "Core.h"

typedef void (*FunPtrInit)();

typedef void (*FunPtrMainloop)(real delta_time);

typedef void (*FunPtrFree)();

typedef void (*FunPtrOnKeyDown)(unsigned char key);

typedef void (*FunPtrOnKeyUp)(unsigned char key);

struct _GameInstance{
    FunPtrInit gameInit;
    FunPtrMainloop gameMainLoop;
    FunPtrFree gameFree;
    FunPtrOnKeyDown onKeyDown;
    FunPtrOnKeyUp onKeyUp;
};

typedef struct _GameInstance GameInstance;

#endif 
