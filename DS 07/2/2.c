// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 20

typedef struct {
    int id;
    char name[MAX_NAME_SIZE];
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

void push(element item);
element pop();
void stackFull();

void stackFull() {
    fprintf(stderr, "stack is full, cannot add element\n");
    fprintf(stderr, "current stack elements :\n");
    for (int i = top; i >= 0; i--) {
        fprintf(stderr, "%d %s\n", stack[i].id, stack[i].name);
    }
    system("pause");
    exit(EXIT_FAILURE);
}

void push(element item) {
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

element pop() {
    if (top == -1) {
        fprintf(stderr, "stack is empty, cannot delete element.\n");
        system("pause");
        element errorElement = { -1, "" };
        return errorElement;
    }
    return stack[top--];
}

int main(void) {
    char input[80];
    char* op = NULL;
    element student;

    printf("<< stack operations where MAX_STACK_SIZE is 5>>\n");
    printf("push 1 Jung\n");
    printf("pop\n\n");
    printf("**********************************************\n");

    while (1) {
        gets(input);

        if (!input || !strcmp(input, "")) {
            continue;
        }

        op = strtok(input, " \n");

        if (!op) continue;

        if (!strcmp(op, "push")) {
            char* id_str = strtok(NULL, " ");
            char* name_str = strtok(NULL, " \n");
            if (id_str && name_str) {
                student.id = atoi(id_str);
                strcpy(student.name, name_str);
                push(student);
            }
            else {
                printf("wrong command! try again!\n");
            }
        }
        else if (!strcmp(op, "pop")) {
            pop();
        }
        else if (!strcmp(op, "quit")) {
            break;
        }
        else {
            printf("wrong command! try again!\n");
        }
    }
	system("pause");
    return 0;
}