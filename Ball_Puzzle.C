#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>

struct Ball
{
	int x;
	int y;
	int clr;
}sel_ball;

struct Jars
{
	int tot_Bls;
	struct Ball bls[5];

}Jrs[6];

struct gmdata
{
	struct Ball sel_bl;
	struct Jars jrs[6];
	int moves;
}gt;

struct hscore
{
	char p_name[50];
	int scr;
}hs;


// mouse handel function
union REGS in,out;
void status();
void position(int* ,int* ,int*);
void show();
void hide();
void setpos();

// main screen functions
void game_scr(struct Jars jrs[5],int sel_jar);
void main_scr();
void show_hs(struct hscore th);
void win_todo();
void save_score();
void save_scr_scn();
char *char_inp(int []);

int canFillBall(int Col,int Blcl[5]);
int isSelectabel(int jNo);
int isSwapable(int pre_sel,int new_sel);
void swap(int pre_sel,int new_sel);

int isCompalete();
// Some Structure


int SCORE=0;

void main()
{
	int x,y,m,i=0,j=0;
	int jarNo,Col,Tbl;
	int Blcl[5],rs,se;
	char qu;
	int sel_jar=0,pre_sel=-1,clb;
	FILE *f1;


	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}
	randomize();

START_SCR:
{
	hide();
	cleardevice();
	main_scr();
	show();
	setpos();
	position(&x,&y,&m);
	while(1)
	{
		show();
		position(&x,&y,&m);

		if(x>=350 && x<=400 && y>=0 && y<=40)
		{
			if(m==1)
			{
				setcolor(RED);
				settextstyle(7,0,3);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(20,150,380,300);
				outtextxy(200,225,"Do you want to exit (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					exit(0);
				}
				cleardevice();
				main_scr();
			}
		}
		if(x>=0 && x<=400 && y>60 && y<=160)
		{
			if(m==1)
			{
				goto RESUME_GAME;
			}
		}
		if(x>=0 && x<=400 && y>160 && y<=260)
		{
			if(m==1)
			{
				goto NEW_GAME;
			}
		}
		if(x>=0 && x<=400 && y>260 && y<=360)
		{
			if(m==1)
			{
				goto HEIGH_SCORE;
			}
		}
		if(x>=0 && x<=400 && y>360 && y<=460)
		{
			if(m==1)
			{
				setcolor(RED);
				settextstyle(7,0,3);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(20,150,380,300);
				outtextxy(200,225,"Do you want to exit (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					exit(0);
				}
				cleardevice();
				main_scr();
			}
		}

	}
};

RESUME_GAME:
{
	FILE *f2;
	int rs=0;
	hide();
	f2=fopen("BallGame\\Game_Dat.txt", "r");
	if(f2==NULL)
	{
		
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(10,150,390,300);
		settextstyle(1,0,2);
		outtextxy(200,200,"FILE NOT FIND TO READ DATA");
		show();
		getch();
		goto RESTART;
	}
	else
	{
		rs=fread(&gt,sizeof(gt),1,f2);
		fclose(f2);
		if(rs==0)
		{
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(10,150,400,300);
			settextstyle(1,0,2);
			outtextxy(200,200,"FILE NOT READ");
			hide();
			getch();
			goto RESTART;
		}
		else
		{
			sel_ball=gt.sel_bl;

			for(i=0;i<6;i++)
			{
				Jrs[i]=gt.jrs[i];
			}
			SCORE=gt.moves;
		}
	}
	goto START;


};

NEW_GAME:
{
	goto RESTART;
};

HEIGH_SCORE:
{
	f1=fopen("BallGame\\SCORE.txt", "r");
	if(f1==NULL)
	{
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(10,150,400,300);
		settextstyle(7,0,2);
		outtextxy(200,200,"SCORE FILE NOT FOUND");
		getch();
	}
	else
	{
		fread(&hs,sizeof(hs),1,f1);
		fclose(f1);
		show_hs(hs);
	}
	goto START_SCR;
};

