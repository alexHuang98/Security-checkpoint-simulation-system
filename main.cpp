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
#include <graphics.h>

#include <stdio.h>
//����ڵĽṹ
int Stopprint = 0;//�Ƿ�ֹͣ��ӡ�ȴ�����
int Line = 0;//�������� 
int Offduty = 0;//�Ƿ��°�
int MaxCustSingleLine=12;  //���������ȴ��˿���
int MaxLines=10;  //���λ����������MaxLines��ֱ�����
int MaxSeqLen=10;    //�������ȴ�����
int MinTimeLen=2;     //һ�ΰ������ʱ������λΪ��
int MaxTimeLen=5;    //һ�ΰ������ʱ������λΪ��
int MinRestTimeLen=30;    //�����һ����ͣ��Ϣ���ʱ������λΪ��
int MaxRestTimeLen=60;   //�����һ����ͣ��Ϣ���ʱ������λΪ��
FILE* f1;//����������ļ����ļ�output.txt��ָ��
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
	int u = 5;//��̬�ֲ�ģ����u
	int f = 1;//��̫�ֲ�ģ����f
	int flag=0;//�����ж��Ƿ�����ɹ� 
	int y=0; 
	int drawtime;
	int lastdrawtime=0;
	double exetime;
	f1 = fopen("output.txt", "w");
	if (f1==NULL)
	{
		printf("���ļ�����\n");
	}
	//printf("%d", f1);
	int custnum=0;

//	setinitmode(INIT_ANIMATION);
	initgraph(800,600);
	setbkcolor(WHITE);

	
//	setrendermode(RENDER_AUTO);
//	delay_fps(60);
	char caption[50]="ģ���������";
	setcaption(caption);
	custnum=1;
	setfont(16, 0, "����");
	setcolor(WHITE);
	setfillcolor(RED);
	xyprintf(0, 16*y++, "��ӭ���������˿Ͱ���ģ��ϵͳ");
	fprintf(f1, "��ӭ���������˿Ͱ���ģ��ϵͳ");
	//��ʼѡ�񸽼ӹ���--��ģ����ӳ˿�
	char str[100]={'\0'};
	inputbox_getline("��ѡ�����˿ͽ���ģʽ","A.�ֶ����루�Ƽ�����ʹ�ã�\nB.����ѧģ����ӣ��Ƽ���ʹ�þ�����û�ʹ�ã�", str, 100);
	for(i=0;i<=98;i++)
	{
		if(str[i]=='a'||str[i]=='A')
		{
			mode='a';
			flag=1;
		}
		else if(str[i]=='b'||str[i]=='B')
		{
			mode='b';
			flag=1;
		}
	}
	while(flag==0)
	{
	inputbox_getline("��ѡ�����˿ͽ���ģʽ","A.�ֶ����루�Ƽ�����ʹ�ã�\nB.����ѧģ����ӣ��Ƽ���ʹ�þ�����û�ʹ�ã�", str, 100);
	for(i=0;i<=99;i++)
	{
		if(str[i]=='a'||str[i]=='A')
		{
			mode='a';
			flag=1;
		}
		else if(str[i]=='b'||str[i]=='B')
		{
			mode='b';
			flag=1;
		}
	}
	if(flag==0)
	{
		xyprintf(0, 16*y++, "�������\n");
	}
	}
	cleardevice();
	switch (mode)
		{
		case 'b'://ѡ��ģ���Զ����
		case 'B':
			xyprintf(0,16*y++,"���򽫸�����̬�ֲ�ģ�����ɳ˿�\n");
			fprintf(f1, "���򽫸�����̬�ֲ�ģ�����ɳ˿�\n");
			u=5;
			f=1;		
			Math = 1;
			break;
		case 'a'://ѡ���ֶ����
		case 'A':
			Math = 0;
			break;
		default:
			break;
		}
	HANDLE handle1 = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(Input), NULL, 0, NULL);//���������߳�

	for ( k = 0; k < 8; k++) //��ʼ���ṹ��
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
	cleardevice();
	xyprintf(0,0,"����ϵͳ,�����������");
		//delay_fps(60);
	getch();
	cleardevice();

	//getch();
	lasttime = clock() / CLOCKS_PER_SEC;//��ʼ�������жϱ���
	lastdrawtime=clock();
	drawbottom();
	drawsec();
	//getch();
	drawall();
	while(closedown!=1)
	{
		nowtime = clock() / CLOCKS_PER_SEC;//���������
		
		if (((nowtime-lasttime)!=0&& (nowtime - lasttime)%3==0)&&Stopprint==0)
		{
			lasttime = nowtime;
			x = 1;
		}
		else
		{
			x = 0;
		}//������������

		if (Math==1)//ѡ���Զ���ӳ˿�ʱ��ӳ˿�
		{
			customWaitMath(x,u,f);
		}

		AutoSec();//���������

		customIn();//�������˿ͽ��밲���

		if (Offduty==1)//�ж��Ƿ��°࣬�Ƿ��˳�����
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

		for (k = 0; k < 8; k++)//�����ͬʱ�����ж�
		{
			if (door[k].WaitForRest == 1 && ((clock() / CLOCKS_PER_SEC) - door[k].StartWaitTime) > 2)
			{//�������û��ͬʱ���뼴���һ���������Ϣ
				door[k].WaitForRest = 0;
				door[k].nextState = WAITREST;
				printstate(3, k+1);
			}
		}
		drawtime = clock();//���������
		
		if ((drawtime-lastdrawtime)!=0&&(drawtime - lastdrawtime)%500==0)
		{
			drawall();
		lastdrawtime = drawtime;
		}
	}//ѭ���������˳�����

	printf("�˿ʹ�����ϣ������˳�\n");
	fprintf(f1, "�˿ʹ�����ϣ������˳�\n");
	fclose(f1);//�ر��ļ�
	closegraph();
	return 0;
}