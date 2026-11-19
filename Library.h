
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Member.h"
#include "FileManager.h"

#include <vector>
#include <string>

using namespace std;

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Transaction> transactions;

    int nextBookId;
    int nextMemberId;
    int nextTransactionId;

    void saveAll();

    Book* findBook(int id);
    Member* findMember(int id);

public:
    Library();

    void addBook();
    void viewBooks() const;
    void searchBook() const;
    void updateBook();
    void deleteBook();
    void sortBooks();

    void registerMember();
    void viewMembers() const;

    void borrowBook();
    void returnBook();

    void viewBorrowingHistory() const;
    void generateReports() const;
};

#endif