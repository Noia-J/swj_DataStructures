// Visual Studio에서 strcpy, gets와 같은 오래된 C 표준 함수를 사용할 때 발생하는
// 보안 경고를 비활성화하는 전처리기 지시문입니다.
#define _CRT_SECURE_NO_WARNINGS

// 표준 입출력 함수(printf, gets, sscanf 등)를 사용하기 위한 헤더 파일입니다.
#include <stdio.h>
// 메모리 할당, 프로그램 종료(exit) 등과 같은 표준 라이브러리 함수를 사용하기 위한 헤더 파일입니다.
#include <stdlib.h>
// 문자열 처리 함수(strcpy, strcmp, strtok 등)를 사용하기 위한 헤더 파일입니다.
#include <string.h>


// --- 전처리기 매크로 및 전역 변수 선언 ---

// 큐가 가질 수 있는 최대 크기를 5로 정의합니다. 코드 전체에서 MAX_QUEUE_SIZE는 5로 대체됩니다.
#define MAX_QUEUE_SIZE 5
// 이름 문자열이 가질 수 있는 최대 길이를 20으로 정의합니다.
#define MAX_NAME_SIZE 20
// 사용자로부터 입력받을 명령어 문자열의 최대 길이를 50으로 정의합니다.
#define MAX_COMMAND_SIZE 50

// 큐에 저장될 데이터(요소)의 구조를 정의합니다.
typedef struct {
    int id;                     // ID를 저장할 정수형 변수
    char name[MAX_NAME_SIZE];   // 이름을 저장할 문자형 배열
} element; // 이제부터 이 구조체를 'element'라는 이름으로 사용할 수 있습니다.

// 'element' 타입의 데이터를 저장할 수 있는, 크기가 MAX_QUEUE_SIZE인 배열을 선언합니다.
// 이 배열이 바로 우리의 큐(Queue) 본체입니다.
element queue[MAX_QUEUE_SIZE];

// 큐의 가장 마지막 요소를 가리키는 인덱스 변수입니다.
// -1은 큐가 비어있다는 의미입니다.
int rear = -1;

// 큐의 가장 첫 번째 요소의 '바로 앞'을 가리키는 인덱스 변수입니다.
// -1은 큐가 비어있다는 의미입니다.
int front = -1;


// --- 함수 정의 ---

/**
 * @brief 큐가 비어있을 때 호출되는 함수입니다.
 * @return 에러를 의미하는 특별한 ID(-1)를 가진 element를 반환합니다.
 */
element queueEmpty() {
    // stderr는 '표준 에러 출력'을 의미합니다. 일반 출력(stdout)과 구분되어 에러 메시지를 출력할 때 주로 사용됩니다.
    fprintf(stderr, "Queue is empty, cannot delete element.\n");
    element error_item;
    error_item.id = -1; // id가 -1인 element는 에러 상황을 나타내는 약속입니다.
    return error_item;
}

/**
 * @brief 현재 큐에 들어있는 모든 유효한 요소들을 출력하는 함수입니다.
 */
void printQueue() {
    printf("current queue elements :\n");
    // 큐의 유효한 데이터는 front의 '다음' 인덱스부터 rear 인덱스까지 존재합니다.
    // 그래서 루프는 front + 1 부터 시작합니다.
    for (int i = front + 1; i <= rear; i++) {
        printf("%d %s\n", queue[i].id, queue[i].name);
    }
}

/**
 * @brief 큐의 맨 앞에서 요소를 하나 꺼내는(삭제하는) 함수입니다. (Dequeue)
 */
element deleteq() {
    // front와 rear가 같다는 것은 큐가 비어있다는 의미입니다.
    if (front == rear)
        return queueEmpty(); // 큐가 비었으므로, 에러 처리를 하는 queueEmpty 함수를 호출합니다.
    
    // ++front: front 값을 1 증가시킨 '후에' 그 값을 사용합니다.
    // 즉, front가 가리키는 위치를 한 칸 뒤로 옮겨서(맨 앞 요소를 가리키게 됨) 그 위치의 요소를 반환합니다.
    // 이 작업으로 인해 해당 요소는 논리적으로 큐에서 제거됩니다.
    return queue[++front];
}

/**
 * @brief 큐가 가득 찼을 때 호출되는 함수입니다.
 * 앞쪽에 빈 공간이 있는지 여부에 따라 다르게 동작합니다.
 */
