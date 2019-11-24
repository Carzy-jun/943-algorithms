//
// Created by 李学俊 on 2019/10/25.
//
/*
 * PIPI给你一个合法的括号序列，希望跟你按左括号下标递增顺序给出每对括号在序列中的下标。（下标从1开始）
 */

int main(){
    int data[100],top = -1,a[100],t;
    char s[100];
    gets(s);
    memset(a,-1, sizeof(a));
    for (int i = 0; s[i]!='\0'; ++i) {
        if (s[i] == '(') {
            data[++top] = i+1;
        } else {
            t = data[top--];
            a[t] = i+1;
        }
    }
    for (int j = 1; s[j] != '\0' ; ++j) {
        if (a[j]!=-1) {
            printf("%d\t%d\n", j,a[j]);
        }
    }

    return 0;
}