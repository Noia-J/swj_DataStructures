//#include <stdio.h>
//
//// Step Count를 저장할 전역 변수
//int count = 0;
//
//// 행렬 덧셈 및 Step Count 계산 함수 (Program 1.18 기반)
//void add(int a[][4], int b[][4], int c[][4], int rows, int cols) {
//    int i, j;
//
//    for (i = 0; i < rows; i++) {
//        // 안쪽 루프를 시작하기 전, 바깥쪽 루프의 연산 2회를 카운트
//        count += 2;
//        for (j = 0; j < cols; j++) {
//            // 실제 덧셈 연산
//            c[i][j] = a[i][j] + b[i][j];
//            // 안쪽 루프의 연산(덧셈+할당) 2회를 카운트
//            count += 2;
//        }
//    }
//    // 바깥쪽 for 루프가 최종적으로 종료될 때 1회 카운트
//    count++;
//}
//
//int main(void) {
//    // 1. main의 지역변수로 3행 4열의 2차원 배열 3개 선언
//    int a[3][4], b[3][4], c[3][4];
//    int i, j;
//
//    // 2. 파일 열기 및 파일 입력 함수 사용
//    FILE* fpA, * fpB;
//
//    // a.txt 파일 읽기
//    fpA = fopen("a.txt", "r");
//
//    for (i = 0; i < 3; i++) {
//        for (j = 0; j < 4; j++) {
//            fscanf(fpA, "%d", &a[i][j]);
//        }
//    }
//    fclose(fpA);
//
//    // b.txt 파일 읽기
//    fpB = fopen("b.txt", "r");
//
//    for (i = 0; i < 3; i++) {
//        for (j = 0; j < 4; j++) {
//            fscanf(fpB, "%d", &b[i][j]);
//        }
//    }
//    fclose(fpB);
//
//    // 3. add 함수를 호출하여 Step Count 계산
//    add(a, b, c, 3, 4);
//
//    // 실행 결과와 같이 출력
//    printf("step count : %d\n", count);
//
//    return 0;
//}