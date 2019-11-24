//
// Created by 李学俊 on 2019/11/2.
//
//小明是今年参加复试的外校考生，他要去民主楼小礼堂签到。由于对中南大学校本部很不熟悉，
// 小明找到了这边读书的好朋友鲁大师，不巧，鲁大师在忙着自由探索项目的结题工作，
// 不能给他带路，只好给他发了一份半成品的电子地图。地图上只列出了校本部内的N个点，
// M条路，小明处于S点，民主楼小礼堂是T点。小明感谢鲁大师，当然只是在拿到地图的一瞬间，
// 后面的情况让他知道这半成品到底有多坑。鲁大师制作的电子地图是带有语音提示功能的，
// 但是在编号为奇数的点他要等1分钟才能告诉他具体怎么走，而在编号为偶数的点要等2分钟。
// 现在告诉你地图的具体情况，小明想知道他能不能在A分钟内赶到民主楼小礼堂。

int main(){
    int vexnum, arcnum,start,end,time, temp,min,u,x,y,z,max = (int) 1e5;
    scanf("%d%d%d%d%d",&vexnum,&arcnum,&start,&end,&time);
    int M[vexnum+1][vexnum+1];
    for (int i = 1; i < vexnum+1; ++i) {
        for (int j = 1; j < vexnum+1; ++j) {
            if (i == j)M[i][j] = 0;
            else M[i][j] = max;
        }
    }
    for (int m = 0; m < arcnum; ++m) {
        scanf("%d%d%d",&x,&y,&z);
        if (x % 2 == 0) M[x][y] = z+2;
        if (x % 2 != 0)M[x][y] = z+1;
        if (y % 2 == 0)M[y][x] = z+2;
        if (y % 2 != 0)M[y][x] = z+1;
    }
    int S[vexnum+1],dist[vexnum+1];
    for (int k = 1; k < vexnum+1; ++k) {
        S[k] = 0;   //S[]置空
        dist[k] = M[start][k]; //距离初始化
    }
    S[start] = 1;
    for (int l = 1; l < vexnum; ++l) {
        min = max;
        for (int i = 1; i < vexnum+1; ++i) {
            if (S[i] == 0 && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        S[u] = 1;
        for (int j = 1; j < vexnum+1; ++j) {
            if (S[j] == 0)
                if (M[u][j] != max && dist[u] + M[u][j] < dist[j])
                    dist[j] = dist[u] + M[u][j];
        }
    }
    if (dist[end] <=  time)
        printf("YES\t%d", dist[end]);
    else
        printf("KENG");

}