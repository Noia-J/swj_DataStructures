// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 80

typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

int stack[MAX_STACK_SIZE];
int top = -1;
char expr[MAX_EXPR_SIZE];

void push(int item) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack is full.\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = item;
}

int pop() {
    if (top == -1) {
        fprintf(stderr, "Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

precedence getToken(char* symbol, int* n) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    case '%': return mod;
    case '\0': return eos;
    default: return operand;
    }
}

int eval() {
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    top = -1;

    token = getToken(&symbol, &n);
    while (token != eos) {
        if (token == operand) {
            push(symbol - '0');
        }
        else {
            op2 = pop();
            op1 = pop();
            switch (token) {
            case plus:  push(op1 + op2); break;
            case minus: push(op1 - op2); break;
            case times: push(op1 * op2); break;
            case divide:push(op1 / op2); break;
            case mod:   push(op1 % op2); break;
            default: break;
            }
        }
        token = getToken(&symbol, &n);
    }
    return pop();
}

int main(void) {
    FILE* fp = NULL;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open the file: input.txt\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%s", expr);
    fclose(fp);

    printf("postfix expression : %s\n", expr);
    printf("the evaluation value : %d\n", eval());

    return 0;
}