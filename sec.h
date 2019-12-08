#include "conh.h"
void AutoSec(void)
{
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		//前四个窗口
		if (door[i].nextState!=10)
		{
			door[i].State = door[i].nextState;
			door[i].nextState = 10;
		}
		//使安检口进入预存状态
		if (i <= 3)
		{
			int restTime = 0;
			int workT;
				switch (door[i].State)
				{
				case WAITREST:
					door[i].StartRestTime = 0;
					if (door[i].WinListCustCout == 0)
					{
						door[i].State = REST;
						//drawstate(i+1,REST);
						printf("安检口%d等待休息结束，开始休息\n",i+1);
						fprintf(f1, "安检口%d等待休息结束，开始休息\n", i + 1);
					}
					else if (door[i].StartSecTime == 0)
					{
						workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
						door[i].Servetime = workT;
						door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
						door[i].State = WAITREST;
						//drawstate(i+1,WAITREST);
					}
					else
					{
						if (((clock() / CLOCKS_PER_SEC) >= door[i].StartSecTime + door[i].Servetime)&& door[i].WinListCustCout!=0)
						{
							door[i].State = WAITREST;
						//	drawstate(i+1,WAITREST);
							door[i].StartSecTime = 0;
							door[i].WinListCustCout--;
							
						//	deleteman(2,door[i].WinListCustCout+1,i+1);
							if(door[i].WinListCustCout!=0)
							{
							printf("安检口【%d】有新乘客开始安检\n",i+1);
							fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
                           }
						}

						else
						{
							door[i].State = WAITREST;
						//	drawstate(i+1,WAITREST);
						}
					}
					break;
				case FULL:
					door[i].StartRestTime = 0;
					if (door[i].StartSecTime == 0) {

						workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
						door[i].Servetime = workT;
						door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
					}
					else if ((clock() / CLOCKS_PER_SEC) >= door[i].StartSecTime + door[i].Servetime) {
						door[i].State = IDLE;
						door[i].WinListCustCout--;
						//drawstate(i+1,IDLE);
					//	deleteman(2,door[i].WinListCustCout+1,i+1);
						if (door[i].WinListCustCout != 0)
						{
							printf("安检口【%d】有新乘客开始安检\n", i + 1);
							fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
						}
						door[i].StartSecTime = 0;
					}
					else
						door[i].State = FULL;
					//	drawstate(i+1,FULL);
					break;
				case REST:
					door[i].StartSecTime = 0;
					if (door[i].StartRestTime == 0)
					{
						restTime = (rand() % (MaxRestTimeLen - MinRestTimeLen + 1) + MinRestTimeLen);
						door[i].StartRestTime = clock() / CLOCKS_PER_SEC;
						door[i].Resttime = restTime;
						door[i].State = REST;
					//	drawstate(i+1,REST);
					
					}
					else if((clock() / CLOCKS_PER_SEC)>door[i].StartRestTime+ door[i].Resttime)
					{
						door[i].State = IDLE;
					//	drawstate(i+1,IDLE);
						printf("安检口%d休息结束\n", i + 1);
						fprintf(f1, "安检口%d休息结束\n", i + 1);
					}
					else
					{
						door[i].Restlen = clock() / CLOCKS_PER_SEC - door[i].StartRestTime;
						door[i].State = REST;
					//	drawstate(i+1,REST);
					}
						break;
					case IDLE:
						door[i].StartRestTime = 0;
						if (door[i].WinListCustCout == 6)
							{
							door[i].State = FULL;
					//		drawstate(i+1,FULL);
							}
						else if(door[i].StartSecTime == 0&&door[i].WinListCustCout>0)
						{
							workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
							door[i].Servetime = workT;
							door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
							door[i].State = IDLE;
					//		drawstate(i+1,IDLE);
						}
						else if (((clock() / CLOCKS_PER_SEC) >= door[i].StartSecTime + door[i].Servetime)&& door[i].StartSecTime != 0) 
							{
							door[i].State = IDLE;
							door[i].WinListCustCout--;
					//		drawstate(i+1,IDLE);
					//		deleteman(2,door[i].WinListCustCout+1,i+1);
							if (door[i].WinListCustCout != 0)
							{
								printf("安检口【%d】有新乘客开始安检\n", i + 1);
								fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
							}
							door[i].StartSecTime = 0;
						}
						else
						{
							door[i].State = IDLE;
					//		drawstate(i+1,IDLE);
						}
						break;
					case SECEND:
						if (door[i].WinListCustCout==0)
						{
							break;
						}
						else if (door[i].StartSecTime == 0)
						{
							workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
							door[i].Servetime = workT;
							door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
							door[i].State = SECEND;
					//		drawstate(i+1,SECEND);
						}
						else if(clock() / CLOCKS_PER_SEC>(door[i].StartSecTime+ door[i].Servetime))
						{
							door[i].StartSecTime = 0;
							door[i].WinListCustCout--;
					//	deleteman(2,door[i].WinListCustCout--,i+1);
							if (door[i].WinListCustCout != 0)
							{
								printf("安检口【%d】有新乘客开始安检\n", i + 1);
								fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
							}
							door[i].State = SECEND;
					//		drawstate(i+1,SECEND);

						}
						else
						{
							door[i].State = SECEND;
					//		drawstate(i+1,SECEND);
						}
						break;
				}
			}
		else
		{
			int startTime;
			int restTime = 0;
			int workT;
				//startTime = clock() / CLOCKS_PER_SEC;
			if ((2*i+2)>Line&&(door[i].State ==IDLE|| door[i].State ==FULL))
			{
				door[i].State = CLOSE;
		//		drawstate(i+1,CLOSE);
				printf("安检口%d关闭\n", i + 1);
				fprintf(f1, "安检口%d关闭\n", i + 1);
			}
				switch (door[i].State)
				{
				case CLOSE:
					if (Line > 3 * i)
					{
						door[i].State = IDLE;
			//			drawstate(i+1,IDLE);
						printf("安检口%d开启\n", i + 1);
						fprintf(f1, "安检口%d开启\n", i + 1);
						break;
						//door[i].StartSecTime = 0;
					}
					if ((door[i].WinListCustCout != 0) && door[i].StartSecTime == 0)
					{
						workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
						door[i].Servetime = workT;
						door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
						door[i].State = CLOSE;
			//			drawstate(i+1,IDLE);
					}
					else if ((clock() / CLOCKS_PER_SEC >= (door[i].Servetime + door[i].StartSecTime)) && door[i].StartSecTime != 0)
					{
						door[i].WinListCustCout--;
				//		deleteman(2,door[i].WinListCustCout+1,i+1);
						if (door[i].WinListCustCout != 0)
						{
							printf("安检口【%d】有新乘客开始安检\n", i + 1);
							fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
						}
						door[i].StartSecTime = 0;
						door[i].State = CLOSE;
					}
					else door[i].State = CLOSE;
					break;
				case WAITREST:

					if (door[i].WinListCustCout == 0)
						door[i].State = REST;

					else if (door[i].StartSecTime == 0)
					{
						workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
						door[i].Servetime = workT;
						door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
						/*					while ((clock() / CLOCKS_PER_SEC) <= workTime1 + workT)
						{

						};
						*/
						door[i].State = WAITREST;
					}
					else
					{
						if (((clock() / CLOCKS_PER_SEC) >= door[i].StartSecTime + door[i].Servetime) && door[i].WinListCustCout != 0)
						{
							door[i].State = WAITREST;
							door[i].StartSecTime = 0;
							door[i].WinListCustCout--;
							if (door[i].WinListCustCout != 0)
							{
								printf("安检口【%d】有新乘客开始安检\n", i + 1);
								fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
							}
						}
						else
						{
							door[i].State = WAITREST;
						}
					}
					break;
				case FULL:
					door[i].StartRestTime = 0;
					if (door[i].WinListCustCout<6)
					{
						door[i].State = IDLE;
					}
					else if (door[i].StartSecTime == 0) {

						workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
						door[i].Servetime = workT;
						door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
					}
					else if ((clock() / CLOCKS_PER_SEC) >= door[i].StartSecTime + door[i].Servetime) {
						door[i].State = IDLE;
						door[i].WinListCustCout--;
						if (door[i].WinListCustCout != 0)
						{
							printf("安检口【%d】有新乘客开始安检\n", i + 1);
							fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
						}
						door[i].StartSecTime = 0;
					}
					else
						door[i].State = FULL;
					break;
				case REST:
					door[i].StartSecTime = 0;
					if (door[i].StartRestTime == 0)
					{
						restTime = (rand() % (MaxRestTimeLen - MinRestTimeLen + 1) + MinRestTimeLen);
						door[i].StartRestTime = clock() / CLOCKS_PER_SEC;
						door[i].Resttime = restTime;
						door[i].Restlen += restTime;
						door[i].State = REST;
					}
					else if ((clock() / CLOCKS_PER_SEC) > door[i].StartRestTime + door[i].Resttime)
					{
						door[i].State = IDLE;
					}
					else
					{
						door[i].State = REST;
					}
					break;
				case IDLE:

					if (door[i].WinListCustCout == 6)
						door[i].State = FULL;
					else if (door[i].WinListCustCout == 0)
					{
						door[i].State = IDLE;
					}
					else if (door[i].StartSecTime == 0 && door[i].WinListCustCout > 0)
					{
						workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
						door[i].Servetime = workT;
						door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
						door[i].State = IDLE;
					}
					else if ((clock() / CLOCKS_PER_SEC) >= door[i].StartSecTime + door[i].Servetime) {
						door[i].State = IDLE;
						door[i].WinListCustCout--;
						if (door[i].WinListCustCout != 0)
						{
							printf("安检口【%d】有新乘客开始安检\n", i + 1);
							fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
						}
						door[i].StartSecTime = 0;
					}
					else
					{
						door[i].State = IDLE;
					}
					break;
				case SECEND:
					if (door[i].WinListCustCout == 0)
					{
						;
					}
					else if (door[i].StartSecTime == 0)
					{
						workT = (clock() % (MaxTimeLen - MinTimeLen + 1) + MinTimeLen);
						door[i].Servetime = workT;
						door[i].StartSecTime = clock() / CLOCKS_PER_SEC;
						door[i].State = SECEND;
					}
					else if (clock() / CLOCKS_PER_SEC > (door[i].StartSecTime + door[i].Servetime))
					{
						door[i].StartSecTime = 0;
						door[i].WinListCustCout--;
						if (door[i].WinListCustCout != 0)
						{
							printf("安检口【%d】有新乘客开始安检\n", i + 1);
							fprintf(f1, "安检口【%d】有新乘客开始安检\n", i + 1);
						}
						door[i].State = SECEND;

					}
					else
					{
						door[i].State = SECEND;
					}
					break;
				}
		}
		}
	}					
int ifRest(int number) {
		int i, flag = 0;
		int secnum = 0;
		for (i = 0; i < 9; i++)
		{
			if (((door[i].State == FULL) || (door[i].State == IDLE)) && (i != number))
			{
				flag = 1;
				secnum++;
			}
		}
		if (flag != 1 || (Line / secnum) >= MaxSeqLen)
			flag = 0;
		return flag;
	}