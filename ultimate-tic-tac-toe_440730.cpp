/********************************************************************************************************************************************************************************************************/
/********************************************************************************************************************************************************************************************************/
/*
Introduction to Programming
Final Project
Tic-Tac-Toe
Created by: github user jvcor-24

v1.0 - started 14 Mar 2019
v1.1 - added reference grid for easier input
	 - added input error handling
		- player can no longer override previous players move
		- error message shows if input not part of the grid		
v1.2 - revamped ui for grid
		- removed need for grid guide
	 - finished win determining block
	 - successful error handling
v1.3 - added menu 31 Mar 2019
	 - implemented array system
	 	- revamped player_input(), 
		 	win_message(), 
		 	winner() - added draw function
		- added turn(), print_game()
v1.4 - created computer ai						
v2.0 - started 1 Apr 2019
	 - began works on ultimate tic-tac-toe
	 - finished all basic PVP elements for ultimate, 2 Apr 2019
	 - additional features:
	 	- help section
		- color changing elements	
v3.0 - began and completed ultimate ai, 3 Apr 2019
	 - fixed an issue with ultimate where a mini grid
	   where a draw occured was not recognised as a completed mini
	 - added a midgame exit function
	 - minor UI adjustments

TO DO LIST
1. Test full games with the ultimate version		-all good so far
2. Hunt for more bugs
3. add edit color function - can be edited directly in the code
4. improve computer ai skills, especially for ultimate
5. add option for difficulty levels (create an input at pregame message and input into computer logic)
*/
/********************************************************************************************************************************************************************************************************/
/********************************************************************************************************************************************************************************************************/

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>		//for time delay		
#include <time.h> 			//for random seed
#include <dos.h>			//for color()
#include <dir.h>			//for color()

using namespace std;

/********************************************************************************************************************************************************************************************************/
/********************************************************************************************************************************************************************************************************/
//VARIABLES

const int x_c=9;			//color for X						0 = Black	5 = Purple		A = Light Green		D = Light Purple
const int o_c=2;			//color for O						1 = Blue	6 = Yellow		B = Light Aqua		E = Light Yellow
const int a_c=7;			//color for active boards			2 = Green	7 = White 		C = Light Red 		F = Bright White
const int i_c=6;			//color for inactive boards lines	3 = Aqua	8 = Gray
const int m_c=7;			//color for menu text				4 = Red		9 = Light Blue      
const int d_c=3;			//color for draw case

char a,b,c,d,e,f,g,h,i,		//used as shorthand for critical array coordinates
	 a1,b1,c1,d1,e1,f1,g1,h1,i1,
	 ua,ub,uc,ud,ue,uf,ug,uh,ui;

char current=' ';			//to indicate current player identification X/O
char opt[]=" ";				//menu selection
int win=0;					//indicator for a match-3
int error=0;				//indicator for errors
int m=0;					//counts number of valid moves
int ord=0;					//for random order
int com=0;					//for random computer moves
int valid=0;				//check for valid computer move
int move=0;					//player move

int grid=0;					//indicator for ultimate
int win_mini=0; 			//checks if mini can be taken over
int ctmh=0;
char ultimate[9]={'1','2','3','4','5','6','7','8','9'};					//checker for states of big board
const char reset_ultimate[9]={'1','2','3','4','5','6','7','8','9'};		//reset for ultimate[]
const char dr='%';			//symbol for draw cases

char normal[13][25]=		//[height][width], array for normal game
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',	//0
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',	//1
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',	//2
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',	//3
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',	//4
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',	//5
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',	//6
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',	//7
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',	//8
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',	//9
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',	//10
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',	//11
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'		//12
};/* guide for array coordinates
 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24
*/

char ultimate1[13][25]=		//arrays for the ultimate board
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

char ultimate2[13][25]=	
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

char ultimate3[13][25]=	
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

char ultimate4[13][25]=
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

char ultimate5[13][25]=
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

char ultimate6[13][25]=
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

char ultimate7[13][25]=
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

char ultimate8[13][25]=	
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

char ultimate9[13][25]=
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

const char reset[13][25]=	//reference array for new game, same as normal[][]
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','7',' ',' ',' ','|',' ',' ',' ','8',' ',' ',' ','|',' ',' ',' ','9',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','4',' ',' ',' ','|',' ',' ',' ','5',' ',' ',' ','|',' ',' ',' ','6',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'|',' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','3',' ',' ',' ','|',
'|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ','|',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'	
};

/********************************************************************************************************************************************************************************************************/
/********************************************************************************************************************************************************************************************************/
//COMMON FUNCTIONS

void color(int ForgC)		//credits to Sir J**d for this function
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
							//We use csbi for the wAttributes word.
	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{						//Mask out all but the background attribute, and add in the forgournd color
	    wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
	    SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

/****************************************************************************************************/

void reset_game()			//resets all important variables and arrays to original values for new game
{
	move=0;
	current=' ';
	opt[0]=' ';
	win=0;
	error=0;
	m=0;
	grid=0;
	win_mini=0;
	ctmh=0;
	//reverts normal[][] to original
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{normal[j][i]=reset[j][i];}		}
	//reverts ultimate(n)[][] to original
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate1[j][i]=reset[j][i];}	}
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate2[j][i]=reset[j][i];}	}	
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate3[j][i]=reset[j][i];}	}
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate4[j][i]=reset[j][i];}	}
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate5[j][i]=reset[j][i];}	}
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate6[j][i]=reset[j][i];}	}
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate7[j][i]=reset[j][i];}	}
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate8[j][i]=reset[j][i];}	}
	for(int j=0; j<=12; j++)	{	for(int i=0; i<=24; i++)	{ultimate9[j][i]=reset[j][i];}	}
	//reverts ultimate[] to original
	for(int i=0; i<=8; i++)		{	ultimate[i]=reset_ultimate[i];	}	
}

/****************************************************************************************************/

