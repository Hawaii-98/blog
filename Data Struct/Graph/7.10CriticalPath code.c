#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 14
#define GRAPH_INFINITY 65535

//建立邻接矩阵结构体
typedef struct
{
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

//建立邻接表结构体
typedef struct EdgeNode /* 边表结点  */
{
    int adjvex;            /* 邻接点域，存储该顶点对应的下标 */
    int weight;            /* 用于存储权值，对于非网图可以不需要 */
    struct EdgeNode *next; /* 链域，指向下一个邻接点 */
} EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
    int in;              /* 顶点入度 */
    int data;            /* 顶点域，存储顶点信息 */
    EdgeNode *firstedge; /* 边表头指针 */
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numVertexes, numEdges; /* 图中当前顶点数和边数 */
} graphAdjList, *GraphAdjList;
/***************************** */

//建立邻接矩阵表示的网结构
void CreateMGraph(MGraph *G) /* 构件图 */
{
    int i, j;

    G->numEdges = 13;
    G->numVertexes = 10;

    for (i = 0; i < G->numVertexes; i++) /* 初始化图 */
    {
        G->vexs[i] = i;
    }

    for (i = 0; i < G->numVertexes; i++) /* 初始化图 */
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            if (i == j)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = GRAPH_INFINITY;
        }
    }

    G->arc[0][1] = 3;
    G->arc[0][2] = 4;
    G->arc[1][3] = 5;
    G->arc[1][4] = 6;
    G->arc[2][3] = 8;
    G->arc[2][5] = 7;
    G->arc[3][4] = 3;
    G->arc[4][6] = 9;
    G->arc[4][7] = 4;
    G->arc[5][7] = 6;
    G->arc[6][9] = 2;
    G->arc[7][8] = 5;
    G->arc[8][9] = 3;
}

//利用邻接矩阵构建邻接表
void CreateALGraph(MGraph G, GraphAdjList *GL)
{
    int i, j;
    EdgeNode *e;

    *GL = (GraphAdjList)malloc(sizeof(graphAdjList));

    (*GL)->numVertexes = G.numVertexes;
    (*GL)->numEdges = G.numEdges;
    for (i = 0; i < G.numVertexes; i++) /* 读入顶点信息，建立顶点表 */
    {
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].data = G.vexs[i];
        (*GL)->adjList[i].firstedge = NULL; /* 将边表置为空表 */
    }

    for (i = 0; i < G.numVertexes; i++) /* 建立边表 */
    {
        for (j = 0; j < G.numVertexes; j++)
        {
            if (G.arc[i][j] != 0 && G.arc[i][j] < GRAPH_INFINITY)
            {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                e->adjvex = j; /* 邻接序号为j */
                e->weight = G.arc[i][j];
                e->next = (*GL)->adjList[i].firstedge; /* 将当前顶点上的指向的结点指针赋值给e */
                (*GL)->adjList[i].firstedge = e;       /* 将当前顶点的指针指向e  */
                (*GL)->adjList[j].in++;
            }
        }
    }
}

int *etv, *ltv; /* 事件最早发生时间和最迟发生时间数组 */
int *stack2;    /* 用于存储拓扑序列的栈 */
int top2;       /* 用于stack2的指针 */

//拓扑排序，用于计算etv和拓扑序列列表；若GL有回路，则打印提示
void TopologicalSort(GraphAdjList GL)
{
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;
    top2 = 0;
    int count = 0;
    int *stack; //此处使用的是顺序栈
    stack = (int *)malloc(GL->numVertexes * sizeof(int));
    stack2 = (int *)malloc(GL->numVertexes * sizeof(int)); /* 事件最早发生时间和最迟发生时间数组 */
    etv = (int *)malloc(GL->numVertexes * sizeof(int));    /* 事件最早发生时间数组 */
    for (i = 0; i < GL->numVertexes; i++)
    {
        etv[i] = 0;
        if ((GL->adjList[i].in) == 0) //这里需要特别注意->和.符号的使用
        {
            stack[++top] = i; //此处从栈的第1号位置开始存储,为下面的主循环做铺垫
        }
    }
    while (top != 0)
    {
        gettop = stack[top--];
        count++;
        stack2[++top2] = gettop;
        for (e = GL->adjList[gettop].firstedge; e; e = e->next) // e一直遍历边表结点直到指向空（此时e=0）
        {
            k = e->adjvex;
            if (!(--(GL->adjList[k].in)))
            {
                stack[++top] = k;
            }
            if ((etv[gettop] + e->weight) > etv[k])
            {
                etv[k] = etv[gettop] + e->weight;
            }
        }
    }

    if (count < GL->numVertexes)
    {
        printf("图中有环存在！\n");
    }
}

//求关键路径,GL为有向网，输出G的各项关键活动
void CriticalPath(GraphAdjList GL)
{
    EdgeNode *e;
    int i, gettop, k, j;
    int ete, lte;                                       /* 声明活动最早发生时间和最迟发生时间变量 */
    TopologicalSort(GL);                                /* 求拓扑序列，计算数组etv和stack2的值 */
    ltv = (int *)malloc(GL->numVertexes * sizeof(int)); /* 事件最早发生时间数组 */
    for (i = 0; i < GL->numVertexes; i++)
    {
        ltv[i] = etv[GL->numVertexes - 1];
    }
    while (top2 != 0) //求解ltv
    {
        gettop = stack2[top2--];
        for (e = GL->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            if (ltv[k] - e->weight < ltv[gettop])
            {
                ltv[gettop] = ltv[k] - e->weight;
            }
        }
    }

    printf("etv:\t");
    for (i = 0; i < GL->numVertexes; i++)
    {
        printf("%d -> ", etv[i]);
    }
    printf("\n");

    printf("ltv:\t");
    for (i = 0; i < GL->numVertexes; i++)
    {
        printf("%d -> ", ltv[i]);
    }
    printf("\n");

    for (j = 0; j < GL->numVertexes; j++)
    {
        for (e = GL->adjList[j].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            ete = etv[j];
            lte = ltv[k] - e->weight;
            if (ete == lte)
            {
                printf("<v%d - v%d> length: %d \n", GL->adjList[j].data, GL->adjList[k].data, e->weight);
            }
        }
    }
}

/******************主函数*************************************/
void main()
{
    MGraph G;
    GraphAdjList GL;
    CreateMGraph(&G);
    CreateALGraph(G, &GL);
    CriticalPath(GL);
}
