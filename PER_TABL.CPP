#include<conio.h>
#include<fstream.h>
#include<process.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<dos.h>
#define x1 40
#define x2 60
#define E_COUNT 110

class Element
{
   protected:

      char Name[20],Symbol[3],Category[15];
      int Group,Period,At_no,E_config[19],O_state[8];
      float M_point,B_point,A_mass;
      char sub_shell[19][3];

	  void get_E_config()
	  {
		  cout<<"Enter Electronic Coniguration (enter zero to terminate) "<<endl;
		  for(int i=0;i<19;++i)
		  {
			  int temp;
			  cout<<sub_shell[i];
			  //puts(sub_shell[i]);
			  cin>>temp;
			  if(temp==0)
				  break;
			  else
				  E_config[i]=temp;
		  }
	  }

	  void getO_states()
	  {
		  cout<<"Enter Oxidation States(with sign)(Enter 0 to terminate)"<<endl;
		  int temp;
		  for(int i=0;i<8;++i)
		  {
			  cin>>temp;
			  if(temp==0)
				  break;
			  else
				  O_state[i]=temp;
		  }
	  }
      void put_E_config()
      {
		cout<<"Electronic Configuration : ";
		for(int i=0;i<19;++i)
		{
			if (E_config[i]==0)
				break;
			cout<<sub_shell[i]<<E_config[i]<<" ";
		}
		cout<<endl;
      }
      void put_O_state()
      {
		cout<<"Oxidation States : ";
		for(int i=0;i<8;++i)
		{
			cout<<O_state[i]<<",";
			if(O_state[i]==0)
				break;
		}
		cout<<endl;
      }
   public:
      Element()
      {
		  for(int i=0;i<20;++i)
			 Name[i]=NULL;
		  for(i=0;i<3;++i)
			  Symbol[0]=NULL;
		  for(i=0;i<15;++i)
			  Category[0]=NULL;
		  char shell[19][3]={"1s","2s","2p","3s","3p","4s","3d","4p","5s","4d","5p","6s","4f","5d","6p","7s","5f","6d","7p"};
		  for(i=0;i<19;++i)
		  {
			for(int j=0;j<3;++j)
				sub_shell[i][j]=shell[i][j];
		  }
		  Group=Period=At_no=M_point=B_point=A_mass=0;
		  for(i=0;i<8;++i)
			  O_state[i]=0;
		  for(i=0;i<19;++i)
			  E_config[i]=0;
      }
      void get_E_info()
      {
		 cout<<"Enter Atomic No "<<endl;
		 cin>>At_no;
		 cout<<"Enter Atomic Mass"<<endl;
		 cin>>A_mass;
		 cout<<"Enter Element Name "<<endl;
		 cin>>Name;
		 cout<<"Enter Element Symbol "<<endl;
		 cin>>Symbol;
		 cout<<"Enter Catergory "<<endl;
		 gets(Category);
		 cout<<"Enter Group "<<endl;
		 cin>>Group;
		 cout<<"Enter Period "<<endl;
		 cin>>Period;
		 get_E_config();
		 cout<<"Enter Melting Point "<<endl;
		 cin>>M_point;
		 cout<<"Enter Boiling Point "<<endl;
		 cin>>B_point;
		 getO_states();
      }
      void disp_elements()
      {
		 cout<<"Name : "<<Name<<endl;
		 cout<<"Symbol : "<<Symbol<<endl;
		 cout<<"Category : ";
		 puts(Category);
		 cout<<"Group : "<<Group<<endl;
		 cout<<"Period : "<<Period<<endl;
		 cout<<"Atomic Number : "<<At_no<<endl;
		 put_E_config();
		 cout<<"Melting Point : "<<M_point<<endl;
		 cout<<"Boiling Point : "<<B_point<<endl;
		 cout<<"Atomic Mass : "<<A_mass<<endl;
		 put_O_state();
      }
      int get_atno()
      {
		return At_no;
      }

};

