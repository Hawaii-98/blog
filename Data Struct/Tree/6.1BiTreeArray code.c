#include <stdio.h>
#include <string.h>
#include <math.h >

#define MAX 80
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
                                                                    //注意此处的表达式不可以是i/2!，因为数组从0开始存储，所以要做相应的位移
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
int BiTreeEmpty(SqBiTree T)
{
    if (T[0] == Nil)
    {
        printf("二叉树为空！\n");
        return 0;
    }
    else
    {
        printf("二叉树非空！\n");
        return 1;
    }
}

//计算树的深度
int BiTreeDepth(SqBiTree T)
{
    int i, lastone, Depth;
    for (i = MAX - 1; i >= 0; i--) //注意i从max-1 开始遍历！！
                                   //注意找树的最后一个结点一定是从后向前找空结点！
    {
        if (T[i] != Nil)
        {
            lastone = i + 1; //记录最后一个元素的位置(此处+1因为数组中的位置是从0开始的！)
            break;
        }
    }
    Depth = (int)log2(lastone) + 1; //树的深度计算公式
    printf("树的深度为：%d\n", Depth);
    return Depth;
}

//如果树不空，返回树的根
void GetRoot(SqBiTree T)
{
    if (BiTreeEmpty(T) == 0)
    {
        printf("二叉树为空！\n");
    }
    else
    {
        printf("二叉树的根为：%c\n", T[0]);
    }
}

//返回处于位置e(层,本层序号)的结点的的值
char GetValue(SqBiTree T, Position e)
{
    printf("位置e处的值为：%c\n", T[(int)pow(2, e.level - 1) + e.order - 2]);
    return T[(int)pow(2, e.level - 1) + e.order - 2]; //注意pow的返回值为double，所以此处应该强制类型转换
}

//给处于位置e(层,本层序号)的结点赋新值value
void Assign(SqBiTree T, Position e, char value)
{
    int i = (int)pow(2, e.level - 1) + e.order - 2; //将层、本层序号转为矩阵的序号
    if (value != Nil && T[i / 2] == Nil)            //给叶子赋非空值但双亲为空
    {
        printf("给双亲为空的叶子结点赋非空值!\n");
    }
    else
    {
        if (value == Nil && (T[2 * i + 1] == Nil || T[2 * i + 2] == Nil)) //给双亲赋空值但有叶子（不空）
        {
            printf("给有儿子的双亲结点赋空值!\n");
        }
        T[i] = value;
    }
}

// e是T中某个结点，返回e的左兄弟。若e是T的左孩子或无左兄弟,则打印提示
void LeftBro(SqBiTree T, char e)
{
    if (BiTreeEmpty == 0)
    {
        printf("二叉树为空！\n");
    }
    else
    {
        int i;
        int flag = 0;
        for (i = 0; i < MAX; i++)
        {
            if (T[i] == e && i % 2 == 0) //找到e且其序号为偶数(是右孩子)
            {
                printf("该元素的左兄弟为：%c\n", T[i - 1]);
                flag = 1; //放置一个标志变量-----一个不错的思路！
            }
        }
        if (flag == 0) //如果标志没有被改变，说明没有找到！！
        {
            printf("该元素无左兄弟！\n");
        }
    }
}

// e是T中某个结点，返回e的右兄弟。若e是T的右孩子或无右兄弟,则打印提示
void RightBro(SqBiTree T, char e)
{
    if (BiTreeEmpty == 0)
    {
        printf("二叉树为空！\n");
    }
    else
    {
        int i;
        int flag = 0;
        for (i = 0; i < MAX; i++)
        {
            if (T[i] == e && i % 2 != 0) //找到e且其序号为奇数(是左孩子)
            {
                printf("该元素的右兄弟为：%c\n", T[i + 1]);
                flag = 1; //放置一个标志变量-----一个不错的思路！
            }
        }
        if (flag == 0) //如果标志没有被改变，说明没有找到！！
        {
            printf("该元素无右兄弟！\n");
        }
    }
}

