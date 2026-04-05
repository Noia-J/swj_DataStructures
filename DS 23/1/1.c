// 2019110610 정성원
// 본인은 이 소스파일을 다른 사라므이 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define SWAP(x, y, t) { t = x; x = y; y = t; }

typedef struct {
    int key;
} element;

int n;

void printArray(element a[], int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");
}

void adjust(element a[], int root, int n) {
    int child;
    int rootkey;
    element temp;

    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root; // 왼쪽 자식

    while (child <= n) {
        if ((child < n) && (a[child].key < a[child + 1].key))
            child++; // 오른쪽 자식이 더 크면 오른쪽 선택

        if (rootkey > a[child].key) // 부모가 더 크면 종료
            break;
        else {
            a[child / 2] = a[child]; // 자식을 부모로 올림
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

void heapSort(element a[], int n) {
    int i;
    element temp;

    for (i = n / 2; i > 0; i--)
        adjust(a, i, n);

    printf("after initialization of max heap...\n");
    printArray(a, n);
    printf("\n");

    for (i = n - 1; i > 0; i--) {
        SWAP(a[1], a[i + 1], temp); // 루트(최대값)와 마지막 요소 교환
        adjust(a, 1, i);            // 힙 재구성

        printf("step %2d: ", n - i);
        printArray(a, n);
    }
}

int main() {
    FILE* fp_in = fopen("input.txt", "r");
    FILE* fp_out = fopen("output.txt", "w");
    element a[MAX_SIZE];
    int i;

    if (fp_in == NULL) {
        printf("input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    fscanf(fp_in, "%d", &n);
    for (i = 1; i <= n; i++) {
        fscanf(fp_in, "%d", &a[i].key);
    }

    printf("<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    printArray(a, n);
    printf("\n");

    printf("<<<<<<<< executing heap sort >>>>>>>>>>\n");
    heapSort(a, n);

    printf("\n<<<<<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>\n");
    printArray(a, n);

    // 파일 저장
    fprintf(fp_out, "%d\n", n);
    for (i = 1; i <= n; i++) fprintf(fp_out, "%d ", a[i].key);

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}