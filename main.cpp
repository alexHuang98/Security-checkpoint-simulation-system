#include "conh.h" 
#include "input.h"
#include"line.h"
#include"print.h"
#include"sec.h"
//安检处常量设置
#define WAITREST 0
#define FULL 1
#define REST 2
#define IDLE 3
#define CLOSE 4
#define SECEND 5
//全局变量定义
#include <graphics.h>

#include <stdio.h>
//安检口的结构
int Stopprint = 0;//是否停止打印等待输入
int Line = 0;//队列人数 
int Offduty = 0;//是否下班
int MaxCustSingleLine=12;  //单队列最大等待乘客数
int MaxLines=10;  //蛇形缓冲区最多由MaxLines个直队组成
int MaxSeqLen=10;    //最大允许等待长度
int MinTimeLen=2;     //一次安检最短时长，单位为秒
int MaxTimeLen=5;    //一次安检最大时长，单位为秒
int MinRestTimeLen=30;    //安检口一次暂停休息最短时长，单位为秒
int MaxRestTimeLen=60;   //安检口一次暂停休息最大时长，单位为秒
FILE* f1;//用于输出到文件，文件output.txt的指针
int main() {
	int closedown = 0;//判断乘客是否全部离开
	int nowtime;//用于判断现在时间
	int lasttime = 0;///记录上次打印时间，用于周期性打印
	char mode;//记录用户选择的模式
	int inputflag=0;//用于判断用户输入是否正确
	int k;//由于循环的计数
	int i=0;//用于判断输入是否合法
	int Math = 0;//用于判断是否按照数学规律声称乘客
	int x = 0;//用于生成乘客
	int u = 5;//正态分布模型中u
	int f = 1;//正太分布模型中f
	int flag=0;//用于判断是否输入成功 
	int y=0; 
	int drawtime;
	int lastdrawtime=0;
	double exetime;
	f1 = fopen("output.txt", "w");
	if (f1==NULL)
	{
		printf("打开文件错误\n");
	}
	//printf("%d", f1);
	int custnum=0;

//	setinitmode(INIT_ANIMATION);
	initgraph(800,600);
	setbkcolor(WHITE);

	
//	setrendermode(RENDER_AUTO);
//	delay_fps(60);
	char caption[50]="模拟机场安检";
	setcaption(caption);
	custnum=1;
	setfont(16, 0, "宋体");
	setcolor(WHITE);
	setfillcolor(RED);
	xyprintf(0, 16*y++, "欢迎来到机场乘客案件模拟系统");
	fprintf(f1, "欢迎来到机场乘客案件模拟系统");
	//开始选择附加功能--按模型添加乘客
	char str[100]={'\0'};
	inputbox_getline("请选择程序乘客进入模式","A.手动输入（推荐新手使用）\nB.按数学模型添加（推荐有使用经验的用户使用）", str, 100);
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
	inputbox_getline("请选择程序乘客进入模式","A.手动输入（推荐新手使用）\nB.按数学模型添加（推荐有使用经验的用户使用）", str, 100);
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
		xyprintf(0, 16*y++, "输入错误\n");
	}
	}
	cleardevice();
	switch (mode)
		{
		case 'b'://选择按模型自动添加
		case 'B':
			xyprintf(0,16*y++,"程序将根据正态分布模型生成乘客\n");
			fprintf(f1, "程序将根据正态分布模型生成乘客\n");
			u=5;
			f=1;		
			Math = 1;
			break;
		case 'a'://选择手动添加
		case 'A':
			Math = 0;
			break;
		default:
			break;
		}
	HANDLE handle1 = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(Input), NULL, 0, NULL);//加载输入线程

	for ( k = 0; k < 8; k++) //初始化结构体
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
	xyprintf(0,0,"进入系统,按任意键继续");
		//delay_fps(60);
	getch();
	cleardevice();

	//getch();
	lasttime = clock() / CLOCKS_PER_SEC;//初始化周期判断变量
	lastdrawtime=clock();
	drawbottom();
	drawsec();
	//getch();
	drawall();
	while(closedown!=1)
	{
		nowtime = clock() / CLOCKS_PER_SEC;//周期性输出
		
		if (((nowtime-lasttime)!=0&& (nowtime - lasttime)%3==0)&&Stopprint==0)
		{
			lasttime = nowtime;
			x = 1;
		}
		else
		{
			x = 0;
		}//周期性输出完毕

		if (Math==1)//选择自动添加乘客时添加乘客
		{
			customWaitMath(x,u,f);
		}

		AutoSec();//安检口运行

		customIn();//缓冲区乘客进入安检口

		if (Offduty==1)//判断是否下班，是否退出程序
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

		for (k = 0; k < 8; k++)//安检口同时输入判断
		{
			if (door[k].WaitForRest == 1 && ((clock() / CLOCKS_PER_SEC) - door[k].StartWaitTime) > 2)
			{//若两秒后没有同时输入即令第一个输入的休息
				door[k].WaitForRest = 0;
				door[k].nextState = WAITREST;
				printstate(3, k+1);
			}
		}
		drawtime = clock();//周期性输出
		
		if ((drawtime-lastdrawtime)!=0&&(drawtime - lastdrawtime)%500==0)
		{
			drawall();
		lastdrawtime = drawtime;
		}
	}//循环结束，退出程序

	printf("乘客处理完毕，程序退出\n");
	fprintf(f1, "乘客处理完毕，程序退出\n");
	fclose(f1);//关闭文件
	closegraph();
	return 0;
}