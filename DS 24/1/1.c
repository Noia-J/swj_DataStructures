// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 코드를 복사하지 않고 직접 작성하였습니다.

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

// 해시 함수 (Division Method)
int h(int k) {
    return k % TABLE_SIZE;
}

// 데이터 삽입 함수 (Linear Probing)
void insert(element* item) {
    int homeBucket, currentBucket;
    homeBucket = h(item->key);

    // 빈 버킷을 찾을 때까지 선형 조사
    for (currentBucket = homeBucket; ht[currentBucket] != NULL; ) {
        // 이미 같은 키가 존재하는지 확인 (문제 조건: 중복 처리)
        // 여기서는 단순히 빈 곳을 찾아 넣는 로직만 구현 
        currentBucket = (currentBucket + 1) % TABLE_SIZE;

        // 테이블이 꽉 찼는지 확인 (한 바퀴 돌아서 원래 위치로 돌아옴)
        if (currentBucket == homeBucket) {
            printf("Hash table is full!\n");
            return;
        }
    }

    // 빈 버킷에 데이터 저장
    ht[currentBucket] = item;
}

element* search(char* str) {
    int key = stringToInt(str);
    int homeBucket = h(key);
    int currentBucket;
    int comparisons = 0;

    for (currentBucket = homeBucket; ht[currentBucket] != NULL; ) {
        comparisons++;
        // 키가 같고 문자열 내용도 같은지 확인
        if (ht[currentBucket]->key == key && strcmp(ht[currentBucket]->item, str) == 0) {
            printf("item: %s, key: %d, the number of comparisions: %d\n",
                ht[currentBucket]->item, ht[currentBucket]->key, comparisons);
            return ht[currentBucket];
        }

        currentBucket = (currentBucket + 1) % TABLE_SIZE;

        // 한 바퀴 돌아서 원래 위치로 돌아오면 못 찾음
        if (currentBucket == homeBucket) {
            return NULL;
        }
    }

    // 빈 버킷을 만나면 탐색 실패
    return NULL;
}

int main() {
    FILE* fp;
    char buffer[MAX_CHAR];
    int i;

    // 1. 해시 테이블 초기화 (전역변수라 이미 NULL이지만 명시적으로)
    for (i = 0; i < TABLE_SIZE; i++) {
        ht[i] = NULL;
    }

    // 2. 파일 입력 및 해시 테이블 구성
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("input.txt 파일을 열 수 없습니다.\n");
        return 1;
    }

    printf("input strings : ");
    while (fscanf(fp, "%s", buffer) != EOF) {
        printf("%s ", buffer);

        // 동적 할당
        element* new_item = (element*)malloc(sizeof(element));
        strcpy(new_item->item, buffer);
        new_item->key = stringToInt(buffer);

        // 삽입
        insert(new_item);
    }
    printf("\n\n");
    fclose(fp);

    // 3. 해시 테이블 출력
    printf("        item       key\n");
    for (i = 0; i < TABLE_SIZE; i++) {
        printf("ht[%2d]:", i);
        if (ht[i] != NULL) {
            printf("%12s%10d", ht[i]->item, ht[i]->key);
        }
        printf("\n");
    }
    printf("\n");

    // 4. 검색 기능
    char search_str[MAX_CHAR];
    printf("string to search >> ");
    scanf("%s", search_str);

    element* result = search(search_str);
    if (result == NULL) {
        printf("it dosen't exist!\n");
    }

    return 0;
}