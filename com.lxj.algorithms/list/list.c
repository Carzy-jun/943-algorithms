//
// Created by 李学俊 on 2019/5/18.
//
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define Maxsize 50
typedef struct {
    int data[Maxsize];
    int length;
}SqList;
SqList CreateList(int data[], int len){
    SqList list;
    for (int i = 0; i < len; ++i) {
        list.data[i] = data[i];
    }
    list.length = len;
    return list;
}

/**
 * 将元素e插入到顺序表L中的第i个位置
 * @param L 顺序表
 * @param i 插入位置
 * @param e 插入元素
 * @return
 */
bool ListInsert(SqList *L, int i, int e){
    if (i < 1 || i > L->length+1)
        return false;
    if (L->length >= Maxsize)
        return false;
    for (int j = L->length; j >= i ; j--) {
        L->data[j] = L->data[j-1];
    }
    L->data[i-1] = e;
    L->length++;
    return true;
}
/**
 * 删除第i个位置元素，成功将删除值赋给e，并返回true
 * @param L 顺序表
 * @param i 删除位置
 * @param e 成功删除返回元素
 * @return
 */
bool ListDelete(SqList L, int i, int e){
    if (i > L.length || i < 1)
        return false;
    e = L.data[i-1];
    for (int j = i; j < L.length ; ++j) {
        L.data[j-1] = L.data[j];
    }
    L.length--;
    return true;
}
//按值查找等于e的元素的位序
int LocateElem(SqList L, int e){
    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] == e){
            return i+1;
        }
    }
    return 0;
}
void PrintList(SqList L){
    for (int i = 0; i < L.length; ++i) {
        printf("%d\t",L.data[i]);
    }
}
void PrintArray(int a[], int len){
    for (int i = 0; i < len; ++i) {
        printf("%d\t",a[i]);
    }
}
//2.1删除线性表最小元素
int DeleteMin(SqList *L){
    if (L->length == 0)
        return -1;
    int min = 0;
    for (int i = 0; i < L->length-1; ++i) {
        if (L->data[i] > L->data[i+1]){
            min = i+1;
        }
    }
    int e = L->data[min];
    L->data[min] = L->data[L->length-1];
    L->length--;
    return e;
}
//2.2反转线性表
void ReverseList(SqList *L){
    int temp;
    for (int i = 0,j = L->length-1; i < j ;) {
        temp = L->data[i];
        L->data[i] = L->data[j];
        L->data[j] = temp;
        i++;
        j--;
    }
}

//2.3 删除线性表中所有值为x的元素，时间复杂度O(n),空间复杂度O(1)
void DeleteX(SqList *L, int x){
    int k = 0;
    for (int i = 0; i < L->length; ++i) {
        if (L->data[i] == x){
            ++k;
        } else{
            L->data[i-k] = L->data[i];
        }
    }
    L->length = L->length-k;
}
//2.4删除其值在给定值s与t之间的所有元素
void DeleteValueBetween(SqList *L, int s, int t){
    if (s >= t || L == NULL){
        printf("error!");
        return;
    }
    int k = 0;
    for (int i = 0; i < L->length; ++i) {
        if (s < L->data[i] && L->data[i] < t){
            k++;
        } else{
            L->data[i-k]=L->data[i];
        }
    }
    L->length = L->length-k;
}
//2.5删除其值在给定值s与t之间的所有元素(包括s,t)
void DeleteValueContain(SqList *L, int s, int t){
    if (s >= t || L == NULL){
        printf("error!");
        return;
    }
    int k = 0;
    for (int i = 0; i < L->length; ++i) {
        if (s <= L->data[i] && L->data[i] <= t){
            k++;
        } else{
            L->data[i-k]=L->data[i];
        }
    }
    L->length = L->length-k;
}
//2.6删除表中所有其值重复的元素，使表中所有元素的值均不同
void DeleteAllSame(SqList *L){
    if (L==NULL) return;
    int k;
    for (int i = 0; i < L->length; ++i) {
        k = 0;
        for (int j = i+1; j < L->length; ++j) {
            if (L->data[i] == L->data[j]){
                k++;
            } else{
                L->data[j-k] = L->data[j];
            }
        }
        L->length = L->length - k;
    }
}

//2.7将两个有序顺序表合并成一个新的顺序有序表，并由函数返回结果顺序表
bool MergeList(SqList L1, SqList L2, SqList *L3){
    if (L1.length+L2.length > 15)
        return false;
    int i=0,j=0,p=0;
    while (i < L1.length && j < L2.length ){
        if (L1.data[i] > L2.data[j]){
            L3->data[p++] = L2.data[j++];
        } else{
            L3->data[p++] = L1.data[i++];
        }
    }
    while (i < L1.length){
        L3->data[p++] = L1.data[j++];
    }
    while (j < L2.length){
        L3->data[p++] = L2.data[i++];
    }
    L3->length = p;
    return true;
}
//2.8
void Reverse(){}

