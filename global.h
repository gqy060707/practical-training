#ifndef GLOBAL_H
#define GLOBAL_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXNUM 100
#define INF 32767

typedef struct stCNode{
    int index;
    struct stCNode*next;
    int length;
}CNode;//边节点信息

typedef struct stHNode{
    char data[10];
    CNode *first;
}HNode,RoadList[MAXNUM];//顶点信息

typedef struct stGraph{
    RoadList roadlist;
    int nodenum;
    int edgnum;
}ALGraph;//ALGraph 图的邻接表

int locate(ALGraph graph,char *e);//定位

#endif
