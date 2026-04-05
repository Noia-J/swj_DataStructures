#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define SWAP(x, y, t) { t = x; x = y; y = t; }

typedef struct {
    int key;
} element;

int callCount = 0;
int n;

void printState(element a[], int left, int right) {
    for (int i = 1; i <= n; i++) {
        printf("%4d", a[i].key);
    }
    printf(": %4d %4d\n", left, right);
}

void quickSort(element a[], int left, int right) {
    int pivot, i, j;
    element temp;

    printState(a, left, right);
    callCount++;

    if (left < right) {
        i = left;
        j = right + 1;
        pivot = a[left].key;

        do {
            do { i++; } while (i <= right && a[i].key < pivot);
            do { j--; } while (j >= left && a[j].key > pivot);
            if (i < j) SWAP(a[i], a[j], temp);
        } while (i < j);

        SWAP(a[left], a[j], temp);

        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

int main() {
    FILE* fp_in = fopen("input.txt", "r");
    element a[MAX_SIZE];
    int i;

    if (fp_in == NULL) return 1;

    fscanf(fp_in, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(fp_in, "%d", &a[i].key);
    }

    printf("<<<<<<<<<<<< Input List >>>>>>>>>>>>\n");
    for (i = 1; i <= n; i++) printf("%d ", a[i].key);
    printf("\n\n");

    printf("execution of quick sort ...\n");

    for (i = 1; i <= n; i++) printf("[%2d] ", i);
    printf("[left right]\n");

    quickSort(a, 1, n);

    printf("calls of quick sort: %d\n", callCount);

    printf("\n<<<<<<<<<<<< Sorted List >>>>>>>>>>>>\n");
    for (i = 1; i <= n; i++) printf("%d ", a[i].key);
    printf("\n");

    fclose(fp_in);
    return 0;
}