#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

string
getInput ()
{
  string fileName;
  cout << "enter file name with file extension: ";
  cin >> fileName;
  return fileName;
}

int
initLineCount ()
{
  ifstream inventoryFile;
  inventoryFile.open ("inventory.txt");
  if (!inventoryFile)
    {
      cerr << "Error: File could not be opened" << endl;
      exit (1);
    }
  inventoryFile.unsetf (ios_base::skipws);
  unsigned lineCount = count (istream_iterator<char> (inventoryFile),
                              istream_iterator<char> (), '\n');
  inventoryFile.close ();
  return lineCount;
}

void
initMerchTable (int lineCount, string fileName)
{
  int merchCategories = 4;
  string tempMerchValue;
  // string **lineCountPtr = initFileMalloc (lineCount);
  /*vector<string> merchTable[merchCategories][lineCount];*/
  vector<vector<string> > merchTable (lineCount,
                                      vector<string> (merchCategories));
  /*vector<vector<string> > merchTable (merchCategories, vector<string>
   * (lineCount, 0));*/
  ifstream inventoryFile;
  inventoryFile.open (fileName);
  if (!inventoryFile)
    {
      cerr << "Error: File could not be opened" << endl;
      exit (1);
    }
  for (int i = 0; i < lineCount; i++)
    {
      for (int j = 0; j < merchCategories; j++)
        {
          inventoryFile >> tempMerchValue;
          merchTable[i].insert (merchTable[i].begin () + j, tempMerchValue);
        }
    }
  inventoryFile.close ();

  for (int i = 0; i < merchTable.size (); i++)
    {
      for (int j = 0; j < merchTable[i].size (); j++)
        {
          cout << merchTable[i][j] << " ";
        }
      cout << endl;
    }
}

/*
string **
initFileMalloc (int lineCount)
{
  string ** lineCountPtr = new (nothrow) string * [lineCount];
  if (lineCountPtr == nullptr)
    {
      cerr << "Error: Memory could not be allocated" << endl;
      exit(1);
    }
  return lineCountPtr;
}
*/

int
main ()
{
  string fileName = getInput ();
  initMerchTable (initLineCount (), fileName);

  return 0;
}
