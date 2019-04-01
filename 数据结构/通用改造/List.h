typedef int bool;
#define false 0
#define true 1

#define ERROR 0x7fffffff


///函数指针的声明和数据结构的声明

#define ListHeaderMacro(_PID_, _type_)\
\
typedef struct  _PID_##List  _PID_##ListN;\
\
typedef bool (*_PID_##CmFun)           (_type_* target, _type_* find);\
\
typedef void (*_PID_##LoopFun)         (_type_* item, int index, bool* stop);\
\
typedef void (*_PID_##AssignDataFun)   (_type_* item, _type_* arg);\
\
typedef void (*_PID_##DelDataFun)      (_type_* item);\
\
struct _PID_##List{\
    _type_* data;\
    _PID_##ListN* next;\
};\


