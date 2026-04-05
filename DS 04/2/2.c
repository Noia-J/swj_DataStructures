// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "selectionSort.h"
#define MAX_SIZE 2001

void main(void)
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;

	clock_t start;
	FILE* fp;

	fp = fopen("out.txt", "w");
	if (fp == NULL)
	{
		fprintf(stderr, "File open error\n");
		return;
	}

	printf("     n   repetitions    time\n");
	fprintf(fp,"     n   repetitions    time\n");
	for (n = 0; n <= 2000; n += step)
	{
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;
			for (i = 0; i < n; i++)
				a[i] = n - i;
			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		printf("%6d   %9d    %f\n", n,repetitions,duration);
		fprintf(fp, "%6d   %9d    %f\n", n, repetitions, duration);
		if (n == 100) step = 100;
	}
	fclose(fp);
	return 0;
}