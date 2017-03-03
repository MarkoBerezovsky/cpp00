#include <iostream>
#include <vector>

// Knapsack problem with unlimited number of items of the same sort
// The method is equivalent to finding a longest path in a DAG
// With each object are associated its  mass and its price
// Nodes in DAG are all possible total masses up to given mass capacity of the Knapsack
// Edge from c1 to c2 exists in the DAG  iff   ((c2 - c1) == cost of some item)
// Each edge is labelled by the cost of the corresponding item


using namespace std;

void knapMulti( vector<int> & masses, vector<int> & prices, int capacity ) {
  int  N = masses.size();

  // for each capacity there will be a max price attainable
  // at the beginning each capacity allows for 0 price
  vector<int> maxPrices ( capacity+1, 0 );

  // register a path in the DAG corresponding to the optimal solution
  vector<int> prevByItem ( capacity+1, -1 );

  int totalBestPrice = 0, totalBestPriceMass;

  int prevCapa, candidateBetterPrice; // auxiliary variables

  for( int currCapa = 1; currCapa <= capacity; currCapa++ ) {

    for( int currItem = 0; currItem < N; currItem++ ) {

      prevCapa = currCapa - masses[currItem];
      if( prevCapa < 0 ) continue;

      candidateBetterPrice = maxPrices[prevCapa] + prices[currItem];
      if(  maxPrices[currCapa] < candidateBetterPrice ){
            maxPrices[currCapa] = candidateBetterPrice;
            prevByItem[currCapa] = currItem;
          }
      if( totalBestPrice < maxPrices[currCapa] ){
        totalBestPrice = maxPrices[currCapa];
        totalBestPriceMass = currCapa;
      }

    } // for all items
  } // for all masses

  // reconstruct optimum items selection
  vector<int> itemCount ( N, 0 );
  int currMass = totalBestPriceMass;
  while( currMass > 0 && prevByItem[currMass] >= 0 ) {
      itemCount[prevByItem[currMass]]++;
      currMass -= masses[prevByItem[currMass]];
    }

  // print result
  for( int item = 0; item < N; item++ )
    if( itemCount[item] > 0 )
      cout << itemCount[item] << " x item " << item
           << " of mass " << masses[item] << " and price " << prices[item] << endl;
  cout << "---------------------------------------------------------" << endl;
  cout << "total mass " << totalBestPriceMass << "  total price " << totalBestPrice << endl;
}


// ------------------------------------------------------------------------------------------------
//                                M A I N
// ------------------------------------------------------------------------------------------------

int main() {

  vector<int> masses {3, 6, 4, 7, 5};
  vector<int> prices { 50, 80, 60, 90, 70};
  int capacity = 20;
  knapMulti( masses, prices, capacity );

    return 0;
}