void menu()					//displays menu
{
	system("cls");
	color(d_c);
	cout<<"\n\t  #    #  #     #######  #  #     #   ####  ####### #####  ";
	cout<<"\n\t  #    #  #        #     #  ##   ##  #    #    #    #      ";
	cout<<"\n\t  #    #  #        #     #  # # # #  ######    #    ###    ";
	cout<<"\n\t  #    #  #        #     #  #  #  #  #    #    #    #      ";
	cout<<"\n\t   ####   ######   #     #  #     #  #    #    #    #####  ";
	cout<<"\n\t                                                           ";
	cout<<"\n\t  ##### #  ####    #####  ###   ####    #####  ###  #####  ";
	cout<<"\n\t    #   # #          #   #   # #          #   #   # #      ";
	cout<<"\n\t    #   # #     ##   #   ##### #     ##   #   #   # ###    ";
	cout<<"\n\t    #   # #          #   #   # #          #   #   # #      ";
	cout<<"\n\t    #   #  ####      #   #   #  ####      #    ###  #####  ";
	color(m_c);
	cout<<"\n\t|---------------------------------------------------------|";
	cout<<"\n\t|                                                         |";
	cout<<"\n\t|          [1] - CLASSIC  [Player v Player]               |";
	cout<<"\n\t|          [2] - CLASSIC  [Player v Computer]             |";
	cout<<"\n\t|          [3] - ULTIMATE [Player v Player]               |";
	cout<<"\n\t|          [4] - ULTIMATE [Player v Computer]             |";
	cout<<"\n\t|          [5] - Help                                     |";
	cout<<"\n\t|          [X] - Quit                                     |";
	cout<<"\n\t|                                                         |";
	cout<<"\n\t|---------------------------------------------------------|";
	color(d_c);
	cout<<"\n\t>>> ";
	cin>>opt;
}

/****************************************************************************************************/

void help()					//displays help
{
	system("cls");
	color(m_c);
	cout<<"\n\tCLASSIC Tic-Tac-Toe\n";
	cout<<"\t\tPlayers take turns to place their marks on the board.\n";
	cout<<"\t\tFirst player to match 3 in a row, column, or diagonal wins.\n\n\n";
	cout<<"\tULTIMATE Tic-Tac-Toe\n";
	cout<<"\t\tThis game involves a mini tic-tac-toes within a larger tic-tac-toe.\n";
	cout<<"\t\tA grid on the big board is taken by the player who wins that grid's mini board\n\n";
	cout<<"\t\t1. For the first turn, choose which grid on the big board to play.\n";
	cout<<"\t\t2. Make your move on the mini board.\n";
	cout<<"\t\t3. The next turn will be done on the grid on the big board\n";
	cout<<"\t\t   that corrresponds to previous move on the mini board\n";
	cout<<"\t\t4. If the supposed next grid is already taken by any player, \n";
	cout<<"\t\t   the current player can choose anywhere to move.\n";
	cout<<"\t\t5. The game ends once someone completes a match-3 on the big board.\n\n\n";
	cout<<"\tPlayer v Player\n";
	cout<<"\t\t1. Decide who plays as X and who plays as O.\n";
	cout<<"\t\t2. The game will choose who plays first randomly.\n";
	cout<<"\t\t3. If you see a draw, complete the board to finish the game.\n\n\n";
	cout<<"\tPlayer v Computer\n";
	cout<<"\t\t1. You are automatically assigned as player X,\n";
	cout<<"\t\t   and the computer as player O.\n";
	cout<<"\t\t2. The game will choose who plays first randomly.\n";
	cout<<"\t\t3. If you detect a draw, complete the board to finish the game.\n\n\n";	
	cout<<"\tPress any key to go back...";
	getch();
}

/****************************************************************************************************/

void order()				//for randomising player turn
{
    srand((unsigned)time(0)); 
	ord=(rand()%100)+1;
}

/****************************************************************************************************/
//function only for CLASSIC but needs to be defined already for win_message()

void print_game()			//prints the current state of the game table, c/o J**o C**o for teaching me this
{
	{color(8); cout<<"\n\tInput 9342 to exit the current game.\n\n";}
	for(int j=0; j<=12; j++)
	{
		for(int i=0; i<=24; i++)
		{
			if 		(normal[j][i]=='X')	{	color(x_c);	}
			else if (normal[j][i]=='O')	{	color(o_c);	}
			if (i==0) {cout<<"\t";}
			cout<<normal[j][i];
			color(a_c);
			if (i==24)	{cout<<"\n";}	//adds a line break
		}
				
	}
}

/****************************************************************************************************/
//function only for ULTIMATE but needs to be defined already for win_message()

void print_ultimate()		//prints the table for ultimate, color functions for better ui
{
	color(8); cout<<"\n\tInput 9342 to exit the current game.\n\n";
	color(i_c);	cout<<("\t|-------------------------------------------------------------------------------|\n");
	for(int j=0; j<=12; j++)
	{
		color(i_c);	cout<<("\t| ");		//multiple conditions for when to change the colors
		for(int i=0; i<=24; i++)	{	if (grid==7) color(a_c); else color(i_c); if (ultimate7[j][i]=='X') color(x_c); else if (ultimate7[j][i]=='O') color(o_c); else if (ultimate7[j][i]==dr) color(d_c); cout<<ultimate7[j][i];	if (i==24) cout<<(" "); }
		for(int i=0; i<=24; i++)	{	if (grid==8) color(a_c); else color(i_c); if (ultimate8[j][i]=='X') color(x_c); else if (ultimate8[j][i]=='O') color(o_c); else if (ultimate8[j][i]==dr) color(d_c); cout<<ultimate8[j][i];	if (i==24) cout<<(" ");	}
		for(int i=0; i<=24; i++)	{	if (grid==9) color(a_c); else color(i_c); if (ultimate9[j][i]=='X') color(x_c); else if (ultimate9[j][i]=='O') color(o_c); else if (ultimate9[j][i]==dr) color(d_c); cout<<ultimate9[j][i];	
										if (i==24)	{color(i_c);	cout<<(" |"); cout<<"\n";}			}	//adds a line break
	}
	for(int j=0; j<=12; j++)
	{
		color(i_c);	cout<<("\t| ");
		for(int i=0; i<=24; i++)	{	if (grid==4) color(a_c); else color(i_c); if (ultimate4[j][i]=='X') color(x_c); else if (ultimate4[j][i]=='O') color(o_c); else if (ultimate4[j][i]==dr) color(d_c); cout<<ultimate4[j][i];	if (i==24) cout<<(" ");	}
		for(int i=0; i<=24; i++)	{	if (grid==5) color(a_c); else color(i_c); if (ultimate5[j][i]=='X') color(x_c); else if (ultimate5[j][i]=='O') color(o_c); else if (ultimate5[j][i]==dr) color(d_c); cout<<ultimate5[j][i];	if (i==24) cout<<(" ");	}
		for(int i=0; i<=24; i++)	{	if (grid==6) color(a_c); else color(i_c); if (ultimate6[j][i]=='X') color(x_c); else if (ultimate6[j][i]=='O') color(o_c); else if (ultimate6[j][i]==dr) color(d_c); cout<<ultimate6[j][i];	
										if (i==24)	{color(i_c);	cout<<(" |"); cout<<"\n";}	}	//adds a line break
	}
	for(int j=0; j<=12; j++)
	{
		color(i_c);	cout<<("\t| ");
		for(int i=0; i<=24; i++)	{	if (grid==1) color(a_c); else color(i_c); if (ultimate1[j][i]=='X') color(x_c); else if (ultimate1[j][i]=='O') color(o_c); else if (ultimate1[j][i]==dr) color(d_c); cout<<ultimate1[j][i];	if (i==24) cout<<(" ");	}
		for(int i=0; i<=24; i++)	{	if (grid==2) color(a_c); else color(i_c); if (ultimate2[j][i]=='X') color(x_c); else if (ultimate2[j][i]=='O') color(o_c); else if (ultimate2[j][i]==dr) color(d_c); cout<<ultimate2[j][i];	if (i==24) cout<<(" ");	}
		for(int i=0; i<=24; i++)	{	if (grid==3) color(a_c); else color(i_c); if (ultimate3[j][i]=='X') color(x_c); else if (ultimate3[j][i]=='O') color(o_c); else if (ultimate3[j][i]==dr) color(d_c); cout<<ultimate3[j][i];	
										if (i==24)	{color(i_c);	cout<<(" |"); cout<<"\n";}	}	//adds a line break
	}
	color(i_c);	cout<<("\t|-------------------------------------------------------------------------------|\n");
}

