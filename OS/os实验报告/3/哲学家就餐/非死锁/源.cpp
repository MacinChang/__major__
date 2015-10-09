#include <windows.h>
#include <process.h>
#include <time.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
using namespace std;                     

const unsigned int NUM = 5;    
const char THINKING = 1;                  
const char HUNGERY = 2;
const char EAT = 3;

HANDLE hPhilosopher[5];                  

//���ӵ�״̬���Ƿ����
HANDLE semaphore[NUM];       
//��ֹ����
HANDLE mutex;                            

DWORD WINAPI philosopherProc(LPVOID lpParameter){
	int  myid;
	char idStr[128];
	char stateStr[128];
	char mystate;
	int  ret;

	unsigned int leftFork;                  //�����
	unsigned int rightFork;                 //�ҿ���

	myid = int(lpParameter);
	itoa(myid, idStr, 10);


	WaitForSingleObject(mutex, INFINITE);
	cout << "��ѧ�� " << myid << " �����˲���" << endl;
	ReleaseMutex(mutex);

	//��ʼ��
	mystate = THINKING;                                    
	leftFork = (myid) % NUM;
	rightFork = (myid + 1) % NUM;

	while (true)
	{
		switch (mystate)
		{
			//ÿ����ѧ�ҿ����Լ���״̬ 
		case THINKING:
			mystate = HUNGERY;                                      
			strcpy(stateStr, "����");
			break;

		case HUNGERY:
			strcpy(stateStr, "����");
			//������Ƿ����
			ret = WaitForSingleObject(semaphore[leftFork], 0);   
			if (ret == WAIT_OBJECT_0)
			{
				//�ҿ����Ƿ����
				ret = WaitForSingleObject(semaphore[rightFork], 0);  
				if (ret == WAIT_OBJECT_0)
				{
					//����
					mystate = EAT;                                   
					strcpy(stateStr, "�Է�");
				}
				else
				{

					ReleaseSemaphore(semaphore[leftFork], 1, NULL);    
				}
			}
			break;

		case EAT:
			//���¿���
			ReleaseSemaphore(semaphore[leftFork], 1, NULL);
			ReleaseSemaphore(semaphore[rightFork], 1, NULL);

			mystate = THINKING;          
			//�����Լ���״̬
			strcpy(stateStr, "˼��");
			break;
		}

		// ���״̬
		WaitForSingleObject(mutex, INFINITE);
		cout << "��ѧ�� " << myid << " ����" << stateStr << endl;
		//�ͷŻ�����
		ReleaseMutex(mutex);
		// sleep a random time : between 1 - 5 s
		int sleepTime;
		sleepTime = 1 + (int)(5.0*rand() / (RAND_MAX + 1.0));
		Sleep(sleepTime * 10);
	}
}


int main()
{
	int i;
	freopen("out.txt", "w", stdout);
	srand(time(0));
	mutex = CreateMutex(NULL, false, NULL);
	for (i = 0; i < NUM; i++)
	{
		//���ȴ��������߳�
		semaphore[i] = CreateSemaphore(NULL, 1, 1, NULL);
		hPhilosopher[i] = CreateThread(NULL, 0, philosopherProc, LPVOID(i), CREATE_SUSPENDED, 0);
	}
	for (i = 0; i < NUM; i++)
		ResumeThread(hPhilosopher[i]);
	Sleep(2000);
	return 0;
}
