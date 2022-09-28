#include <stdio.h>
#include "stdlib.h"

#define MAXSIZE 9 /* 存储空间初始分配量 */
#define MAXEDGE 15
#define MAXVEX 9

typedef int Boolean; /* Boolean是布尔类型,其值是TRUE-1或FALSE-0 */

//建立邻接矩阵结构体
typedef struct
{
    char vexs[MAXVEX];         /* 顶点表 */
    int arc[MAXVEX][MAXVEX];   /* 邻接矩阵，可看作边表 */
    int numVertexes, numEdges; /* 图中当前的顶点数和边数 */
} MGraph;

/**用到的队列结构与函数********************************** */

//循环队列的顺序存储结构
typedef struct
{
    int data[MAXSIZE];
    int front; /* 头指针 */
    int rear;  /* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
} Queue;

/* 初始化一个空队列Q */
int InitQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return 1;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
int QueueEmpty(Queue Q)
{
    if (Q.front == Q.rear) /* 队列空的标志 */
        return 1;
    else
        return 0;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
int EnQueue(Queue *Q, int e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front) /* 队列满的判断 */
        return 0;
    Q->data[Q->rear] = e;              /* 将元素e赋值给队尾 */
    Q->rear = (Q->rear + 1) % MAXSIZE; /* rear指针向后移一位置， */
                                       /* 若到最后则转到数组头部 */
    return 1;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
int DeQueue(Queue *Q, int *e)
{
    if (Q->front == Q->rear) /* 队列空的判断 */
        return 0;
    *e = Q->data[Q->front];              /* 将队头元素赋值给e */
    Q->front = (Q->front + 1) % MAXSIZE; /* front指针向后移一位置， */
                                         /* 若到最后则转到数组头部 */
    return 1;
}

/* ****************************************************** */
void CreateMGraph(MGraph *G)
{
    int i, j;
    G->numEdges = 15;
    G->numVertexes = 9;
    /* 读入顶点信息，建立顶点表 */
    G->vexs[0] = 'A';
    G->vexs[1] = 'B';
    G->vexs[2] = 'C';
    G->vexs[3] = 'D';
    G->vexs[4] = 'E';
    G->vexs[5] = 'F';
    G->vexs[6] = 'G';
    G->vexs[7] = 'H';
    G->vexs[8] = 'I';

    for (i = 0; i < G->numVertexes; i++) /* 初始化图 */
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = 0;
        }
    }

    //建立无向图
    G->arc[0][1] = 1;
    G->arc[0][5] = 1;

    G->arc[1][2] = 1;
    G->arc[1][8] = 1;
    G->arc[1][6] = 1;

    G->arc[2][3] = 1;
    G->arc[2][8] = 1;

    G->arc[3][4] = 1;
    G->arc[3][7] = 1;
    G->arc[3][6] = 1;
    G->arc[3][8] = 1;

    G->arc[4][5] = 1;
    G->arc[4][7] = 1;

    G->arc[5][6] = 1;

    G->arc[6][7] = 1;

    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

Boolean visited[MAXVEX]; /* 访问标志的数组 */

//邻接矩阵的深度遍历操作
void DFSTraverse(MGraph G)
{
    int i;
    for (i = 0; i < G.numVertexes; i++)
    {
        visited[i] = 0;
    }
    for (i = 0; i < G.numVertexes; i++)
    {
        if (visited[i] == 0)
        {
            DFS(G, i);
        }
    }
}

//邻接矩阵的深度优先递归算法
void DFS(MGraph G, int i)
{
    int j;
    visited[i] = 1;
    printf("%c\n", G.vexs[i]);
    for (j = 0; j < G.numVertexes; j++)
    {
        if (visited[i] == 0 && G.arc[i][j] == 1)
            DFS(G, j);
    }
}

//邻接矩阵的广度遍历算法
void BFS(MGraph G)
{
    int i, j;
    //初始化
    for (i = 0; i < G.numVertexes; i++)
    {
        visited[i] = 0;
    }
    Queue Q;
    InitQueue(&Q);
    for (i = 0; i < G.numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("%c\n", G.vexs[i]);
            EnQueue(&Q, i);
            while (QueueEmpty(Q) == 0) //队列不空
            {
                DeQueue(&Q, &i);
                for (j = 0; j < G.numVertexes; j++)
                {
                    if (visited[j] == 0 && G.arc[i][j] == 1) //其它顶点若与当前顶点存在边（邻接点）且未访问过
                    {
                        visited[j] = 1;
                        printf("%c\n", G.vexs[j]);
                        EnQueue(&Q, j);
                    }
                }
            }
        }
    }
}

/*********************主函数*******************************/
void main()
{
    MGraph G;
    CreateMGraph(&G);
    printf("图的深度遍历：\n");
    DFSTraverse(G);
    printf("图的广度遍历：\n");
    BFS(G);
}
