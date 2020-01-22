/*
Author: Liu Lan Zheng
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 3 C
	This program makes the dwarf survive 7 days with following requirements:
		All dwarves must survive,
		Must build a contiguous fence structure of size 30 or more,
		Must collect at least 30 pumpkins,
		Must collect at least 1000 apples. 
*/
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;

/* onStart: 
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do 
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}

bool emptySpot(Dwarf &dwarf, int r, int c)//check if (r, c) is empty (no tree, no pumpkin, no dwarf, no fence at (r,c))
{
	if(dwarf.look(r, c) != PINE_TREE 
		&& dwarf.look(r, c) != APPLE_TREE 
		&& dwarf.look(r, c) != FENCE
		&& dwarf.look(r, c) != DWARF 
		&& dwarf.look(r, c) != PUMPKIN)
		return true;
	else
		return false;
} 
bool nextToEmpty(Dwarf & dwarf, int r, int c) //if is next to an empty spot
{
	if (emptySpot(dwarf, r, c+1)&& c+1<COLS)//check right side
		return true;
	else if (emptySpot(dwarf, r, c-1)&& c-1>=0 )//check left
		return true;
	else if (emptySpot(dwarf, r-1, c)&& r-1 >=0)//check bottom
		return true;     
	else if (emptySpot(dwarf, r+1, c)&& r+1<ROWS)//check up
		return true;
	else
		return false;
}

Dir emptyDirection(Dwarf & dwarf, int & r, int & c)//direction of empty spot
{
	if (emptySpot(dwarf, r, c+1) && c+1 <COLS)//check right side
		return EAST;
	else if (emptySpot(dwarf, r, c-1) && c-1 >=0)//check left
		return WEST;
	else if (emptySpot(dwarf, r-1, c) && r-1 >=0)//check bottom
		return NORTH;
	else if (emptySpot(dwarf, r+1, c) && r+1 <ROWS)//check up
		return SOUTH;
}
void newEmptySpot(Dwarf & dwarf, int & r, int & c) //dwarf will walk to the empty spot next to (r,c)
{	
	
	if(emptySpot(dwarf, r-1, c))
		r = r - 1;
	else if(emptySpot(dwarf, r+1, c))
		r = r + 1;
	else if(emptySpot(dwarf, r, c-1))
		c = c - 1;
	else if(emptySpot(dwarf, r, c+1))
		c = c + 1;
	dwarf.start_walk(r, c);
}
bool hasZombieOnMap(Dwarf & dwarf)//check if there's zombie on the map
{
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col <COLS; col++){
			if(dwarf.look(row,col)== ZOMBIE ||dwarf.look(row,col)== PUMPKIN_ZOMBIE )
				return true;
		}
	}
	return false;
}

/*************Tree funtions:*************************/
/*
bool isNextToATree(Dwarf & dwarf, int r, int c)
returns true if there is at least one tree adjacent to the location (r, c), 
that is, there is a PINE_TREE or an APPLE_TREE at (r+1, c), (r-1, c), (r, c+1), 
or (r, c-1). Otherwise, return false.*/
bool isNextToATree(Dwarf & dwarf, int r, int c)//if dwarf is next to a pine tree
{
	if (dwarf.look(r, c+1) == PINE_TREE)//check right side
		return true;
	else if (dwarf.look(r, c-1) == PINE_TREE )//check left
		return true;
	else if (dwarf.look(r-1, c) == PINE_TREE )//check bottom
		return true;     
	else if (dwarf.look(r+1, c) == PINE_TREE)//check up
		return true;
	else
		return false;
	
}
bool isNextToAnyTree(Dwarf & dwarf, int r, int c)
{
	if (dwarf.look(r, c+1) == PINE_TREE||dwarf.look(r, c+1) == APPLE_TREE)//check right side
		return true;
	else if (dwarf.look(r, c-1) == PINE_TREE ||dwarf.look(r, c-1) == APPLE_TREE)//check left
		return true;
	else if (dwarf.look(r-1, c) == PINE_TREE  ||dwarf.look(r-1, c) == APPLE_TREE)//check bottom
		return true;     
	else if (dwarf.look(r+1, c) == PINE_TREE ||dwarf.look(r+1, c) == APPLE_TREE)//check up
		return true;
	else
		return false;
	
}
Dir choppingDirection(Dwarf & dwarf, int r, int c)//direction of chopping pine tree 
{
	if (dwarf.look(r, c+1) == PINE_TREE )//check right side
		return EAST;
	else if (dwarf.look(r, c-1) == PINE_TREE )//check left
		return WEST;
	else if (dwarf.look(r-1, c) == PINE_TREE)//check bottom
		return NORTH;
	else if (dwarf.look(r+1, c) == PINE_TREE)//check up
		return SOUTH;
	
}
Dir choppingDirectionAnyTree(Dwarf & dwarf, int r, int c)//direction of chopping pine tree and apple tree
{
	if (dwarf.look(r, c+1) == PINE_TREE||dwarf.look(r, c+1) == APPLE_TREE )//check right side
		return EAST;
	else if (dwarf.look(r, c-1) == PINE_TREE||dwarf.look(r, c-1) == APPLE_TREE) //check left
		return WEST;
	else if (dwarf.look(r-1, c) == PINE_TREE ||dwarf.look(r-1, c) == APPLE_TREE)//check bottom
		return NORTH;
	else if (dwarf.look(r+1, c) == PINE_TREE ||dwarf.look(r+1, c) == APPLE_TREE)//check up
		return SOUTH;
	
}
bool treeWithinRadius(Dwarf & dwarf, int  & r, int & c, int radius)//check if there's a pine tree within radius
{
	for(int row = r - radius ; row <= r + radius; row++){
		for (int col = c - radius; col <= c + radius; col++){
			if(isNextToATree(dwarf, row, col)&&emptySpot(dwarf, row, col)){
				r = row;
				c = col;
				return true;
			}
		}
	}
	return false;
}

