#include<conio.h>
#include<fstream.h>
#include<process.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class Element
{
   protected:

      char Name[20],Symbol[3],Category[15];
      int Group,Period,At_no,E_config[19],O_state[8];
      float M_point,B_point,A_mass,E_negativity;
      char sub_shell[19][3];

	  void get_E_config()
	  {
		  cout<<"Enter Electronic Configuration (enter zero to terminate) "<<endl;
		  for(int i=0;i<19;++i)
		  {
			  int temp;
			  cout<<sub_shell[i];
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
		  Group=Period=At_no=M_point=B_point=A_mass=E_negativity=0;
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
		 cout<<"Enter Electronegativity "<<endl;
		 cin>>E_negativity;
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
		 cout<<"Electronegativity : "<<E_negativity<<endl;
      }

};

class show_in_table:public Element
{
	int xpos,ypos,catcol;
public:
	show_in_table()
	{
		xpos=ypos=catcol=0;
	}
	void drawtotable()
	{
		//draw to default position in the table
	}
	void drawtotable(int x,int y)
	{
		//draw at any entered pos (x,y)
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
}substance[108];

int main()
{
	clrscr();

	//variable declaration
	fstream chemstorage;
	int elmnew=0;
	char notdone='y';
	//char astr[5],fname[10];
	chemstorage.open("CBASE.bin",ios::out|ios::binary|ios::app);
	if(!chemstorage)
	{
		cout<<"Cant read the elements stored; contact system designer !"<<endl;
		getch();
		exit(1);
	}
	while((notdone=='y'||notdone=='Y')&&chemstorage.good())
	{
		substance[elmnew].gettabdata();
		chemstorage.write((char*)&substance[elmnew],sizeof(substance[elmnew]));
		++elmnew;
		cout<<"Wanna' enter more ??(Y(yes)orN(no))"<<endl;
		cin>>notdone;
	}
	chemstorage.close();
	//getch();
	return 0;
}
