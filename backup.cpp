#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <dirent.h>

using namespace std;

string adminUsername = "admin"; // Default admin username
string adminPassword = "password"; // Default admin password

bool login() {
    string username, password, fileUsername, filePassword;
    cout << "Login\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    
    // Read from file
    ifstream inFile("admin.txt");
    if (inFile.is_open()) {
        getline(inFile, fileUsername);
        getline(inFile, filePassword);
        inFile.close();
        
        if (username == fileUsername && password == filePassword) {
            return true;
        } else {
            cout << "Incorrect username or password.\n";
            return false;
        }
    } else {
        cout << "Error opening file.\n";
        return false;
    }
}


bool registerAdmin() {
    string username, password;
    cout << "Register\n";
    cout << "Set new admin username: ";
    cin >> username;
    cout << "Set new admin password: ";
    cin >> password;
    
    // Save to file
    ofstream outFile("admin.txt");
    if (outFile.is_open()) {
        outFile << username << endl;
        outFile << password << endl;
        outFile.close();
        cout << "Registration successful. Admin credentials saved.\n";
    } else {
        cout << "Error opening file.\n";
        return false;
    }
    
    return login(); // Automatically attempt to log in after registering
}

int main() {
	
	bool loggedIn = false;
    
    while (!loggedIn) {
        int choice;
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                loggedIn = registerAdmin();
                break;
            case 2:
                loggedIn = login();
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
	
    int choose;
    
    do {
     cout << "Menu\n";
        cout << "1. Show the category\n";
        cout << "2. Add a new category\n";
        cout << "3. Quit\n"; // Add a quit option to the menu
        cout << "Enter :";
        cin >> choose;
        cin.ignore(); // to clear the newline character left in the input buffer
    
    switch (choose) {
        case 1: {
    cout << "Category:\n";
    DIR *dir;
    struct dirent *ent;
    int count = 1; // Initialize a counter for numbering the categories
    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;
            size_t pos = filename.rfind(".txt");
            if (pos != string::npos && pos == filename.size() - 4) {
                // Remove the .txt extension and display with numbering
                cout << count << ". " << filename.substr(0, pos) << endl;
                count++; // Increment the counter
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }
    break;
}


        case 2: {
            string categoryTitle;
            cout << "Enter the new category title: ";
            getline(cin, categoryTitle);

            // Create and open a text file
            ofstream MyFile((categoryTitle + ".txt").c_str());

            // Write to the file
            MyFile << "Category: " << categoryTitle << "\n";

            // Close the file
            MyFile.close();

            cout << "New category '" << categoryTitle << "' created.\n";
            break;
        }
        
        case 3: // Case for quitting the program
                cout << "Exiting program.\n";
                return 0; // Exit the program


        default:
            cout << "Invalid choice.\n";
            break;
    }
    
    } while (true);
    return 0;
}

