#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Struct to represent each record in the linked list
struct RecordNode {
    int id;
    string data;
    RecordNode* next;
};

// LinkedList class to manage records
class LinkedList {
private:
    RecordNode* head;

public:
    LinkedList() : head(nullptr) {}

    // Add a new record to the list
    void addRecord(int id, const string& data) {
        RecordNode* newNode = new RecordNode{id, data, head};
        head = newNode;
    }

    // Display records in the list
    void displayRecords(const string& category, bool sorted = false) {
        loadRecordsFromFile(category);

        if (sorted) {
            vector<RecordNode*> records;
            RecordNode* temp = head;
            while (temp) {
                records.push_back(temp);
                temp = temp->next;
            }
            insertionSort(records);
            for (const auto& record : records) {
                cout << "ID: " << record->id << ", Data: " << record->data << endl;
            }
        } else {
            RecordNode* temp = head;
            while (temp) {
                cout << "ID: " << temp->id << ", Data: " << temp->data << endl;
                temp = temp->next;
            }
        }
    }

    // Insertion sort for sorting records
    void insertionSort(vector<RecordNode*>& records) {
        for (size_t i = 1; i < records.size(); ++i) {
            RecordNode* key = records[i];
            int j = i - 1;
            while (j >= 0 && records[j]->id > key->id) {
                records[j + 1] = records[j];
                --j;
            }
            records[j + 1] = key;
        }
    }

