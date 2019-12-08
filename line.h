#include "conh.h"

void customWaitMath(int x,int u,int f)
{
	int nowtime;//用于判断现在时间
	int lasttime = 0;///记录上次人员进入时间，用于周期性打印
	int inNumber;//用于计算进入的人数
	int randomNum;//用于按数学模型输出人数
	int lastLine;//用于人数溢出时记录进入人数
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
			printf("按数学模型进入%d名乘客\n", u);
			fprintf(f1, "按数学模型进入%d名乘客\n", u);
		}
		else if (randomNum<96)
		{
			if (randomNum%2==0)
			{
				Line += u+f;
				printf("按数学模型进入%d名乘客\n", u + f);
				fprintf(f1, "按数学模型进入%d名乘客\n", u + f);

			}
			else
			{
				if ((u-f)>0)
				{
					Line += (u - f);
					printf("按数学模型进入%d名乘客\n", (u - f));
					fprintf(f1, "按数学模型进入%d名乘客\n", (u - f));

				}
			}
		}
		else
		{
			if (randomNum % 2 == 0)
			{
				Line += (u + 2*f);
				printf("按数学模型进入%d名乘客\n", (u + 2 * f));
				fprintf(f1, "按数学模型进入%d名乘客\n", (u + 2 * f));

			}
			else
			{
				if ((u - 2 * f)>0)
				{
					Line += (u - 2 * f);
					printf("按数学模型进入%d名乘客\n", (u - 2 * f));
					fprintf(f1, "按数学模型进入%d名乘客\n", (u - 2 * f));
				}
			}
		}
	}
	if (Line>(MaxLines*MaxCustSingleLine))
	{
		Line = (MaxLines*MaxCustSingleLine);
		printf("由于人数溢出，实际有%d名乘客进入\n", Line - lastLine);
	}
}
int custnum; 
int customWait(void)
{
	
	if (Line<(MaxLines*MaxCustSingleLine)&&Offduty!=1)
	{
		Line++;
		custnum++;
		printf("乘客进入缓冲区\n");
		return 1;
	}
	else
		return 0;
}
extern int custom[1010]; 
extern int  custnum;
void customIn(void)
{
	int i; //用于计数
	while (Line)
	{
		int flag = 0;//用于统计不能进入乘客的安检窗口数量
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
				printf("缓冲区有乘客进入安检口%d\n",i+1);
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
