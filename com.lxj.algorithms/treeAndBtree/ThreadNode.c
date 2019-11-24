#include <stddef.h>

//
// Created by 李学俊 on 2019/7/17.
//
//线索二叉树
typedef struct ThreadTree{
    int data;
    struct ThreadTree *lchild, *rchild;
    int ltag, rtag; //左右线索标志
}ThreadNode,*ThreadTree;

ThreadTree Create(int a[], int n, int i){
    if (i > n)  return NULL;
    else{
        ThreadTree T = (ThreadTree)malloc(sizeof(ThreadTree));
        if (a[i] != 0) {
            T->data = a[i];
            T->lchild = Create(a, n, 2*i);
            T->rchild = Create(a, n, 2*i+1);
            return T;
        } else {
            return NULL;
        }
    }
}
void InThread(ThreadTree p, ThreadTree pre){
    if (p != NULL) {
        InThread(p->lchild,pre);
        if (p->lchild) {
            p->ltag = 0;
        }
        if (p->lchild == NULL) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (p->rchild) {
            p->rtag = 0;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        InThread(p->rchild, pre);
    }
}
void CreateInThread(ThreadTree T){
    ThreadTree pre = NULL;
    if (T) {
        InThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}
ThreadTree FirstNode(ThreadTree p){
    while (p->ltag == 0) {
        p = p->lchild;
    }
    return p;
}
ThreadTree NextNode(ThreadTree p){
    if (p->rtag == 0) {
        return FirstNode(p->rchild);
    } else {
        return p->rchild;
    }
}

void InOrder(ThreadTree T){
    for (ThreadTree p = FirstNode(T);p != NULL; p = NextNode(p)) {
        printf("%d\t", p->data);
    }
}
int main(){
    int a[]={0,1,2,3,4,5,6,7,8};
    ThreadTree T = Create(a, 8, 1);
    CreateInThread(T);
    InOrder(T);
}