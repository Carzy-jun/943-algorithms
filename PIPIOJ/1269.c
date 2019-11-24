//
// Created by 李学俊 on 2019/10/19.
//
#include <stdio.h>
#include <stddef.h>

/*
 *  后序、中序序列还原二叉树
 */
typedef struct BTree{
    int data;
    struct BTree *lchlid,*rchlid;
}*BTree,BiNode;

BTree CreateBTree(int *post, int *in, int n){
    BiNode *b;
    int *p,k,r;
    if (n <= 0)
        return NULL;
    b = (BTree)malloc(sizeof(BiNode));
    r = *(post+n-1);
    b->data = r;
    for (p = in; p < in+n; p++) {
        if (*p == r) {
            break;
        }
    }
    k = (int) (p - in);
    b->lchlid = CreateBTree(post,in,k);
    b->rchlid = CreateBTree(post+k,p+1,n-k-1);
    return b;
}

void PreOrder(BiNode *T){
    if (T != NULL){
        printf("%d\t",T->data);
        PreOrder(T->lchlid);
        PreOrder(T->rchlid);
    }
}

int main(){
    int n, post[100],in[100];
    scanf("%d",&n);
    for (int j = 0; j < n; ++j) {
        scanf("%d",in+j);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d",post+i);
    }
    BTree T = CreateBTree(post,in,n);
    PreOrder(T);
    return 0;
}
