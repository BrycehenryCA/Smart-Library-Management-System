
#include "Member.h"
#include <iostream>
#include <sstream>

Member::Member() {
    id = 0;
}

Member::Member(int id, string name, string email, string phone) {
    this->id = id;
    this->name = name;
    this->email = email;
    this->phone = phone;
}

int Member::getId() const {
    return id;
}

string Member::getName() const {
    return name;
}

string Member::getEmail() const {
    return email;
}

string Member::getPhone() const {
    return phone;
}

void Member::display() const {
    cout << "\nMember ID: " << id
         << "\nName: " << name
         << "\nEmail: " << email
         << "\nPhone: " << phone
         << "\n-----------------------------------\n";
}

string Member::toFileString() const {
    stringstream ss;

    ss << id << "|"
       << name << "|"
       << email << "|"
       << phone;

    return ss.str();
}

Member Member::fromFileString(const string& data) {
    stringstream ss(data);

    string idValue, name, email, phone;

    getline(ss, idValue, '|');
    getline(ss, name, '|');
    getline(ss, email, '|');
    getline(ss, phone, '|');

    return Member(stoi(idValue), name, email, phone);
}