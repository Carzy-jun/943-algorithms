//
// Created by 李学俊 on 2019/7/7.
//

//
//用标记tag来区分队满和队空
#define MaxSize 50
typedef struct {
    int data[MaxSize];
    int rear,front,tag;//tag为0时队空，为1时队满
}TagQueue;

void InitQueue(TagQueue *Q){
    Q->rear = Q->front = Q->tag = 0;
}
void EnQueue(TagQueue *Q, int x){
    if (Q->tag == 1 && Q->rear == Q->front){
        printf("队已满");
    } else{
        Q->data[Q->rear] = x;
        Q->rear = (Q->rear+1)%MaxSize;
        Q->tag = 1;
    }
}
void DeQueue(TagQueue *Q, int *x){
    if (Q->tag == 0 && Q->front == Q->rear){
        printf("队空");
    } else{
        *x = Q->data[Q->front];
        Q->front = (Q->front+1)%MaxSize;
        Q->tag = 0;
    }
}
void main(){
    int a[] = {3,3,3,1,1},x;
    TagQueue Q;InitQueue(&Q);
    for (int i = 0; i < 5; ++i) {
        EnQueue(&Q,a[i]);
    }
    for (int j = 0; j < 5; ++j) {
        DeQueue(&Q, &x);
        printf("%d\t",x);
    }
};