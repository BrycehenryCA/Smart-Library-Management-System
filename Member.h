
#ifndef MEMBER_H
#define MEMBER_H

#include <string>
using namespace std;

class Member {
private:
    int id;
    string name;
    string email;
    string phone;

public:
    Member();
    Member(int id, string name, string email, string phone);

    int getId() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;

    void display() const;

    string toFileString() const;
    static Member fromFileString(const string& data);
};

#endif