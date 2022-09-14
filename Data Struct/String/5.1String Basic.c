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
    if (S[0] == 0)
        printf("待输出的字符串为空！\n");
    else
    {
        int i;
        printf("字符串中的字符有：\n");
        for (i = 1; i <= S[0]; i++)
        {
            printf("%c\n", S[i]);
        }
    }
}

//比较两个字符串的大小
void CompareString(String T, String S)
{
    if (T[0] > S[0])
        printf("第一个字符串更大！\n");
    else
    {
        if (T[0] < S[0])
            printf("第二个字符串更大！\n");
        else
        {
            int i = 1;
            while (T[i] == S[i])
            {
                i++;
            }
            if (T[i] > S[i])
                printf("第一个字符串更大！\n");
            else
                printf("第二个字符串更大！\n");
        }
    }
}

//用T返回S1和S2联接而成的新串。并对截断情况打印提示
void ContactString(String T, String S1, String S2)
{
    if (S1[0] + S2[0] > MAX) //说明连接之后要被截断了
    {
        int i, j;
        for (i = 1; i <= S1[0]; i++)
        {
            T[i] = S1[i];
        }
        for (j = 1; j <= MAX - S1[0]; j++)
        {
            T[S1[0] + j] = S2[j];
        }
        T[0] = MAX;
        printf("字符串已连接，超出部分被截断。\n");
    }
    else //连接之后也没有被截断
    {
        int i, j;
        for (i = 1; i <= S1[0]; i++)
        {
            T[i] = S1[i];
        }
        for (j = 1; j <= S2[0]; j++)
        {
            T[S1[0] + j] = S2[j];
        }
        T[0] = S1[0] + S2[0];
        printf("字符串已连接，未被截断。\n");
    }
}

//清空字符串
void ClearString(String S)
{
    S[0] = 0;
    printf("字符串已清空！\n");
}

//用Sub返回串S的第pos个字符起长度为len的子串
void SubString(String Sub, String S, int pos, int len)
{
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        printf("输入的参数有错误！\n");
    else
    {
        int i;
        for (i = 1; i <= len; i++)
        {
            Sub[i] = S[pos + i - 1];
        }
        Sub[0] = len;
    }
}

/**********************主函数*********************/
void main()
{
    String S, T, R, T1, S1, X, Sub;
    ProduceString(S, "ascdsf"); //生成一个其值等于chars的串T
    StringLength(S);            //返回串的元素个数
    PrintString(S);             //输出字符串的所有字符

    CopyString(S, T); //由串S复制得串T
    StringLength(T);  //返回串的元素个数
    PrintString(T);   //输出字符串的所有字符

    // GetString(R);    //从键盘获得字符串R
    // StringLength(R); //返回串的元素个数
    // PrintString(R);  //输出字符串的所有字符（注意包含了换行符！）
    //可以用fputs(R, stdout);//与fgets()搭配使用，不会输出换行符，但是首字符（字符串长度）也输出了

    ProduceString(S1, "ascdsrtrtrtt"); //生成一个其值等于chars的串T
    ProduceString(T1, "asddsfpopo");   //生成一个其值等于chars的串T
    CompareString(S1, T1);             //比较两个字符串的大小

    ContactString(X, S1, T1); //连接S1，T1之后赋值给X
    StringLength(X);          //返回串的元素个数
    PrintString(X);           //输出字符串的所有字符

    ClearString(S); //清空字符串
    PrintString(S); //输出字符串的所有字符

    SubString(Sub, X, 4, 5); //用Sub返回串S的第pos个字符起长度为len的子串
    PrintString(Sub);        //输出字符串的所有字符

    
}