class show_in_table:public Element
{
	int xpos,ypos,catcol;
	void drawEconfig()
	{
		char shell[19][3]={"1s","2s","2p","3s","3p","4s","3d","4p","5s","4d","5p","6s","4f","5d","6p","7s","5f","6d","7p"};
		int xp=10;
		settextstyle(SMALL_FONT,0,4);
		setcolor(15);
		for(int i=0;i<19;++i)
		{
			char fill[3];
			if(E_config[i]==0)
				break;
			itoa(E_config[i],fill,10);
			outtextxy(xp,368,shell[i]);
			xp=xp+textwidth(shell[i]);
			outtextxy(xp,365,fill);
			xp=xp+textwidth("  ");
		}
	}
	void rtostring()
	{
		char startstr[50],prevstr[50]="\n";
		int len=strlen(Name);
		for(int i=0;i<len;++i)
		startstr[i]=48+random(122-49);
		startstr[len]=NULL;
		for(int j=0;j<=len;++j)
		{
			setcolor(0);
			settextstyle(DEFAULT_FONT,0,2);
			outtextxy(240,90,prevstr);
			setcolor(15);
			outtextxy(240,90,startstr);
			delay(150);
			strcpy(prevstr,startstr);
			startstr[j]=Name[j];
			for(int k=j+1;k<len;++k)
			{
				startstr[k]=97+random(122-97);
			}
			startstr[len]=NULL;
		}
	}
public:
	show_in_table()
	{
		xpos=ypos=catcol=0;
	}
	void drawtotable()
	{
		//draw to default position in the table
		char anomber[5];
		//setcolor(WHITE);
		itoa(At_no,anomber,10);
		setfillstyle(SOLID_FILL,catcol);
		bar(xpos+2,ypos+2,24+xpos,24+ypos);
		rectangle(xpos,ypos,26+xpos,26+ypos);
		settextstyle(DEFAULT_FONT,0,1);
		settextjustify(LEFT_TEXT,RIGHT_TEXT);
		//setcolor(WHITE);
		outtextxy(4+xpos,4+ypos,Symbol);
		settextstyle(SMALL_FONT,0,4);
		settextjustify(RIGHT_TEXT,LEFT_TEXT);
		outtextxy(23+xpos,22+ypos,anomber);
		setcolor(WHITE);
	}
	void p_ostate()
	{
		char ostr[8];
		int x=220,y=262;
		settextjustify(LEFT_TEXT,CENTER_TEXT);
		for(int i=0;i<8;++i)
		{
			if(O_state[i]==0)
				break;
			itoa(O_state[i],ostr,10);
			outtextxy(x,y,ostr);
			x=x+textwidth(ostr);
			outtextxy(x,y,",");
			x=x+textwidth(",");
		}
		outtextxy(x,y,"0");
	}
	void drawtopanel()
	{
		//draw at any entered pos (x,y)
	   cleardevice();
	   char ano[10],amass[10],grp[10],per[10],mp[10],bp[10];
	   itoa(At_no,ano,10);
	   itoa(A_mass,amass,10);
	   itoa(Group,grp,10);
	   itoa(Period,per,10);
	   itoa(M_point,mp,10);
	   itoa(B_point,bp,10);
	   setfillstyle(SOLID_FILL,catcol);
	   bar(13,43,77,127);
	   rectangle(10,40,80,130);
	   settextjustify(CENTER_TEXT, CENTER_TEXT);
	   settextstyle(DEFAULT_FONT,0,3);
	   outtextxy(45,75,Symbol);
	   settextstyle(DEFAULT_FONT,0,2);
	   outtextxy(45,110,ano);
	   settextjustify(LEFT_TEXT,CENTER_TEXT);
	   settextstyle(DEFAULT_FONT,0,1);
	   outtextxy(10,182,"Category :");
	   outtextxy(10,202,"Group :");
	   outtextxy(10,222,"Period :");
	   outtextxy(10,242,"Atomic Number :");
	   outtextxy(10,348,"Electronic Configuration :");
	   outtextxy(10,282,"Melting Point (in K) :");
	   outtextxy(10,302,"Boiling Point (in K) :");
	   outtextxy(10,322,"Atomic Mass :");
	   outtextxy(10,262,"Oxidation States :");
	   settextstyle(SMALL_FONT,0,4);
	   outtextxy(220,182,Category);
	   outtextxy(220,202,grp);
	   outtextxy(220,222,per);
	   outtextxy(220,242,ano);
	   outtextxy(220,282,mp);
	   outtextxy(220,302,bp);
	   outtextxy(220,322,amass);
	   p_ostate();
	   drawEconfig();
	   rtostring();
	   settextstyle(SMALL_FONT,0,4);
	   setcolor(10);
	   outtextxy(530,440,"[BACKSPACE] Exit");
	   settextstyle(DEFAULT_FONT,0,1);
	   setcolor(15);
	   int keyp=0;
	   while(keyp!=8)
		   keyp=getch();
	}
	int search(char searchstr[])
	{
		int ptr;
		char cmpstring[3][30];
		strcpy(cmpstring[0],Symbol);
		strcpy(cmpstring[1],Name);
		itoa(At_no,cmpstring[2],10);
		for(int i=0;i<3;++i)
		{
			ptr=strcmpi(cmpstring[i],searchstr);
			if(ptr==0)
			{
				return 1;
			}
		}
		return 0;
	}
	void gettabdata()
	{
		get_E_info();
		cout<<"Enter Top left box x position (if this is not your part just enter 0)"<<endl;
		cin>>xpos;
		cout<<"Enter Top left box y position (if this is not your part just enter 0)"<<endl;
		cin>>ypos;
		cout<<"Enter Box Color "<<endl;
		cout<<"BLACK          0\nBLUE           1\nGREEN          2\n"
		    <<"CYAN           3\nRED            4\nMAGENTA        5\nBROWN          6\n"
		    <<"LIGHTGRAY      7\nDARKGRAY       8\nLIGHTBLUE      9\nLIGHTGREEN    10\n"
		    <<"LIGHTCYAN     11\nLIGHTRED      12\nLIGHTMAGENTA  13\nYELLOW        14\nWHITE         15"<<endl;
		cin>>catcol;
	}
}substance[110];


