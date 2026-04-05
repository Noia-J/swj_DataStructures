// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 20
#define MAX_COMMAND_SIZE 50
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

typedef struct {
    int id;
    char name[MAX_NAME_SIZE];
} element;

element* queue;
int capacity = 2;
int rear = 0;
int front = 0;

void copy(element* a, element* b, element* c)
{
    while (a != b)
        *c++ = *a++;
}

element queueEmpty() {
    fprintf(stderr, "queue is empty, cannot delete element.\n");
    element error_item;
    error_item.id = -1;
    strcpy(error_item.name, "");
    return error_item;
}

void queueFull()
{
    int start;
    element* newQueue;
    MALLOC(newQueue, 2 * capacity * sizeof(*queue));

    start = (front + 1) % capacity;

    if (start < 2)
    {
        copy(queue + start, queue + start + capacity - 1, newQueue);
    }
    else
    {
        copy(queue + start, queue + capacity, newQueue);
        copy(queue, queue + rear + 1, newQueue + capacity - start);
    }

    front = 2 * capacity - 1;
    rear = capacity - 1;
    capacity *= 2;
    free(queue);
    queue = newQueue;

    printf("queue capacity is doubled.\n");
    printf("current queue capacity is %d.\n", capacity);
}

void addq(element item)
{
    rear = (rear + 1) % capacity;
    if (front == rear)
        queueFull();
    queue[rear] = item;
}

element deleteq()
{
    if (front == rear)
        return queueEmpty();
    front = (front + 1) % capacity;
    return queue[front];
}

int main(void) {
    char command_line[MAX_COMMAND_SIZE];
    char* command;
    char* id_str;
    char* name_str;
    element new_item;
    element deleted_item;

    MALLOC(queue, capacity * sizeof(element));

    printf("<< circular queue operations where the initial capacity is 2>>\n");
    printf("add 1 Jung\ndelete\n\n");
    printf("*****************************************************\n");

    while (1) {
        fgets(command_line, sizeof(command_line), stdin);
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
            deleted_item = deleteq();
            if (deleted_item.id != -1) {
                printf("deleted item : %d %s\n", deleted_item.id, deleted_item.name);
            }
        }
        else if (strcmp(command, "quit") == 0) {
            break;
        }
        else {
            printf("wrong command! try again!\n");
        }
    }

    free(queue);
    return 0;
}