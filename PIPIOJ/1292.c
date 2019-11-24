//
// Created by 李学俊 on 2019/11/8.
//
//PIPI现在有若干个包含小写英文字母作为操作数 以及 '+', '-', '*', '/', '^' ,'(',')'
// 七种操作符的合法中缀表达式。请你将其转为后缀表达式(逆波兰式)。
typedef struct {
    char data[100];
    int top;
} st;

void change(char *exp, char postexp[]) {
    int i = 0;
    char e;
    st *S = (st *) malloc(sizeof(st));
    S->top = -1;
    while (*exp != '\0') {
        switch (*exp) {
            case '(':
                S->data[++S->top] = *exp;
                exp++;
                break;
            case ')':
                e = S->data[S->top--];
                while (e != '(') {
                    postexp[i++] = e;
                    e = S->data[S->top--];
                }
                exp++;
                break;
            case '+':
            case '-':
                while (S->top != -1) {
                    e = S->data[S->top];
                    if (e != '(') {
                        e = S->data[S->top--];
                        postexp[i++]=e;
                    } else break;
                }
                S->data[++S->top] = *exp;
                exp++;
                break;
            case '*':
            case '/':
                while (S->top != -1) {
                    e = S->data[S->top];
                    if (e == '*' || e == '/') {
                        postexp[i++] = e;
                        e = S->data[S->top--];
                    } else {
                        break;
                    }
                }
                S->data[++S->top] = *exp;
                exp++;
                break;
            case '^':
                while (S->top != -1) {
                    e = S->data[S->top];
                    if (e == '^') {
                        postexp[i++] = e;
                        e = S->data[S->top--];
                    } else {
                        break;
                    }
                }
                S->data[++S->top] = *exp;
                exp++;
                break;
            default:
                postexp[i++] = *exp;
                exp++;
        }
    }
    while (S->top != -1) {
        e = S->data[S->top--];
        postexp[i++] = e;
    }
    postexp[i] = '\0';
}

int main() {
    char s[100], post[100];
    gets(s);
    change(s, post);
    puts(post);
    return 0;
}