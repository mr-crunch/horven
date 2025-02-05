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
// 4. Change inventory values of specific items in table                 //
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
    cout << "\nEnter item design: ";
    cin >> merchVec[i].merchDesign;
    cout << "\nEnter size: ";
    cin >> merchVec[i].size;
    cout << "\nEnter amount available: ";
    cin >> merchVec[i].amountAvailable;
    merchTable.emplace(merchVec[i].name, merchVec[i]);
  }
}

void findKeys(unordered_map<string, merchItem> &merchTable, int itemCount,
              string item) {
  for (int i = 0; i < itemCount; i++) {
    cout << "enter item id: ";
    cin >> item;
  }
}

void viewFullInventory(unordered_map<string, merchItem> &merchTable,
                       vector<merchItem> &merchVec, string fileName) {
  // output full inventory table
  for (int i = 0; i < merchVec.size(); i++) {
    cout << merchVec[i].name << " ";
    cout << merchVec[i].merchType << " ";
    cout << merchVec[i].merchDesign << " ";
    cout << merchVec[i].size << " ";
    cout << merchVec[i].amountAvailable << endl;
  }
  for (int i = 0; i < merchTable.size(); i++) {
  }
}

void viewCurrentInventory(unordered_map<string, merchItem> &merchTable) {
  // output current inventory of selected items
  // find keys and then output key and amount available
  using merchTableIter = unordered_map<string, merchItem>::const_iterator;
  string item;
  int itemCount;
  cout << "enter the number of items to view: ";
  cin >> itemCount;
  for (int i = 0; i < itemCount; i++) {
    cout << "enter item id: ";
    cin >> item;
    merchTableIter foundItem = merchTable.find(item);
    if (foundItem == merchTable.end()) {
      cout << "item not found" << endl;
      return;
    } else {
      auto &key = foundItem->first;
      auto &item = foundItem->second.amountAvailable;
      cout << key << " amount available: " << item << endl;
    }
  }
}

void editCurrentInventory(unordered_map<string, merchItem> &merchTable,
                          vector<merchItem> &merchVec) {
  // edit current inventory of slected items
  using merchTableIter = unordered_map<string, merchItem>::iterator;
  string item;
  int itemCount, newAmountAvailable;
  cout << "enter the number of items to edit: ";
  cin >> itemCount;
  for (int i = 0; i < itemCount; i++) {
    cout << "enter item id: ";
    cin >> item;
    cout << "\nenter new inventory amount: ";
    cin >> newAmountAvailable;
    merchTableIter foundItem = merchTable.find(item);
    if (foundItem == merchTable.end()) {
      cout << "item not found" << endl;
      return;
    } else {
      auto &key = foundItem->first;
      auto &item = foundItem->second;
      item.amountAvailable = newAmountAvailable;
      cout << key << " amount available: " << item.amountAvailable << endl;
    }
  }
}

void inventorySwitch(vector<merchItem> &merchVec,
                     unordered_map<string, merchItem> &merchTable,
                     int lineCount, string fileName) {
  int choice = 0;
  while (choice != 4) {
    cout << "please select from the available options: " << endl;
    cout << "\t1. view current inventory (full list)" << endl;
    cout << "\t2. view current inventory by item id" << endl;
    cout << "\t3. edit inventory by item id" << endl;
    cout << "\t4. exit to main menu" << endl;
    cin >> choice;
    if (choice > 0 && choice <= 4) {
      switch (choice) {
      case 1: {
        // view current inventory in full
        viewFullInventory(merchTable, merchVec, fileName);
        break;
      }
      case 2: {
        // view current inventory by item id
        viewCurrentInventory(merchTable);
        break;
      }
      case 3: {
        // edit inventory by item id
        editCurrentInventory(merchTable, merchVec);
        break;
      }
      case 4:
        break;
      }
    } else {
      cerr << "invalid input." << endl;
      exit(1);
      return;
    }
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
        cout << "enter file name with file extension: ";
        cin >> fileName;
        lineCount = initLineCount(fileName);
        initMerchTableFromFile(merchVec, merchTable, lineCount, fileName);
        inventorySwitch(merchVec, merchTable, lineCount, fileName);
        // init merch table from file
        // new switch for editing inventory values
        break;
      }
      case 2: {
        // init merch table and new file
        cout << "enter file name with file extension: ";
        cin >> fileName;
        initMerchTable(merchVec, merchTable, lineCount);
        inventorySwitch(merchVec, merchTable, lineCount, fileName);
        break;
      }
      case 3:
        // exit
        break;
      }
    } else {
      cout << "invalid input." << endl;
      return;
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
