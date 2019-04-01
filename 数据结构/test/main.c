//
//  main.c
//  test
//
//  Created by 刘泊 on 2018/10/25.
//  Copyright © 2018 LB. All rights reserved.
//

#include <stdio.h>
int test01(int * restrict a, int* restrict b){
    *a = 1;
    *b = 10;
    return *a;
}


int main(int argc, const char * argv[]) {
    int num = 324;
    int* restrict a = &num;
    int* restrict b = &num;
    printf("%d ",test01(a, b));
    return 0;
}
