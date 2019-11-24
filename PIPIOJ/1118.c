//
// Created by 李学俊 on 2019/11/6.
//
//省政府“畅通工程”的目标是使全省任何两个村庄间都可以实现公路交通（但不一定有直接的公路相连，
// 只要能间接通过公路可达即可）。现得到城镇道路统计表，
// 表中列出了任意两城镇间修建道路的费用，以及该道路是否已经修通的状态。现请你编写程序，
// 计算出全省畅通需要的最低成本。
#define Max 100000

int prim(int n, int M[n + 1][n + 1]) {
    int lowcost[n + 1], Min, sum = 0, k = 0;
    for (int i = 1; i <= n; ++i) {
        lowcost[i] = M[1][i];
    }
    for (int i = 1; i < n; ++i) {
        Min = Max;
        for (int j = 1; j <= n; ++j) {
            if (lowcost[j] != -1 && lowcost[j] < Min) {
                Min = lowcost[j];
                k = j;
            }
        }
        sum += Min;
        lowcost[k] = -1;
        for (int j = 1; j <= n; ++j) {
            if (M[k][j] != -1 && lowcost[j] != -1 && lowcost[j] > M[k][j]) {
                lowcost[j] =  M[k][j];
            }
        }
    }
    return sum;
}

int main() {
    int n, x, y, cost, hasRoad;
    while (1) {
        scanf("%d", &n);
        if (n != 0) {
            int M[n + 1][n + 1];
            for (int i = 1; i <= n; ++i) {
                for (int j = i; j <= n; ++j) {
                    if (i == j) {
                        M[i][j] = -1;
                    } else {
                        scanf("%d%d%d%d", &x, &y, &cost, &hasRoad);
                        if (hasRoad) {
                            M[i][j] = 0;
                            M[j][i] = 0;
                        } else {
                            M[i][j] = cost;
                            M[j][i] = cost;
                        }
                    }
                }
            }
            printf("%d\n", prim(n,M));
        } else {
            break;
        }
    }
    return 0;
}