//
//  Queue.c
//  顺序存储
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include "Queue.h"

#include <stdlib.h>



#if 0
QueueN* queue_init(void){
    QueueN* result = malloc(sizeof(typeof(QueueN)));
    result->length = 0;
    result->front = result->rear = NULL;
    return result;
}


int queue_empty(QueueN* ptrQ){
    if (ptrQ && !ptrQ->front) return 1;
    return 0;
}

int queue_length(QueueN* ptrQ){
    if (ptrQ == NULL)return -1;
    return ptrQ->length;
}

void* queue_del(QueueN* ptrQ, QueueDelFun fun){
    ///如果队列是空
    if (!ptrQ) return NULL;

    ///如果队列是空
    if (queue_empty(ptrQ))return NULL;


    Node* tmpNode = ptrQ->front;
    void* delData = tmpNode->data;

    ////如果不只1个节点
    if (tmpNode->next) {
        ptrQ->front = ptrQ->front->next;

    }else{////只有一个节点的时候, 出队后就变成空队列了
        ptrQ->front = ptrQ->rear = NULL;
    }

    ptrQ->length--;

    free(tmpNode);


    return delData;
}




QueueN* queue_add(QueueN* ptrQ, void* data, QueueAddFun fun){
    if (!ptrQ)return NULL;

    if (data == NULL) return ptrQ;


    Node* tmpN = malloc(sizeof(typeof(Node)));
    tmpN->next = NULL;


    void* item = NULL;

    if (fun){
        item = malloc(sizeof(void*));
        fun(item, data);

    }else item = data;

    tmpN->data = item;

    if (queue_empty(ptrQ)) {
        ptrQ->front = ptrQ->rear = tmpN;
    }else{
        tmpN->next = ptrQ->front;
        ptrQ->front = tmpN;
    }
    ptrQ->length++;
    return ptrQ;
}

#endif
