//
// Created by 李学俊 on 2019/10/25.
//
#include <stddef.h>

/*
 * 反转长度为N的单链表从位置 L 到 R 的子段。请在常数空间复杂度下使用一趟扫描完成反转
 */
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,*LinkList;

LinkList CreateList(LinkList L,int N){
    int a;
    L = (LinkList)malloc(sizeof(LNode));
    LNode *s,*r = L;
    for (int i = 0; i < N; ++i) {
        scanf("%d",&a);
        s = (LinkList)malloc(sizeof(LNode));
        s->data = a;
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}
void Reverse(LinkList list, int N, int L, int R){
    LNode *l=list,*r=list;
    for (int i = 1; i < L; ++i) {
        l = l->next;
    }
    for (int j = 0; j < R+1; ++j) {
        r = r->next;
    }
    LNode *p = l->next,*s=p;
    for (int k = 0; k < R - L+1; ++k) {
        s = s->next;
        p->next = r;
        r = p;
        l->next = p;
        p = s;
    }
}
void PrintLinkList(LinkList L){
    LinkList s;
    s = L->next;
    while (s != NULL){
        printf("%d\t",s->data);
        s = s->next;
    }
    printf("\n");
}
int main(){
    int N,L,R;
    scanf("%d%d%d",&N,&L,&R);
    LinkList l = NULL;
    l = CreateList(l,N);
    Reverse(l,N,L,R);
    PrintLinkList(l);
    return 0;
}