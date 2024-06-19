#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <limits>

using namespace std;

// Struct to represent each record in the linked list
struct RecordNode {
	
    int id;
    string data;
    string deliveryStatus;
    string receiveStatus; // New field for receive status
    RecordNode* next;
    string superadminpass;
    
};

// LinkedList class to manage records
class LinkedList {
	
private:
	
    RecordNode* head;

public:
	
    LinkedList() : head(nullptr) {}

    // Add a new record to the list
    
    
     void addRecord(int id, const string& data, const string& deliveryStatus, const string& receiveStatus) {
    RecordNode* newNode = new RecordNode{id, data, deliveryStatus, receiveStatus, nullptr};

    if (!head) {
    	
        head = newNode;
        
    } else {
    	
        RecordNode* temp = head;
        
        while (temp->next) {
        	
            temp = temp->next;
            
        }
        
        temp->next = newNode;
        
    }
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
        	
            cout << "\t\tID: " << record->id << ", Data: " << record->data << ", Delivered: " << record->deliveryStatus << ", Received: " << record->receiveStatus << endl;
                 
        }
    } else {
        RecordNode* temp = head;
        while (temp) {
        	
            cout << "\t\tID: " << temp->id << ", Data: " << temp->data << ", Delivered: " << temp->deliveryStatus << ", Received: " << temp->receiveStatus << endl;
            
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
    
    RecordNode* searchRecord(int id, const string& data = "", const string& deliveryStatus = "", const string& receiveStatus = "") {
    RecordNode* temp = head;
    while (temp) {
    	
        // Check if any of the given criteria match
        if ((id == -1 || temp->id == id) &&
            (data.empty() || temp->data == data) &&
            (deliveryStatus.empty() || temp->deliveryStatus == deliveryStatus) &&
            (receiveStatus.empty() || temp->receiveStatus == receiveStatus)) {
            	
            return temp;
            
        }
        
        temp = temp->next;
        
    }
    
    return nullptr; // Return nullptr if not found
    
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
    string line;

    while (getline(file, line)) {
    	
        int id;
        string data, deliveryStatus, receiveStatus;

        stringstream ss(line);
        ss >> id >> data >> deliveryStatus >> receiveStatus;

        addRecord(id, data, deliveryStatus, receiveStatus);
    }

    file.close();
}

    // Get the head of the list
    RecordNode* getHead() {
    	
        return head;
        
    }
};

// Function to load categories from file into a vector
void loadCategories(vector<string>& categories) {
    ifstream file("categories.txt"); // Open the file "categories.txt" for reading
    string category; // Variable to store each category read from the file
    
    // Check if the file opened successfully
    if (!file.is_open()) {
        cout << "\t\tError opening file 'categories.txt'\n";
        return;
    }
    
    // Read each category from the file
    while (file >> category) {
        categories.push_back(category); // Add each category to the vector
    }
    
    file.close(); // Close the file
}

// Base User class
class User {
public:
    // Register a new user
virtual void registerUser(const string& filename) {
    ofstream writeFile;
    ifstream readFile;
    string username, password, line, storedUsername, storedPassword;
    bool userExists;

    cout << "---------------------------------------";
    cout << "\n";

    do {
        cout << "Enter username: ";
        cin >> username;

        userExists = false;

        // Open file for reading
        readFile.open(filename);

        // Check if the username already exists
        while (getline(readFile, line)) {
            istringstream iss(line);
            iss >> storedUsername >> storedPassword;
            if (storedUsername == username) {
                userExists = true;
                break;
            }
        }

        readFile.close();

        if (userExists) {
            cout << "Username already exists. Please choose a different username." << endl;
        }
    } while (userExists);

    cout << "Enter password: ";
    cin >> password;

    // Open file for appending
    writeFile.open(filename, ios::app);
    writeFile << username << " " << password << endl;
    writeFile.close();

    cout << "Registration successful!" << endl;

}

    // Login an existing user
    virtual bool loginUser(const string& filename) {
    	
        ifstream file(filename);
        string username, password, inputUsername, inputPassword;
        
		cout << "\t\t---------------------------------------"<<endl;
		cout << "\t\t\tLOGIN"<<endl;
        cout << "\t\t---------------------------------------"<<endl;
        cout << "\n";
        
        cout << "\t\tEnter username: ";
        cin >> inputUsername;
        
        cout << "\t\tEnter password: ";
        cin >> inputPassword;
        
        while (file >> username >> password) {
            if (username == inputUsername && password == inputPassword) {
            	
                file.close();
                cout <<"\n";
                cout << "\t\t======================================="<<endl;
				cout <<"\n";
                cout << "\t\tLogin successful! ! !" << endl;
                system("pause");
                system("cls");
                return true;
                
            }
        }
        
        file.close();
        cout << "\t\t======================================="<<endl;
        cout << "Invalid credentials!" << endl;
        system("pause");
        system("cls");
        return false;
        
    }

// Function to add a new record
void addNewRecordUser(LinkedList& list, const string& category) {
    int id;
    string data, deliveryStatus, receiveStatus;
    ifstream readFile;
    bool idExists;

    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\tADD RECORD" << endl;
    cout << "\t\t---------------------------------------" << endl;

    do {
        cout << "\t\tEnter record ID: ";
        cin >> id;
        idExists = false;

        // Open file for reading
        readFile.open(category + ".txt");

        // Check if the ID already exists
        string line;
        while (getline(readFile, line)) {
            istringstream iss(line);
            int storedId;
            iss >> storedId >> data >> deliveryStatus >> receiveStatus;
            if (id == storedId) {
                idExists = true;
                break;
            }
        }

        readFile.close();

        if (idExists) {
            cout << "\t\tID already exists. Please enter a different ID." << endl;
        }
    } while (idExists);

    // Capture the rest of the data for the record
    cout << "\t\tEnter record data: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, data);

while (true) {
        cout << "\t\tEnter delivery status (yes/no): ";
        getline(cin, deliveryStatus);

        // Convert input to lowercase for case-insensitive comparison
        for (char &c : deliveryStatus) {
            c = tolower(c);
        }

        // Check if the input is valid
        if (deliveryStatus == "yes" || deliveryStatus == "no") {
            break; // Exit loop if valid input
        } else {
            cout << "\t\tInvalid input! Please enter 'yes' or 'no'.\n";
        }
    }

    // Input validation loop for receive status
    while (true) {
        cout << "\t\tEnter receive status (received/not received): ";
        getline(cin, receiveStatus);

        // Convert input to lowercase for case-insensitive comparison
        for (char &c : receiveStatus) {
            c = tolower(c);
        }

        // Check if the input is valid
        if (receiveStatus == "received" || receiveStatus == "not received") {
            break; // Exit loop if valid input
        } else {
            cout << "\t\tInvalid input! Please enter 'received' or 'not received'.\n";
        }
    }

    // Add the record to the linked list
    list.addRecord(id, data, deliveryStatus, receiveStatus);

    // Append the record to the file
    ofstream file(category + ".txt", ios::app);
    file << id << " " << data << " " << deliveryStatus << " " << receiveStatus << endl;
    file.close();

    cout << "\t\tRecord added successfully!" << endl;
}
    

   void editRecord(LinkedList& list, const string& category) {
    int id;
    string data, deliveryStatus, receiveStatus;

    system("cls");
    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t EDIT RECORD" << endl;
    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\tEnter record ID to edit: ";
    cin >> id;

    RecordNode* record = list.searchRecord(id);

    if (record) {
        system("cls");
        cout << "\n";
        cout << "\t\t---------------------------------------" << endl;
        cout << "\t\tEnter new record data: ";
        cin.ignore();
        getline(cin, data);

        cout << "\t\tEnter new delivery status (yes/no): ";
        getline(cin, deliveryStatus);

        cout << "\t\tEnter new receive status (received/not received): ";
        getline(cin, receiveStatus);

        // Update the record in memory
        record->data = data;
        record->deliveryStatus = deliveryStatus;
        record->receiveStatus = receiveStatus;

        // Open the file and rewrite all records
        ofstream file(category + ".txt");
        RecordNode* temp = list.getHead();
        while (temp) {
            file << temp->id << " " << temp->data << " " << temp->deliveryStatus << " " << temp->receiveStatus << endl;
            temp = temp->next;
        }
        file.close();

        cout << "\t\tRecord updated successfully and saved to file!" << endl;

    } else {
        cout << "\t\t---------------------------------------" << endl;
        cout << "\t\tRecord not found." << endl;
    }
}

    // Search for a record
    void searchRecord(LinkedList& list) {
        int id;
        string data, deliveryStatus, receiveStatus;

        cout << "\t\t---------------------------------------" << endl;
        cout << "\t\t\t\t SEARCH"<<endl;
        cout << "\t\t---------------------------------------" << endl;

        cout << "\t\tEnter record ID to search (-1 to skip): ";
        cin >> id;

        RecordNode* record = list.searchRecord(id, data, deliveryStatus, receiveStatus);

        if (record) {
            cout << "\t\tRecord found: ID: " << record->id << ", Data: " << record->data
                 << ", Delivered: " << record->deliveryStatus
                 << ", Received: " << record->receiveStatus << endl;
        } else {
            cout << "Record not found." << endl;
        }
    }


    // Display records
void displayRecords(LinkedList& list, bool sorted) {
    string category;
    system("cls");
    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t DISPLAY RECORDS"<< endl;
    cout << "\t\t---------------------------------------" << endl;
    
    vector<string> categories;
    loadCategories(categories);
    
    cout << "\t\tAvailable categories: ";
    for (size_t i = 0; i < categories.size(); ++i) {
        cout <<"\n\t\t"<< i + 1 << ". " << categories[i] << " ";
    }
    cout << "\n";
    cout << "\t\t---------------------------------------" << endl;

    cout << "\t\tEnter category to display records: ";
    cin >> category;
    list.loadRecordsFromFile(category);

    if (sorted) {
        vector<RecordNode*> records;
        RecordNode* temp = list.getHead();
        while (temp) {
            records.push_back(temp);
            temp = temp->next;
        }

        list.insertionSort(records);

        for (const auto& record : records) {
            cout << "\t\tID: " << record->id << ", Data: " << record->data
                 << ", Delivered: " << record->deliveryStatus
                 << ", Received: " << record->receiveStatus << endl;
        }
    } else {
        RecordNode* temp = list.getHead();
        while (temp) {
            cout << "\t\tID: " << temp->id << ", Data: " << temp->data
                 << ", Delivered: " << temp->deliveryStatus
                 << ", Received: " << temp->receiveStatus << endl;
            temp = temp->next;
        }
    }
}


    // Logout the user
    virtual void logout() {
    	
        cout << "\t\tLogged out." << endl;
        cout << "\t\t---------------------------------------";
        
    }
};

// Admin class derived from User
class Admin : public User {
public:
    // Add a new category
// Function to add a new category and create a corresponding text file
void addCategory() {
    string category;
    
    // Prompt user for category name
    cout << "\t\tEnter new category name: ";
    getline(cin >> ws, category); // Use getline to read the category name, and ws to skip leading whitespace
    
    // Open file with category name as the file name
    ofstream file("categories.txt", ios::app);
    
    if (!file.is_open()) {
        cout << "\t\tError creating file '" << category << ".txt'\n";
        return;
    }
    
    file << category << endl;
    
    // Optionally, write category details or contents to the file
    // file << "Details for category: " << category << endl;
    
    file.close();
    
    // Provide feedback to the user
    cout << "\t\tCategory '" << category << "' added to file '" << category << ".txt' successfully!\n";
}

    // Delete a record
    void deleteRecord(LinkedList& list, const string& category) {
    	
        int id;
        cout << "\t\t---------------------------------------"<<endl;
        cout << "\t\t\t\t DELETE RECORD "<<endl;
        cout << "\t\t---------------------------------------"<<endl;
        cout << "\n";
        
        cout << "\t\tEnter record ID to delete: ";
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

	cout << "\t\t---------------------------------------"<<endl;
	cout << "\t\t\t\tMain Menu"<<endl;
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\n";
    cout << "\t\t1. Admin \n";
	cout << "\t\t2. Customer \n";
	cout << "\t\t3. Exit\n";
	cout << "\t\t========================================"<<endl;
	cout << "\t\tChoose: ";	
}
//login and register admin
void displayLoginMenuAdmin() {
	system("cls");
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\t\tLogin And Register For Admin"<<endl;
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\n";
    cout << "\t\t1. Admin Register\n";
	cout << "\t\t2. Admin Login\n";
	cout << "\t\t3. Exit\n";
	cout << "\t\t========================================"<<endl;	
	cout << "\t\tChoose: ";
	
}

//login and register customer 
void displayLoginMenuCustomer() {
	system("cls");
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\t\tLogin And Register For Customer"<<endl;
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\n";
	cout << "\t\t1. Customer Register\n";
	cout << "\t\t2. Customer Login\n";
	cout << "\t\t3. Exit\n";
	cout << "\t\t========================================"<<endl;	
	cout << "\t\tChoose: ";
	
}
// Display the admin menu
void displayAdminMenu() {
	system("cls");
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\t\t\t\t Main Menu"<<endl;
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\n";
    cout << "\t\t1. Add Record\n"<<endl;
	cout << "\t\t2. Edit Record\n"<<endl;
	cout << "\t\t3. Delete Record\n"<<endl;
	cout << "\t\t4. Search Record\n"<<endl;
	cout << "\t\t5. Display Records\n"<<endl;
	cout << "\t\t6. Add Category\n"<<endl;
	cout << "\t\t7. Display Customer Information\n" << endl;
	cout << "\t\t8. Read Feedback\n" << endl;
	cout << "\t\t9. View Categories\n" << endl;
	cout << "\t\t10. Delete Category\n" << endl;
	cout << "\t\t11. Logout\n"<<endl;
	cout << "\t\t========================================"<<endl;	
	cout << "\t\tChoose: ";
	
}

// Display the customer menu
void displayCustomerMenu() {
	system("cls");
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\t\t\t\t Main Menu"<<endl;
	cout << "\t\t---------------------------------------"<<endl;
	cout << "\n";
    cout << "\t\t1. Add Record\n"<<endl;
	cout << "\t\t2. Edit Record\n"<<endl;
	cout << "\t\t3. Search Record\n"<<endl;
	cout << "\t\t4. Display Records\n"<<endl;
	cout << "\t\t5. Provide Feedback\n" << endl; 
	cout << "\t\t6. How to use each feature\n" << endl; 
	cout << "\t\t7. Check Password\n" << endl;
	cout << "\t\t8. change Username\n" << endl;
	cout << "\t\t9. Delete Account\n" << endl;
	cout << "\t\t0. Logout\n"<<endl;
	cout << "\t\t========================================"<<endl;
	cout << "\t\tChoose: ";
	
}
//welcome page
void welcome(){
	system("cls");
				 cout << endl;
    cout << "\t\t\t___]--=============----------------------------------------------------=============--[___" << endl;
	cout << "\t\t\t-------------------===============+++=====++++++=====+++===============-------------------"  << endl;
    cout << "\t\t\t       |                                                                          |       " << endl;
    cout << "\t\t\t       |                                                                          |       " << endl;
    cout << "\t\t\t       |                                                                          |       " << endl;
    cout << "\t\t\t       |\t\t\t  " <<"WELCOME TO TX EXPRESS SYSTEM"<<"                    |" << endl;
    cout << "\t\t\t       |                                                                          |       " << endl;
    cout << "\t\t\t       |                                                                          |       " << endl;
    cout << "\t\t\t       |                                                                          |       "  << endl;
	cout << "\t\t\t_______________||--===============+++=====++++++=====+++===============--||________________" << endl;
    cout << "\t\t\t----------------[________________________________________________________]----------------"  << endl << endl << endl;

    system("pause");
    system("cls");
	}

// Function to display all usernames and passwords from customer.txt
void displayCustomerInfo() {
    ifstream file("customer.txt");
    string line;

    if (!file.is_open()) {
        cout << "Unable to open file 'customer.txt'\n";
        return;
    }

    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t CUSTOMER INFORMATION" << endl;
    cout << "\t\t---------------------------------------" << endl;
	cout << "\t\t UserName   Password"<<endl;
    while (getline(file, line)) {
    	string username, password;

        stringstream ss(line);
        ss >> username >> password;
        cout << "   \t\t" << username<<"\t"<<password<< endl; // Assuming each line contains username and password
    }

    file.close();
    cout << "\t\t---------------------------------------" << endl;
}

// Function to display feedback from feedback.txt
void displayFeedback() {
    ifstream file("feedback.txt");
    string line;

    if (!file.is_open()) {
        cout << "\t\tUnable to open file 'feedback.txt'\n";
        return;
    }

    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t FEEDBACK INFORMATION" << endl;
    cout << "\t\t---------------------------------------" << endl;

    while (getline(file, line)) {
        cout << "\t\t" << line << endl; // Assuming each line contains username and feedback
    }

    file.close();
    cout << "\t\t---------------------------------------" << endl;
}

// Function to validate phone number format
bool isValidPhoneNumber(const string& phoneNumber) {
    if (phoneNumber.length() == 10 || phoneNumber.length() == 11) {
        if (phoneNumber.substr(0, 2) == "01") {
            for (char c : phoneNumber) {
                if (!isdigit(c)) {
                    return false; // Phone number contains non-digit characters
                }
            }
            return true; // Valid phone number format
        }
    }
    return false; // Invalid phone number length or format
}

// Function for customers to provide feedback
void provideFeedback() {
    ofstream file("feedback.txt", ios::app); // Open file in append mode

    if (!file.is_open()) {
        cout << "\t\tUnable to open file 'feedback.txt' for writing\n";
        return;
    }

    string phoneNumber;
    bool validPhoneNumber = false;

    // Input validation loop for phone number format
    do {
        cout << "\t\tEnter your phone number (starting with '01' and 10 or 11 digits): ";
        cin >> phoneNumber;

        // Validate phone number format
        validPhoneNumber = isValidPhoneNumber(phoneNumber);

        if (!validPhoneNumber) {
            cout << "\t\tInvalid phone number format. Please enter a number starting with '01' and with 10 or 11 digits.\n";
        }
    } while (!validPhoneNumber);

    string feedback;
    cout << "\t\tEnter your feedback: ";
    cin.ignore(); // Clear input buffer
    getline(cin, feedback);

    // Write username, phone number, and feedback to file
    file <<" Phone Number: " << phoneNumber << ", Feedback: " << feedback << endl;

    file.close();
    cout << "\t\tThank you for your feedback!\n";
}




void viewCategories() {
    vector<string> categories;

    // Read categories from file
    ifstream file("categories.txt");
    string category;

    while (getline(file, category)) {
        categories.push_back(category);
    }

    file.close();

    // Display categories
    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t AVAILABLE CATEGORIES" << endl;
    cout << "\t\t---------------------------------------" << endl;

    for (size_t i = 0; i < categories.size(); ++i) {
        cout << "\t\t" << i + 1 << ". " << categories[i] << endl;
    }

    cout << "\t\t---------------------------------------" << endl;
}

void deleteCategory() {
    vector<string> categories;
    loadCategories(categories);

    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t AVAILABLE CATEGORIES" << endl;
    cout << "\t\t---------------------------------------" << endl;

    for (size_t i = 0; i < categories.size(); ++i) {
        cout << "\t\t" << i + 1 << ". " << categories[i] << endl;
    }

    cout << "\t\t---------------------------------------" << endl;

    cout << "\t\tSelect category to delete (enter number): ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= categories.size()) {
        string deletedCategory = categories[choice - 1];
        categories.erase(categories.begin() + choice - 1);

        ofstream file("categories.txt");
        if (file.is_open()) {
            for (const auto& category : categories) {
                file << category << endl;
            }
            file.close();
            cout << "\t\tCategory '" << deletedCategory << "' deleted successfully from 'categories.txt'!\n";
        } else {
            cout << "\t\tError: Unable to open 'categories.txt' for writing\n";
            return;
        }

        // Optionally, you may want to inform the user that the associated .txt file is not deleted.
        cout << "\t\tNote: Associated file '" << deletedCategory << ".txt' is not deleted.\n";
    } else {
        cout << "\t\tInvalid choice\n";
    }
}


void displayHelp() {
    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t SYSTEM HELP" << endl;
    cout << "\t\t---------------------------------------" << endl;
    
    cout << "\t\t1. Add Record:\n";
    cout << "\t\t   Allows you to add a new record to the system.\n";
    cout << "\t\t   You will be prompted to enter details such as ID, data,\n";
    cout << "\t\t   delivery status, and receive status.\n";
    
    cout << "\t\t2. Edit Record:\n";
    cout << "\t\t   Allows you to edit an existing record in the system.\n";
    cout << "\t\t   You can modify fields like data, delivery status,\n";
    cout << "\t\t   and receive status based on the record ID.\n";
    
    cout << "\t\t3. Delete Record:\n";
    cout << "\t\t   Enables you to delete a record from the system.\n";
    cout << "\t\t   You need to specify the ID of the record to delete.\n";
    
    cout << "\t\t4. Search Record:\n";
    cout << "\t\t   Allows you to search for records based on keywords\n";
    cout << "\t\t   or specific criteria. Results will be displayed if found.\n";
    
    cout << "\t\t5. Display Records:\n";
    cout << "\t\t   Displays all records currently stored in the system.\n";
    cout << "\t\t   You can choose to display records sorted or unsorted.\n";
    
    cout << "\t\t6. Add Category:\n";
    cout << "\t\t   Adds a new category to classify records.\n";
    cout << "\t\t   Each category can have multiple records associated with it.\n";
    
    cout << "\t\t7. Display Customer Information:\n";
    cout << "\t\t   Shows information about customers stored in the system.\n";
    cout << "\t\t   This may include details like usernames, addresses, etc.\n";
    
    cout << "\t\t8. Read Feedback:\n";
    cout << "\t\t   Allows administrators to read feedback provided by customers.\n";
    cout << "\t\t   Feedback is stored in a 'feedback.txt' file with timestamps.\n";
    
    cout << "\t\t9. Logout:\n";
    cout << "\t\t   Logs out the current user from the system.\n";
    
    cout << "\t\t---------------------------------------" << endl;
}

void viewcheckpassword(const string& username) {
    ifstream file("customer.txt");
    if (!file.is_open()) {
        cout << "\t\tUnable to open file 'customer.txt'\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            cout << "\t\tProfile  Password : " << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\t\tProfile for '" << username << "' not found.\n";
    }

    file.close();
}


void deleteAccount(const string& username) {
    ifstream infile("customer.txt");
    ofstream outfile("temp.txt");

    if (!infile.is_open() || !outfile.is_open()) {
        cout << "\t\tError opening file.\n";
        return;
    }

    string line, storedUsername;
    bool found = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        ss >> storedUsername;

        if (storedUsername == username) {
            found = true;
            cout << "\t\tAccount '" << storedUsername << "' deleted successfully.\n";
        } else {
            outfile << line << endl;
        }
    }

    infile.close();
    outfile.close();

    remove("customer.txt");
    rename("temp.txt", "customer.txt");

    if (!found) {
        cout << "\t\tUsername '" << username << "' not found.\n";
    }
}






