//
// Created by 李学俊 on 2019/7/3.
//

#include "../list/linklist.c"
#include "../stackAndQueue/Queue.c"
#include <stdbool.h>

#define MaxSize 100
#define Type BTree

//顺序栈存储结构定义
typedef struct s{
    Type data[MaxSize];
    int data1[MaxSize];
    int top,top1;
}SqStack;

//初始化
void InitStack(SqStack *S){
    S->top = -1;
    S->top1 = -1;
}
//判断栈空
bool StackEmpty(SqStack S){
    return S.top == -1;
}
bool StackEmpty1(SqStack S){
    return S.top1 == -1;
}
//进栈
void Push(SqStack *S, Type x){
    if (S->top != MaxSize-1)
        S->data[++S->top] = x;
    else
        printf("\n栈满，进栈失败!");
}
void Push1(SqStack *S, int x){
    if (S->top1 != MaxSize-1)
        S->data1[++S->top1] = x;
    else
        printf("\n栈满，进栈失败!");
}
//出栈
void Pop(SqStack *S, Type *x){
    if (S->top != -1)
        *x = S->data[S->top--];
}
void Pop1(SqStack *S, int *x){
    if (S->top1 != -1)
        *x = S->data1[S->top1--];
}
//读栈顶元素
void GetTop(SqStack S, Type x){
    if (S.top != -1)
        x = S.data[S.top];
}
//队列存储结构定义
typedef struct q{
    Type data[MaxSize];
    int front, rear;
}SqQueue;

//队列初始化
void InitQueue1(SqQueue *Q){
    Q->rear = Q->front = 0;
}
//判队空
bool isEmpty1(SqQueue Q){
    return Q.rear == Q.front;
}
//入队
void EnQueue1(SqQueue *Q, Type x){
    if ((Q->rear+1)%MaxSize!=Q->front){
        Q->data[Q->rear] = x;
        Q->rear = (Q->rear+1)%MaxSize;
    } else
        printf("队满，入队失败！\n");
}
//出队
void DeQueue1(SqQueue *Q, Type *x){
    if (Q->rear != Q->front){
        *x =  Q->data[Q->front];
        Q->front = (Q->front+1)%MaxSize;
    } else
        printf("队为空，出队失败\n");
}

////1.判断单链表L中元素是否中心对称
//int IsCentrosymmetry(LinkList *L){
//    SqStack S; int x; LNode *s = L;
//    InitStack(&S);
//    while (s->next){
//        Push(&S, s->next->data);
//        s = s->next;
//    }
//    s = L;
//    while (s->next){
//        Pop(&S, &x);
//        if (s->next->data != x){
//            return 0;
//        }
//        s = s->next;
//    }
//    return 1;
//}
////Q是一个队列，S是一个空栈，实现将队列中元素逆置的算法
//void reverseQueue(SqStack S, SqQueue Q){
//    int x;
//    while (!isEmpty(Q)){
//        DeQueue(&Q,&x);
//        Push(&S, x);
//    }
//    while (!StackEmpty(S)){
//        Pop(&S, &x);
//        printf("%d\t",x);
//    }
//}
//
////判断表达式中括号是否配对
//int BracksCheck(char *string){
//    SqStack S;InitStack(&S);char x,t;
//    for (int i = 0; string[i] != '\0' ; ++i) {
//        switch (string[i]){
//            case '(':
//            case '[':
//            case '{': Push(&S, string[i]);break;
//            case ')':{
//                if (StackEmpty(S))return 0;
//                Pop(&S, &x);
//                if (x != '(')return 0;
//                break;
//            }
//            case ']':{
//                if (StackEmpty(S))return 0;
//                Pop(&S, &x);
//                if (x != '[')return 0;
//                break;
//            }
//            case '}':{
//                if (StackEmpty(S))return 0;
//                Pop(&S, &x);
//                if (x != '{')return 0;
//                break;
//        }
//            default:return 0;
//        }
//    }
//    return 1;
//}
//
////用栈实现以下递归函数的非递归计算
////
////          {1,          n = 0;
////Pn(x) =   {2x,         n = 1;
////          {2xPn-1(x)-2(n-1)Pn-2(x), n>1
//double P(int n, double x){
//    if (n == 0)return 1;
//    if (n == 1)return 2*x;
//    if (n > 1) return 2*x*P(n-1,x)-2*(n-1)*P(n-2,x);
//}
//
//double p(int n, int x){
//    struct stack{
//        int no;
//        double val;
//    }st[MaxSize];
//    int top = -1,i;
//    double fv1 = 1, fv2 = 2*x;
//    for (i = n; i>=2 ; i--) {
//        top++;
//        st[top].no = i;
//    }
//    while (top >= 0){
//        st[top].val = 2*x*fv2-2*(st[top].no-1)*fv1;
//        fv1 = fv2;
//        fv2 = st[top].val;
//        top--;
//    }
//    if (n==0){
//        return fv1;
//    }
//    return fv2;
//}
//void main(){
//    int a[] = {1,2,3,4,5},x;
//    char b[] = "{{}[{}]({[})}";
//    double P1 = P(3,2);
//    double p2 = p(3,2);
//    printf("%lf\t%lf",P1,p2);
//};