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
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/** quick find
 * Implementation of quick find connectivity algorithm, example
 * program 1.1 from Sedgewick Algorithms in C++.
 * 
 * This algorithm determins the connectivity of a set of nodes.
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
void quickFind(string connectivityFileName)
{
  // open file and check we succeeded in finding and opening it,
  // fail immediately with error message if not opened successfully.
  ifstream connectivityFile;
  connectivityFile.open(connectivityFileName.c_str());
  if (not connectivityFile)
  {
    cerr << "<quickFind> Error: could not open specified connectivity file: "
	 << connectivityFileName
	 << endl;
    exit(0);
  }

  // first line is total number of nodes in connectivity graph we are processing
  int N;
  connectivityFile >> N;

  // dynamically allocate array of node ids and initialize them so initially
  // they are all in their own set
  int* id = new int[N];
  for (int i = 0; i < N; i++)
  {
    id[i] = i;
  }

  // process each line of input file, reading in a connected pair of nodes,
  // that we identify as p and q
  int p;
  int q;
  while (connectivityFile >> p >> q)
  {
    //cout << "Processing pair: " << p << "-" << q << endl;

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
  
  // return 0 to indicate successful program completion
  return 0;
}
