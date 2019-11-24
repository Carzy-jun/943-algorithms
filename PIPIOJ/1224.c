//
// Created by 李学俊 on 2019/11/1.
//
#include <stddef.h>

/*
 * PIPI为了考察大家程序设计能力，给大家提出了下面这个题目：
人民艺术家PIPI的主要工作就是创作分形图，它有一个N*N的模板图，它制作分形的步骤如下：
1：将当前画纸分成N*N小块，在按照模板图染色(白或黑色)；
2：对于每个白色的小块，递归操作#1，即分成更小的N*N块，继续染色，而黑色的小块则不必操作。

你的任务是画出k次分型后的分型图。
 */
void Fx(int k, int n, char a[][n],char b[n^k][n^k]){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == '*') {
                for (int l = 0; l < n; ++l) {
                    for (int m = 0; m < n; ++m) {
                        b[i*n+l][j*n+m] = '*';
                    }
                }
            }
            if (a[i][j] == '.') {
                for (int l = 0; l < n; ++l) {
                    for (int m = 0; m < n; ++m) {
                        b[i*n+l][j*n+m] = a[l][m];
                    }
                }
            }
        }
    }
}

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    char a[2][2]={'.','*','.','.'};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
//            scanf("%c",&a[i][j]);
            printf("%c\t", a[i][j]);

        }
    }
//    printf("\n\n");
//
//    char b[n^k][n^k];
//    Fx(k,n,a,b);
//    for (int l = 0; l < n^k; ++l) {
//        for (int i = 0; i < n^k; ++i) {
//            printf("%c\t", b[l][i]);
//        }
//        printf("\n");
//    }
    return 0;
}
