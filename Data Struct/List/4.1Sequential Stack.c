#include <stdio.h>

#define MAX 20

//建立一个结构体，定义顺序栈的结构
typedef struct
{
    int data[MAX];
    int top;
} SqStack;

//初始化顺序栈
int InitStack(SqStack *S)
{
    S->top = -1;
    printf("顺序栈初始化完成!\n");
}

//插入元素e为新的栈顶元素
int InsertStack(SqStack *S, int e)
{
    S->top++;
    S->data[S->top] = e;
    printf("元素%d已插入！\n", e);
}

//从栈底到栈顶依次对栈中每个元素显示
int PrintStack(SqStack S)
{
    int i;

    printf("顺序栈中的元素为:\n");

    for (i = 0; i <= (S.top); i++)
    {

        printf("%d\n", S.data[i]);
    }
}

//若栈不空，则删除S的栈顶元素,输出删除的值
int DeleteStack(SqStack *S)
{
    int e;
    if (S->top == -1)
        printf("这个栈是空的！\n");
    else
    {
        e = S->data[S->top];
        S->top--;
        printf("删除的元素是%d\n", e);
    }
}

/*********************************主函数***********************************/
int main()
{
    SqStack S;
    int i;

    InitStack(&S);
    for (i = 1; i < 8; i++)
    {
        InsertStack(&S, i); //循环插入7个元素
    }
    PrintStack(S); //打印栈底到栈底的元素

    DeleteStack(&S); //删除栈顶元素

    PrintStack(S);
}
