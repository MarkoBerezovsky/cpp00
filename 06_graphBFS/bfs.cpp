/*
Example methods presented here are based on BFS.
All methods work in O(|E|) time,
however, they are a mere concept illustration
a therefore might be far from optimized.
In these examples, we consider the graph to be undirected,
however, the methods are applicable to directed graphs as well.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>


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

// your data path is probably different:
string dataPath = "D:\\Iskola\\osoby\\Grossman\\Prj\\Set06\\";


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
//                             BFS
// ------------------------------------------------------------------------------


void BFS( int start ){
  std::queue< int > q;
  std::vector< bool > fresh( N, true );
  q.push( start );
  fresh[start] = false;

  int currn, neigh;
  while( !q.empty() ){
    currn = q.front(); q.pop();
    for( int j = 0; j < edge[currn].size(); j++ ){
      neigh = edge[currn][j];
      if( fresh[neigh] ){
        q.push( neigh );
        fresh[neigh] = false;
        cout << " BFS edge: " << currn << " -> " << neigh << endl;
        //printf(" BFS edge: %d -> %d\n", currn, neigh );
      }
    }
  }
}

// ------------------------------------------------------------------------------
//                         Check connectedness
// ------------------------------------------------------------------------------

bool isConnected(){
/**/  int start = 0;   // change #1
  std::queue< int > q;
  std::vector< bool > fresh( N, true );
  q.push( start );
  fresh[start] = false;

  int currn, neigh;
  while( !q.empty() ){
    currn = q.front(); q.pop();
    for( int j = 0; j < edge[currn].size(); j++ ){
      neigh = edge[currn][j];
      if( fresh[neigh] ){
        q.push( neigh );
        fresh[neigh] = false;
      }
    }
  }

/**/  // change #2
  for( int i = 0; i < N; i++ )
    if( fresh[i] ) return false;
  return true;
}

// ------------------------------------------------------------------------------
//                         Check tree
// ------------------------------------------------------------------------------

bool isTree(){
/**/  int start = 0;   // change #1
  std::queue< int > q;
/**/  std::vector< bool > pred( N, -1 ); // change #2
  q.push( start );

  int currn, neigh;
  while( !q.empty() ){
    currn = q.front(); q.pop();
    for( int j = 0; j < edge[currn].size(); j++ ){
      neigh = edge[currn][j];
/**/    if( pred[neigh] == -1 ){  // change #3, formal, is neigh fresh?
        q.push( neigh );
        pred[neigh] = currn;
      }
/**/  else if( neigh != pred[currn] ) return false; // change #4
    }
  }

/**/  return true;  // change #5
}

// ------------------------------------------------------------------------------
//                     All distances from a node
// ------------------------------------------------------------------------------

void distancesFrom( int start ){
  std::queue< int > q;
  std::vector< bool > fresh( N, true );
/**/  std::vector< int > dist( N, N+1 );  // change #1

  q.push( start );
  fresh[start] = false;
/**/  dist[start] = 0; // change #2

  int currn, neigh;
  while( !q.empty() ){
    currn = q.front(); q.pop();
    for( int j = 0; j < edge[currn].size(); j++ ){
      neigh = edge[currn][j];
 /**/ dist[neigh] = min(dist[neigh], 1+dist[currn]); // change #3
      if( fresh[neigh] ){
        q.push( neigh );
        fresh[neigh] = false;
      }
    }
  }

 /**/ // change #4
  for( int i = 0; i < N; i++ )
    cout << "dist("<< start << " " << i << ") = " << dist[i] << endl;
    //printf( "dist(%d %d) = %d\n", start, i, dist[i]);
}


// ------------------------------------------------------------------------------
//                     Distance between two nodes
// ------------------------------------------------------------------------------


