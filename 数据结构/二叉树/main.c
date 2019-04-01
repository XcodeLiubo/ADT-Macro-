//
//  main.c
//  二叉树
//
//  Created by 刘泊 on 2019/3/30.
//  Copyright © 2019 LB. All rights reserved.
//

#include <stdio.h>

#include "BinaryTree.h"
#include "MyAlloc.h"

#include <stdlib.h>

typedef void test(void);

typedef struct testSTs testSTs;

struct testSTs{
    int a;
};


void*  loopCallbackFun(TraverseStd* att){
    BinaryTree* node = att->_std_basic.indexNode;
    if (node) {
        att->_std_basic.isStop = false;
        printf("\n%d index:%ld level:%ld ",node->value,att->_std_basic.index,att->_std_basic.n_heigth);
    }

    return NULL;
}

int main(int argc, const char * argv[]){
    BinaryTreeRoot* root = create_tree_root();

    BinaryTree* t = create_tree_node(1,NULL);
    root->root = t;
    root->count++;

    BinaryTree* t2 = create_tree_node(2, NULL);
    t->left = t2;
    root->count++;

    BinaryTree* t3 = create_tree_node(3, NULL);
    t->right = t3;
    root->count++;

    BinaryTree* t4 = create_tree_node(4, NULL);
    t2->left = t4;
    root->count++;

    BinaryTree* t5 = create_tree_node(5, NULL);
    t2->right = t5;
    root->count++;

    BinaryTree* t6 = create_tree_node(6, NULL);
    t3->right = t6;
    root->count++;

    BinaryTree* t7 = create_tree_node(7, NULL);
    t5->right = t7;
    root->count++;
//
    BinaryTree* t8 = create_tree_node(8, NULL);
    t6->left = t8;
    root->count++;

    BinaryTree* t9 = create_tree_node(9, NULL);
    t8->left = t9;
    root->count++;


/**
 1 2 4 5 7 3 6 8
 4 2 5 7 1 3 8 6
 4 7 5 2 8 6 3 1

                        1
                2              3
            4      5                 6
                       7        8

 */

    ///1 2 4 5 7 3 6 8
    traverse_binaryT(root, TraverseBTType_first, loopCallbackFun);
    printf("\n");

    ///4 2 5 7 1 3 8 6
    traverse_binaryT(root, TraverseBTType_middle, loopCallbackFun);
    printf("\n");

    ///4 5 2 6 3 1
    traverse_binaryT(root, TraverseBTType_last, loopCallbackFun);
    printf("\n");

    traverse_binaryT(root, TraverseBTType_level, loopCallbackFun);
    printf("\n");

//    btTest(root);
    tree_height(root, loopCallbackFun);

    return 1;

}