bool anyTreeWithinRadius(Dwarf & dwarf, int  & r, int & c, int radius)//check if there's a tree (pine and apple ) within radius
{
	for(int row = r - radius ; row <= r + radius; row++){
		for (int col = c - radius; col <= c + radius; col++){
			if(isNextToAnyTree(dwarf, row, col)&& emptySpot(dwarf, row, col)){
				r = row;
				c = col;
				return true;
			}
		}
	}
	return false;
} 

void choppingTreeAnyTree(Dwarf & dwarf, int radius, int r, int  c, ostream &log) //chopping any tree (pine and apple) with a starting position r, c
{
	while((r + radius <MAX_ROWS) ||(r - radius >= 0 )|| (c + radius < MAX_COLS) ||( c - radius >= 0))//(r < MAX_ROWS  && c < MAX_COLS)
	{	
		
		if(isNextToAnyTree(dwarf, r, c)){
			log << "Found a tree -- chop" << endl;
			dwarf.start_chop(choppingDirectionAnyTree(dwarf, r, c));
			return;
		}
		else if (anyTreeWithinRadius(dwarf, r, c, radius)){
			log << "Walk to " << r << " " << c << endl;
			dwarf.start_walk(r, c);
		}
		else
			radius++;
	}

	r = rand() % ROWS;
	c = rand() % COLS;
	log << "Walk to " << r << " " << c << endl;
	dwarf.start_walk(r, c);
}
void choppingTree(Dwarf & dwarf, int radius, int r, int  c, ostream &log) //chopping pine tree with a starting position r, c
{
	while((r + radius <MAX_ROWS) ||(r - radius >= 0 )|| (c + radius <MAX_COLS) ||( c - radius >= 0))//(r < MAX_ROWS  && c < MAX_COLS)
	{	
		
		if(isNextToATree(dwarf, r, c)){
			log << "Found a tree -- chop" << endl;
			dwarf.start_chop(choppingDirection(dwarf, r, c));
			return;
		}
		else if (treeWithinRadius(dwarf, r, c, radius)){
			log << "Walk to " << r << " " << c << endl;
			dwarf.start_walk(r, c);
		}
		else
			radius++;
	}

	r = rand() % ROWS;
	c = rand() % COLS;
	log << "Walk to " << r << " " << c << endl;
	dwarf.start_walk(r, c);
}
bool thereIsPineTree(Dwarf & dwarf)//check if there's pine tree
{
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col <COLS; col++){
			if(dwarf.look(row,col)== PINE_TREE)
				return true;
		}
	}
	return false;
}
/***********************APPLE****************/


bool thereIsAppleTree(Dwarf & dwarf)//check if there's apple tree
{
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col <COLS; col++){
			if(dwarf.look(row,col)== APPLE_TREE)
				return true;
		}
	}
	return false;
}


