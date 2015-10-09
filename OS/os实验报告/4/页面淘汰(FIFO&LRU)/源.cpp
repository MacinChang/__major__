#include <cstdio>
#include <iostream>
#include <time.h>
using namespace std;
#define TOTAL_INSTRUCTION 320
#define TOTAL_VP 32
#define INVALID -1
#define INF 9999999
typedef struct{
	int pn;
	int pfn;
	int counter;
	int time;
} pl_type;
pl_type pl[TOTAL_VP];

struct pfc_struct{
	int pn, pfn;
	struct pfc_struct *next;
};
typedef struct pfc_struct pfc_type;
pfc_type pfc[TOTAL_VP], *freepf_head, *busypf_head, *busypf_tail;
int a[TOTAL_INSTRUCTION], page[TOTAL_INSTRUCTION], offset[TOTAL_INSTRUCTION];
int total_pf;//��ҳ����
int disaffect;//ʧЧҳ����

void init(int total_pf){
	int i;
	disaffect = 0;
	for (i = 0; i < TOTAL_VP; i++)
	{
		pl[i].pn = i;
		pl[i].pfn = INVALID;
		pl[i].counter = 0;
		pl[i].time = -1;
	}
	for (i = 0; i < total_pf - 1; i++)
	{
		pfc[i].next = &pfc[i + 1];
		pfc[i].pfn = i;
	}
	pfc[total_pf - 1].next = NULL;
	pfc[total_pf - 1].pfn = total_pf - 1;
	freepf_head = &pfc[0];
}

void FIFO(int total_pf){
	int i;
	pfc_type *p;
	init(total_pf);
	//disaffect��ʾȱҳ��Ŀ
	disaffect = 0;
	//head��tail�ֱ��ʾ���׺Ͷ�β
	busypf_head = busypf_tail = NULL;
	for (i = 0; i < TOTAL_INSTRUCTION; i++)
	{
		if (pl[page[i]].pfn == INVALID)
		{
			//ҳ��ʧЧʱ��ȱҳ��+1
			disaffect += 1;
			if (freepf_head == NULL)
			{	//��ǰû�п���ҳ�棬�򽫶�����̭
				p = busypf_head->next;
				pl[busypf_head->pn].pfn = INVALID;
				freepf_head = busypf_head;
				freepf_head->next = NULL;
				busypf_head = p;
			}
			//����ҳ��״̬
			p = freepf_head->next;
			freepf_head->next = NULL;
			freepf_head->pn = page[i];
			pl[page[i]].pfn = freepf_head->pfn;

			if (busypf_tail == NULL)
				//��ǰû��æҳ��������ָ��
				busypf_head = busypf_tail = freepf_head;
			else
			{	//����ǰ��ҳ��������
				busypf_tail->next = freepf_head;  		
				busypf_tail = freepf_head;
			}
			freepf_head = p;
		}
	}
	printf("FIFOȱҳ��: %.2f\n", (float)disaffect / TOTAL_INSTRUCTION);
}

void LRU(int total_pf)
{
	int min, minj, i, j, present_time;
	init(total_pf); 
	present_time = 0;
	for (i = 0; i < TOTAL_INSTRUCTION; i++)
	{
		if (pl[page[i]].pfn == INVALID)     
		{
			//ҳ��ʧЧʱ��ȱҳ��+1
			disaffect++;
			if (freepf_head == NULL) 
			{
				//��ǰû�п���ҳ��
				min = INF;
				//Ѱ������ʹ�ô�����ҳ��
				for (j = 0; j < TOTAL_VP; j++)
				if (min>pl[j].time&&pl[j].pfn != INVALID)
				{
					min = pl[j].time;
					minj = j;
				}
				//��̭��ҳ��
				freepf_head = &pfc[pl[minj].pfn];
				pl[minj].pfn = INVALID;
				pl[minj].time = -1;
				freepf_head->next = NULL;
			}
			pl[page[i]].pfn = freepf_head->pfn;
			pl[page[i]].time = present_time;
			freepf_head = freepf_head->next;
		}
		else
			//����ʹ�ô���
			pl[page[i]].time = present_time;
		present_time++;
	}
	printf("LRUȱҳ��: %.2f\n", (float)disaffect / TOTAL_INSTRUCTION);
}


int main(){
	int i, o, temp;
	srand((unsigned)time(NULL));
	o = rand() % 320 + 1;
	for (i = 0; i < TOTAL_INSTRUCTION; i++){
		a[i] = i;
	}

	for (i = 0; i < TOTAL_INSTRUCTION; i++){
		o = rand() % TOTAL_INSTRUCTION;
		swap(a[i], a[o]);
	}
	for (i = 0; i < TOTAL_INSTRUCTION; i++){
		page[i] = a[i] / 10;
		offset[i] = a[i] / 10;
	}
	for (i = 4; i <= 32; i++){
		printf("%d page frames\n", i);
		FIFO(i);
		LRU(i);
	}
}