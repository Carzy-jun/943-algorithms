#include <stddef.h>
#include <stdbool.h>

//
// Created by 李学俊 on 2019/11/2.
//
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

bool TopologicalSort(ALGraph *G){
    st *S = (st*)malloc(sizeof(st));S->top = -1;
    int indegree[G->vexnum+1],i,j, count = 0;
    ArcNode *p;
    for (i = 1; i < G->vexnum+1; ++i)
        indegree[i] = 0;
    for (i = 1; i < G->vexnum+1; ++i) {
        p = G->vertices[i].first;
        while (p) {
            indegree[p->adjvex]++;
            p = p->next;
        }
    }
    for (i = 1; i < G->vexnum+1; ++i) {
        if (indegree[i] == 0) {
            S->data[++S->top] = i;
            count++;
        }
    }
    while (S->top!=-1) {
        i = S->data[S->top--];
        p = G->vertices[i].first;
        while (p) {
            j = p->adjvex;
            indegree[j]--;
            if (indegree[j] == 0) {
                S->data[++S->top] = j;
                count++;
            }
            p = p->next;
        }
    }
    return count != G->vexnum;
}
int main(){
    ALGraph G;
    Create(&G);
    if (TopologicalSort(&G)) {
        printf("yes");
    } else {
        printf("no");
    }
}