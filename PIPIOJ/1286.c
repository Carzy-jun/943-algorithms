//
// Created by 李学俊 on 2019/11/4.
//
//PIPI是一个商人，经常需要将货物从A地运到B地，我们可以把PIPI经常活动的区域抽象成一个n个结点的地图，用一个nxn的矩阵表示。
//矩阵第i行第j列的值代表PIPI从 i 地将货物运到j地所需要的费用，若该值为-1则代表 i 和 j之间没有直接的通路，注意道路是双向的。
//出了上述固定费用外，PIPI在经过每一个结点时都需要交一次过路费(起点和终点不需要交过路费)。
//作为一个精打细算的商人，你能帮PIPI计算出从A地到B地的最少费用是多少吗？

//输入
//第一行输入结点数目n (0<n<=100)
//接下来n行输入一个nxn的矩阵(矩阵的值不大于1000)。
//第n+2行输入n个数，代表每个结点的过路费cost(cost<=1000)。
//第n+3行输入一个数q (q<=10000),代表PIPI的询问次数。
//接下来q行，每行输入两个数字，询问A到B的最少花费。

#define max 10000
void Floyd(int n, int M[n+1][n+1],int c[]){
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (M[i][j] > M[i][k]+M[k][j]+c[k]) {
                    M[i][j] = M[i][k]+M[k][j]+c[k];
                }
            }
        }
    }
}
//int Dijkstra(int n, int M[n+1][n+1],int A, int B){
//    int dist[n+1],S[n+1],min,u = 0;
//    for (int i = 1; i <= n ; ++i) {
//        dist[i] = M[A][i];
//        S[i] = 0;
//    }
//    S[A] = 1;
//    for (int i = 1; i <= n; ++i) {
//        min = max;
//        for (int j = 1; j <= n; ++j) {
//            if (dist[j] < min && S[j] == 0) {
//                u = j;
//                min = dist[j];
//            }
//        }
//        S[u] = 1;
//        for (int j = 1; j <= n; ++j) {
//            if (S[j] == 0) {
//                if (M[u][j] < max && M[u][j] + dist[u] < dist[j]) {
//                    dist[j] =  M[u][j] + dist[u];
//                }
//            }
//        }
//    }
//    return dist[B];
//}
int main(){
    int n,q,A,B,cost,x;
    scanf("%d",&n);
    int M[n+1][n+1],c[n];

    for (int i = 1; i <= n; ++i) {  //输入图
        for (int j = 1; j <= n; ++j) {
            scanf("%d",&x);
            if (x == -1) M[i][j] = max;
            else M[i][j] = x;
        }
    }
    for (int i = 1; i <= n; ++i) { //输入每个节点过路费
        scanf("%d",&cost);
        c[i] = cost;
//        for (int j = 1; j <=n ; ++j)
//            if (i!=j && M[i][j]<max)M[i][j]+=cost;
    }

    Floyd(n,M,c);

    scanf("%d",&q); //询问次数
    for (int k = 0; k < q; ++k) {
        scanf("%d%d",&A,&B);
        printf("%d\n", M[A][B]);
    }
//    for (int i = 0; i < q; ++i) {
//        int S[n+1][n+1];
//        memcpy(S,M, sizeof(M));//复制数组
//        scanf("%d%d",&A,&B);
//        for (int j = 1; j <= n ; ++j) {
//            if (S[A][j] < max && A != j) {
//                S[A][j]-=c[A];
//            }
//            if (S[B][j] < max && B != j) {
//                S[B][j]-=c[B];
//            }
//        }
//
//        printf("%d\n",Dijkstra(n,S,A,B));
//    }
    return 0;
}
