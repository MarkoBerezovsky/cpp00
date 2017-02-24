#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_map>



using namespace std;


int hf( string st, int mult, int mod ){
  int hfVal = 0;
  for( int j = 0; j < st.size(); j++ )
    hfVal = ( hfVal * mult +  int(st[j]) ) % mod;
  return hfVal;
}

void hfVal( vector<string> & names,  vector<int> & hfVals, int mult, int mod ) {
  hfVals.resize( names.size(), 0 );
  for( int i = 0; i < names.size(); i++ )
    hfVals[i] = hf( names[i], mult, mod );
}


int main(){

  string path = "D:\\Iskola\\osoby\\Grossman\\Prj\\Set12_Hash\\";
  string fileName = "names.txt";

  vector<string> names;
  vector<int> hfVals;

  string line;
  ifstream namesFile( path + fileName );
  while( getline( namesFile, line ) )
    names.push_back( line );
  namesFile.close();


  vector<double> loadFactors { 0.9, 0.8, 0.7, 0.6, 0.5 };
  int range = 1;
  int mult = 31;
  int dataSize = names.size();

  // process

  cout << "Data size " << dataSize << endl << "-----------------" << endl;

  for( int i = 0; i < loadFactors.size(); i++ ) {
    int baseTableSize = int( ceil( (1.0 / loadFactors[i]) * dataSize ) );

    for( int tableSize = baseTableSize-range; tableSize <= baseTableSize+range; tableSize++ ) {
      hfVal( names, hfVals, mult, tableSize );
      sort( hfVals.begin(), hfVals.end() );
      int collisions = 0;
      for( int k = 1; k < hfVals.size(); k++)
        if( hfVals[k-1] == hfVals[k] ) collisions++;

      cout << "   table size " << tableSize << "  collisions " << collisions << endl;
    }

    cout << endl;
  }



    return 0;
}
