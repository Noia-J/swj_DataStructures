// 2019110610 정성원
// 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct {
    char name[20];
    int age;
    float salary;
} humanBeing;

int humansEqual(humanBeing* person1, humanBeing* person2);

int main(void) {
    humanBeing person1, person2;

    printf("Input person1's name, age, salary : \n");
    gets(person1.name);
    scanf("%d%*c %f%*c", &person1.age, &person1.salary);

    printf("\nInput person2's name, age, salary : \n");
    gets(person2.name);
    scanf("%d%*c %f%*c", &person2.age, &person2.salary);

    //    gets가 넘어가는 문제
    //    >>
    //    gets 앞에 scanf에서 개행 문제가 버퍼에 남아 생기는 문제
    //    scanf("%d",&a) 대신 scanf("%d%*c, &a) 사용
    //    뒤에 &*c를 추가

    if (humansEqual(&person1, &person2)) {
        printf("\n=>The two human beings are the same\n");
    }
    else {
        printf("\n=>The two human beings are not the same\n");
    }

    printf("계속하려면 아무 키나 누르십시오. . .");

    return 0;
}

int humansEqual(humanBeing* person1, humanBeing* person2) {
    if (strcmp(person1->name, person2->name) != 0) {
        return FALSE;
    }

    if (person1->age != person2->age) {
        return FALSE;
    }

    if (person1->salary != person2->salary) {
        return FALSE;
    }

    return TRUE;
}