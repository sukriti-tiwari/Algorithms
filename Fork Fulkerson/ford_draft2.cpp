/* =========== ALGORITHMS PROGRAM 3 - FORD FULKERSON BIPARTITE MATCHING MAXIMUM FLOW =================
AUTHOR: SUKRITI TIWARI
------------------------------------------------------------------------------------------
Classes in file:
1. Graph : Contanins functions to define the given Graph as an adjacency matrix, add edges to it, print it and delete it.
2. InputData : Reads data from file and stores into Graph variables
3. FordFulkerson : Contains two functions - One recursive function 'BipartiteMatching' and 'maxBPM' to show the final maximum matchings result

*/

// ---------------------HEADER FILES------------------------------
#include <iostream> 
#include <string.h> 
#include <stdio.h>
#include <list>
#include <fstream>


using namespace std; 


#define MAX 100
#define LEFTSET 5
#define RIGHTSET 5



// ===============================CLASS "GRAPH" DEFINED==================================
class Graph {
   public:
  
  bool **G, **Gf;
  int numVertices;


  
  // Initialize the adjacency matrix to zero
  Graph(int numVertices) {
    this->numVertices = numVertices;

    G = new bool*[this->numVertices+1];

    for (int i = 1; i <=this->numVertices; i++) {
      G[i] = new bool[this->numVertices];
      for (int j = 1; j <=this->numVertices; j++)

        G[i][j] = false;
    }
  }


  
  // Add edges
  void addEdge(int i, int j) {
    G[i][j] = true;
    G[j][i] = true;
  }

  // Print the martix
  void toString() {
    for (int i = 1; i < numVertices+1; i++) {
      cout << i << " : ";
      for (int j = 1; j < numVertices+1; j++)
        cout << G[i][j] << " ";
      cout << "\n";
    }
  }

 //Destructor
  ~Graph() {
    for (int i = 0; i < numVertices+1; i++)
      delete[] G[i];
    delete[] G;
  }
};



// ===============================CLASS "InputData" DEFINED==================================
class InputData
{
    //--------------------------MEMBER VARIABLES DEFINED---------------------------
    public:
    ifstream infile;
    int numEdges, left, right, numVertices;
    string peoplenames[MAX];
    Graph *obj;

    //------------------------READ DATA FROM FILE-------------------------------
    void readdata()
    {
        int i,j;
        infile.open("program3data.txt");

        //---------check if file opens or not-------------------
        if (infile.fail())
        {
            cout << "Error reading file!";
        }

        // -------------if file opens, start reading data--------------
        else
        {

            // read number of vertices/nodes
            
            infile >> numVertices;
            obj = new Graph(numVertices);

            //read names of people
            for ( i = 1; i <= numVertices; i++)
            {
                infile >> peoplenames[i];

            }

            // read number of edges
            infile >> numEdges;


            //store edges in adjecency matrix
            for(j = 1; j <= numEdges; j++){
                infile >> left >> right;
                obj->addEdge(left, right);
            }  

        }
        // Close the file after reading
        infile.close();
    }

    // Function to access printing of Graph
    void toString(){
      obj->toString();
    }

};


// ===============================CLASS "FordFulkerson" DEFINED==================================

class FordFulkerson
{
  //---------------------MEMBER VARIABLES DEFINED--------------------------------
  public:
  bool *visited;
  int *matchR;
  int N;
  int M;
  int size;

  //Constructor for initialization
  FordFulkerson(int leftSet, int rightSet){
    N = leftSet;
    M = rightSet;
    size = leftSet;
    visited = new bool[N+1];
    matchR =  new int[N+1];
  }


  /* Let the vertices for the left set be "u" and those for the right set be "v"
    A Depth First Search based recursive function that returns true if a matching for vertex 'u' is possible
    Pre-conditions: Data should be correctly read from the file and stored into Graph variables.
                    Input variables are - the residual graph, the current left node, the original input graph.
    Post-conditions: Return true if a matching between left node and right node exists. 
  */

  bool BipartiteMatching(Graph *bpGraph, int u, InputData &data) 
  { 
      // Try to connect every right node one by one 
      for (int v = N+1; v <=N+M; v++) 
      {
          //If the right node has not been visited
          if (bpGraph->G[u][v] && !visited[v]) 
          { 
              // Mark v as visited 
              visited[v] = true;
    
              /* If 'v' is not connected to 'u' OR previously connected 'u' to 'v' (which is matchR[v]) has an alternative available. 
              Since 'v' is marked as visited in the above line, matchR[v] in the following recursive call will not get connected to 'v' again */
              if (matchR[v] < 0 || BipartiteMatching(bpGraph, matchR[v], data)) 
              { 
                  matchR[v] = u;
                  matchR[u] = v;
                  return true; 
              } 
          } 
      } 
      return false; 
  } 
    
  /* Returns maximum number of matchings from LEFTSET to RIGHTSET. Recursively calls Bipartite matching function.
  Pre-conditions: Input the level graph and original input data
  Post-conditions: Displays result with names of nodes - stored in an array with 1-based indexing
  */
  int maxBPM(Graph *bpGraph, InputData &data) 
  { 
      /* An array to keep track of left nodes connected to right nodes. The value of matchR[i] is the  
      left node assigned to a right node, the value -1 indicates no node is assigned. */
    
      // Initially all right nodes are available 
      for (int temp = 1; temp <=N+M; temp++) 
      {
        matchR[temp] = -1;
      }

      // Count of assigned right nodes to left nodes
      int result = 0;  
      for (int u = 1; u <=M; u++) 
      { 
          // Mark all right nodes as not visited  
          for (int temp = 1; temp <=M+N; temp++) 
          {
            visited[temp] = false;
          }

          // Find if 'u' can be connected to 'v' through recursion
          if (BipartiteMatching(bpGraph, u, data)) 
              result++; 
      }

      //Output names of final matchings
      for (int temp = 1; temp <=N; temp++) 
          {
            if(matchR[temp]!=-1)
              cout<<data.peoplenames[temp]<<"/"<<data.peoplenames[matchR[temp]]<<"\n";
          }
      return result; 
  } 
  
};


// -----------------------------------MAIN--------------------------------------------

int main() 
{ 
    InputData read;
    read.readdata();

    //Call constructor
    FordFulkerson algo(read.numVertices/2,read.numVertices/2);
    int matches = algo.maxBipartiteMatching(read.obj,read);
    cout<<matches<<" Total Matches\n";
    return 0; 

    //--------------------end of program----------------------------------------

} 
