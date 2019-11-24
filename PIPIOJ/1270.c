//
// Created by 李学俊 on 2019/10/19.
//
#include <stddef.h>

/*
 * 已知一颗二叉搜索树的先序遍历还原二叉树
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
void InsertSort(int a[], int n){
    int t;
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 && a[j] < a[j-1] ; j--) {
            t = a[j] ;
            a[j] = a[j-1];
            a[j-1] = t;
        }
    }
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
        in[i] = pre[i];
    }
    InsertSort(in,n);
    BTree T = CreateBTree(pre,in,n);
    PostOrder(T);
    return 0;
}