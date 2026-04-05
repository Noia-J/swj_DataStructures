// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ROWS 2
#define COLS 3
void input2dArray(int ary[][COLS], int rows, int cols); // 사용자 데이터 입력
void print2dArray(int ary[][COLS], int rows, int cols); // 행렬 출력
void add(int a[][COLS], int b[][COLS], int c[][COLS], int rows, int cols); // 덧셈

int main(void)
{
	int matrixA[ROWS][COLS];
	int matrixB[ROWS][COLS];
	int matrixC[ROWS][COLS];
	printf("Input data for %d x %d matrix A >> ", ROWS, COLS);
	input2dArray(matrixA, ROWS, COLS);
	printf("Input data for %d x %d matrix B >> ", ROWS, COLS);
	input2dArray(matrixB, ROWS, COLS);
	add(matrixA, matrixB, matrixC, ROWS, COLS);

	printf("\nMatrix A\n");
	print2dArray(matrixA, ROWS, COLS);

	printf("\nMatrix B\n");
	print2dArray(matrixB, ROWS, COLS);

	printf("\nMatrix C\n");
	print2dArray(matrixC, ROWS, COLS);

	printf("\n계속하려면 아무 키나 누르십시오. . .");
	getchar(); // 키 입력 대기 (결과 확인용)

	return 0;

}

void add(int a[][COLS], int b[][COLS], int c[][COLS], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}

void input2dArray(int ary[][COLS], int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			scanf("%d", &ary[i][j]);
		}
	}
}
void print2dArray(int ary[][COLS], int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d ", ary[i][j]);
		}
		printf("\n"); // 한 행을 다 출력한 후 줄바꿈
	}
}

