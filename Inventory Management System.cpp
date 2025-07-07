#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <conio.h> // For getch() in Windows

using namespace std;

// Structure for item
struct Item {
    int id;
    string name;
    int quantity;
    float price;
};

const string filename = "inventory.txt";

// Hardcoded login credentials
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";
const string USER_USERNAME = "user";
const string USER_PASSWORD = "user123";

// Function declarations
void addItem();
void displayItems();
void searchItem();
void updateItem();
void deleteItem();
void adminMenu();
void userMenu();
string login();
bool isIdUnique(int);
bool parseItem(const string&, Item&);

// Main function
int main() {
    while (true) {
        string role = login();
        if (role == "") break;

        int choice;
        do {
            if (role == "admin") adminMenu();
            else userMenu();

            cout << "Enter your choice: ";
            cin >> choice;

            if (role == "admin") {
                switch (choice) {
                case 1: addItem(); break;
                case 2: displayItems(); break;
                case 3: searchItem(); break;
                case 4: updateItem(); break;
                case 5: deleteItem(); break;
                case 0: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice.\n";
                }
            }
            else {
                switch (choice) {
                case 1: displayItems(); break;
                case 2: searchItem(); break;
                case 0: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice.\n";
                }
            }
        } while (choice != 0);
    }

    return 0;
}

// Login function with masking and option to go back
string login() {
    string uname, pass;
    char ch;
    int option;

    cout << "\n--- Login Page ---\n";
    cout << "1. Admin Login\n";
    cout << "2. User Login\n";
    cout << "0. Exit\n";
    cout << "Select option: ";
    cin >> option;

    if (option == 0) return "";

    cout << "Username: ";
    cin >> uname;

    cout << "Password: ";
    pass = "";
    ch = _getch();
    while (ch != 13) {
        if (ch == 8 && !pass.empty()) {
            cout << "\b \b";
            pass.pop_back();
        }
        else if (ch != 8) {
            pass += ch;
            cout << '*';
        }
        ch = _getch();
    }
    cout << endl;

    if (option == 1 && uname == ADMIN_USERNAME && pass == ADMIN_PASSWORD) {
        cout << "✅ Logged in as Admin.\n";
        return "admin";
    }
    else if (option == 2 && uname == USER_USERNAME && pass == USER_PASSWORD) {
        cout << "✅ Logged in as User.\n";
        return "user";
    }
    else {
        cout << "❌ Invalid credentials. Try again.\n";
        return "";
    }
}

// Admin menu
void adminMenu() {
    cout << "\n--- Admin Menu ---\n";
    cout << "1. Add Item\n";
    cout << "2. Display All Items\n";
    cout << "3. Search Item by ID\n";
    cout << "4. Update Item\n";
    cout << "5. Delete Item\n";
    cout << "0. Logout\n";
}

// User menu
void userMenu() {
    cout << "\n--- User Menu ---\n";
    cout << "1. Display All Items\n";
    cout << "2. Search Item by ID\n";
    cout << "0. Logout\n";
}

// Helper: Parse item from a line
bool parseItem(const string& line, Item& item) {
    stringstream ss(line);
    string temp;

    getline(ss, temp, '|');
    if (temp.empty()) return false;
    item.id = stoi(temp);

    getline(ss, item.name, '|');
    getline(ss, temp, '|');
    item.quantity = stoi(temp);

    getline(ss, temp, '|');
    item.price = stof(temp);

    return true;
}

// Check if ID is unique
bool isIdUnique(int idToCheck) {
    ifstream file(filename);
    string line;
    Item item;

    while (getline(file, line)) {
        if (parseItem(line, item)) {
            if (item.id == idToCheck) return false;
        }
    }
    return true;
}

// Add item
void addItem() {
    ofstream file(filename, ios::app);
    Item item;

    cout << "Enter Item ID: ";
    cin >> item.id;

    if (!isIdUnique(item.id)) {
        cout << "❌ ID already exists. Use a unique ID.\n";
        return;
    }

    cout << "Enter Item Name: ";
    cin.ignore();
    getline(cin, item.name);
    cout << "Enter Quantity: ";
    cin >> item.quantity;
    cout << "Enter Price: ";
    cin >> item.price;

    file << item.id << "|" << item.name << "|" << item.quantity << "|" << item.price << endl;
    file.close();

    cout << "✅ Item added successfully.\n";
}

// Display all items
void displayItems() {
    ifstream file(filename);
    string line;
    Item item;

    cout << "\n--- Inventory List ---\n";
    cout << left << setw(10) << "ID"
        << setw(20) << "Name"
        << setw(10) << "Qty"
        << setw(10) << "Price" << endl;

    while (getline(file, line)) {
        if (parseItem(line, item)) {
            cout << left << setw(10) << item.id
                << setw(20) << item.name
                << setw(10) << item.quantity
                << setw(10) << item.price << endl;
        }
    }

    file.close();
}

// Search item by ID
void searchItem() {
    ifstream file(filename);
    string line;
    Item item;
    int searchId;
    bool found = false;

    cout << "Enter Item ID to search: ";
    cin >> searchId;

    while (getline(file, line)) {
        if (parseItem(line, item) && item.id == searchId) {
            cout << "\nItem Found:\n";
            cout << "ID: " << item.id << "\nName: " << item.name
                << "\nQuantity: " << item.quantity << "\nPrice: " << item.price << endl;
            found = true;
            break;
        }
    }

    if (!found) cout << "❌ Item not found.\n";
    file.close();
}

// Update item
void updateItem() {
    ifstream file(filename);
    ofstream temp("temp.txt");
    string line;
    Item item;
    int updateId;
    bool found = false;

    cout << "Enter Item ID to update: ";
    cin >> updateId;

    while (getline(file, line)) {
        if (parseItem(line, item)) {
            if (item.id == updateId) {
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, item.name);
                cout << "Enter new quantity: ";
                cin >> item.quantity;
                cout << "Enter new price: ";
                cin >> item.price;
                found = true;
            }
            temp << item.id << "|" << item.name << "|" << item.quantity << "|" << item.price << endl;
        }
    }

    file.close();
    temp.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found) cout << "✅ Item updated successfully.\n";
    else cout << "❌ Item not found.\n";
}

// Delete item
void deleteItem() {
    ifstream file(filename);
    ofstream temp("temp.txt");
    string line;
    Item item;
    int deleteId;
    bool found = false;

    cout << "Enter Item ID to delete: ";
    cin >> deleteId;

    while (getline(file, line)) {
        if (parseItem(line, item)) {
            if (item.id == deleteId) {
                found = true;
                continue;
            }
            temp << item.id << "|" << item.name << "|" << item.quantity << "|" << item.price << endl;
        }
    }

    file.close();
    temp.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (found) cout << "✅ Item deleted successfully.\n";
    else cout << "❌ Item not found.\n";
}
