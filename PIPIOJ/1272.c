//
// Created by 李学俊 on 2019/10/18.
//
#include <stddef.h>
#include <stdbool.h>

/*
 * 验证BST
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
int t = -32767;
bool IsBST(BTree T){
    if (T == NULL) {
        return true;
    }
    bool f1 = IsBST(T->lchlid);
    if (t >= T->data) {
        return false;
    }
    t = T->data;
    bool f2 = IsBST(T->rchlid);
    return f1 && f2;
}
int main(){
    BTree T = NULL;
    T = CreateBT(T);
    if (IsBST(T))
        printf("true");
    else
        printf("false");
    return 0;
}