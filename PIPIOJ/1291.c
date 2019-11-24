//
// Created by 李学俊 on 2019/11/8.
//
//现在有若干个包含小写英文字母作为操作数 以及 '+', '-', '*', '/', '^'
// 五种操作符的合法中缀表达式。请你将其转为后缀表达式(逆波兰式)。

typedef struct {
    char data[100];
    int top;
} st;

//返回当前运算符优先级
int GetPrior(char c){
    if (c == '+' || c == '-') {
        return 1;
    }else if (c == '*' || c == '/') {
        return 2;
    } else {
        return 3;
    }
}
//判断是否为运算符
int IsOp(char c){
    if (c >= 'a' && c <= 'z') {
        return 0;
    }
    return 1;
}
void Trans(char *exp, char postexp[]){
    char e;
    int j = 0;
    st *S = (st *) malloc(sizeof(st));
    S->top = -1;
    for (int i = 0; exp[i]!='\0'; ++i) {
        char now = exp[i];
        if (IsOp(now)) {
            int prior = GetPrior(now);
            while (S->top!=-1) {
                e = S->data[S->top];
                if (prior <= GetPrior(e)) {
                    postexp[j++] = e;
                    S->top--;
                } else {
                    break;
                }
            }
            S->data[++S->top] = now;
        } else {
            postexp[j++] = now;
        }
    }
    while (S->top != -1) {
        postexp[j++] = S->data[S->top--];
    }
    postexp[j] = '\0';
}
//void change(char *exp, char postexp[]) {
//    int i = 0;
//    char e;
//    st *S = (st *) malloc(sizeof(st));
//    S->top = -1;
//    while (*exp != '\0') {
//        switch (*exp) {
//            case '+':
//            case '-':
//                while (S->top != -1) {
//                    e = S->data[S->top--];
//                    postexp[i++]=e;
//                }
//                S->data[++S->top] = *exp;
//                exp++;
//                break;
//            case '*':
//            case '/':
//                while (S->top != -1) {
//                    e = S->data[S->top];
//                    if (e == '*' || e == '/') {
//                        e = S->data[S->top--];
//                        postexp[i++] = e;
//                    } else {
//                        break;
//                    }
//                }
//                S->data[++S->top] = *exp;
//                exp++;
//                break;
//            case '^':
//                while (S->top != -1) {
//                    e = S->data[S->top];
//                    if (e == '^') {
//                        postexp[i++] = e;
//                        e = S->data[S->top--];
//                    } else {
//                        break;
//                    }
//                }
//                S->data[++S->top] = *exp;
//                exp++;
//                break;
//            default:
//                postexp[i++] = *exp;
//                exp++;
//        }
//    }
//    while (S->top != -1) {
//        e = S->data[S->top--];
//        postexp[i++] = e;
//    }
//    postexp[i] = '\0';
//}

int main() {
    char s[100],post[100];
    gets(s);
    Trans(s,post);
    puts(post);
    return 0;
}