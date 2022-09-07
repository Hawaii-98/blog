//循环队列的顺序存储结构
#include <stdio.h>

#define MAX 10

typedef struct
{
    int data[MAX];
    int front;
    int rear;
} sqQueue;

//初始化一个空队列（清空队列）
int InitQueue(sqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
}

//若队列未满，则插入元素e为Q新的队尾元素
int EnQueue(sqQueue *Q, int e)
{
    if (((Q->rear + 1) % MAX) == Q->front)
        printf("队列已满\n");
    else
    {
        Q->data[Q->rear] = e;
        Q->rear = (Q->rear + 1) % MAX;
        printf("元素%d已插入队列!\n", e);
    }
}

//输出队列的长度
int LengthQueue(sqQueue Q)
{
    printf("队列的长度为%d!\n", (Q.rear - Q.front + MAX) % MAX);
}

//从队头到队尾依次对队列Q中每个元素输出
int PrintQueue(sqQueue Q)
{
    int i;
    i = Q.front;
    if (Q.front == Q.rear)
        printf("待打印的队列为空！\n");
    else
    {
        printf("队列中的元素为：\n");
        while ((i) != Q.rear)
        {
            printf("%d\n", Q.data[i]);
            i = (i + 1) % MAX;
        }
    }
}

//若队列不空，则删除Q中队头元素，打印删除的值
int DeleteQueue(sqQueue *Q)
{
    if (Q->front == Q->rear)
        printf("队列为空！\n");
    else
    {
        printf("出队(删除)的元素是：%d。\n", Q->data[Q->front]);
        Q->front = (Q->front + 1) % MAX;
    }
}
/*******************主函数***********************/
int main()
{
    int i;
    sqQueue Q;
    InitQueue(&Q); //队列的初始化
    for (i = 1; i < 5; i++)
    {
        EnQueue(&Q, i); //给队列赋值
    }

    LengthQueue(Q); //输出队列的长度
    PrintQueue(Q);  //逐个输出队列的元素

    DeleteQueue(&Q); //元素出列
    DeleteQueue(&Q); //元素出列
    DeleteQueue(&Q); //元素出列
    DeleteQueue(&Q); //元素出列

    PrintQueue(Q); //逐个输出队列的元素

    for (i = 1; i < 10; i++)
    {
        EnQueue(&Q, i); //给队列赋值
    }

    PrintQueue(Q); //逐个输出队列的元素
}
