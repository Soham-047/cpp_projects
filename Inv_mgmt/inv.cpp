#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<algorithm>
using namespace std;

struct Item {
    int id;
    string name;
    int quantity;
    double price;
};

const string FILENAME = "inventory.txt";

vector<Item> loadInventory() {
    vector<Item> items;
    ifstream in(FILENAME);
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Item it;
        char sep;
        iss >> it.id >> sep;
        getline(iss, it.name, ',');
        iss >> it.quantity >> sep >> it.price;
        items.push_back(it);
    }
    return items;
}

void saveInventory(const vector<Item>& items) {
    ofstream out(FILENAME, ios::trunc);
    for (auto& it : items) {
        out << it.id << ',' << it.name << ',' << it.quantity << ',' << it.price << "\n";
    }
}

Item* findById(vector<Item>& items, int id) {
    for (auto& it : items) if (it.id == id) return &it;
    return nullptr;
}

void showAll(const vector<Item>& items) {
    cout << "ID\tName\tQuantity\tPrice\n";
    cout << "---------------------------------\n";
    for (auto& it : items) {
        cout << it.id << "\t" << it.name << "\t" << it.quantity << "\t\t" << it.price << "\n";
    }
}

int main() {
    vector<Item> items = loadInventory();
    while (true) {
        cout << "\nMenu: 1=Add, 2=Update, 3=Delete, 4=Show, 5=Exit > ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            Item it;
            cout << "Enter id, name, quantity, price: ";
            cin >> it.id;
            cin.ignore();
            getline(cin, it.name);
            cin >> it.quantity >> it.price;
            items.push_back(it);
            saveInventory(items);
        } else if (choice == 2) {
            cout << "Enter id to update: ";
            int id; cin >> id;
            Item* p = findById(items, id);
            if (p) {
                cout << "New quantity: ";
                cin >> p->quantity;
                cout << "New price: ";
                cin >> p->price;
                saveInventory(items);
            }
        } else if (choice == 3) {
            cout << "Enter id to delete: ";
            int id; cin >> id;
            items.erase(remove_if(items.begin(), items.end(),
                        [id](const Item& i){ return i.id == id; }),
                        items.end());
            saveInventory(items);
        } else if (choice == 4) {
            showAll(items);
        } else {
            break;
        }
    }
    return 0;
}
