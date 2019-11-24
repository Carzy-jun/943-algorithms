//
// Created by 李学俊 on 2019/11/19.
//

//交换二叉树的左右子树

#include <stddef.h>

typedef struct node{
    int data;
    struct node *left,*right;
}*BTree;

BTree Build(){
    BTree T = (BTree)malloc(sizeof(BTree));
    int c;
    scanf("%d",&c);
    if (c== -1) return NULL;
    T->data = c;
    T->left = Build();
    T->right = Build();
    return T;
}

void Change(BTree t){
    if (!t) {
        return;
    }
    Change(t->left);
    Change(t->right);
    BTree temp = t->left;
    t->left = t->right;
    t->right = temp;
}

void PreOrder(BTree t){
    if (!t) {
        return;
    }
    printf("%d\t",t->data);
    PreOrder(t->left);
    PreOrder(t->right);
}
int main(){
    BTree t = Build();
    Change(t);
    PreOrder(t);
    return 0;
}