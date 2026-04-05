// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

#define MAX_VERTICES 50

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} node;

nodePointer adjLists[MAX_VERTICES] = { NULL };

void insertEdge(int u, int v);
void printAdjList(int n);

int main(void) {
    FILE* fp;
    char type;
    int n, e;
    int u, v;

    if ((fp = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Cannot open input.txt\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, " %c %d %d", &type, &n, &e);

    for (int i = 0; i < e; i++) {
        fscanf(fp, "%d %d", &u, &v);
        insertEdge(u, v);
        if (type == 'u') {
            insertEdge(v, u);
        }
    }
    fclose(fp);

    printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>\n");
    printAdjList(n);

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
        printf("adjList[%d]: ", i);
        nodePointer current = adjLists[i];
        while (current) {
            printf("%d ", current->vertex);
            current = current->link;
        }
        printf("\n");
    }
}