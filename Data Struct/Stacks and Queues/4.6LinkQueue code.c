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

//从队头到队尾依次对队列Q中每个元素输出
int PrintQueue(LinkQueue Q)
{
    if (Q.front == Q.rear)
        printf("待打印的队列为空！\n");
    else
    {
        QueuePtr p = Q.front->next;
        printf("队列元素为：\n");
        while (p) //注意，判定条件while (p != Q.rear)会使得最后一个元素无法输出！！
        {         //应该是while (p != Q.rear->next)即p不为空！！
            printf("%d\n", p->data);
            p = p->next;
        }
    }
}

//若队列不空,删除Q的队头元素,打印其值,否则打印提示
int DeleteQueue(LinkQueue *Q)
{
    if (Q->front == Q->rear)
        printf("队列为空，无法删除！\n");
    else
    {
        QueuePtr p;
        p = Q->front->next;
        printf("出队的元素是%d。\n", p->data);
        Q->front->next = p->next;
        if (p == Q->rear)
            Q->rear = Q->front;
        free(p);
    }
}

//清空队列
int ClearQueue(LinkQueue *Q)
{
    QueuePtr p, q;
    Q->rear = Q->front;
    p = Q->front->next;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    printf("队列已清空！\n");
}

//销毁队列
int DestroyQueue(LinkQueue *Q)
{
    while (Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
}

//注意销毁队列函数如果这样写：引入临时变量p。此时！p和Q->front都指向头节点空间，释放的p，但是还存在着Q->front，因此需要对头结点进行释放！！
int DestroyQueue(LinkQueue *Q)
{

    QueuePtr p = Q->front;

    while (p)
    {
        Q->rear = p->next;
        free(p);
        p = Q->rear;
    }

    Q->front = NULL;       //清空头结点，此处不要用free(Q->front)，不能释放！原因持续探索中.....
}

/*******************主函数*************************/
int main()
{
    int i;
    LinkQueue Q;
    InitQueue(&Q); //初始化队列
    for (i = 2; i < 8; i++)
    {
        EnQueue(&Q, i); //元素入队
    }

    GetHead(Q);
    LengthQueue(Q); //队列长度

    PrintQueue(Q); //打印队列元素

    DeleteQueue(&Q); //队头元素出队
    PrintQueue(Q);

    ClearQueue(&Q); //清空队列
    PrintQueue(Q);

    for (i = 5; i < 8; i++)
    {
        EnQueue(&Q, i); //元素入队
    }
    PrintQueue(Q); //打印队列元素

    printf("销毁队列前,Q.front=%u Q.rear=%u\n", Q.front, Q.rear);
    DestroyQueue(&Q); //销毁队列
    printf("销毁队列后,Q.front=%u Q.rear=%u\n", Q.front, Q.rear);
}
