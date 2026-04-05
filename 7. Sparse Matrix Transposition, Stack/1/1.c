// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 101
#define MAX_COL 101 
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
} term;

void fastTranspose(term a[], term b[]);
void printMatrix(term matrix[]);

int main(void) {
    term a[MAX_TERMS];
    term b[MAX_TERMS];
    FILE* in, * out;

    in = fopen("a.txt", "r");
    if (in == NULL) {
        printf("a.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    fscanf(in, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);
    for (int i = 1; i <= a[0].value; i++) {
        fscanf(in, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
    }
    fclose(in);

    fastTranspose(a, b);

    out = fopen("b.txt", "w");
    if (out == NULL) {
        printf("b.txt 파일을 생성할 수 없습니다.\n");
        return 1;
    }

    fprintf(out, "%d %d %d\n", b[0].row, b[0].col, b[0].value);
    for (int i = 1; i <= b[0].value; i++) {
        fprintf(out, "%d %d %d\n", b[i].row, b[i].col, b[i].value);
    }
    fclose(out);

	printf("A\n");
    printMatrix(a);
    printf("B\n");
    printMatrix(b);

	system("pause");
    return 0;
}

void fastTranspose(term a[], term b[]) {
    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int i, j;
    int numCols = a[0].col;
    int numTerms = a[0].value;

    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) {
        for (i = 0; i < numCols; i++) {
            rowTerms[i] = 0;
        }
        for (i = 1; i <= numTerms; i++) {
            rowTerms[a[i].col]++;
        }

        startingPos[0] = 1;
        for (i = 1; i < numCols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }

        for (i = 1; i <= numTerms; i++) {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void printMatrix(term matrix[]) {
    int i, j;
    int numRows = matrix[0].row;
    int numCols = matrix[0].col;
    int numTerms = matrix[0].value;
    int currentTerm = 1;

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            if (currentTerm <= numTerms && matrix[currentTerm].row == i && matrix[currentTerm].col == j) {
                printf("%3d ", matrix[currentTerm].value);
                currentTerm++;
            }
            else {
                printf("%3d ", 0);
            }
        }
        printf("\n");
    }
}