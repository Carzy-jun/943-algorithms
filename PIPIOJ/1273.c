//
// Created by 李学俊 on 2019/10/27.
//

/*
 * 现在有三个有序数组 A ， B ，C ，请你求出他们的交集。
 */
int com(int a,int b){
    if(a<b)return a;
    else return b;
}
int main(){
    int max = 100;
    int a[max],b[max],c[max],n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    for (int i = 0; i < n; ++i) {
        scanf("%d",&a[i]);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d",&b[i]);
    }
    for (int i = 0; i < q; ++i) {
        scanf("%d",&c[i]);
    }
    for (int i=0,j=0,k=0; i<n&&j<m&&k<q ; ) {
        if (a[i] == b[j] && b[j] == c[k]) {
            printf("%d\t", a[i]);
            i++;j++;k++;
        } else {
            int cp= com(com(a[i],b[j]),c[k]);
            if (cp == a[i]) {
                i++;
            }
            if (cp == b[j]) {
                j++;
            }
            if (cp == c[k]) {
                k++;
            }
        }
    }
}
