//
// Created by 李学俊 on 2019/11/12.
//
//若一棵二叉树的左子树和右子树是镜像对称的，我们就将这棵二叉树称为手性二叉树。

#include <stddef.h>
#include <stdbool.h>

typedef struct BTree {
    int data;
    struct BTree *lchlid, *rchlid;
} *BTree;
BTree CreateBT(BTree T) {
    T = (BTree) malloc(sizeof(BTree));
    int c;
    scanf("%d",&c);
    if (c!= -1) {
        T->data = c;
        T->lchlid = CreateBT(T->lchlid);
        T->rchlid = CreateBT(T->rchlid);
        return T;
    } else
        return NULL;
}

bool IsMirror(BTree t1, BTree t2){
    if (!t1 && !t2) {
        return true;
    }
    if (!t1 || !t2) {
        return false;
    }
    return t1->data == t2->data && IsMirror(t1->lchlid,t2->rchlid) && IsMirror(t1->rchlid,t2->lchlid);
}
int main(){
    BTree T = NULL;
    T = CreateBT(T);
    if (IsMirror(T,T)) printf("yes\n");
    else printf("no\n");
}