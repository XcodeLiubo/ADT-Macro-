//
//  testMyAlloc.c
//  通用改造
//
//  Created by 刘泊 on 2019/3/15.
//  Copyright © 2019 LB. All rights reserved.
//

#include <stdio.h>

#include "testMyAlloc.h"

#include "MyAlloc.h"


void testAlloc(){
////当申请

    int* a = alloc_find_mem(sizeof(int));
    *a = 100;

    int*b = alloc_find_mem(sizeof(int));
    *b = 234;
    printf("%d %d",*a,*b);


    void* s = alloc_find_mem(15);
    printf("%p",s);

    void* s2 = alloc_find_mem(12);
    printf("%p",s2);

    alloc_recycle_mem(sizeof(int), a);

    a = alloc_find_mem(sizeof(int));

}
