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

typedef struct BiTNode
{
    int data;
    int bf;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//对以p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点
void R_Rotate(BiTree *P)
{
    BiTree L;
    L = (*P)->lchild;         // L指向P的左子树根结点
    (*P)->lchild = L->rchild; // L的右子树挂接为P的左子树
    L->rchild = (*P);
    *P = L; // P指向新的根结点
}

//对以p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转处理之前的右子树的根结点
void L_Rotate(BiTree *P)
{
    BiTree R;
    R = (*P)->rchild;         /*  R指向P的右子树根结点 */
    (*P)->rchild = R->lchild; /* R的左子树挂接为P的右子树 */
    R->lchild = (*P);
    *P = R; /*  P指向新的根结点 */
}

#define LH +1 /*  左高 */
#define EH 0  /*  等高 */
#define RH -1 /*  右高 */

//对以指针T所指结点为根的二叉树作左平衡旋转处理，本算法结束时，指针T指向新的根结点
void LeftBalance(BiTree *T)
{
    BiTree L, Lr;
    L = (*T)->lchild; // L指向T的左子树根结点
    switch (L->bf)
    {        //检查T的左子树的平衡度，并做相应的平衡处理
    case LH: //说明新结点插入到了T的左孩子的左子树上，对根节点做单右旋即可
        (*T)->bf = L->bf = EH;
        R_Rotate(T);
        break;
    case RH:            //说明新结点插入到了T的左孩子的右子树上，此时要做双旋处理
        Lr = L->rchild; // Lr指向T的左孩子的右子树根
        switch (Lr->bf) //修改T及其左孩子的平衡因子
        {
        case LH:
            (*T)->bf = RH;
            L->bf = EH;
            break;
        case EH:
            (*T)->bf = L->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            L->bf = LH;
            break;
        }
        Lr->bf = EH;
        L_Rotate(&(*T)->lchild); //对T的左子树做左旋平衡处理
        R_Rotate(T);             //对T做右旋处理
    }
}

//对以指针T所指结点为根的二叉树作左平衡旋转处理，本算法结束时，指针T指向新的根结点
void RightBalance(BiTree *T)
{
    BiTree R, Rl;
    R = (*T)->rchild;
    switch (R->bf)
    {
    case RH:
        (*T)->bf = R->bf = EH;
        L_Rotate(T);
        break;
    case LH:
        Rl = R->lchild;
        switch (Rl->bf)
        {
        case RH:
            (*T)->bf = LH;
            R->bf = EH;
            break;
        case EH:
            (*T)->bf = R->bf = EH;
            break;
        case LH:
            (*T)->bf = EH;
            R->bf = RH;
            break;
        }
        Rl->bf = EH;
        R_Rotate(&(*T)->rchild);
        L_Rotate(T);
    }
}

//若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素为e的新结点，并返回1，否则返回0。
//若因插入而使二叉排序树失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。
Status InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!(*T))
    { //插入新结点，树“长高”，置taller为TRUE
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->bf = EH;
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        *taller = TRUE;
    }
    else
    {
        if (e == (*T)->data)
        { //树中已存在和e有相同关键字的结点则不5再插入
            *taller = FALSE;
            return FALSE;
        }
        else if (e < (*T)->data)
        {                                             //应继续在T的左子树中进行搜索
            if (!InsertAVL(&(*T)->lchild, e, taller)) /*  未插入 */
            {
                return FALSE;
            }
            if (*taller) //已插入到T的左子树中且左子树“长高”
            {
                switch ((*T)->bf)
                {
                case LH: //原本左子树比右子树高，需要作左平衡处理
                    LeftBalance(T);
                    *taller = FALSE;
                    break;
                case EH: //原本左、右子树等高，现因左子树增高而使树增高
                    (*T)->bf = LH;
                    *taller = TRUE;
                    break;
                case RH: //原本右子树比左子树高，现左、右子树等高
                    (*T)->bf = EH;
                    *taller = FALSE;
                    break;
                }
            }
        }
        else //继续在T的右子树进行搜寻，与上面思路相同
        {
            if (!InsertAVL(&(*T)->rchild, e, taller))
                return FALSE;
            if (*taller)
                switch ((*T)->bf)
                {
                case LH:
                    (*T)->bf = EH;
                    *taller = FALSE;
                    break;
                case EH:
                    (*T)->bf = RH;
                    *taller = TRUE;
                    break;
                case RH:
                    RightBalance(T);
                    *taller = FALSE;
                    break;
                }
        }
    }
    return TRUE;
}

/*********************主函数**************************/
int main()
{
    int i;
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    BiTree T = NULL;
    Status taller;
    for (i = 0; i < 10; i++)
    {
        InsertAVL(&T, a[i], &taller);
    }
}
