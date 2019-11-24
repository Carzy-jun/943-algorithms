//
// Created by 李学俊 on 2019/11/19.
//
//PIPI最近在看家里的族谱，发现族谱刚好组成了一棵二叉树，
// 现在PIPI想询问族谱中的两个结点是否为兄弟或者堂兄弟。
//兄弟: 深度相同, 双亲节点相同(同一个结点不能是兄弟)。
//堂兄弟: 深度相同，双亲节点不同。
#include <stddef.h>

typedef struct node {
    int data;
    struct node *left, *right;
} *BTree;

BTree Build() {
    BTree T = (BTree) malloc(sizeof(BTree));
    int c;
    scanf("%d", &c);
    if (c == -1) return NULL;
    T->data = c;
    T->left = Build();
    T->right = Build();
    return T;
}

typedef struct {
    BTree data[100];
    int data1[100];
    int top;
} st;

void Relationship(BTree T, int x, int y) {
    st *st1 = (st*) malloc(sizeof(st));
    st *st2 = (st*) malloc(sizeof(st));
    st1->top = -1;
    st2->top = -1;
    BTree p = T;
    int t, hx = 0, hy = 0;
    while (st1->top != -1 || p) {
        while (p) {
            st1->data[++st1->top] = p;
            st2->data1[++st2->top] = 0;
            p = p->left;
        }
        p = st1->data[st1->top--];
        t = st2->data1[st2->top--];
        if (t == 0) {
            st1->data[++st1->top] = p;
            st2->data1[++st2->top] = 1;
            p = p->right;
        } else {
            if (p->data == x) {
                hx = st1->top + 2;
            }
            if (p->data == y) {
                hy = st1->top + 2;
            }
            p = NULL;
        }
    }
    if (hx == hy) {
        printf("cousin");
        return;
    }
    printf("other relathionship");
}
int IsBrother(BTree t, int x, int y) {
    if (!t) return 0;
    if (t->left && t->right) {
        if (t->left->data == x && t->right->data == y) {
            printf("brother");
            return 1;
        }
        if (t->right->data == x && t->left->data == y) {
            printf("brother");
            return 1;
        }
    }
    return IsBrother(t->left, x, y) || IsBrother(t->right, x, y);
}



int main() {
    BTree t = Build();
    int x, y;
    scanf("%d%d", &x, &y);
    if (x == y) {
        printf("other relathionship");
        return 0;
    }
    if (!IsBrother(t, x, y)) {
        Relationship(t,x,y);
    }
}