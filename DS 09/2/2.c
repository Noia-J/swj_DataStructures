// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 12         // 10x10 미로 + 테두리(2)
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

// 전역 변수 선언
int maze[MAX_SIZE][MAX_SIZE];
int mark[MAX_SIZE][MAX_SIZE] = { 0 }; // 방문 기록 배열은 0으로 초기화

int EXIT_ROW, EXIT_COL; // 출구 좌표

// 8방향 이동을 위한 오프셋 구조체
typedef struct {
    short int vert;
    short int horiz;
} offsets;

offsets move[8] = {
    {-1, 0},   // N (북)
    {-1, 1},   // NE (북동)
    {0, 1},    // E (동)
    {1, 1},    // SE (남동)
    {1, 0},    // S (남)
    {1, -1},   // SW (남서)
    {0, -1},   // W (서)
    {-1, -1}   // NW (북서)
};

// 경로 탐색을 위한 스택의 요소
typedef struct {
    short int row;
    short int col;
    short int dir;
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

// 스택 함수
void push(element item) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack is full, cannot add element.\n");
        return;
    }
    stack[++top] = item;
}

element pop() {
    if (top == -1) {
        fprintf(stderr, "Stack is empty, cannot delete element.\n");
        element error_item = { -1, -1, -1 }; // 에러 시 반환할 값
        return error_item;
    }
    return stack[top--];
}

// 미로 탐색 함수 (제공된 코드)
void path(void)
{
    int i, row, col, nextRow, nextCol, dir, found = FALSE;
    element position;
    mark[1][1] = 1; top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 0; // 시작 방향은 0(N)부터

    while (top > -1 && !found) {
        position = pop();
        row = position.row; col = position.col;
        dir = position.dir;
        while (dir < 8 && !found) {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
                found = TRUE;
            else if (!maze[nextRow][nextCol] &&
                !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                position.row = row; position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow; col = nextCol; dir = 0;
            }
            else ++dir;
        }
    }
    if (found) {
        printf("The path is:\n");
        printf("row col\n");
        // 스택에 저장된 경로 출력 (실행 예시와 같이 개행 추가)
        for (i = 0; i <= top; i++)
            printf("%2d%5d\n", stack[i].row, stack[i].col);
        // 경로의 마지막 두 지점 출력
        printf("%2d%5d\n", row, col);
        printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
    }
    else printf("The maze does not have a path\n");
}


int main(void) {
    FILE* fp = NULL;
    int rows, cols;
    int i, j;

    // input.txt 파일 열기
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file input.txt\n");
        return 1;
    }

    // 미로 크기 읽기
    fscanf(fp, "%d %d", &rows, &cols);
    EXIT_ROW = rows;
    EXIT_COL = cols;

    // 미로 데이터 읽고 테두리 설정
    for (i = 0; i < rows + 2; i++) {
        for (j = 0; j < cols + 2; j++) {
            if (i == 0 || i == rows + 1 || j == 0 || j == cols + 1) {
                // 테두리를 벽(1)으로 설정
                maze[i][j] = 1;
            }
            else {
                // 파일에서 미로 내부 데이터 읽기
                fscanf(fp, "%d", &maze[i][j]);
            }
        }
    }

    fclose(fp); // 파일 닫기

    // 경로 탐색 함수 호출
    path();

    return 0;
}