void introscr()
{
   settextjustify(LEFT_TEXT,TOP_TEXT);
   setfillstyle(SOLID_FILL,12);
   bar(62+x1,82+x2,148+x1,168+x2);

   setfillstyle(SOLID_FILL,10);
   bar(152+x1,172+x2,238+x1,258+x2);

   rectangle(60+x1,80+x2,150+x1,170+x2);
   rectangle(150+x1,170+x2,240+x1,260+x2);

   outtextxy(95+x1,150+x2,"15");
   outtextxy(190+x1,240+x2,"79");

   settextstyle(DEFAULT_FONT,0,4);

   outtextxy(90+x1,100+x2,"P");
   outtextxy(170+x1,190+x2,"Ta");
   outtextxy(160+x1,100+x2,"eriodic");
   outtextxy(250+x1,190+x2,"ble");
   settextstyle(SMALL_FONT,0,4);
   setcolor(10);
   outtextxy(530,440,"[ENTER] Select");
   settextstyle(DEFAULT_FONT,0,1);
   setcolor(15);
}

void disp_menu(int choice)
{
	char mitem[3][23]={">> Periodic Table",">> Chemical Analyser",">> Exit"};
	//draw the selected in yellow
	int y1[3]={150,200,250};
	settextstyle(SMALL_FONT,0,4);
	for(int i=0;i<3;++i)
	{
		if(i==choice)
		{
			setcolor(14);
			outtextxy(510,y1[i],mitem[i]);
		}
		else
		{
			setcolor(4);
			outtextxy(510,y1[i],mitem[i]);
		}
	}
	setcolor(15);
}

void d_table()
{
	cleardevice();
	for(int i=0;i<E_COUNT;++i)
	{
		substance[i].drawtotable();
		//getch();
	}
	settextstyle(SMALL_FONT,0,4);
	outtextxy(52,110,"1");
	outtextxy(78,136,"2");
	for(i=3;i<=12;i++)
	{
		char gno[3];
		itoa(i,gno,10);
		outtextxy(27+(i*26),188,gno);
	}
	for(i=13;i<=17;i++)
	{
		char gno[3];
		itoa(i,gno,10);
		outtextxy(27+(i*26),136,gno);
	}
	outtextxy(494,110,"18");
	for(i=1;i<=7;i++)
	{
		char gno[3];
		itoa(i,gno,10);
		outtextxy(25,110+(i*26),gno);
	}
	settextstyle(1,0,4);
	outtextxy(370,40,"Periodic Table");
	setcolor(10);
	settextstyle(SMALL_FONT,0,4);
	outtextxy(630,440,"[BACKSPACE] Exit");
	settextstyle(DEFAULT_FONT,0,1);
	setcolor(15);
	settextstyle(SMALL_FONT,0,4);
	settextjustify(LEFT_TEXT,RIGHT_TEXT);
	outtextxy(20,332,"Lanthanoids");
	outtextxy(25,376,"Actinoids");

}


void notfnd_diag()
{
	setfillstyle(SOLID_FILL,0);
	bar(200,320,430,420);
	setcolor(15);
	rectangle(202,322,428,418);
	settextstyle(SMALL_FONT,0,5);
	outtextxy(290,360,"Element not found");
	settextstyle(DEFAULT_FONT,0,4);
	rectangle(220,340,270,400);
	setfillstyle(SOLID_FILL,4);
	bar(222,342,268,398);
	outtextxy(230,355,"!");
	getch();
}

