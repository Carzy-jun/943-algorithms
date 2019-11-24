//
// Created by 李学俊 on 2019/11/5.
//

int main(){
    int n,m,sum = 0;
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            sum = sum + i*j*(n%i)*(m%j);
        }
    }
}