#include <stdio.h>

#define INFINITY 65535 //用65535来代表无穷大∞
#define MAX 100        //定义最大顶点数

//定义图的邻接矩阵存储方式结构体
typedef struct
{
    char vexs[MAX];      //顶点表
    int arc[MAX][MAX];   //邻接矩阵
    int vexsnum, arcnum; //图中的顶点数和边数
} MGraph;

//建立无向网图的邻接矩阵表示
void CreateMGraph(MGraph *G)
{
    int i, j, k, w;
    printf("请输入图的顶点数和边数：\n");
    scanf("%d%d", &G->vexsnum, &G->arcnum);
    for (i = 0; i < G->vexsnum; i++)
    {
        printf("请输入顶点数据：\n");
        scanf("%d", &G->vexs[i]);
    }
    for (i = 0; i < G->arcnum; i++)
    {
        for (j = 0; j < G->arcnum; j++)
        {
            G->arc[i][j] = INFINITY;
        }
    }
    for (k = 0; k < G->arcnum; k++)
    {
        printf("输入边(vi,vj)上的下标i，下标j和权w:\n");
        // scanf("%d,%d,%d", &i, &j, &w); //非常不建议在%d中间加逗号！
        //详见https://github.com/Hawaii-98/blog/blob/main/Some%20points%20about%20C/%E4%BD%BF%E7%94%A8scanf%E7%9A%84%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9
        scanf("%d%d%d", &i, &j, &w);
        G->arc[i][j] = w;
        G->arc[i][i] = w; //对称矩阵
    }
}

/****************主函数*********************/
void main()
{
    MGraph G;
    CreateMGraph(&G); //与键盘交互时注意输入的格式（与scanf函数设置格式应一致）
}