void pickApple(Dwarf & dwarf, int r, int c)//pick up apple
{
	if(dwarf.look(r+1,c) == APPLE_TREE&& r+1 <ROWS)
		dwarf.start_pick(SOUTH);
	else if(dwarf.look(r-1,c) == APPLE_TREE&& r-1 >=0)
		dwarf.start_pick(NORTH);
	else if(dwarf.look(r,c+1) == APPLE_TREE&& c+1 <COLS)
		dwarf.start_pick(EAST);
	else if(dwarf.look(r,c-1) == APPLE_TREE&& c-1>=0)
		dwarf.start_pick(WEST);
}
bool nextToAppleTree(Dwarf& dwarf, int r, int c)//check if there's an apple tree around 
{
	if(dwarf.look(r-1,c) == APPLE_TREE ) 
		return true;
	else if(dwarf.look(r+1,c) == APPLE_TREE )
		return true;
	else if(dwarf.look(r,c-1) == APPLE_TREE)
		return true;
	else if(dwarf.look(r,c+1) == APPLE_TREE)
		return true;
	else	
		return false;
}
Dir appleDirection(Dwarf & dwarf, int r, int c)//direction of apple tree
{
	if (dwarf.look(r, c+1) == APPLE_TREE )//check right side
		return EAST;
	else if (dwarf.look(r, c-1) == APPLE_TREE) //check left
		return WEST;
	else if (dwarf.look(r-1, c) == APPLE_TREE)//check bottom
		return NORTH;
	else if (dwarf.look(r+1, c) == APPLE_TREE)//check up
		return SOUTH;
	
}
bool appleTreeWithinRadius(Dwarf & dwarf, int &r, int &c, int& radius)//find apple tree within radius
{
	for(int row = r - radius ; row <= r + radius; row++){
		for (int col = c - radius; col <= c + radius; col++){
			if(nextToAppleTree(dwarf, row, col)&& emptySpot(dwarf, row, col)){
				r = row;
				c = col;
				return true;
			}
		}
	}
	return false;
} 

void pickNearestApple(Dwarf & dwarf, int radius, int r, int  c, ostream &log) //pick up the nearst pumpkin with a starting position r, c
{
	while((r + radius <MAX_ROWS) ||(r - radius >= 0 )|| (c + radius < MAX_COLS) ||( c - radius >= 0))//(r < MAX_ROWS  && c < MAX_COLS)
	{	
		
		if(nextToAppleTree(dwarf, r, c)){
			dwarf.start_pick(appleDirection(dwarf, r, c));
			return;
		}
		else if(appleTreeWithinRadius(dwarf, r, c, radius)){
			dwarf.start_walk(r, c);
		}
		else
			radius++;
	}

	r = rand() % ROWS;
	c = rand() % COLS;
	dwarf.start_walk(r, c);
}



/******************PUMPKIN FUNCTIONS*****************/



bool isNextToPumpkin(Dwarf & dwarf, int r, int c)//check if dwarf is next to a pumpkin
{
	if (dwarf.look(r, c+1) == PUMPKIN)//check right side
		return true;
	else if (dwarf.look(r, c-1) == PUMPKIN )//check left
		return true;
	else if (dwarf.look(r-1, c) == PUMPKIN)//check bottom
		return true;     
	else if (dwarf.look(r+1, c) == PUMPKIN)//check up
		return true;
	else
		return false;
}
void pickPumpkin(Dwarf & dwarf, int r, int c) //if there's a pumpkin around them, collect them
{
	if(dwarf.look(r+1,c) == PUMPKIN && r+1 <ROWS)
		dwarf.start_pick(SOUTH);
	else if(dwarf.look(r-1,c) == PUMPKIN&& r-1 >=0)
		dwarf.start_pick(NORTH);
	else if(dwarf.look(r,c+1) == PUMPKIN&& c+1 <COLS)
		dwarf.start_pick(EAST);
	else if(dwarf.look(r,c-1) == PUMPKIN&& c-1>=0)
		dwarf.start_pick(WEST);
}
bool thereIsPumpkin(Dwarf & dwarf)//check if there's pumpkin on the map
{
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col <COLS; col++){
			if(dwarf.look(row,col)== PUMPKIN)
				return true;
		}
	}
	return false;
}

