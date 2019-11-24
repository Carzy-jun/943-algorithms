//
// Created by 李学俊 on 2019/11/2.
//
//并查集数据结构

#include "../map/Mapset.c"


typedef struct {
    int data;
    int rank;//节点对应秩，秩为近似子树高度的正整数，节点高度的一个上界
    int parent;//双亲下标
}UFSTree;

//初始化并查集树
void MAKE_SET(UFSTree t[],int n){
    for (int i = 0; i < n; ++i) {
        t[i].data = i;
        t[i].rank = 0;
        t[i].parent = i; //双亲初始化指向自己
    }
}

//在x所在的子树中查找集合编号
int FIND_SET(UFSTree t[], int x){
    if (x != t[x].parent) {
        return FIND_SET(t, t[x].parent);
    } else {
        return x;
    }
}

//将x和y所在的子树合并
void UNION(UFSTree t[], int x, int y){
    x = FIND_SET(t, x);
    y = FIND_SET(t, y);
    if (t[x].rank > t[y].rank) {
        t[y].parent = x;
    } else {
        t[x].parent = y;
        if (t[x].rank == t[y].rank) {
            t[y].rank++;
        }
    }
}

