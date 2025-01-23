#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <unordered_map>
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

void initMerchTableFromFile(vector<merchItem> &merchVec, unordered_map<int, merchItem> &merchTable, int lineCount,
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
  inventoryFile.close();
}

void initMerchTable(vector<merchItem> &merchVec, unordered_map<int, merchItem> &merchTable, int lineCount)
{
  cout << "Enter the number of items you want to add to the inventory: ";
  cin >> lineCount;
  for (int i = 0; i < lineCount; i++)
  {
    cout << "Enter item name (TypeSizeDesignNumber): ";
    cin >> merchVec[i].name;
    cout << "\nEnter item type: ";
    cin >> merchVec[i].merchType;
    cout << "\nEnter item design";
    cin >> merchVec[i].merchDesign;
    cout << "\nEnter size: ";
    cin >> merchVec[i].size;
    cout << "\nEnter amount available: ";
    cin >> merchVec[i].amountAvailable;
    merchTable.emplace(merchVec[i].name, merchVec[i]);
  }
}

int main()
{
  merchItem merch;
  unordered_map<int, merchItem> merchTable;
  int lineCount = 12;
  string fileName = "inventory.txt";
  vector<merchItem> merchVec(lineCount, merchItem());
  initMerchTableFromFile(merchVec, merchTable, lineCount, fileName);

  return 0;
}
