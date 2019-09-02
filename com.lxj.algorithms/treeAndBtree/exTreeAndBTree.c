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
        return ldepth > rdepth ? ldepth : rdepth;
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
//中序遍历和后序遍历建立二叉树
BTree InPostCreate(int in[], int post[]){

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
int p=1,ch;
int GetValueFromPreOrder(BTree T, int k){
    if (T == NULL) {
        return -1;
    }
    if (p == k) {
        return T->data;
    }
    p++;
    ch = GetValueFromPreOrder(T->lchlid,k);
    if (ch != -1) {
        return ch;
    }
    ch = GetValueFromPreOrder(T->rchlid, k);
    return ch;
}

//11.对于二叉树中每个元素值为x的节点，删去以它为根的子树，并释放相应的空间
void DeleteCt(BTree T, int x){
    BTree p;
    Queue *Q = InitQueue();
    EnQueue(Q,T);
    if (T->data == x) {
        DestoryBT(T);
        return;
    }
    while (!IsEmpty(Q)) {
        DeQueue(Q,&p);
        if (p->lchlid) {
            if (p->lchlid->data == x) {
                DestoryBT(p->lchlid);
                p->lchlid = NULL; //这一步不能少。
            } else {
                EnQueue(Q,p->lchlid);
            }
        }
        if (p->rchlid) {
            if (p->rchlid->data == x) {
                DestoryBT(p->rchlid);
                p->rchlid = NULL;
            } else {
                EnQueue(Q,p->rchlid);
            }
        }
    }
}

//12.在二叉树中查找值为x的节点，打印值为x的节点的所有祖先，
//假设值为x的节点不多于一个
void FindAndPtX(BTree T, int x){  //利用后序遍历找到x后栈中元素均为祖先
    BTree p = T;int t;
    SqStack S1,S2;InitStack(&S1);InitStack(&S2);
    while (!StackEmpty(S1) || p) {
        while (p) {
            Push(&S1, p);
            Push1(&S2, 0);
            p = p->lchlid;
        }
        Pop(&S1, &p);
        Pop1(&S2, &t);
        if (t == 0) {
            Push(&S1,p);
            Push1(&S2,1);
            p = p->rchlid;
        } else {
            if (p->data == x) {
                while (!StackEmpty(S1)) {
                    Pop(&S1,&p);
                    printf("%d\t", p->data);
                }
                return;
            }
            p = NULL;
        }
    }
}
//13.找到p、q最近公共祖先节点r
BTree Ancestor(BTree T, BTree p, BTree q){
    SqStack S1,S2,S3;InitStack(&S1);InitStack(&S2);InitStack(&S3);
    BTree s = T;int t;
    while (!StackEmpty(S1) || s) {
        while (s) {
            Push(&S1, s);
            Push1(&S2, 0);
            s = s->lchlid;
        }
        Pop(&S1, &s);
        Pop1(&S2, &t);
        if (t == 0) {
            Push(&S1, s);
            Push1(&S2, 1);
            s = s->rchlid;
        } else {
            if (s->data == p->data) {
                for (int i = 0; i <= S1.top ; i++) {
                    S3.data[i] = S1.data[i];
                }
                S3.top = S1.top;
            }
            if (s->data == q->data) {
                for (int i = S3.top; i >= 0 ; --i) {
                    for (int j = S1.top; j >= 0 ; --j) {
                        if (S1.data[j]->data == S3.data[i]->data) {
                            return S3.data[i];
                        }
                    }
                }
            }
            s = NULL;
        }
    }
    return NULL;
}

//14.求非空二叉树的宽度
//我们知道层序遍历二叉树是使用queue来实现的：每次打印一个节点之后，
// 如果存在左右子树，则把左右子树压入queue，那么此时的队列中可能既包含当前层的节点，
// 也包含下一层的节点。而我们要求的是对于特定某一层的节点的个数，
// 因此我们需要从头结点开始，记录每一层的个数，对于当前层的每一个节点，
// 在弹出自身之后把其左右子树压入queue，当把当前层全部弹出队列之后，
// 在队列中剩下的就是下一层的节点。然后比较队列的size和之前得到的maxWidth，
// 取最大值即为队列的宽度。最终队列为空，得到的maxWidth就是二叉树的宽度！
int GetBTWidth(BTree T){
    if (!T) return 0;  //数为空宽度为0
    Queue *Q = InitQueue();
    int maxWidth = 1;//最大宽度，用于当只有一个节点的时候返回1
    BTree p = T;
    EnQueue(Q, p); //头节点入队
    while (true) {
        int length = Size(Q); //当前层节点的个数
        if (length == 0) { //当层没有节点，跳出循环
            break;
        }
        while (length > 0) {//若当层还有节点，将该层所有子节点入队，知道该层节点都已出队
            DeQueue(Q,&p);
            length--;
            if (p->lchlid) {
                EnQueue(Q,p->lchlid);
            }
            if (p->rchlid) {
                EnQueue(Q,p->rchlid);
            }
        }
        maxWidth = maxWidth > Size(Q)? maxWidth: Size(Q); //比较每一层的宽度
    }
    return maxWidth;
}
//15.设有一颗满二叉树（所有节点值均不同），已知其先序序列为pre，求其后序序列post
void PreToPost(int pre[], int l1, int h1, int post[], int l2, int h2){
    int half;
    if (h1 >= l1) {
        post[h2] = pre[l1];
        half = (h1-l1)/2;
        PreToPost(pre, l1+1, l1+half, post, l2, l2+half-1);
        PreToPost(pre, l1+half+1, h1, post, l2+half, h2-1);
    }
}

//16.将二叉树的叶节点按从左到右的顺序连成一个单链表，表头指针为head.
LinkList Linkleafnode(BTree T){

}
//17.判断两颗二叉树是否相似，T1,T2都为空或都只有一个根节点，或T1，T2的左子树相似且右子树相似
bool IsSimailer(BTree T1, BTree T2){
    if (!T1 && !T2) {
        return true;
    }
    if (!T1 || !T2) {
        return false;
    }
    return IsSimailer(T1->lchlid,T2->lchlid)&&IsSimailer(T1->rchlid,T2->rchlid);
}


//int main(){
//    int a[]={0,1,2,3,4,5,0,7,8,9,10,11,12,13,14};
//    int b[]={1,2,4,5,3,6,7};
//    BTree T = CreateBT(a, 14, 1);
//    BTree T1 = CreateBT(b, 8, 1);
//    LevelOrder(T);
//    printf("\n" );
//    LevelOrder(T);
//}
