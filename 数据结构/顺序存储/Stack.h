//
//  Stack.h
//  顺序存储
//
//  Created by 刘泊 on 2019/3/9.
//  Copyright © 2019 LB. All rights reserved.
//




#define STHeaderMacro(__pre_identify__, __type__) HeaderMacro(__pre_identify__, __type__)\
typedef struct __pre_identify__##Stack __pre_identify__##Stack;\
\
struct __pre_identify__##Stack{\
    __pre_identify__##ListN* stack;\
};\
\
\
extern __pre_identify__##Stack*  __pre_identify__##stack_init(void);\
\
extern bool __pre_identify__##stack_empty(__pre_identify__##Stack* ptrS);\
\
extern int __pre_identify__##stack_size(__pre_identify__##Stack* ptrS);\
\
extern bool __pre_identify__##stack_push(__type__* data, __pre_identify__##Stack* ptrS, __pre_identify__##ListAssignDataFun assignFun);\
\
extern void __pre_identify__##stack_pop(__pre_identify__##Stack* ptrS, __pre_identify__##ListDelDataFun delFun);\
\
extern __type__* __pre_identify__##stack_top(__pre_identify__##Stack* ptrS);\
\



