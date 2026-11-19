
# Smart Library Management System

## 1. Project Overview

The Smart Library Management System is a console-based application developed using C++17.

The application helps librarians manage books, register members, process borrowing and returning transactions, calculate overdue fines, and generate library reports.

The system uses Object-Oriented Programming principles and file handling to store records permanently.

## 2. Technologies Used

- C++17
- Object-Oriented Programming
- Classes and Objects
- Encapsulation
- Vectors and STL
- File Handling
- Exception Handling
- Lambda Functions
- Algorithms

## 3. Project Structure

SmartLibrary/

- main.cpp
- Book.h
- Book.cpp
- Member.h
- Member.cpp
- Library.h
- Library.cpp
- FileManager.h
- FileManager.cpp
- books.txt
- members.txt
- transactions.txt
- README.md

## 4. System Requirements

- C++ compiler supporting C++17
- GCC or MinGW
- Visual Studio Code or another C++ IDE
- Windows, Linux, or macOS

## 5. Compilation

Open a terminal inside the project directory.

Compile the application using:

g++ -std=c++17 main.cpp Book.cpp Member.cpp Library.cpp FileManager.cpp -o SmartLibrary

## 6. Running the Application

On Windows:

.\SmartLibrary.exe

On Linux:

./SmartLibrary

## 7. Administrator Credentials

Username: admin

Password: admin123

The application allows three login attempts.

Note: These are demonstration credentials. 

## 8. System Features

### Book Management

- Add new books.
- View all books.
- Search by title, author, ISBN, or ID.
- Update book information.
- Delete books.
- Sort books by title, author, or publication year.

### Member Management

- Register new members.
- View registered members.
- Automatically assign member IDs.
- Prevent duplicate email registration.

### Borrowing Management

- Issue books to registered members.
- Check book availability.
- Set a borrowing period of 14 days.
- Record borrowing transactions.
- Prevent members from borrowing the same book twice while it is still outstanding.

### Return Management

- Process book returns.
- Calculate overdue days.
- Calculate overdue fines.
- Update available book copies.

### Reporting

- Total book titles.
- Total book copies.
- Available book copies.
- Registered members.
- Active borrowings.
- Returned books.
- Overdue books.
- Total recorded fines.

## 9. File Storage

The application uses three text files:

books.txt - Stores book information.

members.txt - Stores registered member information.

transactions.txt - Stores borrowing and returning history.

Records are automatically loaded when the application starts and saved when changes are made.

## 10. Fine Calculation

The library allows members to borrow books for 14 days.

An overdue fine of $1.00 is charged for each day after the due date.

Fine = Overdue Days × $1.00
