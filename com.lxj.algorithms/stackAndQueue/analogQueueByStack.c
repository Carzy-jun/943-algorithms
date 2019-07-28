//
// Created by 李学俊 on 2019/7/7.
//
//双栈模拟队列
#include "./StackAndQueue.c"

bool aQueueEmpty(SqStack S1, SqStack S2){
    return StackEmpty(S1)&&StackEmpty(S2);
}
void aEnQueue(SqStack *S1, SqStack *S2, int x){
    if (S1->top != MaxSize-1){
        Push(S1, x);
        return;
    }
    if (S1->top == MaxSize-1 && !StackEmpty(*S2)) {
        printf("队满");
        return;
    }
    if (S1->top == MaxSize-1 && StackEmpty(*S2)){
        while (!StackEmpty(*S1)){
            Pop(S1, &x);
            Push(S2, x);
        }
    }
    Push(S1, x);
}
void aDeQueue(SqStack *S1, SqStack *S2, int *x){
    if (!StackEmpty(*S2)){
        Pop(S2,x);
    } else if (StackEmpty(*S1)){
        printf("队空");
    } else{
        while (!StackEmpty(*S1)){
            Pop(S1, x);
            Push(S2, *x);
        }
        Pop(S2,x);
    }
}
void main(){
    int a[] = {1,2,3,4,5},x;
    SqStack S1;SqStack S2;InitStack(&S1);InitStack(&S2);
    for (int i = 0; i < 5; ++i) {
        aEnQueue(&S1,&S2,a[i]);
    }
    for (int j = 0; j < 5; ++j) {
        aDeQueue(&S1,&S2,&x);
        printf("%d\t",x);
    }
};