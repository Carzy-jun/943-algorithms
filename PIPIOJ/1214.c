//
// Created by 李学俊 on 2019/10/13.
//
/*
 * 逆置顺序表
 */
typedef struct SqList{
    int data[100];
    int length;
}SqList;

SqList CreateSqList(SqList *L, int len){
    for (int i = 0; i < len; ++i) {
        int a;
        scanf("%d", &a);
        L->data[i] = a;
    }
    L->length = len;
    return *L;
}
void Reverse(SqList *L){
    int temp;
    int n = L->length/2;
    for (int i = 0; i < n; ++i) {
        temp = L->data[i];
        L->data[i] = L->data[L->length-i-1];
        L->data[L->length-i-1] = temp;
    }
}
void PrintList(SqList L){
    for (int i = 0; i < L.length; ++i) {
        printf("%d",L.data[i]);
    }
}
int main(){
    int len;
    scanf("%d",&len);
    SqList L = CreateSqList(&L,len);
    Reverse(&L);
    PrintList(L);
    return 0;
}
