#include <stdio.h>
#include <iostream>
//The 2D board for our 8-puzzle in format board[x][y]
int** board;
//The output logging file. Don't worry about this one
FILE* output;

int** goal;



struct Position{
int x;
int y;
};

struct Tile {
int Heuristic;
int Moves;
int Total;
int Value;
Position goal;
};


/*
ReadBoardFile: Read board data in from a file to populate our board structure.
Arguments:
char* fname: The name of the file to read
This just reads a simple file format of a b c each line. There should be three lines.
Each of the 9 entries should go from 0-8 inclusive. If you spot a problem let us know.
Returns bool: Returns true if the file was opened and read successfuly, and false if the file could not be read
*/
bool ReadBoardFile(char* fname)
{
	FILE* file = fopen(fname, "r");
	if (file)
	{
		rewind(file);
		int a, b, c;

		board = new int*[3];
		for (int u = 0; u < 3; u++)
		{
			board[u] = new int[3];

			for (int v = 0; v < 3; v++)
			{
				board[u][v] = 0;
			}
		}

		int i = 0;
		//while (fscanf_s(file, "%d %d %d", &a, &b, &c) != EOF)
		while (fscanf(file, "%d %d %d", &a, &b, &c) != EOF)
		{
			board[0][i] = a;
			//LogCell(0, i);
		//	std::cout<<"WHYYYYYYY"<<std::endl;
		        board[1][i] = b;
			//LogCell(1,i);
			board[2][i] = c;
			//LogCell(2,i);
			i++;
		}

		fclose(file);
          //      std::cout <<"I DIDNT DO ANYTHING" <<std::endl;
		return true;
	}
	else
	{
		printf("Failed to read file...\n");
		return false;
	}
}

/*
LogCell: Prints the current cell traveled to and its value and saves the output to a file
Arguments:
int x: The x of the cell you are visiting
int y: The y of the cell you are visiting
In order for us to grade you, you must print the cell you are travelling to in your algorithm.
This function makes it easier for you to print the proper data. It also saves the data to a file.
Returns void: No values returned
*/
void LogCell(int x, int y)
{
	printf("(%d, %d): %d\n", x, y, board[x][y]);
	fprintf(output, "(%d, %d): %d\n", x, y, board[x][y]);
}

/*
SetartLogging: Opens the logging file for later writing
Arguments:
None
Pretty much just a wrapper for fopen so that we make sure you are writing your logging data to the right file.
Returns void: No values returned
*/
void StartLogging()
{
	output = fopen("log.txt", "w");
}

/*
EndLogging: Closes the logging file properly
Arguments:
None
Pretty much just a wrapper for fclose so that we make sure you close the right file.
Returns void: No values returned
*/
void EndLogging()
{
	fclose(output);
}

/*Initializing the tile array*/
void SetTiles()
{
 bool found = false;
 int value = 1;
 Tile * BoardTiles = new Tile[8];
 for(int index = 0; index< 8; index++)
 {
	BoardTiles[index].Value = value;
	value++;
        BoardTiles[index].Moves = 0;
 }

//Storing the goal state for the different values
 for(int row = 0; row<3; row++)
{
	//std::cout<<std::endl;
	for(int column =0; column < 3; column++)
	{
          BoardTiles[goal[row][column]].goal.x = row;
	  BoardTiles[goal[row][column]].goal.y = column;
	  //std::cout<<goal[row][column];
	}
}

}
/*This function sets up a board that has the goal state that can be refered back to 
throguhout the program*/
void SetGoal()
{
	int tileValue= 0;
	
	goal = new int* [3];
	for(int row=0; row < 3; row++)
	{	
		goal[row] = new int[3];
		//std::cout<<std::endl;
		for(int column=0; column < 3; column++)
		{
			goal[row][column] = tileValue;
			//std::cout << tileValue;
			tileValue++;
		}
	}
  SetTiles(); // Need to set the tiles as well
	
}

//Sees is the board is at the goal state
bool GoalState()
{
	bool equal = true;
        int row, column;
	while(equal && row < 2) // Will this stop the loop too soon? 
         {
	   for( row = 0; row< 3; row++)
      	   {
		for( column = 0; column < 3; column++)
		{
                  if(!(board[row][column] == goal[row][column]))
		    {   
    			equal = false;
			break;
		    }
		}
             if (!equal) // Need to break the second for loop to get to the while loop
		break;
	   }
	 }
        // end result of the function
	if(equal)
	return true;
	else
	return false;
}

