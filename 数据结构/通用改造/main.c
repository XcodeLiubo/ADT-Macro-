//
//  main.c
//  通用改造
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include <stdio.h>
#include "testList.h"
#include "testStack.h"
#include "testQ.h"

#include <stdlib.h>

#include <string.h>

#include "testMyAlloc.h"



typedef struct testNn testNN;

void asldfaslkf(testNN* n, int a);

struct testNn{
    int a;
};
void asldfaslkf(testNN* n, int a){
    printf("%s %d",__func__, n->a);
}

void (^sss)(testNN*, int);

#define obj(x) ((void)x,x.call(&x))

int main(int argc, const char * argv[]) {
    // insert code here...



#if 0
    testList01();
    testNN* n = malloc(sizeof(testNN));
    n->next = NULL;
    n->a = 10;

#endif

#if 0
    testNN* n = malloc(sizeof(testNN));
    n->a = 97;
    testNN dsa;
    dsa.a = 98;


    
    char* str0 = malloc(sizeof(typeof(testNN))+1);
    memset(str0, '0', sizeof(typeof(testNN))+1);
    memcpy(str0, n, sizeof(typeof(testNN)));


    char* str1 = malloc(sizeof(typeof(testNN))+1);
    memset(str1, '0', sizeof(typeof(testNN))+1);
    memcpy(str1, &dsa, sizeof(typeof(testNN)));


    printf("%d",strcmp(str0, str1));
#endif
//    testList01();

    testAlloc();
    return 0;
}
