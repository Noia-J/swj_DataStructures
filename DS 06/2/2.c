// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct {
    float coef;
    int exp;
} term;

term terms[MAX_TERMS];
int avail = 0;

void inputPoly(char* fname, int* startA, int* finishA, int* startB, int* finishB);
void printPoly(int start, int finish);
void attach(float coefficient, int exponent);
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);

int main(void) {
    int startA, finishA, startB, finishB, startD, finishD;

    inputPoly("input.txt", &startA, &finishA, &startB, &finishB);

    printf("two input polynomials ...\n");
    printf("A(x) = ");
    printPoly(startA, finishA);
    printf("B(x) = ");
    printPoly(startB, finishB);

    padd(startA, finishA, startB, finishB, &startD, &finishD);

    printf("\nthe result of polynomial addition ...\n");
    printf("D(x) = A(x) + B(x) = \n");
    printPoly(startD, finishD);

    printf("계속하려면 아무 키나 누르십시오. . .");
    getchar();

    return 0;
}

void inputPoly(char* fname, int* startA, int* finishA, int* startB, int* finishB) {
    FILE* fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }

    int num_termsA, num_termsB;
    fscanf(fp, "%d %d", &num_termsA, &num_termsB);

    *startA = avail;
    for (int i = 0; i < num_termsA; i++) {
        fscanf(fp, "%f %d", &terms[avail].coef, &terms[avail].exp);
        avail++;
    }
    *finishA = avail - 1;

    *startB = avail;
    for (int i = 0; i < num_termsB; i++) {
        fscanf(fp, "%f %d", &terms[avail].coef, &terms[avail].exp);
        avail++;
    }
    *finishB = avail - 1;

    fclose(fp);
}

void printPoly(int start, int finish) {
    for (int i = start; i <= finish; i++) {
        if (terms[i].exp == 0) {
            printf("%.1f", terms[i].coef);
        }
        else {            
            printf("%.1fx^%d", terms[i].coef, terms[i].exp);
        }
        if (i < finish) {
            printf(" + ");
        }
    }
    printf("\n");
}

void attach(float coefficient, int exponent) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail].exp = exponent;
    avail++;
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
    float coefficient;
    *startD = avail;
    while (startA <= finishA && startB <= finishB) {
        switch (COMPARE(terms[startA].exp, terms[startB].exp)) {
        case -1:
            attach(terms[startB].coef, terms[startB].exp);
            startB++;
            break;
        case 0:
            coefficient = terms[startA].coef + terms[startB].coef;
            if (coefficient) {
                attach(coefficient, terms[startA].exp);
            }
            startA++;
            startB++;
            break;
        case 1:
            attach(terms[startA].coef, terms[startA].exp);
            startA++;
        }
    }

    for (; startA <= finishA; startA++) {
        attach(terms[startA].coef, terms[startA].exp);
    }
    for (; startB <= finishB; startB++) {
        attach(terms[startB].coef, terms[startB].exp);
    }
    *finishD = avail - 1;
}