void MoveOptions(int x, int y)
{
	std::cout<<"0 is at row:" << x << "and column: " << y<<std::endl;
  if(!GoalState()) // Board is not at goal state
  {	  
   Position * Moves =  new Position [4];
   Position Left, Right, Up, Down, Unavail;
        //The left Position
	Left.x = x-1;
        Left.y = y;
	//The right position
    	Right.x = x+1;
	Right.y = y;
	// the Up position
  	Up.x = x;
	Up.y = y+1;
	//The down position
   	Down.x =x;
	Down.y = y-1;
	// The varaiable for when a positon is unavailable
   	Unavail.x =-1;
	Unavail.y = -1;
	
        int NumMoves = 4;
	//The moves will be starting with down and then moving clockwise
   
	if(x == 0)// No up Move up
        {
	  Moves[0] = Down;
	  Moves[2] = Unavail;
	  NumMoves -1;
	}// The blank space can't move up
	if(x == 2) // No move down
	{
	 Moves[0] = Unavail; 
         Moves[2] = Up;
	 NumMoves -1;
	}
	else
	{
	Moves[0] = Down;
	Moves[2] = Up;
	}
	if(y == 0)
	{
	  Moves[1] = Unavail;
          Moves[3] = Right;
	  NumMoves -1; 
	}
	if (y == 2)
	{
	  Moves[1] = Left;
	  Moves[3] = Unavail;
	  NumMoves-1;
	}
	else
	{
	  Moves[1] = Left;	
	  Moves[3] = Right;	
	}
       }
  else // The goal state test cam back true!!
  { 
   std::cout <<"Board is at Goal State!! " <<std::endl;
  }
}

void FindZero()
{
	for(int row = 0; row< 3; row++)
	{
		for (int column = 0; column<3; column++)
		{
			if(board[row][column] == 0)
                        {
			 MoveOptions(row, column);
			 break;
			}
		}
	}
   
}

int FindTile(int vlaue)
{
 bool found  = false; //int index = 0;
 while(!found)
 {
  if(BoardTiles[index].Value == value)
  found = true;
  else
  index++;
 }
 return index;
}

int calcHeur(int currentLocx, int currentLocy, int index)
{
 //bool found = false
 int heuristic =0;//, index = 0;
 /*while(!found)
 {
  if (BoardTiles[index].Value == value)
  found = true;
  else
  index++; 
 }*/
 //Find how many tiles the value is from its goal
 if(BoardTiles[index].goal.x > currentLocx )
	heuristic = heuristic +(BoardTiles[index].goal.x - currentLocx);
 if(currentLocx > BoardTiles[index].goal.x )
 	heuristic = heuristic + (currentLocx - BoardTiles[index].goal.x);
 if(currentLocy > BoardTiles[index].goal.y)
	heuristic = heuristic + (currentLocy - BoardTiles[index].goal.y);
 if(BoardTiles[index].goal.y > currentLocy)
	heuristic = heuristic + (BoardTiles[index].goal.y - currentLocy);

return heuristic;
}

void UpdateTiles(int value, int moveIncrease)
{
 //Update the Heuristic
	//bool found = false;  
	//while(!found)
	//{
 	int index = 0; 
	bool found = false; 
	while(!found)
	 {
       	 if (BoardTiles[index].Value == value)
 	 found = true;
 	 else
 	 index++; 
 	 }


 	 for(int row =0; row<3; row++)
	 {
	  for(int column =0; column<3; column++)
	  {
		if(board[row][column] = value)
                {
		  int heur = calcHeur(row, column,index);// found = true;
		  break;
		}
	  }
	  //if(found)
	  break;
	 }
	//}
	//Updating the tiles a* search values
	BoardTiles[index].Heuristic = heur;
	BoardTiles[index].Moves += moveIncrease;
	BoardTiles[index].Total = Heuristic + Moves;
 
}

void MoveDecision(int x, int y, Position Moves[], int numMoves)
{
 
 int index = 0,availIndex =0, temp;
 Position aValue; 
 Position *availMoves = new Position [numMoves];
 while(index < 4)
{
 if(Moves[index] >= 0)
 {
   temp = FindTile(Moves[index].x, Moves[index].y);
   if (BoardTiles[temp].Heuristic > 0)
   {
    availMoves[availIndex] = Moves[index];
    availIndex++;
   } 
 }
 index++;
}

if(availIndex > 0)
{
 int swappIndex, first, second, tempOne = 0, tempTwo = 1;
 if(availIndex == 1)
 {
  swapIndex = 0;// just swapp
 }
 else
 {
  while(tempOne < availIndex && tempSecond < availIndex)
  {
   first = FindTile(availMoves[tempOne].x, availMoves[tempOne].y);
   second = FindTile(availMoves[tempTwo].x, availMoves[tempTwo].y);
   if(BoardTile[first].Total<= BoardTile[second])
    {
     swapIndex = tempOne;
     tempTwo += 2;
    }
   else
    {
      swapIndex = tempTwo;
      tempOne += 2;
    }
  }
 }
  // Swap 0 with the swappIndex
  int tempx, tempy, tempValue;
  tempValue = BoardTile(FindTile(availMoves[swapIndex].x, availMoves[swapIndex].y)).value;
  
}
else
{ 
  std::cout << "No other available moves" <<std::endl;
}
 
}

int main(int argc, char** argv)
{
	//Setup
	//-----------------------------------
	if (argc == 2)
	{
		if (!ReadBoardFile(argv[1]))
			return 2;
	}
	else
	{
		printf("No file argument given...\n");
		return 1;
	}
	StartLogging();
	//-------------------------------------
         
 	SetGoal();        
        FindZero();
	//Your code

	//std::cout<<"Or didnt" <<std::endl;
	//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------

	return 0;
}
