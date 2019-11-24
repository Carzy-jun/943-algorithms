//
// Created by 李学俊 on 2019/8/4.
//

#include "../stackAndQueue/StackAndQueue.c"
#include "../sort/sort.c"
#include "../union-find/Union-find.c"



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
    SqStack S;
    InitStack(&S);
    int k;
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    Push(&S, v);
    visited[v] = true;
    while (!StackEmpty(S)) {
        Pop(&S, &k);
        printf("%c\t", G.vertices[k].data);     //先访问，再将其所有子节点入栈
        for (int i = FirstNeighbor(G, k); i >= 0; i = NextNeighbor(G, k, i)) {
            if (!visited[i]) {              //未进过栈的顶点入栈
                Push(&S, i);
                visited[i] = true;          //做标记，以免再次入栈
            }
        }
    }
}
//分别采用基于深度优先和广度优先算法判别有向图中是否存在由顶点vi 到 vj(vi!=vj)的路径
//1.基于深度优先
bool BFS_HasRoad(ALGraph G, int v1, int v2) {
    if (v1 == v2) return true;
    visited[v1] = true;
    for (int i = FirstNeighbor(G, v1); i >= 0; i = NextNeighbor(G, v1, i)) {
        if (!visited[i]) {
            return BFS_HasRoad(G, i, v2);
        }
    }
    return false;
}

