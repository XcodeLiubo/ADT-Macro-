//
//  testList.h
//  通用改造
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#ifndef testList_h
#define testList_h

#include <stdio.h>




/********************** listIntT begin ******************/


#include "List.h"
ListHeaderMacro(listIntT, int);

#include "ListMethodDeclaration.h"
ListMethodDeclaration(listIntT, int);


/********************** listIntT ended ******************/







/** ************ myType begin ************ */

typedef struct myType MyType;
struct myType{
    int age;
};
ListHeaderMacro(listMyType, MyType);
ListMethodDeclaration(listMyType, MyType);

/** ************ myType ended ************ */


extern void testList01(void);


#endif /* testList_h */
