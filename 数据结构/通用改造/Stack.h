//
//  Stack.h
//  顺序存储
//
//  Created by 刘泊 on 2019/3/9.
//  Copyright © 2019 LB. All rights reserved.
//


#include "List.h"

#define STHeaderMacro(_PID_, _type_) ListHeaderMacro(_PID_, _type_)\
typedef struct _PID_##Stack _PID_##Stack;\
\
struct _PID_##Stack{\
    _PID_##ListN* stack;\
};\
\
\
extern _PID_##Stack*  _PID_##stack_init(void);\
\
extern bool _PID_##stack_empty(_PID_##Stack* ptrS);\
\
extern int _PID_##stack_size(_PID_##Stack* ptrS);\
\
extern bool _PID_##stack_push(_type_ data, _PID_##Stack* ptrS, _PID_##AssignDataFun assignFun);\
\
extern void _PID_##stack_pop(_PID_##Stack* ptrS, _PID_##DelDataFun delFun);\
\
extern _type_* _PID_##stack_top(_PID_##Stack* ptrS);\
\



