#include "conh.h"
void printstate(int state, int number)
{
	int currentTime = clock() / CLOCKS_PER_SEC;
	int i;
	//printf("T=%d\n", currentTime);
	switch (state)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		//printf("进入失败\n");
		fprintf(f1, "进入失败\n");
		break;
	case 3:
		//printf("安检口【%d】开始进入等待休息状态\n", number);
		fprintf(f1, "安检口【%d】开始进入等待休息状态\n", number);
		break;
	case 4:
		//printf("安检口【%d】休息请求未被批准\n", number);
		fprintf(f1, "安检口【%d】休息请求未被批准\n", number);
		break;
	case 5:
		//printf("安检口【%d】恢复工作成功\n", number);
		fprintf(f1, "安检口【%d】恢复工作成功\n", number);
		break;
	case 6:
		//printf("进入下班状态\n");
		fprintf(f1, "进入下班状态\n");
	case 7:
		//printf("安检口【%d】不在休息状态\n", number);
		fprintf(f1, "安检口【%d】不在休息状态\n", number);
	default:
		break;
	}
	if (state==0)
	{
		//printf("OFFDUTY=");
		fprintf(f1, "OFFDUTY=");
		if (Offduty)
		{
			//printf("Y\n");
			fprintf(f1, "Y\n");
		}
		else
		{
			//printf("N\n");
			fprintf(f1, "N\n");
		}
		//printf("ListLines=%d\n", Line / MaxCustSingleLine);
		fprintf(f1, "ListLines=%d\n", Line / MaxCustSingleLine);
		//printf("ListCustCount=%d\n", Line);
		fprintf(f1, "ListCustCount=%d\n", Line);
		for (i = 0; i < 8; i++)
		{
			//printf("WIN%d: state= ", i + 1);
			fprintf(f1, "WIN%d: state= ", i + 1);
			switch (door[i].State)
			{
			case FULL:
				//printf("已满   ");
				fprintf(f1, "已满   ");
				//printf("ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);
				fprintf(f1, "ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);
				//printf("RestLen=%d/%d   ", 0, 0);
				fprintf(f1, "RestLen=%d/%d   ", 0, 0);
				//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
				fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
				break;
			case IDLE:
				if (door[i].WinListCustCout == 0)
				{
					//printf("空闲   ");
					fprintf(f1, "空闲   ");
					//printf("ServLen=%d/%d   ", 0, 0);
					fprintf(f1, "ServLen=%d/%d   ", 0, 0);
					//printf("RestLen=%d/%d   ", 0, 0);
					fprintf(f1, "RestLen=%d/%d   ", 0, 0);
					//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
					fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
				}
				else
				{
					//printf("工作   ");
					fprintf(f1, "工作   ");
					if ((clock() / CLOCKS_PER_SEC - door[i].StartSecTime) <= door[i].Servetime)
					{
						//printf("ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);
						fprintf(f1, "ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);
						//printf("RestLen=%d/%d   ", 0, 0);
						fprintf(f1, "RestLen=%d/%d   ", 0, 0);
						//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
						fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
					}
					else
					{
						//printf("ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime - door[i].Servetime, door[i].Servetime);
						fprintf(f1, "ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime - door[i].Servetime, door[i].Servetime);
						//printf("RestLen=%d/%d   ", 0, 0);
						fprintf(f1, "RestLen=%d/%d   ", 0, 0);
						//printf("WinListCustCount=%d\n", door[i].WinListCustCout - 1);
						fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout - 1);
					}

				}

				break;
			case CLOSE:
				//printf("关闭\n");
				fprintf(f1, "关闭\n");
				if (door[i].WinListCustCout!=0)
				{
					if ((clock() / CLOCKS_PER_SEC - door[i].StartSecTime) <= door[i].Servetime)
					{
						//printf("ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);
						fprintf(f1, "ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);
						//printf("RestLen=%d/%d   ", 0, 0);
						fprintf(f1, "RestLen=%d/%d   ", 0, 0);
						//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
						fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
					}
					else
					{
						//printf("ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime - door[i].Servetime, door[i].Servetime);
						fprintf(f1, "ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime - door[i].Servetime, door[i].Servetime);
						//printf("RestLen=%d/%d   ", 0, 0);
						fprintf(f1, "RestLen=%d/%d   ", 0, 0);
						//printf("WinListCustCount=%d\n", door[i].WinListCustCout - 1);
						fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout - 1);
					}
				}
				break;
			case SECEND:
				//printf("下班\n");
				fprintf(f1, "下班\n");
				if (door[i].WinListCustCout != 0)
				{
					if ((clock() / CLOCKS_PER_SEC - door[i].StartSecTime) <= door[i].Servetime)
					{
						//printf("ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);
						fprintf(f1, "ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);

						//printf("RestLen=%d/%d   ", 0, 0);
						fprintf(f1, "RestLen=%d/%d   ", 0, 0);
						//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
						fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
					}
					else
					{
						//printf("ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime - door[i].Servetime, door[i].Servetime);
						fprintf(f1, "ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime - door[i].Servetime, door[i].Servetime);

						//printf("RestLen=%d/%d   ", 0, 0);
						fprintf(f1, "RestLen=%d/%d   ", 0, 0);
						//printf("WinListCustCount=%d\n", door[i].WinListCustCout - 1);
						fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout - 1);
					}
				}
				break;
			case REST:
				//printf("休息   ");
				fprintf(f1, "休息   ");
				//printf("ServLen=%d/%d   ", 0, 0);
				fprintf(f1, "ServLen=%d/%d   ", 0, 0);
				//printf("RestLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartRestTime, door[i].Resttime);
				fprintf(f1, "RestLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartRestTime, door[i].Resttime);

				//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
				fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
				break;
			case WAITREST:
				//printf("等待休息   ");
				fprintf(f1, "等待休息   ");
				//printf("ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);
				fprintf(f1, "ServLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartSecTime, door[i].Servetime);

				//printf("RestLen=%d/%d   ", 0, 0);
				fprintf(f1, "RestLen=%d/%d   ", 0, 0);
				//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
				fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
				break;
			default:
				break;
			}
		}
		//printf("您可以随时输入以下命令：\n‘G’表示一个乘客申请进入“排队缓冲区”。\n‘RX’X是一个正整数，表示X号安检口请求暂停，X取值为1~8。\n‘CX’X是一个正整数，表示X号安检口请求恢复安检，X取值为1~8。\n‘Q’表示下班。\n");
		fprintf(f1, "您可以随时输入以下命令：\n‘G’表示一个乘客申请进入“排队缓冲区”。\n‘RX’X是一个正整数，表示X号安检口请求暂停，X取值为1~8。\n‘CX’X是一个正整数，表示X号安检口请求恢复安检，X取值为1~8。\n‘Q’表示下班。\n");
	}
	
}
