//
//  ParticleForceGen.c
//  PhyicDemo
//
//  Created by  潘易  on 17/1/9.
//  Copyright (c) 2017年 xinlan. All rights reserved.
//

#include "PtlForceGen.h"

STATUS ptlAddForceGenNode(Linkedlist *list,Particle *particle,PtlForceGen *gen){
    if(!list || !particle || !gen)
        return ERROR;
    PtlFGenNode *node = (PtlFGenNode *)malloc(sizeof(PtlFGenNode));
    
    if(!node)
        return ERROR;
    node->particle = particle;
    node->forceGen = gen;
    
    return linkedlist_add(list, node);
}

STATUS ptlRemoveForceGenNode(Linkedlist *list,Particle *particle,PtlForceGen *gen){
    if(!list)
        return ERROR;
    
    List_Node *p = list->head;
    while(p){
        PtlFGenNode *node = (PtlFGenNode *)p->data;
        if(node->particle == particle
                && node->forceGen == gen){
            //free(node);
            free(node);
            return linkedlist_remove_element(list, p);
        }
        p = p->next;
    }//end while
    
    return ERROR;
}

void ptlClearForceGenList(Linkedlist *list){
    if(!list)
        return;
    
    List_Node *p =list->head;
    while(p){
        PtlFGenNode *node = (PtlFGenNode *)p->data;
        if(node)
            free(node);
        p =p->next;
    }//end while
    linkedlist_free(list);
}


void ptlUpdateForce(Linkedlist *list,real delta_time){
    if(!list)
        return;
    List_Node *p = list->head;
    while(p){
        if(p->data){
            PtlFGenNode *node = (PtlFGenNode *)p->data;
            Particle *particle = node->particle;
            PtlForceGen *gen = node->forceGen;
            (*gen->updateForce)(particle,delta_time,gen->params);
        }//end if
        p = p->next;
    }//end while
}

