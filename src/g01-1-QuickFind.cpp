/**
 * @author Derek Harter
 * @cwid   123 45 678
 * @class  CSci 520, Spring 2022
 * @ide    VSCode Server
 * @date   January 24, 2022
 * @assg   Quick Find
 *
 * @description Quick find connectivity algorithm, example 1.1 from
 *   Sedgewick class textbook.
 */
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/** @brief open file or exit
 *
 * Open file with indicated file name and return an input
 * file stream if successfully opened.  If we fail to open
 * the file, exit immediately.
 *
 * @param fileName A (path) name to a file in filesystem to
 *   attempt to open.
 *
 * @returns ifstream Returns a read only stream connected to the
 *   indicated file if file is found and opened successfully.
 */
ifstream openFileOrExit(string fileName)
{
  // open file and check we succeeded in finding and opening it,
  // fail immediately with error message if not opened successfully.
  ifstream file;

  file.open(fileName.c_str());
  if (not file)
  {
    cerr << "<quickFind> Error: could not open specified connectivity file: " << fileName << endl;
    exit(0);
  }

  // if successful return the opened file stream
  return file;
}

/** @brief initialize set ids
 *
 * Initialize given array of set ids.  Initially all nodes are
 * in their own set, so initialize all ids to be same as node
 * number.
 *
 * @param N The number of nodes in the connectivity set.
 * @param id An integer array of set ids to be initialized.
 *
 * @returns Nothing is returned explicitly, by the array
 *   values of the id parameter will be initialized upon
 *   return.
 */
void initializeSetIds(int N, int id[])
{
  for (int i = 0; i < N; i++)
  {
    id[i] = i;
  }
}

/** @brief quick find
 *
 * Implementation of quick find connectivity algorithm, example
 * program 1.1 from Sedgewick Algorithms in C++.
 *
 * This algorithm determines the connectivity of a set of nodes.
 * This function expects a file name as input, which is a file that
 * can be opened and that contains pairs of connected nodes in the
 * graph.
 *
 * This algorithm represents connected nodes by setting the index
 * of the nodes in an array (representing connected sets) to be
 * equal.  Thus to find if two nodes are connected at any point is
 * trivial, just check if the indexes are currently in the same set.
 * But to perform the union, a scan of the whole array must be done,
 * so given M input pairs, this algorithm takes O(M * N) time to
 * perform the unions on the M pairs of items.
 *
 * @param fileName The name of the file with the connection
 *   pairs used as input for the connectivity algorithm.  We
 *   open this file for reading, and fail immediately if we do
 *   not successfully open the file.  We expect the first line
 *   to contain N, the number of nodes in the connectivity
 *   graph we will be processing.
 */
void quickFind(string fileName)
{
  // open input file for use by algorithm. First line of file is
  // total number of nodes. Dynamically allocate array of ids and
  // initialize them.
  ifstream file = openFileOrExit(fileName);
  int N;
  file >> N;
  int* id = new int[N];
  initializeSetIds(N, id);

  // process each line of input file, reading in a connected pair of nodes,
  // that we identify as p and q
  cout << "quickFind" << endl;
  int p;
  int q;
  while (file >> p >> q)
  {
    // cout << "Processing pair: " << p << "-" << q << endl;

    // First perform a search to see if p and q are already in the same set,
    // because this is quick find, when p and q are in same set then we know
    // they are already connected.
    int setNum = id[p];
    if (id[q] == setNum)
    {
      continue;
    }

    // otherwise search through sets and chance all old set items to be now in
    // the same set as q, since we know p and q are connected
    for (int i = 0; i < N; i++)
    {
      if (id[i] == setNum)
      {
        id[i] = id[q];
      }
    }

    // and output this pair, indicating a new connection found and processed
    cout << p << "-" << q << endl;
  }

  cout << endl;
}

/** @brief quick union
 *
 * Implementation of quick union connectivity algorithm, example
 * program 1.2 from Sedgewick Algorithms in C++.
 *
 * This algorithm determins the connectivity of a set of nodes.
 * This function expects a file name as input, which is a file that
 * can be opened and that contains pairs of connected nodes in the
 * graph.
 *
 * This algorithm provides for quick unions of set.  Basically a
 * tree of connected nodes is built represented connected.
 * As with quick find, initially all nodes in their own tree.
 * When we want to connect two nodes, we first search the tree for
 * the root node of the set tree.  If the root node of the two
 * nodes being connected is the same, the nodes are already
 * connected.  If they differ, we connect them with a union by
 * combining the trees, essentially by setting the root of one of the
 * trees to now point to the other tree root.
 *
 * In best case (as discussed in text), the trees representing
 * the connecivity sets remain relatively balanced.  Thus each
 * find requires about log_2 N sarches to perform when balanced.
 * But can degenerate to N/2, so overall M * N/2 performance in
 * worst case, which is not better than the quick find.
 *
 * @param fileName The name of the file with the connection
 *   pairs used as input for the connectivity algorithm.  We
 *   open this file for reading, and fail immediately if we do
 *   not successfully open the file.  We expect the first line
 *   to contain N, the number of nodes in the connectivity
 *   graph we will be processing.
 */
void quickUnion(string fileName)
{
  // open input file for use by algorithm. First line of file is
  // total number of nodes. Dynamically allocate array of ids and
  // initialize them.
  ifstream file = openFileOrExit(fileName);
  int N;
  file >> N;
  int* id = new int[N];
  initializeSetIds(N, id);

  // process each line of input file, reading in a connected pair of nodes,
  // that we identify as p and q
  cout << "quickUnion" << endl;
  int p;
  int q;
  while (file >> p >> q)
  {
    // search tree that node p is in to find root of the current tree set
    int i;
    for (i = p; i != id[i]; i = id[i])
    {
      // do nothing, the loop terminates when i == id[i] which
      // indicates we are at the root of this tree
    }

    // do same search for root of tree of node q
    int j;
    for (j = q; j != id[j]; j = id[j])
    {
      // do nothing, the loop terminates when j == id[j] which
      // indicates we are at the root of this tree
    }

    // we found the roots of the set trees for nodes p and q, if the
    // root is the same for both nodes, then these nodes are already connected
    if (i == j)
    {
      continue;
    }

    // otherwise we will set the root of the i tree to now point to
    // tree with j as root
    id[i] = j;

    // and output this pair, indicating a new connection found and processed
    cout << p << "-" << q << endl;
  }

  cout << endl;
}

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
  string connectivityFileName = "data/d01-1-connectivity.dat";

  quickFind(connectivityFileName);
  quickUnion(connectivityFileName);

  // return 0 to indicate successful program completion
  return 0;
}
