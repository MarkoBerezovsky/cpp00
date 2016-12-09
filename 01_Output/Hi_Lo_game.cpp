#include <iostream>

using namespace std;


void playComp() {
  char ans;
  cout << "Choose an integer in the range 1..99." << endl << endl;

  int low = 1, mid = 50, high = 99;

  while( low < high ) {
    cout << "Is your integer BIGGER than   " << mid << "  ?";
    cout << " [n .. No, y .. yes:]  ";
    cin >> ans;
    cout << endl;

    if( ans == 'y') {
      low = mid+1; mid = (low+high)/2 ;
    }
    else {
      high = mid; mid = (low+high)/2 ;
    }
   }
   cout << "Your integer is " << mid << "." << endl;
}



int main()
{
  playComp();
  return 0;
}