Dir pumpkinDirection(Dwarf & dwarf, int r, int c)//return the direction of pumpkin
{
	if (dwarf.look(r, c+1) == PUMPKIN)//check right side
		return EAST;
	else if (dwarf.look(r, c-1) == PUMPKIN)//check left
		return WEST;
	else if (dwarf.look(r-1, c) == PUMPKIN)//check bottom
		return NORTH;
	else if (dwarf.look(r+1, c) == PUMPKIN)//check up
		return SOUTH;
}
void pickNearestPumpkin(Dwarf & dwarf, int radius, int r, int  c, ostream &log) //pick up the nearst pumpkin with a starting position r, c
{
	if(isNextToPumpkin(dwarf, r, c))
		dwarf.start_pick(pumpkinDirection(dwarf, r, c));
	else{
		for(int row = 0; row < ROWS; row++){//move next to the apple tree
			for(int col = 0; col <COLS; col++){
				if(dwarf.look(row,col)== PUMPKIN){
					if(emptySpot(dwarf, row+1, col)&& row+1 < ROWS)
						dwarf.start_walk(row+1, col);
					else if(emptySpot(dwarf, row-1, col)&& row-1 >=0)
						dwarf.start_walk(row-1, col);
					else if(emptySpot(dwarf, row, col+1)&& col+1 <COLS)
						dwarf.start_walk(row, col+1);
					else if(emptySpot(dwarf, row, col-1)&& col-1 >=0)
						dwarf.start_walk(row, col-1);
						
				}
			}
		}
	}
}

/***********FENCE FUNCTION*************/


void walkToFence(Dwarf & dwarf)//walk to next to the fence
{
	int fenceR, fenceC;
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col <COLS; col++){
			if(dwarf.look(row, col) == FENCE){
				fenceC = col;
				fenceR = row;
			}
				
		}
	}
	newEmptySpot(dwarf, fenceR, fenceC);
}

