//
//  testStack.c
//  顺序存储
//
//  Created by 刘泊 on 2019/3/13.
//  Copyright © 2019 LB. All rights reserved.
//

#include "testStack.h"
#include "testList.h"

#include <string.h>
#include <stdlib.h>

#if 1
void assign02(DefineType* newData, DefineType* oldData){
    newData->age = oldData->age;
    newData->name = malloc(sizeof(strlen(oldData->name)+1));
    strcpy(newData->name, oldData->name);
}

void del02(DefineType* data){
    if (data->name) {
        free(data->name);
        data->name = NULL;
    }
}



typedef enum OpCmResult OpCmResult;
enum OpCmResult{
    OpCmResult_equal,
    OpCmResult_greate,
    OpCmResult_less
};


#pragma mark - 优先级
OpCmResult testJudgePriorityOp02(char top, char index){
    if ((top == '+'||top == '-') && (index == '-' || index == '+')) return OpCmResult_equal;

    if ((top == '+'||top == '-') && (index == '*' || index == '/')) return OpCmResult_less;

    if ((top == '*'||top == '/') && (index == '-' || index == '+')) return OpCmResult_greate;

    if ((top == '*'||top == '/') && (index == '*' || index == '/')) return OpCmResult_equal;

    return OpCmResult_less;
}

#define NOT_FOUND 0xffffffffffffffff



#pragma mark - 将前缀表达式转换为后缀表达式
const char* testConvertPrefixEx(const char* source){
    if (!strlen(source))return NULL;
    //2+9/3+6 (2+9)/3+6
    char* result = (char*)malloc(strlen(source)+1);
    if (result)memset(result, '\0', strlen(source)+1);

    testStackChStack* stack = testStackChstack_init();


    int i = 0;
    int record = 0;
    char index = source[i];

    while (index || !testStackChstack_empty(stack)) {
        switch (index) {
            case '0'...'9':{
                result[record++] = index;
                index = source[++i];
            }break;

            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':{

                if (index == '(') {
                    char* indexCh = malloc(sizeof(char)+1);
                    indexCh[1] = '\0';
                    *indexCh = index;
                    testStackChstack_push(indexCh, stack, NULL);
                    index = source[++i];

                }else if(index == ')'){///一直出栈 直到遇到 '('
                    char* topStack = testStackChstack_top(stack);
                    if (*topStack != '(') {
                        result[record++] = *topStack;
                    }else{
                        index = source[++i];
                    }
                    testStackChstack_pop(stack, NULL);///自己释放
                    free(topStack);
                    topStack = NULL;
                }else{
                    char* topStack = testStackChstack_top(stack);
                    ///遍历出来的操作符优先级 < 栈顶的 则栈顶的操作符放到结果里 继续出栈
                    if (topStack && testJudgePriorityOp02(topStack[0], index) != OpCmResult_less) {
                        result[record++] = *topStack;
                        testStackChstack_pop(stack, NULL);
                        free(topStack);
                        topStack = NULL;
                        continue;
                    }
                    ///将遍历出来的运算符压栈
                    char* indexCh = malloc(sizeof(char)+1);
                    indexCh[1] = '\0';
                    *indexCh = index;
                    testStackChstack_push(indexCh, stack, NULL);
                    index = source[++i];
                }
            }break;

            default:{
                char* topStack = testStackChstack_top(stack);
                if (topStack) {
                    result[record++] = *topStack;
                    testStackChstack_pop(stack, NULL);
                    free(topStack);
                    topStack = NULL;
                }
            }break;
        }

    }
    return result;
}



#pragma mark - 计算
int testCalculate02(int a, int b, char op){
    if (op == '+')return a + b;

    if (op == '-')return a - b;

    if (op == '*')return a * b;

    if (op == '/')return a / b;

    return NOT_FOUND >> (4*8);
}

#pragma mark - 栈
void test02(const char* postfixInput){

#define maxSize 100
    char expr[maxSize] = {};

    strcpy(expr, postfixInput);

    ///放数字的
    testStackIntStack* tmpStack = testStackIntstack_init();


    int i = 0;


    while (expr[i]) {
        char index = expr[i];
        switch (index) {
            case '0' ... '9':{
                int* tmp = malloc(sizeof(int));
                *tmp = index - '0';
                testStackIntstack_push(tmp, tmpStack, NULL);
            }break;

            case '+':
            case '-':
            case '*':
            case '/':{
                int* opSec = testStackIntstack_top(tmpStack);
                testStackIntstack_pop(tmpStack, NULL);
                int* opFir = testStackIntstack_top(tmpStack);
                testStackIntstack_pop(tmpStack, NULL);
                int* result =  malloc(sizeof(int));
                *result = testCalculate02(*opFir, *opSec, expr[i]);
                testStackIntstack_push(result, tmpStack, NULL);
                free(opFir);
                free(opSec);
                opFir = opSec = NULL;
            }break;


            case '\t':
            case ' ':
            case '\n':
            default:{

            }break;
        }
        ++i;
    }
    printf("%d\n",*testStackIntstack_top(tmpStack));

}

#endif
