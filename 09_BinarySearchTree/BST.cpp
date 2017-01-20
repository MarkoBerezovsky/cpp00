#include <iostream>

using namespace std;

// ==============================================================================
//                         Node
// ==============================================================================

struct node
{
  int key;
  node *left;
  node *right;
};


node * newnode( int aKey ) {
  node * n = new node;
  n->left = n->right = NULL;
  n->key = aKey;
  return n;
}

// ==============================================================================
//                        Binary search tree
// ==============================================================================

// the whole tree is accessed through the root only
node * root;

// ------------------------------------------------------------------------------
//                             Initialize
// ------------------------------------------------------------------------------

void tree_init() {
  root = NULL;
}

// ------------------------------------------------------------------------------
//                             Insert a key
// ------------------------------------------------------------------------------


bool tree_insert( node * currNode, int aKey ) {
  if( currNode == NULL ) {
    root = newnode( aKey );
    return true;
  }

  if( aKey == currNode->key ) return false;

  if( aKey < currNode->key ) {
    if( currNode->left != NULL )
      tree_insert( currNode->left, aKey );
    else
      currNode->left = newnode( aKey );
  }

  if( currNode->key < aKey ) {
    if( currNode->right != NULL )
      tree_insert( currNode->right, aKey );
    else
      currNode->right = newnode( aKey );
  }

  return true;
}

// ------------------------------------------------------------------------------
//                             Contains a key ?
// ------------------------------------------------------------------------------


bool tree_contains( node * currNode, int aKey ) {
  if( currNode == NULL ) return false;
  if( currNode->key == aKey ) return true;
  return  tree_contains( currNode->left, aKey ) || tree_contains( currNode->right, aKey );
}

// ------------------------------------------------------------------------------
//                           Destroy tree,  De-allocate
// ------------------------------------------------------------------------------

void tree_destroy( node * currNode ) {
  if( currNode == NULL ) return;

  tree_destroy( currNode->left );
  tree_destroy( currNode->right );
  delete currNode;
}

// ------------------------------------------------------------------------------
//                        Print
// ------------------------------------------------------------------------------

void tree_print( node * currNode, int depth ){
  if( currNode == NULL ) return;

  tree_print( currNode->right, depth+1 );
  cout << std::string( 3*depth, ' ' ) << "[" << currNode->key << "]" << endl;
  tree_print( currNode->left, depth+1 );

  // Note the order : first the right subtree, then the current node and finally
  // the left subtree. The tree appears rotated to the left by 90 deg on the scree.
}

// ------------------------------------------------------------------------------
//                        Generate a bigger tree example
// ------------------------------------------------------------------------------

// 1 < number < modulus
// If "number" is a primitive root of multiplicative group of integers modulo "modulus"
// then a tree with |modulus-1| keys is built. For example, this is guaranteed when
// "modulus" is a prime.

void tree_make( int number, int modulus ){
  tree_init();
  int aKey = number;
  for( int i = 0; i < modulus-1; i++ ) {
    tree_insert( root, aKey );
    aKey = (aKey * number) % modulus;
  }
}

// ------------------------------------------------------------------------------
//                        Calculate max depth
// ------------------------------------------------------------------------------

int tree_depth( node * currNode ){
  if( currNode == NULL ) return -1 ;
  return 1 + max( tree_depth( currNode->left ), tree_depth( currNode->right ) );
 }

// ------------------------------------------------------------------------------
//                       Calculate number of leaves
// ------------------------------------------------------------------------------

int tree_noOfLeaves( node * currNode ){
  if( currNode == NULL ) return 0 ;
  if( currNode->left == NULL && currNode->right == NULL ) return 1;

  return tree_noOfLeaves( currNode->left ) +  tree_noOfLeaves( currNode->right ) ;
 }


// ==============================================================================
//                          M  A  I  N
// ==============================================================================

int main(){

  tree_init();
  tree_insert( root, 33 );
  tree_insert( root, 11 );
  tree_insert( root, 22 );
  tree_insert( root, 55 );
  tree_insert( root, 44 );
  tree_insert( root, 66 );

  tree_print( root, 0 );
  tree_destroy( root );

  cout << string( 30, '-') << endl;

  tree_make( 19 , 58 );
  tree_print( root, 0 );
  cout <<  "depth: " << tree_depth( root ) << endl;
  cout <<  "no of leaves: " << tree_noOfLeaves( root ) << endl;
  cout <<  "contains 11? " << tree_contains( root, 11 ) << endl;
  cout <<  "contains 12? " << tree_contains( root, 12 ) << endl;
  tree_destroy( root );

  return 0;
}
