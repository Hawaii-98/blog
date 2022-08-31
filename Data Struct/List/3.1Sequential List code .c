#include <stdio.h>

#define MAX 20

//结构体定义
typedef struct
{
    int data[MAX];
    int length;
} sqList;

//初始化线性表
int InitList(sqList *L)
{
    L->length = 0;
    return 666;
}

//向线性表中插入元素（向第i个位置插入元素e）
int InsertList(sqList *L, int e, int i)
{
    int k;
    if (L->length == MAX)
        printf("线性表已满，无法插入元素!\n");
    if (i > L->length + 1 || i < 0)
        printf("插入元素的位置不对！\n");
    if (i <= L->length)
    {
        for (k = L->length-1; k >= i - 1; k--) //如果插入位置不是最后一个，则所有元素向后移动一个
        {                                    //注意是从后向前遍历
            L->data[k + 1] = L->data[k];
        }
    }
    L->data[i-1] = e; //赋值
    L->length++;    //线性表长度加一

    printf("元素已经插入!\n");
}

//逐个输出线性表中的元素
int PrintList(sqList L)
{
    int j;
    int x;
    printf("线性表中现有的元素为\n");
    for (j = 0; j < L.length; j++)
    {
        x = L.data[j];
        printf("%d\n", x);
    }
}
int main()
{
    int flag;
    int i;
    sqList L;
    int e;

    flag = InitList(&L);
    printf("初始化线性表之后的线性表长度是%d\n", L.length);
    printf("线性表初始化真的%d\n", flag);
    for(i=1;i<6;i++)
    InsertList(&L, i, 1);
    PrintList(L);
    printf("插入元素之后的线性表长度是%d\n", L.length);
}
