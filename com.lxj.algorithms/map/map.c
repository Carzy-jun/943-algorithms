//
// Created by 李学俊 on 2019/8/4.
//
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "../stackAndQueue/StackAndQueue.c"
#include "../sort/sort.c"

#define MaxVertexNum 100
#define M 32767

typedef int InfoType;//边权值数据类型
typedef char VertexType;//顶点数据类型
typedef int EdgeType; //带权图中边上权值的数据类型

//邻接矩阵存储结构定义
typedef struct {
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum; //图的当前顶点数和弧数
} MGraph;

//创建邻接矩阵
void CreateMG(MGraph *G,int vexnum, int arcnum, const VertexType vexNode[], EdgeType arc[][vexnum]){
    int i, j;
    for (i = 0; i < vexnum; ++i) {
        G->Vex[i] = vexNode[i];
    }
    for (i = 0; i < vexnum; ++i) {
        for (j = 0; j < vexnum; ++j) {
            G->Edge[i][j] = arc[i][j];
        }
    }
    G->arcnum = arcnum;
    G->vexnum = vexnum;
}

//打印邻接矩阵
void PrintMG(MGraph G){
    printf("邻接矩阵为：\n");
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            printf("%d\t", G.Edge[i][j]);
        }
        printf("\n");
    }
}

//图的邻接表的存储结构定义
typedef struct ArcNode { //边（弧）表节点
    int adjvex; //该弧指向的顶点的位置
    struct ArcNode *next; //指向下一条弧的指针
    InfoType info;  //边权值
} ArcNode;
typedef struct VNode {  //顶点表节点
    VertexType data; //顶点信息
    ArcNode *first; //指向第一条依附该顶点的弧的指针
} VNode, AdjList;
typedef struct {
    AdjList vertices[MaxVertexNum]; //邻接表
    int vexnum, arcnum; //顶点数和弧数
} ALGraph;


//创建邻接表
void Create(ALGraph *G) {
    int i, j, k;
    ArcNode *p;
    printf("输入顶点数和边数:\n");
    scanf("%d%d", &G->vexnum, &G->arcnum);

    //输入顶点信息
    printf("输入顶点信息:\n");
    for (i = 0; i < G->vexnum; i++) {
        getchar();
        scanf("%c", &G->vertices[i].data);
        G->vertices[i].first = NULL;           //将指向边表的指针初始化
    }

    //建立边表
    printf("输入边(Vi,Vj)中的下标i,j:\n");
    for (k = 0; k < G->arcnum; k++) {
        scanf("%d%d", &i, &j);
        p = (ArcNode *) malloc(sizeof(ArcNode));
        p->adjvex = j;                                //存储弧头
        p->next = G->vertices[i].first;            //头插法插入边结点
        G->vertices[i].first = p;

        //下面代码有向图无,无向图有
        p = (ArcNode *) malloc(sizeof(ArcNode));
        p->adjvex = i;                                //存储弧头
        p->next = G->vertices[j].first;            //头插法插入边结点
        G->vertices[j].first = p;
    }
}

//通过数组创建邻接表
void CreateG(ALGraph *G, int vexnum, int arcnum, const char vexNode[], int arc[][vexnum]) {
    int i, j;
    ArcNode *p;
    G->vexnum = vexnum;
    G->arcnum = arcnum;
    //输入顶点信息
    for (i = 0; i < G->vexnum; i++) {
        G->vertices[i].data = vexNode[i];
        G->vertices[i].first = NULL;           //将指向边表的指针初始化
    }
    //建立边表
    for (i = 0; i < vexnum; ++i) {
        for (j = 0; j < vexnum; j++) {
            if (arc[i][j] != 0) {
                ArcNode *r = G->vertices[i].first;
                p = (ArcNode *) malloc(sizeof(ArcNode));
                p->adjvex = j;                            //存储弧头
                if (!r) {
                    G->vertices[i].first = p;
                    p->next = NULL;
                } else {
                    while (r->next) {
                        r = r->next;
                    }
                    r->next = p;
                    p->next = NULL;           //尾插法插入边结点
                }
            }
        }
    }
}

//打印邻接表
void PrintGraph(ALGraph G) {
    ArcNode *p;
    printf("邻接表为:\n");
    for (int i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].first;
        while (p) {
            printf("(%c,%c)", G.vertices[i].data, G.vertices[p->adjvex].data);
            p = p->next;
        }
        printf("\n");
    }
}

