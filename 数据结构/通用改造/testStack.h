//
//  testStack.h
//  通用改造
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#ifndef testStack_h
#define testStack_h



extern void testStack01(void);

/** ************ testStack begin ************ */
#include "Stack.h"
STHeaderMacro(testStack, int);
/** ************ testStack ended ************ */







/** ************ myType begin ************ */

typedef struct myType2 MyType2;
struct myType2{
    int age;
    char* name;
};
STHeaderMacro(stMyType, MyType2);

/** ************ myType ended ************ */




#endif /* testStack_h */
