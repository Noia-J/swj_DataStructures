// 2019110610 (학번/이름)
// 본 코드는 다른 사람의 코드를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 10
#define TABLE_SIZE 11

typedef struct {
    char item[MAX_CHAR];
    int key;
} element;

element* ht[TABLE_SIZE];

unsigned int stringToInt(char* key) {
    int number = 0;
    while (*key) {
        number += *key++;
    }
    return number;
}

// 해시 함수 (제산 함수, Division Method)
int h(int k) {
    return k % TABLE_SIZE;
}

// 해시 테이블 삽입 함수 (선형 조사법, Linear Probing)
void insert(element* item) {
    int homeBucket, currentBucket;
    homeBucket = h(item->key);

    // 빈 버킷을 찾을 때까지 반복해서 이동
    for (currentBucket = homeBucket; ht[currentBucket] != NULL; ) {
        // 충돌 발생 시 다음 버킷으로 이동 (테이블 크기만큼 모듈러 연산)
        currentBucket = (currentBucket + 1) % TABLE_SIZE;

        // 테이블을 한 바퀴 돌아 제자리로 돌아온 경우 (테이블 포화 상태)
        if (currentBucket == homeBucket) {
            printf("Hash table is full!\n");
            return;
        }
    }

    // 빈 버킷에 아이템 삽입
    ht[currentBucket] = item;
}

// 해시 테이블 검색 함수
element* search(char* str) {
    int key = stringToInt(str);
    int homeBucket = h(key);
    int currentBucket;
    int comparisons = 0;

    // 빈 버킷을 만나기 전까지 반복
    for (currentBucket = homeBucket; ht[currentBucket] != NULL; ) {
        comparisons++;

        // 키 값이 일치하고 문자열도 동일한지 확인 (탐색 성공)
        if (ht[currentBucket]->key == key && strcmp(ht[currentBucket]->item, str) == 0) {
            printf("item: %s, key: %d, the number of comparisions: %d\n",
                ht[currentBucket]->item, ht[currentBucket]->key, comparisons);
            return ht[currentBucket];
        }

        // 일치하지 않으면 다음 버킷을 탐색
        currentBucket = (currentBucket + 1) % TABLE_SIZE;

        // 테이블을 한 바퀴 다 돌았는데도 찾지 못한 경우 (탐색 실패)
        if (currentBucket == homeBucket) {
            return NULL;
        }
    }

    // 해당하는 값을 찾지 못하고 빈 버킷을 만난 경우
    return NULL;
}

int main() {
    FILE* fp;
    char buffer[MAX_CHAR];
    int i;

    // 1. 해시 테이블 초기화 (NULL 포인터로 초기화)
    for (i = 0; i < TABLE_SIZE; i++) {
        ht[i] = NULL;
    }

    // 2. 파일에서 데이터를 읽어와 해시 테이블에 삽입
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    printf("input strings : ");
    while (fscanf(fp, "%s", buffer) != EOF) {
        printf("%s ", buffer);

        // 새 아이템을 위한 동적 메모리 할당
        element* new_item = (element*)malloc(sizeof(element));
        strcpy(new_item->item, buffer);
        new_item->key = stringToInt(buffer);

        // 해시 테이블에 삽입
        insert(new_item);
    }
    printf("\n\n");
    fclose(fp);

    // 3. 해시 테이블 저장 상태 출력
    printf("        item       key\n");
    for (i = 0; i < TABLE_SIZE; i++) {
        printf("ht[%2d]:", i);
        if (ht[i] != NULL) {
            printf("%12s%10d", ht[i]->item, ht[i]->key);
        }
        printf("\n");
    }
    printf("\n");

    // 4. 검색할 문자열 입력 및 탐색 수행
    char search_str[MAX_CHAR];
    printf("string to search >> ");
    scanf("%s", search_str);

    element* result = search(search_str);
    if (result == NULL) {
        printf("it dosen't exist!\n");
    }

    return 0;
}