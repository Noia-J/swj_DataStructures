// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n);
element pop(int* n);
void printHeap(int n);

int main(void) {
    FILE* fp;
    element item;
    int initial_n;

    if ((fp = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Cannot open input.txt\n");
        exit(EXIT_FAILURE);
    }

    printf("***** insertion into a max heap *****\n");

    while (fscanf(fp, "%d", &item.key) == 1) {
        push(item, &n);
        printHeap(n);
    }
    fclose(fp);

    initial_n = n;
    printf("***** deletion from a max heap *****\n");

    for (int i = 0; i < initial_n; i++) {
        item = pop(&n);
        printHeap(n);
    }

    return 0;
}

void printHeap(int n) {
    if (n == 0) {
        return;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");
}

void push(element item, int* n) {
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full. \n");
        exit(EXIT_FAILURE);
    }
    i = ++(*n);
    while ((i != 1) && (item.key > heap[i / 2].key)) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = item;
}

element pop(int* n) {
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty\n");
        exit(EXIT_FAILURE);
    }
    item = heap[1];
    temp = heap[(*n)--];
    parent = 1;
    child = 2;
    while (child <= *n) {
        if ((child < *n) && (heap[child].key < heap[child + 1].key))
            child++;
        if (temp.key >= heap[child].key) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}