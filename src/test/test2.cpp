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
    string name;
    string merchType;
    string merchDesign;
    int amountAvailable;
    string size;
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

void initMerchTableFromFile(vector<merchItem> &merchVec, map<int, merchItem> &merchTable, int lineCount,
                            string fileName)
{
  ifstream inventoryFile;
  inventoryFile.open(fileName);
  if (!inventoryFile)
  {
    cerr << "Error: File could not be opened" << endl;
    exit(1);
  }

  for (int i = 0; i < merchVec.size(); i++)
  {
    inventoryFile >> merchVec[i].name;
    inventoryFile >> merchVec[i].merchType;
    inventoryFile >> merchVec[i].merchDesign;
    inventoryFile >> merchVec[i].size;
    inventoryFile >> merchVec[i].amountAvailable;
  }
  for (int i = 0; i < merchVec.size(); i++)
  {
    merchTable.emplace(merchVec[i].name, merchVec[i]);
  }
}

void initMerchTable(vector<merchItem> &itemVector, map<int, merchItem> &merchTable)
{
}

int main()
{
  merchItem merch;
  map<int, merchItem> merchTable;
  int lineCount = 12;
  string fileName = "inventory.txt";
  vector<merchItem> merchVec(lineCount, merchItem());
  initMerchTableFromFile(merchVec, merchTable, lineCount, fileName);

  return 0;
}