/****************************************************************************************************/

void win_message(char w)	//displays message indicating end of a game
{
	system("cls");
	if 		(opt[0]=='1' || opt[0]=='2')	print_game();	//prints game one last time
	else if (opt[0]=='3' || opt[0]=='4')	print_ultimate();
	if (w=='d')				//for draws
	{
		color(d_c);
		cout<<"\t------------------------------\n";
		cout<<"\t|                            |\n";
		cout<<"\t|        It's a draw!        |\n";
		cout<<"\t|                            |\n";
		cout<<"\t------------------------------\n";
		win=1;				//to exit game loop in main()
		color(m_c);
		system("pause");
	}
	else					//for winning cases
	{
		if 		(w=='X')	{	color(x_c);	}		//color changes according to player's color
		else if (w=='O')	{	color(o_c);	}
		cout<<"\t------------------------------\n";
		cout<<"\t|                            |\n";
		cout<<"\t|      Player "<<w<<" has won!     |\n";
		cout<<"\t|                            |\n";
		cout<<"\t------------------------------\n";
		win=1;
		color(m_c);
		system("pause");
	}

}

/********************************************************************************************************************************************************************************************************/
/********************************************************************************************************************************************************************************************************/
//CLASSIC MODE FUNCTIONS

void turn(int y, int x)		//rewrites array elements into big marks in classic
{
	if (current=='X')
	{
		normal[y-1][x-1]='X';	//X X
		normal[y-1][x+1]='X';	// X
								//X X
		normal[y][x]='X';

		normal[y+1][x-1]='X';
		normal[y+1][x+1]='X';
	}
	if (current=='O')
	{
		normal[y-1][x-1]='O';	//OOO
		normal[y-1][x]='O';		//OOO
		normal[y-1][x+1]='O';	//OOO

		normal[y][x-1]='O';
		normal[y][x]='O';
		normal[y][x+1]='O';

		normal[y+1][x-1]='O';
		normal[y+1][x]='O';
		normal[y+1][x+1]='O';
	}
}

/****************************************************************************************************/

void player_input(char cur)		//takes input from current player
{
		current=cur;			//sets the character to be used for turn() function
		valid=0;							
		while (valid==0)
		{
			print_game();		//prints current state of board
			if 		(cur=='X')	{	color(x_c);	}		//color changes according to player's color
			else if (cur=='O')	{	color(o_c);	}
			cout<<"\tPlayer "<<cur<<"\n";
			cout<<"\tMark box: ";
			color(m_c);
			cin>>move;
			if (cin.fail())		//flushes cin if character input
				cin.clear();	////https://stackoverflow.com/questions/1283302/user-input-of-integers-error-handling
				cin.ignore();	//user Brandon E Taylor
			switch (move)		//inputs move into visible board, prevents overwriting previous moves
			{
				case 1:	{ if(normal[10][04]=='1') {turn(10,04);	m++; valid=1;}	break; }
				case 2:	{ if(normal[10][12]=='2') {turn(10,12); m++; valid=1;}	break; }
				case 3:	{ if(normal[10][20]=='3') {turn(10,20); m++; valid=1;}	break; }
				case 4:	{ if(normal[06][04]=='4') {turn(06,04); m++; valid=1;}	break; }
				case 5:	{ if(normal[06][12]=='5') {turn(06,12); m++; valid=1;}	break; }
				case 6:	{ if(normal[06][20]=='6') {turn(06,20); m++; valid=1;}	break; }
				case 7:	{ if(normal[02][04]=='7') {turn(02,04); m++; valid=1;}	break; }
				case 8:	{ if(normal[02][12]=='8') {turn(02,12); m++; valid=1;}	break; }
				case 9:	{ if(normal[02][20]=='9') {turn(02,20); m++; valid=1;}	break; }
				case 9342: {	win=1;	valid=1;	break;	}		//exit midgame
			}
			if (valid==0)		
			{
				cout<<"\tInvalid input...";
				getch();
				system ("cls");
			}
		}
		system ("cls");			//clears screen for next player if no errors were made
}

/****************************************************************************************************/

void computer_input(int comp)	//input for computer, works with computer_think()
{
	current='O';
	print_game();			//prints current state of board
	color(o_c);
	cout<<"\tPlayer O\t[Computer]\n";
	cout<<"\tMark box: ";
	color(m_c);
	Sleep(500);				//added delay for computer move, gives illusion of the computer thinking
	switch (comp)			//inputs move into visible board
	{						//removed checks for overwriting, computer_think() does not make an error in input
		case 1:	{turn(10,04); m++;	break;}
		case 2:	{turn(10,12); m++;	break;}
		case 3:	{turn(10,20); m++;	break;}
		case 4:	{turn(06,04); m++;	break;}
		case 5:	{turn(06,12); m++;	break;}
		case 6:	{turn(06,20); m++;	break;}
		case 7:	{turn(02,04); m++;	break;}
		case 8:	{turn(02,12); m++;	break;}
		case 9:	{turn(02,20); m++;	break;}
	}
	system ("cls");			//clears screen for next player if no errors were made
}

