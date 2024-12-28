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
initLineCount (string fileName)
{
  ifstream inventoryFile;
  inventoryFile.open (fileName);
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
outputMerchTable (vector<vector<string> > &merchTable)
{
  for (int i = 0; i < merchTable.size (); i++)
    {
      for (int j = 0; j < merchTable[i].size (); j++)
        {
          cout << merchTable[i][j] << " ";
        }
      cout << endl;
    }
}

void
editMerchTable (vector<vector<string> > &merchTable)
{

  outputMerchTable (merchTable);
}

void
initMerchTable (int lineCount, string fileName)
{
  int merchCategories = 4;
  string tempMerchValue;
  vector<vector<string> > merchTable (lineCount,
                                      vector<string> (merchCategories));
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
  cout << "merch table initialized" << endl;

  editMerchTable (merchTable);
}

void
initNewFile ()
{
  string fileName;
  cout << "enter new file name with extension: ";
  cin >> fileName;
  fstream inventoryFile;
  inventoryFile.open (fileName);
}

void
printMainMenu ()
{
  cout << "please select from available options: " << endl;
  cout << "\t 1. initialize table from existing file" << endl;
  cout << "\t 2. initialize new file" << endl;
  cout << "\t 3. exit" << endl;
}

int
main ()
{
  int option = -1;
  while (option != 3)
    {
      printMainMenu ();
      cin >> option;
      if (option == 1 && option > 0 && option <= 3)
        {
          switch (option)
            {
            case 1:
              {
                string fileName = getInput ();
                initMerchTable (initLineCount (fileName), fileName);
                break;
              }
            case 2:
              {
                initNewFile ();
                // initialize new file
                break;
              }
            case 3:
              break;
            }
        }
    }

  return 0;
}
