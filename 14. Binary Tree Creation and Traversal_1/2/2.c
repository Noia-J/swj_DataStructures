// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

typedef struct node* treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer root = NULL;

#define MAX_QUEUE_SIZE 100 
treePointer queue[MAX_QUEUE_SIZE]; 
int front = -1;
int rear = -1;

int queueEmpty() {
    return (front == rear);
}

int queueFull() {
    return (rear == MAX_QUEUE_SIZE - 1);
}

treePointer getFront() {
    if (queueEmpty()) {
        fprintf(stderr, "Queue is empty, cannot get front element.\n");
        return NULL;
    }
    return queue[front + 1];
}

void addq(treePointer item) {
    if (queueFull()) {
        fprintf(stderr, "Queue is full, cannot add element.\n");
        exit(EXIT_FAILURE); 
    }
    queue[++rear] = item;
}

treePointer deleteq() {
    if (queueEmpty()) {
        fprintf(stderr, "Queue is empty, cannot delete element.\n");
        return NULL; 
    }
    return queue[++front];
}

treePointer createNode(char data) {
    treePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

void insert(treePointer* pRoot, treePointer pNode) {
    treePointer frontNode;

    if (!(*pRoot)) 
    {
        *pRoot = pNode;
    }
    else 
    {
        frontNode = getFront(); 
        if (!frontNode->leftChild) { 
            frontNode->leftChild = pNode;
        }
        else if (!frontNode->rightChild) { 
            frontNode->rightChild = pNode;
        }
        if (frontNode->leftChild && frontNode->rightChild) {
            deleteq();
        }
    }
    addq(pNode);
}

treePointer createCompBinTree(FILE* fp) {
    treePointer pNode;
    char data;
    root = NULL;
    front = rear = -1;

    while (fscanf(fp, " %c", &data) == 1) {
        pNode = createNode(data);
        insert(&root, pNode);
    }
    return root;
}

void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr) {
    if (ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr) {
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
}

int main(void) {
    FILE* fp;

    printf("creating a complete binary tree\n\n");

    if ((fp = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Cannot open input.txt\n");
        exit(EXIT_FAILURE);
    }
    root = createCompBinTree(fp);
    fclose(fp);

    printf("three binary tree traversals\n");

    printf("inorder traversal   : ");
    inorder(root);
    printf("\n");

    printf("preorder traversal  : ");
    preorder(root);
    printf("\n");

    printf("postorder traversal : ");
    postorder(root);
    printf("\n");

    // 생성된 트리의 메모리 해제 (선택 사항)

    return 0;
}