/****************************************************************************************************/

void computer_think()		//main logic of computer
{	//checks if computer can win
	if 		((a=='1') && ((b=='O'&&c=='O')||(d=='O'&&g=='O')||(e=='O'&&i=='O')))					{computer_input(1);}
	else if ((b=='2') && ((a=='O'&&c=='O')||(e=='O'&&h=='O')))										{computer_input(2);}
	else if ((c=='3') && ((f=='O'&&i=='O')||(e=='O'&&g=='O')||(a=='O'&&b=='O')))					{computer_input(3);}
	else if ((d=='4') && ((e=='O'&&f=='O')||(a=='O'&&g=='O')))										{computer_input(4);}
	else if ((e=='5') && ((d=='O'&&f=='O')||(b=='O'&&h=='O')||(a=='O'&&i=='O')||(c=='O'&&g=='O')))	{computer_input(5);}
	else if ((f=='6') && ((d=='O'&&e=='O')||(c=='O'&&i=='O')))										{computer_input(6);}
	else if ((g=='7') && ((h=='O'&&i=='O')||(a=='O'&&d=='O')||(c=='O'&&e=='O')))					{computer_input(7);}
	else if ((h=='8') && ((g=='O'&&i=='O')||(b=='O'&&e=='O')))										{computer_input(8);}
	else if ((i=='9') && ((g=='O'&&h=='O')||(c=='O'&&f=='O')||(a=='O'&&e=='O')))					{computer_input(9);}
	//prevents opponents from winning
	else if ((a=='1') && (b==c||d==g||e==i))		{computer_input(1);}
	else if ((b=='2') && (a==c||e==h))				{computer_input(2);}
	else if ((c=='3') && (f==i||e==g||a==b))		{computer_input(3);}
	else if ((d=='4') && (e==f||a==g))				{computer_input(4);}
	else if ((e=='5') && (d==f||b==h||a==i||c==g))	{computer_input(5);}
	else if ((f=='6') && (d==e||c==i))				{computer_input(6);}
	else if ((g=='7') && (h==i||a==d||c==e))		{computer_input(7);}
	else if ((h=='8') && (g==i||b==e))				{computer_input(8);}
	else if ((i=='9') && (g==h||c==f||a==e))		{computer_input(9);}
	//for random boards, computer tries to mark corners first 
	else if (a=='1'||c=='3'||g=='7'||i=='9')
	{
		srand((unsigned)time(0)); ustodi
		valid=0;
		while (valid==0)
		{	
			com=(rand()%4)+1;
			switch (com)
			{	
				case 1:	{if (a=='1') {computer_input(1); valid=1;}	break;}
				case 2:	{if (c=='3') {computer_input(3); valid=1;}	break;}
				case 3:	{if (g=='7') {computer_input(7); valid=1;}	break;}
				case 4:	{if (i=='9') {computer_input(9); valid=1;}	break;}
			}
		}
	}
	//if corners are occupied, center 
	else if (e=='5')	{computer_input(5);}
	//last resort are edges
	else if (b=='2'||d=='4'||f=='6'||h=='8')
	{
		srand((unsigned)time(0)); 
		valid=0;
		while (valid==0)
		{	
			com=(rand()%4)+1;
			switch (com)
			{	
				case 1:	{if (b=='2') {computer_input(2); valid=1;}	break;}
				case 2:	{if (d=='4') {computer_input(4); valid=1;}	break;}
				case 3:	{if (f=='6') {computer_input(6); valid=1;}	break;}
				case 4:	{if (h=='8') {computer_input(8); valid=1;}	break;}
			}
		}	
	}
}

/****************************************************************************************************/

void winner()				//checks if a match-3 has been made or if the whole board is marked
{	
	a=normal[10][04];		//sets the array values to these values every turn
	b=normal[10][12];	
	c=normal[10][20];
	d=normal[6][04];
	e=normal[6][12];
	f=normal[6][20];
	g=normal[2][04];
	h=normal[2][12];
	i=normal[2][20];

	if (a==b && b==c)		{win_message(a);}	//rows
	else if	(d==e && e==f)	{win_message(d);}
	else if (g==h && h==i)	{win_message(g);}
	
	else if (a==d && d==g)	{win_message(a);}	//columns
	else if (b==e && e==h)	{win_message(b);}
	else if (c==f && f==i)	{win_message(c);}
	
	else if (a==e && e==i)	{win_message(e);}	//diagonals
	else if (c==e && e==g)	{win_message(e);}
	
	else if (m==9)			{win_message('d');}	//draw
}

/********************************************************************************************************************************************************************************************************/
/********************************************************************************************************************************************************************************************************/
//ULTIMATE MODE FUNCTIONS

void ultimate_turn(int y, int x, char cur_grid[13][25]);	//https://www.programiz.com/cpp-programming/passing-arrays-function
void ultimate_turn(int y, int x, char cur_grid[13][25])		//inputs turns into the arrays for ultimate
{
	if (current=='X')
	{
		cur_grid[y-1][x-1]='X';	//X X
		cur_grid[y-1][x]=' ';	// X
		cur_grid[y-1][x+1]='X';	//X X
		
		cur_grid[y][x-1]=' ';	//important for takeover(), fully replaces an O mark
		cur_grid[y][x]='X';
		cur_grid[y][x+1]=' ';
		
		cur_grid[y+1][x-1]='X';
		cur_grid[y+1][x]=' ';
		cur_grid[y+1][x+1]='X';
	}
	if (current=='O')
	{
		cur_grid[y-1][x-1]='O';	//OOO
		cur_grid[y-1][x]='O';	//OOO
		cur_grid[y-1][x+1]='O';	//OOO

		cur_grid[y][x-1]='O';
		cur_grid[y][x]='O';
		cur_grid[y][x+1]='O';

		cur_grid[y+1][x-1]='O';
		cur_grid[y+1][x]='O';
		cur_grid[y+1][x+1]='O';
	}
	if (current==dr)	//for draw conditions in a mini grid
	{
		cur_grid[y-1][x-1]=dr;	//%%%
		cur_grid[y-1][x]=dr;	//%%%
		cur_grid[y-1][x+1]=dr;	//%%%

		cur_grid[y][x-1]=dr;
		cur_grid[y][x]=dr;
		cur_grid[y][x+1]=dr;

		cur_grid[y+1][x-1]=dr;
		cur_grid[y+1][x]=dr;
		cur_grid[y+1][x+1]=dr;
	}
}

