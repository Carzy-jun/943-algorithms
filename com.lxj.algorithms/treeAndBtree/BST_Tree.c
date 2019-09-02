//
// Created by 李学俊 on 2019/8/14.
//
#include "../treeAndBtree/exTreeAndBTree.c"

//二叉排序树插入节点
BTree BSF_Insert(BTree root,int k) {
    if(root == NULL) {
        root = (BTree)malloc(sizeof(BiNode));
        root->data = k;
        root->lchlid = NULL;
        root->rchlid = NULL;
        return root;
    }
    if(k < root->data)
        root->lchlid = BSF_Insert(root->lchlid,k);
    else if(k > root->data)
        root->rchlid = BSF_Insert(root->rchlid,k);
    else
        printf("已在树中，不能再次插入!!");
    return root;
}
//二叉排序树的构造
BTree Create_BSF(BTree T, int str[], int n){
    T = NULL;
    for (int i = 0; i < n; ++i) {
        T = BSF_Insert(T,str[i]);
    }
    return T;
}

//二叉排序树查找算法
BTree BST_Search(BTree T , int key){//非递归
    while (T && key != T->data) {
        if (key < T->data) {
            T = T->lchlid;
        } else {
            T = T->rchlid;
        }
    }
    return T;
}
//递归
BTree BST_Search1(BTree T, int key){
    if (T->data == key) {
        return T;
    }
    else if (key < T->data) {
        return BST_Search1(T->lchlid,key);
    } else {
        return BST_Search1(T->rchlid, key);
    }
}
//查找以T为根节点最小值节点
BTree FindMin(BTree T){
    if (T == NULL) {
        return T;
    }
    if (T->lchlid) {
        T = FindMin(T->lchlid);
    }
    return T;
}
//查找以T为根节点中最大值节点
BTree FindMax(BTree T){
    if (T == NULL) {
        return T;
    }
    if (T->rchlid) {
        T = FindMax(T->rchlid);
    }
    return T;
}
BTree DeleteMinBST(BTree T){
    if (T->lchlid == NULL) {
        return T->rchlid;
    }
    T->lchlid = DeleteMinBST(T->lchlid);
    return T;
}
//删除二叉排序树中的一个节点
BTree DeleteBSTNode(BTree T, int key){
    if (T == NULL) return NULL;
    if (key < T->data) T->lchlid = DeleteBSTNode(T->lchlid,key);
    else if (key > T->data) T->rchlid = DeleteBSTNode(T->rchlid,key);
    else {
        if (T->rchlid == NULL) return T->lchlid;
        if (T->lchlid == NULL) return T->rchlid;
        BTree t = T;
        T = FindMin(t->rchlid);
        T->rchlid = DeleteMinBST(t->rchlid);
        T->lchlid = t->lchlid;
    }
    return T;
}


void Delete(BTree *T) {
    /* 从二叉排序树中删除节点p， 并重接它的左或右子树 */
    BTree q, s;
    if( !(*T)->lchlid && !(*T)->rchlid )	/* p为叶子节点 */
        *T = NULL;
    else if( !(*T)->lchlid ) { /* 左子树为空，重接右子树 */
        q = *T;
        *T = (*T)->rchlid;
        free(q);
    } else if( !(*T)->rchlid ) {/* 右子树为空，重接左子树 */
        q = *T;
        *T = (*T)->lchlid;		/* 不太理解 */
        free(q);
    } else {              /* 左右子树均不为空 */
        q = *T;
        s = (*T)->lchlid;
        while(s->rchlid) {/* 转左，然后向右走到尽头*/
            q = s;
            s = s->rchlid;
        }
        (*T)->data = s->data;
        if( q != *T )				/* 判断是否执行上述while循环 */
            q->rchlid = s->lchlid;	/* 执行上述while循环，重接右子树 */
        else
            q->lchlid = s->lchlid;	/* 未执行上述while循环，重接左子树 */
        free(s);
    }
}

void DeleteBST(BTree *T, int key)
{
    /* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素节点 */
    if( !(*T)) return;	/* 不存在关键字等于key的数据元素 */
    if( key == (*T)->data )
        Delete(T);
    else if( key < (*T)->data)
        return DeleteBST(&(*T)->lchlid, key);
    else
        return DeleteBST(&(*T)->rchlid, key);
}

//判断给定二叉树是否为二叉排序树
bool IsBSTTree(BTree T){
    SqStack S;InitStack(&S);
    BTree p = T;
    int temp = -32768;
    while (!StackEmpty(S) || p){
        while (p) {
            Push(&S,p);
            p = p->lchlid;
        }
        Pop(&S,&p);
        if (p->data < temp) {
            return false;
        }
        temp = p->data;
        p = p->rchlid;
    }
    return true;
}
//求指定节点在二叉排序树中的层次
int GetLengthBSTNode(BTree T, int x){
    int length = 0;
    BTree p = T;
    while (p) {
        length++;
        if (p->data == x) {
            break;
        }else if (p->data < x) {
            p = p->rchlid;
        } else if (p->data > x){
            p = p->lchlid;
        }
    }
    return length;
}

//判断一棵二叉树是否是平衡二叉树
bool IsAVLTree(BTree T){}

//求出给定二叉排序树中最小，和最大关键字
int GetBSTMin(BTree T){
    while (T->lchlid) {
        T = T->lchlid;
    }
    return T->data;
}

//从大到小输出二叉排序树中所有值不小于k的关键字
void PrintValueMoreThanK(BTree T, int k){
    SqStack s;InitStack(&s);
    BTree  p = T;
    while (!StackEmpty(s) || p) {
        while (p) {
            Push(&s,p);
            p = p->rchlid;
        }
        Pop(&s, &p);
        if (p->data >= k) {
            printf("%d\t", p->data);
        }
        p = p->lchlid;
    }
}
int main(){
    BTree T;
    int str[7] = {4,2,6,1,3,5,7};
    T = Create_BSF(T,str,7);
//    int a[] = {0,4,2,6,1,3,5,7};
//    T = CreateBT(a,7,1);
    InOrder(T);
    printf("\n");
    T = DeleteMinBST(T);
    printf("%d\t", T->data);

//    InOrder(T);
}