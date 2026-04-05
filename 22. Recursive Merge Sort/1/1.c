// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

int n;

void printList(element a[], int link[]) {
    int i;

    printf("      [ 0]");
    for (i = 1; i <= n; i++) printf("[%2d]", i);
    printf("\n");

    printf("link: %4d", link[0]);
    for (i = 1; i <= n; i++) printf("%4d", link[i]);
    printf("\n");

    printf("   a:     ");
    for (i = 1; i <= n; i++) printf("%4d", a[i].key);
    printf("\n\n");
}

int listMerge(element a[], int link[], int start1, int start2) {
    int last1, last2, lastResult = 0;

    for (last1 = start1, last2 = start2; last1 && last2;) {
        if (a[last1].key <= a[last2].key) {
            link[lastResult] = last1;
            lastResult = last1;
            last1 = link[last1];
        }
        else {
            link[lastResult] = last2;
            lastResult = last2;
            last2 = link[last2];
        }
    }

    if (last1 == 0) link[lastResult] = last2;
    else link[lastResult] = last1;

    return link[0];
}

int rmergeSort_RLV(element a[], int link[], int left, int right) {
    int mid, leftResult, rightResult, mergedResult;

    printf("rmergeSort(a, link, %d, %d)\n", left, right);

    if (left >= right) return left;

    mid = (left + right) / 2;

    rightResult = rmergeSort_RLV(a, link, mid + 1, right);
    leftResult = rmergeSort_RLV(a, link, left, mid);

    mergedResult = listMerge(a, link, leftResult, rightResult);

    printf("listMerged(a, link, %d, %d)\n", left, right);
    printList(a, link);

    return mergedResult;
}

int rmergeSort_LRV(element a[], int link[], int left, int right) {
    int mid, leftResult, rightResult, mergedResult;

    printf("rmergeSort(a, link, %d, %d)\n", left, right);

    if (left >= right) return left;

    mid = (left + right) / 2;

    leftResult = rmergeSort_LRV(a, link, left, mid);
    rightResult = rmergeSort_LRV(a, link, mid + 1, right);

    mergedResult = listMerge(a, link, leftResult, rightResult);

    printf("listMerged(a, link, %d, %d)\n", left, right);
    printList(a, link);

    return mergedResult;
}

void printSortedList(element a[], int link[], int startNode) {
    printf("<<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>>>>>\n");
    int current = startNode;
    while (current != 0) {
        printf("%d ", a[current].key);
        current = link[current];
    }
    printf("\n");
}

int main() {
    FILE* fp;
    element a[MAX_SIZE];
    int link[MAX_SIZE];
    int i;
    int startNode;
    int mode;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    fscanf(fp, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(fp, "%d", &a[i].key);
        link[i] = 0;
    }
    link[0] = 0;
    fclose(fp);

    printf("Select Mode (1: RLV, 2: LRV): ");
    scanf("%d", &mode);

    printf("<<<<<<<<<< startng from initial %d chains. >>>>>>>>>>\n", n);
    printf("<<<<<<<<<<<<<< each of which has one node >>>>>>>>>>>\n");
    printList(a, link);

    printf("<<<<<<<<<< executing recursive merge sort >>>>>>>>>>\n");

    if (mode == 1) {
        startNode = rmergeSort_RLV(a, link, 1, n);
    }
    else {
        startNode = rmergeSort_LRV(a, link, 1, n);
    }

    printSortedList(a, link, startNode);

    return 0;
}