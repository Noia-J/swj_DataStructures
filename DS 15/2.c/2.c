// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100 
#define MAX_EXPR_SIZE 81

typedef struct node* treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer stack[MAX_STACK_SIZE];
int top = -1;

treePointer queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

char expr[MAX_EXPR_SIZE];
treePointer createBinTree(void);
treePointer createNode(char data);
precedence getToken(char* symbol, int* n);
void push(treePointer item);
treePointer pop(void);
void queueFull(void);
void addq(treePointer item);
treePointer deleteq(void);
void iterInorder(treePointer node);
void iterPreorder(treePointer node);
void levelOrder(treePointer ptr);

int main(void) {
    FILE* fp;
    treePointer root;

    printf("the length of input string should be less than 80\n");


    if ((fp = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Cannot open input.txt\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%s", expr);
    fclose(fp);

    printf("input string (postfix expression) : %s\n", expr);
    printf("creating its binary tree\n\n");

    root = createBinTree();

    printf("Iterative inorder traversal   : ");
    iterInorder(root);
    printf("\n");

    printf("Iterative preorder traversal  : ");
    iterPreorder(root);
    printf("\n");

    printf("level order traversal         : ");
    levelOrder(root);
    printf("\n");

    return 0;
}


void push(treePointer item) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack is full.\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = item;
}

treePointer pop(void) {
    if (top == -1) {
        return NULL;
    }
    return stack[top--];
}

void queueFull(void) {
    fprintf(stderr, "Queue is full, cannot add element.\n");
    exit(EXIT_FAILURE);
}

void addq(treePointer item) {
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (front == rear)
        queueFull();
    queue[rear] = item;
}

treePointer deleteq(void) {
    if (front == rear)
        return NULL;
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

precedence getToken(char* symbol, int* n) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '+': return plus;
    case '-': return minus;
    case '*': return times;
    case '/': return divide;
    case '%': return mod;
    case '\0': return eos;
    default: return operand;
    }
}

treePointer createNode(char data) {
    treePointer pNode;
    MALLOC(pNode, sizeof(*pNode));
    pNode->data = data;
    pNode->leftChild = NULL;
    pNode->rightChild = NULL;
    return pNode;
}

treePointer createBinTree(void) {
    treePointer pNode;
    precedence token;
    char symbol;
    int n = 0;
    top = -1;

    token = getToken(&symbol, &n);
    while (token != eos) {
        pNode = createNode(symbol);
        if (token != operand) {
            pNode->rightChild = pop();
            pNode->leftChild = pop();
        }
        push(pNode);
        token = getToken(&symbol, &n);
    }
    return pop();
}

void iterInorder(treePointer node) {
    top = -1;
    for (;;) {
        for (; node; node = node->leftChild)
            push(node);
        node = pop();
        if (!node) break;
        printf("%c", node->data);
        node = node->rightChild;
    }
}

void iterPreorder(treePointer node) {
    top = -1;
    if (!node) return;
    push(node);
    while (top != -1) {
        node = pop();
        if (node) {
            printf("%c", node->data);
            if (node->rightChild)
                push(node->rightChild);
            if (node->leftChild)
                push(node->leftChild);
        }
    }
}

void levelOrder(treePointer ptr) {
    front = rear = 0;
    if (!ptr) return;
    addq(ptr);
    for (;;) {
        ptr = deleteq();
        if (ptr) {
            printf("%c", ptr->data);
            if (ptr->leftChild)
                addq(ptr->leftChild);
            if (ptr->rightChild)
                addq(ptr->rightChild);
        }
        else {
            break;
        }
    }
}