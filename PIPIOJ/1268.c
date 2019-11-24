//
// Created by 李学俊 on 2019/10/19.
//
#include <stddef.h>

/*
 * 先序、中序序列还原二叉树
 */
typedef struct BTree{
    int data;
    struct BTree *lchlid,*rchlid;
}*BTree,BiNode;

BiNode *CreateBTree(int *pre, int *in, int n){
    BiNode *b;
    int *p,k;
    if (n <= 0)
        return NULL;
    b = (BTree)malloc(sizeof(BiNode));
    b->data = *pre;
    for (p = in; p < in+n; p++) {
        if (*p == *pre) {
            break;
        }
    }
    k = (int) (p - in);
    b->lchlid = CreateBTree(pre+1,in,k);
    b->rchlid = CreateBTree(pre+k+1,p+1,n-k-1);
    return b;
}

void PostOrder(BiNode *T){
    if (T != NULL){
        PostOrder(T->lchlid);
        PostOrder(T->rchlid);
        printf("%d\t",T->data);
    }
}

int main(){
    int n, pre[100],in[100];
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        scanf("%d",pre+i);
    }
    for (int j = 0; j < n; ++j) {
        scanf("%d",in+j);
    }
    BTree T = CreateBTree(pre,in,n);
    PostOrder(T);
    return 0;
}