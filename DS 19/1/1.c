#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

#define MAX_VERTICES 50
#define FALSE 0
#define TRUE 1

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} node;

nodePointer adjLists[MAX_VERTICES] = { NULL };
short int visited[MAX_VERTICES];
int n;

void insertEdge(int u, int v);
void printAdjList(int n);
void dfs(int v);
void reset_visited(void);

int main(void) {
    FILE* fp;
    int e;
    int u, v;

    if ((fp = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Cannot open input.txt\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &n, &e);

    for (int i = 0; i < e; i++) {
        fscanf(fp, "%d %d", &u, &v);
        insertEdge(u, v);
        insertEdge(v, u);
    }
    fclose(fp);

    printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>\n");
    printAdjList(n);

    printf("\n<<<<<<<<<<<<< Depth First Search >>>>>>>>>>>\n");
    for (int i = 0; i < n; i++) {
        reset_visited();
        printf("dfs<%d>: ", i);
        dfs(i);
        printf("\n");
    }

    return 0;
}

void insertEdge(int u, int v) {
    nodePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->vertex = v;
    newNode->link = adjLists[u];
    adjLists[u] = newNode;
}

void printAdjList(int n) {
    for (int i = 0; i < n; i++) {
        printf("graph[%d]: ", i);
        nodePointer current = adjLists[i];
        while (current) {
            printf("%d ", current->vertex);
            current = current->link;
        }
        printf("\n");
    }
}

void dfs(int v) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = adjLists[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex);
        }
    }
}

void reset_visited(void) {
    for (int i = 0; i < n; i++) {
        visited[i] = FALSE;
    }
}