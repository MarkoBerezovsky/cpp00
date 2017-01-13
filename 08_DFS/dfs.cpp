#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

// TODO: Open and close times

using namespace std;

// ==============================================================================
//                         Graph representation
// ==============================================================================

/*
We use so called "Linked list representation"
 Nodes are labeled 0, 1, 2, ..., N-1
Each label x is asociated with the list of labels
 of neighbours of node labeled by x
*/

int N;  // number of nodes
int M;  // number of edges
vector<vector<int> > edge;


// ==============================================================================
//                          Basic graph I/O
// ==============================================================================

string dataPath = "D:\\Iskola\\osoby\\Grossman\\Prj\\Set06\\";

// read form console
void readGrConsole(){
	cin >> N >> M;

	edge.resize( N, vector<int>(0) );

	int n1, n2;
	for( int i = 0; i < M; i++ ) {
		cin >> n1 >> n2;
		edge[n1].push_back( n2 );  // add edge
		edge[n2].push_back( n1 );  // add edge
	}
}

void readGrFile( string fname ){
  ifstream infile( dataPath + fname );
  infile >> N >> M;

  edge.resize( N, vector<int>(0) );

	int n1, n2;
	for( int i = 0; i < M; i++ ) {
		infile >> n1 >> n2;
		edge[n1].push_back( n2 );  // add edge
		edge[n2].push_back( n1 );  // add edge
	}
  infile.close();
}


// print Graph, may help in debugging (sometimes greatly!)
void printGr(){
  for( int i = 0; i < N; i++ ){
    cout << i << " _";
    for( int j = 0; j < edge[i].size(); j++ )
      cout << " " << edge[i][j];
    cout << endl;
  }
}

// ==============================================================================
//                          Graph methods
// ==============================================================================

// ------------------------------------------------------------------------------
//                             DFS recursively
// ------------------------------------------------------------------------------

void DFS(int currNode, std::vector<bool> & visited) {
  int neigh;
  visited[currNode] = true;
  for( int j = 0; j < edge[currNode].size(); j++ ){
    neigh = edge[currNode][j];
    if( !visited[neigh] ) {
      DFS( neigh, visited );
      cout << currNode << " --> " << neigh << endl;
    }
  }
}


void DFS (int start) {
  std::vector< bool > visited( N, false );
  DFS(start, visited);

}

// ------------------------------------------------------------------------------
//                         DFS iteratively
// ------------------------------------------------------------------------------

// note that the DFS_iter tree differs from the tree produced in recursive DFS
void DFS_iter( int start ){
  std::stack< int > st;
  std::vector< bool > fresh( N, true );
  st.push( start );
  fresh[start] = false;

  int currn, neigh;
  while( !st.empty() ){
    currn = st.top(); st.pop();
    for( int j = 0; j < edge[currn].size(); j++ ){
      neigh = edge[currn][j];
      if( fresh[neigh] ){
        st.push( neigh );
        fresh[neigh] = false;
        cout << " DFS edge: " << currn << " -> " << neigh << endl;
        //printf(" BFS edge: %d -> %d\n", currn, neigh );
      }
    }
  }
}


// ==============================================================================
//                          M  A  I  N
// ==============================================================================


int main() {

  readGrFile("graph1.txt");
  printGr();
  cout << "DFS from 0: " << endl;
  DFS( 0 );

  cout << "DFS_iter from 0: " << endl;
  DFS_iter( 0 );

return 0;
}



/*
graph1.txt:

16 19
0 1
1 2
2 3
3 4
4 5
6 7
8 9
10 11
12 13
14 15
0 6
1 7
2 8
3 9
4 10
5 11
9 13
12 14
13 15

*/