RESTART:
{
	SCORE=0;
	sel_ball.x=0;
	sel_ball.y=0;
	sel_ball.clr=6;
	sel_jar=0;
	pre_sel=-1;
	
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			Blcl[i]=0;
		}
		Jrs[i].tot_Bls=0;
	}
	Jrs[i].tot_Bls=0;

	i=0;
	while(i<25)
	{
		jarNo=random(6)+1;
		Col=random(5)+1;
		if(canFillBall(Col,Blcl)==1)
		{
			if(jarNo==1)
			{
				Tbl=Jrs[jarNo-1].tot_Bls;

				if(Tbl<5)
				{
					Jrs[jarNo-1].bls[Tbl].x=66;
					Jrs[jarNo-1].bls[Tbl].y=215-(Tbl*30);
					Jrs[jarNo-1].bls[Tbl].clr=Col;
					Jrs[jarNo-1].tot_Bls++;
					Blcl[Col-1]++;
					i++;
				}
			}
			else if(jarNo==2)
			{
				Tbl=Jrs[jarNo-1].tot_Bls;
				
				if(Tbl<5)
				{
					Jrs[jarNo-1].bls[Tbl].x=199;
					Jrs[jarNo-1].bls[Tbl].y=215-(Tbl*30);
					Jrs[jarNo-1].bls[Tbl].clr=Col;
					Jrs[jarNo-1].tot_Bls++;
					Blcl[Col-1]++;
					i++;
				}
			}
			else if(jarNo==3)
			{
				Tbl=Jrs[jarNo-1].tot_Bls;
				
				if(Tbl<5)
				{
					Jrs[jarNo-1].bls[Tbl].x=332;
					Jrs[jarNo-1].bls[Tbl].y=215-(Tbl*30);
					Jrs[jarNo-1].bls[Tbl].clr=Col;
					Jrs[jarNo-1].tot_Bls++;
					Blcl[Col-1]++;
					i++;
				}
			}
			else if(jarNo==4)
			{
				Tbl=Jrs[jarNo-1].tot_Bls;
				
				if(Tbl<5)
				{
					Jrs[jarNo-1].bls[Tbl].x=66;
					Jrs[jarNo-1].bls[Tbl].y=415-(Tbl*30);
					Jrs[jarNo-1].bls[Tbl].clr=Col;
					Jrs[jarNo-1].tot_Bls++;
					Blcl[Col-1]++;
					i++;
				}
			}
			else if(jarNo==5)
			{
				Tbl=Jrs[jarNo-1].tot_Bls;
				
				if(Tbl<5)
				{
					Jrs[jarNo-1].bls[Tbl].x=199;
					Jrs[jarNo-1].bls[Tbl].y=415-(Tbl*30);
					Jrs[jarNo-1].bls[Tbl].clr=Col;
					Jrs[jarNo-1].tot_Bls++;
					Blcl[Col-1]++;
					i++;
				}
			}
			else if(jarNo==6)
			{
				Tbl=Jrs[jarNo-1].tot_Bls;
				
				if(Tbl<5)
				{
					Jrs[jarNo-1].bls[Tbl].x=332;
					Jrs[jarNo-1].bls[Tbl].y=415-(Tbl*30);
					Jrs[jarNo-1].bls[Tbl].clr=Col;
					Jrs[jarNo-1].tot_Bls++;
					Blcl[Col-1]++;
					i++;
				}
			}
			else
			{
				;
			}

		}
		else
		{
			;
		}
	}

};

