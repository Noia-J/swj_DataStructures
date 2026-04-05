#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

void merge(element initList[], element mergedList[], int i, int m, int n) {
    int j, k, t;
    j = m + 1;
    k = i;

    while (i <= m && j <= n) {
        if (initList[i].key <= initList[j].key)
            mergedList[k++] = initList[i++];
        else
            mergedList[k++] = initList[j++];
    }
    if (i > m) {
        for (t = j; t <= n; t++) mergedList[t] = initList[t];
    }
    else {
        for (t = i; t <= m; t++) mergedList[k + t - i] = initList[t];
    }
}

void mergePass(element initList[], element mergedList[], int n, int s) {
    int i, j;
    for (i = 1; i <= n - 2 * s + 1; i += 2 * s) {
        merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
    }
    if (i + s - 1 < n) {
        merge(initList, mergedList, i, i + s - 1, n);
    }
    else {
        for (j = i; j <= n; j++)
            mergedList[j] = initList[j];
    }
}

void printArray(const char* name, element list[], int n) {
    printf("%5s :", name);
    for (int i = 1; i <= n; i++) {
        printf(" %d", list[i].key);
    }
    printf("\n");
}

void mergeSort(element a[], int n) {
    int s = 1;
    element extra[MAX_SIZE];

    printf("<<<<< executing itterative merge sort >>>>>\n");

    while (s < n) {
        printf("segment size : %d\n", s);
        mergePass(a, extra, n, s);
        printArray("a", a, n);
        printArray("extra", extra, n);
        s *= 2;

        printf("\nsegment size : %d\n", s);
        mergePass(extra, a, n, s);
        printArray("extra", extra, n);
        printArray("a", a, n);
        s *= 2;

        printf("\n");
    }
}

int main() {
    FILE* fp_in = fopen("input.txt", "r");
    element a[MAX_SIZE];
    int n, i;

    if (fp_in == NULL) return 1;

    fscanf(fp_in, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(fp_in, "%d", &a[i].key);
    }

    printf("<<<<<<<<<<<< Input List >>>>>>>>>>>>\n");
    for (i = 1; i <= n; i++) printf("%d ", a[i].key);
    printf("\n\n");

    mergeSort(a, n);

    printf("<<<<<<<<<<<< Sorted List >>>>>>>>>>>>\n");
    for (i = 1; i <= n; i++) printf("%d ", a[i].key);
    printf("\n");

    fclose(fp_in);
    return 0;
}