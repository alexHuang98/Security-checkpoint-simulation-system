#include "conh.h"

void customWaitMath(int x,int u,int f)
{
	int nowtime;//�����ж�����ʱ��
	int lasttime = 0;///��¼�ϴ���Ա����ʱ�䣬���������Դ�ӡ
	int inNumber;//���ڼ�����������
	int randomNum;//���ڰ���ѧģ���������
	int lastLine;//�����������ʱ��¼��������
	lastLine = Line;
	if (x==1 && Offduty!=1&& Line<(MaxLines*MaxCustSingleLine))
	{
		srand((unsigned)time(NULL));
		randomNum=rand() % 100+1;
//		printf("%d", randomNum);
//		fprintf(f1, "%d", randomNum);
		if (randomNum<=68)
		{
			
			Line += u;
			printf("����ѧģ�ͽ���%d���˿�\n", u);
			fprintf(f1, "����ѧģ�ͽ���%d���˿�\n", u);
		}
		else if (randomNum<96)
		{
			if (randomNum%2==0)
			{
				Line += u+f;
				printf("����ѧģ�ͽ���%d���˿�\n", u + f);
				fprintf(f1, "����ѧģ�ͽ���%d���˿�\n", u + f);

			}
			else
			{
				if ((u-f)>0)
				{
					Line += (u - f);
					printf("����ѧģ�ͽ���%d���˿�\n", (u - f));
					fprintf(f1, "����ѧģ�ͽ���%d���˿�\n", (u - f));

				}
			}
		}
		else
		{
			if (randomNum % 2 == 0)
			{
				Line += (u + 2*f);
				printf("����ѧģ�ͽ���%d���˿�\n", (u + 2 * f));
				fprintf(f1, "����ѧģ�ͽ���%d���˿�\n", (u + 2 * f));

			}
			else
			{
				if ((u - 2 * f)>0)
				{
					Line += (u - 2 * f);
					printf("����ѧģ�ͽ���%d���˿�\n", (u - 2 * f));
					fprintf(f1, "����ѧģ�ͽ���%d���˿�\n", (u - 2 * f));
				}
			}
		}
	}
	if (Line>(MaxLines*MaxCustSingleLine))
	{
		Line = (MaxLines*MaxCustSingleLine);
		printf("�������������ʵ����%d���˿ͽ���\n", Line - lastLine);
	}
}
int custnum; 
int customWait(void)
{
	
	if (Line<(MaxLines*MaxCustSingleLine)&&Offduty!=1)
	{
		Line++;
		custnum++;
		printf("�˿ͽ��뻺����\n");
		return 1;
	}
	else
		return 0;
}
extern int custom[1010]; 
extern int  custnum;
void customIn(void)
{
	int i; //���ڼ���
	while (Line)
	{
		int flag = 0;//����ͳ�Ʋ��ܽ���˿͵İ��촰������
		for ( i = 0; i < 8; i++)
		{
			if (door[i].State==IDLE&&Line>0&&door[i].WinListCustCout<6)
			{
				door[i].WinListCustCout++;
				custom[custnum-1]=i+1;
				if(door[i].WinListCustCout>0)
					{
					//drawman(2,door[i].WinListCustCout,i+1,custnum);
					custnum++;}
				if (door[i].WinListCustCout==6)
				{
					door[i].nextState = FULL;
				}
				Line--;
				printf("�������г˿ͽ��밲���%d\n",i+1);
				flag = 0;
			}
			else if(door[i].State!=IDLE||door[i].WinListCustCout==6)
			{
				flag++;
			}
		}
		if (flag==8)
		{
			break;
		}
	}
}
