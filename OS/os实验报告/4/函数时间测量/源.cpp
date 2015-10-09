
#include <iostream>
#include <windows.h>
#include <time.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
int main(int argc, char* argv[])
{
	double time1, time2, time3, time4;
	clock_t begin1, end1;
	DWORD begin2, end2, begin3, end3, dff;
	long long begin4, end4;
	//���ּ�ʱ����
	begin1 = clock();
	begin2 = timeGetTime();
	begin3 = GetTickCount();
	LARGE_INTEGER longint;
	//�߾��� ��ʱ�� ΢��
	QueryPerformanceFrequency(&longint);
	dff = longint.QuadPart;
	QueryPerformanceCounter(&longint);
	begin4 = longint.QuadPart;
	//����ʱ��
	for (int j = 1; j <= 5; j++){
		for (int i = 1; i <= 100000000; i++)
			i = i;
	}
	//��ֹʱ��
	end1 = clock();
	end2 = timeGetTime();
	end3 = GetTickCount();
	QueryPerformanceCounter(&longint);
	end4 = longint.QuadPart;
	time1 = (double)(end1 - begin1);
	time2 = (double)(end2 - begin2);
	time3 = (double)(end3 - begin3);
	time4 = (end4 - begin4) * 1000 / dff;
	//���ʱ���
	printf("clock() = %.6fms\n", time1);
	printf("timeGetTime() = %.6fms\n", time2);
	printf("GetTickCount() = %.6fms\n", time3);
	printf("QueryPerformanceCounter() = %.6fms\n", time4);
	return 0;
}

