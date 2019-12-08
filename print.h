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
		//printf("����ʧ��\n");
		fprintf(f1, "����ʧ��\n");
		break;
	case 3:
		//printf("����ڡ�%d����ʼ����ȴ���Ϣ״̬\n", number);
		fprintf(f1, "����ڡ�%d����ʼ����ȴ���Ϣ״̬\n", number);
		break;
	case 4:
		//printf("����ڡ�%d����Ϣ����δ����׼\n", number);
		fprintf(f1, "����ڡ�%d����Ϣ����δ����׼\n", number);
		break;
	case 5:
		//printf("����ڡ�%d���ָ������ɹ�\n", number);
		fprintf(f1, "����ڡ�%d���ָ������ɹ�\n", number);
		break;
	case 6:
		//printf("�����°�״̬\n");
		fprintf(f1, "�����°�״̬\n");
	case 7:
		//printf("����ڡ�%d��������Ϣ״̬\n", number);
		fprintf(f1, "����ڡ�%d��������Ϣ״̬\n", number);
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
				//printf("����   ");
				fprintf(f1, "����   ");
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
					//printf("����   ");
					fprintf(f1, "����   ");
					//printf("ServLen=%d/%d   ", 0, 0);
					fprintf(f1, "ServLen=%d/%d   ", 0, 0);
					//printf("RestLen=%d/%d   ", 0, 0);
					fprintf(f1, "RestLen=%d/%d   ", 0, 0);
					//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
					fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
				}
				else
				{
					//printf("����   ");
					fprintf(f1, "����   ");
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
				//printf("�ر�\n");
				fprintf(f1, "�ر�\n");
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
				//printf("�°�\n");
				fprintf(f1, "�°�\n");
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
				//printf("��Ϣ   ");
				fprintf(f1, "��Ϣ   ");
				//printf("ServLen=%d/%d   ", 0, 0);
				fprintf(f1, "ServLen=%d/%d   ", 0, 0);
				//printf("RestLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartRestTime, door[i].Resttime);
				fprintf(f1, "RestLen=%d/%d   ", clock() / CLOCKS_PER_SEC - door[i].StartRestTime, door[i].Resttime);

				//printf("WinListCustCount=%d\n", door[i].WinListCustCout);
				fprintf(f1, "WinListCustCount=%d\n", door[i].WinListCustCout);
				break;
			case WAITREST:
				//printf("�ȴ���Ϣ   ");
				fprintf(f1, "�ȴ���Ϣ   ");
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
		//printf("��������ʱ�����������\n��G����ʾһ���˿�������롰�Ŷӻ���������\n��RX��X��һ������������ʾX�Ű����������ͣ��XȡֵΪ1~8��\n��CX��X��һ������������ʾX�Ű��������ָ����죬XȡֵΪ1~8��\n��Q����ʾ�°ࡣ\n");
		fprintf(f1, "��������ʱ�����������\n��G����ʾһ���˿�������롰�Ŷӻ���������\n��RX��X��һ������������ʾX�Ű����������ͣ��XȡֵΪ1~8��\n��CX��X��һ������������ʾX�Ű��������ָ����죬XȡֵΪ1~8��\n��Q����ʾ�°ࡣ\n");
	}
	
}
