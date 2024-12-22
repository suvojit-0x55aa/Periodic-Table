/*
 * PER_TABL.CPP - Interactive Periodic Table System
 * 
 * This program provides an interactive periodic table interface with:
 * - Visual representation of all chemical elements
 * - Element search functionality by name, symbol, or atomic number
 * - Detailed element information display
 * - Menu-driven interface with graphics
 * - Binary file storage for element data
 *
 * Author: [Your Name]
 * Last Updated: [Date]
 */

#include<conio.h>
#include<fstream.h>
#include<process.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<dos.h>

// Display positioning constants
#define x1 40    // Left margin offset (in pixels) for intro screen elements and menu items
#define x2 60    // Top margin offset (in pixels) for intro screen elements and menu items

// Program constants
#define E_COUNT 110  // Maximum number of chemical elements supported in the database
                    // Set to 110 to include all known elements plus space for potential new elements

class Element
{
   protected:

      // Element identification and classification
      char Name[20],       // Full element name (max 19 chars + null terminator)
           Symbol[3],      // Chemical symbol (max 2 chars + null terminator)
           Category[15];   // Element category (e.g., "Noble Gas", "Alkali Metal")

      // Atomic properties and configurations
      int Group,          // Periodic table group number (1-18)
          Period,         // Periodic table period number (1-7)
          At_no,         // Atomic number (unique element identifier)
          E_config[19],   // Electron configuration (number of electrons in each subshell)
          O_state[8];     // Oxidation states (max 8 different states per element)

      // Physical properties
      float M_point,      // Melting point in Kelvin
            B_point,      // Boiling point in Kelvin
            A_mass;       // Atomic mass in atomic mass units (amu)

