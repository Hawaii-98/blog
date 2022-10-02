#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define GRAPH_INFINITY 65535

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

//定义图的邻接矩阵存储方式结构体
typedef struct
{
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

typedef int Patharc[MAXVEX];        /* 用于存储最短路径下标的数组 */
typedef int ShortPathTable[MAXVEX]; /* 用于存储到各点最短路径的权值和 */

//建立无向图
void CreateMGraph(MGraph *G)
{
    int i, j;

    /* printf("请输入边数和顶点数:"); */
    G->numEdges = 16;
    G->numVertexes = 9;

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
                G->arc[i][j] = G->arc[j][i] = GRAPH_INFINITY;
        }
    }

    G->arc[0][1] = 1;
    G->arc[0][2] = 5;
    G->arc[1][2] = 3;
    G->arc[1][3] = 7;
    G->arc[1][4] = 5;

    G->arc[2][4] = 1;
    G->arc[2][5] = 7;
    G->arc[3][4] = 2;
    G->arc[3][6] = 3;
    G->arc[4][5] = 3;

    G->arc[4][6] = 6;
    G->arc[4][7] = 9;
    G->arc[5][7] = 5;
    G->arc[6][7] = 2;
    G->arc[6][8] = 7;

    G->arc[7][8] = 4;

    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

// Dijkstra算法，求无向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v]
void Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D)
{
    int v, w, k, min;
    int final[MAXVEX];
    for (v = 0; v < G.numVertexes; v++)
    {
        final[v] = 0;
        (*D)[v] = G.arc[v0][v];
        (*P)[v] = -1;
    }
    final[v0] = 1;
    (*D)[v0] = 0;
    for (w = 1; w < G.numVertexes; w++)
    {
        int j;
        min = GRAPH_INFINITY;
        for (j = 0; j < G.numVertexes; j++)
        {
            if (!final[j] && (*D)[j] < min)
            {
                k = j;
                min = (*D)[j];
            }
        }
        final[k] = 1;
        for (j = 0; j < G.numVertexes; j++)
        {
            if (!final[j] && (min + G.arc[k][j] < (*D)[j]))
            {
                (*D)[j] = min + G.arc[k][j];
                (*P)[j] = k;
            }
        }
    }
}

//打印最短路径及路径长度
void printshortpath(MGraph G, int v0, Patharc P, ShortPathTable D)
{
    int i, j;
    printf("最短路径倒序如下:\n");
    for (i = 1; i < G.numVertexes; i++)
    {
        printf("v%d - v%d : ", v0, i);

        j = i;
        while (P[j] != -1)
        {
            printf("%d ", P[j]);
            j = P[j];
        }
        printf("\n");
    }
    printf("\n源点到各顶点的最短路径长度为:\n");
    for (i = 1; i < G.numVertexes; ++i)
        printf("v%d - v%d : %d \n", G.vexs[0], G.vexs[i], D[i]);
}

/******************主函数***********************************/
void main()
{
    MGraph G;
    Patharc P;
    ShortPathTable D;
    int v0 = 0;
    CreateMGraph(&G);
    Dijkstra(G, v0, &P, &D);
    printshortpath(G, v0, P, D);
}