bool HasRoad(ALGraph G, int v1, int v2) {
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    return BFS_HasRoad(G, v1, v2);
}
//2.基于广度优先
bool HasRoad1(ALGraph G, int v1, int v2) {
    for (int i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    Queue *Q = InitQueue();
    EnQueue(Q, v1);
    while (!IsEmpty(Q)) {
        DeQueue(Q, &v1);
        if (v1 == v2) return true;
        visited[v1] = true;
        for (int v = FirstNeighbor(G, v1); v >= 0; v = NextNeighbor(G, v1, v)) {
            if (!visited[v])
                EnQueue(Q, v);
        }
    }
    return false;
}

//输出从顶点vi到顶点vj的所有简单路径
void PrintPath(ALGraph G, int v1, int v2, int path[], int d) {
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

void FindPath(ALGraph G, int v1, int v2) {
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    int *a = (int *) malloc(G.vexnum * sizeof(int));
    PrintPath(G, v1, v2, a, -1);
}

//Prim算法的原理是在开始时选取一个节点最为其实节点，然后遍历所有该节点链接的边，
// 并选取其中权重最小的边，同时将已经选取的节点标位已知；接下来重复之前的步骤，
// 在已知节点的链接的边中选取权重最小的边，同时将其所链接的边标位已知，一直这样操作，
// 直到所有的节点都已知。(PS:在实际代码中，我们使用一个表格来储存生成树的信息)
void Prim(ALGraph G) {
    ArcNode *p;
    int v = 0, w;
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }
    ALGraph *Min_tree = (ALGraph *) malloc(sizeof(ALGraph));
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
void prim(MGraph G, int v) {
    int lowcost[MaxVertexNum];
    int MIN;
    int closest[MaxVertexNum], i, j, k = 0;
    for (i = 0; i < G.vexnum; i++) { //初始化lowcost,closest
        lowcost[i] = G.Edge[v][i];
        closest[i] = v;
    }
    for (i = 1; i < G.vexnum; i++) {
        MIN = M;
        for (j = 0; j < G.vexnum; ++j) {
            if (lowcost[j] != 0 && lowcost[j] < MIN) {
                MIN = lowcost[j];
                k = j;
            }
        }
        printf("边(%c,%c)权为：%d\n", G.Vex[closest[k]], G.Vex[k], MIN);
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
} Edge;

void Insertsort1(Edge a[], int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 && a[j - 1].wight > a[j].wight; --j) {
            Edge t = a[j];
            a[j] = a[j - 1];
            a[j - 1] = t;
        }
    }
}

//Kruskal算法
void Kruskal(MGraph G) {
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
    Insertsort1(E, G.arcnum);
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
            printf("边(%c,%c):权值为:%d\n", G.Vex[start1], G.Vex[end1], E[j].wight);
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

void Kruskal1(MGraph G) {
    int i, j, k, sn1, sn2, start1, end1;
    UFSTree t[MaxSize];
    Edge E[MaxSize];
    k = 0;
    for (i = 0; i < G.vexnum; i++) {
        for (j = 0; j <= i; j++) {
            if (G.Edge[i][j] != 0 && G.Edge[i][j] != M) {
                E[k].start = i;
                E[k].end = j;
                E[k].wight = G.Edge[i][j];
                k++;
            }
        }
    }
    Insertsort1(E, G.arcnum);
    MAKE_SET(t, G.vexnum);
    k = 1;
    j = 0;
    while (k < G.vexnum) {
        start1 = E[j].start;
        end1 = E[j].end;
        sn1 = FIND_SET(t, start1);
        sn2 = FIND_SET(t, end1);
        if (sn1 != sn2) {
            printf("边(%c,%c):权值为:%d\n", G.Vex[start1], G.Vex[end1], E[j].wight);
            k++;
            UNION(t, start1, end1);
        }
        j++;
    }
}

//dijkstra算法求单源最短路径
//输出
void Dispath(MGraph G, int dist[], const int path[], const int S[], int v) {//输出单源最短路径
    int i, j, k;
    int apath[MaxVertexNum], d;
    for (i = 0; i < G.vexnum; ++i) {
        if (S[i] == 1 && i != v) {
            printf("从顶点%c到顶点%c的路径长度为:%d\t", G.Vex[v], G.Vex[i], dist[i]);
            d = 0;
            apath[d] = i;
            k = path[i];
            if (k == -1) {
                printf("无路径\n");
            } else {
                while (k != v) {
                    d++;
                    apath[d] = k;
                    k = path[k];
                }
                d++;
                apath[d] = v;
                printf("%d", apath[d]);
                for (j = d - 1; j >= 0; --j) {
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
//输出
void DispathFd(MGraph G, int A[][MaxVertexNum], int path[][MaxVertexNum]) {
    int i, j, k, s;
    int apath[MaxVertexNum], d;
    for (i = 0; i < G.vexnum; ++i) {
        for (j = 0; j < G.vexnum; ++j) {
            if (A[i][j] != M && i != j) {
                printf("从%c到%c的路径为：", G.Vex[i], G.Vex[j]);
                k = path[i][j];
                d = 0;
                apath[d] = j;
                while (k != -1 && k != i) {
                    d++;
                    apath[d] = k;
                    k = path[i][k];
                }
                d++;
                apath[d] = i;
                printf("%d", apath[d]);
                for (s = d - 1; s >= 0; --s) {
                    printf(",%d", apath[s]);
                }
                printf("\t路径长度为：%d\n", A[i][j]);
            }
        }
    }
}

void Floyd(MGraph G) {
    int A[MaxVertexNum][MaxVertexNum], path[MaxVertexNum][MaxVertexNum];
    int i, j, k;
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
                    A[i][j] = A[i][k] + A[k][j];     //修改最短路径长度
                    path[i][j] = path[k][j];        //修改最短路径
                }
            }
        }
    }
    DispathFd(G, A, path); //输出
}


//拓扑排序
bool TopologicalSort(ALGraph *G) {
    SqStack S;
    InitStack(&S); //存储入度为0的顶点
    int indegree[G->vexnum], i, j, count = 0;//count用来判断是否所有顶点是否拓扑排序成功
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
            Push(&S, i);
            count++;
        }
    }
    while (!StackEmpty(S)) {    //栈不为空循环
        Pop(&S, &i);     //出栈一个顶点
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
int ve[100], vl[100];//最早发生时间和最迟发生时间数组，全局的

bool Topo(ALGraph *G, SqStack *T)//对各顶点求入度，邻接矩阵的列
{
    SqStack *S = (SqStack*)malloc(sizeof(SqStack)); InitStack(S);
    int count = 0,e,j;
    ArcNode *p;
    int indegree[G->vexnum];
    memset(indegree,0, sizeof(indegree));//初始化所有顶点入度
    memset(ve,0, sizeof(ve));   //初始化每个事件最早发生时间
    for (int i = 0; i < G->vexnum; ++i) {//求所有顶点的入度
        p = G->vertices[i].first;
        while (p) {
            indegree[p->adjvex]++;
            p = p->next;
        }
    }
    for (int i = 0; i < G->vexnum; ++i) {//入度为0节点进栈
        if (indegree[i] == 0) {
            Push(S,i);
            count++;
        }
    }
    while (!StackEmpty(*S)) {
        Pop(S,&e);
        Push(T,e);  //把逆拓扑排序顺序的顶点存入栈T中
        for (p = G->vertices[e].first; p; p = p->next) {
            j = p->adjvex;
            if (--indegree[j] == 0) {
                Push(S,j);
                count++;
            }
            if (ve[e] + p->info > ve[j]) {  //求每个顶点的最早发生时间
                ve[j] = ve[e] + p->info;
            }
        }
    }
    return count == G->vexnum;
}
int CriticalPath(ALGraph *G)//求关键路径，适合图中关键路径唯一
{
    int e; ArcNode *p;
    SqStack *T =(SqStack*)malloc(sizeof(SqStack));InitStack(T);
    if (!Topo(G,T)) {
        printf("图存在环，无关键路径");
        return 0;
    }
    for (int i = 0; i < G->vexnum; ++i) { //初始化每个顶点的最迟发生时间
        vl[i] = ve[G->vexnum-1];
    }
    while (!StackEmpty(*T)) {
        Pop(T,&e);
        p = G->vertices[e].first;
        while (p) {
            if (vl[p->adjvex] - p->info < vl[e]) {
                vl[e] = vl[p->adjvex] - p->info;
            }
            p = p->next;
        }
    }
    printf("关键路径上的顶点为：\n");
    for (int i = 0; i < G->vexnum; ++i) {
        p = G->vertices[i].first;
        while (p) {
            int k = p->adjvex, a = p->info;
            int eei = ve[i],eli = vl[k]-a;
            if (eei == eli) {
                printf("%c\t",G->vertices[i].data);
            }
            p = p->next;
        }
    }
    return 1;
}

int main() {
    ALGraph G;
    char vexNode[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int arc[][6] = {
            //  a   b   c   d   e   f
                0,  1,  1,  0,  0,  0,//a
                0,  0,  0,  1,  0,  0,//b
                0,  0,  0,  1,  0,  0,//c
                0,  0,  0,  0,  1,  0,//d
                0,  0,  0,  0,  0,  1,//e
                0,  0,  0,  0,  0,  0 //f
    };
//  CreateG(&G);
    CreateG(&G, 6, 6, vexNode, arc);
    Set_Info(&G);
    CriticalPath(&G);
//    PrintGraph(G);
//    char vexNode[] = {'a', 'b', 'c', 'd', 'e', 'f'};
//    int arc[][6] = {
//            //  a   b   c   d   e   f
//            0, 3, 1, 5, M, M,//a
//            3, 0, 8, M, 3, M,//b
//            1, 8, 0, 7, 6, 4,//c
//            5, M, 7, 0, M, 2,//d
//            M, 3, 6, M, 0, 6,//e
//            M, M, 4, 2, 6, 0 //f
//    };
//    MGraph G;
//    CreateMG(&G, 6, 10, vexNode, arc);
//    int arc[][6] = {
//            //  a   b   c   d   e   f
//                0,  1,  0,  0,  0,  0,//a
//                0,  0,  1,  0,  0,  0,//b
//                0,  0,  0,  1,  0,  0,//c
//                0,  0,  0,  0,  0,  0,//d
//                0,  1,  0,  0,  0,  1,//e
//                0,  0,  0,  1,  0,  0 //f
//    };
//    ALGraph G;
//    CreateG(&G,6,6,vexNode,arc);
//    printf("\n");
//    TopologicalSort(&G);
//    PrintMG(G);
//    PrintGraph(G);
}