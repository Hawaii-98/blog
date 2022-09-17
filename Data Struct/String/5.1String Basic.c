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

//比较两个字符串的大小,不相等则提示！
int CompareString(String T, String S)
{
    if (T[0] > S[0])
    {
        printf("第一个字符串更大！\n");
    }
    else
    {
        if (T[0] < S[0])
        {
            printf("第二个字符串更大！\n");
        }
        else
        {
            int i = 1;
            while (T[i] == S[i])
            {
                i++;
            }
            if (T[i] > S[i])
            {
                printf("第一个字符串更大！\n");
            }
            else
            {
                printf("第二个字符串更大！\n");
            }
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

//返回子串T在主串S中第pos个字符之后的位置。若不存在,则打印提示。
int Index(String S, String T, int pos)
{
    int i = pos;                   // i用于主串的遍历
    int j = 1;                     // j用于子串的遍历
    while (i <= S[0] && j <= T[0]) // 若i小于S的长度并且j小于T的长度时，循环继续
    {
        if (S[i] == T[j]) // 两字符相等则继续
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1 + 1; // i退回到上次匹配首位的下一位(再加1)---注意此处不可以是i = i - pos + 1，因为i是从破事开始递增的！！，而且i之前已经被赋值为pos，会导致语法错误！！
            j = 1;             // j退回到子串T的首位
        }
    }
    if (j > T[0])
    {
        printf("待查找子串的位置是：%d！\n", i - T[0]);
        return i - T[0];
    }
    else
    {
        printf("找不到该字符串！\n");
    }
}

// T为非空串。若主串S中第pos个字符之后存在与T相等的子串，
//则返回第一个这样的子串在S中的位置，否则打印提示。
void Index2(String S, String T, int pos)
{
    int i;
    String sub;
    if (pos > 0)
    {
        i = pos;
        while (i <= S[0] - T[0] + 1)
        {
            int j;
            int k = 0;
            SubString(sub, S, i, T[0]);
            for (j = 1; j <= sub[0] && j <= T[0]; ++j) //比较两个字符串是否相等（默认相等，为零）
                if (sub[j] != T[j])
                    k = 1; //比较两个字符串是否相等，若不等，k=1;
            if (k == 1)    //如果两串不相等
            {
                i++;
            }
            else
            {
                printf("第一个子串在S中的位置为：%d!\n", i);
                break; //及时跳出循环！！否则死循环！
            }
        }
    }
    else
        printf("输入不正确!\n");
}

//在串S的第pos个字符之前插入串T。插入位置不正确或完全插入或者部分插入都返回提示
void InsertString(String S, String T, int pos)
{
    if (pos < 1 || pos > MAX)
        printf("插入位置不正确！\n");
    else
    {
        int i = pos;
        if (S[0] + T[0] <= MAX) //完全插入
        {
            for (i = S[0]; i >= pos; i--)
            {
                S[T[0] + i] = S[i];
            }
            for (i = 1; i <= T[0]; i++)
            {
                S[pos + i - 1] = T[i];
            }
            S[0] = S[0] + T[0];
            printf("字符串已完全插入！\n");
        }
        else //部分插入------此程序存在问题
        {
            for (i = MAX; i <= pos; i--)
            {
                S[i] = S[i - T[0]]; //仅此处与上面的不同！但思路相同！！
            }
            for (i = pos; i < pos + T[0]; i++)
                S[i] = T[i - pos + 1];
            S[0] = MAX;
            printf("字符串已部分插入！\n");
        }
    }
}

//从串S中删除第pos个字符起长度为len的子串
void DeleteString(String S, int pos, int len)
{
    if (pos < 1 || len < 0 || pos + len - 1 > S[0])
        printf("输入参数有误！\n");
    else
    {
        int i;
        for (i = pos + len; i <= S[0]; i++) //从删除的位置直到最后，每个字符依次向前挪len长度
        {
            S[i - len] = S[i];
        }
        S[0] = S[0] - len;
        printf("设定的字符串已删除！\n");
    }
}

//用V替换主串S中出现的所有与T相等的不重叠的子串
void Replace(String S, String T, String V)
{
    int i = 1; // 从串S的第一个字符起查找串T
    if (T[0] == 0)
        printf("子串为空！\n");
    else
    {
        do
        {
            i = Index(S, T, i); //  结果i为从上一个i之后找到的子串T的位置
            if (i)
            {
                DeleteString(S, i, T[0]); //  删除该串T
                InsertString(S, V, i);    //  在原串T的位置插入串V
                i += V[0];                //  在插入的串V后面继续查找串T
            }
        } while (i);
        printf("替换已完成！\n");
    }
}

/**********************主函数*********************/
void main()
{
    String S, T, R, T1, S1, X, Sub, A, B, S2, T2, V;
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

    ProduceString(S1, "ascdsrtrtrt"); //生成一个其值等于chars的串
    ProduceString(T1, "trtiu");       //生成一个其值等于chars的串
    CompareString(S1, T1);            //比较两个字符串的大小

    ContactString(X, S1, T1); //连接S1，T1之后赋值给X
    StringLength(X);          //返回串的元素个数
    PrintString(X);           //输出字符串的所有字符

    ClearString(S); //清空字符串
    PrintString(S); //输出字符串的所有字符

    SubString(Sub, X, 4, 5); //用Sub返回串S的第pos个字符起长度为len的子串
    PrintString(Sub);        //输出字符串的所有字符

    Index(X, T1, 3); //返回子串T在主串S中第pos个字符之后的位置。若不存在,则打印提示。
    printf("Index函数的返回值为：%d\n", Index(X, T1, 3));
    Index2(X, T1, 2); //若主串S中第pos个字符之后存在与T相等的子串，则返回第一个这样的子串在S中的位置，否则打印提示

    ProduceString(A, "ascdsf"); //生成一个其值等于chars的串T
    ProduceString(B, "ascef");  //生成一个其值等于chars的串T

    InsertString(A, B, 4); //在串S的第pos个字符之前插入串T。插入位置不正确或完全插入或者部分插入都返回提示
    PrintString(A);        //输出字符串的所有字符

    DeleteString(A, 2, 3); //从串S中删除第pos个字符起长度为len的子串
    PrintString(A);        //输出字符串的所有字符

    printf("--------------我是分割线----------------\n"); //分割线
    ProduceString(S2, "tratoitroitroirttr");              //生成一个其值等于chars的串
    ProduceString(T2, "tr");                              //生成一个其值等于chars的串
    ProduceString(V, "xx");                               //生成一个其值等于chars的串
    Replace(S2, T2, V);                                   //用V替换主串S中出现的所有与T相等的不重叠的子串
    PrintString(S2);                                      //输出字符串的所有字符
}
