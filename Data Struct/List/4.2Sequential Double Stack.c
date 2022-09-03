//两栈共享空间
#include <stdio.h>

#define MAX 20

//建立一个双栈结构体
typedef struct
{
    int data[MAX]; //注意这里是指定义的数组长度为max，数组下标最大为max-1!!!所以下面栈空的条件就可以理解了！！
    int top1;
    int top2;
} sqDoubleStack;

//双栈的初始化（设置空栈）
int InitDoubleStack(sqDoubleStack *D)
{
    D->top1 = -1;
    D->top2 = MAX;
    printf("栈已初始化！\n");
}

//插入元素e为新的栈顶元素
int Push(sqDoubleStack *D, int e)
{
    int i;
    if (D->top1 + 1 == D->top2)
        printf("栈已满！\n");
    else
    {
        printf("你想往哪个栈里面压入元素？\n");
        printf("一号栈请输入1，二号栈请输入2！\n");

        if (scanf("%d", &i) == 1) //判断输入的数据对不对
        {
            if (i == 1)
                D->data[++D->top1] = e; /* 若是栈1则先top1+1后给数组元素赋值。 */
            if (i == 2)
                D->data[--D->top2] = e; /* 若是栈2则先top2-1后给数组元素赋值。 */
            else
                printf("你输入的不对！\n");
        }
        else
            printf("你输入的不对！\n");
    }
}

//返回栈的长度
int StackLength(sqDoubleStack D)
{
    printf("栈的长度为%d\n", D.top1 - (-1) + (-(D.top2 - MAX))); //两个指针相对于空栈时的指针的偏移量绝对值之和！
}

//从前往后输出栈中元素的数据
int PrintStack(sqDoubleStack D)
{
    int i;
    printf("栈中的元素为：\n");
    i = 0; //输出第一个栈的元素
    while (i <= D.top1)
    {
        printf("%d\n", D.data[i]);
        i++;
    }
    i = D.top2;
    while (i < MAX)
    {
        printf("%d\n", D.data[i]);
        i++;
    }
}

//若栈不空，则删除S的栈顶元素，打印删除的值
int DeleteStack(sqDoubleStack *D)
{
    int i;
    int e = 0;
    int f = 0;
    printf("你想从哪个栈里面删除元素？\n");
    printf("一号栈请输入1，二号栈请输入2！\n");
    if (scanf("%d", &i) == 1) //判断输入的数据对不对
    {
        if (i == 1)
        {
            if (D->top1 == -1)
                printf("1号栈是空的，无法删除！\n");
            else
            {
                e = D->data[D->top1--];
                printf("元素已删除，你删除的数据是%d\n", e);
            }
        }
        if (i == 2)
        {
            if (D->top1 == MAX)
                printf("2号栈是空的，无法删除！\n");
            else
            {
                f = D->data[D->top2++];
                printf("元素已删除，你删除的数据是%d\n", f);
            }
        }
        else
            printf("你输入的不对！\n");
    }
    else
        printf("你输入的不对！\n");
}

/******************主函数**************************/
int main()
{
    sqDoubleStack D;
    InitDoubleStack(&D); //初始化双栈D

    Push(&D, 2); //压入四个元素
    Push(&D, 6);
    Push(&D, 4);
    Push(&D, 9);

    StackLength(D); //输出栈的长度

    PrintStack(D); //打印栈的所有元素值

    DeleteStack(&D); //删除数据元素
    StackLength(D);  //输出栈的长度
    PrintStack(D);   //打印栈的所有元素值
}