    // Search for a record by ID
    RecordNode* searchRecord(int id) {
        RecordNode* temp = head;
        while (temp) {
            if (temp->id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Delete a record by ID
    void deleteRecord(int id) {
        RecordNode* temp = head;
        RecordNode* prev = nullptr;
        while (temp && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }
        if (temp) {
            if (prev) {
                prev->next = temp->next;
            } else {
                head = temp->next;
            }
            delete temp;
        }
    }

    // Load records from a file
    void loadRecordsFromFile(const string& category) {
        ifstream file(category + ".txt");
        int id;
        string data;
        while (file >> id) {
            getline(file, data);
            addRecord(id, data);
        }
        file.close();
    }

    // Get the head of the list
    RecordNode* getHead() {
        return head;
    }
};

// Load categories from file
void loadCategories(vector<string>& categories) {
    ifstream file("categories.txt");
    string category;
    while (file >> category) {
        categories.push_back(category);
    }
    file.close();
}

// Base User class
class User {
public:
    // Register a new user
    virtual void registerUser(const string& filename) {
        ofstream file(filename, ios::app);
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        file << username << " " << password << endl;
        file.close();
        cout << "Registration successful!" << endl;
    }

    // Login an existing user
    virtual bool loginUser(const string& filename) {
        ifstream file(filename);
        string username, password, inputUsername, inputPassword;
        cout << "Enter username: ";
        cin >> inputUsername;
        cout << "Enter password: ";
        cin >> inputPassword;
        while (file >> username >> password) {
            if (username == inputUsername && password == inputPassword) {
                file.close();
                cout << "Login successful!" << endl;
                return true;
            }
        }
        file.close();
        cout << "Invalid credentials!" << endl;
        return false;
    }

    // Add a new record
    virtual void addNewRecord(LinkedList& list, const string& category) {
        int id;
        string data;
        cout << "Enter record ID: ";
        cin >> id;
        cout << "Enter record data: ";
        cin.ignore();
        getline(cin, data);
        list.addRecord(id, data);

        ofstream file(category + ".txt", ios::app);
        file << id << " " << data << endl;
        file.close();
    }

    // Edit an existing record
    virtual void editRecord(LinkedList& list, const string& category) {
        int id;
        string data;
        cout << "Enter record ID to edit: ";
        cin >> id;
        RecordNode* record = list.searchRecord(id);
        if (record) {
            cout << "Enter new record data: ";
            cin.ignore();
            getline(cin, data);
            record->data = data;

            vector<RecordNode*> records;
            RecordNode* temp = list.getHead();
            while (temp) {
                records.push_back(temp);
                temp = temp->next;
            }
            ofstream file(category + ".txt");
            for (const auto& rec : records) {
                file << rec->id << " " << rec->data << endl;
            }
            file.close();
        } else {
            cout << "Record not found." << endl;
        }
    }

    // Search for a record
    virtual void searchRecord(LinkedList& list) {
        int id;
        cout << "Enter record ID to search: ";
        cin >> id;
        RecordNode* record = list.searchRecord(id);
        if (record) {
            cout << "Record found: ID: " << record->id << ", Data: " << record->data << endl;
        } else {
            cout << "Record not found." << endl;
        }
    }

    // Display records
    virtual void displayRecords(LinkedList& list, bool sorted) {
        string category;
        cout << "Available categories: ";
        vector<string> categories;
        loadCategories(categories);
        for (const auto& cat : categories) {
            cout << cat << " ";
        }
        cout << "\nEnter category to display records: ";
        cin >> category;
        list.displayRecords(category, sorted);
    }

    // Logout the user
    virtual void logout() {
        cout << "Logged out." << endl;
    }
};

// Admin class derived from User
class Admin : public User {
public:
    // Add a new category
    void addCategory() {
        string category;
        cout << "Enter new category name: ";
        cin >> category;
        ofstream file("categories.txt", ios::app);
        file << category << endl;
        file.close();
        cout << "Category added successfully!" << endl;
    }

    // Delete a record
    void deleteRecord(LinkedList& list, const string& category) {
        int id;
        cout << "Enter record ID to delete: ";
        cin >> id;
        list.deleteRecord(id);

        vector<RecordNode*> records;
        RecordNode* temp = list.getHead();
        while (temp) {
            records.push_back(temp);
            temp = temp->next;
        }
        ofstream file(category + ".txt");
        for (const auto& rec : records) {
            file << rec->id << " " << rec->data << endl;
        }
        file.close();
    }
};

// Customer class derived from User {
class Customer : public User {
    // Customer specific functions can be added here if needed
};

// Display the login menu
void displayLoginMenu() {
    cout << "1. Admin Login\n2. Customer Login\n3. Admin Register\n4. Customer Register\n5. Exit\nChoose: ";
}

// Display the admin menu
void displayAdminMenu() {
    cout << "1. Add Record\n2. Edit Record\n3. Delete Record\n4. Search Record\n5. Display Records\n6. Add Category\n7. Logout\nChoose: ";
}

// Display the customer menu
void displayCustomerMenu() {
    cout << "1. Add Record\n2. Edit Record\n3. Search Record\n4. Display Records\n5. Logout\nChoose: ";
}

int main() {
    LinkedList list;
    Admin admin;
    Customer customer;

    vector<string> categories;
    loadCategories(categories);

    int choice;
    while (true) {
        displayLoginMenu();
        cin >> choice;
        if (choice == 1) {
            if (admin.loginUser("admin.txt")) {
                int adminChoice;
                while (true) {
                    displayAdminMenu();
                    cin >> adminChoice;
                    if (adminChoice == 1) {
                        cout << "Available categories: ";
                        for (const auto& cat : categories) {
                            cout << cat << " ";
                        }
                        cout << "\nEnter category: ";
                        string category;
                        cin >> category;
                        admin.addNewRecord(list, category);
                    } else if (adminChoice == 2) {
                        cout << "Available categories: ";
                        for (const auto& cat : categories) {
                            cout << cat << " ";
                        }
                        cout << "\nEnter category: ";
                        string category;
                        cin >> category;
                        admin.editRecord(list, category);
                    } else if (adminChoice == 3) {
                        cout << "Available categories: ";
                        for (const auto& cat : categories) {
                            cout << cat << " ";
                        }
                        cout << "\nEnter category: ";
                        string category;
                        cin >> category;
                        admin.deleteRecord(list, category);
                    } else if (adminChoice == 4) admin.searchRecord(list);
                    else if (adminChoice == 5) {
                        cout << "1. Sorted\n2. Unsorted\nChoose: ";
                        int sortChoice;
                        cin >> sortChoice;
                        admin.displayRecords(list, sortChoice == 1);
                    } else if (adminChoice == 6) {
                        admin.addCategory();
                        loadCategories(categories);
                    } else if (adminChoice == 7) {
                        admin.logout();
                        break;
                    }
                }
            }
        } else if (choice == 2) {
            if (customer.loginUser("customer.txt")) {
                int customerChoice;
                while (true) {
                    displayCustomerMenu();
                    cin >> customerChoice;
                    if (customerChoice == 1) {
                        cout << "Available categories: ";
                        for (const auto& cat : categories) {
                            cout << cat << " ";
                        }
                        cout << "\nEnter category: ";
                        string category;
                        cin >> category;
                        customer.addNewRecord(list, category);
                    } else if (customerChoice == 2) {
                        cout << "Available categories: ";
                        for (const auto& cat : categories) {
                            cout << cat << " ";
                        }
                        cout << "\nEnter category: ";
                        string category;
                        cin >> category;
                        customer.editRecord(list, category);
                    } else if (customerChoice == 3) customer.searchRecord(list);
                    else if (customerChoice == 4) {
                        cout << "1. Sorted\n2. Unsorted\nChoose: ";
                        int sortChoice;
                        cin >> sortChoice;
                        customer.displayRecords(list, sortChoice == 1);
                    } else if (customerChoice == 5) {
                        customer.logout();
                        break;
                    }
                }
            }
        } else if (choice == 3) {
            admin.registerUser("admin.txt");
        } else if (choice == 4) {
            customer.registerUser("customer.txt");
        } else if (choice == 5) {
            break;
        }
    }
    return 0;
}
