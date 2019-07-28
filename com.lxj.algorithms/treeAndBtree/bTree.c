//
// Created by 李学俊 on 2019/7/10.
//
#include <stddef.h>
#include <stdio.h>
#include <malloc.h>

//二叉树结构定义
typedef struct BTree{
    int data;
    struct BTree *lchlid,*rchlid;
}*BTree,BiNode;

//建立二叉树
BTree CreateBT(int a[], int n, int i){
    if (i > n)  return NULL;
    else{
        BTree T = (BTree)malloc(sizeof(BTree));
        if (a[i] != 0) {
            T->data = a[i];
            T->lchlid = CreateBT(a, n, 2*i);
            T->rchlid = CreateBT(a, n, 2*i+1);
            return T;
        } else {
            return NULL;
        }
    }
}
//销毁二叉树
//如果采用先序遍历或者中序遍历，销毁根节点后就找不到左右孩子
//在销毁的时候需要保存左右孩子的地址。
//因此采用后序遍历销毁一颗二叉树，按照左孩子，右孩子，根节点的顺序销毁，
//注意：根节点将根节点指向空，防止成为野指针。
void DestoryBT(BTree T){
    if (!T) {
        return;
    }
    DestoryBT(T->lchlid);
    DestoryBT(T->rchlid);
    free(T);
}
BTree CreateBT1(int a[], int n){
    BTree *p;
    p = (BTree*)malloc(sizeof(BTree)*n);
    for (int i = 1; i <= n; ++i) {
        if (a[i] != 0) {
            p[i] = (BTree)malloc(sizeof(BiNode));
            p[i]->data = a[i];
        } else {
            p[i] = NULL;
        }
    }
    for (int j = 1; j <= n; ++j) {
        if (p[j] != NULL) {
            p[j]->lchlid = p[2*j];
            p[j]->rchlid = p[2*j+1];
        }
    }
    return p[1];
}
