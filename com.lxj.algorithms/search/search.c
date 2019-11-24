//
// Created by 李学俊 on 2019/8/19.
//
#include "../list/list.c"
#define ElemType int
typedef struct {
    ElemType *elem;
    int length;
}SStable;

//顺序查找
int Search_Seq(SStable ST, ElemType key){
    ST.elem[0]=key;
    int i = ST.length;
    for(;ST.elem[i] != key; --i);
    return i;
}

//二分查找
int Binary_Search(SqList L, ElemType key){
    int low = 0, high = L.length-1, mid;
    while (low < high) {
        mid = (low + high)/2;
        if (L.data[mid] == key) {
            return mid;
        } else if (L.data[mid] > key) {
            high = mid-1;
        } else{
            low = mid+1;
        }
    }
    return -1;
}
