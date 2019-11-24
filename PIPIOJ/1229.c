//
// Created by 李学俊 on 2019/10/19.
//
#include <stddef.h>
#include <stdbool.h>
#define size  50
/*
 * 括号匹配
 */
typedef struct {
    char data[size];
    int top;
}Stack;
bool check(char *s){
    Stack *S = (Stack*)malloc(sizeof(Stack)); S->top = -1;
    char t;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i]=='('||s[i]=='['||s[i]=='{') {
            S->data[++S->top] = s[i];
        } else{
            if (S->top == -1)return false;
            t = S->data[S->top--];
            if (s[i]-1!=t && s[i]-2!=t)return false;
        }
    }
    return S->top == -1;
}
int main(){
    char s[size];
    gets(s);
    if (check(s))
        printf("yes");
    else
        printf("no");
    return 0;
}