
#include "MyAlloc.h"

#include <string.h>


#define ListImMacro(_PID_ ,_type_)\
_PID_##ListN* _PID_##list_idx(_PID_##ListN* ptrL, int index);\
\
\
_PID_##ListN* _PID_##list_last_node(_PID_##ListN* ptrL){\
    if (ptrL == 0) return NULL;\
    while(ptrL->next) ptrL = ptrL->next;\
    return ptrL;\
}\
\
\
\
\
_PID_##ListN* _PID_##list_init(_type_ value,_PID_##AssignDataFun assignFun){\
    _PID_##ListN* result = alloc_find_mem(sizeof(typeof(_PID_##ListN)));\
    result->next = NULL;\
    result->data = alloc_find_mem(sizeof(typeof(_type_)));\
    if(assignFun)assignFun(result->data,&value);\
    else *result->data = value;\
    return result;\
}\
\
void _PID_##list_loop(_PID_##ListN* ptrL,_PID_##LoopFun fun){\
    if (ptrL == 0) return;\
    if (fun == 0) return;\
\
    bool stop = false;\
    int tmpIndex = 0;\
    while (ptrL) {\
        fun(ptrL->data, tmpIndex++, &stop);\
        if (stop)break;\
        ptrL = ptrL->next;\
    }\
}\
_type_* _PID_##list_front(_PID_##ListN* ptrL){\
    if (ptrL == 0) return NULL;\
    return ptrL->data;\
}\
_type_* _PID_##list_last(_PID_##ListN* ptrL){\
    if (ptrL == 0) return NULL;\
    return _PID_##list_last_node(ptrL)->data;\
}\
\
int _PID_##list_length(_PID_##ListN* ptrL){\
    if (!ptrL)return 0;\
\
    int count = 1;\
    while ((ptrL = ptrL->next))count++;\
    return count;\
}\
\
_type_* _PID_##list_index(_PID_##ListN* ptrL, int index){\
    if(_PID_##list_idx(ptrL,index))return _PID_##list_idx(ptrL,index)->data;\
    return NULL;\
}\
\
\
void _PID_##list_value(_PID_##ListN* ptrL, _type_ target, _PID_##CmFun callback){\
    if (ptrL == 0)return;\
\
    while (ptrL){\
        if (callback && callback(&target,ptrL->data))break;\
        else {\
            int tmpSize = sizeof(typeof(_type_));\
            char* targetStr = alloc_find_mem(tmpSize+1);\
            memset(targetStr,'\0',tmpSize+1);\
            memcpy(targetStr,&target,tmpSize);\
\
            char* itemStr = alloc_find_mem(tmpSize+1);\
            memset(itemStr,'\0',tmpSize+1);\
            memcpy(itemStr,ptrL->data,tmpSize);\
\
            if (strcmp(targetStr,itemStr)){\
                alloc_recycle_mem(tmpSize+1,targetStr);\
                alloc_recycle_mem(tmpSize+1,itemStr);\
                itemStr = targetStr = NULL;\
                break;\
            }else{\
                alloc_recycle_mem(tmpSize+1,targetStr);\
                alloc_recycle_mem(tmpSize+1,itemStr);\
                itemStr = targetStr = NULL;\
            }\
        }\
        ptrL = ptrL->next;\
    }\
}\
\
void _PID_##list_append(_PID_##ListN* ptrL, _type_ target, _PID_##AssignDataFun assignFun){\
    if (ptrL == NULL)return;\
    _PID_##ListN* newN = alloc_find_mem(sizeof(typeof(_PID_##ListN)));\
    newN->next = NULL;\
    newN->data = alloc_find_mem(sizeof(typeof(_type_)));\
    if(assignFun) assignFun(newN->data,&target);\
    else *newN->data = target;\
    _PID_##list_last_node(ptrL)->next = newN;\
}\
\
_PID_##ListN* _PID_##list_insert(_PID_##ListN* ptrL, _type_ inseart, int insertIndex,_PID_##AssignDataFun assignFun){\
    if (ptrL == NULL)return NULL;\
\
\
    if (insertIndex == 0) {\
        _PID_##ListN* newN = NULL;\
        newN = alloc_find_mem(sizeof(typeof(_PID_##ListN)));\
        newN->data = alloc_find_mem(sizeof(typeof(_type_)));\
        if (newN) {\
            if (assignFun) {\
                assignFun(newN->data,&inseart);\
            }else *newN->data = inseart;\
            newN->next = ptrL;\
            ptrL = newN;\
        }\
        return ptrL;\
    }\
\
    _PID_##ListN* preN = _PID_##list_idx(ptrL, insertIndex - 1);\
    if (!preN) return ptrL;\
\
\
\
    _PID_##ListN* newN = alloc_find_mem(sizeof(typeof(_PID_##ListN)));\
    newN->data = alloc_find_mem(sizeof(typeof(_type_)));\
    if (newN) {\
        if (assignFun){\
            assignFun(newN->data,&inseart);\
        }else *newN->data = inseart;\
\
        newN->next =  preN->next;\
        preN->next = newN;\
    }\
\
    return ptrL;\
}\
\
\
_PID_##ListN* _PID_##list_remove(_PID_##ListN* ptrL, int delIndex, _PID_##DelDataFun delFun){\
    if (ptrL == 0) return ptrL;\
\
    if (delIndex == 0) {\
        _PID_##ListN* tmpPtrL = ptrL;\
        if (delFun)delFun(ptrL->data);\
        alloc_recycle_mem(sizeof(typeof(ptrL->data)),ptrL->data);\
        ptrL = ptrL->next;\
        alloc_recycle_mem(sizeof(typeof(_PID_##ListN)),tmpPtrL);\
    }else{\
        _PID_##ListN* tmpPreN = _PID_##list_idx(ptrL, delIndex - 1);\
        if (tmpPreN && tmpPreN->next) {\
            _PID_##ListN* tmp = tmpPreN->next;\
            tmpPreN->next = tmpPreN->next->next;\
            if (delFun)delFun(tmp->data);\
            alloc_recycle_mem(sizeof(typeof(tmp->data)),tmp->data);\
            alloc_recycle_mem(sizeof(typeof(_PID_##ListN)),tmp);\
        }\
    }\
    return ptrL;\
}\
\
_PID_##ListN* _PID_##list_rmlast(_PID_##ListN* ptrL, _PID_##DelDataFun delFun){\
    int tmpCount = _PID_##list_length(ptrL);\
    if(tmpCount) return _PID_##list_remove(ptrL,tmpCount-1,delFun);\
    else  return NULL;\
}\
\
\
_PID_##ListN* _PID_##list_idx(_PID_##ListN* ptrL, int index){\
    \
    if (ptrL == 0)return 0;\
    \
    if (index < 0)return 0;\
    \
    int tmp_index = 0;\
    \
    while (ptrL){\
        if (tmp_index++ == index)return ptrL;\
        ptrL = ptrL->next;\
    }\
    return 0;\
}\
\
