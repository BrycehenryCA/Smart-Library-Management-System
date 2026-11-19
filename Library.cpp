
#include "Library.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <chrono>
#include <ctime>
#include <sstream>
#include <cmath>

using namespace std;

namespace {

const double DAILY_FINE = 1.00;
const int LOAN_PERIOD = 14;

bool validText(const string& value) {
    return !value.empty() &&
           value.find('|') == string::npos;
}

string readText(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        if (validText(value)) {
            return value;
        }

        cout << "Invalid input. Try again.\n";
    }
}

int readInteger(const string& prompt, int minimum, int maximum) {
    string line;
    int value;

    while (true) {
        cout << prompt;
        getline(cin, line);

        stringstream ss(line);
        char extra;

        if (ss >> value && !(ss >> extra) &&
            value >= minimum && value <= maximum) {
            return value;
        }

        cout << "Enter a valid number between "
             << minimum << " and " << maximum << ".\n";
    }
}

long long currentDay() {
    using namespace chrono;

    return duration_cast<days>(
        system_clock::now().time_since_epoch()
    ).count();
}

string formatDate(long long day) {
    time_t timestamp = static_cast<time_t>(day * 86400);

    tm* date = localtime(&timestamp);

    if (date == nullptr) {
        return "Invalid date";
    }

    stringstream ss;

    ss << put_time(date, "%Y-%m-%d");

    return ss.str();
}

int nextIdFromBooks(const vector<Book>& books) {
    int maximum = 0;

    for (const Book& book : books) {
        maximum = max(maximum, book.getId());
    }

    return maximum + 1;
}

int nextIdFromMembers(const vector<Member>& members) {
    int maximum = 0;

    for (const Member& member : members) {
        maximum = max(maximum, member.getId());
    }

    return maximum + 1;
}

int nextIdFromTransactions(
    const vector<Transaction>& transactions) {

    int maximum = 0;

    for (const Transaction& t : transactions) {
        maximum = max(maximum, t.id);
    }

    return maximum + 1;
}

}

// Constructor
Library::Library() {
    books = FileManager::loadBooks();
    members = FileManager::loadMembers();
    transactions = FileManager::loadTransactions();

    nextBookId = nextIdFromBooks(books);
    nextMemberId = nextIdFromMembers(members);
    nextTransactionId = nextIdFromTransactions(transactions);

    // Restore inventory counts from active borrowing records.
    for (const Transaction& t : transactions) {
        if (!t.isReturned()) {
            Book* book = findBook(t.bookId);

            if (book != nullptr) {
                book->borrowBook();
            }
        }
    }

    saveAll();
}

void Library::saveAll() {
    FileManager::saveBooks(books);
    FileManager::saveMembers(members);
    FileManager::saveTransactions(transactions);
}

Book* Library::findBook(int id) {
    for (Book& book : books) {
        if (book.getId() == id) {
            return &book;
        }
    }

    return nullptr;
}

Member* Library::findMember(int id) {
    for (Member& member : members) {
        if (member.getId() == id) {
            return &member;
        }
    }

    return nullptr;
}

// Add a new book
void Library::addBook() {
    cout << "\n===== ADD NEW BOOK =====\n";

    string title = readText("Enter book title: ");
    string author = readText("Enter author: ");
    string isbn = readText("Enter ISBN: ");

    for (const Book& book : books) {
        if (book.getISBN() == isbn) {
            cout << "A book with this ISBN already exists.\n";
            return;
        }
    }

    int year = readInteger(
        "Enter publication year: ", 1, 9999
    );

    int copies = readInteger(
        "Enter number of copies: ", 1, 100000
    );

    Book book(
        nextBookId++,
        title,
        author,
        isbn,
        year,
        copies
    );

    books.push_back(book);

    saveAll();

    cout << "\nBook added successfully.\n";
    cout << "Assigned Book ID: " << book.getId() << endl;
}

// Display all books
void Library::viewBooks() const {
    cout << "\n========== ALL BOOKS ==========\n";

    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    for (const Book& book : books) {
        book.display();
    }
}

// Search for a book
void Library::searchBook() const {
    cout << "\n===== SEARCH BOOK =====\n";
    cout << "1. Search by ID\n";
    cout << "2. Search by Title\n";
    cout << "3. Search by Author\n";
    cout << "4. Search by ISBN\n";

    int choice = readInteger("Choose option: ", 1, 4);

    if (choice == 1) {
        int id = readInteger("Enter book ID: ", 1, 1000000000);

        for (const Book& book : books) {
            if (book.getId() == id) {
                book.display();
                return;
            }
        }
    } else {
        string keyword = readText("Enter search keyword: ");

        for (const Book& book : books) {
            bool found = false;

            if (choice == 2) {
                found = book.getTitle().find(keyword) != string::npos;
            } else if (choice == 3) {
                found = book.getAuthor().find(keyword) != string::npos;
            } else if (choice == 4) {
                found = book.getISBN().find(keyword) != string::npos;
            }

            if (found) {
                book.display();
            }
        }
    }

    cout << "Search completed.\n";
}