//2.9   已知一有序线性表，查找值为x的元素，找到则将其与后继元素互换，
//    否则插入表中并使表中元素仍递增有序
void FindX(SqList *L, int x){
    int temp;
    for (int i = 0; i < L->length - 1; ++i) {
        if (L->data[i] == x){
            temp = L->data[i];
            L->data[i] = L->data[i+1];
            L->data[i+1] = temp;
            return;
        }
    }
    for (int j = L->length; j >= 0; j--) {
        if (x < L->data[j-1])
            L->data[j] = L->data[j-1];
        else{
            L->data[j-1] = x;
            L->length++;
            return;
        }
    }
}
//2.10将R中保存的序列循环左移p个位置(o<p<n)
//本方法先把首元素存放到temp，然后将后面元素逐个向前移动一个单位，再把temp赋值给末尾元素，执行p次，时间复杂度O(n*p),空间复杂度O(1).
void MoveLeft(int a[],int len, int p){
    if (p<0 || p>len)return;
    int temp;
    for (int i = 0; i < p; ++i) {
        temp = a[0];
        for (int j = 0; j < len-1; ++j) {
            a[j] = a[j+1];
        }
        a[len-1] = temp;
    }
}
//法二：思路：将问题视为把数组ab转换成数组ba， ba = (a的逆置b的逆置)整体的逆置,a代表前p个元素,b代表后n-p个元素
//本算法时间复杂度为O(p/2+(n-p)/2+n/2)=O(n),空间复杂度为O(1)
void Reverse(int a[], int lo, int hi){
    int temp;
    for (int i = 0; i < (hi-lo+1)/2; i++) {
        temp = a[lo+i];
        a[lo+i] = a[hi-i];
        a[hi-i] = temp;
    }
}
void MoveLeft1(int a[],int len, int p){
    Reverseit(a,0,p-1);
    Reverseit(a, p, len-1);
    Reverseit(a,0,len-1);
}
//2.11求两个序列A,B中位数，A,B等长
int Median(int A[], int B[],int n){
    int s1 = 0,d1 = n-1, m1, s2 = 0,d2 = n-1, m2;//分别表示序列A、B的首位数、末位数和中位数
    while (s1 != d1 || s2 != d2){
        m1 = (s1 + d1)/2;
        m2 = (s2 + d2)/2;
        if (A[m1]==B[m2])
            return A[m1];
        if (A[m1] < B[m2]){
            if ((s1+d1)%2 == 0){
                s1 = m1;
                d2 = m2;
            }else{
                s1 = m1+1;
                d2 = m2;
            }
        } else{
            if ((s2+d2)%2 == 0){
                d1 = m1;
                s2 = m2;
            } else{
                d1 = m1;
                s2 = m2+1;
            }
        }
    }
    return A[s1]<B[s2]? A[s1]:B[s2];
}

void SelectionSort(int a[],int n){
    int min,temp ;
    for (int i = 0; i < n; ++i) {
        min = i;
        for (int j = i+1; j < n; ++j) {
            if (a[min]>a[j])
                min = j;
        }
        temp = a[min];
        a[min] = a[i];
        a[i] = temp;
    }
}
//2.12
int FindMainElem(int a[], int n){
    SelectionSort(a,n);
    int i = 1, x;
    for (int k = 0; k < n; ++k) {
        if (a[k] == a[k+1]){
            i++;
        }else{
            i = 1;
        }
        if (i > n/2){
            x = a[k];
            return x;
        }
    }
    return -1;
}

//2.13 找出数组中未出现的最小正整数
//垃圾方法
int FindMinIntegerNotIn(int a[], int n){
    int min = -1;
    for (int k = 0; k < n; ++k) {
        if (a[k]>0){
            min = a[k];
            break;
        }
    }
    for (int i = min; i < n; ++i) {
        if (min > a[i] && a[i] > 0)
            min = a[i];
    }
    if (min>1)return 1;
    int j = min+1;
    for (; j <n ; ++j) {
        int flag =1;
        for (int i = 0; i < n; ++i) {
            if (j == a[i]){
                flag = 0;
                break;
            }
        }
        if (flag == 1){
            return j;
        }
    }
    return j+1;
}
//法2 空间换时间
int FindMinIntegerNotIn1(int a[], int n){
    int i,*b;
    b = (int *)malloc(sizeof(int)*n);
    memset(b,0, sizeof(int)*n);
    for (i = 0; i < n; i++) {
        if (a[i]>0 && a[i]<=n) //若a[i]的值介于1-n之间，则标记数组b
            b[a[i]-1]=1;
    }
    for (i = 0; i < n; i++) {
        if (b[i]==0) break;
    }
    return i+1;
}
void main(){
    int a[10] = {11,22,3,4,5,9,83,7,6,10};
    int b[5] = {1,2,3,4 ,5};
//    SqList L1 = CreateList(a,5);
//    SqList L2= CreateList(b,5);
//    PrintList(L1);
    int n = FindMinIntegerNotIn1(a,10);
    printf("%d",n);
//    PrintList(L1);
//    SqList L3;
//    PrintList(L1);
//    printf("\n");
}
