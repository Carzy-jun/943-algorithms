//
// Created by 李学俊 on 2019/10/26.
//
/*
 * 长度为n的顺序表L，编写一个时间复杂度为O(n),空间复杂度为O(1)的算法，删除线性表中所有值为x的数据元素
 */
int main(){
    int n,x,min,a[99],j=0;
    scanf("%d%d",&n,&min);
    for(int i=1;i<n;++i){
        scanf("%d",&x);
        if(x>min)a[j++]=x;
        else{
            a[j++]=min;
            min=x;
        }
    }
    printf("%d\n", min);
    for (int k = n-1; k >1; --k) {
        printf("%d\t",a[k]);
    }
}