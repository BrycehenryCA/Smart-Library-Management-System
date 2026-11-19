
#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

vector<Book> FileManager::loadBooks() {
    vector<Book> books;
    ifstream file("books.txt");

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        try {
            books.push_back(Book::fromFileString(line));
        }
        catch (const exception& e) {
            cerr << "Skipping invalid book record: "
                 << e.what() << endl;
        }
    }

    return books;
}

vector<Member> FileManager::loadMembers() {
    vector<Member> members;
    ifstream file("members.txt");

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        try {
            members.push_back(Member::fromFileString(line));
        }
        catch (const exception& e) {
            cerr << "Skipping invalid member record: "
                 << e.what() << endl;
        }
    }

    return members;
}

vector<Transaction> FileManager::loadTransactions() {
    vector<Transaction> transactions;
    ifstream file("transactions.txt");

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        try {
            stringstream ss(line);
            Transaction t;
            string value;

            getline(ss, value, '|');
            t.id = stoi(value);

            getline(ss, value, '|');
            t.memberId = stoi(value);

            getline(ss, value, '|');
            t.bookId = stoi(value);

            getline(ss, value, '|');
            t.borrowDay = stoll(value);

            getline(ss, value, '|');
            t.dueDay = stoll(value);

            getline(ss, value, '|');
            t.returnDay = stoll(value);

            getline(ss, value, '|');
            t.fine = stod(value);

            if (t.id <= 0 || t.memberId <= 0 || t.bookId <= 0 ||
                t.borrowDay <= 0 || t.dueDay < t.borrowDay ||
                t.returnDay < 0 || t.fine < 0 ||
                (t.returnDay != 0 && t.returnDay < t.borrowDay)) {
                throw invalid_argument("Invalid transaction values.");
            }

            transactions.push_back(t);
        }
        catch (const exception& e) {
            cerr << "Skipping invalid transaction: "
                 << e.what() << endl;
        }
    }

    return transactions;
}

void FileManager::saveBooks(const vector<Book>& books) {
    ofstream file("books.txt");

    if (!file) {
        cerr << "Unable to save books." << endl;
        return;
    }

    for (const Book& book : books) {
        file << book.toFileString() << endl;
    }
}

void FileManager::saveMembers(const vector<Member>& members) {
    ofstream file("members.txt");

    if (!file) {
        cerr << "Unable to save members." << endl;
        return;
    }

    for (const Member& member : members) {
        file << member.toFileString() << endl;
    }
}

void FileManager::saveTransactions(
    const vector<Transaction>& transactions) {

    ofstream file("transactions.txt");

    if (!file) {
        cerr << "Unable to save transactions." << endl;
        return;
    }

    for (const Transaction& t : transactions) {
        file << t.id << "|"
             << t.memberId << "|"
             << t.bookId << "|"
             << t.borrowDay << "|"
             << t.dueDay << "|"
             << t.returnDay << "|"
             << t.fine << endl;
    }
}