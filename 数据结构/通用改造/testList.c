//
//  testList.c
//  通用改造
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include "testList.h"

#include <stdlib.h>


/********************** listIntT begin ******************/
#include "List.c"
ListImMacro(listIntT, int);
/********************** listIntT ended ******************/




/** ************ myType begin ************ */
ListImMacro(listMyType, MyType);

/** ************ myType ended ************ */





static void ListAssignDataFun(int* item, int* arg){
    *item = *arg;
    
}

static void ListLoopFun(int* item, int index, bool* stop){
    printf("%d ", *item);
}

void testList01(void){

    listIntTListN* node = listIntTlist_init(3, ListAssignDataFun);
    listIntTlist_append(node, 10, ListAssignDataFun);
    node = listIntTlist_insert(node, 20, 1, NULL);

    printf("\n");
    listIntTlist_loop(node, ListLoopFun);

    listIntTlist_append(node, 123, NULL);

    printf("\n");
    listIntTlist_loop(node, ListLoopFun);

    node = listIntTlist_remove(node, 1, NULL);

    printf("\n");
    listIntTlist_loop(node, ListLoopFun);

    node = listIntTlist_rmlast(node, NULL);

    printf("\n");
    listIntTlist_loop(node, ListLoopFun);



    listMyTypeListN* list = listMyTypelist_init((MyType){12313}, NULL);

    printf("%d\n",listMyTypelist_last(list)->age);

}

