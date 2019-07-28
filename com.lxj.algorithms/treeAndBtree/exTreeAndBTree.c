//
// Created by 李学俊 on 2019/7/12.
//
#include "../stackAndQueue/StackAndQueue.c"
//递归先序遍历
void PreOrder(BiNode *T){
    if (T != NULL){
        printf("%d\t",T->data);
        PreOrder(T->lchlid);
        PreOrder(T->rchlid);
    }
}
//非递归先序遍历
void PreOrder1(BiNode *T){
    SqStack S;InitStack(&S);
    BiNode *s = T;
    while (s || !StackEmpty(S)) {
        if (s) {
            printf("%d\t", s->data);
            Push(&S, s);
            s = s->lchlid;
        } else{
            Pop(&S, &s);
            s = s->rchlid;
        }
    }
}
//递归中序遍历
void InOrder(BiNode *T){
    if (T != NULL){
        InOrder(T->lchlid);
        printf("%d\t",T->data);
        InOrder(T->rchlid);
    }
}
//非递归中序遍历
void InOrder1(BiNode *T){
    SqStack S;InitStack(&S);
    BiNode *s = T;
    while (s || !StackEmpty(S)){
        if (s) {
            Push(&S, s);
            s = s->lchlid;
        } else {
            Pop(&S, &s);
            printf("%d\t", s->data);
            s = s->rchlid;
        }
    }
}
//递归后序遍历
void PostOrder(BiNode *T){
    if (T != NULL){
        PostOrder(T->lchlid);
        PostOrder(T->rchlid);
        printf("%d\t",T->data);
    }
}
//非递归后序遍历
void PostOrder1(BiNode *T){
    SqStack S1,S2;InitStack(&S1);InitStack(&S2);
    BiNode *p = T;int x;
    while (p != NULL || !StackEmpty(S1)) {
        while (p != NULL) {
            Push(&S1, p);
            Push1(&S2, 0);
            p = p->lchlid;
        }
        Pop(&S1, &p);
        Pop1(&S2, &x);
        if (x == 0) {
            Push(&S1, p);
            Push1(&S2, 1);
            p = p->rchlid;
        } else {
            printf("%d\t", p->data);
            p = NULL;
        }
    }
}
//层次遍历
void LevelOrder(BiNode *T){
    BiNode *x;Queue *Q = InitQueue();
    EnQueue(Q,T);
    while (!IsEmpty(Q)){
        DeQueue(Q, &x);
        printf("%d\t", x->data);
        if (x->lchlid != NULL){
            EnQueue(Q, x->lchlid);
        }
        if (x->rchlid != NULL) {
            EnQueue(Q, x->rchlid);
        }
    }
}

