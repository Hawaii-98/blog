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

//建立邻接矩阵表示的图结构
void CreateMGraph(MGraph *G)
{
    int i, j;

    G->numEdges = MAXEDGE;
    G->numVertexes = MAXVEX;

    for (i = 0; i < G->numVertexes; i++) /* 初始化图 */
    {
        G->vexs[i] = i;
    }

    for (i = 0; i < G->numVertexes; i++) /* 初始化图 */
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = 0;
        }
    }

    G->arc[0][4] = 1;
    G->arc[0][5] = 1;
    G->arc[0][11] = 1;
    G->arc[1][2] = 1;
    G->arc[1][4] = 1;
    G->arc[1][8] = 1;
    G->arc[2][5] = 1;
    G->arc[2][6] = 1;
    G->arc[2][9] = 1;
    G->arc[3][2] = 1;
    G->arc[3][13] = 1;
    G->arc[4][7] = 1;
    G->arc[5][8] = 1;
    G->arc[5][12] = 1;
    G->arc[6][5] = 1;
    G->arc[8][7] = 1;
    G->arc[9][10] = 1;
    G->arc[9][11] = 1;
    G->arc[10][13] = 1;
    G->arc[12][9] = 1;
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
            if (G.arc[i][j] == 1)
            {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                e->adjvex = j;                         /* 邻接序号为j  */
                e->next = (*GL)->adjList[i].firstedge; /* 将当前顶点上的指向的结点指针赋值给e */
                (*GL)->adjList[i].firstedge = e;       /* 将当前顶点的指针指向e  */
                (*GL)->adjList[j].in++;
            }
        }
    }
}

//拓扑排序，若GL无回路，则输出拓扑排序序列并打印提示，若有回路也打印提示
void TopologicalSort(GraphAdjList GL)
{
    EdgeNode *e;
    int i, k, gettop;
    int top = 0;
    int count = 0;
    int *stack; //此处使用的是顺序栈
    stack = (int *)malloc(GL->numVertexes * sizeof(int));
    for (i = 0; i < GL->numVertexes; i++)
    {
        if ((GL->adjList[i].in) == 0) //这里需要特别注意->和.符号的使用
        {
            stack[++top] = i; //此处从栈的第1号位置开始存储,为下面的主循环做铺垫
        }
    }
    while (top != 0)
    {
        gettop = stack[top--];
        printf("%d -> ", GL->adjList[gettop].data);
        count++;
        for (e = GL->adjList[gettop].firstedge; e; e = e->next) // e一直遍历边表结点直到指向空（此时e=0）
        {
            k = e->adjvex;
            if (!(--(GL->adjList[k].in)))
            {
                stack[++top] = k;
            }
        }
    }
    printf("\n");
    if (count < GL->numVertexes)
    {
        printf("结点不完整输出，图中有环存在！\n");
    }
    else
    {
        printf("结点完整输出，图中无环存在！\n");
    }
}
/************************主函数***************************/
void main()
{
    MGraph G;
    GraphAdjList GL;
    int result;
    CreateMGraph(&G);
    CreateALGraph(G, &GL);
    TopologicalSort(GL);
}
