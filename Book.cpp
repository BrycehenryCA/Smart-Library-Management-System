
#include "Book.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

Book::Book() {
    id = 0;
    publicationYear = 0;
    totalCopies = 0;
    availableCopies = 0;
}

Book::Book(int id, string title, string author, string isbn,
           int publicationYear, int totalCopies) {
    this->id = id;
    this->title = title;
    this->author = author;
    this->isbn = isbn;
    this->publicationYear = publicationYear;
    this->totalCopies = totalCopies;
    this->availableCopies = totalCopies;
}

int Book::getId() const {
    return id;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getISBN() const {
    return isbn;
}

int Book::getPublicationYear() const {
    return publicationYear;
}

int Book::getTotalCopies() const {
    return totalCopies;
}

int Book::getAvailableCopies() const {
    return availableCopies;
}

void Book::setTitle(string title) {
    this->title = title;
}

void Book::setAuthor(string author) {
    this->author = author;
}

void Book::setISBN(string isbn) {
    this->isbn = isbn;
}

void Book::setPublicationYear(int year) {
    publicationYear = year;
}

void Book::setTotalCopies(int copies) {
    int borrowed = totalCopies - availableCopies;

    if (copies < borrowed) {
        throw invalid_argument(
            "Total copies cannot be less than borrowed copies.");
    }

    totalCopies = copies;
    availableCopies = copies - borrowed;
}

bool Book::borrowBook() {
    if (availableCopies <= 0) {
        return false;
    }

    availableCopies--;
    return true;
}

bool Book::returnBook() {
    if (availableCopies >= totalCopies) {
        return false;
    }

    availableCopies++;
    return true;
}

void Book::display() const {
    cout << "\nBook ID: " << id
         << "\nTitle: " << title
         << "\nAuthor: " << author
         << "\nISBN: " << isbn
         << "\nPublication Year: " << publicationYear
         << "\nTotal Copies: " << totalCopies
         << "\nAvailable Copies: " << availableCopies
         << "\n-----------------------------------\n";
}

string Book::toFileString() const {
    stringstream ss;

    ss << id << "|"
       << title << "|"
       << author << "|"
       << isbn << "|"
       << publicationYear << "|"
       << totalCopies << "|"
       << availableCopies;

    return ss.str();
}

Book Book::fromFileString(const string& data) {
    stringstream ss(data);

    string idValue, title, author, isbn;
    string yearValue, totalValue, availableValue;

    getline(ss, idValue, '|');
    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');
    getline(ss, yearValue, '|');
    getline(ss, totalValue, '|');
    getline(ss, availableValue, '|');

    Book book(
        stoi(idValue),
        title,
        author,
        isbn,
        stoi(yearValue),
        stoi(totalValue)
    );

    int available = stoi(availableValue);

    if (available < 0 || available > book.getTotalCopies()) {
        throw invalid_argument("Invalid available copies.");
    }

    while (book.getAvailableCopies() > available) {
        book.borrowBook();
    }

    return book;
}