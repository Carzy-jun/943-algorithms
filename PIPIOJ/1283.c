//
// Created by 李学俊 on 2019/11/4.
//
//

//
// Created by 李学俊 on 2019/10/29.
//
/*
 * 在数组中找到从小到大排序倒数第k大的元素。
 */
int Partition(int a[],int lo,int hi){
    int pivot = a[lo];
    while (lo < hi) {
        while (lo < hi && a[hi] >= pivot) {
            hi--;
        }
        a[lo]=a[hi];
        while (lo < hi && a[lo] <= pivot) {
            lo++;
        }
        a[hi]=a[lo];
    }
    a[lo]=pivot;
    return lo;
}
void sort(int a[],int lo,int hi,int n,int k){
    int pivot = Partition(a,lo,hi);
    if (pivot == n-k || lo > hi) {
        return;
    } else if(pivot > n-k){
        sort(a,lo,pivot-1,n,k);
    } else {
        sort(a,pivot+1,hi,n,k);
    }
}
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    int a[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    sort(a,0,n-1,n,k);
    printf("%d\n", a[n-k]);
}
