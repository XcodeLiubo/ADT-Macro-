//
//  MyAlloc.c
//  通用改造
//
//  Created by 刘泊 on 2019/3/14.
//  Copyright © 2019 LB. All rights reserved.
//

#include <stdlib.h>
#include "MyAlloc.h"

#define alloc_min_item 8        ///最小8个字节

#define alloc_max_item 128      ///最大128个字节

#define alloc_pool_unit 20      ///内存池 切割的单位

#define _MIN(a,b) ((a)>(b)?(b):(a))

#include <string.h>




Alloc g_alloc;
static void give_back_mgr(long long, void*);

static void* findPoolMem(long long);



void* alloc_find_mem(long long size){
    if (size > alloc_max_item)return malloc(size);
    return findPoolMem(size);
}

void alloc_recycle_mem(long long size, void* loc){
    if (size > alloc_max_item)free(loc);
    return give_back_mgr(size, loc);
}






#pragma mark - 辅助函数

static inline void adjustVolume(long long*);
static int findIdx(long long* count);
static void carvePool(long long size, int carveCount, void* beginMem);
static void mallocPool(long long size,int idx);
static int findNextListMgr(long long size, int idx);


void* findPoolMem(long long size){

    ////找到负责管理 size 字节的 第n号链表
    int idx = findIdx(&size);


    Alloc_List* tmpIdxList = g_alloc.list[idx];


    ///如果找到对应idx的管理链表 并且链表有值了直接拿
    if (tmpIdxList) {
        ///指向下一个节点
        g_alloc.list[idx] = tmpIdxList->next;
        
        return tmpIdxList;
    }

    ///剩余多少内存
    long long tmpResidueSize = g_alloc.poolEnded - g_alloc.poolStart;


    if (tmpResidueSize) {

        ///如果剩余内存<size(调整之后)
        if (tmpResidueSize<size) { ///不够切割当前这个单位
            /**
                方案: 从下一个idx开始 往后idx++ 找到最近的 有值的 管理链表,
                    如果找到 取出其中的一块, 切除size的长度, 然后将剩余的算出是第几个idx 挂上去
                    如果没找到, malloc一坨内存来 然后切割 40个单位 钱20个挂上去, 后面的当做剩余内存
             */

            int findNIdx = findNextListMgr(size, idx);

            if (findNIdx != -1) { ///找到了
                long long findUnit = findNIdx * 8 + 8;

                ///取出第一块
                Alloc_List* find = g_alloc.list[findNIdx];

                ///将找到的管理的list的指针指向下一个
                g_alloc.list[findNIdx] = find->next;

                ///清空掉
                find->next = NULL;


                ///取出的这块内存挂到 第idx的链表上
                g_alloc.list[idx] = find;


                ///算出给出去这块内存后剩余的内存(一定是16条链表里的某个单位)
                long long willUnit = findUnit - size;

                ///为了保险还是再一次计算出 willUnit 对应的idx
                long long willIdx = findIdx(&willUnit);

                ///定位到 给出 size 长度的地址去
                void* tmpBegin = ((void*)find)+ size;

                if(g_alloc.list[willIdx]){
                    ((Alloc_List*)tmpBegin)->next = g_alloc.list[willIdx];
                    g_alloc.list[willIdx] = tmpBegin;
                }else{
                    g_alloc.list[willIdx] = tmpBegin;
                }
                return findPoolMem(size);

            }else{
                /////直接malloc 40个当前单位的空间
                mallocPool(size * alloc_pool_unit * 2,idx);

                ///递归返回
                return findPoolMem(size);
            }



            return NULL;

        }else{
            ////将剩余内存挂到对应的链表上
            g_alloc.list[idx] = g_alloc.poolStart;

            ///查看剩余内存能切多少块
            int craveCount = _MIN((int)(tmpResidueSize / size),alloc_pool_unit);

            ///调整剩余内存的起始地址
            g_alloc.poolStart += craveCount * size;

            ////切割链接起来
            carvePool(size, craveCount, g_alloc.list[idx]);

            ///递归一下 返回
            return findPoolMem(size);
        }

    }else{
        /**
            malloc 内存空间 这样做有个问题, 就是 如果上面的if 里刚好是将 剩余内存用光了(tmpResidueSize), 但是数组里还有 链表(比如 idx == 13 14 15等等时)有值, 那么这个时候,还挂着很多空的没用的 空间, 如果直接从malloc取, 是不是浪费了
         */

        /////直接malloc 40个当前单位的空间
        mallocPool(size * alloc_pool_unit * 2,idx);

        ///递归返回
        return findPoolMem(size);
    }
}

#pragma mark - 上调为 8的倍数
void adjustVolume(long long* size){
    *size = *size + (alloc_min_item - 1) & ~(alloc_min_item - 1);
}

#pragma mark - 找到是第n个链表
int findIdx(long long* volume){
    adjustVolume(volume);
    return (int)*volume/8-1;
}

#pragma mark - 切割
void carvePool(long long size, int carveCount, void* beginMem){
    Alloc_List* tmpIdxList = beginMem;
    for (int i = 1; i < carveCount; ++i){
        tmpIdxList->next = beginMem + size*i;
        tmpIdxList = tmpIdxList->next;
    }
}

#pragma mark - 挖一块内存作为pool
void mallocPool(long long size, int idx){
    void* pool = malloc(size);
    memset(pool, '\0', size); ////全部清零
    g_alloc.list[idx] = pool;

    ////切割前20个
    int unit = idx*8+8;
    carvePool(unit, alloc_pool_unit, pool);


    ///调整pool的起始位置
    g_alloc.poolStart = pool + unit * alloc_pool_unit;
    g_alloc.poolEnded = pool + unit * alloc_pool_unit * 2;//0x000000010283f688 0x0000000102840ef0
}

#pragma mark - 当pool<size后, 寻找下一个listmgr
int findNextListMgr(long long size, int idx){
    for (int i = idx + 1; i < MGR_MAX; ++i) {
        if(g_alloc.list[i])return i;
    }
    return -1;
}





#pragma mark - 归还到内存池里
void give_back_mgr(long long size, void* loc){//0x0000000100726df0 0x0000000100726e00
    int idx = findIdx(&size);
    Alloc_List* tmp = g_alloc.list[idx];
    ((Alloc_List*)loc)->next = tmp;
    g_alloc.list[idx] = loc;
}