//打印所有顶点
void PrintVexNode(ALGraph G) {
    printf("该图节点有:\n");
    for (int i = 0; i < G.vexnum; ++i) {
        printf("%c\t", G.vertices[i].data);
    }
    printf("\n");
}
//判断是否存在边<x,y>
bool Adjacent(ALGraph G, int x, int y) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (x == i) {
            ArcNode *p = G.vertices[i].first;
            while (p) {
                if (p->adjvex == y) {
                    return true;
                }
                p = p->next;
            }
        }
    }
    return false;
}

//列出图G中与节点x邻接的边
void Neighbors(ALGraph G, char x) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (x == G.vertices[i].data && G.vertices[i].first) {
            ArcNode *p = G.vertices[i].first;
            printf("该顶点邻接的边有:\n");
            while (p) {
                printf("(%c,%c),", G.vertices[i].data, G.vertices[p->adjvex].data);
                p = p->next;
            }
        }
    }
}
//判断是否存在顶点x
bool ExistVextex(ALGraph G, int x) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (i == x) {
            return true;
        }
    }
    return false;
}

//获取顶点x的标号
int LocateVextex(ALGraph G, VNode x) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (x.data == G.vertices[i].data) {
            return i;
        }
    }
    return -1;
}

//在图G中插入顶点x
void InsertVertex(ALGraph *G, VNode x) {
    for (int i = 0; i < G->vexnum; ++i) {
        if (G->vertices[i].data == x.data) {
            printf("该顶点已存在.");
            return;
        }
    }
    G->vertices[G->vexnum].first = x.first;
    G->vertices[G->vexnum++].data = x.data;
}

//向图G中添加边
void AddEdge(ALGraph *G, int x, int y) {
    if (Adjacent(*G, x, y)) {
        printf("该边已存在");
        return;
    }
    for (int i = 0; i < G->vexnum; ++i) {
        if (i == x) {
            ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
            p->adjvex = y;
            p->next = G->vertices[i].first;
            G->vertices[i].first = p;
            G->arcnum++;
        }
    }
    //无向图含以下代码
//    for (int j = 0; j < G->vexnum; ++j) {
//        if (j == y) {
//            ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
//            p->adjvex = x;
//            p->next = G->vertices[j].first;
//            G->vertices[j].first = p;
//            G->arcnum++;
//        }
//    }
}

//从图中删除边
void RemoveEdge(ALGraph *G, int x, int y) {
    if (!Adjacent(*G, x, y)) {
        printf("边(%d%d)不存在", x, y);
        return;
    }
    for (int i = 0; i < G->vexnum; ++i) {
        if (i == x) {
            ArcNode *p = G->vertices[i].first, *t;
            //设置一个头节点
            ArcNode *pre = (ArcNode *) malloc(sizeof(ArcNode));
            pre->next = p;

            if (G->vertices[i].first->adjvex == y) {
                t = G->vertices[i].first;
                G->vertices[i].first = G->vertices[i].first->next;
                free(t);
                return;
            }
            while (p) {
                if (p->adjvex == y) {
                    t = p;
                    p = p->next;
                    pre->next = p;
                    free(t);
                    G->arcnum--;
                    return;
                }
                pre = p;
                p = p->next;
            }
        }
    }
}

//从图G中删除顶点x
void DeleteVertex(ALGraph *G, int y) {
//    int y = LocateVextex(*G,x);
    //先删除与x相关的边
    for (int i = 0; i < G->vexnum; ++i) {
        if (Adjacent(*G, y, i)) {
            RemoveEdge(G, y, i);
        }
        if (Adjacent(*G, i, y)) {
            RemoveEdge(G, i, y);
        }
    }
    for (int k = 0; k < G->vexnum; ++k) {
        //修改必要表结点的顶点的位置值
        ArcNode *p;
        p = G->vertices[k].first;
        while (p) {
            if (p->adjvex > y) {
                p->adjvex--;
            }
            p = p->next;
        }
    }
    //删除顶点x
    for (int j = y; j < G->vexnum; ++j) {
        G->vertices[j] = G->vertices[j + 1];
    }
    G->vexnum--;
}
//设置图边权值
void Set_Info(ALGraph *G){
    for (int i = 0; i < G->vexnum; ++i) {
        ArcNode *p = G->vertices[i].first;
        while (p) {
            scanf("%d", &p->info);
            p = p->next;
        }
    }
}

//求图中顶点x的第一个邻接点，有则返回顶点号，若没有或x不存在，返回-1
int FirstNeighbor(ALGraph G, int x) {
    ArcNode *p = G.vertices[x].first;
    if (!p) return -1;
    return p->adjvex;
}

