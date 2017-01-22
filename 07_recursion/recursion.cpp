/*
Some simple recursion demonstrations
*/

#include <iostream>
#include <vector>

using namespace std;

// ------------------------------------------------------------------------------
//                             Max of array recursively
// ------------------------------------------------------------------------------

int maxValue1( std::vector<int> & v, int from, int to ) {
  if( from+1 == to ) return v[from];
  return max( v[from], maxValue1(v, from+1, to) );
}

// divide in the middle:
int maxValue2( std::vector<int> & v, int from, int to ) {
  if( from+1 == to ) return v[from];
  int lmax = maxValue2( v, from, (from+to)/2 );
  int rmax = maxValue2( v, (from+to)/2, to );
  return max( lmax, rmax );
}

// divide in the middle shorter
int maxValue3( std::vector<int> & v, int from, int to ) {
  if( from+1 == to ) return v[from];
  return max( maxValue3( v, from, (from+to)/2 ), maxValue3( v, (from+to)/2, to ));
}


// ------------------------------------------------------------------------------
//                             Is non-decrasing?
// ------------------------------------------------------------------------------

bool isNonDecreasing1( std::vector<int> & v, int from, int to ) {
  if( from+1 >= to ) return true;
  return      v[from] <= v[from+1]
          && isNonDecreasing1(v, from+1, to);
}


