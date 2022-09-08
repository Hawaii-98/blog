#include <stdio.h>
#include <stdlib.h>

typedef struct QNode
{
    int data;
    struct QNode *next;
} QNode;

typedef QNode *QueuePtr;

typedef struct
{
    QueuePtr front, rear; // QueuePtr是一个（QNode结构体类型的）指针变量，
} LinkQueue;

//队列的初始化（构造空队列）
int InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (Q->front == NULL)
        printf("空间不足！\n");
    else
    {
        Q->front->next = NULL;
        printf("队列已初始化完成！\n");
    }
}

//插入元素e为Q的新的队尾元素
int EnQueue(LinkQueue *Q, int e)
{
    QueuePtr s;
    s = (QueuePtr)malloc(sizeof(QNode));
    if (s == NULL)
        printf("空间不足！\n");
    else
    {
        s->data = e;
        s->next = NULL;
        Q->rear->next = s;
        Q->rear = s;
        printf("元素%d已入队！\n", e);
    }
}

//若队列不空,则打印Q的队头元素,否则打印提示
int GetHead(LinkQueue Q)
{
    if (Q.front == Q.rear)
        printf("空队列！无法打印！\n");
    else
    {
        printf("队头元素是%d.\n", Q.front->next->data);
    }
}

//求队列的长度
int LengthQueue(LinkQueue Q)
{
    int i = 0;
    QueuePtr p = Q.front;
    while (p != Q.rear) //若此处条件为while(p),结果会比实际队列长度多1！！
    {                   //因为队列空的条件不是p为空，而是头结点等于队尾结点！！
        i++;
        p = p->next;
    }
    printf("队列的长度为%d.\n", i);
}

/*******************主函数*************************/
int main()
{
    int i;
    LinkQueue Q;
    InitQueue(&Q);
    for (i = 2; i < 8; i++)
    {
        EnQueue(&Q, i);
    }

    GetHead(Q);
    LengthQueue(Q);
}