//假设顶点y是顶点x的一个邻接点,返回除y之外顶点x的下一个顶点的顶点号,若y是x的
//最后一个邻接点，则返回-1
int NextNeighbor(ALGraph G, int x, int y) {
    ArcNode *p = G.vertices[x].first;
    //找到
    while (p) {
        if (p->adjvex == y)break;
        p = p->next;
    }
    if (p) {
        ArcNode *nextNode = p->next;
        if (nextNode) {
            return nextNode->adjvex;
        }
    }
    return -1;
}

//广度优先搜索
bool visited[MaxVertexNum]; //节点访问标记数组
void BFS(ALGraph G, int v, Queue *Q) {
    printf("%c\t", G.vertices[v].data);
    visited[v] = true;
    EnQueue(Q, v);
    while (!IsEmpty(Q)) {
        DeQueue(Q, &v);
        for (int i = FirstNeighbor(G, v); i >= 0; i = NextNeighbor(G, v, i)) {
            if (!visited[i]) {
                printf("%c\t", G.vertices[i].data);
                visited[i] = true;
                EnQueue(Q, i);
            }
        }
    }
}
void BFSTraverse(ALGraph G) {
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    Queue *Q = InitQueue();
    for (int j = 0; j < G.vexnum; ++j) {//每个连通分量调用一次BFS
        if (!visited[j]) {
            BFS(G, j, Q);
        }
    }
}

//BFS求解单源最短路径
void BFS_MIN_Distance(ALGraph G, int u) {
    int d[G.vexnum];
    for (int i = 0; i < G.vexnum; ++i) {
        d[i] = 32767;
    }
    visited[u] = true;
    d[u] = 0;
    Queue *Q = InitQueue();
    EnQueue(Q, u);
    while (!IsEmpty(Q)) {
        DeQueue(Q, &u);
        for (int i = FirstNeighbor(G, u); i >= 0; i = NextNeighbor(G, u, i)) {
            if (!visited[i]) {
                EnQueue(Q, i);
                d[i] = d[u] + 1; //关键步骤
                visited[i] = true;
            }
        }
    }
    for (int j = 0; j < G.vexnum; ++j) {
        printf("%d\t", d[j]);
    }
}


//深度优先搜索，（类似于树的先序遍历）
void DFS(ALGraph G, int v) {
    printf("%c\t", G.vertices[v].data);
    visited[v] = true;
    for (int i = FirstNeighbor(G, v); i >= 0; i = NextNeighbor(G, v, i)) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
}

void DFSTraverse(ALGraph G) {
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    for (int j = 0; j < G.vexnum; ++j) {
        if (!visited[j]) {
            DFS(G, j);
        }
    }
}

//判断一个无向图是否是一棵树
//一个无向图是一颗树的条件是G必须是无回路的连通图 或 有n-1条边的连通图,这里采用第二种方法
void IsTreeByDFS(ALGraph G, int v, int *Vnum, int *Enum) {
    visited[v] = true;
    (*Vnum)++;
    for (int i = FirstNeighbor(G, v); i >= 0; i = NextNeighbor(G, v, i)) {
        (*Enum)++;
        if (!visited[i]) {
            IsTreeByDFS(G, i, Vnum, Enum);
        }
    }
}

bool IsTree(ALGraph G) {
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    int Vnum = 0, Enum = 0;
    IsTreeByDFS(G, 0, &Vnum, &Enum);
    return Vnum == G.vexnum && Enum == 2 * (G.vexnum - 1);
}

