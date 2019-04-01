//
//  testQ.c
//  通用改造
//
//  Created by 刘泊 on 2019/3/14.
//  Copyright © 2019 LB. All rights reserved.
//

#include "testQ.h"


#include <stdlib.h>
#include <stdio.h>

#include "Queue.c"
QImMacro(testQ,int)

void testQ01(){
    testQQueueN* q = testQqueue_init ();
    testQqueue_add(q, 3, NULL);




    printf("%d",testQqueue_length(q));
    printf("%d",*testQqueue_del(q, NULL));


}
