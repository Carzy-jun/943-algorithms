//
// Created by 李学俊 on 2019/7/7.
//

//共享栈
#include <stdbool.h>

#define MaxSize 100
typedef struct {
    int data[MaxSize];
    int top[2];
} CqStack;
void InitCqStack(CqStack *S){
    S->top[0] = -1;
    S->top[1] = MaxSize;
}
bool IsEmpty(CqStack S){
    return S.top[0] == -1 && S.top[1] == MaxSize;
}
void Push(CqStack *S, int x, int top){
    if (S->top[0]+1 != S->top[1]){
        if (top == 0){
            S->data[++S->top[0]] = x;
        } else{
            S->data[--S->top[1]] = x;
        }
    } else
        printf("栈满,入栈失败！");
}
void Pop(CqStack *S, int *x, int top){
    if (top == 0){
        if (S->top[0] != -1){
            *x = S->data[S->top[0]--];
        }
    } else {
        if (S->top[1] != MaxSize){
            *x = S->data[S->top[1]++];
        }
    }
}
int main (){
    CqStack S; int x;
    InitCqStack(&S);
    for (int i = 0; i < 10; ++i) {
        Push(&S, i, 0);
        Push(&S, i, 1);
    }
    for (int j = 0; j < 10; ++j) {
        Pop(&S, &x, 0);
        printf("%d\t", x);
    }
    printf("\n");
    for (int k = 0; k < 10; ++k) {
        Pop(&S, &x, 1);
        printf("%d\t", x);
    }

}
