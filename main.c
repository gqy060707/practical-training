#include "main.h"
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main()
{   
    SetConsoleOutputCP(65001); // 设置输出UTF8
    SetConsoleCP(65001);       // 设置输入UTF8
    ALGraph graph = {0};
    int path[MAXNUM][MAXNUM];
    double shortpath[MAXNUM][MAXNUM];
    int opt = 0;
    char buf[100];
    showMenu();
    while (1)
    {
        printf("请输入你的选择：");
        if (scanf("%99s", buf) != 1) {
            printf("输入错误，请重新输入。\n");
            continue;
        }

        while (1) {
            char *endptr;
            long value = strtol(buf, &endptr, 10);
            if (buf[0] == '\0' || *endptr != '\0') {
                printf("你输入的不是数字，请重新输入你的选择：");
                scanf("%99s", buf);
            } else if (value < 0 || value > 5) {
                printf("你输入的数字有错误，请重新输入你的选择：");
                scanf("%99s", buf);
            } else {
                opt = (int)value;
                break;
            }
        }

        switch (opt) {
        case 0:
            return 0;
        case 1:
            // 创建景区景点图
            createGraph(&graph);
            break;
        case 2:
            if (graph.nodenum <= 0) {
                printf("请先创建景区景点图，再查看分布图。\n");
            } else {
                printGraph(&graph);
            }
            break;
        case 3:
            if (graph.nodenum <= 0) {
                printf("请先创建景区景点图，再查看导游路线。\n");
            } else {
                printf("导游路线图\n");
            }
            break;
        case 4:
            if (graph.nodenum <= 0) {
                printf("请先创建景区景点图，再检查回路。\n");
            } else {
                printf("导游路线中的回路\n");
            }
            break;
        case 5:
            minDistance(graph, path, shortpath);
            break;
        }
    }
    return 0;
}