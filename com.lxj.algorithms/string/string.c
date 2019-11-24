//
// Created by 李学俊 on 2019/9/6.
//



#include <stdbool.h>

//顺序串存储结构定义
typedef struct {
    char data[100];//存放串字符
    int length;//串长
}SqString;

//生成串
void StrAssign(SqString *s, char cstr[]){
    int i;
    for (i = 0; cstr[i] != '\0' ; ++i) {
        s->data[i] = cstr[i];
    }
    s->length = i;
}
//销毁串
void DestroyStr(SqString *s){}//无操作

//复制串,将t复制给s
void StrCopy(SqString *s, SqString t){
    for (int i = 0; i < t.length; ++i) {
        s->data[i] = t.data[i];
    }
    s->length = t.length;
}
//判断串相等
bool StrEqual(SqString s, SqString t){
    if (s.length != t.length) {
        return false;
    }
    for (int i = 0; i < s.length; ++i) {
        if (s.data[i] != t.data[i]) {
            return false;
        }
    }
    return true;
}
//求串长
int StrLength(SqString s){
    return s.length;
}
//连接串
SqString Concat(SqString s, SqString t){
    SqString str;
    int i;
    str.length = s.length+t.length;
    for (i = 0; i < s.length; ++i) {
        str.data[i] = s.data[i];
    }
    for (i = 0; i < t.length; i++) {
        str.data[s.length+i] = t.data[i];
    }
    return str;
}
//求子串
SqString SubString(SqString s, int i, int j){
    int k;
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s.length || j < 0 || i + j - 1 > s.length) {
        return str;        //参数不正确返回空串
    }
    for (k = i-1; k < i+j-1; k++) {
        str.data[k-i+1] = s.data[k];
    }
    str.length = j;
    return str;
}
//子串的插入,将s2插入到s1的第i个位置上
SqString InsStr(SqString s1, int i, SqString s2){
    int j;
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s1.length + 1) {
        return str;
    }
    for (j = 0; j < i-1; ++j) {
        str.data[j] = s1.data[j];  //将s1.data[0,.,i-2]复制到str
    }
    for (j = 0; j < s2.length; j++) {
        str.data[i+j-1] = s2.data[j];   //将s2.data[0..s2.length-1]复制到str
    }
    for (j = i-1; j < s1.length; ++j) {
        str.data[s2.length+j] = s1.data[j];
    }
    str.length = s1.length + s2.length;
    return str;
}
//子串的删除,删除从第i个字符开始的长度为j的字串
SqString DelStr(SqString s, int i, int j){
    int k;
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s.length || i + j > s.length + 1) {
        return str;
    }
    for (k = 0; k < i-1; ++k) {
        str.data[k] = s.data[k];
    }
    for (k = 0; k < s.length; ++k) {
        str.data[k-j] = s.data[k];
    }
    str.length = s.length - j;
    return str;
}
//子串的替换,将第i个字符连续j个字符构成的子串用顺序串t替换
SqString RepStr(SqString s, int i, int j, SqString t){
    int k;
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s.length || i + j - 1 > s.length) {
        return str;
    }
    for (k = 0; k < i-1; ++k) {
        str.data[k] = s.data[k];
    }
    for (k = 0; k < t.length; ++k) {
        str.data[i+k-1] = t.data[k];
    }
    for (k = i+j-1; k < s.length; ++k) {
        str.data[t.length+k-j] = s.data[k];
    }
    str.length = s.length-j+t.length;
    return str;
}

//输出串
void DispStr(SqString s){
    if (s.length > 0) {
        for (int i = 0; i < s.length; ++i) {
            printf("%c", s.data[i]);
        }
    }
}