//写出图的DFS深度优先搜索的非递归算法
void DFS1(ALGraph G, int v) {
    SqStack S;InitStack(&S);int k;
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    Push(&S, v);
    visited[v] = true;
    while (!StackEmpty(S)) {
        Pop(&S, &k);
        printf("%c\t", G.vertices[k].data);     //先访问，再将其所有子节点入栈
        for (int i = FirstNeighbor(G,k); i >= 0 ; i = NextNeighbor(G, k, i)) {
            if (!visited[i]) {              //未进过栈的顶点入栈
                Push(&S, i);
                visited[i] = true;          //做标记，以免再次入栈
            }
        }
    }
}
//分别采用基于深度优先和广度优先算法判别有向图中是否存在由顶点vi 到 vj(vi!=vj)的路径
//1.基于深度优先
bool BFS_HasRoad(ALGraph G, int v1, int v2){
    if (v1 == v2) return true;
    visited[v1] = true;
    for (int i = FirstNeighbor(G, v1); i >= 0 ; i = NextNeighbor(G, v1, i)) {
        if (!visited[i]) {
            return BFS_HasRoad(G, i, v2);
        }
    }
    return false;
}
bool HasRoad(ALGraph G, int v1, int v2){
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    return BFS_HasRoad(G,v1,v2);
}
//2.基于广度优先
bool HasRoad1(ALGraph G, int v1, int v2){
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    Queue *Q = InitQueue();
    EnQueue(Q, v1);
    while (!IsEmpty(Q)) {
        DeQueue(Q, &v1);
        if (v1 == v2) return true;
        visited[v1] = true;
        for (int v = FirstNeighbor(G,v1); v >= 0 ; v = NextNeighbor(G, v1, v)){
            if (!visited[v])
                EnQueue(Q, v);
        }
    }
    return false;
}

//输出从顶点vi到顶点vj的所有简单路径
void PrintPath(ALGraph G, int v1, int v2, int path[], int d){
    d++;
    path[d] = v1;
    visited[v1] = true;
    if (v1 == v2) {
        for (int j = 0; j < d; ++j)
            printf("%c\t", G.vertices[path[j]].data);
        printf("\n");
    }
    ArcNode *p = G.vertices[v1].first;
    while (p) {
        int w = p->adjvex;
        if (!visited[w]) {
            PrintPath(G, w, v2, path, d);
        }
        p = p->next;
    }
    visited[v1] = false;
}
void FindPath(ALGraph G, int v1, int v2){
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    int *a = (int*)malloc(G.vexnum*sizeof(int));
    PrintPath(G, v1, v2, a, -1);
}

//Prim算法的原理是在开始时选取一个节点最为其实节点，然后遍历所有该节点链接的边，
// 并选取其中权重最小的边，同时将已经选取的节点标位已知；接下来重复之前的步骤，
// 在已知节点的链接的边中选取权重最小的边，同时将其所链接的边标位已知，一直这样操作，
// 直到所有的节点都已知。(PS:在实际代码中，我们使用一个表格来储存生成树的信息)
void Prim(ALGraph G){
    ArcNode *p;
    int v = 0, w;
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    ALGraph *Min_tree = (ALGraph*)malloc(sizeof(ALGraph));
    Min_tree->vertices[v] = G.vertices[v]; //添加第一个顶点
    Min_tree->vexnum++;
    while (Min_tree->vexnum != G.vexnum) { //若树中不含全部顶点
        p = G.vertices[v].first;
        int min = p->info;
        while (p) {
            w = p->adjvex;
            if (!visited[w] && p->info < min) {
                Min_tree->vertices[v].first = p;    //入权值最小边
                Min_tree->vertices[w] = G.vertices[w];  //添加该顶点
                visited[w] = true;
            }
            p = p->next;
            Min_tree->vexnum++;
            Min_tree->arcnum++;
        }

    }

}
//prim 邻接矩阵存储
void prim(MGraph G, int v){
    int lowcost[MaxVertexNum];
    int MIN;
    int closest[MaxVertexNum],i,j, k = 0;
    for (i = 0; i < G.vexnum; i++) { //初始化lowcost,closest
        lowcost[i] = G.Edge[v][i];
        closest[i] = v;
    }
    for (i = 1; i < G.vexnum; i++){
        MIN = M;
        for (j = 0; j < G.vexnum; ++j) {
            if (lowcost[j] != 0 && lowcost[j] < MIN) {
                MIN = lowcost[j];
                k = j;
            }
        }
        printf("边(%c,%c)权为：%d\n", G.Vex[closest[k]],G.Vex[k],MIN);
        lowcost[k] = 0;
        for (j = 0; j < G.vexnum; ++j) {
            if (lowcost[j] != 0 && G.Edge[k][j] < lowcost[j]) {
                lowcost[j] = G.Edge[k][j];
                closest[j] = k;
            }
        }
    }
}

