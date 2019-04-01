//
//  Stack.c
//  顺序存储
//
//  Created by 刘泊 on 2019/3/9.
//  Copyright © 2019 LB. All rights reserved.
//




#define STImMacro(__pre_identify__ ,__type__) ImCMacro(__pre_identify__ ,__type__)\
__pre_identify__##Stack* __pre_identify__##stack_init(void){\
    __pre_identify__##Stack* s = malloc(sizeof(__pre_identify__##Stack));\
    s->stack = NULL;\
    return s;\
}\
\
bool __pre_identify__##stack_empty(__pre_identify__##Stack* ptrS){\
    if (ptrS == 0) return true;\
\
    if (ptrS->stack == NULL)return true;\
\
    return false;\
}\
\
int __pre_identify__##stack_size(__pre_identify__##Stack* ptrS){\
    if (__pre_identify__##stack_empty(ptrS))return 0;\
    return __pre_identify__##list_length(ptrS->stack);\
}\
\
bool __pre_identify__##stack_push(__type__* data, __pre_identify__##Stack* ptrS, __pre_identify__##ListAssignDataFun assignFun){\
    if (!ptrS) return false;\
\
    if (!data) return false;\
\
\
    if (ptrS->stack == NULL) {\
        ptrS->stack = malloc(sizeof(__pre_identify__##ListN));\
        ptrS->stack->data = malloc(sizeof(__type__));\
        if (assignFun) assignFun(ptrS->stack->data,data);\
        else  ptrS->stack->data = data;\
        ptrS->stack->next = NULL;\
        return true;\
    }\
\
\
\
    __pre_identify__##ListN* old = ptrS->stack;\
    ptrS->stack = __pre_identify__##list_insert(ptrS->stack, data, 0, assignFun);\
    if (old != ptrS->stack)return true;\
    return false;\
}\
\
void __pre_identify__##stack_pop(__pre_identify__##Stack* ptrS, __pre_identify__##ListDelDataFun delFun){\
    if (__pre_identify__##stack_empty(ptrS))return;\
    ptrS->stack = __pre_identify__##list_remove(ptrS->stack, 0, NULL);\
}\
__type__* __pre_identify__##stack_top(__pre_identify__##Stack* ptrS){\
if (__pre_identify__##stack_empty(ptrS))return NULL;\
__type__* result = ptrS->stack->data;\
return result;\
}\





