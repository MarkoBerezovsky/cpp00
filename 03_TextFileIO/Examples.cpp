#include <iostream>
#include <fstream>
#include <sstream> // string stream
#include <string>

using namespace std;

string path = "D:\\Iskola\\osoby\\Grossman\\Prj\\";

void file1() {
  ofstream outfile( path + "file1.txt" );
  outfile << "1 2 3 4" << endl;
  outfile << "6 7 8 9" << endl;
  outfile << "1 1 2 3 5 8" << endl;
  outfile.close();
}

void file2() {
  ifstream infile( path + "file1.txt" );
  ofstream outfile( path + "file2.txt" );
   int value;

  while( infile >> value )
    outfile << value << endl;

  infile.close();
  outfile.close();
}

void file3() {
  ifstream filein( path + "file1.txt" );
  ofstream fileout( path + "file2.txt" );
  string line;
  int value;

  while( getline( filein, line ) ) {
    istringstream linein( line );
    while( linein >> value )
      fileout << value << " ";
    fileout << endl;
  }

  filein.close();
  fileout.close();
}


void filecopy( string infname, string outfname ) {
  ifstream filein( path + infname );
  ofstream fileout( path + outfname );
  string line;
  int value;

  while( getline( filein, line ) ) {
    istringstream linein( line );
    while( linein >> value )
      fileout << value << " ";
    fileout << endl;
  }

  filein.close();
  fileout.close();
}




int main() {
  file3();
  filecopy( "f1.txt", "f2.txt" );
  return 0;
}