int main() {
    LinkedList list;
    Admin admin;
    Customer customer;

    vector<string> categories;
    loadCategories(categories);

    int choice,choice1;
    while (true) {
    	
    	welcome();
        displayLoginMenu();
        cin >> choice1;
        
        if(choice1 == 1)
        {
        	displayLoginMenuAdmin();
        	cin >> choice;
        	
        	if (choice == 1) 
			{
            ofstream writeFile;
    ifstream readFile;
    string username, password, line, storedUsername, storedPassword;
    bool userExists;
    system("cls");

    cout << "\t\t---------------------------------------"<<endl;
    cout << "\t\t\tREGISTER ADMIN"<<endl;
	cout << "\t\t---------------------------------------"<<endl;

    cout << "\n";

    do {
        cout << "\t\tEnter username: ";
        cin >> username;

        userExists = false;

        // Open file for reading
        readFile.open("admin.txt");

        // Check if the username already exists
        while (getline(readFile, line)) {
            istringstream iss(line);
            iss >> storedUsername >> storedPassword;
            if (storedUsername == username) {
                userExists = true;
                break;
            }
        }

        readFile.close();

        if (userExists) {
            cout << "\t\tUsername already exists. Please choose a different username." << endl;
        }
    } while (userExists);

    cout << "\t\tEnter password: ";
    cin >> password;

    // Open file for appending
    writeFile.open("admin.txt", ios::app);
    writeFile << username << " " << password << endl;
    writeFile.close();

    cout << "\t\tRegistration successful!" << endl;
    system("pause");
    system("cls");
		if (admin.loginUser("admin.txt")) {
                int adminChoice;
                
                while (true) {
                	
                    displayAdminMenu();
                    cin >> adminChoice;
                    
                    if (adminChoice == 1) {
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tADD RECORD"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n"<< endl;
                        cout << "\t\t---------------------------------------"<< endl;
                        cout << "\n\t\tEnter category: ";
                        
                        string category;
                        cin >> category;
                        admin.addNewRecordUser(list, category);
                        system("pause");
                        system("cls");
                    } else if (adminChoice == 2) {
                    	
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\t\t\t\t EDIT RECORD"<< endl;
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------"<< endl;
                        
                        cout << "\n\t\tEnter category: ";
                        
                        string category;
                        cin >> category;
                        admin.editRecord(list, category);
                        system("pause");
                        system("cls");
                        
                    } else if (adminChoice == 3) {
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\t\t\t\tDELETE RECORD"<< endl;
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------"<< endl;
                        
                        cout << "\n\t\tEnter category: ";
                        
                        string category;
                        cin >> category;
                        admin.deleteRecord(list, category);
                        system("pause");
                        system("cls");
                        
                    } else if (adminChoice == 4) {
                    	system("cls");
                    	admin.searchRecord(list);
                    	system("pause");
					}
                    
                    else if (adminChoice == 5) {
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\t\t\t\tDISPLAY"<< endl;
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\n";
                        cout << "\t\t1. Sorted\n"<< endl;
						cout << "\t\t2. Unsorted\n"<< endl;
						cout << "\t\t======================================="<< endl;
						cout << "Choose: ";
                        
                        int sortChoice;
                        cin >> sortChoice;
                        
                        admin.displayRecords(list, sortChoice == 1);
                        system("pause");
                        
                    } else if (adminChoice == 6) {
                    	system("cls");
                        admin.addCategory();
                        loadCategories(categories);
                        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                    } else if (adminChoice == 7) {
                    	system("cls");
                    	displayCustomerInfo();
						system("pause");
                        
                    }else if (adminChoice == 8) {
                    	system("cls");
						displayFeedback();
                        system("pause");
                        
                    }else if (adminChoice == 9) {
                    	system("cls");
						viewCategories();
                        system("pause");
                        
                    }else if (adminChoice == 10) {
						system("cls");
						deleteCategory();
                      	system("pause");
                    }else if (adminChoice == 11) {
                        admin.logout();
                        break;
                        
                    }
                }
            }
			
        	}else if (choice == 2) 
			{
        	
            if (admin.loginUser("admin.txt")) {
                int adminChoice;
                
                while (true) {
                	
                    displayAdminMenu();
                    cin >> adminChoice;
                    
                    if (adminChoice == 1) {
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tADD RECORD"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------"<< endl;
                        cout << "\n\t\tEnter category: ";
                        
                        string category;
                        cin >> category;
                        admin.addNewRecordUser(list, category);
                        system("pause");
                        system("cls");
                    } else if (adminChoice == 2) {
                    	
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\t\t\t\t EDIT RECORD"<< endl;
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------"<< endl;
                        
                        cout << "\n\t\tEnter category: ";
                        
                        string category;
                        cin >> category;
                        admin.editRecord(list, category);
                        system("pause");
                        system("cls");
                        
                    } else if (adminChoice == 3) {
                    	
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\t\t\t\tDELETE RECORD"<< endl;
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------"<< endl;
                        
                        cout << "\n\t\tEnter category: ";
                        
                        string category;
                        cin >> category;
                        admin.deleteRecord(list, category);
                        system("pause");
                        system("cls");
                        
                    } else if (adminChoice == 4) {
                    	admin.searchRecord(list);
					}
                    
                    else if (adminChoice == 5) {
                    	
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\t\t\t\tDISPLAY"<< endl;
                    	cout << "\t\t---------------------------------------"<< endl;
                    	cout << "\n";
                        cout << "\t\t1. Sorted\n"<< endl;
						cout << "\t\t2. Unsorted\n"<< endl;
						cout << "\t\t======================================="<< endl;
						cout << "\t\tChoose: ";
                        
                        int sortChoice;
                        cin >> sortChoice;
                        
                        admin.displayRecords(list, sortChoice == 1);
                        system("pause");
                    } else if (adminChoice == 6) {
                    	
                        admin.addCategory();
                        loadCategories(categories);
                        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                    } else if (adminChoice == 7) {
                    	system("cls");
                    	displayCustomerInfo();
						system("pause");
                        
                    }else if (adminChoice == 8) {
                    	system("cls");
						displayFeedback();
                        system("pause");
                        
                    }else if (adminChoice == 9) {
                    	system("cls");
						viewCategories();
                        system("pause");
                        
                    }else if (adminChoice == 10) {
						system("cls");
						deleteCategory();
                      	system("pause");
                    }else if (adminChoice == 11) {
                        admin.logout();
                        break;
                        
                    }
                }
            }
                
            
        }else if (choice == 3) {
            break;
        }//end choice admin
        	
		}else if (choice1 == 2){
			
			displayLoginMenuCustomer();
			cin >> choice;
			
		if (choice == 1) {
        	ofstream writeFile;
    ifstream readFile;
    string username, password, line, storedUsername, storedPassword;
    bool userExists;
	system("cls");
    cout << "\t\t---------------------------------------"<<endl;
    cout << "\t\t\tREGISTER CUSTOMER"<<endl;
	cout << "\t\t---------------------------------------"<<endl;

    cout << "\n";

    do {
        cout << "\t\tEnter username: ";
        cin >> username;

        userExists = false;

        // Open file for reading
        readFile.open("customer.txt");

        // Check if the username already exists
        while (getline(readFile, line)) {
            istringstream iss(line);
            iss >> storedUsername >> storedPassword;
            if (storedUsername == username) {
                userExists = true;
                break;
            }
        }

        readFile.close();

        if (userExists) {
            cout << "\t\tUsername already exists. Please choose a different username." << endl;
        }
    } while (userExists);

    cout << "\t\tEnter password: ";
    cin >> password;

    // Open file for appending
    writeFile.open("customer.txt", ios::app);
    writeFile << username << " " << password << endl;
    writeFile.close();

    cout << "\t\tRegistration successful!" << endl;
    system("pause");
    system("cls");
    if (customer.loginUser("customer.txt")) {
                int customerChoice;
                
                while (true) {
                	
                    displayCustomerMenu();
                    cin >> customerChoice;
                    
                    if (customerChoice == 1) {
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\t ADD RECORD"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------";
                        
                        cout << "\n\t\tEnter category: ";
                        
                        string category;
                        cin >> category;
                        customer.addNewRecordUser(list, category);
                        system("pause");
                    } else if (customerChoice == 2) {
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\t EDIT RECORD"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------";
                        
                        cout << "\n\t\Enter category: ";
                        
                        string category;
                        cin >> category;
                        
                        customer.editRecord(list, category);
                        system("pause");
                    } else if (customerChoice == 3) 
					{
						system("cls");
						customer.searchRecord(list);
						system("pause");
					}
                    else if (customerChoice == 4) {
                    	
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tDISPLAY RECORD"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\n";
                    	
                        cout << "\t\t1. Sorted\n";
						cout << "\t\t2. Unsorted\n";
						cout << "\t\tChoose: ";
						
                        int sortChoice;
                        cin >> sortChoice;
                        
                        customer.displayRecords(list, sortChoice == 1);
                        
                    } else if (customerChoice == 5) {
                    	system("cls");
                        provideFeedback();
                        system("pause");
						
                    }else if (customerChoice == 6) {
                        system("cls");
						displayHelp();
						system("pause");
                    }else if (customerChoice == 7) {
                    	system("cls");
                    	string username;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tView Account "<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\tWhat is your username : ";
                    	cin >> username;
                        viewcheckpassword(username);
						system("pause");
                    }else if (customerChoice == 8) {
                    	system("cls");
                    	string username;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tEdit Account Name"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\tWhat is your username : ";
                    	cin >> username;
                        ifstream infile("customer.txt");
    ofstream outfile("temp.txt");

    if (!infile.is_open() || !outfile.is_open()) {
        cout << "\t\tError opening file.\n";
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(username) != string::npos) {
            found = true;
            string newPassword;
            cout << "\t\tEnter new password: ";
            getline(cin, newPassword);
            outfile << username << " " << newPassword << endl;
        } else {
            outfile << line << endl;
        }
    }

    infile.close();
    outfile.close();

    remove("customer.txt");
    rename("temp.txt", "customer.txt");

    if (found) {
        cout << "\t\tPassword reset successfully for username '" << username << "'.\n";
    } else {
        cout << "\t\tUsername '" << username << "' not found.\n";
    }
						system("pause");
                    }else if (customerChoice == 9) {
                    	system("cls");
                    	string username;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tEdit Account Name"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\tWhat is your username : ";
                    	deleteAccount(username);
						getline(cin,username);
                        system("pause");
						break;}
                else if (customerChoice == 0) {
                    	
						customer.logout();
                        
						break;}
                }
            }
            
            
        }else if (choice == 2) {
        	
               if (customer.loginUser("customer.txt")) {
                int customerChoice;
                
                while (true) {
                	
                    displayCustomerMenu();
                    cin >> customerChoice;
                    
                    if (customerChoice == 1) {
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\t ADD RECORD"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------";
                        
                        cout << "\n\t\tEnter category: ";
                        
                        string category;
                        cin >> category;
                        customer.addNewRecordUser(list, category);
                        system("pause");
                    } else if (customerChoice == 2) {
                    	system("cls");
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\t EDIT RECORD"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\n";
                    	
                        cout << "\t\tAvailable categories: ";
                        cout << "\n";
                        
                         for (size_t i = 0; i < categories.size(); ++i) {
                         	
        					cout <<"\t\t"<< i + 1 << ". " << categories[i] << " " << endl;
        					
    					}
                        
                        cout << "\n";
                        cout << "\t\t---------------------------------------";
                        
                        cout << "\n\t\Enter category: ";
                        
                        string category;
                        cin >> category;
                        
                        customer.editRecord(list, category);
                        system("pause");
                    } else if (customerChoice == 3) 
					{
						system("cls");
						customer.searchRecord(list);
						system("pause");
					}
                    else if (customerChoice == 4) {
                    	
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tDISPLAY RECORD"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\n";
                    	
                        cout << "\t\t1. Sorted\n";
						cout << "\t\t2. Unsorted\n";
						cout << "\t\tChoose: ";
						
                        int sortChoice;
                        cin >> sortChoice;
                        
                        customer.displayRecords(list, sortChoice == 1);
                        
                    } else if (customerChoice == 5) {
                        system("cls");
                        provideFeedback();
                        system("pause");
						
                    }else if (customerChoice == 6) {
                        system("cls");
						displayHelp();
						system("pause");
                    }else if (customerChoice == 7) {
                    	system("cls");
                    	string username;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tView Account "<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\tWhat is your username : ";
                    	cin >> username;
                        viewcheckpassword(username);
						system("pause");
                    }else if (customerChoice == 8) {
                    	system("cls");
                    	string username;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\t\t\tEdit Account Name"<<endl;
                    	cout << "\t\t---------------------------------------"<<endl;
                    	cout << "\t\tWhat is your username : ";
                    	cin >> username;
                        ifstream infile("customer.txt");
    ofstream outfile("temp.txt");

    if (!infile.is_open() || !outfile.is_open()) {
        cout << "\t\tError opening file.\n";
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(username) != string::npos) {
            found = true;
            string newPassword;
            cout << "\t\tEnter new password: ";
            getline(cin, newPassword);
            outfile << username << " " << newPassword << endl;
        } else {
            outfile << line << endl;
        }
    }

    infile.close();
    outfile.close();

    remove("customer.txt");
    rename("temp.txt", "customer.txt");

    if (found) {
        cout << "\t\tPassword reset successfully for username '" << username << "'.\n";
    } else {
        cout << "\t\tUsername '" << username << "' not found.\n";
    }
						system("pause");
                    }else if (customerChoice == 9) {
                    	 system("cls");

    string username;
    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\t\t\tAccount Name" << endl;
    cout << "\t\t---------------------------------------" << endl;
    cout << "\t\tWhat is your username: ";
    
    // Clear the input buffer before using getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, username);
    
    deleteAccount(username);

    system("pause");
						break;}
            else if (customerChoice == 0) {
                    	
						customer.logout();
                        
						break;}
                }
                }
            }
        }else if (choice == 3) {
        	
            break;
            
        }//end choice customer
			
		else if(choice1 == 3){
			
			break;
		}//end choice1
        
        

    }
    
    return 0;
}
