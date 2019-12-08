#ifndef CONH_H
#define CONH_H


#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#define WAITREST 0
#define FULL 1
#define REST 2
#define IDLE 3
#define CLOSE 4
#define SECEND 5
//乘客进入常量设置

//extern struct Security;//八个安检口*/
extern int Stopprint;
int custom[1010];
struct Security {
	int State;//状态
	int nextState;//下一状态
	int Servetime;//当前乘客安检时间
	int StartSecTime;//当前乘客安检开始时间
	int Restlen;//分配休息时间
	int Resttime;//已经休息时间
	int StartRestTime;//当前休息开始时间
	int WinListCustCout;//安检口队列人数
	int WaitForRest;//是否等待休息
	int StartWaitTime;//等待休息开始时间
	int Linecustnum;
}door[8];//八个安检口
extern int Offduty;//判断是否下班
extern int Line;//排队缓冲区乘客人数
extern FILE* f1;//用于输出到文件，文件output.txt的指针
extern int MaxCustSingleLine;  //单队列最大等待乘客数
extern int MaxLines;  //蛇形缓冲区最多由MaxLines个直队组成
extern int MaxSeqLen;    //最大允许等待长度
extern int MinTimeLen;     //一次安检最短时长，单位为秒
extern int MaxTimeLen;    //一次安检最大时长，单位为秒
extern int MinRestTimeLen;    //安检口一次暂停休息最短时长，单位为秒
extern int MaxRestTimeLen;   //安检口一次暂停休息最大时长，单位为秒
extern int custnum;


void drawbottom()
{
	setcolor(BLACK);
	//setfillcolor(EGERGB(0xFF, 0x0, 0x80));
	setfont(16,8,"宋体");
	setfontbkcolor(RED);
	xyprintf(10,20,"进入人员");
	xyprintf(10,40,"申请休息"); 
	xyprintf(10,60,"恢复工作"); 
	xyprintf(10,80,"下班指令"); 
}
void drawsec()
{
	setcolor(WHITE);
	setfillcolor(RED);
	setfont(16,8,"宋体");
	for(int i=0;i<8;i++)
	{
		bar(760,100+i*50,800,140+i*50);
	}
}
void drawman(int state,int num,int linenum,int custnum)
{
	
	setcolor(BLACK);
	setbkmode(TRANSPARENT);	
	PIMAGE picture;
     picture = newimage();
     getimage(picture, "picture.png",40,40);
     setfillcolor(EGERGB(0x0, 0x70, 0x0),picture);
//	setfontbkcolor(EGERGB(0x00, 0x00, 0x00));
	if(state==1)
	{
		
		putimage(510-num*40,60+linenum*40,picture);
		xyprintf(515-num*40,70+linenum*40,"%04d",custnum);
	}
	if(state==2)
	{
		putimage(760-40*num,50+linenum*50,picture);
		xyprintf(765-40*num,60+linenum*50,"%04d",custnum);
	}

}
void deleteman(int state,int num,int linenum)
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	if(num<=0||num>=9)
		{
			setcolor(EGERGB(0xFF, 0xFF, 0xFF));
			return;
		}
		
	if(state==1)
	{
		bar(510-num*40,60+linenum*40,550-num*40,100+linenum*40);
	}
	if(state==2)
	{
		bar(760-40*num,50+linenum*50,800-40*num,90+linenum*50);
	}
	setcolor(BLACK);
}
void drawstate(int num,int state)
{
	
	setcolor(WHITE);
	switch(state)
	{
		case FULL:
		xyprintf(760,50+num*50,"FULL");
		break;
		case WAITREST:
		xyprintf(760,50+num*50,"WAIT");
		break;
		case IDLE:
		if(door[num-1].WinListCustCout==0)
			xyprintf(760,50+num*50,"IDLE");
		else
			xyprintf(760,50+num*50,"WORK");
		break;
		case CLOSE:
		xyprintf(760,50+num*50,"CLOSE");
		break;
		case SECEND:
		xyprintf(760,50+num*50,"END");
		break;
		default:
		break;
	}
	
	
}
void drawsecnum(int num,int tim)
{
	setcolor(BLACK);
	xyprintf(760,70+50*num,"%d",tim);
}
void drawall(void)
{
	int i,j,k;
	cleardevice();
	PIMAGE beijing=newimage();
	getimage(beijing,"背景.jpg",0,0);
	putimage(0,0,beijing) ;
	setcolor(BLACK);
	setfillcolor(TRANSPARENT);
	setbkmode(TRANSPARENT);	
	drawbottom();
	drawsec();
	drawbottom();
	drawsec();
	for(i=1;i<=8;i++)
	{
		drawstate(i,door[i-1].State);
		if(door[i-1].State==REST)
		{
			drawsecnum(i,clock() / CLOCKS_PER_SEC - door[i-1].StartRestTime);
		}
		else if(door[i-1].WinListCustCout!=0)
		{
			
			for(j=door[i-1].WinListCustCout;j>0;j--)
			{

				 drawman(2,j,i,custnum);

			}
			drawsecnum(i,clock() / CLOCKS_PER_SEC - door[i-1].StartSecTime);
		}
		else{
			drawsecnum(i,0);
		}
	}
	for(k=Line;k>0;k--)
	{
		if(k<= MaxCustSingleLine)
			{
				if(k>0)
					{	
						drawman(1,k,1,custnum);
						custnum++;
					}
			}
		else if(k>0&&k%MaxCustSingleLine!=0)
			{
				drawman(1,k%MaxCustSingleLine,k/MaxCustSingleLine+1,custnum);
				custnum++;
			}
		else{
			drawman(1,MaxCustSingleLine,k/MaxCustSingleLine+1,custnum);
			custnum++;
		}
	}
}
#endif // !CONH_H