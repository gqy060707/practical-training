#ifndef MENU_H
#define MENU_H

#include<stdio.h>

void showMenu(){
    printf("\n********************\n");
    printf("欢迎使用景区路径规划系统\n");
    printf("请输入您的选择：\n");
    printf("1 创建景区景点图\n");
    printf("2 景区景点分布图\n");
    printf("3 导游路线\n");
    printf("4 导游路线中的回路\n");
    printf("5 两个景点间的最短路径和距离\n");
    printf("0 退出系统\n");
}

#endif