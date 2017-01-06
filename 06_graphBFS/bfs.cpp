#include <stdio.h>
#include <vector>
#include <queue>




/*
Example methods presented here are based on BFS.
All methods work in O(|E|) time,
however, they are a mere concept illustration
a therefore might be far from optimized.
*/


using namespace std;

// Graph representation
int N, M;
vector<vector<int> > edge;


void readGr(){
	scanf( "%d%d", &N, &M );
	edge.resize( N, vector<int>(0) );

	int n1, n2;
	for( int i = 0; i < M; i++ ) {
		scanf( "%d%d", &n1, &n2 );
		edge[n1].push_back( n2 );  // add edge
		edge[n2].push_back( n1 );  // add edge
	}
}

// print Graph, may help in debugging (sometimes greatly!)
void prGr(){
  for( int i = 0; i < N; i++ ){
    printf( "%d _", i );
    for( int j = 0; j < edge[i].size(); j++ )
      printf( " %d", edge[i][j] );
    printf( "\n" );
  }
}


// --------------------------------------------------------------

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
        printf(" BFS edge: %d -> %d\n", currn, neigh );
      }
    }
  }
}

// --------------------------------------------------------------

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

// --------------------------------------------------------------

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

// --------------------------------------------------------------

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
    printf( "dist(%d %d) = %d\n", start, i, dist[i]);
}

// --------------------------------------------------------------


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
  printf("shortest path: %d", start);
  while( start != target ) {
    start = pred[start];
    printf( " -> %d", start);
  }
  printf( "\n" );
}

// --------------------------------------------------------------

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

// --------------------------------------------------------------

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

// --------------------------------------------------------------

int treeDiameter() {
  // just a demo(!), distanceFromTo performs additional redundant search.
  int node1 = mostDistantNode( 0 ); // start anywhere
  int node2 = mostDistantNode( node1 );
  return distanceFromTo( node1, node2 );
}

// --------------------------------------------------------------

// Fill in yourself:
// bool isBipartite(){
// }

// --------------------------------------------------------------

int main() {

  readGr();
  prGr();
  BFS( 3 );
  printf( "Connected: %s\n", isConnected()? "Yes" : "No" );
  printf( "Is a tree: %s\n", isTree() ? "Yes" : "No" );
  distancesFrom( 1 );
  shortestPathFromTo( 4, 0 );
  if( isTree() ) printf( "Tree Diameter: %d\n", treeDiameter() );

return 0;
}

