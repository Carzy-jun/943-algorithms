//
// Created by 李学俊 on 2019/11/23.
//
//这是树吗?

int main(){
    int k = 0,a[1001],indegree[1001],i,j,arcnum= 0, vexnum= 0,flag=1;
    memset(a,0, sizeof(a));
    memset(indegree,0, sizeof(indegree));
    while (1) {
        scanf("%d%d",&i,&j);
        if (i == -1 && j == -1) break;
        if (i != 0 && j != 0) {
            arcnum++;
            if (a[i] == 0) {
                a[i]=1;
                vexnum++;
            }
            if (a[j] == 0) {
                a[j]=1;
                vexnum++;
            }
            if (++indegree[j] > 1) {
                flag = 0;
            }
        } else {
            if (vexnum - 1 == arcnum && flag) {
                printf("Case %d is a tree.\n",++k);
            } else {
                printf("Case %d is not a tree.\n",++k);
            }
            memset(a,0, sizeof(a));
            memset(indegree,0, sizeof(indegree));
            flag = 1;
            arcnum = 0;
            vexnum = 0;
        }
    }
    return 0;
}