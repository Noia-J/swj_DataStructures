// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) ((p)=malloc(s))
void inputMatrix(int** ary, int rows, int cols); // 사용자 데이터 입력
void printMatrix(int** ary, int rows, int cols); // 행렬 출력
void addMatrix(int** a, int** b, int** c, int rows, int cols); // 덧셈
int** make2dArray(int rows, int cols); // 2차원 배열 동적할당
void free2dArray(int** ary, int rows); // 2차원 배열 메모리 해제

int main(void)
{
	int rows, cols;
	int** matrixA, ** matrixB, ** matrixC;
	printf("Enter row size and column size (ex) 2 3 >> ");
	scanf("%d %d", &rows, &cols);

	matrixA = make2dArray(rows, cols);
	matrixB = make2dArray(rows, cols);
	matrixC = make2dArray(rows, cols);

	printf("Input data for %d x %d matrix A >> ", rows, cols);
	inputMatrix(matrixA, rows, cols);
	printf("Input data for %d x %d matrix B >> ", rows, cols);
	inputMatrix(matrixB, rows, cols);

	addMatrix(matrixA, matrixB, matrixC, rows, cols);
	printf("\nMatrix A\n");
	printMatrix(matrixA, rows, cols);
	printf("\nMatrix B\n");
	printMatrix(matrixB, rows, cols);
	printf("\nMatrix C\n");
	printMatrix(matrixC, rows, cols);

	free2dArray(matrixA, rows);
	free2dArray(matrixB, rows);
	free2dArray(matrixC, rows);

	printf("\n2d array - free!!!\n");
	printf("계속하려면 아무 키나 누르십시오. . .");
	getchar(); // 키 입력 대기 (결과 확인용)

	return 0;
}

int** make2dArray(int rows, int cols)
{
	int** ary, i;

	MALLOC(ary, rows * sizeof(*ary));
	for (i = 0; i < rows; i++)
		MALLOC(ary[i], cols * sizeof(**ary));

	return ary;
}

void addMatrix(int** a, int** b, int** c, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}

void inputMatrix(int** ary, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			scanf("%d", &ary[i][j]);
		}
	}
}

void printMatrix(int** ary, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d ", ary[i][j]);
		}
		printf("\n"); // 한 행을 다 출력한 후 줄바꿈
	}
}

void free2dArray(int** ary, int rows)
{
	int i;
	for (i = 0; i < rows; i++)
		free(ary[i]);
	free(ary);
}