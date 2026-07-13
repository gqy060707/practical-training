#include "travels.h"

void DFSTravels(ALGraph graph)
{
    int i;
    int *visited = (int *)calloc(graph.nodenum, sizeof(int));
    if (visited == NULL) {
        printf("内存分配失败，无法执行深度遍历！\n");
        return;
    }

    printf("深度优先遍历顺序：");
    for (i = 0; i < graph.nodenum; i++) {
        if (!visited[i]) {
            DFS(graph, i, visited);
        }
    }
    printf("\n");
    free(visited);
}

void DFS(ALGraph graph, int i, int visited[])
{
    CNode *p;

    visited[i] = 1;
    printf("%s ", graph.roadlist[i].data);
    p = graph.roadlist[i].first;
    while (p != NULL) {
        if (!visited[p->index]) {
            DFS(graph, p->index, visited);
        }
        p = p->next;
    }
}

int isedg(ALGraph graph, char *e1, char *e2)
{
    int vi = locate(graph, e1);
    int vj = locate(graph, e2);
    if (vi == -1 || vj == -1) {
        return 0;
    }
    CNode *p = graph.roadlist[vi].first;
    while (p != NULL) {
        if (p->index == vj) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

void shortPath(ALGraph graph, int path[][MAXNUM], double shortpath[][MAXNUM])
{
    int i, j, k;
    int n = graph.nodenum;
    if (n <= 0) {
        return;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                shortpath[i][j] = 0;
                path[i][j] = -1;
            } else {
                shortpath[i][j] = INF;
                path[i][j] = -1;
            }
        }
    }

    for (i = 0; i < n; i++) {
        CNode *p = graph.roadlist[i].first;
        while (p != NULL) {
            shortpath[i][p->index] = p->length;
            path[i][p->index] = i;
            p = p->next;
        }
    }

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (shortpath[i][k] >= INF) continue;
            for (j = 0; j < n; j++) {
                if (shortpath[k][j] >= INF) continue;
                if (shortpath[i][k] + shortpath[k][j] < shortpath[i][j]) {
                    shortpath[i][j] = shortpath[i][k] + shortpath[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
}

void printPath(ALGraph graph, int path[][MAXNUM], int i, int j)
{
    if (i == j) {
        printf("%s", graph.roadlist[i].data);
        return;
    }
    if (path[i][j] == -1) {
        printf("无可达路径");
        return;
    }

    int stack[MAXNUM];
    int top = 0;
    int current = j;

    while (current != i) {
        stack[top++] = current;
        current = path[i][current];
        if (current == -1) {
            printf("无可达路径");
            return;
        }
    }

    printf("%s", graph.roadlist[i].data);
    while (top > 0) {
        printf(" -> %s", graph.roadlist[stack[--top]].data);
    }
}

void minDistance(ALGraph graph, int path[][MAXNUM], double shortpath[][MAXNUM])
{
    if (graph.nodenum <= 0) {
        printf("请先创建景区景点图，再进行最短路径查询。\n");
        return;
    }

    shortPath(graph, path, shortpath);

    char start[10];
    char end[10];
    int si, ei;

    printf("请输入起点景点名称：");
    if (scanf("%9s", start) != 1) {
        printf("输入格式错误。\n");
        return;
    }
    printf("请输入终点景点名称：");
    if (scanf("%9s", end) != 1) {
        printf("输入格式错误。\n");
        return;
    }

    si = locate(graph, start);
    ei = locate(graph, end);
    if (si == -1 || ei == -1) {
        printf("输入的景点名称不存在，请检查后重新输入。\n");
        return;
    }

    if (shortpath[si][ei] >= INF) {
        printf("%s 到 %s 之间不存在可达路径。\n", start, end);
        return;
    }

    printf("从 %s 到 %s 的最短路径距离为：%.0f\n", start, end, shortpath[si][ei]);
    printf("最短路径为：");
    printPath(graph, path, si, ei);
    printf("\n");
}
