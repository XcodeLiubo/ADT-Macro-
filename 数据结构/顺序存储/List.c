#define ImCMacro(__pre_identify__ ,__type__)\
\
void __pre_identify__##list_loop(__pre_identify__##ListN* ptrL,__pre_identify__##ListLoopFun fun){\
    if (ptrL == 0) return;\
    if (fun == 0) return;\
\
    bool stop = false;\
    int tmpIndex = 0;\
    while (ptrL) {\
        fun(ptrL->data, tmpIndex++, &stop);\
        if (stop)break;\
        ptrL = ptrL->next;\
    }\
}\
\
int __pre_identify__##list_length(__pre_identify__##ListN* ptrL){\
    if (!ptrL)return 0;\
\
    int count = 1;\
    while ((ptrL = ptrL->next))count++;\
    return count;\
}\
\
__pre_identify__##ListN* __pre_identify__##list_index(__pre_identify__##ListN* ptrL, int index){\
\
    if (ptrL == 0)return 0;\
\
    if (index < 0)return 0;\
\
    int tmp_index = 0;\
\
    while (ptrL){\
        if (tmp_index++ == index)return ptrL;\
        ptrL = ptrL->next;\
    }\
    return 0;\
}\
\
\
void __pre_identify__##list_value(__pre_identify__##ListN* ptrL, __type__* target, __pre_identify__##ListCmFun callback){\
    if (ptrL == 0)return;\
\
    if (target == 0)return;\
\
    while (ptrL){\
        if (callback && callback(target,ptrL->data))break;\
        else if (target == ptrL->data)break;\
        ptrL = ptrL->next;\
    }\
}\
\
\
\
__pre_identify__##ListN* __pre_identify__##list_insert(__pre_identify__##ListN* ptrL, __type__* inseart, int insertIndex,__pre_identify__##ListAssignDataFun assignFun){\
    if (ptrL == NULL)return NULL;\
\
    if (inseart == NULL)return ptrL;\
\
    if (insertIndex == 0) {\
        __pre_identify__##ListN* newN = NULL;\
        newN = malloc(sizeof(typeof(__pre_identify__##ListN)));\
        if (newN) {\
            if (assignFun) {\
                newN->data = malloc(sizeof(typeof(__type__)));\
                assignFun(newN->data,inseart);\
            }else newN->data = inseart;\
            newN->next = ptrL;\
            ptrL = newN;\
        }\
        return ptrL;\
    }\
\
__pre_identify__##ListN* preN = __pre_identify__##list_index(ptrL, insertIndex - 1);\
    if (!preN) return ptrL;\
\
\
\
    __pre_identify__##ListN* newN = malloc(sizeof(typeof(__pre_identify__##ListN)));\
    if (newN) {\
        if (assignFun){\
            newN->data = malloc(sizeof(typeof(__type__)));\
            assignFun(newN->data,inseart);\
        }else newN->data = inseart;\
\
        newN->next =  preN->next;\
        preN->next = newN;\
    }\
\
    return ptrL;\
}\
\
\
__pre_identify__##ListN* __pre_identify__##list_remove(__pre_identify__##ListN* ptrL, int delIndex, __pre_identify__##ListDelDataFun delFun){\
    if (ptrL == 0) return ptrL;\
\
    if (delIndex == 0) {\
        __pre_identify__##ListN* tmpPtrL = ptrL;\
        if (delFun)delFun(ptrL->data);\
        ptrL = ptrL->next;\
        free(tmpPtrL);\
    }else{\
        __pre_identify__##ListN* tmpPreN = __pre_identify__##list_index(ptrL, delIndex - 1);\
        if (tmpPreN && tmpPreN->next) {\
            __pre_identify__##ListN* tmp = tmpPreN->next;\
            tmpPreN->next = tmpPreN->next->next;\
            if (delFun)delFun(tmp->data);\
            free(tmp);\
        }\
    }\
    return ptrL;\
}\