/****************************************************************************************************/

void takeover(char w, char cur_grid[13][25]);
void takeover(char w, char cur_grid[13][25])	//transforms the minigrid into a big big mark
{
	current=w;
	ultimate_turn(10,04,cur_grid);
	ultimate_turn(10,12,cur_grid);
	ultimate_turn(10,20,cur_grid);
	ultimate_turn(6,04,cur_grid);
	ultimate_turn(6,12,cur_grid);
	ultimate_turn(6,20,cur_grid);
	ultimate_turn(2,04,cur_grid);
	ultimate_turn(2,12,cur_grid);
	ultimate_turn(2,20,cur_grid);
	ultimate[grid-1]=w;							//identifies the current grid as taken
}

/****************************************************************************************************/

void mini_winner(char cur_grid[13][25]);
void mini_winner(char cur_grid[13][25])			//checks if a match-3 or a draw has occured
{	
	a=cur_grid[10][04];	//sets the array values to these values every turn
	b=cur_grid[10][12];	//used for shorthand in critical array coordinates
	c=cur_grid[10][20];
	d=cur_grid[6][04];
	e=cur_grid[6][12];
	f=cur_grid[6][20];
	g=cur_grid[2][04];
	h=cur_grid[2][12];
	i=cur_grid[2][20];

	if (a==b && b==c)		{takeover(a,cur_grid);}	//rows
	else if	(d==e && e==f)	{takeover(d,cur_grid);}
	else if (g==h && h==i)	{takeover(g,cur_grid);}
	
	else if (a==d && d==g)	{takeover(a,cur_grid);}	//columns
	else if (b==e && e==h)	{takeover(b,cur_grid);}
	else if (c==f && f==i)	{takeover(c,cur_grid);}
	
	else if (a==e && e==i)	{takeover(e,cur_grid);}	//diagonals
	else if (c==e && e==g)	{takeover(e,cur_grid);}
	
	else if (a!='1' && b!='2' && c!='3' && 
		 d!='4' && e!='5' && f!='6' && 
		 g!='7' && h!='8' && i!='9'		)	{takeover(dr,cur_grid);}	//draw
}

/****************************************************************************************************/

void player_input_mini(char cur_grid[13][25]);	
void player_input_mini(char cur_grid[13][25])				//handles player input for ultimate
{
	system ("cls");
	valid=0;							
	while (valid==0)
	{
		print_ultimate();									//prints current state of board
			if 		(current=='X')	{	color(x_c);	}		//color changes according to player's color
			else if (current=='O')	{	color(o_c);	}
			cout<<"\tPlayer "<<current<<"\n";
			cout<<"\tMark box: ";
			color(m_c);
		cin>>move;
		if (cin.fail())
			cin.clear();
			cin.ignore();
		switch (move)										//inputs move into visible board
		{			//checks first if the move is valid; no previous move has been made on that spot; also tesst if the move was a winning move
			case 1:	{ if(cur_grid[10][04]=='1') {ultimate_turn(10,04,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[0]=='1') {grid=1;} else {grid=0;}}	break; }
			case 2:	{ if(cur_grid[10][12]=='2') {ultimate_turn(10,12,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[1]=='2') {grid=2;} else {grid=0;}}	break; }
			case 3:	{ if(cur_grid[10][20]=='3') {ultimate_turn(10,20,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[2]=='3') {grid=3;} else {grid=0;}}	break; }
			case 4:	{ if(cur_grid[06][04]=='4') {ultimate_turn(06,04,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[3]=='4') {grid=4;} else {grid=0;}}	break; }
			case 5:	{ if(cur_grid[06][12]=='5') {ultimate_turn(06,12,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[4]=='5') {grid=5;} else {grid=0;}}	break; }
			case 6:	{ if(cur_grid[06][20]=='6') {ultimate_turn(06,20,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[5]=='6') {grid=6;} else {grid=0;}}	break; }
			case 7:	{ if(cur_grid[02][04]=='7') {ultimate_turn(02,04,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[6]=='7') {grid=7;} else {grid=0;}}	break; }
			case 8:	{ if(cur_grid[02][12]=='8') {ultimate_turn(02,12,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[7]=='8') {grid=8;} else {grid=0;}}	break; }
			case 9:	{ if(cur_grid[02][20]=='9') {ultimate_turn(02,20,cur_grid); valid=1; mini_winner(cur_grid); if(ultimate[8]=='9') {grid=9;} else {grid=0;}}	break; }
			case 9342: {	win=1;	valid=1;	break;	}
		}
		if (valid==0)
		{
			cout<<"\tInvalid input...";
			getch();
			system ("cls");
		}
	}	
}

/****************************************************************************************************/

void player_input_grid(char cur)
{
	current=cur;
	valid=0;
	while (valid==0)
	{
		if (grid==0)									//grid=0 whenever the previous move leads to an overtaken grid
		{												//also grid=0 at start of game
			print_ultimate();							//prints current state of board
			if 		(cur=='X')	{	color(x_c);	}		//color changes according to player's color
			else if (cur=='O')	{	color(o_c);	}
			cout<<"\tPlayer "<<cur<<"\n";
			cout<<"\t-------------\n";					//displays grid guide for big board
			cout<<"\t| 7 | 8 | 9 |\n";
			cout<<"\t-------------\n";
			cout<<"\t| 4 | 5 | 6 |\n";
			cout<<"\t-------------\n";
			cout<<"\t| 1 | 2 | 3 |\n";
			cout<<"\t-------------";
			cout<<"\tGo to grid: ";
			color(m_c);
			cin>>grid;
			if (cin.fail())		{	cin.clear();		
									cin.ignore();	}	
		}
		switch (grid)					//inputs move into visible board
		{		//checks first if the grid is open; not yet overtaken
			case 1:	{ if(ultimate[0]=='1') {player_input_mini(ultimate1); valid=1;}	break; }
			case 2:	{ if(ultimate[1]=='2') {player_input_mini(ultimate2); valid=1;}	break; }
			case 3:	{ if(ultimate[2]=='3') {player_input_mini(ultimate3); valid=1;}	break; }
			case 4:	{ if(ultimate[3]=='4') {player_input_mini(ultimate4); valid=1;}	break; }
			case 5:	{ if(ultimate[4]=='5') {player_input_mini(ultimate5); valid=1;}	break; }
			case 6:	{ if(ultimate[5]=='6') {player_input_mini(ultimate6); valid=1;}	break; }
			case 7:	{ if(ultimate[6]=='7') {player_input_mini(ultimate7); valid=1;}	break; }
			case 8:	{ if(ultimate[7]=='8') {player_input_mini(ultimate8); valid=1;}	break; }
			case 9:	{ if(ultimate[8]=='9') {player_input_mini(ultimate9); valid=1;}	break; }
			case 9342: {	win=1;	valid=1;	break;	}
		}
		if (valid==0)
		{
			cout<<"\tSelect another grid...";
			grid=0;
			getch();
			system ("cls");
		}
	}
	system ("cls");
}

