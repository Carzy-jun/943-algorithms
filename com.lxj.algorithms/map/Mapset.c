//
// Created by 李学俊 on 2019/11/2.
//
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
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