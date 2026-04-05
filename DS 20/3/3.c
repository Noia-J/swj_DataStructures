// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char name[20];
    int grade;
} element;

void insertionSort(element a[], int n);
void insert(element e, element a[], int i);

int main() {
    FILE* fp_in, * fp_out;
    int n;
    element* list;

    fp_in = fopen("input.txt", "r");
    if (fp_in == NULL) {
        fprintf(stderr, "Cannot open input.txt\n");
        exit(1);
    }

    fscanf(fp_in, "%d", &n);

    list = (element*)malloc(sizeof(element) * (n + 1));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    printf("<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
    for (int i = 1; i <= n; i++) {
        fscanf(fp_in, "%d %s %d", &list[i].key, list[i].name, &list[i].grade);
        printf("< %d, %s, %d >\n", list[i].key, list[i].name, list[i].grade);
    }
    fclose(fp_in);

    insertionSort(list, n);

    fp_out = fopen("output.txt", "w");
    if (fp_out == NULL) {
        fprintf(stderr, "Cannot open output.txt\n");
        exit(1);
    }

    printf("\n<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
    for (int i = 1; i <= n; i++) {
        printf("< %d, %s, %d >\n", list[i].key, list[i].name, list[i].grade);
        fprintf(fp_out, "< %d, %s, %d >\n", list[i].key, list[i].name, list[i].grade);
    }
    fclose(fp_out);

    free(list);
    return 0;
}

void insert(element e, element a[], int i) {
    a[0] = e;
    while (e.key < a[i].key) {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

void insertionSort(element a[], int n) {
    int j;
    for (j = 2; j <= n; j++) {
        element temp = a[j];
        insert(temp, a, j - 1);
    }
}