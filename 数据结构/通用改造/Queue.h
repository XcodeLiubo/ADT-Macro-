//
//  Queue.h
//  顺序存储
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include "List.h"
#define QHeaderMacro(_PID_, _type_) ListHeaderMacro(_PID_, _type_)\
\
typedef struct _PID_##QueueN _PID_##QueueN;\
struct _PID_##QueueN{\
    _PID_##ListN* front;\
    _PID_##ListN* rear;\
    int length;\
};\
\
extern _PID_##QueueN* _PID_##queue_init(void);\
\
extern bool _PID_##queue_empty(_PID_##QueueN* ptrQ);\
\
extern int _PID_##queue_length(_PID_##QueueN* ptrQ);\
\
extern _type_* _PID_##queue_del(_PID_##QueueN* ptrQ, _PID_##DelDataFun fun);\
\
extern void _PID_##queue_add(_PID_##QueueN* ptrQ, _type_ data, _PID_##AssignDataFun fun);




#ifndef Queue_h
#define Queue_h

#if 0

#include <stdio.h>
/** 节点的类型 */
typedef struct Node Node;
struct Node{
    void* data;
    Node* next;
};

/** 队列 */
typedef struct QueueN QueueN;
struct QueueN{
    Node* front;    ///队头
    Node* rear;     ///队尾
    int length;     ///长度
};
////用链表实现队列的时候, 队头在链表的头部, 队尾在链表的最后


typedef void(*QueueDelFun) (void* delData);
typedef void(*QueueAddFun) (void* addData,void* sourceData);



extern QueueN* queue_init(void);

extern int queue_empty(QueueN* ptrQ);

extern int queue_length(QueueN* ptrQ);

extern void* queue_del(QueueN* ptrQ, QueueDelFun fun);

extern QueueN* queue_add(QueueN* ptrQ, void* data, QueueAddFun fun);


#endif




#endif /* Queue_h */
