#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;

//The number of vertices stored in our graph
int vertexCount = 0;
//A 2D array of edges in the format graph[vertexA][vertexB] = distance between vertexA and vertexB
int** graph;
//The output logging file. Don't worry about this one
FILE* output;

/*
AddEdge: Add an edge to the graph from vertex u to vertex v.
Arugments:
	int u: One of the vertices that form the edge
	int v: The other vertice that forms the edge
	int dist: The distance between u and v
Adds an edge to the graph from vertex u to vertex v with the given distance dist.
The graph is represented a a 2D array of integers, where each integer is a distance.
When an edge is added from u to v an edge from v to u is also saved in memory.
Returns void: No value returned
*/
void AddEdge(int u, int v, int dist)
{
	graph[u][v] = dist;
	graph[v][u] = dist;
}

/*
ReadGraphFile: Read graph data in from a file to populate our graph structure.
Arguments:
	char* fname: The name of the file to read
Reads graph data in from a file to populate our graph structure. The format of the file
defines a number of vertices at the top of the file, and edges for the graph for each
line afterwards in the format (U, V, DIST).
Returns bool: Returns true if the file was opened and read successfuly, and false if the file could not be read
*/
bool ReadGraphFile(char* fname)
{
	FILE* file = fopen(fname, "r");
	if (file)
	{
		rewind(file);
		int a, b, d;
		
		fscanf(file, "%d", &vertexCount);
		//fscanf_s(file, "%d", &vertexCount);

		graph = new int*[vertexCount];
		for (int u = 0; u < vertexCount; u++)
		{
			graph[u] = new int[vertexCount];

			for (int v = 0; v < vertexCount; v++)
			{
				graph[u][v] = 0;
			}
		}

		while (fscanf(file, "%d %d %d", &a, &b, &d) != EOF)
//		while (fscanf_s(file, "%d %d %d", &a, &b, &d) != EOF)
		{
			AddEdge(a, b, d);
		}

		fclose(file);

		return true;
	}
	else
	{
		printf("Failed to read file...\n");
		return false;
	}
}

/*
LogVertex: Prints the current vertex traveled to and saves the output to a file
Arguments:
	int vert: The vertex that you are currently visiting
In order for us to grade you, you must print the vertex you are travelling to in your algorithm.
This function makes it easier for you to print the proper data. It also saves the data to a file.
Returns void: No values returned
*/
void LogVertex(int vert)
{
	printf("%d\n", vert);
	fprintf(output, "%d\n", vert);
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


/*
FindPath: Finds the next path from the current city that hasn't already been visited.
Arguments:
	start: City that the function is trying to find a path from
	visited: array with a list of which citys have and haven't been visited.
Returns: an int representing the next city to go to*/
 
int FindPath(int start, bool visited[])
{
  
	int pathIndex = 0;
	while(visited[pathIndex] || graph[start][pathIndex] == 0 &&
		pathIndex< vertexCount)
	{
		pathIndex++;
	}
 
 visited[pathIndex] = true;
 return pathIndex;

	
}

/*DFSHelper: This is the recursive helper function for the dfs search
Arguments: 
	start: the current or starting city
	goal: the city the function is trying to find
	visited: the array that tells the function which cities have been visited or not
Returns: a  bool to let the program know if the search was successful or not*/
bool  DFSHelper(int start, int goal, bool visited [])
{
  if(start == goal)
	{
	  	cout <<" found the goal via DFS" <<endl;
		return true;
	}
  else
	{
		int nextCity = FindPath(start, visited);
		LogVertex(nextCity);
		DFSHelper(nextCity, goal, visited);	
	}
	return false; 	

}


/*
DepthFirstSearch: This is the depth first search function
Arguments: 
	start: The starting city
	goal: The city that that the function is trying to find a path to
Return: Nothing
*/
void DepthFirstSearch(int start, int goal)
{
	bool* visited = new bool[vertexCount];
	for (int index= 0; index < vertexCount; index++)
		{
			visited[index] = false;
		}
	visited[start] = true;
        
	LogVertex(start);
	DFSHelper(start,goal, visited);
	   
}




	

/*BreadthFirstSearch: this is the breadth first search function
Arguments:
	start: starting city
	goal: City the function is trying to find a path to
return: nothing*/
void BreadthFirstSearch(int start, int goal)
{
	
	bool * visited = new bool [vertexCount];
	for(int index = 0; index < vertexCount; index++)
	{
 	  visited[index] = false;
	}

  		
	queue <int> cities;
	cities.push(start);
	visited[start] = true;
	LogVertex(start);
         int CurrentCity = cities.front();
        while(!cities.empty())
	{
         
          cities.pop();
	  int newCity;
          
         for(newCity = 0; newCity < vertexCount; newCity++)
		{
		 // is it a valid path
		  if(!visited[newCity] && graph[CurrentCity][newCity] != 0)
			{
			 visited[newCity] = true;
			 LogVertex(newCity);
			 cities.push(newCity);
			 if(newCity == goal)
			   { // is it our goal?
			    cout <<" BFS was successful" <<endl;
			     break;
			   }
			}
		 
		}
        // Breaks the while loop
        if(newCity == goal)
	break;

	CurrentCity = cities.front();

	} 		

}

/*ISHelper: This is the helper function for the iterative search
Arguments: 
	start: The starting city 
	goal: The city we are trying to find a path towards
	visited: the boolean array for which cities have been visited
	index: the depth that the search is at
Return: true or false for whether or not the search was successful*/
bool ISHelper(int start, int goal,bool visited [],  int index)
{
  if(start == goal)
	{
	  	cout <<" found the goal via Iterative Searchs" <<endl;
		return true;
	}
  else
	{
		int nextCity = FindPath(start, visited);
		LogVertex(nextCity);
		if(ISHelper(nextCity, goal, visited, index-1))
			return true;	
	}
	return false; 	
}
/*ITERATIVE SEARCH FUNCTION
Arguments: 
	start: The starting city
	goal: the ending city
	maxdept: The deph limit on the search*/
void IterativeSearch(int start, int goal,int maxDepth)
{
	bool* visited = new bool[vertexCount];
	for (int index= 0; index < vertexCount; index++)
		{
			visited[index] = false;
		}
	visited[start] = true;
        
	LogVertex(start);
        for (int depthIndex = 0 ; depthIndex< maxDepth; depthIndex++)
		 if (ISHelper(start,goal, visited, depthIndex))
			break; 
                         
}

int main(int argc, char** argv)
{
	//Setup
	//-----------------------------------
	if (argc == 4)
	{
		if (!ReadGraphFile(argv[3]))
			return 2;
	}
	else
	{
		printf("No file argument given...\n");
		return 1;
	}
	StartLogging();
	//-------------------------------------

 	
        DepthFirstSearch(argv[1][0] - '0', argv[2][0] - '0');
	BreadthFirstSearch(argv[1][0] - '0', argv[2][0] - '0');
	IterativeSearch(argv[1][0]- '0', argv[2][0] - '0', 8);
        //Your code


	//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------

	return 0;
}
