#include "conh.h" 
#include "input.h"
#include"line.h"
#include"print.h"
#include"sec.h"
//���촦��������
#define WAITREST 0
#define FULL 1
#define REST 2
#define IDLE 3
#define CLOSE 4
#define SECEND 5
//ȫ�ֱ�������

//����ڵĽṹ
		 //��������
int Stopprint = 0;//�Ƿ�ֹͣ��ӡ�ȴ�����
int Line = 0;//����״̬
int Offduty = 0;//�Ƿ��°�
int MaxCustSingleLine=30;  //���������ȴ��˿���
int MaxLines=8;  //���λ����������MaxLines��ֱ�����
int MaxSeqLen=10;    //�������ȴ�����
int MinTimeLen=2;     //һ�ΰ������ʱ������λΪ��
int MaxTimeLen=5;    //һ�ΰ������ʱ������λΪ��
int MinRestTimeLen=30;    //�����һ����ͣ��Ϣ���ʱ������λΪ��
int MaxRestTimeLen=60;   //�����һ����ͣ��Ϣ���ʱ������λΪ��
double TimeLen;//ƽ������ʱ��
FILE* f1;//����������ļ�
int main() {
	int closedown = 0;//�жϳ˿��Ƿ�ȫ���뿪
	int nowtime;//�����ж�����ʱ��
	int lasttime = 0;///��¼�ϴδ�ӡʱ�䣬���������Դ�ӡ
	char mode;//��¼�û�ѡ���ģʽ
	int inputflag=0;//�����ж��û������Ƿ���ȷ
	int k;//����ѭ���ļ���
	int i=0;//�����ж������Ƿ�Ϸ�
	int Math = 0;//�����ж��Ƿ�����ѧ�������Ƴ˿�
	int x = 0;//�������ɳ˿�
	int u = 5;
	int f = 1;
	f1 = fopen("output.txt", "w");
	if (f1==NULL)
	{
		printf("���ļ�����\n");
	}
	//printf("%d", f1);
	printf("��ӭ���������˿Ͱ���ģ��ϵͳ");
	printf("��ѡ�����˿ͽ���ģʽ\n");
	printf("A.�ֶ����루�Ƽ�����ʹ�ã�\n");
	printf("B.����ѧģ����ӣ��Ƽ���ʹ�þ�����û�ʹ�ã�\n");
	while (inputflag!=1)
	{
		mode = getchar();
		switch (mode)
		{
		case 'b':
		case 'B':
			printf("���򽫸�����̬�ֲ�ģ�����ɳ˿�\n");
			fprintf(f1, "���򽫸�����̬�ֲ�ģ�����ɳ˿�\n");
			printf("������ÿ����ƽ���˿�����:\n");
			fprintf(f1, "������ÿ����ƽ���˿�����:\n");
			k=scanf("%d", &u);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("�����������������\n");
					fprintf(f1, "�����������������\n");
				}
				getchar();
				k = scanf("%d", &u);
				fprintf(f1, "%d\n", u);
				i = 1;
			}
			i = 0;
			printf("������˿������仯��Χ(�仯��Χ���С��ƽ��������������\n");
			k=scanf("%d", &f);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("�����������������\n");
					fprintf(f1, "�����������������\n");
				}
				getchar();
				k = scanf("%d", &f);
				fprintf(f1, "%d\n", f);
				i = 1;
			}
			i = 0;
			Math = 1;
			inputflag = 1;
			break;
		case 'a':
		case 'A':
			Math = 0;
			inputflag = 1;
			break;
		case '\n':
			printf("�������\n");
			break;
		default:
			break;
		}
	}
	inputflag = 0;
