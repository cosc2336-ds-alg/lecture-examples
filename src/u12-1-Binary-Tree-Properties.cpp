/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   November 11, 2019
 * @assg   C++ Binary Tree Properties
 *
 * @description Discuss some properties of binary trees
 *   and look at some implementation issues of binary
 *   search trees.
 */
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/** Binary Tree Node
 * A Node struct/type for internal use to create
 * binary trees.  This is an example of a templatized
 * struct, so we can templatize our binary tree.
 * The item we hold in each node is of some type T.
 * And each node in a binary tree can have a left and/or
 * a right child node.  These should be NULL when
 * there is no child node in that direction, and when
 * both of these are NULL then this current node
 * is a leaf node.
 */
template<class T>
struct BinaryTreeNode
{
  T item;
  BinaryTreeNode<T>* left;
  BinaryTreeNode<T>* right;
};

/** Binary Tree
 * This is an example of a templatized class implementation
 * for a basic binary search tree. The type of item that is
 * contained in the tree is of type T.  The binary tree
 * uses BinaryTreeNode items to organize the tree structure.
 * Nodes are created and deleted dynamically as needed, as
 * items are inserted into and removed from the tree.
 */
template<class T>
class BinaryTree
{
private:
  BinaryTreeNode<T>* root;
  int nodeCount;

  // private methods to implement recursive versions of
  // tree functions that perform the actual work.
  BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, T item);
  string tostring(BinaryTreeNode<T>* node) const;

public:
  BinaryTree();
  ~BinaryTree();

  // methods to manage contents of tree, add and remove items
  void insert(T item);

  // methods for class I/O and testing
  string tostring() const;
  template<typename U>
  friend ostream& operator<<(ostream& out, const BinaryTree<U>& aTree);
};

/** constructor
 * The constructor for our BinaryTree.  Make sure inital tree is empty.
 */
template<class T>
BinaryTree<T>::BinaryTree()
{
  root = NULL;
  nodeCount = 0;
}

/** destructor
 * The destructor for our BinaryTree.  Nodes are created dynamically, so
 * when this tree goes out of scope, make sure that all of the memory
 * of the tree's nodes is correctly freed up and deleted.
 *
 */
template<class T>
BinaryTree<T>::~BinaryTree()
{
  // todo
  // clear();
}

/** insert (private)
 * Private implementation of recursive tree insertion.  Recursively
 * search binary tree to find location where new node should be created,
 * then dynamically create the node and insert it.
 *
 * @param node The node we are currently processing/working on.  Can be
 *   NULL, in which case we are at the location/point to create a new
 *   node dynamically and return it for insertion in the tree.
 * @param item The item to be inserted into the tree.
 *
 * @returns BinaryTreeNode<T>* Returns a pointer to a node struct.  This will
 *   be the newly created node if one is created, or else just the original
 *   node we are given if we don't create a new one.
 */
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::insert(BinaryTreeNode<T>* node, T item)
{
  // base case, when node is null, we need to create a new node dynamically,
  // initialize and return it
  if (node == NULL)
  {
    BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>;
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }

  // otherwise general case.  The node is not null, so determine if we
  // should go left or right in the tree to find location where new node
  // should be placed
  // go left if less or equal to insert
  if (item <= node->item)
  {
    node->left = insert(node->left, item);
  }
  // otherwise go right to insert
  else
  {
    node->right = insert(node->right, item);
  }
  // don't forget to return ourself when we don't create a new
  // node
  return node;
}

/** insert (public)
 * The public interface of insertion into the binary search tree.
 * We simply call the recursive private function to do the actual
 * work of the insertion, starting with our current root node.
 */
template<class T>
void BinaryTree<T>::insert(T item)
{
  root = insert(root, item);
}

/** tree to string (private)
 * Private recursive function of tree to string.  Perform a
 * (recursive) in order traversal of the tree (visit left, display node
 * visit right).  Will cause the tree to be displayed as a sorted
 * list.
 *
 * @param node The node of the tree we are currently traversing.
 *
 * @returns string Returns a string representation of this
 *   tree.
 */
template<class T>
string BinaryTree<T>::tostring(BinaryTreeNode<T>* node) const
{
  // base case, when node is null do nothing
  if (node == NULL)
  {
    return "";
  }

  // otherwise construct a string and return it using an
  // in order traversal
  stringstream out;

  out << tostring(node->left) << node->item << " " << tostring(node->right);

  return out.str();
}

/** tree to string
 * Make a string representation of the current binary tree contents.
 * This function simply returns the tree as a list using an inorder
 * traversal of the tree (visit left, display node, visit right),
 * which if the tree is being correctly maintained, should return
 * the contents of the tree as a sorted list.
 *
 * @returns string Returns a string representation of this tree.
 */
template<class T>
string BinaryTree<T>::tostring() const
{
  stringstream out;

  out << "[ " << tostring(root) << "]";

  return out.str();
}

/** BinaryTree output stream operator
 * Friend function for BinaryTree, overload output stream operator to
 * allow easy output of binary tree representation to an output stream.
 */
template<typename U>
ostream& operator<<(ostream& out, const BinaryTree<U>& aTree)
{
  out << aTree.tostring();
  return out;
}

//-------------------------------------------------------------------------
/** main
 * The main entry point for this program.  Execution of this program
 * will begin with this main function.
 *
 * @param argc The command line argument count which is the number of
 *     command line arguments provided by user when they started
 *     the program.
 * @param argv The command line arguments, an array of character
 *     arrays.
 *
 * @returns An int value indicating program exit status.  Usually 0
 *     is returned to indicate normal exit and a non-zero value
 *     is returned to indicate an error condition.
 */
int main(int argc, char** argv)
{
  BinaryTree<string> tree;

  cout << "Empty tree: " << tree << endl;

  // test insert() and tostring()
  tree.insert("Mark");
  cout << "Inserted item: " << tree << endl;
  tree.insert("Pat");
  cout << "Inserted item: " << tree << endl;
  tree.insert("Susan");
  cout << "Inserted item: " << tree << endl;
  tree.insert("Bob");
  cout << "Inserted item: " << tree << endl;
  tree.insert("Adam");
  cout << "Inserted item: " << tree << endl;
  tree.insert("Clarissa");
  cout << "Inserted item: " << tree << endl;

  return 0;
}
