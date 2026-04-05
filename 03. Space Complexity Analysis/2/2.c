//2019110610
//본인은 이 소스 파일을 다른 사람의 코드를 복사하지 않고 직접 작성하였습니다.

#include <stdio.h>

int count = 0;

void add(int a[][4], int b[][4], int c[][4], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        count += 2;
        for (j = 0; j < cols; j++) {
            c[i][j] = a[i][j] + b[i][j];
            count += 2;
        }
    }
    count++;
}

int main(void) {
    int a[3][4], b[3][4], c[3][4];
    int i, j;

    FILE* fpA, * fpB;

    fpA = fopen("a.txt", "r");

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            fscanf(fpA, "%d", &a[i][j]);
        }
    }
    fclose(fpA);

    fpB = fopen("b.txt", "r");

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            fscanf(fpB, "%d", &b[i][j]);
        }
    }
    fclose(fpB);

    add(a, b, c, 3, 4);

    printf("step count : %d\n", count);

    return 0;
}