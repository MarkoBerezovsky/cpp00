#include <iostream>
#include <string>

#define WIDTH 80
#define HEIGHT 50


using namespace std;

char pic [HEIGHT][WIDTH];


void picinit () {
  for( int i = 0; i < HEIGHT; i++ )
    for( int j = 0; j < WIDTH; j++ )
      pic[i][j] = ' ';
}

void picshow () {
  for( int i = 0; i < HEIGHT; i++ ) {
    for( int j = 0; j < WIDTH; j++ )
      cout << pic[i][j];
    cout << endl;
  }
}

void picrec(int x1, int y1, int x2, int y2, char borchar, char inchar) {
  for( int j = x1; j <= x2; j++ )
    pic[y1][j] = borchar;

  for( int i = y1+1; i < y2; i++ ) {
    pic[i][x1] = borchar;
    for( int j = x1+1; j < x2; j++ )
      pic[i][j] = inchar;
    pic[i][x2] = borchar;
  }

  for( int j = x1; j <= x2; j++ )
    pic[y2][j] = borchar;
}


void picframe(int x1, int y1, int x2, int y2) {
  for( int j = x1+1; j <= x2-1; j++ )
    pic[y1][j] = pic[y2][j] = '-';
  for( int i = y1+1; i <= y2-1; i++ )
    pic[i][x1] = pic[i][x2] = '|';
  pic[y1][x1] = pic[y1][x2] = pic[y2][x1] = pic[y2][x2] = '+';
}

void picframe() {
  picframe(0, 0, WIDTH-1, HEIGHT-1);
}


void pic1() {
  cout << "xooox" << endl;
  cout << "x...x" << endl;
  cout << "x...x" << endl;
  cout << "xooox" << endl;
}

void line(int n, char c) {
  for( int i = 0; i < n; i++ )
    cout << c;
}



void br() { cout << endl;}

void pic2(int n) {

  line( n, 'x' );
  br();
  for( int i = 1; i < n-1; i++ ) {
    cout << "x";
    line(n-2, '.');
    cout << "x" << endl;
  }
  line( n, 'x' );
  br();
}


int main() {
  picinit();

  picframe();

  picrec(4,4,28,18, 'x', '.');
  picrec(7,7,32,25, 'o', ' ');
  picshow();
  pic2(5);
  br();
  pic2(10);

  return 0;
}
