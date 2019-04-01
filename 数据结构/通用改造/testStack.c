//
//  testStack.c
//  通用改造
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include "testStack.h"
#include <stdlib.h>
#include <stdio.h>

/** ************ testStack begin ************ */
#include "Stack.c"
STImMacro(testStack, int);
/** ************ testStack ended ************ */






/** ************ myType begin ************ */
STImMacro(stMyType, MyType2);

/** ************ myType ended ************ */




static void ListAssignDataFun(int* item, int* arg){
    *item = *arg;
}


static void ListLoopFun(int* item, int index, bool* stop){
    printf("%d ", *item);
}

void testStack01(void){
    testStackStack* s = testStackstack_init();

    printf("%d %d",testStackstack_empty(s), testStackstack_size(s));


    testStackstack_push(1, s, ListAssignDataFun);

    printf("%d %d",testStackstack_empty(s), testStackstack_size(s));

    printf("%d ",*testStackstack_top(s));
    testStackstack_pop(s, NULL);

    printf("%d %d",testStackstack_empty(s), testStackstack_size(s));

    stMyTypelist_init((MyType2){2}, ListAssignDataFun);

}
