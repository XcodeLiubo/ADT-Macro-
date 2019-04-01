//
//  ListMethodDeclaration.h
//  数据结构
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#ifndef ListMethodDeclaration_h
#define ListMethodDeclaration_h

#define ListMethodDeclaration(_PID_, _type_)\
extern _PID_##ListN* _PID_##list_init(_type_ value,_PID_##AssignDataFun assignFun);\
\
extern void _PID_##list_loop(_PID_##ListN* ptrL,_PID_##LoopFun fun);\
\
extern _type_* _PID_##list_front(_PID_##ListN* ptrL);\
\
extern _type_* _PID_##list_last(_PID_##ListN* ptrL);\
\
extern int _PID_##list_length(_PID_##ListN* ptrL);\
\
extern _type_* _PID_##list_index(_PID_##ListN* ptrL, int index);\
\
extern void _PID_##list_value(_PID_##ListN* ptrL, _type_ target, _PID_##CmFun callback);\
\
extern void _PID_##list_append(_PID_##ListN* ptrL, _type_ target, _PID_##AssignDataFun assignFun);\
\
extern _PID_##ListN* _PID_##list_insert(_PID_##ListN* ptrL, _type_ inseart, int insertIndex,_PID_##AssignDataFun assignFun);\
\
extern _PID_##ListN* _PID_##list_remove(_PID_##ListN* ptrL, int delIndex, _PID_##DelDataFun delFun);\
\
extern _PID_##ListN* _PID_##list_rmlast(_PID_##ListN* ptrL, _PID_##DelDataFun delFun)


#endif /* ListMethodDeclaration_h */



/**

 ps:    list_value这个函数
        因为c语言里没有操作符重载, 导致当链表里的item是 结构体的时候(不是指针)
        进入到这个函数时, 里面的 条件if比较的时候, 为了通用性, 采取里单纯的内存memcpy的方式比较(否则编译不通过), 因为结构体不能 ==
        如果结构体里 有 malloc的成员 最好在调用这个函数的时候, 传第三个 函数指针, 然后自己比较

 */