bool hasFence(Dwarf &dwarf, int &r, int&c)//check if there's a fence next to r,c
{	
	if(dwarf.look(r-1,c) == FENCE) 
		return true;
	else if(dwarf.look(r+1,c) == FENCE)
		return true;
	else if(dwarf.look(r,c-1) == FENCE)
		return true;
	else if(dwarf.look(r,c+1) == FENCE)
		return true;
	else	
		return false;
}
void dwarfWalking(Dwarf &dwarf, int & r, int & c)//dwarf will walk to a position next to the fence.
{
	
	if(dwarf.look(r-1,c) == FENCE) //update (r,c) to the position of the fence
		r = r - 1;
	else if(dwarf.look(r+1,c) == FENCE)
		r = r + 1;
	else if(dwarf.look(r,c-1) == FENCE)
		c = c - 1;
	else if(dwarf.look(r,c+1) == FENCE)
		c = c + 1;
	
	if(emptySpot(dwarf, r-1, c)){ //check if there's empty spot around(r,c)
		r = r - 1;					//replace (r,c) with empty spot (r,c)
		newEmptySpot(dwarf, r, c);}//dwarf will walk to next to the [empty spot next to the fence]
	else if(emptySpot(dwarf, r+1, c)){
		r = r + 1;
		newEmptySpot(dwarf, r, c);}
	else if(emptySpot(dwarf, r, c-1)){
		c = c - 1;
		newEmptySpot(dwarf, r, c);}
	else if(emptySpot(dwarf, r, c+1)){
		c = c + 1;
		newEmptySpot(dwarf, r, c);}
	else
		walkToFence(dwarf);
}
bool noFence(Dwarf & dwarf)//return true if there's no fence on the map
{
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col <COLS; col++){
			if(dwarf.look(row, col) == FENCE)
				return false;
		}
	}
	return true;
}
void buildFence(Dwarf & dwarf, int r, int c) //check if current spot is good to build fence
{
	if(dwarf.look(r+2 , c) == FENCE && emptySpot(dwarf, r+1, c) && r+2 <ROWS)
		dwarf.start_build(SOUTH);
	else if(dwarf.look(r-2 , c) == FENCE && emptySpot(dwarf, r-1, c) && r-2 >=0)
		dwarf.start_build(NORTH);
	else if(dwarf.look(r, c+2) == FENCE && emptySpot(dwarf, r, c+1) && c+2 <COLS)
		dwarf.start_build(EAST);
	else if(dwarf.look(r, c-2) == FENCE && emptySpot(dwarf, r, c-1) && c-2 >=0)
		dwarf.start_build(WEST);
	else if(dwarf.look(r+1, c+1) == FENCE && emptySpot(dwarf, r+1, c) && r+1 <ROWS && c+1<COLS)
		dwarf.start_build(SOUTH);
	else if(dwarf.look(r+1, c+1) == FENCE && emptySpot(dwarf, r, c+1) && r+1 <ROWS && c+1<COLS)
		dwarf.start_build(EAST);
	else if(dwarf.look(r+1, c-1) == FENCE && emptySpot(dwarf, r+1, c) && r+1 <ROWS && c-1>=0)
		dwarf.start_build(SOUTH);
	else if(dwarf.look(r+1, c-1) == FENCE && emptySpot(dwarf, r, c-1) && r+1 <ROWS && c-1>=0)
		dwarf.start_build(WEST);
	else if(dwarf.look(r-1, c+1) == FENCE && emptySpot(dwarf, r-1, c) && r-1 >0 && c+1<COLS)
		dwarf.start_build(NORTH);
	else if(dwarf.look(r-1, c+1) == FENCE && emptySpot(dwarf, r, c+1) && r-1 >=0 && c+1<COLS)
		dwarf.start_build(EAST);
	else if(dwarf.look(r-1, c-1) == FENCE && emptySpot(dwarf, r-1, c) && r-1 >=0 && c-1>=0)
		dwarf.start_build(NORTH);
	else if(dwarf.look(r-1, c-1) == FENCE && emptySpot(dwarf, r, c-1) && r-1 >=0 && c-1>=0)
		dwarf.start_build(WEST);
}
void buildFenceWhileChoppingTree(Dwarf &dwarf, int lumber, ostream &log, int r, int c, int radius)//build fence next to each other while chopping tree
{
		if(thereIsPumpkin(dwarf) && dwarf.name()<2)
			pickNearestPumpkin(dwarf, radius, r, c, log);
		
		buildFence(dwarf, r, c); 
		if(noFence(dwarf)&& dwarf.name()==2){//check if there's 0 fence on the map
			dwarf.start_build(emptyDirection(dwarf, r, c));}//build first fence
		else if(!hasFence(dwarf, r, c))//if dwarf is not next to a fence
			walkToFence(dwarf);//check for the location of the fence and walk there	
		else if(isNextToAnyTree(dwarf, r, c))
			dwarf.start_chop(choppingDirectionAnyTree(dwarf, r, c));
		else if(isNextToPumpkin(dwarf, r, c))
			pickPumpkin(dwarf, r, c);
		else if(c ==COLS || r == ROWS)
			dwarfWalking(dwarf, r, c);
		else if(hasFence(dwarf, r, c)){//if it's next to a fence
			if (emptySpot(dwarf, r+1, c) && r+1 <ROWS)
				dwarf.start_walk(r+1, c);
			else if(emptySpot(dwarf, r-1, c) && r-1 >=0)
				dwarf.start_walk(r-1, c);
			else if(emptySpot(dwarf, r, c-1) && c-1 >=0)
				dwarf.start_walk(r, c-1);
			else if(emptySpot(dwarf, r, c+1)&& c+1 <COLS)
				dwarf.start_walk(r, c+1);
			else
				dwarfWalking(dwarf, r, c);//dwarf will walk next to the fence
		}
	
}
bool onlyOneFence(Dwarf& dwarf, int & fenceR, int & fenceC)//check if there's only one fence on the map
{
	int n = 0;
	for(int row = 0; row < ROWS; row++){
		for(int col = 0; col <COLS; col++){
			if(dwarf.look(row, col) == FENCE){
				fenceR = row;
				fenceC = col;
				n++;
			}
		}
	}
	if(n ==1){return true;}
	else {return false;}
}


/***********ACTION CALLED****************/