//	Math = 1;
	getchar();
	printf("��ѡ�����ִ��ģʽ��\n");
	printf("A.ʹ��ϵͳԤ��ֵ���Ƽ�����ʹ�ã�\n");
	printf("B.���û����õ�ֵ���г����Ƽ���ʹ�þ�����û�ʹ�ã�\n");
	printf("��ѡ������ģʽ��\n");
	fprintf(f1, "��ӭ���������˿Ͱ���ģ��ϵͳ");
	fprintf(f1, "��ѡ�����ִ��ģʽ��\n");
	fprintf(f1, "A.ʹ��ϵͳԤ��ֵ���Ƽ�����ʹ�ã�\n");
	fprintf(f1, "B.���û����õ�ֵ���г����Ƽ���ʹ�þ�����û�ʹ�ã�\n");
	fprintf(f1, "��ѡ������ģʽ��\n");
	while (inputflag!=1)
	{
		mode = getchar();
		fprintf(f1, "%c", mode);
		switch (mode)
		{
		case 'a':
		case 'A':
			inputflag = 1;
			printf("��ʹ��Ԥ��ֵ�������");
			printf("Ԥ��ֵ��\n");
			printf("�������ȴ��˿�����30\n");
			printf("���ζ������ֱ��������8\n");
			printf("�������ȴ����ȣ�10\n");
			printf("һ�ΰ������ʱ�䣺2\n");
			printf("һ�ΰ����ʱ�䣺5\n");
			printf("һ����Ϣ���ʱ�䣺30\n");
			printf("һ����Ϣ�ʱ�䣺60\n");
			fprintf(f1, "��ʹ��Ԥ��ֵ�������");
			fprintf(f1, "Ԥ��ֵ��\n");
			fprintf(f1, "�������ȴ��˿�����30\n");
			fprintf(f1, "���ζ������ֱ��������8\n");
			fprintf(f1, "�������ȴ����ȣ�10\n");
			fprintf(f1, "һ�ΰ������ʱ�䣺2\n");
			fprintf(f1, "һ�ΰ����ʱ�䣺5\n");
			fprintf(f1, "һ����Ϣ���ʱ�䣺30\n");
			fprintf(f1, "һ����Ϣ�ʱ�䣺60\n");
			break;
		case 'b':
		case 'B':
			printf("���濪ʼ���ó���:\n");
			printf("�����뵥�����ȴ��˿�����������������������\n");
			fprintf(f1,"���濪ʼ���ó���:\n");
			fprintf(f1,"�����뵥�����ȴ��˿�����������������������\n");
			k=scanf("%d", &MaxCustSingleLine);
			fprintf(f1, "%d\n", MaxCustSingleLine);
			while (k!=1)
			{
				if (i==0)
				{
					printf("�����������������\n");
					printf("�����뵥�����ȴ��˿�����������������������\n");
					fprintf(f1,"�����������������\n");
					fprintf(f1,"�����뵥�����ȴ��˿�����������������������\n");
				}
				
				k = scanf("%d", &MaxCustSingleLine);
				fprintf(f1, "%d\n", MaxCustSingleLine);
				i = 1;
				if (MinRestTimeLen =='\n'||getchar()=='\n')
				{
					i = 0;
				}
			}
			i = 0;
			printf("��ȡ�ɹ�\n���������ζ������ֱ��������������������������\n");
			fprintf(f1,"��ȡ�ɹ�\n���������ζ������ֱ��������������������������\n");
			k=scanf("%d", &MaxLines);
			fprintf(f1, "%d\n", MaxLines);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("�����������������\n");
					printf("���������ζ������ֱ��������������������������\n");
					fprintf(f1,"�����������������\n");
					fprintf(f1,"���������ζ������ֱ��������������������������\n");
				}
				getchar();
				k = scanf("%d", &MaxLines);
				fprintf(f1, "%d\n", MaxLines);
				i = 1;
			}
			i = 0;
			printf("��ȡ�ɹ�\n�������������ȴ����ȣ�������������������\n");
			fprintf(f1,"��ȡ�ɹ�\n�������������ȴ����ȣ�������������������\n");
			k=scanf("%d", &MaxSeqLen);
			fprintf(f1, "%d\n", MaxSeqLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("�����������������\n");
					printf("�������������ȴ����ȣ�������������������\n");
					fprintf(f1,"�����������������\n");
					fprintf(f1,"�������������ȴ����ȣ�������������������\n");
				}
				getchar();
				k = scanf("%d", &MaxSeqLen);
				fprintf(f1, "%d\n", MaxSeqLen);
				i = 1;
			}
			i = 0;
			printf("��ȡ�ɹ�\n������һ�ΰ������ʱ�䣨������������������\n");
			fprintf(f1,"��ȡ�ɹ�\n������һ�ΰ������ʱ�䣨������������������\n");
			k = scanf("%d", &MinTimeLen);
			fprintf(f1, "%d\n", MinTimeLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("�����������������\n");
					printf("������һ�ΰ������ʱ�䣨������������������\n");
					fprintf(f1,"�����������������\n");
					fprintf(f1,"������һ�ΰ������ʱ�䣨������������������\n");

				}
				getchar();
				k = scanf("%d", &MinTimeLen);
				fprintf(f1, "%d\n", MinTimeLen);
				i = 1;
			}
			i = 0;
			printf("��ȡ�ɹ�\n������һ�ΰ����ʱ�䣨������������������\n");
			fprintf(f1,"��ȡ�ɹ�\n������һ�ΰ����ʱ�䣨������������������\n");
			k = scanf("%d", &MaxTimeLen);
			fprintf(f1, "%d\n", MaxTimeLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("�����������������\n");
					printf("������һ�ΰ����ʱ�䣨������������������\n");
					fprintf(f1,"�����������������\n");
					fprintf(f1,"������һ�ΰ����ʱ�䣨������������������\n");
				}
				getchar();
				k = scanf("%d", &MaxTimeLen);
				fprintf(f1, "%d\n", MaxTimeLen);
				i = 1;
			}
			i = 0;
			printf("��ȡ�ɹ�\n������һ����Ϣ���ʱ�䣨������������������\n");
			fprintf(f1,"��ȡ�ɹ�\n������һ����Ϣ���ʱ�䣨������������������\n");
			k = scanf("%d", &MinRestTimeLen);
			fprintf(f1, "%d\n", MinRestTimeLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("�����������������\n");
					printf("������һ����Ϣ���ʱ�䣨������������������\n");
					fprintf(f1,"�����������������\n");
					fprintf(f1,"������һ����Ϣ���ʱ�䣨������������������\n");
				}
				getchar();
				k = scanf("%d", &MinRestTimeLen);
				fprintf(f1, "%d\n", MinRestTimeLen);
				i = 1;
				if (MinRestTimeLen=='\n')
				{
					i = 0;
				}
			}
			i = 0;
			printf("��ȡ�ɹ�\n������һ����Ϣ�ʱ�䣨������������������\n");
			fprintf(f1,"��ȡ�ɹ�\n������һ����Ϣ�ʱ�䣨������������������\n");
			k = scanf("%d", &MaxRestTimeLen);
			fprintf(f1, "%d\n", MaxRestTimeLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("�����������������\n");
					printf("������һ����Ϣ�ʱ�䣨������������������\n");
					fprintf(f1,"�����������������\n");
					fprintf(f1,"������һ����Ϣ�ʱ�䣨������������������\n");
				}
				getchar();
				k = scanf("%d", &MaxRestTimeLen);
				fprintf(f1, "%d\n", MaxRestTimeLen);
				i = 1;
			}
			i = 0;
			printf("��ȡ�ɹ�\n�����������\n");
			fprintf(f1,"��ȡ�ɹ�\n�����������\n");
			inputflag = 1;
			break;
		case '\n':
			printf("�����������������\n");

			fprintf(f1,"�����������������\n");
			break;
		default:
			break;
		}
	}
	TimeLen = (MaxTimeLen + MinTimeLen) / 2.0;
	HANDLE handle1 = CreateThread(NULL, 0, Input, NULL, 0, NULL);
	for ( k = 0; k < 8; k++)
	{
		if (k<=3)
		{
			door[k].State = IDLE;
			door[k].nextState = 10;
			door[k].WinListCustCout = 0;
			door[k].WaitForRest = 0;
			door[k].Restlen = 0;
		}
		else
		{
			door[k].State = CLOSE;
			door[k].nextState = 10;
			door[k].WinListCustCout = 0;
			door[k].WaitForRest = 0;
			door[k].Restlen = 0;
		}
	}
	lasttime = clock() / CLOCKS_PER_SEC;
	while (closedown!=1)
	{
		nowtime = clock() / CLOCKS_PER_SEC;
		if (((nowtime-lasttime)!=0&& (nowtime - lasttime)%3==0)&&Stopprint==0)
		{
			printstate(0,0);
			lasttime = nowtime;
			x = 1;
		}
		else
		{
			x = 0;
		}
		AutoSec();
		customIn();
		if (Math==1)
		{
			customWaitMath(x,u,f);
		}
		if (Offduty==1)
		{
			for (k = 0; k <= 7; k++)
			{
				if (door[k].WinListCustCout==0)
				{
					closedown = 1;
				}
				else
				{
					closedown = 0;
					break;
				}
			}
		}
		for (k = 0; k < 8; k++)
		{
			if (door[k].WaitForRest == 1 && ((clock() / CLOCKS_PER_SEC) - door[k].StartWaitTime) > 2)
			{
				door[k].WaitForRest = 0;
				door[k].nextState = WAITREST;
				printstate(3, k+1);
			}
		}
	}
	printf("�˿ʹ�����ϣ������˳�\n");
	fprintf(f1, "�˿ʹ�����ϣ������˳�\n");
	fclose(f1);
	//system("pause");
	return 0;
}