START:
{
	hide();
	cleardevice();
	game_scr(Jrs,sel_jar);
	show();
	while(1)
	{
		show();
		position(&x,&y,&m);
		if(x>=350 && x<=400 && y>=0 && y<=40)
		{
			if(m==1)
			{
				setcolor(RED);
				settextstyle(7,0,3);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(20,150,380,300);
				outtextxy(200,225,"Do you want to exit (Y/N)?");
				qu=getch();
				if(qu=='y' || qu=='Y')
				{
					se=1;
					goto SAVE_EXIT;
//					exit(0);
				}
				hide();
				cleardevice();
				game_scr(Jrs,sel_jar);
				show();
			}
		}
		if(x>=0 && x<=100 && y>=40 && y<=60)
		{
			if(m==1)
			{
				goto TODO_COMM;
			}
		}
		
		
		// 1st jars
		if(x>=0 && x<=133 && y>=61 && y<=260)
		{
			if(m==1)
			{
				if(pre_sel>=0)
				{
					if(isSwapable(pre_sel,0)==1)
					{
						swap(pre_sel,0);
						sel_jar=0;
						pre_sel=-1;
						SCORE++;
						
						if(isCompalete()==1)
						{
							save_score();
							goto RESTART;
						}
					}
					
				}
				else
				{
					if(isSelectabel(0)==1)
					{
						sel_jar=1;
						pre_sel=sel_jar-1;
						clb=Jrs[pre_sel].bls[Jrs[pre_sel].tot_Bls-1].clr;
						sel_ball.clr=clb;
					}
					
				}
				delay(100);
				hide();
				cleardevice();
				game_scr(Jrs,sel_jar);
				show();
				position(&x,&y,&m);
			}
		}
		// 2nd jars
		if(x>=134 && x<=266 && y>=61 && y<=260)
		{
			if(m==1)
			{
				if(pre_sel>=0)
				{
					if(isSwapable(pre_sel,1)==1)
					{
						swap(pre_sel,1);
						sel_jar=0;
						pre_sel=-1;
						SCORE++;
						if(isCompalete()==1)
						{
							save_score();
							goto RESTART;
						}
					}
					
				}
				else
				{
					if(isSelectabel(1)==1)
					{
						sel_jar=2;
						pre_sel=sel_jar-1;
						clb=Jrs[pre_sel].bls[Jrs[pre_sel].tot_Bls-1].clr;
						sel_ball.clr=clb;
					}
					
				}
				delay(100);
				hide();
				cleardevice();
				game_scr(Jrs,sel_jar);
				show();
				position(&x,&y,&m);
			}
		}
		// 3rd jars
		if(x>=267 && x<=400 && y>=61 && y<=260)
		{
			if(m==1)
			{
				if(pre_sel>=0)
				{
					if(isSwapable(pre_sel,2)==1)
					{
						swap(pre_sel,2);
						sel_jar=0;
						pre_sel=-1;
						SCORE++;
						if(isCompalete()==1)
						{
							save_score();
							goto RESTART;
						}
					}
					
				}
				else
				{
					if(isSelectabel(2)==1)
					{
						sel_jar=3;
						pre_sel=sel_jar-1;
						clb=Jrs[pre_sel].bls[Jrs[pre_sel].tot_Bls-1].clr;
						sel_ball.clr=clb;
					}
					
				
				}
				delay(100);
				hide();
				cleardevice();
				game_scr(Jrs,sel_jar);
				show();
				position(&x,&y,&m);
			}
		}
		// 4th jars
		if(x>=0 && x<=133 && y>=261 && y<=460)
		{
			if(m==1)
			{
				if(pre_sel>=0)
				{
					if(isSwapable(pre_sel,3)==1)
					{
						swap(pre_sel,3);
						sel_jar=0;
						pre_sel=-1;
						SCORE++;
						if(isCompalete()==1)
						{
							save_score();
							goto RESTART;
						}
					}
					
				}
				else
				{
					if(isSelectabel(3)==1)
					{
						sel_jar=4;
						pre_sel=sel_jar-1;
						clb=Jrs[pre_sel].bls[Jrs[pre_sel].tot_Bls-1].clr;
						sel_ball.clr=clb;
						
					}
				
				}
				delay(100);
				hide();
				cleardevice();
				game_scr(Jrs,sel_jar);
				show();
				position(&x,&y,&m);
			}
		}
		// 5th jars
		if(x>=134 && x<=266 && y>=261 && y<=460)
		{
			if(m==1)
			{
				if(pre_sel>=0)
				{
					if(isSwapable(pre_sel,4)==1)
					{
						swap(pre_sel,4);
						sel_jar=0;
						pre_sel=-1;
						SCORE++;
						if(isCompalete()==1)
						{
							save_score();
							goto RESTART;
						}
					}
					
				}
				else
				{
					if(isSelectabel(4)==1)
					{
						sel_jar=5;
						pre_sel=sel_jar-1;
						clb=Jrs[pre_sel].bls[Jrs[pre_sel].tot_Bls-1].clr;
						sel_ball.clr=clb;
					}
					
				
				}
				delay(100);
				hide();
				cleardevice();
				game_scr(Jrs,sel_jar);
				show();
				position(&x,&y,&m);
			}
		}
		// 6th jars
		if(x>=267 && x<=400 && y>=261 && y<=460)
		{
			if(m==1)
			{
				if(pre_sel>=0)
				{
					if(isSwapable(pre_sel,5)==1)
					{
						swap(pre_sel,5);
						sel_jar=0;
						pre_sel=-1;
						SCORE++;
						if(isCompalete()==1)
						{
							save_score();
							goto RESTART;
						}
					}
					
				}
				else
				{
					if(isSelectabel(5)==1)
					{
						sel_jar=6;
						pre_sel=sel_jar-1;
						clb=Jrs[pre_sel].bls[Jrs[pre_sel].tot_Bls-1].clr;
						sel_ball.clr=clb;
					}
					
				
				}
				delay(100);
				hide();
				cleardevice();
				game_scr(Jrs,sel_jar);
				show();
				position(&x,&y,&m);
			}
		}
		
		
	}
};

