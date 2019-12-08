#ifndef INPUT_H
#define INPUT_H
#include "conh.h"
extern int ifRest(int number);
extern int customWait();
extern void printstate(int x,int y);
int whichrest(int num1, int num2) {
	if (door[num1].Restlen==door[num2].Restlen)
	{
		if (num1 > num2)
			return num2;
		else
		{
			return num1;
		}
	}
	else if (door[num1].Restlen > door[num2].Restlen)
	{
		return num2;
	}
	else
	{
		return num1;
	}
}
void Input()
{
	char ch;
	int number;
	int i;
	int flag=0;
	int cprt;
	int waiting=0;
	int wflag=0;
	int xflag=0;
	int release=0;
	mouse_msg msg = {0};
	for ( ; is_run(); delay_fps(12))
	{
		//????????????????????????????????????
		if (mousemsg())
		{
			msg = getmouse();
		}
		else
			continue;
		for(i=1;i<=4;i++)
		{
			if(msg.x>=10&&msg.x<=64&&msg.y>=(20*i)&&msg.y<=(40*i)&&(int)msg.is_up()==1)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			switch(i)
			{
				case 1:
					if (customWait())
					{
						printstate(1, 0);
					}
					else
					{
						printstate(2, 0);
					}	
					waiting=0;
				 	release=0;
					break;
				case 2: 
					waiting=1;
					release=0;
					break;
				case 3:
					release=1;
					waiting=0;
					break;
				case 4:
					waiting=0;
				 	release=0;
					Offduty = 1;
					for (i = 0; i < 8; i++)
					{
						door[i].nextState = SECEND;
						printstate(6,0);
					}
				default:
					break;
			}
			flag=0;
		}
		if(waiting==1||release==1)
		{
			for(i=1;i<=8;i++)
			{
				if(msg.x>=760&&msg.x<=800&&msg.y>=(50+50*i)&&msg.y<=(90+50*i)&&(int)msg.is_up()==1)
				{
					wflag=1;
					break;
				}
			}
			if(wflag==1&&waiting==1)
			{
				number=i;
				if (ifRest(number-1))
			{
				door[number-1].StartWaitTime = clock() / CLOCKS_PER_SEC;
				for (i = 0; i < 8; i++)
				{
					if (door[i].WaitForRest == 1)
					{
						xflag = 1;
						break;
					}
				}
				if (xflag == 1)
				{
					door[whichrest(i, number - 1)].nextState = WAITREST;
					printstate(3, whichrest(i, number - 1) + 1);
					door[i].WaitForRest = 0;
					door[number - 1].WaitForRest = 0;
					door[number - 1].StartWaitTime = 0;
					door[i].StartWaitTime = 0;
				}
				else {
					door[number - 1].WaitForRest = 1;
				}
			}
			else
			{
				printstate(4, number-1);
			}
			break;
			}
			else
			{
				if (door[number - 1].State == REST|| door[number - 1].State == WAITREST)
				{
					door[number - 1].nextState = IDLE;
					printstate(5, number);
				}
				else
				{
					printstate(7, number);
				}
				break;
			}
		}
	//	delay(1000);
	}

	/*while (1)
	{
		int flag = 0;
		ch = getchar();
		fprintf(f1, "%c\n", ch);
		switch (ch)
		{
		case 'g':
		case 'G':
			if (customWait())
			{
				printstate(1, 0);
			}
			else
			{
				printstate(2, 0);
			}
			break;
		case 'r':
		case 'R':
			Stopprint = 1;
			scanf("%d", &number);
			fprintf(f1, "%d\n", number);
			Stopprint = 0;
			if (ifRest(number-1))
			{
				door[number-1].StartWaitTime = clock() / CLOCKS_PER_SEC;
				for (i = 0; i < 8; i++)
				{
					if (door[i].WaitForRest == 1)
					{
						flag = 1;
						break;
					}
				}
				if (flag == 1)
				{
					door[whichrest(i, number - 1)].nextState = WAITREST;
					printstate(3, whichrest(i, number - 1) + 1);
					door[i].WaitForRest = 0;
					door[number - 1].WaitForRest = 0;
					door[number - 1].StartWaitTime = 0;
					door[i].StartWaitTime = 0;
				}
				else {
					door[number - 1].WaitForRest = 1;
				}
			}
			else
			{
				printstate(4, number-1);
			}
			break;
		case 'c':
		case 'C':
			Stopprint = 1;
			scanf("%d", &number);
			fprintf(f1, "%d\n", number);
			Stopprint = 0;
			if (door[number - 1].State == REST|| door[number - 1].State == WAITREST)
			{
				door[number - 1].State = IDLE;
				printstate(5, number);

			}
			else
			{
				printstate(7, number);
			}
			break;
		case 'q':
		case 'Q':
			Offduty = 1;
			for (i = 0; i < 8; i++)
			{
				door[i].nextState = SECEND;
			}
			printstate(6, 0);
			break;
		case '\n':
			break;
		default:
			printf("???????\n");
			break;
		}
	}*/
}
#endif // !INPUT_H