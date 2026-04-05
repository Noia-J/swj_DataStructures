// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80

typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

precedence stack[MAX_STACK_SIZE];
int top = -1;
char expr[MAX_EXPR_SIZE];
FILE* fout;

void push(precedence item) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack is full.\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = item;
}

precedence pop() {
    if (top == -1) {
        return eos;
    }
    return stack[top--];
}

precedence getToken(char* symbol, int* n) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '*': return times;
    case '/': return divide;
    case '%': return mod;
    case '\0': return eos;
    default: return operand;
    }
}

void printToken(precedence token) {
    char symbol;
    switch (token) {
    case plus:  symbol = '+'; break;
    case minus: symbol = '-'; break;
    case times: symbol = '*'; break;
    case divide:symbol = '/'; break;
    case mod:   symbol = '%'; break;
    default: return;
    }
    printf("%c", symbol);
    fprintf(fout, "%c", symbol);
}

void postfix(void) {
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;

    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand) {
            printf("%c", symbol);
            fprintf(fout, "%c", symbol);
        }
        else if (token == rparen) {
            while (stack[top] != lparen)
                printToken(pop());
            pop();
        }
        else {
            while (isp[stack[top]] >= icp[token])
                printToken(pop());
            push(token);
        }
    }
    while ((token = pop()) != eos)
        printToken(token);
    printf("\n");
    fprintf(fout, "\n");
}

int main(void) {
    FILE* fin = NULL;

    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");

    if (fin == NULL || fout == NULL) {
        fprintf(stderr, "Cannot open files.\n");
        return 1;
    }

    fscanf(fin, "%s", expr);

    printf("<<<<<<<<<<<< infix to postfix >>>>>>>>>>>>\n");
    printf("infix expression     : %s\n", expr);
    printf("postfix expression   : ");

    postfix();

    fclose(fin);
    fclose(fout);

    return 0;
}