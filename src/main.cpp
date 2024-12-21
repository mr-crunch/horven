#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using std::cerr;
using std::cin;
using std::count;
using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ios_base;
using std::istream_iterator;
using std::string;
using std::vector;

class merchItem
{
  public:
    string size;
    string availableStock;
    string merchType;
    string merchDesign;
};

string
getInput ()
{
  string fileName;
  cout << "enter file name with extension: ";
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
initMerchTable (int lineCount)
{
  int merchCategories = 4;
  string tempMerchValue;
  vector<vector<string> > merchTable (lineCount,
                                      vector<string> (merchCategories));
  ifstream inventoryFile;

  inventoryFile.open ("inventory.txt");
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
      for (int j = 0; j < merchCategories; j++)
        {
          cout << merchTable[i][j] << " ";
        }
      cout << endl;
    }
}

int
main ()
{
  string fileName = getInput ();
  initMerchTable (initLineCount ());
  /*vector<string> merchList;*/
  /*string tempMerchValue;*/
  /*ifstream inventoryFile;*/
  /*inventoryFile.open ("inventory.txt");*/
  /*if (!inventoryFile)*/
  /*  {*/
  /*    cerr << "Error: File could not be opened" << endl;*/
  /*    exit (1);*/
  /*  }*/
  /*for (int i = 0; i < 4; i++)*/
  /*  {*/
  /*    inventoryFile >> tempMerchValue;*/
  /*    merchList.push_back (tempMerchValue);*/
  /*  }*/
  /*inventoryFile.close ();*/
  /*for (int i = 0; i < 4; i++)*/
  /*  {*/
  /*    cout << merchList[i] << endl;*/
  /*  }*/

  return 0;
}