void queueFull() {
    // front가 -1이라는 것은, 요소를 추가만 하고 한 번도 삭제하지 않은 상태를 의미합니다.
    // 이 상태에서 rear가 배열 끝에 도달했다면, 이것이 '진짜로 꽉 찬' 상태입니다.
    if (front == -1) {
        printf("Queue is full, cannot add element!\n");
        deleteq();       // 요구 조건에 따라 deleteq를 호출합니다.
        printQueue();    // 현재 큐의 내용을 출력합니다.
        exit(EXIT_FAILURE); // 프로그램을 에러 상태(FAILURE)로 즉시 종료합니다.
    } 
    // front가 -1이 아니라면, rear는 배열 끝이지만 front가 앞으로 이동해 생긴 빈 공간이 있다는 의미입니다.
    else {
        // 배열을 앞으로 당겨 빈 공간을 없앨 것임을 알리는 메시지를 출력합니다.
        printf("array shifting...\n");
        int j = 0; // 데이터를 배열의 0번 인덱스부터 새로 채워넣기 위한 변수입니다.
        // 유효한 데이터가 있는 front+1 부터 rear까지 반복합니다.
        for (int i = front + 1; i <= rear; i++) {
            queue[j] = queue[i]; // 유효한 데이터를 배열의 앞으로 복사합니다.
            j++;
        }
        // 인덱스를 재조정합니다.
        rear = rear - (front + 1); // rear의 새 위치는 (기존 요소 개수 - 1)이 됩니다.
        front = -1;                // 모든 요소를 앞으로 당겼으므로, 앞쪽 빈 공간은 없어져 front는 -1로 초기화됩니다.
    }
}

/**
 * @brief 큐의 맨 뒤에 새로운 요소를 추가하는 함수입니다. (Enqueue)
 */
void addq(element item) {
    // rear가 배열의 마지막 인덱스(MAX_QUEUE_SIZE - 1)와 같다면, 배열이 물리적으로 꽉 찬 것입니다.
    if (rear == MAX_QUEUE_SIZE - 1) {
        // 배열이 꽉 찼을 때의 모든 복잡한 처리는 queueFull 함수에 맡깁니다.
        queueFull();
    }
    // queueFull 함수가 shifting을 통해 공간을 만들었거나, 원래 공간이 있었던 경우
    // ++rear: rear 값을 1 증가시킨 '후에' 그 값을 사용합니다.
    // 즉, rear를 한 칸 뒤로 옮기고 그 위치에 새로운 item을 저장합니다.
    queue[++rear] = item;
}

/**
 * @brief 프로그램의 시작점인 main 함수입니다.
 */
int main(void) {
    char command_line[MAX_COMMAND_SIZE]; // 사용자 입력을 통째로 저장할 문자열 배열
    char* command;                       // 'add', 'delete' 같은 명령어를 가리킬 포인터
    char* id_str;                        // ID 부분 문자열을 가리킬 포인터
    char* name_str;                      // 이름 부분 문자열을 가리킬 포인터
    element new_item;                    // 큐에 추가할 새로운 element 변수

    // 문제의 실행 결과에 맞추기 위한 초기 출력 부분입니다.
    printf("<< linear queue operations where MAX_QUEUE_SIZE is 5>>\nadd 1 Jung\ndelete\n\n");
    printf("***************************************************\n");

    // while(1)은 무한 루프를 의미합니다. 'quit' 명령이 들어올 때까지 계속 반복됩니다.
    while (1) {
        // gets는 정해진 크기를 넘어 입력을 받을 수 있어 보안에 취약합니다. (대안: fgets)
        // 여기서는 문제의 요구사항을 따르기 위해 사용되었습니다.
        gets(command_line, MAX_COMMAND_SIZE, stdin);

        // gets로 입력받은 문자열 끝에 포함된 줄바꿈(\n) 문자를 찾아 널 문자(\0)로 바꿔서 제거합니다.
        command_line[strcspn(command_line, "\n")] = 0;

        // strtok: 문자열을 특정 구분자(여기서는 " ")를 기준으로 자릅니다.
        // 처음 호출할 때는 원본 문자열을, 그 다음부터는 NULL을 넣어주면 이어서 잘라줍니다.
        command = strtok(command_line, " ");
        if (command == NULL) continue; // 아무것도 입력하지 않았다면 다음 루프로 넘어갑니다.

        // strcmp: 두 문자열을 비교하여 같으면 0을 반환합니다.
        if (strcmp(command, "add") == 0) {
            id_str = strtok(NULL, " ");
            name_str = strtok(NULL, " ");

            if (id_str != NULL && name_str != NULL) {
                // sscanf: 문자열(id_str)에서 특정 형식(여기서는 정수, %d)의 데이터를 읽어 변수(new_item.id)에 저장합니다.
                sscanf(id_str, "%d", &new_item.id);
                // strcpy: 이름 문자열(name_str)을 new_item.name으로 복사합니다.
                strcpy(new_item.name, name_str);
                addq(new_item);
            } else {
                printf("wrong command! try again!\n");
            }
        } else if (strcmp(command, "delete") == 0) {
            deleteq();
        } else if (strcmp(command, "quit") == 0) {
            // 'quit' 명령을 받으면 break를 통해 무한 루프를 탈출합니다.
            break;
        } else {
            // 'add', 'delete', 'quit' 이외의 명령이 들어오면 에러 메시지를 출력합니다.
            printf("wrong command! try again!\n");
        }
    }
    return 0; // 프로그램을 정상적으로 종료합니다.
}