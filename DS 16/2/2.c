//2019110610 정성원
//본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 // MALLOC 매크로
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 81

// 명제식 트리 정의
#define TRUE 1
#define FALSE 0

typedef enum { NOT, AND, OR, TRUE_CONST, FALSE_CONST } logical;
typedef enum { lparen, rparen, or_op, and_op, not_op, eos, operand } precedence;

typedef struct node* treePointer;
typedef struct node {
    treePointer leftChild;
    logical data;
    char var;
    short int value;
    treePointer rightChild;
} tNode;

treePointer root = NULL;
treePointer stack[MAX_STACK_SIZE];
int top = -1;
char expr[MAX_EXPR_SIZE];

void postOrderEval(treePointer node);
precedence getToken(char* symbol, int* n);
treePointer createBinTree(void);
treePointer createNode(char symbol, precedence token);
void inorder(treePointer ptr);
void push(treePointer item);
treePointer pop(void);

short int var_values[3] = { FALSE, FALSE, FALSE };

int main(void) {
    FILE* fp;

    printf("************* satisfiability problem *************\n");
    printf("Note: For efficiency, &, |, ~ are used instead of\n");
    printf("logical and(&&), logical or(||), logical not (!)\n");
    printf("**************************************************\n");

    if ((fp = fopen("postfix.txt", "r")) == NULL) {
        fprintf(stderr, "Cannot open postfix.txt\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%s", expr);
    fclose(fp);

    printf("input string(postfix) : %s\n\n", expr);
    printf("creating binary tree for satisfiability algorithm...\n\n");

    root = createBinTree();

    printf("inorder traversal     : ");
    inorder(root);
    printf("\n\n");

    printf("for all combinations of (a, b, c)...\n");

    for (int i = 1; i >= 0; i--) {    
        for (int j = 1; j >= 0; j--) { 
            for (int k = 1; k >= 0; k--) { 
                var_values[0] = i;
                var_values[1] = j;
                var_values[2] = k;

                postOrderEval(root);

                printf("(%c, %c, %c) is %s\n",
                    (i == TRUE ? 't' : 'f'),
                    (j == TRUE ? 't' : 'f'),
                    (k == TRUE ? 't' : 'f'),
                    (root->value == TRUE ? "TRUE" : "FALSE"));
            }
        }
    }

    return 0;
}

void push(treePointer item) {
    if (top >= MAX_STACK_SIZE - 1) exit(EXIT_FAILURE);
    stack[++top] = item;
}

treePointer pop(void) {
    if (top == -1) return NULL;
    return stack[top--];
}

precedence getToken(char* symbol, int* n) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '|': return or_op;
    case '&': return and_op;
    case '~': return not_op;
    case '\0': return eos;
    default: return operand;
    }
}

treePointer createNode(char symbol, precedence token) {
    treePointer pNode;
    MALLOC(pNode, sizeof(*pNode));
    pNode->leftChild = NULL;
    pNode->rightChild = NULL;
    pNode->value = FALSE;

    if (token == operand) {
        pNode->var = symbol;
    }
    else {
        pNode->var = '\0';
        switch (token) {
        case not_op: pNode->data = NOT; break;
        case and_op: pNode->data = AND; break;
        case or_op:  pNode->data = OR; break;
        default: break;
        }
    }
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
        pNode = createNode(symbol, token);
        if (token != operand) {
            pNode->rightChild = pop();
            if (token != not_op) {
                pNode->leftChild = pop();
            }
        }
        push(pNode);
        token = getToken(&symbol, &n);
    }
    return pop();
}

void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        switch (ptr->data) {
        case NOT: printf("~"); break;
        case AND: printf("&"); break;
        case OR:  printf("|"); break;
        default: 
            printf("%c", ptr->var); break;
        }

        inorder(ptr->rightChild);
    }
}

void postOrderEval(treePointer node) {
    if (node) {
        postOrderEval(node->leftChild);
        postOrderEval(node->rightChild);

        switch (node->data) {
        case NOT:
            node->value = !node->rightChild->value;
            break;
        case AND:
            node->value = node->leftChild->value && node->rightChild->value;
            break;
        case OR:
            node->value = node->leftChild->value || node->rightChild->value;
            break;
        default: 
            if (node->var == 'a') node->value = var_values[0];
            else if (node->var == 'b') node->value = var_values[1];
            else if (node->var == 'c') node->value = var_values[2];
            break;
        }
    }
}