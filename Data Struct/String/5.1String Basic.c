#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef char String[MAX + 1];

//生成一个其值等于chars的串T
void ProduceString(String S, char *chars) //利用指针变量指向字符串！
{
    if (strlen(chars) > MAX)
        printf("字符串生成错误！\n");
    else
    {
        int i;
        S[0] = strlen(chars);
        for (i = 1; i <= S[0]; i++)
        {
            S[i] = *(chars + i - 1);
        }
        printf("内部字符串生成完毕。\n");
    }
}

//由串S复制得串T
void CopyString(String S, String T)
{
    int i;
    for (i = 0; i <= S[0]; i++) //别忘了数组长度也复制过去
    {
        T[i] = S[i];
    }
}

//从键盘获得字符串R
void GetString(String R)
{
    String T;
    printf("请输入一个长度不大于20的字符！\n");
    fgets(T, MAX, stdin); //长度大于MAX的字符将被舍弃
    R[0] = strlen(T) - 1; // fget()函数会把换行符放到字符串的结尾，所以此处减一
    int i;
    for (i = 0; i <= R[0]; i++)
        R[i + 1] = T[i];
    printf("外部字符串生成完毕。\n");
}

//返回串的元素个数
void StringLength(String S)
{
    printf("字符串中的元素个数是%d。\n", S[0]);
}

//输出字符串T
void PrintString(String S)
{
    int i;
    printf("字符串中的字符有：\n");
    for (i = 1; i <= S[0]; i++)
    {
        printf("%c\n", S[i]);
    }
}

/**********************主函数*********************/
void main()
{
    String S, T, R;
    ProduceString(S, "ascdsf"); //生成一个其值等于chars的串T
    StringLength(S);            //返回串的元素个数
    PrintString(S);             //输出字符串的所有字符

    CopyString(S, T); //由串S复制得串T
    StringLength(T);  //返回串的元素个数
    PrintString(T);   //输出字符串的所有字符

    GetString(R);    //从键盘获得字符串R
    StringLength(R); //返回串的元素个数
    PrintString(R);  //输出字符串的所有字符（注意包含了换行符！）
    //可以用fputs(R, stdout);//与fgets()搭配使用，不会输出换行符，但是首字符（字符串长度）也输出了
}
