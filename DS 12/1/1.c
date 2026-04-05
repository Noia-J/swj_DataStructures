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

void inputPoly(char* filename, polyPointer* p);
polyPointer findLast(polyPointer first);
void insert(polyPointer* first, polyPointer pre, int coef, int expon);
void printList(polyPointer first);
polyPointer padd(polyPointer a, polyPointer b);
void attach(int coefficient, int exponent, polyPointer* ptr);
void erase(polyPointer* ptr);

int main(void) {
    char file_a[] = "a.txt";
    char file_b[] = "b.txt";

    inputPoly(file_a, &a);
    inputPoly(file_b, &b);

    printf("      a :");
    printList(a);
    printf("      b :");
    printList(b);

    c = padd(a, b);

    printf("  a+b=c :");
    printList(c);

    erase(&a);
    erase(&b);
    erase(&c);

    return 0;
}

void inputPoly(char* filename, polyPointer* p) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char format;
    int coef, expon;
    fscanf(fp, " %c", &format);

    while (fscanf(fp, "%d %d", &coef, &expon) == 2) {
        if (format == 'd') {
            polyPointer last = findLast(*p);
            insert(p, last, coef, expon);
        }
        else {
            insert(p, NULL, coef, expon);
        }
    }
    fclose(fp);
}

polyPointer findLast(polyPointer first) {
    if (first == NULL) return NULL;
    while (first->link != NULL) {
        first = first->link;
    }
    return first;
}

void insert(polyPointer* first, polyPointer pre, int coef, int expon) {
    polyPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->coef = coef;
    newNode->expon = expon;

    if (*first) {
        if (pre) {
            newNode->link = pre->link;
            pre->link = newNode;
        }
        else {
            newNode->link = *first;
            *first = newNode;
        }
    }
    else {
        newNode->link = NULL;
        *first = newNode;
    }
}

void printList(polyPointer first) {
    if (!first) {
        printf("\n");
        return;
    }
    for (; first; first = first->link) {
        printf(" %+d", first->coef);
        if (first->expon != 0) {
            printf("x^%d", first->expon);
        }
    }
    printf("\n");
}

polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer c, rear, temp;
    int sum;
    MALLOC(rear, sizeof(*rear));
    c = rear;

    while (a && b) {
        switch (COMPARE(a->expon, b->expon)) {
        case -1:
            attach(b->coef, b->expon, &rear);
            b = b->link;
            break;
        case 0:
            sum = a->coef + b->coef;
            if (sum) attach(sum, a->expon, &rear);
            a = a->link;
            b = b->link;
            break;
        case 1:
            attach(a->coef, a->expon, &rear);
            a = a->link;
            break;
        }
    }
    for (; a; a = a->link) attach(a->coef, a->expon, &rear);
    for (; b; b = b->link) attach(b->coef, a->expon, &rear);
    rear->link = NULL;

    temp = c;
    c = c->link;
    free(temp);
    return c;
}

void attach(int coefficient, int exponent, polyPointer* ptr) {
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

void erase(polyPointer* ptr) {
    polyPointer temp;
    while (*ptr) {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}