#include <stdio.h>
#include <stdlib.h>

//建立一个链表的结构体--结点
typedef struct
{
    int data;
    struct Node *next; //定义一个指针，指向struct node类型结构体--结点
} Node;

typedef Node *LinkList; //定义链表为一个指针变量

//初始化链表--令指针域为空
int IntiLinkList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node)); //为头结点L申请一块内存空间！！L存的也是一个地址，因为linklist是指针变量
    if (!(*L))
        printf("申请内存空间失败！\n");
    (*L)->next = NULL; //令指针指为空地址--必须加括号！！
}

//随机产生n个元素的值，建立带表头结点的单链线性表（头插法）
int CreateLinkListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0)); //初始化随机数种子
    *L = ((LinkList)malloc(sizeof(Node)));
    (*L)->next = NULL; //建立并初始化一个带有头结点的单链表
    for (i = 1; i <= n; i++)
    {
        p = ((LinkList)malloc(sizeof(Node)));
        p->data = rand() % 100 + 1;
        p->next = (*L)->next; //头插法的关键步骤
        (*L)->next = p;       //头插法的关键步骤
    }
}

//随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法）
int CreateLinkListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    r = *L;
    for (i = 1; i <= n; i++)
    {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

//依次对L的每个数据元素输出
int PrintLinkList(LinkList L)
{
    LinkList p = L->next;
    if (L->next == NULL) //如果链表为空，输出指示。
        printf("链表为空！\n");

    else
    {
        printf("链表中现有的元素为：\n");
        while (p)
        {
            printf("%d\n", p->data);
            p = p->next;
        }
    }
}

//返回链表中的元素个数
int ListLength(LinkList L)
{
    int i = 0;
    LinkList q = L->next;
    while (q)
    {
        i++;
        q = q->next;
    }
    printf("链表中的元素个数为：%d\n", i);
}

//返回L中第i个数据元素的值
int GetElem(LinkList L, int i)
{
    LinkList p = L->next;
    int j=1;
    int e;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
        printf("第%d个位置的元素不存在！\n", i);
    else
    {
        e = p->data;
        printf("第%d个位置的元素为%d！\n", i, e);
    }
}

//链式线性表L已存在时，将L重置为空表
int ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL;
}

int main()
{
    LinkList L;
    IntiLinkList(&L);
    CreateLinkListHead(&L, 3);
    printf("头插法:\n");
    PrintLinkList(L);

    CreateLinkListTail(&L, 3);
    printf("尾插法:\n");
    PrintLinkList(L);

    ListLength(L); //输出链表元素个数

    GetElem(L, 2);//查找第i个位置的元素
    
    ClearList(&L); //清空链表
    PrintLinkList(L);

}
