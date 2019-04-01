typedef int bool;
#define false 0
#define true 1


#define HeaderMacro(__pre_identify__, __type__)\
typedef struct __pre_identify__##List __pre_identify__##ListN;\
typedef bool (*__pre_identify__##ListCmFun)           (__type__* target, __type__* find);\
typedef void (*__pre_identify__##ListLoopFun)         (__type__* item, int index, bool* stop);\
typedef void (*__pre_identify__##ListAssignDataFun)   (__type__* newData, __type__* oldData);\
typedef void (*__pre_identify__##ListDelDataFun)      (__type__* data);\
struct __pre_identify__##List{\
    __type__* data;\
    __pre_identify__##ListN* next;\
};\
extern void __pre_identify__##list_loop(__pre_identify__##ListN* ptrL,__pre_identify__##ListLoopFun fun);\
extern int __pre_identify__##list_length(__pre_identify__##ListN* ptrL);\
extern __pre_identify__##ListN* __pre_identify__##list_index(__pre_identify__##ListN* ptrL, int index);\
extern void __pre_identify__##list_value(__pre_identify__##ListN* ptrL, __type__* target, __pre_identify__##ListCmFun callback);\
extern __pre_identify__##ListN* __pre_identify__##list_insert(__pre_identify__##ListN* ptrL, __type__* inseart, int insertIndex,__pre_identify__##ListAssignDataFun assignFun);\
extern __pre_identify__##ListN* __pre_identify__##list_remove(__pre_identify__##ListN* ptrL, int delIndex, __pre_identify__##ListDelDataFun delFun);