int exit_diag()
{
	int key,ch=0;
	setfillstyle(SOLID_FILL,0);
	bar(200,330,430,430);
	setcolor(15);
	rectangle(202,332,428,428);
	char mitem[2][10]={">> No",">> Yes"};
	//draw the selected in yellow
	int y1[2]={380,400};
	outtextxy(220,340,"Are you sure you want to");
	outtextxy(220,360,"exit?");
	settextstyle(SMALL_FONT,0,4);
	for(int i=0;i<2;++i)
	{
		if(i==ch)
		{
			setcolor(14);
			outtextxy(240,y1[i],mitem[i]);
		}
		else
		{
			setcolor(4);
			outtextxy(240,y1[i],mitem[i]);
		}
	}
	while(key!=13)
	{
		key=getch();
		if(key==0)
			key=getch();
		if(key==72)
			ch--;
		if(key==80)
			ch++;
		if(ch>1)
			ch=0;
		if(ch<0)
			ch=1;
		for(int i=0;i<2;++i)
		{
			if(i==ch)
			{
				setcolor(14);
				outtextxy(240,y1[i],mitem[i]);
			}
			else
			{
				setcolor(4);
				outtextxy(240,y1[i],mitem[i]);
			}
		}
	}
	setcolor(15);
	return ch;
}
void draw_s_screen()
{
	cleardevice();
	rectangle(110,220,510,250);
	setcolor(14);
	settextstyle(DEFAULT_FONT,0,2);
	outtextxy(100,160,"Chemical Recognition System");
	setcolor(12);
	settextstyle(SMALL_FONT,0,4);
	outtextxy(150,270,"Enter Name, Symbol or Atomic number to be searched");
	setcolor(15);
	settextstyle(SMALL_FONT,0,4);
	setcolor(10);
	outtextxy(530,420,"[ENTER] Search");
	outtextxy(530,440,"[BACKSPACE] Exit");
	settextstyle(DEFAULT_FONT,0,1);
	setcolor(15);
}


int main()
{
	int mmenu=1,done=0;
	fstream chemstorage;
	int active[3]={0,0,0};
	int gdriver = DETECT, gmode, errorcode;
	chemstorage.open("CBASE.bin",ios::in|ios::binary|ios::nocreate);
	if(!chemstorage)
	{
		cout<<"Cant read the elements stored !"<<endl;
		getch();
		exit(1);
	}
	for(int i=0;i<E_COUNT;++i)
	{
		if(chemstorage.good())
		{
			chemstorage.read((char*)&substance[i],sizeof(substance[i]));
		}
		else
		{
			cout<<"Corrupted File ..... \nAborting";
			while(!kbhit())
			{
				cout<<".";
				delay(1000);
				exit(1);
			}
		}
	}
    initgraph(&gdriver, &gmode, "");
	while(!done)
	{
		while(mmenu)
		{
			cleardevice();
			introscr();
			int ch=0,key=27;
			while(key!=13)
			{
				disp_menu(ch);
				key=getch();
				if(key==0)
					key=getch();
				if(key==72)
					ch = (ch-1)%3;
				if(key==80)
					ch = (ch+1)%3;
			}
			for(int i=0;i<3;++i)
			{
				active[i]=0;
				if(i==ch)
					active[ch]=1;
			}
			mmenu=0;
		}
		while(active[0])
		{
			int key=27;
			d_table();
			key=getch();
			while(key!=8)
			{
				key=getch();
			}
			mmenu=1;
			active[0]=0;
		}
		while(active[1])
		{
			int key,iter,found=0;
			char sstring[50];
			//cleardevice();
			draw_s_screen();
			key=0;
			key=getch();
			if(key==8)
			{
				mmenu=1;
				active[1]=0;
			}
			else if(key==13)
			{

				settextstyle(SMALL_FONT,0,4);
				setcolor(0);
				outtextxy(530,440,"[BACKSPACE] Exit");
				settextstyle(DEFAULT_FONT,0,1);
				setcolor(15);
				cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t";
				line(110,220,110,250);
				gets(sstring);
				for(iter=0;iter<E_COUNT;++iter)
				{
					if(found=substance[iter].search(sstring))
					{
						substance[iter].drawtopanel();
						break;
					}
				}
				if(!found)
					notfnd_diag();
				found=0;
				clrscr();
				cleardevice();
				key=0;
			}
		}
		while(active[2])
		{
			if(exit_diag())
			{
				active[2]=0;
				done=1;
			}
			else
			{
				mmenu=1;
				active[2]=0;
			}
		}
	}
	return 0;
}
