#include <stddef.h>

//
// Created by 李学俊 on 2019/11/18.
//
typedef struct LNode {
    int a;
    int e;
    struct LNode *next;
} LNode;

LNode Build(LNode *L, int a[], int len) {
    L = (LNode *) malloc(sizeof(LNode));
    LNode *s, *r = L;
    for (int i = 0; i < len; i += 2) {
        s = (LNode *) malloc(sizeof(LNode));
        s->a = a[i];
        s->e = a[i + 1];
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return *L;
}

void InsertSort(LNode *L) {
    LNode *p, *s = L->next, *r = s->next;
    s->next = NULL;
    s = r;
    while (r != NULL) {
        r = s->next;
        p = L;
        while (p->next != NULL && p->next->e > s->e) {
            p = p->next;
        }
        s->next = p->next;
        p->next = s;
        s = r;
    }
}
//int Count(LNode *La, LNode *Lb, LNode *c){
//    if (!La->next && !Lb->next) {
//        printf("0 0");
//        return 0;
//    }
//    LNode *pa, *pb, *t;
//    c->next = NULL;
//    for (pa = La->next; pa; pa = pa->next) {
//        for (pb = Lb->next; pb ; pb = pb->next) {
//            LNode *s = (LNode*)malloc(sizeof(LNode));
//            s->a = pa->a * pb->a;
//            s->e = pa->e + pb->e;
//            s->next = c->next;
//            c->next = s;
//        }
//    }
//    InsertSort(c);
//    pa = c->next;
//    while (pa->next) {
//        if (pa->e == pa->next->e) {
//            t = pa->next;
//            pa->a+=t->a;
//            pa->next = t->next;
//            free(t);
//        } else {
//            pa = pa->next;
//        }
//    }
//    return 1;
//}

int Mulpoly(LNode *La, LNode *Lb, LNode *c) {
    if (!La->next) {
        printf("0 0");
        return 0;
    }
    c->next = NULL;
    LNode *pa, *pb, *pc, *s, *t;
    for (pa = La->next; pa; pa = pa->next) {
        for (pb = Lb->next; pb; pb = pb->next) {
            s = (LNode *) malloc(sizeof(LNode));
            s->a = pa->a * pb->a;
            s->e = pa->e + pb->e;
            for (pc = c; pc; pc = pc->next) {
                if (!pc->next||pc->next->e < s->e) {
                    if (pc->e == s->e) {
                        pc->a += s->a;
                        free(s);
                        break;
                    }
                    s->next = pc->next;
                    pc->next = s;
                    break;
                }
            }
        }
    }
//    pa = c->next;
//    while (pa->next) {
//        if (pa->e == pa->next->e) {
//            t = pa->next;
//            pa->a += t->a;
//            pa->next = t->next;
//            free(t);
//        } else {
//            pa = pa->next;
//        }
//    }
    return 1;
}

void Print(LNode L) {
    LNode *s = L.next;
    while (s != NULL) {
        printf("%d\t%d\t", s->a, s->e);
        s = s->next;
    }
}

int main() {
    int n1, n2;
    scanf("%d", &n1);
    int a[2 * n1];
    for (int i = 0; i < 2 * n1; ++i) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &n2);
    int b[2 * n2];
    for (int i = 0; i < 2 * n2; ++i) {
        scanf("%d", &b[i]);
    }
    LNode La, Lb, s;
    La = Build(&La, a, 2 * n1);
    Lb = Build(&Lb, b, 2 * n2);
    if (Mulpoly(&La, &Lb, &s)) {
        Print(s);
    }
    return 0;
}