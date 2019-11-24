//
// Created by 李学俊 on 2019/11/19.
//
//多项式加法

#include <stddef.h>

typedef struct LNode{
    int a;
    int e;
    struct LNode *next;
}LNode,LinkList;
LinkList List_TailInsert(LinkList *L, int a[], int len){
    L = (LinkList*)malloc(sizeof(LinkList));
    LNode *s, *r = L;
    for (int i = 0; i < len; i+=2) {
        s = (LNode*)malloc(sizeof(LNode));
        s->e = a[i];
        s->a = a[i+1];
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return *L;
}
void InsertSort(LNode *L){
    LNode *p, *s = L->next,*r = s->next;
    s->next = NULL;
    s = r;
    while (r != NULL){
        r = s->next;
        p = L;
        while (p->next != NULL && p->next->e < s->e){
            p = p->next;
        }
        s->next = p->next;
        p->next = s;
        s = r;
    }
}
void Plus(LNode *La, LNode *Lb){
    LNode *pa=La,*t;
    while (pa->next) {
        pa = pa->next;
    }
    pa->next = Lb->next;
    InsertSort(La);
    pa = La->next;
    while (pa->next) {
        if (pa->e == pa->next->e) {
            t = pa->next;
            pa->a+=t->a;
            pa->next = t->next;
            free(t);
        } else {
            pa = pa->next;
        }
    }
    pa = La;
    while (pa->next) {
        if (pa->next->a == 0) {
            t = pa->next;
            pa->next = t->next;
            free(t);
        } else {
            pa = pa->next;
        }
    }
}
void Print(LNode L){
    LinkList *s;
    s = L.next;
    while (s != NULL){
        printf("%d\t%d\n",s->e,s->a);
        s = s->next;
    }
}
int main(){
    LNode La,Lb;
    int n,m;
    scanf("%d%d",&n,&m);
    int a[2*n];
    for (int i = 0; i < 2 * n; ++i) {
        scanf("%d",&a[i]);
    }
    int b[2*m];
    for (int i = 0; i < 2 * m; ++i) {
        scanf("%d",&b[i]);
    }
    La = List_TailInsert(&La,a,2*n);
    Lb = List_TailInsert(&Lb,b,2*m);
    Plus(&La,&Lb);
    Print(La);
}