/****************************************************************************************************/

void computer_input_mini(int comp, char cur_grid[13][25]);	
void computer_input_mini(int comp, char cur_grid[13][25])	//same as player_input_mini sans error checks
{
	system ("cls");						
	print_ultimate();					//prints current state of board
	color(o_c);							//color changes according to player's color
	cout<<"\tPlayer O\t[Computer]\n";
	cout<<"\tMark box: ";
	color(m_c);
	Sleep(500);
	switch (comp)						//inputs move into visible board
	{
		case 1:	{{ultimate_turn(10,04,cur_grid); mini_winner(cur_grid); if(ultimate[0]=='1') {grid=1;} else {grid=0;}}	break; }
		case 2:	{{ultimate_turn(10,12,cur_grid); mini_winner(cur_grid); if(ultimate[1]=='2') {grid=2;} else {grid=0;}}	break; }
		case 3:	{{ultimate_turn(10,20,cur_grid); mini_winner(cur_grid); if(ultimate[2]=='3') {grid=3;} else {grid=0;}}	break; }
		case 4:	{{ultimate_turn(06,04,cur_grid); mini_winner(cur_grid); if(ultimate[3]=='4') {grid=4;} else {grid=0;}}	break; }
		case 5:	{{ultimate_turn(06,12,cur_grid); mini_winner(cur_grid); if(ultimate[4]=='5') {grid=5;} else {grid=0;}}	break; }
		case 6:	{{ultimate_turn(06,20,cur_grid); mini_winner(cur_grid); if(ultimate[5]=='6') {grid=6;} else {grid=0;}}	break; }
		case 7:	{{ultimate_turn(02,04,cur_grid); mini_winner(cur_grid); if(ultimate[6]=='7') {grid=7;} else {grid=0;}}	break; }
		case 8:	{{ultimate_turn(02,12,cur_grid); mini_winner(cur_grid); if(ultimate[7]=='8') {grid=8;} else {grid=0;}}	break; }
		case 9:	{{ultimate_turn(02,20,cur_grid); mini_winner(cur_grid); if(ultimate[8]=='9') {grid=9;} else {grid=0;}}	break; }
	}
}

/****************************************************************************************************/
 
int computer_think_mini(int check_grid, char m[13][25]);	
int computer_think_mini(int check_grid, char m[13][25])		//checks if mini grid can be taken over
{	
	//if check_grid==0, it means that computer_think_grid is still checking if going to grid is going to be worth it
	win_mini=0;
	int ctmh=0;
	ctmh=0;
	//shorthand for the arrays	
	g1=m[2][04];	h1=m[2][12];	i1=m[2][20];
	d1=m[6][04];	e1=m[6][12];	f1=m[6][20];
	a1=m[10][04];	b1=m[10][12];	c1=m[10][20];
	
	//checks if computer can win mini
	if 		((a1=='1') && ((b1=='O'&&c1=='O')||(d1=='O'&&g1=='O')||(e1=='O'&&i1=='O')))						{ctmh=1;}
	else if ((b1=='2') && ((a1=='O'&&c1=='O')||(e1=='O'&&h1=='O')))											{ctmh=2;}
	else if ((c1=='3') && ((f1=='O'&&i1=='O')||(e1=='O'&&g1=='O')||(a1=='O'&&b1=='O')))						{ctmh=3;}
	else if ((d1=='4') && ((e1=='O'&&f1=='O')||(a1=='O'&&g1=='O')))											{ctmh=4;}
	else if ((e1=='5') && ((d1=='O'&&f1=='O')||(b1=='O'&&h1=='O')||(a1=='O'&&i1=='O')||(c1=='O'&&g1=='O')))	{ctmh=5;}
	else if ((f1=='6') && ((d1=='O'&&e1=='O')||(c1=='O'&&i1=='O')))											{ctmh=6;}
	else if ((g1=='7') && ((h1=='O'&&i1=='O')||(a1=='O'&&d1=='O')||(c1=='O'&&e1=='O')))						{ctmh=7;}
	else if ((h1=='8') && ((g1=='O'&&i1=='O')||(b1=='O'&&e1=='O')))											{ctmh=8;}
	else if ((i1=='9') && ((g1=='O'&&h1=='O')||(c1=='O'&&f1=='O')||(a1=='O'&&e1=='O')))						{ctmh=9;}
	
	if (check_grid!=0)	//computer only check if it can win the board if it tries to lead it there
	{
		//prevents opponents from winning
		if 		((a1=='1') && (b1==c1||d1==g1||e1==i1))			{ctmh=1;}
		else if ((b1=='2') && (a1==c1||e1==h1))					{ctmh=2;}
		else if ((c1=='3') && (f1==i1||e1==g1||a1==b1))			{ctmh=3;}
		else if ((d1=='4') && (e1==f1||a1==g1))					{ctmh=4;}
		else if ((e1=='5') && (d1==f1||b1==h1||a1==i1||c1==g1))	{ctmh=5;}
		else if ((f1=='6') && (d1==e1||c1==i1))					{ctmh=6;}
		else if ((g1=='7') && (h1==i1||a1==d1||c1==e1))			{ctmh=7;}
		else if ((h1=='8') && (g1==i1||b1==e1))					{ctmh=8;}
		else if ((i1=='9') && (g1==h1||c1==f1||a1==e1))			{ctmh=9;}
		//prioritises corners
		else if (a1=='1'||c1=='3'||g1=='7'||i1=='9')
		{
			srand((unsigned)time(0)); 
			valid=0;
			while (valid==0)
			{	
				com=(rand()%4)+1;
				switch (com)
				{	
					case 1:	{if (a1=='1') {computer_input_mini(1,m); valid=1;}	break;}
					case 2:	{if (c1=='3') {computer_input_mini(3,m); valid=1;}	break;}
					case 3:	{if (g1=='7') {computer_input_mini(7,m); valid=1;}	break;}
					case 4:	{if (i1=='9') {computer_input_mini(9,m); valid=1;}	break;}
				}
			}
		}
		//if corners are occupied, center 
		else if (e1=='5')	{computer_input_mini(5,m);}
		//last resort are edges
		else if (b1=='2'||d1=='4'||f1=='6'||h1=='8')
		{
			srand((unsigned)time(0)); 
			valid=0;
			while (valid==0)
			{	
				com=(rand()%4)+1;
				switch (com)
				{	
					case 1:	{if (b1=='2') {computer_input_mini(2,m); valid=1;}	break;}
					case 2:	{if (d1=='4') {computer_input_mini(4,m); valid=1;}	break;}
					case 3:	{if (f1=='6') {computer_input_mini(6,m); valid=1;}	break;}
					case 4:	{if (h1=='8') {computer_input_mini(8,m); valid=1;}	break;}
				}
			}	
		}
	}

	
	//decides what to do depending on checks
	if		(ctmh==1) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(1,m);}}
	else if (ctmh==2) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(2,m);}}
	else if (ctmh==3) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(3,m);}}
	else if (ctmh==4) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(4,m);}}
	else if (ctmh==5) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(5,m);}}
	else if (ctmh==6) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(6,m);}}
	else if (ctmh==7) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(7,m);}}
	else if (ctmh==8) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(8,m);}}
	else if (ctmh==9) {if (check_grid==0) {win_mini=1;} else {computer_input_mini(9,m);}}
	
	return win_mini;
}

