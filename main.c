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

//安检口的结构
		 //队列人数
int Stopprint = 0;//是否停止打印等待输入
int Line = 0;//队列状态
int Offduty = 0;//是否下班
int MaxCustSingleLine=30;  //单队列最大等待乘客数
int MaxLines=8;  //蛇形缓冲区最多由MaxLines个直队组成
int MaxSeqLen=10;    //最大允许等待长度
int MinTimeLen=2;     //一次安检最短时长，单位为秒
int MaxTimeLen=5;    //一次安检最大时长，单位为秒
int MinRestTimeLen=30;    //安检口一次暂停休息最短时长，单位为秒
int MaxRestTimeLen=60;   //安检口一次暂停休息最大时长，单位为秒
double TimeLen;//平均安检时长
FILE* f1;//用于输出到文件
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
	int u = 5;
	int f = 1;
	f1 = fopen("output.txt", "w");
	if (f1==NULL)
	{
		printf("打开文件错误\n");
	}
	//printf("%d", f1);
	printf("欢迎来到机场乘客案件模拟系统");
	printf("请选择程序乘客进入模式\n");
	printf("A.手动输入（推荐新手使用）\n");
	printf("B.按数学模型添加（推荐有使用经验的用户使用）\n");
	while (inputflag!=1)
	{
		mode = getchar();
		switch (mode)
		{
		case 'b':
		case 'B':
			printf("程序将根据正态分布模型生成乘客\n");
			fprintf(f1, "程序将根据正态分布模型生成乘客\n");
			printf("请输入每三秒平均乘客数量:\n");
			fprintf(f1, "请输入每三秒平均乘客数量:\n");
			k=scanf("%d", &u);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("输入错误，请重新输入\n");
					fprintf(f1, "输入错误，请重新输入\n");
				}
				getchar();
				k = scanf("%d", &u);
				fprintf(f1, "%d\n", u);
				i = 1;
			}
			i = 0;
			printf("请输入乘客数量变化范围(变化范围最好小于平均数量的三倍）\n");
			k=scanf("%d", &f);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("输入错误，请重新输入\n");
					fprintf(f1, "输入错误，请重新输入\n");
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
			printf("输入错误\n");
			break;
		default:
			break;
		}
	}
	inputflag = 0;