//前序遍历二叉树
void PreOrderTraverse(SqBiTree T, int i)
{
    if (T[0] == Nil)
    {
        printf("二叉树为空！\n");
    }
    else
    {
        printf("%c\n", T[i]);
        if (T[2 * i + 1] != Nil)
        {
            PreOrderTraverse(T, 2 * i + 1);
        }
        if (T[2 * i + 2] != Nil)
        {
            PreOrderTraverse(T, 2 * i + 2);
        }
    }
}

//中序遍历二叉树
void InOrderTraverse(SqBiTree T, int i)
{
    if (T[0] == Nil)
    {
        printf("二叉树为空！\n");
    }
    else
    {

        if (T[2 * i + 1] != Nil)
        {
            InOrderTraverse(T, 2 * i + 1);
        }
        printf("%c\n", T[i]);
        if (T[2 * i + 2] != Nil)
        {
            InOrderTraverse(T, 2 * i + 2);
        }
    }
}

//后序遍历二叉树
void PostOrderTraverse(SqBiTree T, int i)
{
    if (T[0] == Nil)
    {
        printf("二叉树为空！\n");
    }
    else
    {

        if (T[2 * i + 1] != Nil)
        {
            PostOrderTraverse(T, 2 * i + 1);
        }

        if (T[2 * i + 2] != Nil)
        {
            PostOrderTraverse(T, 2 * i + 2);
        }
        printf("%c\n", T[i]);
    }
}

//层序遍历二叉树
void LevelOrderTraverse(SqBiTree T)
{
    if (T[0] == Nil)
    {
        printf("二叉树为空！\n");
    }
    else
    {
        int i;
        int j = 0; //用于存储最后一个结点的位置
        for (i = MAX - 1; i >= 0; i--)
        {
            if (T[i] != Nil)
            {
                j = i;
                break;
            }
        }
        for (i = 0; i <= j; i++)
        {
            if (T[i] != Nil)
                printf("%c\n", T[i]);
        }
    }
}

//逐层、按本层序号输出二叉树
void PrintBitree(SqBiTree T)
{
    if (T[0] == Nil)
    {
        printf("二叉树为空！\n");
    }
    else
    {
        int i;
        int k = BiTreeDepth(T); //获得树的深度
        for (i = 1; i <= k; i++)
        {
            printf("第%d层\n", i);
            int j;

            for (j = (int)pow(2, i - 1) - 1; j <= (int)pow(2, i) - 2; j++) //第i层的元素的起始和终止位置
            {
                printf("%d:%c\n", j, T[j]); //如果是空的也输出
            }
        }
    }
}

/***************主函数***************************/
int main()
{
    SqBiTree T;
    InitSqBiTree(T); //构造空二叉树

    CreatBiTree(T); //按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T
    PrintTree(T);   //逐个输出树的结点

    // ClearTree(T);   //清空树
    // BiTreeEmpty(T); //判断二叉树是否为空
    BiTreeDepth(T); //计算树的深度
    GetRoot(T);     //计算树的深度

    char value = 'a';
    Position e = {2, 1}; //给结构体赋初值，！！注意此处输入时不要输入该层没有的较大序号，实际上可以在函数体内做一个判别，之前有做过，这里不再写了，有思路即可
    GetValue(T, e);      //返回处于位置e(层,本层序号)的结点的的值
    Assign(T, e, value); //给处于位置e(层,本层序号)的结点赋新值value
    PrintTree(T);        //逐个输出树的结点
    char q = 't';
    LeftBro(T, q); // e是T中某个结点，返回e的左兄弟。若e是T的左孩子或无左兄弟,则打印提示
    char p = 'u';
    RightBro(T, p); // e是T中某个结点，返回e的右兄弟。若e是T的右孩子或无右兄弟,则打印提示

    PreOrderTraverse(T, 0); //前序遍历二叉树---注意在遍历的过程中i值可能会取到很大的值，此处需要把max设置的大一些！！
    printf("------------\n");
    InOrderTraverse(T, 0); //中序遍历二叉树
    printf("------------\n");
    PostOrderTraverse(T, 0); //后序遍历二叉树
    printf("------------\n");
    LevelOrderTraverse(T); //层序遍历二叉树
    PrintBitree(T);        //逐层、按本层序号输出二叉树
}
