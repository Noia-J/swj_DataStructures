// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고, 직접 작성하였습니다.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

typedef struct listNode* listPointer;
typedef struct listNode {
    int data;
    listPointer link;
} listNode;

listPointer first = NULL;

void find(listPointer first, listPointer* x, int data);
void insert(listPointer* first, listPointer x, int data);
void delete(listPointer* first, listPointer trail, listPointer x);
void printList(listPointer first);

int main(void) {
    int data;
    listPointer x;
    FILE* fp;

    if ((fp = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "cannot open the file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%d", &data) != EOF) 
    {
        find(first, &x, data);
        insert(&first, x, data);
    }
    fclose(fp);

    printList(first);

    listPointer ptr = first;
    listPointer trail = NULL;
    while (ptr != NULL) {
        if (ptr->data <= 50) {
            listPointer to_delete = ptr;
            ptr = ptr->link;
            delete(&first, trail, to_delete);
        }
        else {
            trail = ptr;
            ptr = ptr->link;
        }
    }

    printf("\nAfter deleting nodes with data less than and equal to 50\n");
    printList(first);

    listPointer current = first;
    while (current != NULL) {
        listPointer next = current->link;
        free(current);
        current = next;
    }

    return 0;
}

// --- 함수 정의 ---
void find(listPointer first, listPointer* x, int data) {
    listPointer pre = NULL;
    listPointer trav = first;

    while (trav && trav->data < data) {
        pre = trav;
        trav = trav->link;
    }
    *x = pre;
}

void insert(listPointer* first, listPointer x, int data) {
    listPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->data = data;

    if (*first) {
        if (x) {
            temp->link = x->link;
            x->link = temp;
        }
        else {
            temp->link = *first;
            *first = temp;
        }
    }
    else {
        temp->link = NULL;
        *first = temp;
    }
}

void delete(listPointer* first, listPointer trail, listPointer x) {
    if (trail) {
        trail->link = x->link;
    }
    else {
        *first = (*first)->link;
    }
    free(x);
}

void printList(listPointer first) {
    printf("The ordered list contains:\n");
    int count = 0;
    for (; first; first = first->link) {
        printf(" %d ", first->data);
        count++;
        if (count % 10 == 0) {
            printf("\n");
        }
    }
    if (count % 10 != 0) {
        printf("\n");
    }
}