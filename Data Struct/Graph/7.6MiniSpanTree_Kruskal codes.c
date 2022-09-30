#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAXEDGE 20
#define MAXVEX 20
#define GRAPH_INFINITY 65535

//建立图的邻接矩阵结构体
typedef struct
{
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

//建立边集数组结构体
typedef struct
{
    int begin;
    int end;
    int weight;
} Edge; /* 对边集数组Edge结构的定义 */

//创建网
void CreateMGraph(MGraph *G)
{
    int i, j;

    G->numEdges = 15;
    G->numVertexes = 9;

    for (i = 0; i < G->numVertexes; i++) /* 初始化图 */
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            if (i == j)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = G->arc[j][i] = GRAPH_INFINITY;
        }
    }

    G->arc[0][1] = 10;
    G->arc[0][5] = 11;
    G->arc[1][2] = 18;
    G->arc[1][8] = 12;
    G->arc[1][6] = 16;
    G->arc[2][8] = 8;
    G->arc[2][3] = 22;
    G->arc[3][8] = 21;
    G->arc[3][6] = 24;
    G->arc[3][7] = 16;
    G->arc[3][4] = 20;
    G->arc[4][7] = 7;
    G->arc[4][5] = 26;
    G->arc[5][6] = 17;
    G->arc[6][7] = 19;

    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

//利用邻接矩阵构建边集数组
Edge edges[MAXEDGE]; /* 定义边集数组,edge的结构为begin,end,weight,均为整型 */
void CreateEdge(MGraph G)
{
    int i, j, k = 0;
    for (i = 0; i < G.numVertexes - 1; i++)
    {
        for (j = i + 1; j < G.numVertexes; j++)
        {
            if (G.arc[i][j] < GRAPH_INFINITY)
            {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }
}

//对网按权值排序
void sort(Edge edges[], MGraph G)
{
    int i, j, k;
    for (i = 0; i < G.numEdges; i++)
    {
        for (j = i + 1; j < G.numEdges; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                int temp;
                temp = edges[i].begin;
                edges[i].begin = edges[j].begin;
                edges[j].begin = temp;

                temp = edges[i].end;
                edges[i].end = edges[j].end;
                edges[j].end = temp;

                temp = edges[i].weight;
                edges[i].weight = edges[j].weight;
                edges[j].weight = temp;
            }
        }
    }
    printf("权排序之后的边集数组为:\n");
    for (k = 0; k < G.numEdges; k++)
    {
        printf("(%d, %d) %d\n", edges[k].begin, edges[k].end, edges[k].weight);
    }
}

/******************主函数*******************************/
void main()
{
    MGraph G;
    CreateMGraph(&G);
    CreateEdge(G);
    sort(edges, G);
}
