//
//  testQueue.c
//  顺序存储
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include "testQueue.h"

#include "Queue.h"

#include <stdlib.h>

void queue_add_fun(void* addData,void* sourceData);


void test03(){
#if 0
    QueueN* q = NULL;
    q = queue_init();

    int* a = malloc(sizeof(int));
    *a = 100;
    queue_add(q, a, NULL);

    printf("%d",*((int*)queue_del(q, NULL)));
#endif
}


void queue_add_fun(void* addData,void* sourceData){

}
