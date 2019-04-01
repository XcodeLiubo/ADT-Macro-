//
//  BinaryTree.c
//  二叉树
//
//  Created by 刘泊 on 2019/3/8.
//  Copyright © 2019 LB. All rights reserved.
//
#include <stdlib.h>
#include "BinaryTree.h"

#include <stdio.h>



#pragma mark - 声明对应类型的栈(先序中序用到)
#include "Stack.h"
#include "Stack.c"
STHeaderMacro(My, BinaryTree*);     ///头文件声明
STImMacro(My, BinaryTree*);         ///对应栈的实现



#pragma mark - 声明对应类型的栈(后序用到)
typedef struct TraverseLastNode TraverseLastNode;
struct TraverseLastNode{
    BinaryTree* node;
    bool flag;  ////遍历的时候, 标记位
};
STHeaderMacro(T_Last, TraverseLastNode*);     ///头文件声明
STImMacro(T_Last, TraverseLastNode*);         ///对应栈的实现


#pragma mark - 队列相关的数据结构
#include "Queue.h"
QHeaderMacro(BinaryTree,BinaryTree*);
#include "Queue.c"
QImMacro(BinaryTree,BinaryTree*)





#define TraverseCriticalCount 100
#define _MAX(a,b) ((a)>(b)?(a):(b))





#pragma mark - 辅助函数声明
/////判断树是不是空
static inline bool tree_empty(BinaryTreeRoot*);

////是否要递归遍历
static inline bool traverse_recursion_condition(BinaryTreeRoot*);

////二叉树高度(递归方式)
unsigned long binary_tree_height_recursion(BinaryTree*);

///内部定义的二叉树遍历的回调
static void* traverse_call_back(TraverseStd* att);



#pragma mark - 私有函数声明
////递归遍历
static void traverse_recursion(BinaryTree*, TraverseBTType, TraverseCallFun, TraverseStd*);

///堆栈先序遍历
static void traverse_first(BinaryTree*,TraverseCallFun,TraverseStd*);

///堆栈中序遍历
static void traverse_middle(BinaryTree*,TraverseCallFun,TraverseStd*);

///堆栈后序遍历
static void traverse_last(BinaryTree*,TraverseCallFun,TraverseStd*);

///堆栈层次遍历
static void traverse_level(BinaryTree*,TraverseCallFun,TraverseStd*);

///创建TraverseStd
static inline TraverseStd* traversestd_create(TraverseBTType,TraverseCallFun);

////遍历二叉树的时候,通用的操作
static bool traverse_ing_work(TraverseStd* traverseData,BinaryTree* tree,TraverseCallFun callbackFun);



#pragma mark - 创建树的根节点
BinaryTreeRoot* create_tree_root(){
    BinaryTreeRoot* root = (BinaryTreeRoot*)alloc_find_mem(sizeof(BinaryTreeRoot));
    root->count = 0;
    root->root = NULL;
    return root;
}


#pragma mark - 创建树
BinaryTreeRoot* create_tree(BinaryTreeRoot* root,TreeType type){
    if (tree_empty(root))return NULL;
    switch (type) {
        case TreeType_whole:{

        }break;


        case TreeType_perfect:{

        }break;

        default:return root;
    }
    return NULL;
}


#pragma mark - 创建节点
BinaryTree* create_tree_node(BT_VType value,TreeNewNodeAssignFun callbackFun){
    BinaryTree* node = alloc_find_mem(sizeof(BinaryTree));
    node->left = node->right = 0;
    if (callbackFun)callbackFun(&value,&node->value);
    else node->value = value;
    return node;
}


#pragma mark - 遍历二叉树
void traverse_binaryT(BinaryTreeRoot* root,TraverseBTType type,TraverseCallFun callbackFun){
    if (tree_empty(root)) return;
    TraverseStd* tmpTraverseData = NULL;
    if (callbackFun)
        tmpTraverseData = traversestd_create(type, callbackFun);

    ///堆栈遍历或层次遍历
    if (traverse_recursion_condition(root)) {
        switch (type) {
            case TraverseBTType_first:  {   traverse_first(root->root, callbackFun,tmpTraverseData);}break;
            case TraverseBTType_middle: {   traverse_middle(root->root, callbackFun,tmpTraverseData);}break;
            case TraverseBTType_last:   {   traverse_last(root->root, callbackFun,tmpTraverseData);}break;
            case TraverseBTType_level:  {   traverse_level(root->root, callbackFun,tmpTraverseData);}break;
        }
    }else{
        ///递归遍历
        traverse_recursion(root->root, type, callbackFun,tmpTraverseData);
    }
    alloc_recycle_mem(sizeof(TraverseStd), tmpTraverseData);
}

