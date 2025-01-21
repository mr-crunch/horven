#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

///////////////////////////////////////////////////////////////////////////
//                                                                       //
// Things I need to add:                                                 //
// 1. Turn input into data for struct merchItem                          //
// 2. Put merchItems into table                                          //
// 3. Output table to a text file                                        //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

using namespace std;

struct merchItem
{
    string merchType;
    string merchDesign;
    int amountAvailable;
    char size;
};

int initLineCount(string fileName)
{
  ifstream inventoryFile;
  inventoryFile.open(fileName);
  if (!inventoryFile)
  {
    cerr << "Error: File could not be opened" << endl;
    exit(1);
  }
  inventoryFile.unsetf(ios_base::skipws);
  unsigned lineCount = count(istream_iterator<char>(inventoryFile), istream_iterator<char>(), '\n');
  inventoryFile.close();
  return lineCount;
}

void initMerchTableFromFile(vector<merchItem> &merchVector, map<int, merchItem> &merchTable, int lineCount,
                            string fileName)
{
  int rows = 4;
  string tempMerchValue;
  vector<vector<string>> merchVec(lineCount, vector<string>(rows));
  ifstream inventoryFile;
  inventoryFile.open(fileName);
  if (!inventoryFile)
  {
    cerr << "Error: File could not be opened" << endl;
    exit(1);
  }
  for (int i = 0; i < lineCount; i++)
  {
    for (int j = 0; j < rows; j++)
    {
      inventoryFile >> tempMerchValue;
      merchVec[i].insert(merchVec[i].begin() + j, tempMerchValue);
    }
  }
  inventoryFile.close();
  cout << "Merch table initialized" << endl;
}

void initMerchTable(vector<merchItem> &itemVector, map<int, merchItem> &merchTable)
{
}

int main()
{
  merchItem merch;
  map<int, merchItem> merchTable;
  int lineCount;
  string fileName;

  return 0;
}
