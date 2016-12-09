#include <iostream>

using namespace std;

int arr []  = {2,3,5,7,11, 47, -5, 37};

void arrSize() {
  cout << "size of array   " << sizeof(arr)<< endl;
  cout << "size of integer " << sizeof(int)<< endl;
}

void arrPrint() {
  for( int i = 0; i < sizeof(arr)/sizeof(int); i++ )
    cout << arr[i] << " ";
  cout << endl;
}

int arrSum() {
  int sum = 0;
  for( int i = 0; i < sizeof(arr)/sizeof(int); i++ )
    sum = sum + arr[i];
  return sum;
}

int arrMax() {
  int max = arr[0];
  for( int i = 1; i < sizeof(arr)/sizeof(int); i++ )
    if( arr[i] > max )
      max = arr[i];
  return max;
}


int main() {
  arrSize();
  arrPrint();
  cout << "Sum of array: " << arrSum() << endl;
  cout << "Max of array: " << arrMax() << endl;
  return 0;
}
