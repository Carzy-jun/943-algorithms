//
// Created by 李学俊 on 2019/8/18.
//
#include <stddef.h>

#define MAX_TREE_SIZE 100

//双亲表示法
typedef struct { //树的节点定义
    int data;
    int parent;// 双亲位置域
}PTree[MAX_TREE_SIZE];

//孩子链表示
typedef struct node{
    int data;
    struct node *sons[100]
}TSonNode;

//孩子兄弟表示法
typedef struct CSNode{
    int data;
    struct CSNode *firstchild,*nextsibling; //第一个孩子和右兄弟指针
}CSNode,*CSTree;

//1.计算森林（树）的叶子数
int leaves(CSTree T){
    if (T == NULL) {
        return 0;
    }
    if (T->firstchild == NULL) {
        return 1+leaves(T->nextsibling);
    } else {
        return leaves(T->firstchild)+leaves(T->nextsibling);
    }
}

//孩子链存储，求树高
int TreeHeight1(TSonNode *t){
    TSonNode *p;
    int h,maxh = 0;
    if (t == NULL)return 0;
    else{
        for (int i = 0; i < 100; ++i) {
            p = t->sons[i];
            if (p) {
                h = TreeHeight1(p);
                if (maxh < h)maxh = h;
            }
        }
        return maxh+1;
    }
}

//孩子兄弟存储求树高
int TreeHeight2(CSNode *t){
    CSNode *p;
    int h,maxh = 0;
    if (t == NULL) return 0;
    else{
        p = t->firstchild;
        while (p){
            h = TreeHeight2(p);
            if (maxh < h)maxh = h;
            p = p->nextsibling;
        }
        return maxh+1;
    }
}
int main(){

}
