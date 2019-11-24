#include <stddef.h>

//
// Created by 李学俊 on 2019/11/14.
//
//PIPI有一棵结点值均不相同的二叉树，现在他想知道某结点的祖先结点有哪些，你能帮PIPI解决这个问题吗？
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
typedef struct {
    int data1[100];
    BTree data[100];
    int top;
}st;

void Ancestor(BTree t, int x){
   BTree p = t;int n;
   st *st1 = (st*)malloc(sizeof(st));
   st *st2 = (st*)malloc(sizeof(st));
   st1->top = -1;
   st2->top = -1;
    while (st1->top != -1 || p) {
        while (p) {
            st1->data[++st1->top] = p;
            st2->data1[++st2->top] = 0;
            p = p->lchlid;
        }
        p = st1->data[st1->top--];
        n = st2->data1[st2->top--];
        if (n == 0) {
            st1->data[++st1->top] = p;
            st2->data1[++st2->top] = 1;
            p = p->rchlid;
        } else {
            if (p->data == x) {
                if (st1->top == -1) {
                    printf("No Ancestor!");
                    return;
                } else {
                    for (int i = 0; i < st1->top+1; ++i) {
                        printf("%d\t", st1->data[i]->data);
                    }
                    return;
                }
            }
            p = NULL;
        }
    }
    printf("No Node!");
}

int main(){
    BTree t = NULL;
    t = CreateBT(t);
    int x;
    scanf("%d",&x);
    Ancestor(t,x);
}