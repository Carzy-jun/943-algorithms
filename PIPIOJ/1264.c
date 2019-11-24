#include <stddef.h>

//
// Created by 李学俊 on 2019/10/24.
//
/*
 * 给出二叉搜索树的根节点，该二叉树的节点值各不相同，修改二叉树，
 * 使每个节点node 的新值等于原树中大于或等于 node.val 的值之和。
 */
typedef struct BTree {
    int data,v;
    struct BTree *lchlid, *rchlid;
} *BTree, BiNode;
BTree t;
BTree CreateBT(BTree T) {
    T = (BTree) malloc(sizeof(BTree));
    int c;
    scanf("%d",&c);
    if (c!= -1) {
        T->v = 0;
        T->data = c;
        T->lchlid = CreateBT(T->lchlid);
        T->rchlid = CreateBT(T->rchlid);
        return T;
    } else {
        return NULL;
    }
}
void Count(BTree T,BTree a){
    if (!T) return ;
    Count(T->lchlid,a);
    if (T->v == 0 && T!=a) {
        a->data = a->data + T->data;
    }
    Count(T->rchlid,a);
}

void Change(BTree T){
    if (!T) return ;
    Change(T->lchlid);
    Count(t,T);
    T->v = 1;
    Change(T->rchlid);
}
void Print(BTree T){
    if (!T) {
        printf("%d\t", -1);
        return;
    }
    printf("%d\t", T->data);
    Print(T->lchlid);
    Print(T->rchlid);
}
int main(){
    t = CreateBT(t);
    Change(t);
    Print(t);
    return 0;
}
