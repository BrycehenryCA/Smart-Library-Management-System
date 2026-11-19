
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Book.h"
#include "Member.h"
#include <vector>
#include <string>

using namespace std;

struct Transaction {
    int id;
    int memberId;
    int bookId;
    long long borrowDay;
    long long dueDay;
    long long returnDay;
    double fine;

    bool isReturned() const {
        return returnDay != 0;
    }
};

class FileManager {
public:
    static vector<Book> loadBooks();
    static vector<Member> loadMembers();
    static vector<Transaction> loadTransactions();

    static void saveBooks(const vector<Book>& books);
    static void saveMembers(const vector<Member>& members);
    static void saveTransactions(
        const vector<Transaction>& transactions
    );
};

#endif