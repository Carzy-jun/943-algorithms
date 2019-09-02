//
// Created by 李学俊 on 2019/8/18.
//
#include <stddef.h>

#define MAX_TREE_SIZE 100

//双亲表示法
typedef struct { //树的节点定义
    int data;
    int parent;// 双亲位置域
}PTNode;
typedef struct {
    PTNode nodes[MAX_TREE_SIZE];
    int n; //节点树
}PTTree;


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

//
