// 2019110610 정성원
// 본인은 이 소스 파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

//  infix to postfix
// precedence에 or, and, not 추가
typedef enum { lparen, rparen, or , and, not, eos, operand } precedence;
int isp[] = { 0, 19, 12, 13, 15, 0 };
int icp[] = { 20, 19, 12, 13, 15, 0 };
void postfix(void);
precedence getToken(char* symbol, int* n);
void printToken(precedence);

// stack 
precedence stack[MAX_STACK_SIZE];
int top = -1;
void push(precedence item);
void stackFull();
precedence pop();
precedence stackEmpty();

// input
char expr[81];
FILE* fpI, * fpP;	// input(infix), output(postfix)

int main(void)
{
	if (!(fpI = fopen("infix.txt", "r")) || !(fpP = fopen("postfix.txt", "w")))
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	fgets(expr, 80, fpI);
	expr[strcspn(expr, "\n")] = 0;

	printf("<<<<<<<<<< infix to postfix >>>>>>>>>>>>>\n");
	printf("infix expression\t: %s\n", expr);
	printf("postfix expression\t: ");

	postfix();	// infix to postfix

	fclose(fpI);
	fclose(fpP);

	return 0;
}

void postfix(void)
{
	char symbol;
	precedence token;
	int n = 0;
	top = -1;
	stack[++top] = eos;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
		{
			printf("%c", symbol);
			fprintf(fpP, "%c", symbol);
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
	fprintf(fpP, "\n"); 
}

// Program 3.14
precedence getToken(char* symbol, int* n)
{
	// 버퍼 오버런 방지
	if (*n >= 80 || *n >= strlen(expr)) {
		*symbol = '\0';
		return eos;
	}

	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
		// 수정 ~
	case '|': return or ;
	case '&': return and;
	case '~': return not;
	case ' ': return getToken(symbol, n);
		// ~ 끝
	case '\0': return eos;
	default: return operand;

	}
}

void printToken(precedence pre)
{
	// 수정 ~
	switch (pre)
	{
	case or :	printf("%c", '|');	fprintf(fpP, "%c", '|');	break;
	case and :	printf("%c", '&');	fprintf(fpP, "%c", '&');	break;
	case not:	printf("%c", '~');	fprintf(fpP, "%c", '~');	break;
	default:;
	}
	// ~ 끝
}

precedence pop()
{
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}

precedence stackEmpty()
{
	precedence item;
	item = operand;
	return item;
}

void push(precedence item)
{
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}

void stackFull()
{
	fprintf(stderr, "stack is full, cannot add item\n");
	exit(EXIT_FAILURE);
}