SAVE_EXIT:
{
	struct gmdata gd;
	f1=fopen("BallGame\\Game_Dat.txt", "w+");
	if(f1==NULL)
	{
		hide();
		cleardevice();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(10,150,500,300);
		settextstyle(1,0,2);
		outtextxy(245,225,"FILE NOT FIND TO SAVE DATA");
		show();
		getch();


	}
	else
	{
		for(i=0;i<6;i++)
		{
			gd.jrs[i].tot_Bls=Jrs[i].tot_Bls;
			for(j=0;j<Jrs[i].tot_Bls;j++)
			{

				gd.jrs[i].bls[j].x=Jrs[i].bls[j].x;
				gd.jrs[i].bls[j].y=Jrs[i].bls[j].y;
				gd.jrs[i].bls[j].clr=Jrs[i].bls[j].clr;
			}
			
		}
		gd.sel_bl.x=sel_ball.x;
		gd.sel_bl.y=sel_ball.y;
		gd.sel_bl.clr=sel_ball.clr;
		gd.moves=SCORE;
		rs=fwrite(&gd,sizeof(gd),1,f1);
		if(rs==0)
		{
			hide();
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(10,150,500,300);
			settextstyle(7,0,3);
			outtextxy(150,225,"NO DATA WRITTEN TO FILE ");
			show();
			getch();

		}
		else
		{
			hide();
			cleardevice();
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(10,150,500,300);
			settextstyle(7,0,3);
			outtextxy(200,225,"DATA SAVE SUCCESSFULLY!!");
			show();
			getch();
		}
	}
	fclose(f1);
	if(se==1)
	{
		exit(0);
	}
	else
	{
		goto START_SCR;
	}
		
};

