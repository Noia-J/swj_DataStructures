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
    char data; // 문자 출력을 위해 char 형으로 지정
    treePointer leftChild, rightChild;
} node;

treePointer createNode(char data);
treePointer createBinTree();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

treePointer createNode(char data) {
    treePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

treePointer createBinTree() {
    treePointer root = createNode('A');
    treePointer nodeB = createNode('B');
    treePointer nodeC = createNode('C');
    treePointer nodeD = createNode('D');
    treePointer nodeE = createNode('E');

    root->leftChild = nodeB;
    root->rightChild = nodeC;
    nodeB->leftChild = nodeD;
    nodeB->rightChild = nodeE;

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
    printf("creating a binary tree\n\n");

    treePointer root = createBinTree();

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

    // 트리에 할당된 메모리 해제
    // void freeTree(treePointer ptr) {
    //     if (ptr) {
    //         freeTree(ptr->leftChild);
    //         freeTree(ptr->rightChild);
    //         free(ptr);
    //     }
    // }
    // freeTree(root);

    return 0;
}