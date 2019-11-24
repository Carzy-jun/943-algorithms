//
// Created by 李学俊 on 2019/11/1.
//
//寻找最近公共祖先
#include <stddef.h>
#include <stdbool.h>

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
int flag = 0;
void InOrder(BiNode *T,int p,int q) {
    if (T == NULL)return;
    InOrder(T->lchlid,p,q);
    if (T->data==p || T->data==q)flag++;
    InOrder(T->rchlid,p,q);
}
int Ancestor(BTree T, int p, int q) {
    flag = 0;
    InOrder(T->lchlid,p,q);
    if (flag == 2)return Ancestor(T->lchlid,p,q);
    flag = 0;
    InOrder(T->rchlid,p,q);
    if (flag == 2)return Ancestor(T->rchlid,p,q);
    return T->data;
}

int main() {
    BTree T = CreateBT(T);
    int p,q,a;
    scanf("%d%d",&p,&q);
    a = Ancestor(T,p,q);
    printf("%d\t", a);
}