//	Math = 1;
	getchar();
	printf("请选择程序执行模式：\n");
	printf("A.使用系统预设值（推荐新手使用）\n");
	printf("B.以用户设置的值运行程序（推荐有使用经验的用户使用）\n");
	printf("请选择运行模式：\n");
	fprintf(f1, "欢迎来到机场乘客案件模拟系统");
	fprintf(f1, "请选择程序执行模式：\n");
	fprintf(f1, "A.使用系统预设值（推荐新手使用）\n");
	fprintf(f1, "B.以用户设置的值运行程序（推荐有使用经验的用户使用）\n");
	fprintf(f1, "请选择运行模式：\n");
	while (inputflag!=1)
	{
		mode = getchar();
		fprintf(f1, "%c", mode);
		switch (mode)
		{
		case 'a':
		case 'A':
			inputflag = 1;
			printf("将使用预设值进入程序");
			printf("预设值：\n");
			printf("单列最大等待乘客数：30\n");
			printf("蛇形队列最大直队数量：8\n");
			printf("最大允许等待长度：10\n");
			printf("一次安检最短时间：2\n");
			printf("一次安检最长时间：5\n");
			printf("一次休息最短时间：30\n");
			printf("一次休息最长时间：60\n");
			fprintf(f1, "将使用预设值进入程序");
			fprintf(f1, "预设值：\n");
			fprintf(f1, "单列最大等待乘客数：30\n");
			fprintf(f1, "蛇形队列最大直队数量：8\n");
			fprintf(f1, "最大允许等待长度：10\n");
			fprintf(f1, "一次安检最短时间：2\n");
			fprintf(f1, "一次安检最长时间：5\n");
			fprintf(f1, "一次休息最短时间：30\n");
			fprintf(f1, "一次休息最长时间：60\n");
			break;
		case 'b':
		case 'B':
			printf("下面开始设置程序:\n");
			printf("请输入单列最大等待乘客数（请输入大于零的整数）\n");
			fprintf(f1,"下面开始设置程序:\n");
			fprintf(f1,"请输入单列最大等待乘客数（请输入大于零的整数）\n");
			k=scanf("%d", &MaxCustSingleLine);
			fprintf(f1, "%d\n", MaxCustSingleLine);
			while (k!=1)
			{
				if (i==0)
				{
					printf("输入错误，请重新输入\n");
					printf("请输入单列最大等待乘客数（请输入大于零的整数）\n");
					fprintf(f1,"输入错误，请重新输入\n");
					fprintf(f1,"请输入单列最大等待乘客数（请输入大于零的整数）\n");
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
			printf("读取成功\n请输入蛇形队列最大直队数量（请输入大于零的整数）\n");
			fprintf(f1,"读取成功\n请输入蛇形队列最大直队数量（请输入大于零的整数）\n");
			k=scanf("%d", &MaxLines);
			fprintf(f1, "%d\n", MaxLines);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("输入错误，请重新输入\n");
					printf("请输入蛇形队列最大直队数量（请输入大于零的整数）\n");
					fprintf(f1,"输入错误，请重新输入\n");
					fprintf(f1,"请输入蛇形队列最大直队数量（请输入大于零的整数）\n");
				}
				getchar();
				k = scanf("%d", &MaxLines);
				fprintf(f1, "%d\n", MaxLines);
				i = 1;
			}
			i = 0;
			printf("读取成功\n请输入最大允许等待长度（请输入大于零的整数）\n");
			fprintf(f1,"读取成功\n请输入最大允许等待长度（请输入大于零的整数）\n");
			k=scanf("%d", &MaxSeqLen);
			fprintf(f1, "%d\n", MaxSeqLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("输入错误，请重新输入\n");
					printf("请输入最大允许等待长度（请输入大于零的整数）\n");
					fprintf(f1,"输入错误，请重新输入\n");
					fprintf(f1,"请输入最大允许等待长度（请输入大于零的整数）\n");
				}
				getchar();
				k = scanf("%d", &MaxSeqLen);
				fprintf(f1, "%d\n", MaxSeqLen);
				i = 1;
			}
			i = 0;
			printf("读取成功\n请输入一次安检最短时间（请输入大于零的整数）\n");
			fprintf(f1,"读取成功\n请输入一次安检最短时间（请输入大于零的整数）\n");
			k = scanf("%d", &MinTimeLen);
			fprintf(f1, "%d\n", MinTimeLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("输入错误，请重新输入\n");
					printf("请输入一次安检最短时间（请输入大于零的整数）\n");
					fprintf(f1,"输入错误，请重新输入\n");
					fprintf(f1,"请输入一次安检最短时间（请输入大于零的整数）\n");

				}
				getchar();
				k = scanf("%d", &MinTimeLen);
				fprintf(f1, "%d\n", MinTimeLen);
				i = 1;
			}
			i = 0;
			printf("读取成功\n请输入一次安检最长时间（请输入大于零的整数）\n");
			fprintf(f1,"读取成功\n请输入一次安检最长时间（请输入大于零的整数）\n");
			k = scanf("%d", &MaxTimeLen);
			fprintf(f1, "%d\n", MaxTimeLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("输入错误，请重新输入\n");
					printf("请输入一次安检最长时间（请输入大于零的整数）\n");
					fprintf(f1,"输入错误，请重新输入\n");
					fprintf(f1,"请输入一次安检最长时间（请输入大于零的整数）\n");
				}
				getchar();
				k = scanf("%d", &MaxTimeLen);
				fprintf(f1, "%d\n", MaxTimeLen);
				i = 1;
			}
			i = 0;
			printf("读取成功\n请输入一次休息最短时间（请输入大于零的整数）\n");
			fprintf(f1,"读取成功\n请输入一次休息最短时间（请输入大于零的整数）\n");
			k = scanf("%d", &MinRestTimeLen);
			fprintf(f1, "%d\n", MinRestTimeLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("输入错误，请重新输入\n");
					printf("请输入一次休息最短时间（请输入大于零的整数）\n");
					fprintf(f1,"输入错误，请重新输入\n");
					fprintf(f1,"请输入一次休息最短时间（请输入大于零的整数）\n");
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
			printf("读取成功\n请输入一次休息最长时间（请输入大于零的整数）\n");
			fprintf(f1,"读取成功\n请输入一次休息最长时间（请输入大于零的整数）\n");
			k = scanf("%d", &MaxRestTimeLen);
			fprintf(f1, "%d\n", MaxRestTimeLen);
			while (k != 1)
			{
				if (i == 0)
				{
					printf("输入错误，请重新输入\n");
					printf("请输入一次休息最长时间（请输入大于零的整数）\n");
					fprintf(f1,"输入错误，请重新输入\n");
					fprintf(f1,"请输入一次休息最长时间（请输入大于零的整数）\n");
				}
				getchar();
				k = scanf("%d", &MaxRestTimeLen);
				fprintf(f1, "%d\n", MaxRestTimeLen);
				i = 1;
			}
			i = 0;
			printf("读取成功\n程序设置完毕\n");
			fprintf(f1,"读取成功\n程序设置完毕\n");
			inputflag = 1;
			break;
		case '\n':
			printf("输入错误，请重新输入\n");

			fprintf(f1,"输入错误，请重新输入\n");
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
	printf("乘客处理完毕，程序退出\n");
	fprintf(f1, "乘客处理完毕，程序退出\n");
	fclose(f1);
	//system("pause");
	return 0;
}