/* onAction: 
A procedure called each time an idle dwarf is choosing 
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */	

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();
	int radius = 1;
	int lumber = dwarf.lumber();
	//SPECIAL DAY 7
	if(day==7){
		if(hours>=6 && hours< 10&& hasFence(dwarf, r,c)&&!hasZombieOnMap(dwarf)){//chop the fence around them, let the dwarves come out
			if(dwarf.look(r+1,c) == FENCE && r+1 <ROWS)
				dwarf.start_chop(SOUTH);
			else if(dwarf.look(r-1,c) == FENCE && r-1 >=0)
				dwarf.start_chop(NORTH);
			else if(dwarf.look(r,c+1) == FENCE && c+1 < COLS)
				dwarf.start_chop(EAST);
			else if(dwarf.look(r,c-1) == FENCE && c-1 >=0)
				dwarf.start_chop(WEST);
		}
		
		else if(hours>=10&& hours <20 && lumber>NUM *20&& dwarf.name()>=0)//build fences
			buildFenceWhileChoppingTree(dwarf, lumber, log, r, c,  radius);
		else if(hours>=6 && hours <20 && thereIsPumpkin(dwarf))
			pickNearestPumpkin(dwarf, radius, r, c,log);
		else if(hours>=6 && hours <16)
			pickNearestApple(dwarf, radius, r, c, log);
		else if(hours>=16&& hours<18){
			if(!hasFence(dwarf, r, c)){//if dwarf is not next to a fence
				for(int row = 0; row < ROWS; row++){
					for(int col= 0; col  <COLS; col ++){
						if(dwarf.look(row,col) == FENCE){
							if (emptySpot(dwarf, row+1, col) && row+1 <ROWS)
								dwarf.start_walk(r+1, c);
							else if(emptySpot(dwarf, row-1, col) && row-1 >=0)
								dwarf.start_walk(row-1, col);
							else if(emptySpot(dwarf, row, col-1) && col-1 >=0)
								dwarf.start_walk(row, col-1);
							else if(emptySpot(dwarf, row, col+1)&& col+1 <COLS)
								dwarf.start_walk(row, col+1);
						}
					}
				}
			}
		}
		else if(hours>=18){
			if(isNextToPumpkin(dwarf, r, c))
				pickPumpkin(dwarf, r, c);
			else if(emptySpot(dwarf, r, c+1)&& c+1 <COLS)// build fence around them
				dwarf.start_build(EAST);
			else if(emptySpot(dwarf, r, c-1)&& c-1 >=0)
				dwarf.start_build(WEST);
			else if(emptySpot(dwarf, r-1, c)&& r-1 >=0)
				dwarf.start_build(NORTH);
			else if(emptySpot(dwarf, r+1, c)&& r+1 <ROWS)
				dwarf.start_build(SOUTH);
		}
	
		
	}
	//regular day: day 1,2,3,4,5,6
	else if(hours>=6 && hours< 15 && minutes >=1 && hasFence(dwarf, r,c)&& !hasZombieOnMap(dwarf)){//chop the fence around them, let the dwarves come out
		if(dwarf.look(r+1,c) == FENCE && r+1 <ROWS)
			dwarf.start_chop(SOUTH);
		else if(dwarf.look(r-1,c) == FENCE && r-1 >=0)
			dwarf.start_chop(NORTH);
		else if(dwarf.look(r,c+1) == FENCE && c+1 < COLS)
			dwarf.start_chop(EAST);
		else if(dwarf.look(r,c-1) == FENCE && c-1 >=0)
			dwarf.start_chop(WEST);
	}
	else if(thereIsPumpkin(dwarf) && hours>=6 && hours<21&& dwarf.name()==0) //if there's at least one pumpkin on the map
		 pickNearestPumpkin(dwarf, radius, r, c,log);
	else if(hours >= 6 && hours<20 && thereIsPineTree(dwarf)&& dwarf.name()>2)//chop as many tree as possible between 15 and 18
		choppingTree(dwarf, radius, r, c, log);
	else if (hours >= 6 && hours <20)//go to nearest apple tree and pick apple
		 pickNearestApple(dwarf, radius, r,  c, log);
	else if((hours>=20||hours<6) && nextToEmpty(dwarf, r, c)){
	//	if(isNextToATree(dwarf, r, c))
	//		choppingTree(dwarf, radius,  r,  c,log);
		if(emptySpot(dwarf, r, c+1) && c+1 <COLS)// build fence around them
			dwarf.start_build(EAST);
		else if(emptySpot(dwarf, r, c-1)&& c-1 >=0)
			dwarf.start_build(WEST);
		else if(emptySpot(dwarf, r-1, c)&& r-1 >=0)
			dwarf.start_build(NORTH);
		else if(emptySpot(dwarf, r+1, c)&& r+1 <ROWS)
			dwarf.start_build(SOUTH);
	}
	else if(nextToAppleTree(dwarf, r,c) &&( hours >=21 || hours <6)&& hasFence(dwarf, r,c))//pick up apple at night
		pickApple(dwarf, r, c);
	
}
