#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

//二叉树的二叉链表结点结构定义
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//递归查找二叉排序树T中是否存在key
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if (!T)
    {
        *p = f;
        return FALSE;
    }
    else if (key == T->data)
    {
        *p = T;
       // printf("查找到的位置对应的数据为%d。\n", (*p)->data);
        return TRUE;
    }
    else if (key > T->data)
    {
        return SearchBST(T->rchild, key, T, p);
    }
    else
    {
        return SearchBST(T->lchild, key, T, p);
    }
}

//当二叉排序树T中不存在关键字等于key的数据元素时，插入key并返回TRUE，否则返回FALSE
Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;
    if (!SearchBST(*T, key, NULL, &p))
    {
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;
        if (!p)
        {
            *T = s;
        }
        else if (key < p->data)
        {
            p->lchild = s;
        }
        else
        {
            p->rchild = s;
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/********************主函数**************************/
void main()
{
    BiTree T = NULL;
    int i;
    int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
    for (i = 0; i < 10; i++)
    {
        InsertBST(&T, a[i]);
    }
    BiTree *p;
    SearchBST(T, 62, NULL, p);
    printf("查找到的位置对应的数据为%d。\n", (*p)->data);
}