/****************************************************************************************************/

void computer_think_big()		//main logic of computer
{
 	ug=ultimate[6];	uh=ultimate[7];	ui=ultimate[8];	//shorthand for the big board
	ud=ultimate[3];	ue=ultimate[4];	uf=ultimate[5];
	ua=ultimate[0];	ub=ultimate[1];	uc=ultimate[1];	

	//checks if computer can win big board; checks if the last mini grid needed to win can be won in the same move
	if 		((computer_think_mini(grid,ultimate1)==1) && (ua=='1') && ((ub=='O'&&uc=='O')||(ud=='O'&&ug=='O')||(ue=='O'&&ui=='O')))						{grid=1;}
	else if ((computer_think_mini(grid,ultimate2)==1) && (ub=='2') && ((ua=='O'&&uc=='O')||(ue=='O'&&uh=='O')))											{grid=2;}
	else if ((computer_think_mini(grid,ultimate3)==1) && (uc=='3') && ((uf=='O'&&ui=='O')||(ue=='O'&&ug=='O')||(ua=='O'&&ub=='O')))						{grid=3;}
	else if ((computer_think_mini(grid,ultimate4)==1) && (ud=='4') && ((ue=='O'&&uf=='O')||(ua=='O'&&ug=='O')))											{grid=4;}
	else if ((computer_think_mini(grid,ultimate5)==1) && (ue=='5') && ((ud=='O'&&uf=='O')||(ub=='O'&&uh=='O')||(ua=='O'&&ui=='O')||(uc=='O'&&ug=='O')))	{grid=5;}
	else if ((computer_think_mini(grid,ultimate6)==1) && (uf=='6') && ((ud=='O'&&ue=='O')||(uc=='O'&&ui=='O')))											{grid=6;}
	else if ((computer_think_mini(grid,ultimate7)==1) && (ug=='7') && ((uh=='O'&&ui=='O')||(ua=='O'&&ud=='O')||(uc=='O'&&ue=='O')))						{grid=7;}
	else if ((computer_think_mini(grid,ultimate8)==1) && (uh=='8') && ((ug=='O'&&ui=='O')||(ub=='O'&&ue=='O')))											{grid=8;}
	else if ((computer_think_mini(grid,ultimate9)==1) && (ui=='9') && ((ug=='O'&&uh=='O')||(uc=='O'&&uf=='O')||(ua=='O'&&ue=='O')))						{grid=9;}
	//checks if opponent could win big board; needs way to make the computer avoid that mini grid
	if 		((computer_think_mini(grid,ultimate1)==1) && (ua=='1') && (ub==uc||ud==ug||ue==ui))			{grid=1;}
	else if ((computer_think_mini(grid,ultimate2)==1) && (ub=='2') && (ua==uc||ue==uh))					{grid=2;}
	else if ((computer_think_mini(grid,ultimate3)==1) && (uc=='3') && (uf==ui||ue==ug||ua==ub))			{grid=3;}
	else if ((computer_think_mini(grid,ultimate4)==1) && (ud=='4') && (ue==uf||ua==ug))					{grid=4;}
	else if ((computer_think_mini(grid,ultimate5)==1) && (ue=='5') && (ud==uf||ub==uh||ua==ui||uc==ug))	{grid=5;}
	else if ((computer_think_mini(grid,ultimate6)==1) && (uf=='6') && (ud==ue||uc==ui))					{grid=6;}
	else if ((computer_think_mini(grid,ultimate7)==1) && (ug=='7') && (uh==ui||ua==ud||uc==ue))			{grid=7;}
	else if ((computer_think_mini(grid,ultimate8)==1) && (uh=='8') && (ug==ui||ub==ue))					{grid=8;}
	else if ((computer_think_mini(grid,ultimate9)==1) && (ui=='9') && (ug==uh||uc==uf||ua==ue))			{grid=9;}
	else if (ua=='1'||uc=='3'||ug=='7'||ui=='9')
	{
		srand((unsigned)time(0)); 
		valid=0;
		while (valid==0)
		{	
			com=(rand()%4)+1;
			switch (com)
			{	
				case 1:	{if (ua=='1') {grid=1; valid=1;}	break;}
				case 2:	{if (uc=='3') {grid=3; valid=1;}	break;}
				case 3:	{if (ug=='7') {grid=7; valid=1;}	break;}
				case 4:	{if (ui=='9') {grid=9; valid=1;}	break;}
			}
		}
	}
	//if corners are occupied, center 
	else if (ue=='5')	{grid=5;}
	//last resort are edges
	else if (ub=='2'||ud=='4'||uf=='6'||uh=='8')
	{
		srand((unsigned)time(0)); 
		valid=0;
		while (valid==0)
		{	
			com=(rand()%4)+1;
			switch (com)
			{	
				case 1:	{if (ub=='2') {grid=2; valid=1;}	break;}
				case 2:	{if (ud=='4') {grid=4; valid=1;}	break;}
				case 3:	{if (uf=='6') {grid=6; valid=1;}	break;}
				case 4:	{if (uh=='8') {grid=8; valid=1;}	break;}
			}
		}	
	}
}


/****************************************************************************************************/

