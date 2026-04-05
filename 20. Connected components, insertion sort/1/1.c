// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} node;

nodePointer graph[MAX_VERTICES];
int visited[MAX_VERTICES];
int n;

void insertEdge(int u, int v);
void printAdjList();
void dfs(int v);
void connected();

int main() {
    FILE* fp;
    int e;
    int u, v;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open input.txt\n");
        exit(1);
    }

    fscanf(fp, "%d %d", &n, &e);

    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
        visited[i] = FALSE;
    }

    for (int i = 0; i < e; i++) {
        fscanf(fp, "%d %d", &u, &v);
        insertEdge(u, v);
        insertEdge(v, u);
    }

    fclose(fp);

    printAdjList();

    printf("\n<<<<<<<<<<<<< Connected Components >>>>>>>>>>\n");
    connected();

    return 0;
}

void insertEdge(int u, int v) {
    nodePointer newNode = (nodePointer)malloc(sizeof(node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    newNode->vertex = v;
    newNode->link = graph[u];
    graph[u] = newNode;
}

void printAdjList() {
    printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        printf("graph[%d] : ", i);
        for (nodePointer w = graph[i]; w; w = w->link) {
            printf("%5d", w->vertex);
        }
        printf("\n");
    }
}

void dfs(int v) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%5d", v);

    for (w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex);
        }
    }
}

void connected() {
    int i;
    int count = 1;

    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("connected component %d : ", count++);
            dfs(i);
            printf("\n");
        }
    }
}