//
// Created by 李学俊 on 2019/7/12.
//
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include "../stackAndQueue/Queue.c"
typedef BTree ElementType;
typedef struct node* Stack;
struct node {
    ElementType data;
    Stack next;
};


//初始化
void InitStack(Stack *L) {
    (*L) = NULL;
}
//入栈
void Push(Stack *L, ElementType x) {
    Stack s;
    s = (Stack)malloc(sizeof(struct node));
    s->data = x;
    s->next = (*L); //L是栈顶元素
    (*L) = s;  //s成为新的栈顶元素
}
bool StackEmpty(Stack L){
    return L->next == NULL;
}
//出栈
void Pop(Stack *L, ElementType *x) {
    if ((*L)->next == NULL) {
        printf("空栈");
    }
    else {
        Stack p;
        *x = (*L)->data;
        p = (*L);  //标记栈顶
        (*L) = (*L)->next;
        free(p); //出栈
    }
}
void PrintNode(Stack L) {
    while (L != NULL) {
        printf("%c", L->data);
        L = L->next;
    }
    printf("\n");
}