//递归求二叉树的深度
int Depth(BTree T){
    int ldepth,rdepth;
    if (T == NULL) {
        return 0;
    } else {
        ldepth = Depth(T->lchlid);
        rdepth = Depth(T->rchlid);
        if (ldepth > rdepth) {
            return ldepth+1;
        } else {
            return rdepth+1;
        }
    }
}
//非递归求二叉树深度
int Depth1(BTree T){
    BTree p = T;int curDepth, maxDepth = 0;
    SqStack S1,S2;InitStack(&S1);InitStack(&S2);
    if (T != NULL) {
        curDepth = 1;
        while (p || !StackEmpty(S1)) {
            while (p) {
                Push(&S1, p);
                Push1(&S2, curDepth);
                curDepth++;
                p = p->lchlid;
            }
            Pop(&S1, &p);
            Pop1(&S2, &curDepth);
            if (p->lchlid == NULL && p->rchlid == NULL) {
                if (curDepth > maxDepth) {
                    maxDepth = curDepth;
                }
            }
            p = p->rchlid;
            curDepth++;
        }
    }
    return maxDepth;
}
//求节点所在层次
int LayderNode(BTree T, int x){
    SqStack S1, S2;InitStack(&S1);InitStack(&S2);
    BTree p = T;int t;
    while (p || !StackEmpty(S1)) {
        while (p) {
            Push(&S1, p);
            Push1(&S2, 0);
            p = p->lchlid;
        }
        Pop(&S1, &p);
        Pop1(&S2, &t);
        if (t == 0) {
            Push(&S1, p);
            Push1(&S2, 1);
            p = p ->rchlid;
        } else{
            if (p->data == x) {
                return S1.top+2;
            }
            p = NULL;
        }
    }
    return -1;
}
//交换二叉树中所有节点的左右子树位置
void ExchangeBT(BTree T){ //层序遍历实现
    Queue *Q = InitQueue();
    BTree p = T,t;
    EnQueue(Q,p);
    if (T == NULL)
        return;
    while (!IsEmpty(Q)) {
        DeQueue(Q, &p);
        if (p->lchlid) {
            EnQueue(Q,p->lchlid);
        }
        if (p->rchlid) {
            EnQueue(Q,p->rchlid);
        }
        t = p->lchlid;
        p->lchlid = p->rchlid;
        p->rchlid = t;
    }
}
//删除二叉树中以某个节点为根节点的子树
void DeleteSubTree(BTree T, int x){
    BTree p = T, t = NULL;
    SqStack S;InitStack(&S);
    if (T->data == x)
        DestoryBT(T);
    while (p || !StackEmpty(S)) {
        while (p) {
            if (p->data == x) {
                if (t->lchlid == p) { //将删除子树父节点指向空
                    t->lchlid = NULL;
                } else {
                    t->rchlid = NULL;
                }
                DestoryBT(p);
                return;
            }
            Push(&S, p);
            t = p;
            p = p->lchlid;
        }
        Pop(&S, &t);
        p = t->rchlid;
    }
}

//3.编写后序遍历非递归算法
void Postorder(BTree T){
    SqStack S1,S2;InitStack(&S1);InitStack(&S2);
    BTree p = T;int x;
    while (p || !StackEmpty(S1)) {
        while (p) {
            Push(&S1, p);
            Push1(&S2, 0);
            p = p->lchlid;
        }
        Pop(&S1, &p);
        Pop1(&S2, &x);
        if (x == 0) {
            Push(&S1, p);
            Push1(&S2, 1);
            p = p->rchlid;
        } else {
            printf("%d\t", p->data);
            p = NULL;
        }
    }
}

//4.试给出二叉树从下至上，从右至左的遍历算法
void InvertOrder(BTree T){
    SqStack S;InitStack(&S);
    Queue *Q1 = InitQueue();
    BTree p = T,t;
    Push(&S,p);EnQueue(Q1, p);
    while (!IsEmpty(Q1)) {
        DeQueue(Q1, &p);
        if (p->lchlid) {
            Push(&S, p->lchlid);
            EnQueue(Q1, p->lchlid);
        }
        if (p->rchlid) {
            Push(&S, p->rchlid);
            EnQueue(Q1, p->rchlid);
        }
    }
    while (!StackEmpty(S)) {
        Pop(&S, &t);
        printf("%d\t", t->data);
    }
}
//5.设计一个非递归算法求二叉树的高度
int GetHigh(BTree T){
    int maxlength = 0, curlength = 0,x;
    SqStack S1,S2;InitStack(&S1);InitStack(&S2);
    BTree p = T;
    while (!StackEmpty(S1) || p) {
        while (p) {
            Push(&S1, p);
            Push1(&S2, 0);
            p = p->lchlid;
        }
        Pop(&S1, &p);
        Pop1(&S2, &x);
        if (x == 0) {
            Push(&S1, p);
            Push1(&S2, 1);
            p = p->rchlid;
        } else {
            if (p->lchlid==NULL && p->rchlid == NULL) {
                curlength = S1.top+2;
            }
            if (curlength > maxlength) {
                maxlength = curlength;
            }
            p = NULL;
        }
    }
    return maxlength;
}