typedef struct {
    int start;  //边的起始顶点
    int end;  //边的终止顶点
    int wight;  //边的权值
}Edge;
void Insertsort(Edge a[], int n){
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 && a[j-1].wight > a[j].wight ; --j) {
            Edge t = a[j];
            a[j] = a[j-1];
            a[j-1] = t;
        }
    }
}
//Kruskal算法
void Kruskal(MGraph G){
    int i, j, start1, end1, sn1, sn2, k;
    int vset[MaxVertexNum];
    Edge E[MaxSize];  //存放图的所有边
    k = 0;      //E数组下标从0开始
    for (i = 0; i < G.vexnum; i++) {//由G产生边集E，不重复选取同一条边
        for (j = 0; j <= i; ++j) {
            if (G.Edge[i][j] != 0 && G.Edge[i][j] != M) {
                E[k].start = i;
                E[k].end = j;
                E[k].wight = G.Edge[i][j];
                k++;
            }
        }
    }
    Insertsort(E, G.arcnum);
    for (i = 0; i < G.vexnum; ++i) {//初始化辅助数组
        vset[i] = i;
    }
    k = 1; //k表示当前构造生成树的第几条边，初值为1
    j = 0; //E中边的下标，初值为零
    while (k < G.vexnum) { //生成树的边数小于G.vexnum时
        start1 = E[j].start;
        end1 = E[j].end;
        sn1 = vset[start1];
        sn2 = vset[end1];
        if (sn1 != sn2) {
            printf("边(%c,%c):权值为:%d\n",G.Vex[start1],G.Vex[end1],E[j].wight );
            k++;
//            vset[end1] = sn1;
            for (i = 0; i < G.vexnum; ++i) {
                if (vset[i] == sn2) {
                    vset[i] = sn1;
                }
            }
        }
        j++;
    }
}

//dijkstra算法求单源最短路径
void Dispath(MGraph G, int dist[], const int path[], const int S[], int v){//输出单源最短路径
    int i,j,k;
    int apath[MaxVertexNum],d;
    for (i = 0; i < G.vexnum; ++i) {
        if (S[i] == 1 && i != v) {
            printf("从顶点%c到顶点%c的路径长度为:%d\t",G.Vex[v],G.Vex[i],dist[i]);
            d = 0; apath[d] = i;
            k = path[i];
            if (k == -1) {
                printf("无路径\n");
            } else {
                while (k != v) {
                    d++; apath[d] = k;
                    k = path[k];
                }
                d++; apath[d] = v;
                printf("%d", apath[d]);
                for (j = d-1; j >=0 ; --j) {
                    printf(",%d", apath[j]);
                }
                printf("\n");
            }
        }
    }
}
void Dijkstra(MGraph G, int v) {
    int dist[MaxVertexNum], path[MaxVertexNum], S[MaxVertexNum];//S[i]=1表示顶点i在S中，=0表示在U中
    int MINdis, i, j, u = 0;
    for (i = 0; i < G.vexnum; ++i) {
        dist[i] = G.Edge[v][i]; //距离初始化
        S[i] = 0;   //S[]置空
        if (G.Edge[v][i] < M) {//路径初始化
            path[i] = v;    //顶点v到顶点i有边时，顶点i的前一个顶点为v
        } else {
            path[i] = -1; //没有则前一个顶点为-1
        }
    }
    S[v] = 1;
    path[v] = 0;   //源点v放入S中
    for (i = 0; i < G.vexnum - 1; ++i) { //循环直到所有顶点最短路径都求出
        MINdis = M;//置最大长度初值
        for (j = 0; j < G.vexnum; ++j) {  //选取U中具有最小最短路径长度的顶点u
            if (S[j] == 0 && dist[j] < MINdis) {
                u = j;
                MINdis = dist[j];
            }
        }
        S[u] = 1;           //u加入S
        for (j = 0; j < G.vexnum; ++j) {    //修改U中顶点的最短路径
            if (S[j] == 0) {
                if (G.Edge[u][j] < M && dist[u] + G.Edge[u][j] < dist[j]) {
                    dist[j] = dist[u] + G.Edge[u][j];
                    path[j] = u;
                }
            }
        }
    }
    Dispath(G, dist, path, S, v);
}