#pragma mark - 递归遍历
void traverse_recursion(BinaryTree* tree,
                        TraverseBTType type,
                        TraverseCallFun callbackFun,
                        TraverseStd* traverseData){
    if (tree) {
        switch (type) {
            case TraverseBTType_middle:{
                traverse_recursion(tree->left, type, callbackFun,traverseData);
                if (callbackFun && traverse_ing_work(traverseData, tree, callbackFun))return;
                traverse_recursion(tree->right, type, callbackFun,traverseData);
            }break;

            case TraverseBTType_last:{
                traverse_recursion(tree->left, type, callbackFun,traverseData);
                traverse_recursion(tree->right, type, callbackFun,traverseData);
                if (callbackFun && traverse_ing_work(traverseData, tree, callbackFun))return;
            }break;


            case TraverseBTType_level:{
                traverse_level(tree, callbackFun,traverseData);
            }break;

            default:{
                if (callbackFun && traverse_ing_work(traverseData, tree, callbackFun))return;
                traverse_recursion(tree->left, type, callbackFun,traverseData);
                traverse_recursion(tree->right, type, callbackFun,traverseData);
            }break;
        }
    }
}


#pragma mark - 堆栈先序遍历
void traverse_first(BinaryTree* tree,TraverseCallFun callbackFun,TraverseStd* traverseData){
    MyStack* stack = Mystack_init();

    BinaryTree** tmpBt = NULL;

    while (tree || !Mystack_empty(stack)) {

        ///相当于第一次碰到 节点, 立即访问
        if (tree && callbackFun && callbackFun && traverse_ing_work(traverseData, tree, callbackFun))break;

#if 0  ////针对于先序遍历的时候, 优化一下, 如果有右子树,再压栈(减少栈的空间)


        ///压栈
        if (tree && tree->right){
            Mystack_push(tree, stack, NULL);
        }


        ///先访问左子树
        if (tree) {
            tree = tree->left;
            continue;
        }

        ////在先序遍历里 栈的作用就是 为了一个一个取出右子树,一定要判断栈是否空, 因为 入栈的判断是有条件的
        if (!Mystack_empty(stack)) {
            tmpBt = Mystack_top(stack);
            tree = (*tmpBt)->right;
            Mystack_pop(stack, NULL);
        }

#elif 1

        if (tree) Mystack_push(tree, stack, NULL);

        if (tree) {
            tree = tree->left;
            continue;
        }

        ///栈一定不空, 因为能来到这里, 表示先序左子树已经遍历完毕, 后面全是出栈的操作, 然后再重复循环
        tmpBt = Mystack_top(stack);
        tree = (*tmpBt)->right;
        Mystack_pop(stack, NULL);

#endif
    }


    alloc_recycle_mem(sizeof(MyStack), stack);
}

#pragma mark - 堆栈中序遍历
void traverse_middle(BinaryTree* tree,TraverseCallFun callbackFun,TraverseStd* traverseData){
    MyStack* stack = Mystack_init();

    BinaryTree** tmpBt = NULL;

    while (tree || !Mystack_empty(stack)) {

        ///必须压栈, 因为是中序, 需要访问完左子树后利用栈返回状态
        if (tree) Mystack_push(tree, stack, NULL);

        if (tree) {
            tree = tree->left;
            continue;
        }

        ///取出栈顶元素
        tmpBt = Mystack_top(stack);

        ///相当于第2次碰到 节点, 访问
        if (*tmpBt && callbackFun && callbackFun && traverse_ing_work(traverseData, *tmpBt, callbackFun))break;

        tree = (*tmpBt)->right;

        Mystack_pop(stack, NULL);


    }


    alloc_recycle_mem(sizeof(MyStack), stack);
}

#pragma mark - 堆栈后序遍历
void traverse_last(BinaryTree* tree,TraverseCallFun callbackFun,TraverseStd* traverseData){
    T_LastStack* stack = T_Laststack_init();

    TraverseLastNode** tmpBt = NULL;

    int tmpFlag = 0, tmpMax = 0;

    while (tree || !T_Laststack_empty(stack)) {

        /**
         压栈
         并且标记 为0
         第一次遇到这个节点
         */

        if (tree){
            TraverseLastNode* newN = malloc(sizeof(TraverseLastNode));
            newN->flag = 0;
            newN->node = tree;
            T_Laststack_push(newN, stack, NULL);
        }



        ///遍历左子树 (也就是不停一层一层往下走, 这个时候层数要++)
        if (tree) {
            tmpFlag++;
            tree = tree->left;
            continue;
        }



        if (!T_Laststack_empty(stack)) {

            ////表示左子树遍历完毕,要开始遍历右子树了
            ///这个时候不能出栈, 要看当前栈顶元素的标记值
            tmpBt = T_Laststack_top(stack);

            if ((*tmpBt)->flag) {

                ////这里是第三次遇到了节点,表示右子树遍历完毕
                ////这个时候要判断 当前这个节点的层要不是最大的
                if (tmpMax<tmpFlag) {
                    tmpMax = tmpFlag;
                }

                ////右子树也遍历完毕, 那么要开始输出了
                tmpBt = T_Laststack_top(stack);
                if ((*tmpBt)->node && callbackFun && callbackFun){
                    traverseData->_std_basic.n_heigth = tmpFlag;
                    if(traverse_ing_work(traverseData, (*tmpBt)->node, callbackFun))break;
                }
                T_Laststack_pop(stack, NULL);

                ////出栈后相当于往回走(回到上一层) 所以要--
                tmpFlag--;
            }else{
                (*tmpBt)->flag = 1;
                ////找到栈顶元素开始遍历右子树
                tree = (*tmpBt)->node->right;
            }
        }

    }
    if (traverseData)traverseData->_std_basic.n_heigth = tmpMax;
    alloc_recycle_mem(sizeof(T_LastStack), stack);
}