// divide in the middle, carefully!:
bool isNonDecreasing2( std::vector<int> & v, int from, int to ) {
  if( from+1 >= to ) return true;
  int mid = (from+to-1)/2 +1;  // mid is first in the right half
  return      isNonDecreasing2( v, from, mid)
           && isNonDecreasing2( v, mid, to )
           &&  v[mid-1] <= v[mid] ;

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
//                       Hanoi towers
// ------------------------------------------------------------------------------


// Note that the correct sequence of moves is printed
// **without** keeping any information about the disks on particular sticks

void Hanoi( int fromStick, int toStick, int otherStick, int noOfDisks ){
  if( noOfDisks == 0 ) return;  // nothing to do, obviously

  Hanoi( fromStick, otherStick, toStick, noOfDisks-1 );
  cout << "transfer disk of size " <<  noOfDisks << " from stick " << fromStick << " to stick " << toStick << endl;
  Hanoi( otherStick, toStick, fromStick, noOfDisks-1 );
}

// ------------------------------------------------------------------------------
//                       Hanoi towers with pictures
// ------------------------------------------------------------------------------

/** Sticks & disks picture, can be improved endlessly ... */

void Hanoi_posh_print( vector<vector<int>> & sticks, string aComment) { // supposes 3 sticks
  
  // currently, max disk size is not kepth anywhere nor it is passed as a parameter, so go and find it: 
  int maxDisk = 0;
  if( sticks[0].size() > 0 ) maxDisk = sticks[0][0];
  if( sticks[1].size() > 0 ) maxDisk = max( maxDisk, sticks[1][0] );
  if( sticks[2].size() > 0 ) maxDisk = max( maxDisk, sticks[2][0] );

  int columnWidth = maxDisk*2+2+1;

  cout << string( columnWidth*3, ' ') << endl;
  char diskChar = '#';
    for( int level = maxDisk; level >= 0; level-- ) {
      for( int stick = 0; stick < 3; stick++ ) {
        if( level >= sticks[stick].size() ){
          cout << string( columnWidth/2, ' ');
          cout << '|';
          cout << string( columnWidth/2, ' ');
        }
        else {
          int diskWidth = 2 * sticks[stick][level]+1;
          cout << string( columnWidth/2 - diskWidth/2, ' ');
          cout << string( diskWidth/2, diskChar) << sticks[stick][level] << string( diskWidth/2, diskChar);
          cout << string( columnWidth/2 - diskWidth/2, ' ');
        }
      }
      cout << endl;
    }
  cout << string( columnWidth*3, '-') << aComment << endl;
}


/** The recursive function which does the job. */

void Hanoi_posh( vector<vector<int>> & sticksArr, int fromStick, int toStick, int otherStick, int pileSize){
  if( pileSize == 0 ) return;  // nothing to transfer

  // move a pile of disks recursively
  Hanoi_posh( sticksArr, fromStick, otherStick, toStick, pileSize-1 );

  // "physically" transfer the disk
  int disk = sticksArr[fromStick][sticksArr[fromStick].size()-1];
  sticksArr[fromStick].pop_back();
  sticksArr[toStick].push_back(disk);

  // display the disks configuration after the transfer
  ostringstream comment;
  comment << "  moved: " << fromStick+1 << " --> " << toStick+1 << ", disk: " <<  sticksArr[toStick][sticksArr[toStick].size()-1] << endl;
  Hanoi_posh_print( sticksArr, comment.str() );
 
  // move a pile of disks recursively
  Hanoi_posh( sticksArr, otherStick, toStick, fromStick, pileSize-1 );
}


/** Wrapper function which initializes the stuff and runs the recursion. */

void Hanoi_posh(int disksN) {
  //vector of three vectors, each represents the disks on one stick
  // the disks themselves are represented as integers according to their sizes: 1,2,3,...
  vector<vector<int>> sticks (3, vector<int> (0) );

  // fill first stick
  for( int n = disksN; n > 0; n-- )
    sticks[0].push_back(n);

  // display initial state
  Hanoi_posh_print( sticks, "  Start configuration. " );

  // run recursion
  Hanoi_posh( sticks, 0, 2, 1, sticks[0][0] );
}



// ------------------------------------------------------------------------------
//          2D Fractal  generators
// ------------------------------------------------------------------------------

void fillSquare1( vector<vector<char> > & board,  int x, int y, int sqsize, char c){
  if( x < 0 || y < 0 || y >= board.size() || x >= board[y].size() ) return;

  if( sqsize <= 1 ) {
    board[y][x] = c;
    return;
  }

  fillSquare1( board, x,               y,              sqsize/3, c );
  fillSquare1( board, x + sqsize*2/3,  y,              sqsize/3, c );
  fillSquare1( board, x,               y + sqsize*2/3, sqsize/3, c );
  fillSquare1( board, x + sqsize*2/3,  y + sqsize*2/3, sqsize/3, c );
  fillSquare1( board, x + sqsize*1/3,  y + sqsize*1/3, sqsize/3, c );
}


void fillSquare2( vector<vector<char> > & board,  int x, int y, int sqsize, char c){
  if( x < 0 || y < 0 || y >= board.size() || x >= board[y].size() ) return;

  if( sqsize <= 1 ) {
    board[y][x] = c;
    return;
  }

  fillSquare2( board, x + sqsize*1/3,  y             , sqsize/3, c );
  fillSquare2( board, x,               y + sqsize*1/3, sqsize/3, c );
  fillSquare2( board, x + sqsize*2/3,  y + sqsize*1/3, sqsize/3, c );
  fillSquare2( board, x + sqsize*1/3,  y + sqsize*2/3, sqsize/3, c );
  fillSquare2( board, x + sqsize*1/3,  y + sqsize*1/3, sqsize/3, c );
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
  std::vector<int> w { 11, 14, 14, 20, 32 };


  cout << "Check min values:" << endl;
  cout << maxValue1( v, 0, v.size() ) << endl;
  cout << maxValue2( v, 0, v.size() ) << endl;
  cout << maxValue3( v, 0, v.size() ) << endl;

  cout << "Check nonDecreasing:" << endl;
  cout << isNonDecreasing1( v, 0, v.size() )  << endl;
  cout << isNonDecreasing2( v, 0, v.size() )  << endl;
  cout << isNonDecreasing1( w, 0, w.size() )  << endl;
  cout << isNonDecreasing2( w, 0, w.size() )  << endl;


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
 fillSquare2(board, 0,0, 81, 'X');
 listBoard(board);

 return 0;
}