// Update book information
void Library::updateBook() {
    cout << "\n===== UPDATE BOOK =====\n";

    int id = readInteger("Enter book ID: ", 1, 1000000000);

    Book* book = findBook(id);

    if (book == nullptr) {
        cout << "Book not found.\n";
        return;
    }

    cout << "1. Update title\n";
    cout << "2. Update author\n";
    cout << "3. Update ISBN\n";
    cout << "4. Update publication year\n";
    cout << "5. Update total copies\n";

    int choice = readInteger("Choose option: ", 1, 5);

    switch (choice) {
        case 1:
            book->setTitle(readText("New title: "));
            break;

        case 2:
            book->setAuthor(readText("New author: "));
            break;

        case 3: {
            string isbn = readText("New ISBN: ");

            for (const Book& other : books) {
                if (other.getId() != id &&
                    other.getISBN() == isbn) {
                    cout << "This ISBN already exists.\n";
                    return;
                }
            }

            book->setISBN(isbn);
            break;
        }

        case 4:
            book->setPublicationYear(
                readInteger("New publication year: ", 1, 9999)
            );
            break;

        case 5:
            try {
                book->setTotalCopies(
                    readInteger("New total copies: ", 0, 100000)
                );
            }
            catch (const exception& e) {
                cout << e.what() << endl;
                return;
            }
            break;
    }

    saveAll();

    cout << "Book updated successfully.\n";
}

// Delete a book
void Library::deleteBook() {
    cout << "\n===== DELETE BOOK =====\n";

    int id = readInteger("Enter book ID: ", 1, 1000000000);

    Book* book = findBook(id);

    if (book == nullptr) {
        cout << "Book not found.\n";
        return;
    }

    for (const Transaction& t : transactions) {
        if (t.bookId == id && !t.isReturned()) {
            cout << "Cannot delete a book currently borrowed.\n";
            return;
        }
    }

    books.erase(
        remove_if(
            books.begin(),
            books.end(),
            [id](const Book& b) {
                return b.getId() == id;
            }
        ),
        books.end()
    );

    saveAll();

    cout << "Book deleted successfully.\n";
}

// Sort books
void Library::sortBooks() {
    cout << "\n===== SORT BOOKS =====\n";
    cout << "1. Sort by title\n";
    cout << "2. Sort by publication year\n";
    cout << "3. Sort by author\n";

    int choice = readInteger("Choose option: ", 1, 3);

    if (choice == 1) {
        sort(books.begin(), books.end(),
            [](const Book& a, const Book& b) {
                return a.getTitle() < b.getTitle();
            });
    } else if (choice == 2) {
        sort(books.begin(), books.end(),
            [](const Book& a, const Book& b) {
                return a.getPublicationYear() <
                       b.getPublicationYear();
            });
    } else {
        sort(books.begin(), books.end(),
            [](const Book& a, const Book& b) {
                return a.getAuthor() < b.getAuthor();
            });
    }

    saveAll();

    cout << "\nBooks sorted successfully.\n";

    viewBooks();
}

// Register a new member
void Library::registerMember() {
    cout << "\n===== REGISTER MEMBER =====\n";

    string name = readText("Enter member name: ");
    string email = readText("Enter email address: ");
    string phone = readText("Enter phone number: ");

    for (const Member& member : members) {
        if (member.getEmail() == email) {
            cout << "A member with this email already exists.\n";
            return;
        }
    }

    Member member(
        nextMemberId++,
        name,
        email,
        phone
    );

    members.push_back(member);

    saveAll();

    cout << "\nMember registered successfully.\n";
    cout << "Assigned Member ID: " << member.getId() << endl;
}

// Display all members
void Library::viewMembers() const {
    cout << "\n========== REGISTERED MEMBERS ==========\n";

    if (members.empty()) {
        cout << "No members registered.\n";
        return;
    }

    for (const Member& member : members) {
        member.display();
    }
}

