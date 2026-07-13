#include "graph.h"

// 创建图的邻接表
void createGraph(ALGraph *graph)
{
    int i = 0;
    int k = 0;

    if (graph == NULL)
    {
        printf("图对象为空，无法创建！\n");
        return;
    }

    // 先清空原有内容，避免重复调用时残留旧数据
    graph->nodenum = 0;
    graph->edgnum = 0;
    for (i = 0; i < MAXNUM; i++)
    {
        graph->roadlist[i].data[0] = '\0';
        graph->roadlist[i].first = NULL;
    }

    printf("请输入旅游图的景点数和边数：");
    if (scanf("%d %d", &graph->nodenum, &graph->edgnum) != 2)
    {
        printf("输入格式错误，创建失败！\n");
        return;
    }

    if (graph->nodenum <= 0 || graph->nodenum > MAXNUM || graph->edgnum < 0)
    {
        printf("输入的景点数或边数非法，创建失败！\n");
        return;
    }

    for (i = 0; i < graph->nodenum; i++) // 录入景点
    {
        printf("请输入第%d个景点名称：", i + 1);
        if (scanf("%9s", graph->roadlist[i].data) != 1)
        {
            printf("景点名称输入错误，创建失败！\n");
            return;
        }
        graph->roadlist[i].first = NULL;
    }

    for (k = 0; k < graph->edgnum; k++) // 录入边
    {
        int length = 0;
        char c1[10], c2[10];
        int vi = -1;
        int vj = -1;

        printf("请输入第%d条边的两个顶点和长度：", k + 1);
        if (scanf("%9s %9s %d", c1, c2, &length) != 3)
        {
            printf("输入格式错误，本条边录入失败！\n");
            continue;
        }

        vi = locate(*graph, c1);
        vj = locate(*graph, c2);
        if (vi == -1 || vj == -1)
        {
            printf("警告：输入景点名称不存在，本条边录入失败！\n");
            continue;
        }
        if (length < 0)
        {
            printf("警告：边长不能为负，本条边录入失败！\n");
            continue;
        }

        CNode *node1 = (CNode *)malloc(sizeof(CNode));
        CNode *node2 = (CNode *)malloc(sizeof(CNode));
        if (node1 == NULL || node2 == NULL)
        {
            printf("内存分配失败，创建中止！\n");
            free(node1);
            free(node2);
            return;
        }

        node1->length = length;
        node2->length = length;
        node1->index = vj;
        node2->index = vi;
        node1->next = graph->roadlist[vi].first;
        graph->roadlist[vi].first = node1;
        node2->next = graph->roadlist[vj].first;
        graph->roadlist[vj].first = node2;
    }

    printf("=====景区景点图创建完成=====\n");
}

// 打印景区景点分布图（邻接矩阵）
void printGraph(ALGraph *graph)
{
    int i = 0;
    int j = 0;
    int **matrix = NULL;

    if (graph == NULL)
    {
        printf("图对象为空，无法显示！\n");
        return;
    }

    if (graph->nodenum <= 0 || graph->nodenum > MAXNUM)
    {
        printf("当前图中没有景点，无法显示！\n");
        return;
    }

    matrix = (int **)malloc(sizeof(int *) * graph->nodenum);
    if (matrix == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    for (i = 0; i < graph->nodenum; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * graph->nodenum);
        if (matrix[i] == NULL)
        {
            for (j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            printf("内存分配失败！\n");
            return;
        }
    }

    // 初始化矩阵
    for (i = 0; i < graph->nodenum; i++)
    {
        for (j = 0; j < graph->nodenum; j++)
        {
            matrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    // 将邻接表中的边信息写入矩阵
    for (i = 0; i < graph->nodenum; i++)
    {
        CNode *p = graph->roadlist[i].first;
        for (; p != NULL; p = p->next)
        {
            if (p->index >= 0 && p->index < graph->nodenum)
            {
                matrix[i][p->index] = p->length;
            }
        }
    }

    printf("=====景区景点分布图=====\n");
    printf("\t");
    for (i = 0; i < graph->nodenum; i++)
    {
        printf("%s\t", graph->roadlist[i].data);
    }
    printf("\n");

    for (i = 0; i < graph->nodenum; i++)
    {
        printf("%s\t", graph->roadlist[i].data);
        for (j = 0; j < graph->nodenum; j++)
        {
            if (matrix[i][j] == INF)
            {
                printf("INF\t");
            }
            else
            {
                printf("%d\t", matrix[i][j]);
            }
        }
        printf("\n");
    }

    for (i = 0; i < graph->nodenum; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void createGuideGraph(ALGraph *graph, ALGraph *guidgraph)
{
    (void)graph;
    (void)guidgraph;
}