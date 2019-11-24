//
// Created by 李学俊 on 2019/10/25.
//
/*
 * 相邻相同字母删除
 * 找到文本中两个相邻并且相同的字母，然后删除它们。注意这个过程是递归的，比如:
    "abbac"->"aac"->"c"。
 */

int main(){
    char s[11];
    gets(s);
    for (int i = 0; s[i] != '\0' ; ++i) {
        if (s[i] == s[i + 1]) {
            for (int j = i; s[j]!='\0'; ++j) {
                s[j] = s[j+2];
                s[j+1] = s[j+3];
            }
            i=-1;
        }
    }
    puts(s);
    return 0;
}