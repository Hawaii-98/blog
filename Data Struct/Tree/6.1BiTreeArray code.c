#include <stdio.h>
#include <string.h>

#define MAX 20
//定义一个数组用以存储二叉树
// int SqBiTree[MAX];注意不要这样定义，因为后续无法用
// SqBiTree定义数组！！
typedef int SqBiTree[MAX];

//创建结点位置结构体
typedef struct
{
    int level, order;
} Position;

int Nil = ' '; //设字符型以空格符为空，记得加单引号！！

//构造空二叉树
int InitSqBiTree(SqBiTree T)
{
    int i;
    for (i = 0; i < MAX; i++) //此处不能=max，因为数组从零开始
    {
        T[i] = Nil;
    }
    printf("空二叉树已构造！\n");
}

//按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T
int CreatBiTree(SqBiTree T)
{
    int i;
    printf("请按层序输入结点的值(字符型)，0表示空结点，输入回车结束。结点数≤%d:\n", MAX);
    char s[MAX];
    int length;
    gets(s);
    length = strlen(s);
    if (length > MAX)
    {
        printf("输入数据过长，多余部分将被截断！\n");
        for (i = 0; i < MAX; i++)
        {
            T[i] = s[i];
            if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil)
            {
                printf("出现无双亲的非根结点%c\n", T[i]);
                exit(0);
            }
        }
    }
    else
    {
        for (i = 0; i < length; i++)
        {
            T[i] = s[i];
            if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil) //由于i是整形，所以最后表达式(i + 1) / 2 - 1的值会截掉小数部分
                                                                    //注意此处的表达式在函数中的作用应等价于i/2!
            {
                printf("出现无双亲的非根结点%c\n", T[i]);
                exit(0);
            }
        }
        for (i = length; i < MAX; i++)
        {
            T[i] = Nil;
        }
    }
}

//逐个输出树的结点
void PrintTree(SqBiTree T)
{
    int i;
    printf("输出树的结点为：\n");
    for (i = 0; i < MAX; i++)
    {
        printf("%c", T[i]);
    }
}

//清空树
#define ClearTree InitSqBiTree

//判断二叉树是否为空
void BiTreeEmpty(SqBiTree T)
{
    if (T[0] == Nil)
    {
        printf("二叉树为空！\n");
    }
    else
    {
        printf("二叉树非空！\n");
    }
}

/***************主函数***************************/
int main()
{
    SqBiTree T;
    InitSqBiTree(T); //构造空二叉树

    CreatBiTree(T); //按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T
    PrintTree(T);   //逐个输出树的结点

    ClearTree(T);   //清空树
    BiTreeEmpty(T); //判断二叉树是否为空
}
