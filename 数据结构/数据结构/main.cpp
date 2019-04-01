//
//  main.cpp
//  数据结构
//
//  Created by 刘泊 on 2018/10/23.
//  Copyright © 2018 LB. All rights reserved.
//

#include <iostream>
#include <stack>

#include <map>

#include <string>

#define ret return


typedef struct node     ENode;
typedef struct node*    PENode;
typedef int ENodeData;

struct node{
    PENode LPNode;  //左子节点
    PENode RPNode;  //右子节点
    PENode SuperNode; //父节点
    ENodeData data;       //数据
    
    node(){
        LPNode = NULL;
        RPNode = NULL;
        SuperNode = NULL;
        data = 0;
    }
};

struct StackData{
    PENode data_;
    bool left_;
    bool right_;
    StackData(PENode data){
        this->data_ = data;
        
        if (!data) {
            this->left_ = false;
            this->right_ = false;
        }else{
            //初始化的时候 2个标记会根据条件为true 在遍历的过程中 会根据状态变成false
            if (data->LPNode) this->left_ = true;
            else this->left_ = false;
            
            if (data->RPNode) this->right_ = true;
            else this->right_ = false;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const StackData* data){
    
    if (data->data_) {
        os << (data->data_->data) << " ";
    }
    ret os;
}




PENode createNode(ENodeData data, PENode superNode){
    PENode tmp = (PENode)malloc(sizeof(ENode));
    tmp->data = data;
    tmp->SuperNode = superNode;
    tmp->LPNode = NULL;
    tmp->RPNode = NULL;
    return tmp;
}


void printLTree(PENode node){
    if (node->LPNode) {
        std::cout << node->data << " ";
        return printLTree(node->LPNode);
    }else{
        std::cout << node->data << " ";
    }
}


void printRTree(PENode node){
    if (node->RPNode) {
        std::cout << node->data << " ";
        return printRTree(node->RPNode);
    }else{
        std::cout << node->data << " ";
    }
}


typedef enum : unsigned int{
    TraverseF, //先序遍历
    TraverseM, //中序
    TraverseB //后序
}Traverse;



void printTreeF(PENode node){
    if (node) {
        std::cout << node->data << " ";
        printTreeF(node->LPNode);
        printTreeF(node->RPNode);
    }
}

void printTreeM(PENode node){
    if (node) {
        printTreeM(node->LPNode);
        std::cout << node->data << " ";
        printTreeM(node->RPNode);
    }
}

void printTreeB(PENode node){
    if (node) {
        printTreeB(node->LPNode);
        printTreeB(node->RPNode);
        std::cout << node->data << " ";
    }
}

void loopTree(PENode node, Traverse type){
    switch (type) {
        case TraverseF:
            std::cout << "先序遍历:\n";
            printTreeF(node);
            break;
            
        case TraverseM:
            
            std::cout << "中序遍历:\n";
            printTreeM(node);
            break;
            
        case TraverseB:
            
            std::cout << "后序遍历:\n";
            printTreeB(node);
            break;
            
        default:
            break;
    }
}





//非递归实现先序
void printFN(PENode node){
    if (NULL == node) {
        std::cerr << "空指针\n";
        exit(0);
    }
    
    
    
#if 1
    std::cout << "\n";
    std::stack<PENode> st;
    PENode recordNode = node;
    
    //record 永远比栈里的元素多一步 只要左子树没遍历完就不能出栈, 否则在出栈的时候要还原到上一步的状态
    while (st.size() || recordNode) {
        if (recordNode) {
            std::cout << recordNode->data << " ";
            st.push(recordNode);
            recordNode = recordNode->LPNode;
        }else{
            //record 记录的是空的, 返回上一步状态 同时指向右子树
            recordNode = st.top()->RPNode;
            
            //继续返回上一步的状态
            st.pop();
            
        }
    }
    
    
#endif
    
    
    
#if 0
    std::cout << "\n";
    std::stack<PENode> st;
    PENode recordNode = node;
    
    //总体是压左边,再压右边 如果左边没有了要出栈, 但是出栈钱要记录到他的右边
    while (recordNode != NULL || !st.empty()) {
        if (recordNode) {
            std::cout << recordNode->data << " ";
            st.push(recordNode);
            recordNode = recordNode->LPNode;
        }else{
            recordNode = st.top();
            st.pop();
            recordNode = recordNode->RPNode;
        }
    }
#endif
    
    
#if 0
    std::stack<StackData*> st;
    StackData* recordNode = new StackData(node);
    
    std::cout << "先序遍历非递归\n";
    while (1) {
        st.push(recordNode);
        std::cout << recordNode;
        
        if (recordNode->left_) {
            recordNode->left_ = false; //压栈表示会遍历当前节点的左子树, 必然为false
            recordNode = new StackData(recordNode->data_->LPNode);//指向新的节点
            continue;
        }
        if (recordNode->right_) {
            recordNode->right_ = false;//压栈表示会遍历当前节点的右子树, 必然为false
            recordNode = new StackData(recordNode->data_->RPNode);
            continue;
        }
        
        
        while (1) {
            if (recordNode->left_ == false && recordNode->right_ == false) {
                delete recordNode;
                st.pop();
            }else{
                recordNode->right_ = false;//这里必须标记右子树为false
                recordNode = new StackData(st.top()->data_->RPNode);
                break;
            }
            if (st.size())recordNode = st.top();
            else break;
            
       }
       if (st.size() == 0) {
            break;
       }
    }
    
#endif
}



PENode createBinaryTree(){
    PENode p;
    int ch;
    std::cin>>ch;
    
    //如果到了叶子节点，接下来的左、右子树分别赋值为0
    if(ch == 0){
        p = NULL;
    }else{
        p = (PENode)malloc(sizeof(ENode));
        p->data = ch;
        p->LPNode  = createBinaryTree();  //递归创建左子树
        p->RPNode = createBinaryTree();  //递归创建右子树
    }
    return p;
}



PENode createTreeWithF(){
    
    
    
    ENodeData flag = 0;
    
    
    PENode node = NULL;
    
    
    
    
    std::stack<PENode> st;
    PENode recordNode = node;
    
    char ch;
    do {
        
        //创建第一个节点
        if (node == NULL) {
            std::cout << "数据:";
            std::cin >> flag;
            
            recordNode = new ENode();
            recordNode->data = flag;
            node = recordNode;
            
            st.push(recordNode);
        }
        
        
        std::cout << "节点结束/继续/停止(#/n/s):";
        std::cin >> ch;
        
        if (ch == 's')break;
        else if(ch == '#'){
            if (recordNode->RPNode) {
                st.pop();
                std::cout << "\n数据:";
                std::cin >> flag;
                recordNode = new ENode();
                recordNode->data = flag;
                st.top()->RPNode = recordNode;
            }else{
                std::cout << "\n数据:";
                std::cin >> flag;
                recordNode = new ENode();
                recordNode->data = flag;
                st.top()->RPNode = recordNode;
                st.pop();
            }
        }else{
            std::cout << "\n数据:";
            std::cin >> flag;
            
            recordNode = new ENode();
            recordNode->data = flag;
            st.top()->LPNode = recordNode;
            st.push(recordNode);
        }
    } while (st.size());
    
    
    //清空栈
    
    return node;
    
}

int main(int argc, const char * argv[]) {
    
    {
        /**
                                    1
                        2                       3
                4               5        6              7
            8       9       10
         */
        {
            PENode node = createTreeWithF();
//            PENode node = createBinaryTree();
            printFN(node);

            return 1;
        }
        
        
        
#if 1
        PENode nodes = createNode(1, NULL);
        
        
        //2
        PENode tmp2 = createNode(2, nodes);
        nodes->LPNode = tmp2;
        
        
        //3
        PENode tmp3 = createNode(3, nodes);
        nodes->RPNode = tmp3;
        
        
        //4
        PENode tmp4 = createNode(4, tmp2);
        tmp2->LPNode = tmp4;
        
        //5
        PENode tmp5 = createNode(5, tmp2);
        tmp2->RPNode = tmp5;
        
        
        
        //6
        PENode tmp6 = createNode(6, tmp3);
        tmp3->LPNode = tmp6;
        
        
        //7
        PENode tmp7 = createNode(7, tmp3);
        tmp3->RPNode = tmp7;
        
        
        //8
        PENode tmp8 = createNode(8, tmp4);
        tmp4->LPNode = tmp8;
        
        
        //9
        PENode tmp9 = createNode(9, tmp4);
        tmp4->RPNode = tmp9;
        
        
        //10
        PENode tmp10 = createNode(10, tmp5);
        tmp5->LPNode = tmp10;
        
        //11
        PENode tmp11 = createNode(11, tmp10);
        tmp10->LPNode = tmp11;
        
        
        
        
        //12
        PENode tmp12 = createNode(12, tmp6);
        tmp6->LPNode = tmp12;
        

        
        
        loopTree(nodes,TraverseF);
        
        
        printFN(nodes);
        std::cout << "\n";
//        NoPreOrderTraverse(tmp3);
        ret 1;
#endif
    }
    
    return 0;
}
