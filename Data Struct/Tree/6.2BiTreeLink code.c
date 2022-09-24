#include <stdio.h>
#include <string.h>
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define MAX 40

//利用给定字符串建立字符串数组以构造二叉树
typedef char String[24];
String str;
int TreeIndex = 1;
void StrAssign(String S, char *strs)
{
    if (strlen(strs) > MAX)
    {
        printf("给定的字符串的长度过长！\n");
    }
    else
    {
        int i;
        S[0] = strlen(strs);
        for (i = 1; i <= strlen(strs); i++)
        {
            S[i] = *(strs + i - 1); //字符串的值逐一赋值到数组中
        }
    }
}

//定义二叉树的结点结构体
typedef struct BiTNode
{
    char data;
    struct BiTNode *LChild, *RChild;
} BiTNode;
typedef BiTNode *BiTree; //定义一个指向bitnode的指针类型
//以便于在后续需要改变结点的值时，直接传递指针进行改变

//构造空二叉树T
void InitBiTree(BiTree *T) //此处的函数参数是二级指针
{
    *T = NULL;
}

//按前序输入二叉树中结点的值（一个字符）
//#表示空树，构造二叉链表表示二叉树T。
//此处的T表示的是一个最小的树，（一个结点）
void CreatBitree(BiTree *T)
{
    char ch;
    ch = str[TreeIndex++];
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T)
        {
            exit(0);
        }
        (*T)->data = ch;            //生成根结点,注意此处*T必须要加括号！！
        CreatBitree(&(*T)->LChild); //构造左子树，改的一级指针的值，所以要传进去二级指针
        CreatBitree(&(*T)->RChild); //构造右子树
    }
}

//前序遍历二叉树
void PreOrderTraverse(BiTree T)
{
    if (T == NULL)
        return; //函数一旦遇到 return 语句就立即返回，后面的所有语句都不会被执行到了。即return 语句还有强制结束函数执行的作用
    printf("%c", T->data);
    PreOrderTraverse(T->LChild); //前序遍历左孩子子树
    PreOrderTraverse(T->RChild);
}

//中序遍历二叉树
void InOrderTraverse(BiTree T)
{
    if (T == NULL)
        return; //函数一旦遇到 return 语句就立即返回，后面的所有语句都不会被执行到了。即return 语句还有强制结束函数执行的作用
    InOrderTraverse(T->LChild);
    printf("%c", T->data);
    InOrderTraverse(T->RChild);
}

//后序遍历二叉树
void PostOrderTraverse(BiTree T)
{
    if (T == NULL)
        return; //函数一旦遇到 return 语句就立即返回，后面的所有语句都不会被执行到了。即return 语句还有强制结束函数执行的作用
    PostOrderTraverse(T->LChild);
    PostOrderTraverse(T->RChild);
    printf("%c", T->data);
}

//计算二叉树的深度
int BiTreeDepth(BiTree T)
{
    int i, j;
    if (!T)
    {
        return 0;
    }
    if (T->LChild)
    {
        i = BiTreeDepth(T->LChild); //计算左孩子子树
    }
    else
    {
        i = 0;
    }
    if (T->RChild)
    {
        j = BiTreeDepth(T->RChild); //计算右孩子子树
    }
    else
    {
        j = 0;
    }
    return i > j ? i + 1 : j + 1;
}

//返回二叉树的根
char Root(BiTree T)
{
    if (!T)
    {
        return ' ';
    }
    else
    {
        return T->data;
    }
}

//返回某个p结点所对应的值
char Value(BiTree p)
{
    return p->data;
}

// 给p所指结点赋值为value
void Assign(BiTree p, char value)
{
    p->data = value;
}

//销毁二叉树T
void DestroyTree(BiTree *T)
{
    if (*T)
    {
        if ((*T)->LChild)               //有左孩子
            DestroyTree(&(*T)->LChild); //销毁左孩子子树
        if ((*T)->RChild)               //有左孩子
            DestroyTree(&(*T)->RChild); //销毁左孩子子树
        free(*T);                       //释放根节点
        *T = NULL;                      //空指针赋零
    }
}

/****************主函数************************/
void main()
{
    StrAssign(str, "ABDH#K###E##CFI###G#J##"); //利用给定字符串建立字符串数组以构造二叉树

    BiTree T;
    InitBiTree(&T);      //构造空二叉树T
    CreatBitree(&T);     //按前序输入二叉树中结点的值（一个字符）
    PreOrderTraverse(T); //前序遍历二叉树
    printf("\n");
    InOrderTraverse(T); //中序遍历二叉树
    printf("\n");
    PostOrderTraverse(T); //后序遍历二叉树
    printf("\n");
    printf("二叉树的深度为：%d\n", BiTreeDepth(T)); //计算二叉树的深度
    printf("二叉树的根为：%c\n", Root(T));
    DestroyTree(&T);                                //销毁二叉树T
    printf("二叉树的深度为：%d\n", BiTreeDepth(T)); //计算二叉树的深度
}
