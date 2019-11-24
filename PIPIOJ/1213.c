//
// Created by 李学俊 on 2019/10/31.
//
/*
 * 从顺序表L中删除具有最小值的元素(假设唯一)并友函数返回被删元素的值。空出的元素由最后一个元素填补。
 */
int main(){
    int n;
    scanf("%d",&n);
    int a[n],m = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d",&a[i]);
        if (a[i] < a[m])
            m = i;
    }
    printf("%d\n", a[m]);
    a[m] = a[n-1];
    for (int j = 0; j < n-1; ++j)
        printf("%d\t",a[j]);
}

