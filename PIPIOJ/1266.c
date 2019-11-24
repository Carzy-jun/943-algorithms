//
// Created by 李学俊 on 2019/10/24.
//
#include <stddef.h>

/*
 * 求二叉树的直径
 */
typedef struct BTree {
    int data;
    struct BTree *lchlid, *rchlid;
} *BTree, BiNode;

BTree CreateBT(BTree T) {
    T = (BTree) malloc(sizeof(BTree));
    int c;
    scanf("%d",&c);
    if (c!= -1) {
        T->data = c;
        T->lchlid = CreateBT(T->lchlid);
        T->rchlid = CreateBT(T->rchlid);
        return T;
    } else {
        return NULL;
    }
}
int GetLength(BTree T){
    if (!T) {
        return 0;
    }
    int l = GetLength(T->lchlid)+1;
    int r = GetLength(T->rchlid)+1;
    return l>r?l:r;
}
int GetDiameter(BTree T){
    int l = GetLength(T->lchlid);
    int r = GetLength(T->rchlid);
    return l+r;
}
int main(){
    BTree T = CreateBT(T);
    int d = GetDiameter(T);
    printf("%d\t", d);
}