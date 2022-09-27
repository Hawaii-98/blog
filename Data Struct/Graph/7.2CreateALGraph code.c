#include <stdio.h>
#include <stdlib.h>

#define MAX 100 //最大顶点数

//建立边表结点结构体（存储边的表的结点结构体）
typedef struct EdgeNode
{
    int adjvex;            //邻接点域,存储该顶点对应的下标
    int weight;            //用于存储权值,对于非网图可以不需要
    struct EdgeNode *next; //链域,指向下一个邻接点
} EdgeNode;

//建立顶点表结点结构体（存储顶点的表的结点结构体）
typedef struct
{
    char data;           // 顶点域,存储顶点信息
    EdgeNode *firstedge; //边表头指针
} VertexNode;

typedef VertexNode AdjList[MAX]; //定义一个顶点数组

//建立图结构体指针
typedef struct
{
    AdjList adjList;
    int NodeNum, EdgeNum;
} ALGraph;

//建立无向图的邻接表结构
void CreateALGraph(ALGraph *G)
{
    int i, j, k, w;
    EdgeNode *e; //声明边表结点变量
    printf("输入顶点数和边数:\n");
    scanf("%d%d", &G->NodeNum, &G->EdgeNum); // 输入顶点数和边数
    for (i = 0; i < G->NodeNum; i++)         //读入顶点信息,建立顶点表
    {
        printf("输入顶点数据:\n");        //注意提示输入的语句不要忽略！
        scanf("%d", &G->adjList[i].data); //注意此处的写法！！->和.要区分开！//输入顶点信息
        G->adjList[i].firstedge = NULL;   //将边表置为空表
    }
    for (k = 0; k < G->EdgeNum; k++) //建立边表
    {
        printf("输入边(vi,vj)上的顶点序号:\n");
        scanf("%d%d", &i, &j);                    //输入边(vi,vj)上的顶点序号
        e = (EdgeNode *)malloc(sizeof(EdgeNode)); //向内存申请空间,生成边表结点
        e->adjvex = j;                            //邻接序号设置为j，即此时该顶点对应的下标；
        e->next = G->adjList[i].firstedge;        //将e的指针指向当前顶点的边表头指针指向的结点
        G->adjList[i].firstedge = e;              //---头插法

        e = (EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
        e->adjvex = i;                            /* 邻接序号为i */
        e->next = G->adjList[j].firstedge;        /* 将e的指针指向当前顶点上指向的结点 */
        G->adjList[j].firstedge = e;              /* 将当前顶点的指针指向e */
    }
}

/************主函数********************/
void main()
{
    ALGraph G;
    CreateALGraph(&G);
}
