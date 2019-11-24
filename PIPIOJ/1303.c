//
// Created by 李学俊 on 2019/11/19.
//

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

int IsSame(BTree t1,BTree t2){
    if (t1 && t2 && t1->data != t2->data) {
        return 0;
    }
    if (t1 && t2) {
        return IsSame(t1->left,t2->left) && IsSame(t1->right,t2->right);
    }
    if (t1 || t2) {
        return 0;
    }
    return 1;
}

int IsSubTree(BTree t1, BTree t2){
    if (!t1) {
        return 0;
    }
    if (t1->data == t2->data) {
        if (IsSame(t1, t2)) {
            return 1;
        }
    }
    return IsSubTree(t1->left,t2) || IsSubTree(t1->right,t2);
}

int main(){
    BTree t1 = Build();
    BTree t2 = Build();
    if (IsSubTree(t1, t2)) {
        printf("yes");
    } else {
        printf("no");
    }
}