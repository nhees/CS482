#include <stdio.h>
#include <iostream>
//The 2D board for our 8-puzzle in format board[x][y]
int** board;
//The output logging file. Don't worry about this one
FILE* output;

int** goal;


struct Tile {
int Heuristic;
int Moves;
int Total;
int Value;
};

struct Position{
int x;
int y;
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

void SetGoal()
{
	//std::cout<<"maybe I did"<<std::endl;
	int tileValue= 0;
	
	goal = new int* [3];
	for(int row=0; row < 3; row++)
	{	
		goal[row] = new int[3];
		std::cout<<std::endl;
		for(int column=0; column < 3; column++)
		{
			goal[row][column] = tileValue;
			std::cout << tileValue;
			tileValue++;
		}
	}
	
}


void FindZero()
{
	for(int row = 0; row< 3; row++)
	{
		for (int column = 0; coulmn<3; column++)
		{
			if(board[row][column] == 0)
			break;
		}
	}
   
}

void MoveOptions(int x, int y)
{
   Position * Moves;
   Position Left.x = x-1;
   	    Left.y = y;
   Position Right.x = x+1;
	   Right.y = y;
   Position Up.x = x;
	    Up.y = y+1;
   Position Down.x =x;
	    AvailMove;
   int NumMoves = 4;
	if(x == 0)// No up Move up
	{
	 NumMoves - 1;
	 if(y == 0) // No move left
	  {
	    NumMoves -1;
	    Moves = new Position[2];
	    //Move Down
	    AvailMove.x = x;
	    AvailMove.y = y+1; 
	    Moves[0] = AvailMove
	    // Move Right
 
	  }
	 

	 
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

	//Your code

	//std::cout<<"Or didnt" <<std::endl;
	//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------

	return 0;
}
