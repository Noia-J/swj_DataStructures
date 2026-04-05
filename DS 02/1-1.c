// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100

void swap(int* x, int* y);
void sort(int list[], int n);
int compare(int x, int y);
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
        swap(&list[i], &list[min]);
    }
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int compare(int x, int y)
{
    if (x < y) return -1;
    else if (x == y) return 0;
    else return 1;
}

int binsearch(int list[], int searchnum, int left, int right)
{
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        switch (compare(list[middle], searchnum)) {
        case -1:
            left = middle + 1;
            break;
        case 0:
            return middle;
        case 1:
            right = middle - 1;
        }
    }
    return -1;
}