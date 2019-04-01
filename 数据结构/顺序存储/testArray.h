//
//  testArray.h
//  顺序存储
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#ifndef testArray_h
#define testArray_h

#include <stdio.h>

struct Array{
    int a; ///系数
    int e;  ///指数
};

typedef struct Array Array;

/** 多项式相加 */
extern void test0(void);

/** 链表 */
extern void test01(void);

#endif /* testArray_h */
