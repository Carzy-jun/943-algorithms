//
// Created by 李学俊 on 2019/11/3.
//
/*
 * 约瑟夫环
 * N个人坐成一个圆环（编号为1 - N），从第1个人开始报数，数到K的人出列，
 * 后面的人重新从1开始报数。问最后剩下的人的编号。
 * 例如：N = 3，K = 2。2号先出列，然后是1号，最后剩下的是3号。
 */
//typedef struct node{
//    int data;
//    struct node *next;
//}CLinkList,CNode;
//
//CLinkList Create(CLinkList *L, int n){
//    L = (CLinkList*)malloc(sizeof(CNode));
//    L->data = 1;
//    CNode *p = L,*s;
//    for (int i = 2; i < n+1 ; ++i) {
//        s = (CLinkList*)malloc(sizeof(CNode));
//        s->data = i;
//        p->next = s;
//        p = s;
//    }
//    p->next = L;
//    return *L;
//}
//
//int fun(CLinkList *L, int k){
//    if (L->next == L) {
//        return L->data;
//    }
//    for (int i = 0; i < k - 2; ++i) {
//        L=L->next;
//    }
//    CNode *p,t;
//    p = L->next;
//    L->next = L->next->next;
//    L = L->next;
//    t = *L;
//    free(p);
//    return fun(&t,k);
//}
//int main(){
//    int n,k;
//    scanf("%d%d",&n,&k);
//    CLinkList L = Create(&L,n);
//    printf("%d\t", fun(&L, k));
//    return 0;
//}


int main() {
    int n, k,s = 0;
    scanf("%d%d", &n, &k);
    for (int i = 2; i <= n; ++i) {
        s = (s + k) % i;
    }
    printf("%d", s+1);
    return 0;
}