//Floyd算法求多源最短路径
//输出多源最短路径
void DispathFd(MGraph G, int A[][MaxVertexNum], int path[][MaxVertexNum]){
    int i,j,k,s;
    int apath[MaxVertexNum],d;
    for (i = 0; i < G.vexnum; ++i) {
        for (j = 0; j < G.vexnum; ++j) {
            if (A[i][j] != M && i != j) {
                printf("从%c到%c的路径为：",G.Vex[i],G.Vex[j]);
                k = path[i][j];
                d = 0; apath[d] = j;
                while (k != -1 && k != i) {
                    d++; apath[d] = k;
                    k = path[i][k];
                }
                d++; apath[d] = i;
                printf("%d", apath[d]);
                for (s = d-1; s >= 0; --s) {
                    printf(",%d", apath[s]);
                }
                printf("\t路径长度为：%d\n",A[i][j]);
            }
        }
    }
}
void Floyd(MGraph G){
    int A[MaxVertexNum][MaxVertexNum],path[MaxVertexNum][MaxVertexNum];
    int i,j,k;
    for (i = 0; i < G.vexnum; ++i) { //初始化A[]
        for (j = 0; j < G.vexnum; ++j) {
            A[i][j] = G.Edge[i][j];
            if (i != j && G.Edge[i][j] < M) {
                path[i][j] = i;    //顶点i到j有边时
            } else {
                path[i][j] = -1;
            }
        }
    }
    for (k = 0; k < G.vexnum; ++k) {      //依次考察所有顶点
        for (i = 0; i < G.vexnum; ++i) {
            for (j = 0; j < G.vexnum; ++j) {
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k]+ A[k][j];     //修改最短路径长度
                    path[i][j] = path[k][j];        //修改最短路径
                }
            }
        }
    }
    DispathFd(G,A,path); //输出
}


//拓扑排序
bool TopologicalSort(ALGraph *G){
    SqStack S;InitStack(&S); //存储入度为0的顶点
    int indegree[G->vexnum],i,j, count = 0;//count用来判断是否所有顶点是否拓扑排序成功
    ArcNode *p;
    for (i = 0; i < G->vexnum; ++i) { //初始化所有顶点入度
        indegree[i] = 0;
    }
    for (i = 0; i < G->vexnum; ++i) {//求所有顶点的入度
        p = G->vertices[i].first;
        while (p) {
            indegree[p->adjvex]++;
            p = p->next;
        }
    }
    for (i = 0; i < G->vexnum; ++i) {//入度为0的顶点进栈
        if (indegree[i] == 0) {
            Push(&S,i);
            count++;
        }
    }
    while (!StackEmpty(S)) {    //栈不为空循环
        Pop(&S,&i);     //出栈一个顶点
//        printf("%c\t", G->vertices[i].data); //输出该顶点
        p = G->vertices[i].first;
        while (p) {
            j = p->adjvex;
            indegree[j]--;
            if (indegree[j] == 0) { //入度为0的邻接点进栈
                Push(&S, j);
                count++;
            }
            p = p->next;
        }
    }
        return count == G->vexnum;
}



//关键路径算法
void FindInDegree(MGraph G,int *indegree)/*对各顶点求入度，邻接矩阵的列*/
{int i,j;
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++)
            if(G.Edge[j][i].adj==1) indegree[i]++;
}
int *ve,*vl;/*最早发生时间和最迟发生时间数组，全局的*/

int CriticalPath(ALGraph G)/*G为有向网，输出G的各项关键活动*/
{
}
int main() {
//    ALGraph G;
//    char vexNode[] = {'a', 'b', 'c', 'd', 'e', 'f'};
//    int arc[][6] = {
//            //  a   b   c   d   e   f
//                0,  1,  1,  0,  0,  0,//a
//                0,  0,  0,  1,  1,  0,//b
//                0,  0,  0,  0,  0,  1,//c
//                0,  0,  0,  0,  0,  0,//d
//                0,  0,  1,  0,  0,  0,//e
//                0,  0,  0,  0,  0,  0 //f
//    };
//  CreateG(&G);
//    CreateG(&G, 6, 6, vexNode, arc);
//    PrintGraph(G);
    char vexNode[] = {'a', 'b', 'c', 'd', 'e', 'f'};
//    int arc[][6] = {
//            //  a   b   c   d   e   f
//                0,  3,  1,  5,  M,  M,//a
//                3,  0,  8,  M,  3,  M,//b
//                1,  8,  0,  7,  6,  4,//c
//                5,  M,  7,  0,  M,  2,//d
//                M,  3,  6,  M,  0,  6,//e
//                M,  M,  4,  2,  6,  0 //f
//    };
    int arc[][6] = {
            //  a   b   c   d   e   f
                0,  1,  0,  0,  0,  0,//a
                0,  0,  1,  0,  0,  0,//b
                0,  0,  0,  1,  0,  0,//c
                0,  0,  0,  0,  0,  0,//d
                0,  1,  0,  0,  0,  1,//e
                0,  0,  0,  1,  0,  0 //f
    };
    ALGraph G;
    CreateG(&G,6,6,vexNode,arc);
    printf("\n");
    TopologicalSort(&G);
//    PrintMG(G);
//    PrintGraph(G);
}