
#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    string isbn;
    int publicationYear;
    int totalCopies;
    int availableCopies;

public:
    Book();
    Book(int id, string title, string author, string isbn,
         int publicationYear, int totalCopies);

    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    string getISBN() const;
    int getPublicationYear() const;
    int getTotalCopies() const;
    int getAvailableCopies() const;

    void setTitle(string title);
    void setAuthor(string author);
    void setISBN(string isbn);
    void setPublicationYear(int year);
    void setTotalCopies(int copies);

    bool borrowBook();
    bool returnBook();

    void display() const;

    string toFileString() const;
    static Book fromFileString(const string& data);
};

#endif
