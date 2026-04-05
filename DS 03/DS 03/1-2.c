//2019110610
//본인은 이 소스 파일을 다른 사람의 코드를 복사하지 않고 직접 작성하였습니다.

#include <stdio.h>

float sum(float list[], int n)
{
	float tempsum = 0;
	int i;
	for (i=0; i<n; i++)
		tempsum += list[i];
	return tempsum;
}

float rsum(float list[], int n)
{
	if (n)
		return rsum(list, n-1) + list[n - 1];
	return 0;
}

void main(void)
{
	float list[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("sum : 1에서 10까지의 합은 %f\n", sum(list, 10));
	printf("rsum: 1에서 10까지의 합은 %f\n", rsum(list, 10));
}

// 디버깅 시작 : F5
// 디버깅 중단 : Shift + F5
// 한 줄씩 실행 : F11
// 프로시저 단위 실행 : F10
// 함수내부에서 빠져 나오기 : Shift + F11
// 중단점 설정/해제 : F9
// 중단점에서 다음 중단점까지 실행 : F5