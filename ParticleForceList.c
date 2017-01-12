//
//  ParticleForceList.c
//  Lelouch
//
//  Created by  潘易  on 16/10/11.
//  Copyright (c) 2016年 xinlan. All rights reserved.
//

//#include "ParticleForceList.h"
//
//ParticleForceList *particleForceListCreate()
//{
//    ParticleForceList *p = (ParticleForceList *)malloc(sizeof(ParticleForceList));
//    if(p == NULL)
//        return NULL;
//    
//    memset(p,0,sizeof(ParticleForceList));
//    p->head = NULL;
//    p->size = 0;
//    
//    return p;
//}
//
//void particleForceListFree(ParticleForceList *p)
//{
//    particleForceRegisteryClear(p);
//    if(p!=NULL)
//        free(p);
//}
//
//int particleForceRegisteryAdd(ParticleForceList *list,
//                              Particle *particle,ParticleForceGen *gen)
//{
//    
//    if(list->size == 0)
//    {
//        list->head = (ParticleForceRegistery *)malloc(sizeof(ParticleForceRegistery));
//        if(list->head == NULL)
//            return ERROR;
//        
//        list->head->forceGen = gen;
//        list->head->particle = particle;
//        list->head->next = NULL;
//        
//        list->size = 1;
//    }else{
//        ParticleForceRegistery *p = list->head;
//        ParticleForceRegistery *prior = NULL;
//        while(p!=NULL)
//        {
//            if(p->particle == particle && p->forceGen == gen)
//                return ERROR;
//            prior = p;
//            p = p->next;
//        }//end while
//        
//        ParticleForceRegistery *insert = (ParticleForceRegistery *)
//        malloc(sizeof(ParticleForceRegistery));
//        if(insert == NULL)
//            return ERROR;
//        insert->particle = particle;
//        insert->forceGen = gen;
//        insert->next = NULL;
//        prior->next = insert;
//        
//        list->size++;
//    }
//    
//    return OK;
//    
//}
//
////移除一项元素
//int particleForceRegisteryRemove(ParticleForceList *list,
//                                 Particle *particle,ParticleForceGen *gen)
//{
//    if(list == NULL || list->size == 0)
//        return ERROR;
//    
//    if(list->size == 1)
//    {
//        ParticleForceRegistery *p = list->head;
//        
//        if(p->particle == particle && p->forceGen == gen)
//        {
//            free(p);
//            list->size--;
//            list->head = NULL;
//            return OK;
//        }
//        
//        return ERROR;
//    }else{
//        ParticleForceRegistery *p = list->head;
//        ParticleForceRegistery *prior = list->head;
//        ParticleForceRegistery *delete = NULL;
//        int index = 0;
//        while(p != NULL)
//        {
//            if(p->particle == particle
//               && p->forceGen == gen)
//            {
//                delete = p;
//                break;
//            }
//            prior = p;
//            p = p->next;
//            index++;
//        }//end while
//        
//        if(delete != NULL)
//        {
//            prior->next = delete->next;
//            free(delete);
//            list->size--;
//            
//            if(index == 0)//删除的是头部节点  需要修改head字段
//            {
//                list->head = prior->next;
//            }
//            return OK;
//        }
//        return ERROR;
//    }
//}
//
//void particleForceRegisteryClear(ParticleForceList *list)
//{
//    if(list->size == 0)
//        return;
//    ParticleForceRegistery *p = list->head;
//    ParticleForceRegistery *pFree = NULL;
//    while(p!=NULL)
//    {
//        pFree = p;
//        free(pFree);
//        p = p->next;
//    }
//    list->head = NULL;
//    list->size = 0;
//}
//
////更新粒子受力
//void particleForceRegsiteryUpdateForce(ParticleForceList *list,real duration)
//{
//    if(list == NULL)
//        return;
//    ParticleForceRegistery *p = list->head;
//    while(p != NULL)
//    {
//        (*(p->forceGen->updateForce))(p->particle,duration,p->forceGen->params);
//        p = p->next;
//    }//end while
//}
//
//
//void particleForceRegisteryLog(ParticleForceList *list)
//{
//    ParticleForceRegistery *p = list->head;
//    printf("list -----start---\n");
//    while(p != NULL)
//    {
//        vector2Print(&p->particle->position);
//        //printf("particle = %ld\n",p->particle);
//        //printf("forceGen = %ld\n",p->forceGen);
//        p = p->next;
//    }//end while
//    printf("list ----end----\n");
//}