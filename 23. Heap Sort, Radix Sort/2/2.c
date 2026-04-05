// 2019110610 정성원
// 본인은 이 소스파일을 다른 사라므이 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

int n; // 데이터 개수

// 특정 자릿수의 숫자를 반환하는 함수 (1의 자리, 10의 자리 등)
int digit(int key, int d, int r) {
    int i;
    for (i = 0; i < d; i++) {
        key /= r;
    }
    return key % r;
}

// 화면 출력 함수 (PDF 포맷 준수)
void printStatus(element a[], int link[], int first, const char* header, int passNum) {
    int i;

    if (passNum == -1)
        printf("************************* initial chain *********************\n");
    else
        printf("************************* pass %d ****************************\n", passNum);

    // 인덱스 출력
    printf("       ");
    for (i = 1; i <= n; i++) printf("[%d] ", i);
    printf("\n");

    // link 배열 출력
    printf("link:");
    for (i = 1; i <= n; i++) printf("%4d", link[i]);
    printf("\n");

    // a 배열(key) 출력
    printf("   a:");
    for (i = 1; i <= n; i++) printf("%4d", a[i].key);
    printf("\n");

    // first 출력
    printf("first: %4d\n\n", first);

    // result (링크 따라가며 출력)
    printf("result:");
    int current = first;
    while (current != 0) {
        printf("%4d", a[current].key);
        current = link[current];
    }
    printf("\n\n");
}

void printQueues(int front[], int rear[], int r) {
    int i;
    // 인덱스 출력 [0] ~ [9]
    printf("        ");
    for (i = 0; i < r; i++) printf("[%d] ", i);
    printf("\n");

    // rear 출력
    printf("rear: ");
    for (i = 0; i < r; i++) printf("%4d", rear[i]);
    printf("\n");

    // front 출력
    printf("front:");
    for (i = 0; i < r; i++) printf("%4d", front[i]);
    printf("\n\n");
}

int radixSort(element a[], int link[], int d, int r, int n) {
    int* front = (int*)malloc(sizeof(int) * r);
    int* rear = (int*)malloc(sizeof(int) * r);
    int i, bin, current, first, last;

    // 초기 링크 설정
    first = 1;
    for (i = 1; i < n; i++) link[i] = i + 1;
    link[n] = 0;

    // 초기 상태 출력
    printStatus(a, link, first, "initial chain", -1);

    // d번 반복 (1의 자리 -> 10의 자리 -> ...)
    for (i = 0; i < d; i++) {
        // 큐 초기화
        for (bin = 0; bin < r; bin++) front[bin] = rear[bin] = 0;

        // 현재 체인을 순회하며 큐에 분배
        for (current = first; current != 0; current = link[current]) {
            bin = digit(a[current].key, i, r);
            if (front[bin] == 0)
                front[bin] = current;
            else
                link[rear[bin]] = current;
            rear[bin] = current;
        }

        // 큐들을 연결하여 하나의 체인으로 만듦
        for (bin = 0; bin < r; bin++) {
            if (front[bin] != 0) break; // 첫 번째 비어있지 않은 큐 찾기
        }

        if (bin < r) {
            first = front[bin];
            last = rear[bin];

            for (bin++; bin < r; bin++) { // 나머지 큐 연결
                if (front[bin] != 0) {
                    link[last] = front[bin];
                    last = rear[bin];
                }
            }
            link[last] = 0; // 마지막 링크는 0
        }

        // 패스 결과 출력
        printStatus(a, link, first, "", i + 1);
        printQueues(front, rear, r);
    }

    free(front);
    free(rear);
    return first;
}

int main() {
    FILE* fp_in = fopen("input.txt", "r");
    FILE* fp_out = fopen("output.txt", "w");
    element a[MAX_SIZE];
    int link[MAX_SIZE];
    int d, r = 10; // r은 10으로 고정
    int i;

    if (fp_in == NULL) {
        printf("input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    // 첫째 줄: d, n 읽기
    fscanf(fp_in, "%d %d", &d, &n);

    // 둘째 줄: Key 리스트 읽기
    for (i = 1; i <= n; i++) {
        fscanf(fp_in, "%d", &a[i].key);
    }

    // 기수 정렬 실행
    int first = radixSort(a, link, d, r, n);

    // 파일 저장 (링크 순서대로)
    fprintf(fp_out, "%d\n", n);
    int current = first;
    while (current != 0) {
        fprintf(fp_out, "%d ", a[current].key);
        current = link[current];
    }

    fclose(fp_in);
    fclose(fp_out);

    return 0;
}