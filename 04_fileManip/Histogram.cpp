#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


// --------------------------------------------------------------------------
/**
  An easy improvement of random numbers generator
*/

void randInit() {
  // random number generator initialized by current time in seconds
  srand((unsigned)time(0));
}

/**  rand from interval [0, n) */
int rand(int n) { // n must be > 1
  int maxVal = RAND_MAX - RAND_MAX % n;
  int randVal;
  while( (randVal = rand()) >= maxVal );
  return randVal % n;
}

/**  rand from interval [n1, n2) */
int rand( int n1, int n2 ) {
  return n1 + rand( n2-n1 );
}


// --------------------------------------------------------------------------
/**
  Generate random integer file
*/

void randIntFile( int lowVal, int hiVal, string fname,  int size, int lineSize ) {
  ofstream outfile( fname );
  for( int i = 0; i < size; i++ ){
    outfile << rand( lowVal, hiVal );
    if( i % lineSize == lineSize-1 )  // end of line?
      outfile << endl;
    else
      outfile << " ";
  }
  outfile.close();
}

// --------------------------------------------------------------------------
/**
  Find median in an integer file
*/

double median( string fname ){
  ifstream infile( fname );
  vector<int> arr;

  int value;
  while( infile >> value )
    arr.push_back( value );
  infile.close();

  sort( arr.begin(), arr.end() );

  if( arr.size() % 2 == 1 )
    return arr[arr.size() / 2];
  else
    return (arr[arr.size()/2 - 1] + arr[arr.size()/2]) / 2.0;
}

// --------------------------------------------------------------------------
/**
  load integer vector from an integer file
*/
void loadInt(string fname, vector<int> & v){  
  ifstream infile( fname );
  int value;
  v.clear();

  while( infile >> value )
    v.push_back( value );
  infile.close();
 }

// --------------------------------------------------------------------------
/**
  histogram
*/

// returns the fraction of the rectangle(x2, y2, w2, h2) occupied by the vertical bars
// in the histogram, supposing bar width is 1,
double intersection( vector<int> histo, double x2, double y2, double w2, double h2) {
  int x1 = (int) floor( x2 );
  double Lbord, Rbord, area = 0.0;
  while( (x1 < histo.size()) && (x1 < x2 + w2 ) ) {
    Lbord = (double) max( x2, (double)x1 );
    Rbord = (double) min( x2+w2, (double)(x1+1) );
    if( histo[x1] >= y2 ) {
      area +=  (Rbord - Lbord) *  min(h2, (double) histo[x1] - y2 );
    }
    x1 += 1;
  }
  //cout  << " w2 h2 " << w2 << " " << h2 << endl;
  //cout << area / ( w2 * h2) << endl;
  return area / ( w2 * h2);
}

void histogram( vector<int> data, int maxCharHeight, int maxCharWidth, char symbol ){
  int minDataVal, maxDataVal, maxFrequency, charWidth, histN;
  int N = data.size();

  // calculate histogram width
  minDataVal = maxDataVal = data[0];
  for( int i = 1; i < N; i++ ) {
    minDataVal = min( minDataVal, data[i] );
    maxDataVal = max( maxDataVal, data[i] );
  }

  // init histogram
  histN = maxDataVal - minDataVal + 1;
  vector<int> hist ( histN, 0 );  // initialize with zeros
  maxFrequency = 0;

  // obtain histogram
  int jHist;
  for( int i = 0; i < N; i++ ){
    jHist = data[i] - minDataVal;
    hist[jHist]++;
    maxFrequency = max( maxFrequency, hist[jHist] );
  }

  // histogram plot sliding window coords
  charWidth = min( histN, maxCharWidth );
  double outWinX, outWinY,
          outWinH = maxFrequency / (double) maxCharHeight,
          outWinW = histN / (double) charWidth;

  // plot upper border
  cout << "Histogram" << endl;
  for( int j = 0; j < charWidth; j++ ) cout << "-";
  cout << " " << maxFrequency << endl;

  // plot histogram itself
  for( int iHeight = maxCharHeight - 1; iHeight >= 0; iHeight-- ){
    outWinX = 0.0;
    outWinY =  maxFrequency * ( (double) iHeight / (double) maxCharHeight) ;
    for( int j = 0; j < charWidth; j++ ) {
      if( intersection( hist, outWinX, outWinY, outWinW, outWinH) > 0.5 )
      //if ( 0 )
        cout << symbol;
      else cout << " ";
      outWinX += outWinW;
    }
    cout << endl;
  }

  // plot bottom border
  for( int j = 0; j < charWidth; j++ ) cout << "-";
  cout << " 0" << endl;

  // plot summary
  cout << "Range: [" << minDataVal << ", " << maxDataVal << "]" << endl;
}


// --------------------------------------------------------------------------
/**                   M A I N
*/
// --------------------------------------------------------------------------

string path = "D:\\Iskola\\osoby\\Grossman\\Prj\\";

int main() {
  randInit();
  //randIntFile( 100, 200, path+"rand01.txt", 100, 10 );
  //randIntFile( 10, 10000, path+"rand02.txt", 10000, 30 );
  //randIntFile( 0, 2, path+"rand02.txt", 20, 20 );
  //cout << median( path+"rand03.txt" ) << endl;

  vector<int> x = {3, 4, 7, 0, 8, 4, 4, 7,  19, 20, 19, 20, 3, 7, 4};
  loadInt(path+"rand03.txt", x);
  histogram(x, 5, 21, 'x');

}

