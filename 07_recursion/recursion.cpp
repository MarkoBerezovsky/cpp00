/*
Some simple recursion demonstrations
*/

#include <iostream>
#include <vector>

using namespace std;

// ------------------------------------------------------------------------------
//                             Max of array recursively
// ------------------------------------------------------------------------------

int maxValue( std::vector<int> & v , int from, int to ) {
  if( from+1 == to ) return v[from];
  return max( v[from], maxValue(v, from+1, to) );
}

// ------------------------------------------------------------------------------
//                             Insert Sort recursively
// ------------------------------------------------------------------------------

void InsertSort( std::vector<int> & v,  int currPos ){
  if (currPos == v.size() ) return;

  int currVal = v[currPos];
  int j = currPos-1;
  while( j >= 0 && v[j] > currVal ) {
    v[j+1] = v[j];
    j--;
  }
  v[j+1] = currVal;
  InsertSort(v, currPos+1);
}

// ------------------------------------------------------------------------------
//                  n n-1 n-2 ... 3 2 1 1 2 3 ... n-2 n-1 n
// ------------------------------------------------------------------------------

void downUp( int n ) {
  if( n == 0 ) return;

  cout << n << " ";
  downUp(n-1);
  cout << n << " ";
}

// ------------------------------------------------------------------------------
//                 1 2 3 ... n-2 n-1 n n n-1 n-2 ... 3 2 1
// ------------------------------------------------------------------------------

void upDown( int currVal, int n ) {
  if( currVal > n ) return;

  cout << currVal << " ";
  upDown( currVal+1, n);
  cout << currVal << " ";
}

// ------------------------------------------------------------------------------
//      1 2 1 3 1 2 1 4 1 2 1 3 1 2 1 5 1 2 1 3 1 2 1 4 1 2 1 3 1 2 1
// ------------------------------------------------------------------------------

void ruler( int n ){
  if( n == 0 ) return;

  ruler(n-1);
  cout << n << " ";
  ruler(n-1);
}

// ------------------------------------------------------------------------------
//          Fractal  generator
// ------------------------------------------------------------------------------

void fillSquare( vector<vector<char> > & board,  int x, int y, int sqsize, char c){
  if( x < 0 || y < 0 || y >= board.size() || x >= board[y].size() ) return;

  if( sqsize <= 1 ) {
    board[y][x] = c;
    return;
  }

  fillSquare( board, x,               y,              sqsize/3, c );
  fillSquare( board, x + sqsize*2/3,  y,              sqsize/3, c );
  fillSquare( board, x,               y + sqsize*2/3, sqsize/3, c );
  fillSquare( board, x + sqsize*2/3,  y + sqsize*2/3, sqsize/3, c );

  fillSquare( board, x + sqsize*1/3,  y + sqsize*1/3, sqsize/3, c );

}

// ------------------------------------------------------------------------------
//           Auxiliary and service functions
// ------------------------------------------------------------------------------

vector<vector<char> > makeBoard(int n) {
    vector<vector<char> >   board(n, vector<char>(n, '.'));
    return board;
}


void listBoard( vector<vector<char> >  & board ){
  for( int i = 0; i < board.size(); i++ ) {
    for( int j = 0; j < board[i].size(); j++ )
      cout << board[i][j];
    cout << endl;
  }
}

void listVect( std::vector<int> & v ){
  for( int i = 0; i < v.size(); i++ )
    cout << v[i] << " ";
  cout << endl;
}


// ==============================================================================
//                          M  A  I  N
// ==============================================================================

int main(){

  std::vector<int> v { 11, 34, 23, 27, 31, 18 };

  cout << maxValue( v, 0, v.size() ) << endl;

  listVect(v);
  InsertSort(v, 0);
  listVect(v);

  ruler(4);
  cout << endl;
  downUp(12);
  cout << endl;
  upDown(1, 12);
  cout << endl;

 vector<vector<char> > board = makeBoard(81);
 fillSquare(board, 0,0, 81, 'X');
 listBoard(board);

 return 0;
}

