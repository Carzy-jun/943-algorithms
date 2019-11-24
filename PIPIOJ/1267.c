//
// Created by 李学俊 on 2019/10/12.
//
#include <stddef.h>

/*
 * 1267.删除倒数第K个节点，然后从头到尾输出每个节点值
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

void Delete(LinkList L, int k){
    LNode *fast = L;
    LNode *slow = L;
    for (int i = 0; i <= k; ++i) {
        fast = fast->next;
    }
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    LNode *t = slow->next;
    slow->next = t->next;
    free(t);
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
    LinkList L;
    int N,k;
    scanf("%d%d",&N,&k);
    L = CreateList(L,N);
    Delete(L,k);
    PrintLinkList(L);
}