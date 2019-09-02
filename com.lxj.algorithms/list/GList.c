//
// Created by 李学俊 on 2019/8/19.
//

//广义表结构定义
typedef enum {
    ATOM,LIST
} ElemTag;  //ATOM==0:表示原子,LIST==1:表示子表
typedef struct GLNode {
    ElemTag  tag;  //公共部分，用以区分原子部分和表结点
    union {       //原子部分和表结点的联合部分
        int  atom; //atom是原子结点的值域,AtomType由用户定义
        struct {
            struct GLNode *hp, *tp;
        } ptr;
        // ptr是表结点的指针域,ptr.hp 和ptr.tp分别指向表头和表尾
    };
} *Glist;  //广义表类型