#include <stdio.h>
#include <string.h>
#include "stdlib.h"

#define MAX 100

//建立一个枚举类型，包含0,1两个值
typedef enum
{
    Link,
    Thread
} PointerTag;

//建立二叉线索存储结点结构
typedef struct BiThrNode
{
    char data;
    struct BiThrNode *LChild, *RChild;
    PointerTag LTag;
    PointerTag RTag;
} BiThrNode, *BiThrTree;

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

//按前序输入二叉树中结点的值（一个字符）
//#表示空树，构造二叉链表表示二叉树T。
//此处的T表示的是一个最小的树，（一个结点）
void CreatBiThrtree(BiThrTree *T)
{
    char ch;
    ch = str[TreeIndex++];
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if (!*T)
        {
            exit(0);
        }
        (*T)->data = ch;               //生成根结点,注意此处*T必须要加括号！！
        CreatBiThrtree(&(*T)->LChild); //构造左子树，改的一级指针的值，所以要传进去二级指针
        if ((*T)->LChild)              //如果有左孩子
            (*T)->LTag = Link;
        CreatBiThrtree(&(*T)->RChild); //递归构造右子树
        if ((*T)->RChild)              //如果有左孩子
            (*T)->RTag = Link;
    }
}

//前序遍历二叉树
void PreOrderTraverse(BiThrTree T)
{
    if (T == NULL)
        return; //函数一旦遇到 return 语句就立即返回，后面的所有语句都不会被执行到了。即return 语句还有强制结束函数执行的作用
    printf("%c", T->data);
    PreOrderTraverse(T->LChild); //前序遍历左孩子子树
    PreOrderTraverse(T->RChild);
}

BiThrTree pre; //全局变量,始终指向刚刚访问过的结点

//中序遍历进行中序线索化
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->LChild);
        if (!p->LChild) //没有左孩子
        {
            p->LTag = Thread;
            p->LChild = pre;
        }
        if (!pre->RChild) //前驱没有右孩子

        {
            pre->RTag = Thread;
            pre->RChild = p;
        }
        pre = p;
        InThreading(p->RChild);
    }
}

//建立带头结点的线索二叉树（中序遍历二叉树T,并将其中序线索化,Thr指向头结点 ）
void InOrderThreading(BiThrTree T, BiThrTree *Thr)
{
    *Thr = (BiThrTree)malloc(sizeof(BiThrNode));
    if (!*Thr)
    {
        exit(0);
    }
    //对头结点进行初始化
    (*Thr)->LTag = Link;
    (*Thr)->RTag = Thread;
    (*Thr)->RChild = (*Thr);
    if (!T)
    {
        (*Thr)->LChild = (*Thr);
    }
    else
    {
        (*Thr)->LChild = T;
        pre = (*Thr);
        InThreading(T);
        pre->RChild = (*Thr);
        pre->RTag = Thread;
        (*Thr)->RChild = pre;
    }
}

//中序遍历二叉线索树T(头结点)的非递归算法
void InOrderTraverse(BiThrTree T)
{
    BiThrTree p;
    p = T->LChild;
    while (p != T)
    {
        while (p->LTag == Link)
        {
            p = p->LChild;
        }
        printf("%c\n", p->data);
        while (p->RTag == Thread && p->RChild != T)
        {
            p = p->RChild;
            printf("%c\n", p->data);
        }
        p = p->RChild;
    }
}

/*****************主函数**********************/
void main()
{
    StrAssign(str, "ABDH##I##EJ###CF##G##"); //利用给定字符串建立字符串数组以构造线索二叉树

    BiThrTree T;
    CreatBiThrtree(&T);  //按前序输入二叉树中结点的值（一个字符）
    PreOrderTraverse(T); //前序遍历二叉树
    printf("\n");
    pre = T; //对pre进行初始化！
    //InThreading(T); //中序遍历进行中序线索化--!注意中序线索化与下面带头结点的中序线索化不要同时编译！！

    BiThrTree Thr;
    InOrderThreading(T, &Thr); //建立带头结点的线索二叉树（中序遍历二叉树T,并将其中序线索化,Thr指向头结点 ）
    InOrderTraverse(Thr);      //中序遍历二叉线索树T(头结点)的非递归算法
}
