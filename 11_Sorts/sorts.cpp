#include <iostream>
#include <vector>
//#include <cmath>

using namespace std;


// ------------------------------------------------------------------------------
//                      Merge sort
// ------------------------------------------------------------------------------

void merge( vector<int> & in, vector<int> & out, int low, int high) {
  int half = (low+high)/2;
  int i1 = low;
  int i2 = half + 1; // just past the middle of the current segment
  int j = low;               // index in merged array

  // compare and merge
  while( (i1 <= half ) && (i2 <= high))
    if( in[i1] <= in[i2] )  out[j++] = in[i1++];
    else                    out[j++] = in[i2++];

  // copy the rest
  while(i1 <= half) out[j++] = in[i1++];
  while(i2 <= high) out[j++] = in[i2++];

}


void mergeSort( vector<int> & a, vector<int> & aux, int  low, int high ) {
  if( low >= high ) return;         // too small!

  // sort
  int half = (low+high)/2;
  mergeSort( a, aux,   low,  half );   // left half
  mergeSort( a, aux, half+1, high );   // right half
  merge( a, aux, low, high );          // merge halves

  // put sorted values back to a, most simple option:
  for( int i = low; i <= high; i++ ) a[i] = aux[i];

}

// ------------------------------------------------------------------------------
//                      Quick sort
// ------------------------------------------------------------------------------

void quickSort( vector<int> & a, int low, int high ){
  int iL = low, iR = high;
  int pivot = a[low];

  do{
    while(a[iL] < pivot ) iL++;
    while(a[iR] > pivot ) iR--;

    if ( iL < iR ){ swap(a[iL], a[iR]); iL++; iR--; }
    else
      if( iL == iR ) { iL++; iR--;}
  }
  while( iL <= iR) ;

  // recursion
  if( low < iR )  quickSort( a, low, iR );
  if( iL < high ) quickSort( a, iL, high );

}


// ------------------------------------------------------------------------------
//                      Counting sort
// ------------------------------------------------------------------------------

void countingSort( vector<int> & a ) {
  // find min and max in a, use smart method
  int minVal = a[0], maxVal = a[0];
  for( int i=1; i < a.size()-1; i=i+2 )
    if ( a[i] < a[i+1] ){
      if (   a[i] < minVal ) minVal = a[i];
      if ( a[i+1] > maxVal ) maxVal = a[i+1];
    }
    else {
      if (   a[i] > maxVal ) maxVal = a[i];
      if ( a[i+1] < minVal ) minVal = a[i+1];
    }

  vector<int> freq ( maxVal-minVal+1, 0 );  // filled with 0's
  vector<int> output ( a.size() );


  // calcualte frequencies of all values
  int offset = minVal;
  cout << "offset " << offset << endl;
  for( int i = 0; i < a.size(); i++ ) freq[a[i]-offset]++;

  // modify frequencies
  freq[0]--;
  for( int i = 1; i < freq.size(); i++ )  freq[i] += freq[i-1];

  // produce output
  for( int i = a.size()-1 ; i >= 0; i-- ){
    output[freq[a[i]-offset]] = a[i];
    freq[a[i]-offset]--;
  }

  // result back to a
  swap( a, output );
}


int main()
{

    vector<int> arr { 7, 6, 2, 5, 4, 3, 10, 9, 8, 4, 3, 4, 3 };
    vector<int> aux ( arr.size() );  // used in merge sort only

    mergeSort( arr, aux, 0, arr.size()-1 );
    //quickSort( arr , 0, arr.size()-1);
    //countingSort( arr );

    // see the result:
    for( int i = 0; i < arr.size(); i++ )
      cout << arr[i] << " ";
    cout << endl;
    return 0;
}
