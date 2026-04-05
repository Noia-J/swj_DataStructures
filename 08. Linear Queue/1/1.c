// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5
#define MAX_NAME_SIZE 20
#define MAX_COMMAND_SIZE 50

typedef struct {
    int id;
    char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void printQueue() {
    printf("current queue elements :\n");
    for (int i = front + 1; i <= rear; i++) {
        printf("%d %s\n", queue[i].id, queue[i].name);
    }
}

element queueEmpty() {
    fprintf(stderr, "Queue is empty, cannot delete element.\n");
    element error_item;
    error_item.id = -1;
    return error_item;
}

element deleteq() {
    if (front == rear)
        return queueEmpty();
    return queue[++front];
}

void queueFull() {
    if (front == -1) {
        printf("Queue is full, cannot add element!\n");
        deleteq();
        printQueue();
        exit(EXIT_FAILURE);
    }
    else {
        printf("array shifting...\n");
        int j = 0;
        for (int i = front + 1; i <= rear; i++) {
            queue[j] = queue[i];
            j++;
        }
        rear = rear - (front + 1);
        front = -1;
    }
}

void addq(element item) {
    if (rear == MAX_QUEUE_SIZE - 1) {
        queueFull();
    }
    queue[++rear] = item;
}

int main(void) {
    char command_line[MAX_COMMAND_SIZE];
    char* command;
    char* id_str;
    char* name_str;
    element new_item;

    printf("<< linear queue operations where MAX_QUEUE_SIZE is 5>>\nadd 1 Jung\ndelete\n\n");
    printf("***************************************************\n");

    while (1) {
        gets(command_line, MAX_COMMAND_SIZE, stdin);
        command_line[strcspn(command_line, "\n")] = 0;

        command = strtok(command_line, " ");
        if (command == NULL) continue;

        if (strcmp(command, "add") == 0) {
            id_str = strtok(NULL, " ");
            name_str = strtok(NULL, " ");

            if (id_str != NULL && name_str != NULL) {
                sscanf(id_str, "%d", &new_item.id);
                strcpy(new_item.name, name_str);
                addq(new_item);
            }
            else {
                printf("wrong command! try again!\n");
            }
        }
        else if (strcmp(command, "delete") == 0) {
            deleteq();
        }
        else if (strcmp(command, "quit") == 0) {
			printf("\n\n\n\n\n");
            break;
        }
        else {
            printf("wrong command! try again!\n");
        }
    }
    return 0;
}