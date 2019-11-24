#include <stddef.h>

//
// Created by 李学俊 on 2019/11/3.
//
//PIPI现有a-z 26个小球模拟出入栈操作，小球按照a~z的顺序压入栈，
// 在栈顶的元素可以随时被取出，在游戏开始前给出任意26个字母的一些排列，问是否能够由出栈顺序得到这个排列。
typedef struct {
    char data[26];
    int top;
}st;
int main(){
    char s[26];
    st *S = (st*)malloc(sizeof(st));
    gets(s);
    int flag = 0;
    for (int i = 0; i < 26; ++i) {
        S->top = -1;
        for (int j = i+1; j < 26; ++j) {
            if (s[j] < s[i]) {
                S->data[++S->top] = s[j];
            }
        }
        int len = S->top+1;
        for (int j = 0; j < len - 1; ++j) {
            if (S->data[j] < S->data[j + 1]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }
    }
    if (flag == 1) {
        printf("no\n");
    } else {
        printf("yes\n");
    }
    return 0;
}