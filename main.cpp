
#include "Library.h"

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Administrator login
bool adminLogin() {
    const string ADMIN_USERNAME = "admin";
    const string ADMIN_PASSWORD = "admin123";

    cout << "\n====================================\n";
    cout << "       SMART LIBRARY SYSTEM\n";
    cout << "====================================\n";

    for (int attempt = 1; attempt <= 3; attempt++) {

        string username;
        string password;

        cout << "\nAdministrator Login\n";

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (username == ADMIN_USERNAME &&
            password == ADMIN_PASSWORD) {

            cout << "\nLogin successful!\n";
            return true;
        }

        cout << "Incorrect username or password.\n";
        cout << "Attempts remaining: " << 3 - attempt << endl;
    }

    cout << "\nMaximum login attempts reached.\n";
    return false;
}

// Display the main menu
void displayMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "       SMART LIBRARY MANAGEMENT\n";
    cout << "========================================\n";

    cout << "1.  Add New Book\n";
    cout << "2.  View All Books\n";
    cout << "3.  Search Book\n";
    cout << "4.  Update Book Information\n";
    cout << "5.  Delete Book\n";
    cout << "6.  Sort Books\n";
    cout << "7.  Register Member\n";
    cout << "8.  View Registered Members\n";
    cout << "9.  Borrow Book\n";
    cout << "10. Return Book\n";
    cout << "11. View Borrowing History\n";
    cout << "12. Generate Library Reports\n";
    cout << "0.  Exit\n";

    cout << "========================================\n";
    cout << "Enter your choice: ";
}

// Read menu input safely
int getMenuChoice() {
    string line;
    int choice;

    while (true) {
        getline(cin, line);

        try {
            size_t position;
            choice = stoi(line, &position);

            if (position == line.size() &&
                choice >= 0 && choice <= 12) {
                return choice;
            }
        }
        catch (...) {
            
        }

        cout << "Invalid choice. Enter a number from 0 to 12: ";
    }
}

int main() {

    cout << "Starting Smart Library Management System...\n";

    Library library;

    if (!adminLogin()) {
        cout << "Access denied. Exiting application.\n";
        return 0;
    }

    bool running = true;

    while (running) {

        displayMenu();

        int choice = getMenuChoice();

        try {
            switch (choice) {

                case 1:
                    library.addBook();
                    break;

                case 2:
                    library.viewBooks();
                    break;

                case 3:
                    library.searchBook();
                    break;

                case 4:
                    library.updateBook();
                    break;

                case 5:
                    library.deleteBook();
                    break;

                case 6:
                    library.sortBooks();
                    break;

                case 7:
                    library.registerMember();
                    break;

                case 8:
                    library.viewMembers();
                    break;

                case 9:
                    library.borrowBook();
                    break;

                case 10:
                    library.returnBook();
                    break;

                case 11:
                    library.viewBorrowingHistory();
                    break;

                case 12:
                    library.generateReports();
                    break;

                case 0:
                    cout << "\nSaving library records...\n";
                    cout << "Thank you for using Smart Library!\n";
                    running = false;
                    break;

                default:
                    cout << "Invalid menu selection.\n";
            }
        }
        catch (const exception& e) {
            cout << "An error occurred: " << e.what() << endl;
        }
    }

    return 0;
}