TODO_COMM:
{
	hide();
	cleardevice();
	game_scr(Jrs,sel_jar);
	win_todo();
	show();
	setpos();
	delay(100);
	while(1)
	{
		position(&x,&y,&m);
		if(x>=0 && x<=180 && y>60 && y<=100)
		{
			if(m==1)
			{
				goto RESTART;
			}
		}
		else if(x>=0 && x<=180 && y>100 && y<=140)
		{
			if(m==1)
			{
				se=1;
				goto SAVE_EXIT;
			}
		}
		else if(x>=0 && x<=180 && y>140 && y<=180)
		{
			if(m==1)
			{
				se=0;
				
				goto SAVE_EXIT;
			}
		}
		else
		{
			if(m==1)
			{
				goto START;
			}
		}
	}
};

}

int isCompalete()
{
	int i,j;
	int res=1;
	for(i=0;i<5;i++)
	{
		if(Jrs[i].tot_Bls<5)
		{
			return 0;
		}
		else
		{
			for(j=0;j<5;j++)
			{
				if(Jrs[i].bls[j].clr!=i+1)
				{
					return 0;
				}
			}
		}
	}
	return res;
}

int isSelectabel(int jNo)
{
	if(Jrs[jNo].tot_Bls>0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
		
}
int isSwapable(int pre_sel,int new_sel)
{
	int res=0;
	if(pre_sel!=new_sel)
	{
		if(Jrs[new_sel].tot_Bls<5)
		{
			res=1;
		}
	}
	return res;
}

void swap(int pre_sel,int new_sel)
{
	int ptb,ntb;
	ntb=Jrs[new_sel].tot_Bls;
	ptb=Jrs[pre_sel].tot_Bls-1;
	
	if(new_sel==0)
	{
		Jrs[new_sel].bls[ntb].x=66;
		Jrs[new_sel].bls[ntb].y=215-(ntb*30);
		Jrs[new_sel].bls[ntb].clr=sel_ball.clr;

		Jrs[pre_sel].bls[ptb].x=0;
		Jrs[pre_sel].bls[ptb].y=0;
		Jrs[pre_sel].bls[ptb].clr=0;

		Jrs[pre_sel].tot_Bls--;
		Jrs[new_sel].tot_Bls++;
	}
	else if(new_sel==1)
	{
		Jrs[new_sel].bls[ntb].x=199;
		Jrs[new_sel].bls[ntb].y=215-(ntb*30);
		Jrs[new_sel].bls[ntb].clr=sel_ball.clr;

		Jrs[pre_sel].bls[ptb].x=0;
		Jrs[pre_sel].bls[ptb].y=0;
		Jrs[pre_sel].bls[ptb].clr=0;

		Jrs[pre_sel].tot_Bls--;
		Jrs[new_sel].tot_Bls++;
	}
	else if(new_sel==2)
	{
		Jrs[new_sel].bls[ntb].x=332;
		Jrs[new_sel].bls[ntb].y=215-(ntb*30);
		Jrs[new_sel].bls[ntb].clr=sel_ball.clr;

		Jrs[pre_sel].bls[ptb].x=0;
		Jrs[pre_sel].bls[ptb].y=0;
		Jrs[pre_sel].bls[ptb].clr=0;

		Jrs[pre_sel].tot_Bls--;
		Jrs[new_sel].tot_Bls++;
	}
	else if(new_sel==3)
	{
		Jrs[new_sel].bls[ntb].x=66;
		Jrs[new_sel].bls[ntb].y=415-(ntb*30);
		Jrs[new_sel].bls[ntb].clr=sel_ball.clr;

		Jrs[pre_sel].bls[ptb].x=0;
		Jrs[pre_sel].bls[ptb].y=0;
		Jrs[pre_sel].bls[ptb].clr=0;

		Jrs[pre_sel].tot_Bls--;
		Jrs[new_sel].tot_Bls++;
	}
	else if(new_sel==4)
	{
		Jrs[new_sel].bls[ntb].x=199;
		Jrs[new_sel].bls[ntb].y=415-(ntb*30);
		Jrs[new_sel].bls[ntb].clr=sel_ball.clr;

		Jrs[pre_sel].bls[ptb].x=0;
		Jrs[pre_sel].bls[ptb].y=0;
		Jrs[pre_sel].bls[ptb].clr=0;

		Jrs[pre_sel].tot_Bls--;
		Jrs[new_sel].tot_Bls++;
	}
	else if(new_sel==5)
	{
		Jrs[new_sel].bls[ntb].x=332;
		Jrs[new_sel].bls[ntb].y=415-(ntb*30);
		Jrs[new_sel].bls[ntb].clr=sel_ball.clr;

		Jrs[pre_sel].bls[ptb].x=0;
		Jrs[pre_sel].bls[ptb].y=0;
		Jrs[pre_sel].bls[ptb].clr=0;

		Jrs[pre_sel].tot_Bls--;
		Jrs[new_sel].tot_Bls++;
	}
	else
	{
		;
	}
}

void main_scr()
{
	setbkcolor(CYAN);
	setfillstyle(SOLID_FILL,9);
	bar(0,0,400,460);

	//title bar
	setcolor(getmaxcolor());
	settextjustify(1,1);
	settextstyle(7,0,4);
	setfillstyle(SOLID_FILL,8);
	bar(0,0,400,40);
	outtextxy(200,15,"BALL SORT GAME");
	setfillstyle(SOLID_FILL,RED);
	settextstyle(0,0,4);
	bar(350,0,400,40);
	setcolor(GREEN);
	outtextxy(375,20,"X");
	//main menu bar

	setfillstyle(SOLID_FILL,WHITE);
	settextstyle(7,0,3);
	bar(0,40,400,60);

	// menus list
	setcolor(RED);
	line(0,160,400,160);
	line(0,260,400,260);
	line(0,360,400,360);
	setcolor(10);
	settextstyle(7,0,5);
	outtextxy(200,110,"RESUME GAME");
	outtextxy(200,210,"NEW GAME");
	outtextxy(200,310,"HIGH SCORE");
	outtextxy(200,410,"EXIT");

}

void game_scr(struct Jars jrs[5],int sel_jar)
{
	char trb[10];
	int i=0,j=0;

	setbkcolor(CYAN);
	setfillstyle(SOLID_FILL,9);
	bar(0,0,400,460);

	//title bar
	setcolor(getmaxcolor());
	settextjustify(1,1);
	settextstyle(7,0,4);
	setfillstyle(SOLID_FILL,8);
	bar(0,0,400,40);
	outtextxy(200,15,"BALL SORT GAME");
	setfillstyle(SOLID_FILL,RED);
	settextstyle(0,0,4);
	bar(350,0,400,40);
	setcolor(GREEN);
	outtextxy(375,20,"X");
	//main menu bar

	setfillstyle(SOLID_FILL,WHITE);
	settextstyle(7,0,3);
	bar(0,40,400,60);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(0,40,100,60);
	setcolor(BLUE);
	outtextxy(50,45,"MENU");

	setcolor(YELLOW);
	line(133,60,133,460);
	line(266,60,266,460);
	line(0,260,400,260);

	// 1st box
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	bar(16,230,116,260);
	bar(61,70,71,230);

	// 2nd box
	setcolor(2);
	setfillstyle(SOLID_FILL,2);
	bar(149,230,249,260);
	bar(194,70,204,230);

	// 3rd box
	setcolor(3);
	setfillstyle(SOLID_FILL,3);
	bar(282,230,382,260);
	bar(327,70,337,230);

	// 4th box
	setcolor(4);
	setfillstyle(SOLID_FILL,4);
	bar(16,430,116,460);
	bar(61,270,71,430);

	// 5th box
	setcolor(5);
	setfillstyle(SOLID_FILL,5);
	bar(149,430,249,460);
	bar(194,270,204,430);

	// 6th box
	setcolor(6);
	setfillstyle(SOLID_FILL,6);
	bar(282,430,382,460);
	bar(327,270,337,430);


	for(i=0;i<6;i++)
	{
		for(j=0;j<jrs[i].tot_Bls;j++)
		{
			int cl,xp,yp;
			cl=jrs[i].bls[j].clr;
			xp=jrs[i].bls[j].x;
			yp=jrs[i].bls[j].y;
			setcolor(cl);
			setfillstyle(SOLID_FILL,cl);
			fillellipse(xp,yp,15,15);
		}

	}

	setfillstyle(SOLID_FILL,YELLOW);
	settextstyle(7,0,3);
	bar(405,0,635,460);
	setcolor(RED);
	outtextxy(520,30,"TOTAL MOVES :");
	sprintf(trb,"%d",SCORE);
	outtextxy(520,60,trb);
	
	outtextxy(520,150,"SELECTED BOLL :");
	if(sel_jar>0)
	{
		outtextxy(520,180,"From Box No.:");
		sprintf(trb,"%d",sel_jar);
		outtextxy(520,210,trb);
		outtextxy(520,260,"Ball : ");
		setfillstyle(SOLID_FILL,15);
		fillellipse(520,300,20,20);
		setfillstyle(SOLID_FILL,sel_ball.clr);
		fillellipse(520,300,15,15);
	}
	else
	{
		outtextxy(520,180,"From Box No.:");
		outtextxy(520,210,"No boll selected");
		setfillstyle(SOLID_FILL,15);
		outtextxy(520,260,"Ball : ");
		fillellipse(520,300,20,20);

	}
	setcolor(GREEN);

}

int canFillBall(int Col,int Blcl[5])
{
	int res=0;
	if(Blcl[Col-1]<5)
	{
		res=1;
	}
	return res;
}

void show_hs(struct hscore th)
{
	char tm[10],tmt[10],p_n[50];
	hide();
	cleardevice();
	setbkcolor(CYAN);
	setcolor(GREEN);
	settextjustify(1,1);
	setfillstyle(SOLID_FILL,BROWN);
	settextstyle(7,0,3);
	bar(100,20,500,70);
	outtextxy(300,30,"HIGH SCORE");
	settextjustify(0,2);
	setfillstyle(SOLID_FILL,BLUE);
	settextstyle(7,0,3);
	bar(100,70,500,310);
	outtextxy(110,70,"PLAYER NAME : ");
	strcpy(p_n,th.p_name);
	outtextxy(110,110,p_n);
	sprintf(tmt,"%d",th.scr);
	outtextxy(110,150,"TOTAL BALL MOVED : ");
	outtextxy(110,190,tmt);
	settextjustify(1,1);
	show();
	getch();
}

void win_todo()
{
	setfillstyle(SOLID_FILL,WHITE);
	bar(0,60,180,180);
	setcolor(BLUE);
	settextstyle(1,0,2);
	line(0,100,180,100);
	line(0,140,180,140);

	outtextxy(90,80,"RESTART");
	outtextxy(90,120,"SAVE & EXIT");
	outtextxy(90,160,"MAIN MENU");
}

void save_score()
{
	struct hscore ohs;
	FILE *f1,*f2;
	int cr[5],l;
	if((f1=fopen("BallGame\\SCORE.txt","r+"))==NULL)
	{
		l=0;
	}
	else
	{
		fread(&ohs,sizeof(ohs),1,f1);
		if(ohs.scr>SCORE)
		{
			l=0;
		}
		else
		{
			l=1;
		}
	}
	fclose(f1);
	if(l==0)
	{
		if((f1=fopen("BallGame\\SCORE.txt","w+"))==NULL)
		{
			hide();
			cleardevice();
			setbkcolor(CYAN);
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			settextstyle(7,0,3);
			outtextxy(300,200,"FILE NOT FIND TO WRITE DATA");
			show();
			getch();

		}
		else
		{
			cr[0]=100;
			cr[1]=200;
			cr[2]=500;
			cr[3]=300;
			cr[4]=0;
			strcpy(hs.p_name,char_inp(cr));
			hs.scr=SCORE;
			fwrite(&hs,sizeof(hs),1,f1);
			fclose(f1);
			hide();
			cleardevice();
			setbkcolor(CYAN);
			setcolor(RED);
			setfillstyle(SOLID_FILL,YELLOW);
			bar(100,150,500,300);
			settextstyle(7,0,3);
			outtextxy(200,200,"SCORE SAVE ");
			show();
			getch();
			settextjustify(1,1);
		}
	}
	else
	{
		hide();
		cleardevice();
		setbkcolor(CYAN);
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		bar(100,150,500,300);
		settextstyle(7,0,3);
		outtextxy(300,200,"You Score Less than high Score.");
		show();
		getch();
	}
}

void save_scr_scn()
{
		cleardevice();
		settextjustify(0,2);
		setbkcolor(CYAN);
		setcolor(GREEN);
		setfillstyle(SOLID_FILL,BLUE);
		settextstyle(7,0,3);
		bar(100,100,500,300);
		outtextxy(110,130,"ENTER THE PLAYER NAME : ");
		bar(100,200,500,300);

}

char *char_inp(int cor[5])
{
	int h,q,l,i,t,cr;
	char inp[50];
	char chp[50],*endptr;
	char ch='0';
	char ap[50]="",bp[50],cp[50],dp[50];
	h=cor[0]+10;
	i=cor[1]+10;
	settextstyle(1,HORIZ_DIR,2);

	while(ch!='\r')
	{

		save_scr_scn();
		setcolor(YELLOW);
		setfillstyle(1,RED);
		h=cor[0]+10;
		i=cor[1]+10;
		settextstyle(1,HORIZ_DIR,2);
		bar(cor[0],cor[1],cor[2],cor[3]);
		outtextxy(h,i,ap);
		ch=getch();

			if(ch=='\b')
			{
				strcpy(bp,ap);
				strrev(bp);
				q=strlen(bp)-1;
				i=0;
				while(q>0)
				{
					cp[i]=bp[q];
					i++;
					q--;
				}
				cp[i]='\0';
				strcpy(ap,cp);
			}

			if(ch=='a' || ch=='b'|| ch=='c'|| ch=='d' || ch=='e' || ch=='f'|| ch=='g' || ch=='h'|| ch=='i'|| ch=='j' || ch=='k' || ch=='l' || ch=='m' || ch=='n'|| ch=='o'|| ch=='p' || ch=='q' || ch=='r'|| ch=='s' || ch=='t'|| ch=='u'|| ch=='v' || ch=='w' || ch=='x' || ch=='y' || ch=='z')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
			}
			if(ch==' ' || ch=='A' || ch=='B'|| ch=='C'|| ch=='D' || ch=='E' || ch=='F'|| ch=='G' || ch=='H'|| ch=='I'|| ch=='J' || ch=='K' || ch=='L' || ch=='M' || ch=='N'|| ch=='O'|| ch=='P' || ch=='Q' || ch=='R'|| ch=='S' || ch=='T'|| ch=='U'|| ch=='V' || ch=='W' || ch=='X' || ch=='Y' || ch=='Z')
			{
				sprintf(chp,"%c",ch);
				strcat(ap,chp);
			}


	 }
	 strcpy(dp,ap);
	 return(dp);
}

void status()
{
	in.x.ax=0;
	int86(51,&in,&out);
}
void hide()
{
	in.x.ax=2;
	int86(51,&in,&out);
}
void show()
{
	in.x.ax=1;
	int86(51,&in,&out);
}
void setpos()
{
	in.x.ax=4;
	in.x.cx=0;
	in.x.dx=0;
	in.x.bx=0;
	int86(0x33,&in,&out);
}
void position(int *x,int *y,int *m)
{
	in.x.ax=3;
	int86(0x33,&in,&out);
	*m=out.x.bx;
	*x=out.x.cx;
	*y=out.x.dx;
}



