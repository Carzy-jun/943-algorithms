//
// Created by 李学俊 on 2019/6/11.
//

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
//单链表节点定义
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode,LinkList;

//双链表节点定义
typedef struct DNode{
    int data;
    struct DNode *next;
    struct DNode *prior;
}DNode,DLinkList;
//头插法
LinkList List_HeadInsert(LinkList *L, int a[], int len){
    LNode *s;
    L = (LinkList*)malloc(sizeof(LNode));
    L->next = NULL;
    for (int i = 0; i < len; ++i) {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = a[i];
        s->next = L->next;
        L->next = s;
    }
    return *L;
}
//不带头节点头插法建立链表
LinkList List_HeadInsertWithoutHead(LinkList *L, int a[], int len){
    LNode *h;
    h = (LNode*)malloc(sizeof(LNode));
    h->next = NULL;
    for (int i = 0; i < len; ++i) {
        L = (LNode*)malloc(sizeof(LNode));
        L->data = a[i];
        L->next = h->next;
        h->next = L;
    }
    return *L;
}
//尾插法
LinkList List_TailInsert(LinkList *L, int a[], int len){
    L = (LinkList*)malloc(sizeof(LinkList));
    LNode *s, *r = L;
    for (int i = 0; i < len; ++i) {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return *L;
}
//不带头节点尾插法建立链表
LinkList List_TailInsertWithoutHead(LinkList *L, int a[], int len){
    L = (LinkList*)malloc(sizeof(LinkList));
    LNode *r = L,*s;
    L->data = a[0];
    for (int i = 1; i < len; ++i) {
        s = (LinkList*)malloc(sizeof(LinkList));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return *L;
}
//尾插法建立带头节点 循环双链表
DLinkList DlistInsert(DLinkList *L, int a[], int len){
    printf("%d",1);
    L = (DLinkList*)malloc(sizeof(DLinkList));
    DNode *s, *r = L;
    for (int i = 0; i < len; ++i) {
        s = (DNode*)malloc(sizeof(DNode));
        s->data = a[i];
        s->prior = r;
        r->next = s;
        r = s;
        printf("%d",s->data);
    }
    r->next = L;
    L->prior = r;
    return *L;
}
//尾插法创建循环单链表
LinkList CreateCirularList(LinkList *L, int a[], int len){
    printf("123123");
    L = (LinkList*)malloc(sizeof(LinkList));
    LNode *s, *r = L;
    for (int i = 0; i < len; ++i) {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = L;
    return *L;
}

void PrintLinkListWithoutHead(LinkList L){
    LinkList *s;
    s = &L;
    while (s != NULL){
        printf("%d\t",s->data);
        s = s->next;
    }
}
void PrintLinkList(LinkList L){
    LinkList *s;
    s = L.next;
    while (s != NULL){
        printf("%d\t",s->data);
        s = s->next;
    }
    printf("\n");
}
void PrintDLinkList(LinkList *L){
    LinkList *s;
    s = L->next;
    while (s != L){
        printf("%d\t",s->data);
        s = s->next;
    }
}
// 1.设计一个递归算法。删除不带头节点的单链表L中所有值为x的节点

void DeleteX1(LinkList *L, int x){
    LNode *s;
    if (L->next == NULL)
        return;
    if (L->next->data == x){
        s = L->next;
        L->next = L->next->next;
        free(s);
        DeleteX1(L, x);
    } else{
        DeleteX1(L->next, x);
    }
}
void DeleteX(LinkList *L, int x){
    LNode *s;
    if (L->data == x){
        s = L;
        L = L->next;
        free(s);
        DeleteX(L,x);
    } else
        DeleteX1(L,x);
}
//2.带头节点的单链表中，删除所有值为x的节点

//递归
void DeleteXWithHead(LinkList *L, int x){
    LNode *s;
    if (L->next == NULL)
        return;
    if (L->next->data == x){
        s = L->next;
        L->next = L->next->next;
        free(s);
        DeleteX1(L, x);
    } else{
        DeleteX1(L->next, x);
    }
}
//非递归
void DeleteXWithHead1(LinkList *L, int x){
    LNode *p,*r;
    p = L;
    while (p->next != NULL){
        if (p->next->data == x){
            r = p->next;
            p->next = p->next->next;
            free(r);
        } else{
            p = p->next;
        }
    }
}
//尾插法，值为不x则插入尾节点后
void DeleteXWithHead2(LinkList *L, int x){
    LNode *s = L,*r = L,*p;
    while (s->next != NULL){
        if (s->next->data != x){
            r->next = s->next;
            s->next = s->next->next;
            r = s->next;
        } else{
            p = s->next;
            s->next = s->next->next;
            free(p);
        }
    }
    r->next = NULL;
}
//3.设L为带头节点的单链表，反向输出每个节点的值
void ReversePrint(LinkList *L){
    if (L->next != NULL){
        ReversePrint(L->next);
    }
    printf("%d\t", L->data);
}
//4.设L为带头节点的单链表，删除一个最小值节点，要求高效(假设最小节点唯一)
void DeleteMin(LinkList *L){ //时间复杂度O(n)
    LNode *p=L,*q;
    int min = L->next->data; //记第一个元素为最小元素
    while (L->next != NULL){//终止条件：若最后一个节点为空
        if (L->next->data < min){ //比较下个节点，更新最小值min
            min = L->next->data;
            p = L; // 将最小值节点的前驱节点赋给p，以便删除最小值节点
        }
        L = L->next;
    }
    //删除最小值节点
    q = p->next;
    p->next = p->next->next;
    free(q);
}

//5.将带头节点的单链表就地逆置
void ReverseList(LinkList *L){
    LNode *t,*r; //t为工作指针，r为t的后继，以防断链
    t = L->next;
    L->next = NULL;
    while (t != NULL){ //看不懂画图
        r = t->next;
        t->next = L->next;
        L->next = t;
        t = r;
    }
}

//6.将带头节点链表L递增有序
//冒泡法
void BubbleSortLinkList(LinkList *L){
    LNode *s = L->next,*f = s;
    int temp;
    while (f->next != NULL){
        s = L->next;
        while (s->next != NULL){
            if (s->data > s->next->data){
                temp = s->next->data;
                s->next->data = s->data;
                s->data = temp;
            }
            s = s->next;
        }
        f = f->next;
    }
}
//插入排序
void InsertSortLinkList(LinkList *L){
    LNode *p, *s = L->next,*r = s->next;
    s->next = NULL;
    s = r;
    while (r != NULL){
        r = s->next;
        p = L;
        while (p->next != NULL && p->next->data < s->data){
            p = p->next;
        }
        s->next = p->next;
        p->next = s;
        s = r;
    }
}
//7.设带头节点单链表L中所有元素数据值无序，
//  删除表中所有介于给定的两个值（作为函数参数给出）之间的元素的元素（若存在）
void DeleteBetween(LinkList *L, int a, int b){
    LNode *s = L,*t;
    while (s->next != NULL){
        if (s->next->data > a && s->next->data < b){
            t = s->next;
            s->next = t->next;
            free(t);
        } else
            s = s->next;
    }
}

//8.给定两个单链表，找出两个链表的公共节点
LinkList FindMutalNode(LinkList *L1, LinkList *L2){
    int len1=0,len2=0;
    LNode *s1 = L1->next, *s2 = L2->next;
    LNode *L = NULL;
    while (s1){
        s1 = s1->next;
        len1++;
    }
    while (s2){
        s2 = s2->next;
        len2++;
    }
    s1 = L1->next, s2 = L2->next;
        for (int i = 0; i < len1 - len2; ++i) {
            s1 = s1->next;
        }
        while (s1 != NULL){
            if (s1->data != s2->data){
                s1 = s1->next;
                s2 = s2->next;
            } else{
                L1->next = s2;
                return *L1;
            }
        }
    return *L;
}
//9.给一带头节点单链表，按递增次序输出各节点中的数据元素，并释放存储空间
//（要求：不允许使用数组）
void PrintListOrder(LinkList *L){
    LNode *p, *pre, *s;
    while (L->next != NULL){ //循环到只剩头节点
        pre = L;
        s = pre->next;
        while (s->next != NULL){
            if (s->next->data < pre->next->data){
                pre = s;
            }
            s = s->next;
        }
        printf("%d\t",pre->next->data);
        p = pre->next;
        pre->next = p->next;
        free(p);
    }
}
//10.将一个带头节点单链表分解成两个带头节点单链表A和B
//A表中含有原表中序号为奇数的元素，B中有元表中序数为偶数的元素，且相对位置不变
void DecomposeLinkList(LinkList *A, LinkList *B){
    LNode *s1 = A->next, *s2 = s1->next;
    B->next = s2;
    while (s1->next){
        s1->next = s1->next->next;
        s2->next = s2->next->next;
        s1= s1->next;
        s2= s2->next;
    }
}
LinkList DecomposeLinkList2(LinkList *A){
    int i = 0;
    LinkList *B = (LinkList*)malloc(sizeof(LinkList));
    B->next = NULL;
    LNode *ra = A, *rb = B,*p;
    p = A->next;
    A->next = NULL;
    while (p != NULL){
        i++;
        if (i%2 == 0){
            rb->next = p;
            rb = p;
        } else{
            ra->next = p;
            ra = p;
        }
        p = p->next;
    }
    ra->next = NULL;
    rb->next = NULL;
    return *B;
}
//10.将一个带头节点单链表分解成两个带头节点单链表A和B
//A表中含有原表中序号为奇数的元素，B中有元表中序数为逆序的偶数的元素，且相对位置不变
LinkList DecomposeLinkList3(LinkList *A){
    int i = 0;
    LinkList *B = (LinkList*)malloc(sizeof(LinkList));
    B->next = NULL;
    LNode *ra = A, *rb = B,*p,*t;
    p = A->next;
    A->next = NULL;
    while (p != NULL){
        i++;
        if (i%2 == 0){
            t = p;
            p = p->next;
            t->next = rb->next;
            rb->next = t;
        } else{
            ra->next = p;
            ra = p;
            p = p->next;
        }
    }
    return *B;
}

//12.数据元素递增的单链表中，去掉数值相同的元素
void DeleteRepeat(LinkList *L){
    LNode *p = L->next,*r,*pre,*t;
    while (p){
        pre = p;
        r = p->next;
        while (r){
            if (p->data == r->data){
                t = r;
                r = r->next;
                pre->next = r;
                free(t);
            } else{
                pre = r;
                r = r->next;
            }
        }
        p = p->next;
    }
}
void DeleteRepeat1(LinkList *L){
    LNode *p = L->next,*t;
    while (p->next){
        if (p->data == p->next->data){
            t = p->next;
            p->next = t->next;
            free(t);
        } else{
            p = p->next;
        }
    }
}
//13.有两个元素递增的单链表，将这两个单链表归并成一个元素递减的单链表，
//   要求利用原来两个单链表的节点来存放归并后的单链表。
LinkList MergeLinklist(LinkList *A, LinkList *B){
    LNode *pa = A->next, *pb = B->next,*sa,*sb;
    A->next = NULL;
    B->next = NULL;
    while (pa && pb){
        sa = pa;
        sb = pb;
        pa = pa->next;
        pb = pb->next;
        if (sa->data < sb->data){
            sa->next = A->next;
            A->next = sa;
            sb->next = A->next;
            A->next = sb;
        } else{
            sb->next = A->next;
            A->next = sb;
            sa->next = A->next;
            A->next = sa;
        }
        while (pa){
            sa = pa;
            pa = pa->next;
            sa->next = A->next;
            A->next = sa;
        }
        while (pb){
            sb = pb;
            pb = pb->next;
            sb->next = A->next;
            A->next = sb;
        }
    }
    return *A;
}
//14.A,B为两个元素递增单链表，从A,B公共元素产生单链表C,要求不破坏A，B节点
LinkList MergeSame(LinkList *A, LinkList *B){
    LinkList *C = (LinkList*)malloc(sizeof(LinkList));
    LNode *pa = A->next, *pb = B->next,*pre = C,*s = NULL;
    while (pa && pb){
        if (pa->data < pb->data){
            pa = pa->next;
        } else if (pa->data > pb->data){
            pb = pb->next;
        } else{
            s = (LNode*)malloc(sizeof(LNode));
            s->data = pa->data;
            pre->next = s;
            pre = s;
            pa = pa->next;
            pb = pb->next;
        }
    }
    s->next = NULL;
    return *C;
}
//15.A,B为两个元素递增单链表,求A与B的交集,并存放于A链表中
LinkList MergeSame1(LinkList *A, LinkList *B){
    LNode *pa = A->next, *pb = B->next,*ra = A,*t;
    A->next = NULL;
    B->next = NULL;
    while (pa && pb){
        if (pa->data < pb->data){
            t = pa;
            pa = pa->next;
            free(t);
        } else if (pa->data > pb->data){
            t = pb;
            pb = pb->next;
            free(t);
            pb = pb->next;
        } else{
            ra->next = pa;
            ra = pa;
            pa = pa->next;
            pb = pb->next;
        }
    }
    while (pa){
        t = pa;
        pa = pa->next;
        free(t);
    }
    while (pb){
        t = pb;
        pb = pb->next;
        free(t);
    }
    ra->next = NULL;
    return *A;
}
//*//16.两个整数序列A，B已经存入单链表中，判断序列B是否是A的连续子序列
// 链式模式匹配
int IsSubsequence(LinkList A, LinkList B){
    LNode *pa = A.next, *pb = B.next,*p, *pre = pa;
    while (pa && pb){
        if (pa->data == pb->data){
            pa = pa->next;
            pb = pb->next;
        } else{
            pre = pre->next;
            pa = pre;
            pb = B.next;
        }
    }
    return pb == NULL;
}

//17.判断带头节点的循环双链表是否对称

//18.将循环单链表h2链接到循环单链表h1后，并仍保持循环链表形式
LinkList MergeCirularList(LinkList *h1, LinkList *h2){
    LNode *p1 = h1, *p2 = h2;
    while (p1->next != h1){
        p1 = p1->next;
    }
    while (p2->next != p2){
        p2 = p2->next;
    }
    p1->next = h2->next;
    p2->next = h1;
    free(h2);
    return *h1;
}
//21.查找链表中倒数第k个位置上的节点，算法尽可能高效
int Search_k(LinkList L, int k){
    LNode *p = L.next, *q = L.next;
    int count = 0;
    while (p){
        if (count < k) count++;
        else q = q->next;
        p = p->next;
    }
    if (count < k)
        return 0;
    else{
        printf("%d",q->data);
        return 1;
    }
}

//23.对于单链表中data绝对值相同的节点，仅保留第一次出现的节点而删除其余绝对值相等的节点
void DeleteSame(LinkList *L){
    int a[50];
    for (int i = 0; i < 50; ++i) {
        a[i] = 0;
    }
    LNode *p = L->next, *t = L,*q;
    while (p){ //代码还可简化
        if (p->data >= 0 && a[p->data] == 0){
            a[p->data] = 1;
            t = p;
            p = p->next;
        } else if (p->data < 0 && a[-p->data] == 0){
            a[-p->data] = 1;
            t = p;
            p = p->next;
        } else{
            q = p;
            p = p->next;
            t->next = p;
            free(q);
        }
    }
}

//void main() {
//    int a[] = {-1,1,2,-2,2,3,3,4,0,0};
//    int b[] = {6,7,8,9,1};
//    LinkList L, L2,L3;
//    L = List_TailInsert(&L, a, 10);
//    PrintLinkList(L);
//    printf("\n");
//    DeleteSame(&L);
//    PrintLinkList(L);
////    L1 = List_TailInsert(&L1, b, 5);
//}
