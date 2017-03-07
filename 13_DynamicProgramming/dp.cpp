#include <iostream>
#include <vector>


using namespace std;

// ------------------------------------------------------------------------------------------------
//                  K n a p s a c k    U n b o u n d e d
// ------------------------------------------------------------------------------------------------

// Knapsack problem with unlimited number of items of each type
// With each object are associated its  mass and its price
// The method is equivalent to finding a longest path in a DAG
// Nodes in DAG are all possible total masses up to given mass capacity of the Knapsack
// Edge from c1 to c2 exists in the DAG  iff   ((c2 - c1) == cost of some item)
// Each edge is labelled by the cost of the corresponding item

void knapMulti( vector<int> & masses, vector<int> & prices, int capacity ) {
  int  N = masses.size();

  // for each capacity there will be a max price attainable
  // at the beginning each capacity produces 0 price
  vector<int> maxPrices ( capacity+1, 0 );

  // register a path in the DAG corresponding to the optimal solution
  vector<int> prevByItem ( capacity+1, -1 );  // -1 serves as a NULL reference

  int prevCapa, candidateBetterPrice; // auxiliary variables

  // effectively a longest path search in a DAG:
  for( int currCapa = 1; currCapa <= capacity; currCapa++ ) {
    for( int currItem = 0; currItem < N; currItem++ ) {

      prevCapa = currCapa - masses[currItem];
      if( prevCapa < 0 ) continue;

      candidateBetterPrice = maxPrices[prevCapa] + prices[currItem];
      if( maxPrices[currCapa] < candidateBetterPrice ){
          maxPrices[currCapa] = candidateBetterPrice;
          prevByItem[currCapa] = currItem;
      }
    } // for all items
  } // for all masses


  // Establish global maximum
  int totalBestPrice = 0, totalBestPriceMass;
  for( int currCapa = 1; currCapa <= capacity; currCapa++ )
    if( totalBestPrice < maxPrices[currCapa] ){
      totalBestPrice = maxPrices[currCapa];
      totalBestPriceMass = currCapa;
    }

  // reconstruct optimum items selection
  vector<int> itemCount ( N, 0 );
  int currMass = totalBestPriceMass;
  while( currMass > 0 && prevByItem[currMass] >= 0 ) {
      itemCount[prevByItem[currMass]]++;
      currMass -= masses[prevByItem[currMass]];
    }

  // print the result
  for( int item = 0; item < N; item++ )
    if( itemCount[item] > 0 )
      cout << itemCount[item] << " x item " << item
           << " of mass " << masses[item] << " and price " << prices[item] << endl;
  cout << "---------------------------------------------------------" << endl;
  cout << "total mass " << totalBestPriceMass << "  total price " << totalBestPrice << endl;
}


// ------------------------------------------------------------------------------------------------
//                  K n a p s a c k    0 / 1
// ------------------------------------------------------------------------------------------------

// Knapsack problem with unique items of each type
// Each object is either included in the knapsack or it is not included.
// Let optP(c, it) be the optimal price of storing a subset of items from 1st to it-th
// in the knapsack of capacity c. There are only two possibilities for the it-th item:
// It can be either included or not included in the knapsack of capacity c.
// Therefore, the recurrence is
// optP(c, it) = max( optP(c-price[it], it-1), optP(c, it-1) )
// with initial conditions: optP(0, it) = optP(c, 0) = 0, for any c, it.

void knap01( vector<int> & masses, vector<int> & prices, int capacity ) {
  int N = masses.size();

  // insert dummy 0 item with 0 mass and 0 price, to easily process the DP table
  masses.insert( masses.begin(), 0 );
  prices.insert( prices.begin(), 0 );

  // DP table filled with 0;
  vector< vector<int> > optPrices ( N+1, vector<int>( capacity+1, 0 ) );

  // fill the rest of the DP table
  int prevCapa, candidateBetterPrice; // auxiliary variables
  for( int item = 1; item <= N; item++ )
    for( int currCapa = 1; currCapa <= capacity; currCapa++ ) {
      prevCapa = currCapa - masses[item];
      if( prevCapa < 0 ) continue;

      candidateBetterPrice = optPrices[item-1][prevCapa] + prices[item];
      if( optPrices[item-1][currCapa] < candidateBetterPrice )
        optPrices[item][currCapa] = candidateBetterPrice;  // include current item
      else
        optPrices[item][currCapa] = optPrices[item-1][currCapa];  // do not include it
  }

  // reconstruct optimum items selection
  vector<bool > usedItems ( N+1, false );
  int totalBestPrice = 0, totalBestPriceMass = 0;
  int currCapa = capacity;
  for( int item = N; item > 0; item-- ){
    prevCapa = currCapa - masses[item];
    // current item used?
    if( prevCapa >=  0  &&   optPrices[item-1][prevCapa] +  prices[item] > optPrices[item-1][currCapa] ) {
      currCapa = prevCapa;
      usedItems[item] = true;
      totalBestPriceMass += masses[item];
      totalBestPrice += prices[item];
    }
  }

  //restore shifted masses and prices:
  masses.erase( masses.begin() );
  prices.erase( prices.begin() );
  usedItems.erase( usedItems.begin() );

  // print the optimal solution
  for( int item = 0; item <= N; item++ )
    if( usedItems[item] )
      cout << "item "  << item << " of mass " << masses[item] << " and price " << prices[item] << endl;
  cout << "---------------------------------------------------------" << endl;
  cout << "total mass " << totalBestPriceMass << "  total price " << totalBestPrice << endl;
}

// ------------------------------------------------------------------------------------------------
//                                M A I N
// ------------------------------------------------------------------------------------------------

int main() {

  vector<int> masses {  3,  6,  4,  7,  5,  2 };
  vector<int> prices { 50, 80, 60, 90, 70, 30 };
  int capacity = 20;
  knapMulti( masses, prices, capacity );

  cout << endl;
  capacity = 14;
  knap01( masses, prices, capacity );

    return 0;
}