int distanceFromTo( int start, int target ){
  std::queue< int > q;
  std::vector< bool > fresh( N, true );
/**/  std::vector< int > dist( N, N+1 );  // change #1

  q.push( start );
  fresh[start] = false;
/**/  dist[start] = 0; // change #2

  int currn, neigh;
  while( !q.empty() ){
    currn = q.front(); q.pop();
    for( int j = 0; j < edge[currn].size(); j++ ){
      neigh = edge[currn][j];
/**/  dist[neigh] = min(dist[neigh], 1+dist[currn]); // change #3
/**/  if( neigh == target ) return dist[neigh]; // change #4
      if( fresh[neigh] ){
        q.push( neigh );
        fresh[neigh] = false;
      }
    }
  }
/**/ return -1; // change #5
}


// ------------------------------------------------------------------------------
//                     Shortest path between two nodes
// ------------------------------------------------------------------------------

void shortestPathFromTo( int start, int target ){
  std::queue< int > q;
  std::vector< bool > fresh( N, true );
/**/ std::vector< int > pred( N, -1 ); // change #1

/**/  q.push( target );  // change #2  -- swap target and start
/**/  fresh[target] = false;

  int currn, neigh;
  while( !q.empty() ){
    currn = q.front(); q.pop();
    for( int j = 0; j < edge[currn].size(); j++ ){
      neigh = edge[currn][j];
      if( fresh[neigh] ){
        q.push( neigh );
        fresh[neigh] = false;
/**/    pred[neigh] = currn;  // change #3
      }
    }
  }

 /**/ // change #4  -- list the path
  cout << start;
  while( start != target ) {
    start = pred[start];
    cout << " -> " << start;
  }
  cout << endl;
}

// ------------------------------------------------------------------------------
//                    Most distant node
// ------------------------------------------------------------------------------

int mostDistantNode( int start ){
  std::queue< int > q;
  std::vector< bool > fresh( N, true );
/**/  std::vector< int > dist( N, N+1 );  // change #1

  q.push( start );
  fresh[start] = false;
/**/  dist[start] = 0; // change #2

  int currn, neigh;
  while( !q.empty() ){
    currn = q.front(); q.pop();
    for( int j = 0; j < edge[currn].size(); j++ ){
      neigh = edge[currn][j];
 /**/ dist[neigh] = min(dist[neigh], 1+dist[currn]); // change #3
      if( fresh[neigh] ){
        q.push( neigh );
        fresh[neigh] = false;
      }
    }
  }

 /**/ // change #4
 int maxdist = 0, maxdistnode = start;
  for( int i = 0; i < N; i++ )
    if( dist[i] > maxdist )
    { maxdist = dist[i]; maxdistnode = i;}
 return maxdistnode;
}

// ------------------------------------------------------------------------------
//                    Tree diameter
// ------------------------------------------------------------------------------

int treeDiameter() {
  // just a demo(!), distanceFromTo performs additional redundant search.
  int node1 = mostDistantNode( 0 ); // start anywhere
  int node2 = mostDistantNode( node1 );
  return distanceFromTo( node1, node2 );
}


// ------------------------------------------------------------------------------
//                   Check if graph is bipartite
// ------------------------------------------------------------------------------
// Fill in yourself:

bool isBipartite(){
  // .. your code
  return true;
}


// ==============================================================================
//                          M  A  I  N
// ==============================================================================


int main() {

  //readGrConsole();
  readGrFile("graph1.txt");

  printGr();
  BFS( 0 );
  cout << "Connected: " << (isConnected() ? "Yes" : "No") << endl;
  cout << "Is a tree: " << (isTree() ? "Yes" : "No") << endl;

  cout << "Distances from 0 " << endl;
  distancesFrom( 0 );

  int mostDistant0 = mostDistantNode( 0 );
  cout << "Most distant node from 0: " <<  mostDistant0 << endl;
  cout << "Shortest path 0 -- " <<  mostDistant0 << ":" << endl;
  shortestPathFromTo( 0, mostDistant0 );

  if( isTree() )
    cout << "Tree Diameter: " <<  treeDiameter() << endl;

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