#pragma mark - 堆栈层次遍历
void traverse_level(BinaryTree* tree,TraverseCallFun callbackFun,TraverseStd* traverseData){
    BinaryTreeQueueN* Q = BinaryTreequeue_init();
    BinaryTree** tmp = NULL;

    ////将第一个元素添加到队列里去
    BinaryTreequeue_add(Q, tree, NULL);

    while (!BinaryTreequeue_empty(Q)) {

        ////取出队列里的元素
        tmp = BinaryTreequeue_del(Q, NULL);

        ////访问
        if (callbackFun && callbackFun(traverseData))break;


        if ((*tmp)->left)BinaryTreequeue_add(Q, (*tmp)->left, NULL);
        if ((*tmp)->right)BinaryTreequeue_add(Q, (*tmp)->right, NULL);
        alloc_recycle_mem(sizeof(BinaryTree*), tmp);
        tmp = NULL;

    }

    alloc_recycle_mem(sizeof(BinaryTreeQueueN), Q);
}



#pragma mark - 二叉树高度
unsigned long tree_height(BinaryTreeRoot* root,TraverseCallFun* callbackFun){
    if (tree_empty(root)) return 0;

    TraverseStd* tmpTraverseData = NULL;
    if (callbackFun)
        tmpTraverseData = traversestd_create(TraverseBTType_last, callbackFun);

    traverse_last(root->root, callbackFun, tmpTraverseData);
    root->height = tmpTraverseData->_std_basic.n_heigth;
    alloc_recycle_mem(sizeof(TraverseStd), tmpTraverseData);
    return root->height;
}

#pragma mark - 递归二叉树的高度
unsigned long binary_tree_height_recursion(BinaryTree* tree){
    unsigned long hl = 0, hr = 0, maxh = 0;
    if (tree) {
        hl = binary_tree_height_recursion(tree->left);
        hr = binary_tree_height_recursion(tree->right);
        maxh = _MAX(hl, hr) + 1;
        return maxh;
    }else return 0;
}


#pragma mark - 二叉树成员个数
void binary_tree_items(BinaryTreeRoot* root){
    if (tree_empty(root))return;
    BinaryTree* tree = root->root;
    if (!tree) return;
    TraverseStd* tmp = traversestd_create(TraverseBTType_first, traverse_call_back);
    traverse_first(tree, traverse_call_back, tmp);
    root->count = tmp->_std_basic.index;
    alloc_recycle_mem(sizeof(TraverseStd), tmp);
}









#pragma mark - 辅助函数
bool tree_empty(BinaryTreeRoot* root){
    return !root?true:(root->count?false:true);
}

bool traverse_recursion_condition(BinaryTreeRoot* root){
    return  tree_empty(root)?true:(root->count < TraverseCriticalCount?true:false);
}

TraverseStd* traversestd_create(TraverseBTType type,TraverseCallFun callbackFun){
    TraverseStd* tmpTraverseData = alloc_find_mem(sizeof(TraverseStd));
    tmpTraverseData->_std_basic.index = -1; ///从0的前面开始
    tmpTraverseData->_std_basic.indexNode = NULL;
    tmpTraverseData->_std_basic.isStop = false;
    tmpTraverseData->_std_basic.traverseT = type;
    tmpTraverseData->cusType = NULL;
    tmpTraverseData->cusType = callbackFun?callbackFun(tmpTraverseData):NULL;
    return tmpTraverseData;
}

bool traverse_ing_work(TraverseStd* traverseData,BinaryTree* tree,TraverseCallFun callbackFun){
    if(!traverseData)return false;
    traverseData->_std_basic.index++;
    traverseData->_std_basic.indexNode = tree;
    callbackFun(traverseData);
    return traverseData->_std_basic.isStop;
}


void* traverse_call_back(TraverseStd* att){
    BinaryTree* node = att->_std_basic.indexNode;
    if (node)att->_std_basic.isStop = false;
    return NULL;
}



#ifdef DEBUG
void btTest(BinaryTreeRoot* root){
    
}
#endif
