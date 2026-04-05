#include "selectionSort.h" //사용자가 정의한 헤더 파일을 포함할 때는 큰따옴표 사용

void sort(int list[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        SWAP(list[i], list[min], temp);
    }
}