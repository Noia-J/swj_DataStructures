// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct polyNode* polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
} polyNode;

polyPointer a = NULL, b = NULL, c = NULL;
polyPointer lastA = NULL, lastB = NULL;
polyPointer avail = NULL;

polyPointer getNode(void);
void retNode(polyPointer node);
void erase(polyPointer* ptr);
void cerase(polyPointer* ptr);
void attach(int coefficient, int exponent, polyPointer* ptr);
void inputPolyCL(char* filename, polyPointer* p_header, polyPointer* p_last);
void printCList(polyPointer header);
polyPointer cpadd(polyPointer a, polyPointer b);

int main(void) {
    char file_a[] = "a.txt";
    char file_b[] = "b.txt";

    inputPolyCL(file_a, &a, &lastA);
    inputPolyCL(file_b, &b, &lastB);

    printf("      a :");
    printCList(a);
    printf("      b :");
    printCList(b);

    c = cpadd(a, b);

    printf("  a+b=c :");
    printCList(c);

    cerase(&a);
    cerase(&b);
    cerase(&c);

    erase(&avail);

    return 0;
}

polyPointer getNode(void) {
    polyPointer node;
    if (avail) {
        node = avail;
        avail = avail->link;
    }
    else {
        MALLOC(node, sizeof(*node));
    }
    return node;
}

void retNode(polyPointer node) {
    node->link = avail;
    avail = node;
}

void erase(polyPointer* ptr) {
    polyPointer temp;
    while (*ptr) {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}

void cerase(polyPointer* ptr) {
    polyPointer temp;
    if (*ptr) {
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
}

void attach(int coefficient, int exponent, polyPointer* ptr) {
    polyPointer temp = getNode();
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

void inputPolyCL(char* filename, polyPointer* p_header, polyPointer* p_last) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char format;
    int coef, expon;
    
    *p_header = getNode();
    (*p_header)->expon = -1;
    (*p_header)->link = *p_header;
    *p_last = *p_header;

    fscanf(fp, " %c", &format);

    while (fscanf(fp, "%d %d", &coef, &expon) == 2) {
        polyPointer newNode = getNode();
        newNode->coef = coef;
        newNode->expon = expon;

        if (format == 'd') {
            newNode->link = *p_header;
            (*p_last)->link = newNode;
            *p_last = newNode;
        }
        else {
            newNode->link = (*p_header)->link;
            (*p_header)->link = newNode;
            if (*p_last == *p_header) {
                *p_last = newNode;
            }
        }
    }
    fclose(fp);
}

void printCList(polyPointer header) {
    if (!header || header->link == header) {
        printf("\n");
        return;
    }
    polyPointer current = header->link;
    while (current != header) {
        printf(" %+d", current->coef);
        if (current->expon != 0) {
            printf("x^%d", current->expon);
        }
        current = current->link;
    }
    printf("\n");
}

polyPointer cpadd(polyPointer a, polyPointer b) {
    polyPointer startA, c, lastC;
    int sum;
    int done = 0;

    startA = a;
    a = a->link;
    b = b->link;

    c = getNode();
    c->expon = -1;
    lastC = c;

    do {
        switch (COMPARE(a->expon, b->expon)) {
        case -1:
            attach(b->coef, b->expon, &lastC);
            b = b->link;
            break;
        case 0:
            if (startA == a) {
                done = 1;
            }
            else {
                sum = a->coef + b->coef;
                if (sum) attach(sum, a->expon, &lastC);
                a = a->link;
                b = b->link;
            }
            break;
        case 1:
            attach(a->coef, a->expon, &lastC);
            a = a->link;
            break;
        }
        // 원형 리스트 종료 조건 수정: a나 b 둘 중 하나라도 헤더로 돌아오면 루프 조건 변경 필요
        // Program 4.15의 로직은 a가 한 바퀴 돌면 종료인데, b가 남아있을 수 있음
        // 좀 더 안전한 방법: a != startA && b->expon != -1 (b가 헤더가 아닐때) 동안만 루프
    } while (a != startA && b->expon != -1); // 수정된 종료 조건

    while (a != startA) {
        attach(a->coef, a->expon, &lastC);
        a = a->link;
    }

    while (b->expon != -1) {
        attach(b->coef, b->expon, &lastC);
        b = b->link;
    }


    lastC->link = c;
    return c;
}