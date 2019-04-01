//
//  testArray.c
//  顺序存储
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include "testArray.h"
#include <stdlib.h>
#include <string.h>


#include "testList.h"

void prin(Array* const tmp, size_t size){
    for (int i = 0; i < size; ++i){
        printf("%dX^%d ",tmp[i].a,tmp[i].e);
    }
    printf("\n");
}



#pragma mark - 多项式相加
void test0(){
    Array ar0[3] = {
        {9,12},
        {15,8},
        {3,2}
    };

    Array ar1[4] = {
        {26,19},
        {-4,8},
        {-13,6},
        {82,0}
    };


    prin(ar0, 3);
    prin(ar1, 4);


    Array result[7] = {};
    int i = 0, j = 0, count = 0;

    ///前提是各个数组里的指数都是从大到小排的
    while (1) {

        if(i == 3){
            result[count].a = ar1[j].a;
            result[count].e = ar1[j].e;
            j++;
            count++;
            if(j == 4)break;
        }

        if (j == 4) {
            result[count].a = ar1[i].a;
            result[count].e = ar1[i].e;
            i++;
            count++;
            if(i == 3)break;
        }

        if (ar0[i].e == ar1[j].e) {
            result[count].a = ar0[i].a + ar1[j].a;
            result[count].e = ar0[i].e;
            ++i;
            ++j;
            count++;
            continue;
        }

        if (ar0[i].e > ar1[j].e) {
            result[count].e = ar0[i].e;
            result[count].a = ar0[i].a;
            count++;
            ++i;
            continue;
        }

        if(ar0[i].e < ar1[j].e){
            result[count].e = ar1[j].e;
            result[count].a = ar1[j].a;
            count++;
            ++j;
            continue;
        }
    }

    prin(result, count);

}




void loop_list(DefineType* item, int index, bool* stop){
    printf("%s\n",item->name);
}


void assign01(DefineType* newData, DefineType* oldData){
    newData->age = oldData->age;
    newData->name = malloc(sizeof(strlen(oldData->name)+1));
    strcpy(newData->name, oldData->name);
}

void del01(DefineType* delData){
    if (delData->name) {
        free(delData->name);
        delData->name = NULL;
    }
}
void test01(){
    mainTestListListN* list = malloc(sizeof(typeof(mainTestListListN)));
    list->next = NULL;

    typeof(MyType)* a = malloc(sizeof(typeof(MyType)));
    a->age = 10;
    a->name = malloc(sizeof(typeof(char))*20);
    strcpy(a->name, "hello world!");

    list->data = a;
    printf("%p ",list->data->name);
    list = mainTestListlist_insert(list, a,0,assign01);
    printf("%p",list->data->name);

    mainTestListlist_loop(list, loop_list);

    printf("\n\n");
    list = mainTestListlist_remove(list, 1,del01);
    mainTestListlist_loop(list, loop_list);
}
