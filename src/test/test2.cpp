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
// 5. Implementation of proper file handling                             //
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

void initMerchTableFromFile(unordered_map<string, merchItem> &merchTable,
                            vector<merchItem> &merchVec, int lineCount,
                            string fileName) {
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
  fstream inventoryFile;
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
                    unordered_map<string, merchItem> &merchTable, int lineCount,
                    string fileName) {
  cout << "Enter the number of items you want to add to the inventory: ";
  cin >> lineCount;
  merchVec.resize(lineCount);
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
  outputMerchTable(merchVec, fileName);
}

void viewFullInventory(unordered_map<string, merchItem> &merchTable,
                       vector<merchItem> &merchVec, string fileName) {
  for (auto &merch : merchVec) {
    cout << merch.name << " " << merch.merchType << " " << merch.merchDesign
         << " " << merch.size << " " << merch.amountAvailable << endl;
  }
}

void viewCurrentInventory(unordered_map<string, merchItem> &merchTable) {
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

void updateMerchVec(vector<merchItem> &merchVec, int newAmountAvailable,
                    string item) {
  auto it = find_if(merchVec.begin(), merchVec.end(),
                    [&item](const merchItem &obj) { return obj.name == item; });
  if (it != merchVec.end()) {
    it->amountAvailable = newAmountAvailable;
  } else {
    return;
  }
}

void editCurrentInventory(unordered_map<string, merchItem> &merchTable,
                          vector<merchItem> &merchVec) {
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
    updateMerchVec(merchVec, newAmountAvailable, item);
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
        viewFullInventory(merchTable, merchVec, fileName);
        break;
      }
      case 2: {
        viewCurrentInventory(merchTable);
        break;
      }
      case 3: {
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

void mainSwitch() {
  vector<merchItem> merchVec;
  unordered_map<string, merchItem> merchTable;
  string fileName;
  int lineCount;
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
        merchVec.resize(lineCount);
        initMerchTableFromFile(merchTable, merchVec, lineCount, fileName);
        inventorySwitch(merchVec, merchTable, lineCount, fileName);
        break;
      }
      case 2: {
        cout << "enter file name with file extension: ";
        cin >> fileName;
        initMerchTable(merchVec, merchTable, lineCount, fileName);
        inventorySwitch(merchVec, merchTable, lineCount, fileName);
        break;
      }
      case 3:
        break;
      }
    } else {
      cout << "invalid input." << endl;
      return;
    }
  }
}

int main() {
  mainSwitch();

  return 0;
}
