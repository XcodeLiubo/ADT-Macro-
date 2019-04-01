//
//  MyAlloc.h
//  通用改造
//
//  Created by 刘泊 on 2019/3/14.
//  Copyright © 2019 LB. All rights reserved.
//

#ifndef MyAlloc_h
#define MyAlloc_h

#define MGR_MAX 16



#if 1
typedef struct Alloc Alloc;

typedef struct Alloc_List Alloc_List;

struct Alloc_List{
    union{
        void* size;
        Alloc_List* next;
    };
};

struct Alloc{
    Alloc_List* list[MGR_MAX];
    void* poolStart;            ///内存备用池的起始地址
    void* poolEnded;            ///内存备用池的结束地址
};

#endif

/** 这里 虽然是 long long 但设计的就是给容器用的, 所以最好传入 sizeof(type) 容器里元素的类型的长度*/
extern void* alloc_find_mem(long long);

extern void alloc_recycle_mem(long long, void*);

#endif /* MyAlloc_h */


extern Alloc g_alloc;
