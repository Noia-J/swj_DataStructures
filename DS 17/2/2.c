// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

typedef int iType;
typedef struct {
    int key;
    iType item;
} element;
typedef struct node* treePointer;
typedef struct node {
    element data;
    treePointer leftChild, rightChild;
} node;

element* search(treePointer root, int k);
treePointer modifiedSearch(treePointer node, int k);
void insert(treePointer* node, int k, iType theItem);
void inorder(treePointer ptr);

int main(void) {
    int n, seed, key, searchKey;
    treePointer root = NULL;
    element* found;

    printf("random number generation (1 ~ 500)\n");
    printf("the number of nodes in BST (less than and equal to 50) : ");
    scanf("%d", &n);
    if (n > 50) n = 50;

    printf("seed : ");
    scanf("%d", &seed);
    srand(seed);

    printf("\ncreating a BST from random numbers\n");
    for (int i = 0; i < n; ) {
        key = (rand() % 500) + 1;

        if (search(root, key) == NULL) {
            insert(&root, key, key);
            i++;
        }
    }

    printf("the key to search : ");
    scanf("%d", &searchKey);

    found = search(root, searchKey);
    if (found) {
        printf("the element's item is %d\n", found->item);
    }
    else {
        printf("there is no such an element\n");
    }

    printf("\ninorder traversal of the BST shows the sorted sequence\n ");
    inorder(root);
    printf("\n");

    return 0;
}

element* search(treePointer root, int k) {
    if (!root) return NULL;
    if (k == root->data.key) return &(root->data);
    if (k < root->data.key)
        return search(root->leftChild, k);
    return search(root->rightChild, k);
}

treePointer modifiedSearch(treePointer tree, int k) {
    treePointer parent = NULL;

    if (!tree) return NULL;

    while (tree) {
        parent = tree;
        if (k == tree->data.key) {
            return NULL;
        }
        if (k < tree->data.key) {
            tree = tree->leftChild;
        }
        else {
            tree = tree->rightChild;
        }
    }
    return parent;
}

void insert(treePointer* node, int k, iType theItem) {
    treePointer ptr, temp = modifiedSearch(*node, k);

    if (temp || !(*node)) {
        MALLOC(ptr, sizeof(*ptr));
        ptr->data.key = k;
        ptr->data.item = theItem;
        ptr->leftChild = ptr->rightChild = NULL;
        if (*node) {
            if (k < temp->data.key) temp->leftChild = ptr;
            else temp->rightChild = ptr;
        }
        else {
            *node = ptr;
        }
    }
}

void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data.key);
        inorder(ptr->rightChild);
    }
}