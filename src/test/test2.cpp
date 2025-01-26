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

struct merchItem {
    string name;
    string merchType;
    string merchDesign;
    int amountAvailable;
    string size;
};

/*struct textFile*/
/*{*/
/*    string fileName;*/
/*    int lineCount;*/
/**/
/*    int initLineCount(string fileName)*/
/*    {*/
/*      ifstream inventoryFile;*/
/*      inventoryFile.open(fileName);*/
/*      if (!inventoryFile)*/
/*      {*/
/*        cerr << "Error: File could not be opened" << endl;*/
/*        exit(1);*/
/*      }*/
/*      inventoryFile.unsetf(ios_base::skipws);*/
/*      unsigned lineCount = count(istream_iterator<char>(inventoryFile),
 * istream_iterator<char>(), '\n');*/
/*      inventoryFile.close();*/
/*      return lineCount;*/
/*    }*/
/**/
/*    void initMerchTableFromFile(vector<merchItem> &merchVec,
 * unordered_map<int, merchItem> &merchTable, int lineCount,*/
/*                                string fileName)*/
/*    {*/
/*      ifstream inventoryFile;*/
/*      inventoryFile.open(fileName);*/
/*      if (!inventoryFile)*/
/*      {*/
/*        cerr << "Error: File could not be opened" << endl;*/
/*        exit(1);*/
/*      }*/
/*      for (int i = 0; i < merchVec.size(); i++)*/
/*      {*/
/*        inventoryFile >> merchVec[i].name;*/
/*        inventoryFile >> merchVec[i].merchType;*/
/*        inventoryFile >> merchVec[i].merchDesign;*/
/*        inventoryFile >> merchVec[i].size;*/
/*        inventoryFile >> merchVec[i].amountAvailable;*/
/*      }*/
/*      for (int i = 0; i < merchVec.size(); i++)*/
/*      {*/
/*        merchTable.emplace(merchVec[i].name, merchVec[i]);*/
/*      }*/
/*      inventoryFile.close();*/
/*    }*/
/*};*/

int initLineCount(string fileName) {
  ifstream inventoryFile;
  inventoryFile.open(fileName);
  if (!inventoryFile) {
    cerr << "Error: File could not be opened" << endl;
    exit(1);
  }
  inventoryFile.unsetf(ios_base::skipws);
  unsigned lineCount = count(istream_iterator<char>(inventoryFile),
                             istream_iterator<char>(), '\n');
  inventoryFile.close();
  return lineCount;
}

void initMerchTableFromFile(vector<merchItem> &merchVec,
                            unordered_map<string, merchItem> &merchTable,
                            int lineCount, string fileName) {
  ifstream inventoryFile;
  inventoryFile.open(fileName);
  if (!inventoryFile) {
    cerr << "Error: File could not be opened" << endl;
    exit(1);
  }

  for (int i = 0; i < merchVec.size(); i++) {
    inventoryFile >> merchVec[i].name;
    inventoryFile >> merchVec[i].merchType;
    inventoryFile >> merchVec[i].merchDesign;
    inventoryFile >> merchVec[i].size;
    inventoryFile >> merchVec[i].amountAvailable;
  }
  for (int i = 0; i < merchVec.size(); i++) {
    merchTable.emplace(merchVec[i].name, merchVec[i]);
  }
  inventoryFile.close();
}

void outputMerchTable(vector<merchItem> &merchVec, string fileName) {
  ofstream inventoryFile;
  inventoryFile.open(fileName);
  for (int i = 0; i < merchVec.size(); i++) {
    inventoryFile << merchVec[i].name << " ";
    inventoryFile << merchVec[i].merchType << " ";
    inventoryFile << merchVec[i].merchDesign << " ";
    inventoryFile << merchVec[i].size << " ";
    inventoryFile << merchVec[i].amountAvailable << endl;
  }
  inventoryFile.close();
}

void initMerchTable(vector<merchItem> &merchVec,
                    unordered_map<string, merchItem> &merchTable,
                    int lineCount) {
  cout << "Enter the number of items you want to add to the inventory: ";
  cin >> lineCount;
  // cin >> textFile.lineCount;
  // for(int i = 0; i < textFile.lineCount; i++)
  for (int i = 0; i < lineCount; i++) {
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

void mainSwitch(vector<merchItem> &merchVec,
                unordered_map<string, merchItem> &merchTable, int lineCount,
                string fileName) {
  int choice = 0;
  while (choice != 3) {
    cout << "please select from the available options: " << endl;
    cout << "\t1. initialize table from existing file" << endl;
    cout << "\t2. initialize new table and file" << endl;
    cout << "\t3. exit" << endl;
    cin >> choice;
    if (choice > 0 && choice <= 3) {
      switch (choice) {
      case 1: {
        lineCount = initLineCount(fileName);
        initMerchTableFromFile(merchVec, merchTable, lineCount, fileName);
        // init merch table from file
        break;
      }
      case 2: {
        // init merch table and new file
        initMerchTable(merchVec, merchTable, lineCount);
        break;
      }
      case 3:
        // exit
        break;
      }
    }
  }
}

int main() {
  // textFile inventoryFile;
  unordered_map<string, merchItem> merchTable;
  // inventoryFile.lineCount = 12;
  // inventoryFile.fileName = "inventory.txt";
  // vector<merchItem> merchVec(inventoryFile.lineCount, merchItem());
  int lineCount = 12;
  string fileName = "inventory.txt";
  vector<merchItem> merchVec(lineCount, merchItem());
  mainSwitch(merchVec, merchTable, lineCount, fileName);

  return 0;
}
