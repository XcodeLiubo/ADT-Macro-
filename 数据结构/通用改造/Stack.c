//
//  Stack.c
//  顺序存储
//
//  Created by 刘泊 on 2019/3/9.
//  Copyright © 2019 LB. All rights reserved.
//

#include "MyAlloc.h"
#include "List.c"

#define STImMacro(_PID_ ,_type_) ListImMacro(_PID_ ,_type_)\
_PID_##Stack* _PID_##stack_init(void){\
    _PID_##Stack* s = alloc_find_mem(sizeof(_PID_##Stack));\
    s->stack = NULL;\
    return s;\
}\
\
bool _PID_##stack_empty(_PID_##Stack* ptrS){\
    if (ptrS == 0) return true;\
\
    if (ptrS->stack == NULL)return true;\
\
    return false;\
}\
\
int _PID_##stack_size(_PID_##Stack* ptrS){\
    if (_PID_##stack_empty(ptrS))return 0;\
    return _PID_##list_length(ptrS->stack);\
}\
\
bool _PID_##stack_push(_type_ data, _PID_##Stack* ptrS, _PID_##AssignDataFun assignFun){\
    if (!ptrS) return false;\
\
    if (ptrS->stack == NULL) {\
        ptrS->stack = alloc_find_mem(sizeof(_PID_##ListN));\
        ptrS->stack->data = alloc_find_mem(sizeof(_type_));\
        if (assignFun) assignFun(ptrS->stack->data,&data);\
        else  *ptrS->stack->data = data;\
        ptrS->stack->next = NULL;\
        return true;\
    }\
\
\
\
    _PID_##ListN* old = ptrS->stack;\
    ptrS->stack = _PID_##list_insert(ptrS->stack, data, 0, assignFun);\
    if (old != ptrS->stack)return true;\
    return false;\
}\
\
void _PID_##stack_pop(_PID_##Stack* ptrS, _PID_##DelDataFun delFun){\
    if (_PID_##stack_empty(ptrS))return;\
    ptrS->stack = _PID_##list_remove(ptrS->stack, 0, NULL);\
}\
_type_* _PID_##stack_top(_PID_##Stack* ptrS){\
    if (_PID_##stack_empty(ptrS))return NULL;\
    _type_* result = ptrS->stack->data;\
    return result;\
}\





