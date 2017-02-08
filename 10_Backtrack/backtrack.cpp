#include <iostream>
#include <vector>
#include <string>
#include <sstream> // string stream
#include <cmath>

using namespace std;


// ------------------------------------------------------------------------------
//                      Coin change
// ------------------------------------------------------------------------------

void coin( vector<int> & coins, int currPrice, int currCoinIndex, vector<int> & change ){
  if ( currPrice < 0  || currCoinIndex >= coins.size() ) return;

  if( currPrice == 0 ) {
    for( int coinIndex = 0; coinIndex < change.size(); coinIndex++)
      cout << change[coinIndex] << " ";
    cout <<  endl;
    return;
  }

  if ( currPrice < coins[currCoinIndex] )
    coin( coins, currPrice, currCoinIndex+1 , change );
  else
    for( int coinIndex = currCoinIndex; coinIndex < coins.size(); coinIndex++ ){
      change.push_back( coins[coinIndex] );
      coin( coins, currPrice - coins[coinIndex], coinIndex, change );
      change.pop_back( );
    }
}


// ------------------------------------------------------------------------------
//                      N Queens problem
// ------------------------------------------------------------------------------

void print( vector<int> & queenCol ){
  for( int row = 0; row < queenCol.size(); row++ ){
    for( int col = 0; col < queenCol.size(); col++ )
      if( queenCol[row] == col ) cout << "X";
      else cout << ".";
    cout << endl;
  }
  cout  << endl;
}


bool positionOK( vector<int> & queenCol, int row, int col) {
  for ( int r = 0; r < row; r++)
    if( (queenCol[r] == col) ||                 // same column or
        (abs(row-r) == abs(queenCol[r]-col)) )  // same diagonal
      return false;
  return true;
}


void putQueen( vector<int> & queenCol, int row, int col) {
  queenCol[row] = col;                    // put a queen there
  if ( ++row ==  queenCol.size() )         // if solved
    print( queenCol );                     // output solution
  else
    for( col = 0; col < queenCol.size(); col++ )             // test all columns
      if( positionOK( queenCol, row, col ) )                   // if free
          putQueen( queenCol, row, col );           // next row recursion

}


// ------------------------------------------------------------------------------
//                      All paths from a to b
// ------------------------------------------------------------------------------

vector<vector<int> > edges;
vector<int> graphPath(0);
vector<bool> used;

void graphInit ( int N ) {
  edges.resize( N, vector<int>(0) );
  used.resize( N, false );
}
void addEdge( int n1, int n2 ){
    if( n1 >= edges.size() || n2 >= edges.size() ) return; // non-existent node(s)
		edges[n1].push_back( n2 );  // add edge
		edges[n2].push_back( n1 );  // add edge
}

void allPaths( int currNode, int endNode ) {
  graphPath.push_back( currNode );
  used[currNode] = true;

  if( currNode == endNode ) {
    cout << graphPath[0];
    for( int i = 1; i < graphPath.size(); i++ )
      cout << " --> " << graphPath[i];
    cout << endl;
  }
  else
    for( int j = 0; j < edges[currNode].size() ; j++ ) {
      int neighbour = edges[currNode][j];
      if( used[neighbour] == false )
        allPaths( edges[currNode][j], endNode );
    }

  used[currNode] = false;
  graphPath.pop_back();
}


// ==============================================================================
//                          M  A  I  N
// ==============================================================================

int main(){

  // coins change -------------------------------

  vector<int> coins {50, 40, 23, 7};
  vector<int> res (0);
  coin( coins, 100, 0, res );

  cout << endl;

  // N Queens -------------------------------

  int N = 6;
  vector<int> queenCol( N );
  for( int col = 0; col < N; col++ )
    putQueen( queenCol, 0, col );

  // All paths from a to b -------------------------------

  graphInit( 5 );
  addEdge(0, 1);
  addEdge(0, 4);
  addEdge(1, 2);
  addEdge(1, 3);
  addEdge(2, 3);
  addEdge(3, 4);
  allPaths(0, 2);

  /*
     2
    / \
   /   \
  1----3
  |    |
  0----4
  */

}

