// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

void sort(int list[], int n);
int binsearch(int list[], int searchnum, int left, int right);

int main(void)
{
    unsigned int seed;
    int i, n;
    int list[MAX_SIZE];

    printf("input seed >> ");
    scanf_s("%u", &seed);
    srand(seed);

    printf("Enter the number of numbers to generate >> ");
    scanf_s("%d", &n);
    if (n < 1 || n > MAX_SIZE) {
        fprintf(stderr, "Improper value of n\n");
        exit(EXIT_FAILURE);
    }
    printf("Random numbers : \n");
    for (i = 0; i < n; i++) {
        list[i] = rand() % 1000; /* 0~999 사이의 난수 발생 */
        printf("%d ", list[i]);
    }
    sort(list, n);
    printf("\n\nsorted array : \n");
    for (i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n\n");

    int searchnum;
    printf("Enter the number to search >> ");
    scanf_s("%d", &searchnum);

    int result = binsearch(list, searchnum, 0, n - 1);
    if (result != -1)
        printf("The search number present in list[%d]\n", result);
    else
        printf("The search number is not present\n");
}

void sort(int list[], int n)
{
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
		SWAP(list[i], list[min], j);
    }
}

int binsearch(int list[], int searchnum, int left, int right)
{
    int middle;
    if (left <= right) {
        middle = (left + right) / 2;
        switch (COMPARE(list[middle], searchnum)) {
        case -1:
            return binsearch(list, searchnum, middle + 1, right);
        case 0:
            return middle;
        case 1:
            return binsearch(list, searchnum, left, middle - 1);
        }
    }
    return -1;
}