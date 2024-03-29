//
// Created by 李学俊 on 2019/7/12.
//
#ifndef Queue_H
#define Queue_H
#include "../treeAndBtree/bTree.c"

typedef int Item;
typedef struct Qnode * PNode;
typedef struct Qnode
{
    Item data;
    PNode next;
}Node;

typedef struct
{
    PNode front;
    PNode rear;
    int size;
}Queue;

/*构造一个空队列*/
Queue *InitQueue();

/*销毁一个队列*/
void DestroyQueue(Queue *pqueue);

/*清空一个队列*/
void ClearQueue(Queue *pqueue);

/*判断队列是否为空*/
int IsEmpty(Queue *pqueue);

/*返回队列大小*/
int Size(Queue *pqueue);

/*返回队头元素*/
PNode GetFront(Queue *pqueue,Item *pitem);

/*返回队尾元素*/
PNode GetRear(Queue *pqueue,Item *pitem);

/*将新元素入队*/
PNode EnQueue(Queue *pqueue,Item item);

/*队头元素出队*/
PNode DeQueue(Queue *pqueue,Item *pitem);

/*遍历队列并对各数据项调用visit函数*/
void QueueTraverse(Queue *pqueue,void (*visit)());

#endif