      // Electron configuration labels
      char sub_shell[19][3];  // Subshell labels (e.g., "1s", "2p", "3d")
                              // 19 possible subshells, 2 chars + null terminator each

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
      /*
       * Element Class Constructor
       * 
       * Purpose:
       * Initializes a new Element object with default values and proper electron subshell configuration.
       * This ensures all elements start in a clean, well-defined state before specific data is assigned.
       * 
       * Initialization steps:
       * 1. Clear text fields (Name, Symbol, Category) by setting to NULL
       * 2. Set up electron subshell labels in standard quantum mechanical order
       * 3. Initialize all numeric values to zero
       * 4. Clear oxidation states and electron configuration arrays
       */
      Element()
      {
          // Initialize text arrays to NULL
          for(int i=0;i<20;++i)
             Name[i]=NULL;
          for(i=0;i<3;++i)
              Symbol[0]=NULL;          // Note: Bug - should be Symbol[i]
          for(i=0;i<15;++i)
              Category[0]=NULL;        // Note: Bug - should be Category[i]

          // Define and copy standard electron subshell labels
          // Order follows aufbau principle: 1s→2s→2p→3s→3p→4s→3d...
          char shell[19][3]={"1s","2s","2p","3s","3p","4s","3d","4p","5s","4d","5p","6s","4f","5d","6p","7s","5f","6d","7p"};
          for(i=0;i<19;++i)
          {
            for(int j=0;j<3;++j)
                sub_shell[i][j]=shell[i][j];
          }

          // Initialize all numeric properties to zero
          Group=Period=At_no=M_point=B_point=A_mass=0;

          // Clear arrays for oxidation states and electron configuration
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

/*
 * show_in_table Class
 * Inherits from: Element
 * 
 * Purpose: Handles the graphical display and interaction of elements in the periodic table.
 * This class extends Element to add visualization capabilities.
 */
class show_in_table:public Element
{
    private:
        int xpos;    // X coordinate for element's position in table
        int ypos;    // Y coordinate for element's position in table
        int catcol;  // Color code for element category display (0-15)

        /*
         * Draws the electronic configuration in graphical format
         * Uses standard quantum notation (1s2, 2s2, etc.)
         * Displays horizontally with proper spacing
         */
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

        /*
         * Creates an animation effect when displaying element names
         * Generates random characters that transition to the actual name
         * Creates a "decoding" visual effect
         */
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
        // Initialize element position and color to default values
        show_in_table()
        {
            xpos=ypos=catcol=0;
        }

        /*
         * Draws element box in the periodic table
         * Shows:
         * - Element symbol
         * - Atomic number
         * - Color-coded background based on element category
         */
        void drawtotable()
        {
            char anomber[5];
            itoa(At_no,anomber,10);
            setfillstyle(SOLID_FILL,catcol);
            bar(xpos+2,ypos+2,24+xpos,24+ypos);
            rectangle(xpos,ypos,26+xpos,26+ypos);
            settextstyle(DEFAULT_FONT,0,1);
            settextjustify(LEFT_TEXT,RIGHT_TEXT);
            outtextxy(4+xpos,4+ypos,Symbol);
            settextstyle(SMALL_FONT,0,4);
            settextjustify(RIGHT_TEXT,LEFT_TEXT);
            outtextxy(23+xpos,22+ypos,anomber);
            setcolor(WHITE);
        }

        /*
         * Displays oxidation states in a comma-separated format
         * Position: x=220, y=262 on screen
         * Format: "+1, +2, +3, 0" etc.
         */
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

        /*
         * Draws detailed element information panel
         * Shows:
         * - Basic properties (symbol, atomic number)
         * - Physical properties (melting/boiling points)
         * - Electronic properties (configuration)
         * - Classification info (group, period)
         * Includes animated name display
         */
        void drawtopanel()
        {
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

        /*
         * Searches for element by name, symbol, or atomic number
         * Parameters:
         *   searchstr[] - String to search for
         * Returns:
         *   1 if element found
         *   0 if not found
         */
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

        /*
         * Gets element data from user input
         * Includes:
         * - Position in periodic table (x,y coordinates)
         * - Color code for element category
         * - Basic element data (inherited from Element class)
         */
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
};

// Array to store all elements in the periodic table
show_in_table substance[110];  // Supports up to 110 elements

/*
 * Introduction Screen Function
 * 
 * Purpose:
 * Creates an artistic title screen using elements P (Phosphorus) and Ta (Tantalum)
 * to spell out "Periodic Table" in a creative way.
 * 
 * Visual Layout:
 * - Two colored boxes containing element tiles
 * - Box 1 (Red): Contains "P" (Atomic number 15 - Phosphorus)
 * - Box 2 (Green): Contains "Ta" (Atomic number 79 - Tantalum)
 * - Text arranged to spell "Periodic Table"
 * - Navigation hint at bottom
 * 
 * Integration:
 * - Called at program startup and when returning to main menu
 * - Part of the main menu system (mmenu loop in main())
 * - Uses x1, x2 constants for consistent positioning
 */
void introscr()
{
    // Set text alignment to top-left corner
    settextjustify(LEFT_TEXT,TOP_TEXT);

    // Draw first element box (Phosphorus - P)
    setfillstyle(SOLID_FILL,12);      // Color 12 (Light Red)
    bar(62+x1,82+x2,148+x1,168+x2);   // Fill box

    // Draw second element box (Tantalum - Ta)
    setfillstyle(SOLID_FILL,10);      // Color 10 (Light Green)
    bar(152+x1,172+x2,238+x1,258+x2); // Fill box

    // Draw borders for both boxes
    rectangle(60+x1,80+x2,150+x1,170+x2);    // P box border
    rectangle(150+x1,170+x2,240+x1,260+x2);  // Ta box border

    // Add atomic numbers
    outtextxy(95+x1,150+x2,"15");   // Phosphorus
    outtextxy(190+x1,240+x2,"79");  // Tantalum

    // Draw title text
    settextstyle(DEFAULT_FONT,0,4);  // Large text for elements
    outtextxy(90+x1,100+x2,"P");     // Phosphorus symbol
    outtextxy(170+x1,190+x2,"Ta");   // Tantalum symbol
    outtextxy(160+x1,100+x2,"eriodic"); // Complete "Periodic"
    outtextxy(250+x1,190+x2,"ble");     // Complete "Table"

    // Add navigation hint
    settextstyle(SMALL_FONT,0,4);
    setcolor(10);                         // Green color
    outtextxy(530,440,"[ENTER] Select"); // Navigation instruction

    // Reset text settings
    settextstyle(DEFAULT_FONT,0,1);
    setcolor(15);                        // White color
}

/*
 * Displays the main menu options for the user to select from.
 * 
 * Parameters:
 *   choice - The index of the currently selected menu item (0, 1, or 2)
 * 
 * Menu Options:
 * 0 - Periodic Table
 * 1 - Chemical Analyser
 * 2 - Exit
 * 
 * The selected menu item is highlighted in yellow, while the others are displayed in red.
 * This function is called in the main menu loop to allow user navigation.
 */
void disp_menu(int choice)
{
    char mitem[3][23] = {">> Periodic Table", ">> Chemical Analyser", ">> Exit"};
    // Draw the selected item in yellow
    int y1[3] = {150, 200, 250}; // Y positions for each menu item
    settextstyle(SMALL_FONT, 0, 4); // Set text style for menu items
    for (int i = 0; i < 3; ++i)
    {
        if (i == choice)
        {
            setcolor(14); // Yellow color for selected item
            outtextxy(510, y1[i], mitem[i]); // Display selected item
        }
        else
        {
            setcolor(4); // Red color for unselected items
            outtextxy(510, y1[i], mitem[i]); // Display unselected item
        }
    }
    setcolor(15); // Reset color to white
}

/*
 * Draws the complete periodic table on the screen.
 * 
 * This function clears the device and iterates through the array of elements,
 * calling the drawtotable method for each element to render it in the table.
 * It also labels the groups and periods of the periodic table.
 * 
 * Integration:
 * - Called when the user selects the "Periodic Table" option from the main menu.
 * - Provides a visual representation of all elements in the periodic table.
 */
void d_table()
{
    cleardevice(); // Clear the screen for fresh drawing
    for (int i = 0; i < E_COUNT; ++i)
    {
        substance[i].drawtotable(); // Draw each element in the table
    }

    // Draw group numbers
    settextstyle(SMALL_FONT, 0, 4);
    outtextxy(52, 110, "1");
    outtextxy(78, 136, "2");
    for (int i = 3; i <= 12; i++)
    {
        char gno[3];
        itoa(i, gno, 10);
        outtextxy(27 + (i * 26), 188, gno); // Group numbers for the first two rows
    }
    for (int i = 13; i <= 17; i++)
    {
        char gno[3];
        itoa(i, gno, 10);
        outtextxy(27 + (i * 26), 136, gno); // Group numbers for the second row
    }
    outtextxy(494, 110, "18"); // Last group number

    // Draw period numbers
    for (int i = 1; i <= 7; i++)
    {
        char gno[3];
        itoa(i, gno, 10);
        outtextxy(25, 110 + (i * 26), gno); // Period numbers on the left
    }

    // Title and additional labels
    settextstyle(1, 0, 4);
    outtextxy(370, 40, "Periodic Table");
    setcolor(10); // Green color for additional text
    settextstyle(SMALL_FONT, 0, 4);
    outtextxy(630, 440, "[BACKSPACE] Exit"); // Exit instruction
    settextstyle(DEFAULT_FONT, 0, 1);
    setcolor(15); // Reset color to white
    settextstyle(SMALL_FONT, 0, 4);
    settextjustify(LEFT_TEXT, RIGHT_TEXT);
    outtextxy(20, 332, "Lanthanoids"); // Label for Lanthanoids
    outtextxy(25, 376, "Actinoids");   // Label for Actinoids
}

/*
 * Displays a dialog box indicating that the searched element was not found.
 * 
 * Purpose:
 * This function creates a visual alert to inform the user that the element they
 * searched for does not exist in the database.
 * 
 * Visual Layout:
 * - A filled rectangle with a message "Element not found"
 * - An exclamation mark to emphasize the alert
 * 
 * Integration:
 * - Called when a search for an element fails in the search functionality.
 */
void notfnd_diag()
{
    setfillstyle(SOLID_FILL,0); // Set background color to black
    bar(200,320,430,420); // Draw a filled rectangle for the dialog box
    setcolor(15); // Set text color to white
    rectangle(202,322,428,418); // Draw the border of the dialog box
    settextstyle(SMALL_FONT,0,5); // Set text style for the message
    outtextxy(290,360,"Element not found"); // Display the message
    settextstyle(DEFAULT_FONT,0,4); // Reset text style
    rectangle(220,340,270,400); // Draw a rectangle for the exclamation mark
    setfillstyle(SOLID_FILL,4); // Set fill color to red
    bar(222,342,268,398); // Draw the filled rectangle for the exclamation mark
    outtextxy(230,355,"!"); // Display the exclamation mark
    getch(); // Wait for user input to close the dialog
}

/*
 * Displays a confirmation dialog asking the user if they want to exit the program.
 * 
 * Returns:
 *   0 if the user selects "No"
 *   1 if the user selects "Yes"
 * 
 * Purpose:
 * This function creates a dialog box that prompts the user to confirm if they want to exit the application.
 * 
 * Integration:
 * - Called when the user selects the exit option from the main menu.
 * - Provides a way to prevent accidental exits.
 */
int exit_diag()
{
    int key, ch = 0; // Initialize key for input and ch for menu selection
    setfillstyle(SOLID_FILL,0); // Set background color to black
    bar(200,330,430,430); // Draw a filled rectangle for the dialog box
    setcolor(15); // Set text color to white
    rectangle(202,332,428,428); // Draw the border of the dialog box
    char mitem[2][10] = {">> No", ">> Yes"}; // Menu items for confirmation
    int y1[2] = {380, 400}; // Y positions for each menu item
    outtextxy(220,340,"Are you sure you want to"); // Display confirmation message
    outtextxy(220,360,"exit?"); // Display exit question
    settextstyle(SMALL_FONT,0,4); // Set text style for menu items
    for(int i = 0; i < 2; ++i)
    {
        if(i == ch)
        {
            setcolor(14); // Yellow color for selected item
            outtextxy(240,y1[i],mitem[i]); // Display selected item
        }
        else
        {
            setcolor(4); // Red color for unselected items
            outtextxy(240,y1[i],mitem[i]); // Display unselected item
        }
    }
    while(key != 13) // Wait for Enter key to be pressed
    {
        key = getch(); // Get user input
        if(key == 0) // Handle special keys
            key = getch();
        if(key == 72) // Up arrow key
            ch--;
        if(key == 80) // Down arrow key
            ch++;
        if(ch > 1) // Loop back to the first option
            ch = 0;
        if(ch < 0) // Loop to the last option
            ch = 1;
        for(int i = 0; i < 2; ++i)
        {
            if(i == ch)
            {
                setcolor(14); // Yellow color for selected item
                outtextxy(240,y1[i],mitem[i]); // Display selected item
            }
            else
            {
                setcolor(4); // Red color for unselected items
                outtextxy(240,y1[i],mitem[i]); // Display unselected item
            }
        }
    }
    setcolor(15); // Reset color to white
    return ch; // Return the user's choice
}

/*
 * Draws the search screen for the chemical recognition system.
 * 
 * Purpose:
 * This function creates a user interface for searching elements by name, symbol, or atomic number.
 * 
 * Visual Layout:
 * - Title for the Chemical Recognition System
 * - Instructions for user input
 * - Navigation hints for searching and exiting
 * 
 * Integration:
 * - Called when the user selects the "Chemical Analyser" option from the main menu.
 */
void draw_s_screen()
{
    cleardevice(); // Clear the screen for fresh drawing
    rectangle(110,220,510,250); // Draw a rectangle for the input area
    setcolor(14); // Set text color to yellow
    settextstyle(DEFAULT_FONT,0,2); // Set text style for title
    outtextxy(100,160,"Chemical Recognition System"); // Display title
    setcolor(12); // Set text color to red
    settextstyle(SMALL_FONT,0,4); // Set text style for instructions
    outtextxy(150,270,"Enter Name, Symbol or Atomic number to be searched"); // Display instructions
    setcolor(15); // Reset text color to white
    settextstyle(SMALL_FONT,0,4); // Set text style for navigation hints
    setcolor(10); // Set text color to green
    outtextxy(530,420,"[ENTER] Search"); // Display search hint
    outtextxy(530,440,"[BACKSPACE] Exit"); // Display exit hint
    settextstyle(DEFAULT_FONT,0,1); // Reset text style
    setcolor(15); // Reset color to white
}

/*
 * Main Function
 * 
 * Purpose:
 * The main function serves as the entry point for the program, managing the overall flow of the application.
 * It initializes the graphics mode, handles user interactions through a menu system, and facilitates
 * the display and search of chemical elements in the periodic table.
 * 
 * Program Flow:
 * 1. Initialize variables and open the binary file containing element data.
 * 2. Load element data into the `substance` array from the binary file.
 * 3. Enter the main loop, which continues until the user decides to exit.
 * 4. Display the introduction screen and the main menu.
 * 5. Handle user selections:
 *    - If "Periodic Table" is selected, display the periodic table using the `d_table` function.
 *    - If "Chemical Analyser" is selected, display the search screen using the `draw_s_screen` function.
 *    - If "Exit" is selected, prompt the user for confirmation using the `exit_diag` function.
 * 6. Allow users to search for elements by name, symbol, or atomic number.
 * 7. Display detailed information about the found element or show an error dialog if not found.
 * 8. Clean up and exit the program when the user confirms they want to exit.
 */
int main()
{
    int mmenu = 1, done = 0; // Menu state and exit flag
    fstream chemstorage; // File stream for reading element data
    int active[3] = {0, 0, 0}; // Array to track active menu options
    int gdriver = DETECT, gmode, errorcode; // Graphics driver and mode variables

    // Open the binary file containing element data
    chemstorage.open("CBASE.bin", ios::in | ios::binary | ios::nocreate);
    if (!chemstorage)
    {
        cout << "Cant read the elements stored !" << endl;
        getch();
        exit(1); // Exit if the file cannot be opened
    }

    // Load element data into the substance array
    for (int i = 0; i < E_COUNT; ++i)
    {
        if (chemstorage.good())
        {
            chemstorage.read((char*)&substance[i], sizeof(substance[i]));
        }
        else
        {
            cout << "Corrupted File ..... \nAborting";
            while (!kbhit())
            {
                cout << ".";
                delay(1000);
                exit(1); // Exit if the file is corrupted
            }
        }
    }

    // Initialize graphics mode
    initgraph(&gdriver, &gmode, "");

    // Main program loop
    while (!done)
    {
        // Menu loop
        while (mmenu)
        {
            cleardevice(); // Clear the screen
            introscr(); // Display the introduction screen
            int ch = 0, key = 27; // Initialize choice and key variables
            while (key != 13) // Wait for Enter key
            {
                disp_menu(ch); // Display the main menu
                key = getch(); // Get user input
                if (key == 0)
                    key = getch(); // Handle special keys
                if (key == 72) // Up arrow key
                    ch--;
                if (key == 80) // Down arrow key
                    ch++;
                if (ch > 2) // Loop back to the first option
                    ch = 0;
                if (ch < 0) // Loop to the last option
                    ch = 2;
            }
            // Set active menu option
            for (int i = 0; i < 3; ++i)
            {
                active[i] = 0;
                if (i == ch)
                    active[ch] = 1; // Mark selected option as active
            }
            mmenu = 0; // Exit menu loop
        }

        // Handle "Periodic Table" option
        while (active[0])
        {
            int key = 27; // Initialize key variable
            d_table(); // Display the periodic table
            key = getch(); // Wait for user input
            while (key != 8) // Wait for Backspace key
            {
                key = getch();
            }
            mmenu = 1; // Return to menu
            active[0] = 0; // Reset active state
        }

        // Handle "Chemical Analyser" option
        while (active[1])
        {
            int key, iter, found = 0; // Initialize variables
            char sstring[50]; // String for user input
            draw_s_screen(); // Display search screen
            key = 0; // Initialize key variable
            key = getch(); // Get user input
            if (key == 8) // If Backspace is pressed
            {
                mmenu = 1; // Return to menu
                active[1] = 0; // Reset active state
            }
            else if (key == 13) // If Enter is pressed
            {
                settextstyle(SMALL_FONT, 0, 4);
                setcolor(0);
                outtextxy(530, 440, "[BACKSPACE] Exit");
                settextstyle(DEFAULT_FONT, 0, 1);
                setcolor(15);
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t";
                line(110, 220, 110, 250); // Draw input line
                gets(sstring); // Get user input for search
                for (iter = 0; iter < E_COUNT; ++iter)
                {
                    if (found = substance[iter].search(sstring)) // Search for element
                    {
                        substance[iter].drawtopanel(); // Display element details
                        break; // Exit loop if found
                    }
                }
                if (!found)
                    notfnd_diag(); // Show not found dialog if not found
                found = 0; // Reset found flag
                clrscr(); // Clear screen
                cleardevice(); // Clear device
                key = 0; // Reset key variable
            }
        }

        // Handle "Exit" option
        while (active[2])
        {
            if (exit_diag()) // Show exit confirmation dialog
            {
                active[2] = 0; // Reset active state
                done = 1; // Set done flag to exit program
            }
            else
            {
                mmenu = 1; // Return to menu
                active[2] = 0; // Reset active state
            }
        }
    }
    return 0; // Exit the program
}