void computer_input_grid()
{
	current='O';
	if (grid==0)
	{
		print_ultimate();			//prints current state of board
		color(o_c);					
		cout<<"\tPlayer O\t[Computer]\n";
		cout<<"\tGo to grid: ";
		color(m_c);
		computer_think_big();		//checks if winning is already possible
	}
	switch (grid)					//inputs move into visible board
	{
		case 1:	{{computer_think_mini(grid,ultimate1);}	break; }
		case 2:	{{computer_think_mini(grid,ultimate2);}	break; }
		case 3:	{{computer_think_mini(grid,ultimate3);}	break; }
		case 4:	{{computer_think_mini(grid,ultimate4);}	break; }
		case 5:	{{computer_think_mini(grid,ultimate5);}	break; }
		case 6:	{{computer_think_mini(grid,ultimate6);}	break; }
		case 7:	{{computer_think_mini(grid,ultimate7);}	break; }
		case 8:	{{computer_think_mini(grid,ultimate8);}	break; }
		case 9:	{{computer_think_mini(grid,ultimate9);}	break; }
	}
	system ("cls");
}

/****************************************************************************************************/

void ultimate_winner()			//checks if a match-3 has been made or if the whole board is marked
{	
	a=ultimate[0];	//sets the array values to these values every turn
	b=ultimate[1];	//used for shorthand in critical array coordinates
	c=ultimate[2];
	d=ultimate[3];
	e=ultimate[4];
	f=ultimate[5];
	g=ultimate[6];
	h=ultimate[7];
	i=ultimate[8];
	//third condition ensures that a draw cannot win the big board
	if (a==b && b==c && a!=dr)		{win_message(a);}	//rows
	else if	(d==e && e==f && d!=dr)	{win_message(d);}
	else if (g==h && h==i && g!=dr)	{win_message(g);}
	
	else if (a==d && d==g && a!=dr)	{win_message(a);}	//columns
	else if (b==e && e==h && b!=dr)	{win_message(b);}
	else if (c==f && f==i && c!=dr)	{win_message(c);}
	
	else if (a==e && e==i && e!=dr)	{win_message(e);}	//diagonals
	else if (c==e && e==g && e!=dr)	{win_message(e);}
	
	else if (a!='1' && b!='2' && c!='3' && 
			 d!='4' && e!='5' && f!='6' && 
			 g!='7' && h!='8' && i!='9'		)	{win_message('d');}	//draw
}

/********************************************************************************************************************************************************************************************************/
/********************************************************************************************************************************************************************************************************/
//MAIN FUNCTION

int main()
{
	system("Color 07");		//changes system colors

	while (opt[0]!='y' && opt[0]!='Y')
	{
		menu();
		if (strlen(opt)==1)	//error handling code
		{
			switch (opt[0])
			{	
				case '1':	//classic player v player
				{
					system("cls");
					cout<<"\n\tDecide who plays X and who plays O...\n\n";	//players should decide irl who is who
					cout<<"\tPress any key to continue...";
					getch();
					system("cls");
					order();
					if (ord>50)	//50:50 chance of who goes first
					{
						while (win==0)	//loops until win or draw
						{
							if (win==0)winner();
							if (win==0)	player_input('X');
							if (win==0)winner();
							if (win==0)	player_input('O');
						}
					}
					else 
					{
						while (win==0)
						{
							if (win==0)winner();
							if (win==0)	player_input('O');
							if (win==0)winner();
							if (win==0)	player_input('X');
						}
					}
					reset_game();	//prepares necessary variables for new game
					break;
				}
				case '2':	//classic player v computer
				{
					system("cls");
					cout<<"\n\tYou are Player X\n\n";
					cout<<"\tComputer is Player O\n\n";	
					cout<<"\tPress any key to continue...";
					getch();
					system("cls");
					order();
					if (ord>50)	//tweak to change chances of computer going first, higher values mean computer more likely to go first
					{
						while (win==0)
						{
							if (win==0)winner();
							if (win==0)	player_input('X');
							if (win==0)winner();
							if (win==0)	computer_think();
						}
					}
					else
					{
						while (win==0)
						{
							if (win==0)	winner();
							if (win==0)	computer_think();
							if (win==0)	winner();
							if (win==0)	player_input('X');
						}
					}
					reset_game();
					break;
				}
			
				case '3':	//ultimate pvp
				{
					system("cls");
					cout<<"\n\tDecide who plays X and who plays O...\n\n";	
					cout<<"\tPress any key to continue...";
					getch();
					system("cls");
					order();
					if (ord>50)
					{
						while (win==0)
						{
							if (win==0)	ultimate_winner();
							if (win==0)	player_input_grid('X');
							if (win==0)	ultimate_winner();
							if (win==0)	player_input_grid('O');	
						}
					}
					else 
					{
						while (win==0)
						{
							if (win==0)	ultimate_winner();
							if (win==0)	player_input_grid('O');
							if (win==0)	ultimate_winner();
							if (win==0)	player_input_grid('X');	
						}
					}
					reset_game();
					break;
				}
				
				case '4':	//ultimate pve
				{
					system("cls");
					cout<<"\n\tYou are Player X\n\n";
					cout<<"\tComputer is Player O\n\n";	
					cout<<"\tPress any key to continue...";
					getch();
					system("cls");
					order();
					if (ord>50)	//tweak to change chances of computer going first, higher values mean computer more likely to go first
					{
						while (win==0)
						{
							if (win==0)	ultimate_winner();
							if (win==0)	player_input_grid('X');
							if (win==0)	ultimate_winner();
							if (win==0)	computer_input_grid();	
						}
					}
					else
					{
						while (win==0)
						{
							if (win==0)	ultimate_winner();
							if (win==0)	computer_input_grid();
							if (win==0)	ultimate_winner();
							if (win==0)	player_input_grid('X');	
						}
					}
					reset_game();
					break;
				}				
				
				case '5':	//help
				{
					help();
					break;
				}

				case 'x': case 'X':
				{
					system("cls");
					color(m_c);
					cout<<"\n\tExit the game? (Y/N) ";
					cin>>opt;
					switch (opt[0])
					{
						case 'y': case 'Y':	{break;}
						case 'n': case 'N':	{break;}
						default:	
						{	
							cout<<"\tInvalid input...";	
							getch();
							break;	
						}
					}
					break;
				}

				default:
				{
					cout<<"\tInvalid input...";
					getch();
					break;
				}
			}
		}
		else {	cout<<"\tInvalid input...";	getch();	}
	}
	return 0;
}