// Borrow a book
void Library::borrowBook() {
    cout << "\n===== BORROW BOOK =====\n";

    int memberId = readInteger(
        "Enter member ID: ", 1, 1000000000
    );

    int bookId = readInteger(
        "Enter book ID: ", 1, 1000000000
    );

    Member* member = findMember(memberId);
    Book* book = findBook(bookId);

    if (member == nullptr) {
        cout << "Member not found.\n";
        return;
    }

    if (book == nullptr) {
        cout << "Book not found.\n";
        return;
    }

    for (const Transaction& t : transactions) {
        if (t.memberId == memberId &&
            t.bookId == bookId &&
            !t.isReturned()) {
            cout << "This member has already borrowed this book.\n";
            return;
        }
    }

    if (!book->borrowBook()) {
        cout << "No available copies of this book.\n";
        return;
    }

    long long today = currentDay();

    Transaction transaction;

    transaction.id = nextTransactionId++;
    transaction.memberId = memberId;
    transaction.bookId = bookId;
    transaction.borrowDay = today;
    transaction.dueDay = today + LOAN_PERIOD;
    transaction.returnDay = 0;
    transaction.fine = 0.0;

    transactions.push_back(transaction);

    saveAll();

    cout << "\nBook borrowed successfully.\n";
    cout << "Transaction ID: " << transaction.id << endl;
    cout << "Member: " << member->getName() << endl;
    cout << "Book: " << book->getTitle() << endl;
    cout << "Borrow Date: " << formatDate(today) << endl;
    cout << "Due Date: " << formatDate(transaction.dueDay) << endl;
}

// Return a book
void Library::returnBook() {
    cout << "\n===== RETURN BOOK =====\n";

    int transactionId = readInteger(
        "Enter transaction ID: ", 1, 1000000000
    );

    for (Transaction& t : transactions) {
        if (t.id == transactionId && !t.isReturned()) {

            Book* book = findBook(t.bookId);

            if (book == nullptr) {
                cout << "Book record not found.\n";
                return;
            }

            long long today = currentDay();

            long long overdueDays = max(
                0LL, today - t.dueDay
            );

            t.fine = overdueDays * DAILY_FINE;
            t.returnDay = today;

            if (!book->returnBook()) {
                cout << "Inventory error: unable to return book.\n";
                t.returnDay = 0;
                t.fine = 0.0;
                return;
            }

            saveAll();

            cout << "\nBook returned successfully.\n";
            cout << "Return Date: " << formatDate(today) << endl;
            cout << "Overdue Days: " << overdueDays << endl;
            cout << fixed << setprecision(2);
            cout << "Fine Amount: $" << t.fine << endl;

            return;
        }
    }

    cout << "Active borrowing transaction not found.\n";
}

// View borrowing history
void Library::viewBorrowingHistory() const {
    cout << "\n========== BORROWING HISTORY ==========\n";

    if (transactions.empty()) {
        cout << "No borrowing transactions found.\n";
        return;
    }

    for (const Transaction& t : transactions) {

        const Member* member = nullptr;
        const Book* book = nullptr;

        for (const Member& m : members) {
            if (m.getId() == t.memberId) {
                member = &m;
                break;
            }
        }

        for (const Book& b : books) {
            if (b.getId() == t.bookId) {
                book = &b;
                break;
            }
        }

        cout << "\nTransaction ID: " << t.id
             << "\nMember: "
             << (member ? member->getName() : "Deleted member")
             << "\nBook: "
             << (book ? book->getTitle() : "Deleted book")
             << "\nBorrow Date: " << formatDate(t.borrowDay)
             << "\nDue Date: " << formatDate(t.dueDay)
             << "\nReturn Date: "
             << (t.isReturned()
                 ? formatDate(t.returnDay) : "Not returned")
             << "\nFine: $" << fixed << setprecision(2)
             << t.fine
             << "\n-----------------------------------\n";
    }
}

// Generate library reports
void Library::generateReports() const {
    cout << "\n========== LIBRARY REPORTS ==========\n";

    int totalCopies = 0;
    int availableCopies = 0;
    int activeLoans = 0;
    int returnedLoans = 0;
    int overdueLoans = 0;

    double totalFines = 0.0;

    long long today = currentDay();

    for (const Book& book : books) {
        totalCopies += book.getTotalCopies();
        availableCopies += book.getAvailableCopies();
    }

    for (const Transaction& t : transactions) {
        totalFines += t.fine;

        if (t.isReturned()) {
            returnedLoans++;
        } else {
            activeLoans++;

            if (today > t.dueDay) {
                overdueLoans++;
            }
        }
    }

    cout << "\nTotal Book Titles: " << books.size()
         << "\nTotal Book Copies: " << totalCopies
         << "\nAvailable Copies: " << availableCopies
         << "\nRegistered Members: " << members.size()
         << "\nTotal Transactions: " << transactions.size()
         << "\nActive Borrowings: " << activeLoans
         << "\nReturned Books: " << returnedLoans
         << "\nOverdue Books: " << overdueLoans
         << "\nTotal Fines Recorded: $"
         << fixed << setprecision(2) << totalFines
         << "\n===================================\n";
}