//
// Created by 李学俊 on 2019/8/21.
//

#include <malloc.h>

//选择排序
void selectionSort(int a[], int n){
    int min,t;
    for (int i = 0; i < n-1; ++i) {
        min = i;
        for (int j = i; j < n; ++j) {
            if (a[j] < a[i]) {
                min = j;
            }
        }
        t = a[min] ;
        a[min] = a[i];
        a[i] = t;
    }
}

//插入排序
void InsertSort(int a[], int n){
    int t;
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 && a[j] < a[j-1] ; j--) {
            t = a[j] ;
            a[j] = a[j-1];
            a[j-1] = t;
        }
    }
}
//希尔排序
void ShellSort(int a[], int n){
    int h = 1,t;
    while (h < n/3) h = 3*h + 1; //动态设置间隔h
    while (h >= 1){
        for (int i = h; i < n; i++){
            for (int j = i; j >= h && a[j] < a[j-h]; j -= h){
               t = a[j];
               a[j] = a[j-h];
               a[j-h] = t;
            }
        }
        h = h/3;
    }
}

//冒泡排序
void BubbleSort(int a[], int n){
    int t, flag;
    for (int i = 0; i < n-1; ++i) {
        flag = 0;
        for (int j = i+1; j < n; ++j) {
            if (a[i] > a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
                flag = 1;
            }
        }
        if (flag == 0) return;
    }
}
//快速排序
int Partiton(int a[], int low, int high){
    int pivot = a[low];
    while (low < high) {
        while (low < high && a[high] >= pivot) {
            --high;
        }
        a[low] = a[high];
        while (low < high && a[low] <= pivot) {
            ++low;
        }
        a[high] = a[low];
    }
    a[low] = pivot;
    return low;
}
void quickSort(int a[], int low, int high){
    if (low > high) return;
    int pivot = Partiton(a, low, high);
    quickSort(a, low, pivot-1);
    quickSort(a, pivot+1, high);
}
void QuickSort(int a[], int n){
    quickSort(a, 0, n-1);
}

//堆排序
void AdjustDown(int a[], int k, int len){//将元素k向下调整
    a[0] = a[k];
    for (int i = 2*k; i <= len; i*=2) {
        if (i < len && a[i] < a[i + 1]) {
            i++;
        }
        if (a[0] >= a[i]) {
            break;
        } else {
            a[k] = a[i];
            k = i;
        }
    }
    a[k] = a[0];
}
void BuildMaxHeap(int a[], int len){
    for (int i = len/2; i > 0 ; --i) {
        AdjustDown(a, i, len);
    }
}
void HeapSort(int a[], int n){
    BuildMaxHeap(a,n);
    for (int i = n; i > 1 ; --i) {
        int t = a[i];
        a[i] = a[1];
        a[1] = t;
        AdjustDown(a,1,i-1);
    }
}

//归并排序
int *b = NULL;
void Merge(int a[], int low, int mid, int high){
    for (int k = 0; k <= high; ++k) {
        b[k] = a[k];
    }
    int i = low,j = mid +1;//i从左半边开始，j从右半边开始
    for (int k = low; k <= high; k++){
        if (i > mid)         a[k] = b[j++];//左半边用尽，取右半边元素
        else if (j > high)   a[k] = b[i++];//右半边用尽，去左半边元素
        else if (b[j]<b[i])  a[k] = b[j++];
        else                 a[k] = b[i++];
    }
}
void Mergesort(int a[], int low, int high){
    if (low < high) {
        int mid = (low + high)/2;
        Mergesort(a,low,mid);
        Mergesort(a, mid+1, high);
        Merge(a,low, mid, high);
    }
}
void MergeSort(int a[], int n){
    b = (int*)malloc((n+1)* sizeof(int));
    Mergesort(a,0,n-1);
}


void PrintArray(int a[], int n){
    for (int i = 0; i < n; ++i) {
        printf("%d\t", a[i]);
    }
}
//int main(){
//    int a[] = {6,5,4,3,2,1};
//    MergeSort(a,6);
//    PrintArray(a,6);
//    return 0;
//}