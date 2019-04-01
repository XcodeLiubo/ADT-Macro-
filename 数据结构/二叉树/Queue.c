//
//  Queue.c
//  顺序存储
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//




#include "MyAlloc.h"
#include "List.c"

#define QImMacro(_PID_ ,_type_)ListImMacro(_PID_ ,_type_)\
\
_PID_##QueueN* _PID_##queue_init(){\
    _PID_##QueueN* result = alloc_find_mem(sizeof(typeof(_PID_##QueueN)));\
    result->length = 0;\
    result->front = result->rear = NULL;\
    return result;\
}\
\
\
bool _PID_##queue_empty(_PID_##QueueN* ptrQ){\
    if (ptrQ && !ptrQ->front) return true;\
    return false;\
}\
\
\
int _PID_##queue_length(_PID_##QueueN* ptrQ){\
    if (ptrQ == NULL)return -1;\
    return ptrQ->length;\
}\
\
\
_type_* _PID_##queue_del(_PID_##QueueN* ptrQ, _PID_##DelDataFun fun){\
    if (!ptrQ) return NULL;\
\
    if (_PID_##queue_empty(ptrQ))return NULL;\
\
\
    _PID_##ListN* tmpNode = ptrQ->front;\
    _type_* delData = tmpNode->data;\
\
    if (tmpNode->next) ptrQ->front = ptrQ->front->next;\
    else ptrQ->front = ptrQ->rear = NULL;\
\
    ptrQ->length--;\
\
    alloc_recycle_mem(sizeof(typeof(_PID_##ListN)),tmpNode);\
\
    return delData;\
}\
\
\
void _PID_##queue_add(_PID_##QueueN* ptrQ, _type_ data, _PID_##AssignDataFun fun){\
\
    if (!ptrQ)return;\
\
    _PID_##ListN* tmpN = alloc_find_mem(sizeof(typeof(_PID_##ListN)));\
    tmpN->next = NULL;\
    _type_* item = NULL;\
\
    item = alloc_find_mem(sizeof(_type_));\
    if (fun){\
        fun(item, &data);\
    }else *item = data;\
\
    tmpN->data = item;\
\
    if (_PID_##queue_empty(ptrQ)) {\
        ptrQ->front = ptrQ->rear = tmpN;\
    }else{\
        ptrQ->rear->next = tmpN;\
        ptrQ->rear = tmpN;\
    }\
    ptrQ->length++;\
}\
