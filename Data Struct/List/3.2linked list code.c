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
            p = p->next; //常规的链表遍历操作
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
    int j = 1;
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

//在L中第i个位置之前插入新的数据元素e，L的长度加1
int InsertList(LinkList *L, int e, int i)
{
    LinkList p, q;
    p = *L;    //此处不可用p=(*L)->next,这使得向后插入了一个位置
    int j = 1; //一定要在定义变量时想好其初始值！
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
        printf("链表中没有第%d个位置！\n", i);
    else
    {
        q = (LinkList)malloc(sizeof(Node));
        q->data = e;
        q->next = p->next;
        p->next = q;
        printf("数据已经插入！\n");
    }
}

//返回L中第1个与e满足关系的数据元素的位序。
int LocateElem(LinkList L, int e)
{
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
        i++;
        if (p->data == e)
        {
            printf("链表中元素值为%d的元素在第%d个位置。\n", e, i);
            break;
        }
        p = p->next;
    }
    if (p == NULL)
        printf("链表中没有%d这个元素！\n", e);
}

//删除L的第i个数据元素，并用e返回其值，L的长度减1
int DeleteList(LinkList *L, int i)
{
    int m;
    LinkList p, q;
    p = *L;
    int j = 1; //一定要在定义变量时想好其初始值！
    while ((p->next) && j < i)
    {
        p = p->next;
        j++;
    }
    if (!(p->next)|| j > i)
        printf("链表中没有第%d个位置！\n", i);
    else
    {
        q = p->next;
        p->next = q->next;
        m = q->data;
        free(q);
        printf("第%d个元素%d已删除\n", i, m);
    }
}


/****************************主函数****************************/
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

    GetElem(L, 2); //查找第i个位置的元素

    InsertList(&L, 89, 3); //在第i个位置插入值
    PrintLinkList(L);

    LocateElem(L, 89); //查询89的位置

    DeleteList(&L, 2); //删除第i个位置的元素
    PrintLinkList(L);

    ClearList(&L); //清空链表
    PrintLinkList(L);
}