//6.设一颗二叉树中各节点中的值互不相同，其先序遍历序列和中序遍历序列
//  分别存于两个一维数组A[1...n]和B[1...n]中，试建立该二叉树的二叉链表
BTree PreInCreate(int A[], int B[], int loa, int hia, int lob,int hib){
    BTree T = (BTree)malloc(sizeof(BTree));
    T->data = A[loa];
    int i;
    for (i = lob; B[i] != T->data ; ++i);
    int llen = i-lob, rlen = hib-i;
    if (llen) {
        T->lchlid = PreInCreate(A, B, loa+1, loa+llen, lob, lob+llen-1);
    } else {
        T->lchlid = NULL;
    }
    if (rlen) {
        T->rchlid = PreInCreate(A, B, hia-rlen+1, hia, hib-rlen+1, hib);
    } else {
        T->rchlid = NULL;
    }
    return T;
}
//7.写一个判别给定二叉树是否是完全二叉树
int isCompleteBinaryBtree(BTree T){
    Queue *Q = InitQueue();
    BTree p = T;
    EnQueue(Q, p);
    while (!IsEmpty(Q)) {
        DeQueue(Q, &p);
        if (p) {
            EnQueue(Q, p->lchlid);
            EnQueue(Q, p->rchlid);
        } else {
            while (!IsEmpty(Q)) {
                DeQueue(Q, &p);
                if (p) return 0;
            }
        }
    }
    return 1;
};
//8.计算一棵二叉树所有双分支节点个数
int CountDNode(BTree T){
    if (T == NULL) {
        return 0;
    }
    if (T->lchlid && T->rchlid) {   //双分支情况
        return CountDNode(T->lchlid) + CountDNode(T->rchlid) +1;
    } else {    //度为1或0的情况
        return CountDNode(T->lchlid) + CountDNode(T->rchlid);
    }
}

//9.将树的所有左右节点进行互换
void ExchangeNode(BTree T){//前序遍历实现
    if (T == NULL) {
        return;
    }
    BTree p;
    p = T->lchlid;
    T->lchlid = T->rchlid;
    T->rchlid = p;
    ExchangeBT(T->lchlid);
    ExchangeBT(T->rchlid);
}
//10.求二叉树先序遍历中第k个节点的值
int GetValueFromPreOrder(BTree T, int k){

}

//11.对于二叉树中每个元素值为x的节点，删去以它为根的子树，并释放相应的空间
void DeleteCt(BTree T, int x){
    BTree p = T;
    if (p->data == x) {
        DestoryBT(p);
        return;
    }
    SqStack S;InitStack(&S);
    while (!StackEmpty(S) || p) {
        while (p) {
            if (p->lchlid->data == x) {
                DestoryBT(p->lchlid);
                p->lchlid = NULL;
            }
            if (p->rchlid->data == x) {
                DestoryBT(p->rchlid);
                p->rchlid = NULL;
            }
            Push(&S,p);
            p = p->lchlid;
        }
        Pop(&S, &p);
        p = p->rchlid;
    }
}

//12.在二叉树中查找值为x的节点，打印值为x的节点的所有祖先，
//假设值为x的节点不多于一个
void FindAndPtX(BTree T, int x){

}
//13.找到p、q最近公共祖先节点r
void Ancestor(BTree T, BTree r, BTree p, BTree q){

}

//14.求非空二叉树的宽度
int GetBTWidth(BTree T){
    int llen = 0, rlen = 0,curllen = 0, currlen = 0;
    SqStack S; InitStack(&S);
    BTree p = T;
    while (p || !StackEmpty(S)) {
        while (p) {
            if (llen < curllen) {
                llen = curllen;
            }
            if (rlen < currlen) {
                rlen = curllen;
            }
            Push(&S, p);
            p = p ->lchlid;
            curllen++;
            currlen--;
        }
        Pop(&S, &p);
        p = p->rchlid;
        curllen--;
        currlen++;
    }
    return llen + rlen + 1;
}
int main(){
    int a[]={1,2,4,5,3,6,7};
    int b[]={4,2,5,1,6,3,7};
//    BTree T = CreateBT(a, 8, 1);
    BTree T = PreInCreate(a,b,0,6,0,6);
    LevelOrder(T);
//    int d = GetBTWidth(T);
    printf("\n" );
    PreOrder(T);
//    printf("%d",d);
//    ExchangeBT(T);
//    LevelOrder(T);

}
