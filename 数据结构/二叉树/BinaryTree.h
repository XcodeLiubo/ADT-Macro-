//
//  BinaryTree.h
//  二叉树
//
//  Created by 刘泊 on 2019/3/8.
//  Copyright © 2019 LB. All rights reserved.
//

#ifndef BinaryTree_h
#define BinaryTree_h

//#include <stdio.h>
typedef int bool;
#define false 0
#define true 1


#define BT_VType int
typedef struct BinaryTree BinaryTree;
typedef struct BinaryTreeRoot BinaryTreeRoot;




struct BinaryTree{
    BT_VType value;
    BinaryTree* left;
    BinaryTree* right;
};
struct BinaryTreeRoot{
    BinaryTree* root;
    ///这两个成员涉及到二叉树的插入删除的时候
    size_t count;               ///二叉树节点的个数
    unsigned long height;       ///二叉树的高度
};








/** 创建树的根节点 */
extern BinaryTreeRoot* create_tree_root(void);





typedef enum{
    TreeType_common,    ////普通的二叉树
    TreeType_whole,     ////完全二叉树
    TreeType_perfect,   ////满二叉树
}TreeType;

/** 创建树 */
extern BinaryTreeRoot* create_tree(BinaryTreeRoot* root,TreeType type);



typedef void TreeNewNodeAssignFun (BT_VType* oriData, BT_VType* newData);
/** 创建一个节点 */
extern BinaryTree* create_tree_node(BT_VType,TreeNewNodeAssignFun);

/** 二叉树成员个数 结果放在root->count里*/
extern void binary_tree_items(BinaryTreeRoot* root);



typedef enum{
    TraverseBTType_first,       ////先序遍历
    TraverseBTType_middle,      ////中序遍历
    TraverseBTType_last,        ////后序遍历
    TraverseBTType_level,       ////层次遍历
}TraverseBTType;
//traverse_recursion_critical

/** 遍历为了统一*/
struct TraverseStd{
    struct{
        BinaryTree* indexNode;      ///当前的节点
        union{
            size_t index;               ///当前遍历的要第index位置
        };
        unsigned long n_heigth;     ///当前节点是哪一层(只有调用 tree_height 函数才有意义, 并且调用完后其值 = 树的总高度)
        TraverseBTType traverseT;   ///当前遍历的类型
        bool isStop;                ///是否停止
    }_std_basic;
    void* cusType;
};
typedef struct TraverseStd TraverseStd;
/** 内部会调用获取 cusType  */
typedef void*  TraverseCallFun(TraverseStd*);
/** 二叉树的遍历 */
extern void traverse_binaryT(BinaryTreeRoot* root,TraverseBTType type,TraverseCallFun callbackFun);

/** 获取二叉树每个结点在哪一层(回调TraverseCallFun里) 返回结果是二叉树的高度*/
extern unsigned long tree_height(BinaryTreeRoot*,TraverseCallFun);




#ifdef DEBUG
extern void btTest(BinaryTreeRoot*);
#endif






#endif /* BinaryTree_h */
