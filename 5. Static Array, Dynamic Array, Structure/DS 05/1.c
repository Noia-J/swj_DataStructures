// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int sumAry2D_f1(int ary[][3], int rows, int cols);
int sumAry2D_f2(int (*ary)[3], int rows, int cols);
int sumAry2D_f3(int ary[2][3], int rows, int cols);
int sumAry2D_f4(int** ary, int rows, int cols);
int sumAry2D_f5(int*** ary, int rows, int cols);
int freeAry2D(int** ary, int rows);

int main(void)
{
	// 정적 할당의 2차원 배열(2행3열)
	int ary2D[2][3] = { {1,2,3}, {4,5,6} };

	// 동적 할당의 2차원 배열(2행3열)
	int r, c;
	int** ary = (int**)malloc(2 * sizeof(int*));
	for (r = 0; r < 2; r++)
		ary[r] = (int*)malloc(3 * sizeof(int));

	for (r = 0; r < 2; r++)
		for (c = 0; c < 3; c++)
			ary[r][c] = r + c;

	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary2D, 2, 3));

	printf("sumAry2D_f4() %d\n", sumAry2D_f4(ary, 2, 3));
	printf("sumAry2D_f5() %d\n", sumAry2D_f5(&ary, 2, 3));

	printf("sumAry2D_f1~f3() %d\n", sumAry2D_f1(ary, 2, 3));

	printf("sumAry2D_f4~f5() %d\n", sumAry2D_f4(ary, 2, 3));

	freeAry2D(ary, 2);
	printf("2d array - free!!!\n");

	return 0;
}

int sumAry2D_f1(int ary[][3], int rows, int cols)
{
	int r, c, sum = 0;

	for (r = 0; r < rows; r++)
		for (c = 0; c < cols; c++)
			sum += ary[r][c];
	return sum;
}

int sumAry2D_f2(int (*ary)[3], int rows, int cols)
{
	int r, c, sum = 0;
	for (r = 0; r < rows; r++)
		for (c = 0; c < cols; c++)
			sum += ary[r][c];
	return sum;
}

int sumAry2D_f3(int ary[2][3], int rows, int cols)
{
	int r, c, sum = 0;
	for (r = 0; r < rows; r++)
		for (c = 0; c < cols; c++)
			sum += ary[r][c];
	return sum;
}

int sumAry2D_f4(int **ary, int rows, int cols)
{
	int r, c, sum = 0;
	for (r = 0; r < rows; r++)
		for (c = 0; c < cols; c++)
			sum += ary[r][c];
	return sum;
}

int sumAry2D_f5(int ***ary, int rows, int cols)
{
	int r, c, sum = 0;
	for (r = 0; r < rows; r++)
		for (c = 0; c < cols; c++)
			sum += (*ary)[r][c];
	return sum;
}

int freeAry2D(int** ary, int rows)
{
	int r;
	for (r = 0; r < rows; r++)
		free(ary[r]);
	free(ary);
	return 0;
}