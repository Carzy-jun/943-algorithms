//
// Created by 李学俊 on 2019/10/26.
//
#include <stdbool.h>

/*
 * 简单迷宫问题
 * int maze[5][5] = {
    0, 1, 0, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
};
它表示一个迷宫，其中的1表示墙壁，
 0表示可以走的路，只能横着走或竖着走，不能斜着走，请找出从左上角到右下角的最短路线
 */
//typedef struct {
//    int i,j,di;
//}Box;
//typedef struct {
//    Box data[100];
//    int top;
//}stack;
//
//void path(int N,int mg[N][N]){
//    stack *s = (stack*)malloc(sizeof(stack));
//    s->top=-1;
//    int i,j,di,i1=0, j1 = 0,k=0;
//    bool find;
//    Box e,p[30];
//    e.i = 1;e.j = 1;e.di = -1;
//    s->data[++s->top] = e;
//    mg[1][1]=1;
//    while (s->top != -1) {
//        e = s->data[s->top--];
//        i = e.i;j=e.j;di=e.di;
//        if (i == 5 && j == 5) {
//            k = 0;
//            while (s->top != -1) {
//                e = s->data[s->top--];
//                p[k++]=e;
//            }
//            while (k >= 1) {
//                k--;
//                printf("(%d,%d)\t", p[k].i,p[k].j);
//                if ((k + 2) % 5 == 0) {
//                    printf("\n");
//                }
//            }
//            return;
//        }
//        find = false;
//        while (di < 4 && !find) {
//            di++;
//            switch (di){
//                case 0:i1 = i-1;j1 = j;break;
//                case 1:i1 = i;j1 = j+1;break;
//                case 2:i1 = i+1;j1 = j;break;
//                case 3:i1 = i;j1 = j-1;break;
//                default:break;
//            }
//            if (mg[i1][j1]==0)find = true;
//        }
//        if (find) {
//            s->data[s->top].di = di;
//            e.i = i1;e.j = j1;e.di = -1;
//            s->data[++s->top]=e;
//            mg[i1][j1]=1;
//        } else {
//            e = s->data[s->top--];
//            mg[e.i][e.j]=0;
//        }
//    }
//}
//void Print(int n, int M[n][n]) {
//    for (int k = 0; k < n; ++k) {
//        for (int i = 0; i < n; ++i) {
//            printf("%d\t", M[k][i]);
//        }
//        printf("\n");
//    }
//}
typedef struct ArcNode {
    int adjvex;
    struct ArcNode *next;
} ArcNode;
typedef struct VNode {
    int data;
    ArcNode *first;
} VNode, AdjList;
typedef struct {
    AdjList vertices[21];
    int vexnum, arcnum;
} ALGraph;

typedef struct {
    int data[21];
    int top;
}st;

void Create(ALGraph *G) {
    int i, j;
    ArcNode *p;
    scanf("%d%d", &G->vexnum, &G->arcnum);
    for (int o = 1; o < G->vexnum+1; o++) {
        G->vertices[o].first = NULL;
    }
    for (int k = 0; k < G->arcnum; k++) {
        scanf("%d%d", &i, &j);
        p = (ArcNode *) malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->next = G->vertices[i].first;
        G->vertices[i].first = p;
    }
}
int main(){
    int mg[7][7];
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (i == 0 || j == 0 ||i==6||j==6) {
                mg[i][j]=1;
            } else {
                scanf("%d",&mg[i][j]);
            }
        }
    }
//    Print(7,mg);
    path(7,mg);
    return 0;
}

