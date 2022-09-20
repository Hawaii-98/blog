#include <stdio.h>
#include <string.h>

#define MAX 40

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
        printf("字符串生成完毕。\n");
    }
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

//输出next数组
void PrintNext(int next[], int length)
{
    int i;
    printf("next数组为：\n");
    for (i = 1; i < length; i++) // next数组从1开始存储！！
    {
        printf("%d", next[i]);
    }
    printf("\n");
}

//朴素的模式匹配法---返回子串在主串中pos之后第一次出现的位置
void Index(String S, String T, int pos)
{
    int i = pos;
    int j = 1;
    while (i <= S[0] && j <= T[0]) //因为要遍历，所以用到了循环，此处可以取到等号
    {
        if (S[i] == T[j]) //两字母相等，指针后移
        {
            i++;
            j++;
        }
        else //两字母不相等，指针回溯，重新开始匹配。
        {
            i = i - j + 2; // i退回到主串上次匹配首位的下一位
            j = 1;         // j退回到子串T的首位
        }
    }
    if (j > T[0]) //如果退出循环的原因是子串已经循环完毕
    {
        printf("该子串在主串中的位置为：%d\n", i - T[0]);
    }
    else
    {
        printf("该子串在主串中不存在！\n");
    }
}

//求解next数组
void getnext(String T, int *next)
{
    int i, j;
    i = 1;
    j = 0;
    next[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j]; // j的回溯
        }
    }
}

// kmp算法
void kmp(String S, String T, int pos)
{
    int i = pos;      // i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配
    int j = 1;        // j用于子串T中当前位置下标值
    int next[255];    //定义一next数组
    getnext(T, next); //对串T作分析，得到next数组

    while (i <= S[0] && j <= T[0]) //注意这里一定是两个条件都满足才能进入到循环体！！
    {
        if (j == 0 || S[i] == T[j]) //两字母相等则继续，与朴素算法增加了j=0判断
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j]; // j退回合适的位置，i值不变
        }
    }
    if (j > T[0])
    {
        printf("子串匹配成功，位置为%d！\n", i - T[0]);
    }
    else
    {
        printf("无匹配子串！\n");
    }
}

//求解nextval数组
void getnextval(String T, int *nextval)
{
    int i, j;
    i = 1;
    j = 0;
    nextval[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            if (T[i] != T[j])
            {
                nextval[i] = j;
            }
            else
            {
                nextval[i] = nextval[j];
            }
        }
        else
        {
            j = nextval[j]; // j的回溯
        }
    }
}

//改进的kmp算法
void betterkmp(String S, String T, int pos)
{
    int i = pos;         // i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配
    int j = 1;           // j用于子串T中当前位置下标值
    int nextval[255];    //定义一next数组
    getnext(T, nextval); //对串T作分析，得到next数组

    while (i <= S[0] && j <= T[0]) //注意这里一定是两个条件都满足才能进入到循环体！！
    {
        if (j == 0 || S[i] == T[j]) //两字母相等则继续，与朴素算法增加了j=0判断
        {
            ++i;
            ++j;
        }
        else
        {
            j = nextval[j]; // j退回合适的位置，i值不变
        }
    }
    if (j > T[0])
    {
        printf("子串匹配成功，位置为%d！\n", i - T[0]);
    }
    else
    {
        printf("无匹配子串！\n");
    }
}

/*************************主函数*********************************/
void main()
{
    String S, T;
    ProduceString(S, "aaaaaaaaaasdfgaaaaaaaaaaashetas");
    ProduceString(T, "aaaaaaaash");
    Index(S, T, 2); //朴素的模式匹配法
    int next[255];
    getnext(T, next);
    PrintNext(next, T[0]);
    kmp(S, T, 2); // kmp算法

    int nextval[255];
    getnextval(T, nextval);
    PrintNext(nextval, T[0]);
    betterkmp(S, T, 2); //改进的kmp算法
}
