#include <stdio.h>
#include <stdlib.h>

//链栈结构的初始化--两个结构体，一个是栈结点结构体，一个是栈结构体！
typedef struct
{
    int data;
    struct LinkStackNode *next; //这里因为要定义指向本结构体的指针，所以在结构体定义时有必要声明出名称LinkStackNode以便理解（也可以不声明）
} LinkStackNode;

typedef LinkStackNode *LinkStackPtr;

typedef struct
{
    LinkStackPtr top;
    int length;
} LinkStack;

//栈的初始化（构造一个空栈）
int InitLinkStack(LinkStack *L)
{
    L->top = (LinkStackPtr)malloc(sizeof(LinkStackNode));
    if (!(L->top))
        printf("计算机没有足够的内存！\n");
    else
    {
        L->top = NULL;
        L->length = 0;
        printf("链栈初始化完成!\n");
    }
}

//插入元素e为新的栈顶元素 （压入数据）
int Push(LinkStack *L, int e)
{
    LinkStackNode *p;
    p = (LinkStackPtr)malloc(sizeof(LinkStackNode));
    p->data = e;
    p->next = L->top;
    L->top = p;
    L->length++;
    printf("数据%d已压入栈顶\n", e);
}

//打印栈的长度
int LinkStackLength(LinkStack L)
{
    printf("链栈的长度为%d。\n", L.length);
}

//若栈不空，则用e返回S的栈顶元素并打印；否则提示
int GetTop(LinkStack L)
{
    LinkStackPtr p;
    p = (LinkStackPtr)malloc(sizeof(LinkStackNode));
    p = L.top;
    if (p == NULL)
    {
        printf("空栈！\n");
    }
    else
    {
        printf("栈顶元素为%d\n。", p->data);
    }
}

/*方法二--我的方法*/ /*int GetTop(LinkStackPtr top)     //注意在主函数中调用时应该用GetTop(L.top)
 {
     if (top == NULL)
     {
         printf("空栈！\n");
     }
     else
     {
         printf("栈顶元素为%d\n。", top->data);
     }
 }
 */

//若栈不空，输出栈中的数据；空则提示
int PrintLinkStack(LinkStack L)
{
    LinkStackPtr p;
    p = (LinkStackPtr)malloc(sizeof(LinkStackNode));
    // p = L.top;             //这里不用临时变量 p也是一样的！
    if (L.top == NULL || L.length == 0)
    {
        printf("空栈！\n");
    }
    else
    {
        printf("栈中的数据为：\n");
        while (L.top)
        {
            printf("%d\n", L.top->data);
            L.top = L.top->next;
        }
    }
}

//若栈不空，则删除S的栈顶元素并打印（弹出数据）；否则提示
int Pop(LinkStack *L)
{
    LinkStackPtr p;
    if (L->length == 0)
    {
        printf("链栈为空！\n");
    }
    else
    {
        printf("弹出的元素是：%d。\n", L->top->data);
        p = L->top;
        L->top = L->top->next;
        free(p);
        L->length--;
    }
}

//把栈清空
int ClearLinkStack(LinkStack *L)
{
    LinkStackPtr p, q;
    q = (LinkStackPtr)malloc(sizeof(LinkStackNode));
    p = (LinkStackPtr)malloc(sizeof(LinkStackNode));
    p = L->top;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    L->length = 0;
    printf("栈已清空\n");
}

/******************************************主函数***********************************/
int main()
{
    LinkStack L;
    LinkStackPtr top;

    int i;

    InitLinkStack(&L); //链栈的初始化
    for (i = 2; i < 6; i++)
    {
        Push(&L, i); //把i循环压入链栈
    }

    LinkStackLength(L); //查看链栈的长度
    GetTop(L);          //查看栈顶元素
    PrintLinkStack(L);  //输出栈中的元素
                        // Pop1(&L);           //弹出栈顶元素
    Pop(&L);            //弹出栈顶元素
    PrintLinkStack(L);  //输出栈中的元素*/
    Pop(&L);            //弹出栈顶元素
    PrintLinkStack(L);  //输出栈中的元素

    ClearLinkStack(&L); //清空栈
    PrintLinkStack(L);  //输出栈中的元素
}
