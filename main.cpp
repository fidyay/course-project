#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

string hashPassword(string pw) {
    string hash = "";
    for (int i = 0; i < pw.length(); i++) {
        hash += pw[i] ^ '!';
    }
    return hash;
}

bool checkPasswortValidity(string password) {
    const string passwordPattern = "[a-zA-Z0-9!@#$%^&*]+";
    const regex passwordReg(passwordPattern);
    if (!regex_match(password, passwordReg)) return false;
    const string lowercase = "(?=.*[a-z])";
    const string uppercase = "(?=.*[A-Z])";
    const string numbers = "(?=.*[0-9])";
    const string special = "(?=.*[!@#$%^&*])";
    const string length = "(?=.{5,})";
    const string fullPattern = lowercase + uppercase + numbers + special + length;
    const regex fullPatternReg(fullPattern);
    if (!regex_search(password, fullPatternReg)) return false;
    return true;
}

bool isNameUnique(vector<string> users, string name) {
    const string namePattern = "^" + name + ".*";
    const regex nameReg(namePattern);
    for (int i = 0; i < users.size(); i++) {
        if (regex_match(users[i], nameReg)) return false;
    }
    return true;
}

int main() {
    const string ControlsNotEnteredInAccount = "L - login\nR - register\nQ - quit\n";
    const string ControlsEnteredInAccount = "C - cancel account\nD - deposit\nL - logout\nT - transfer\nW - withdraw\n";
    bool enteredAccout = false;
    bool shouldContinue = true;
    vector<string> users {};
    while (shouldContinue) {
        if (!enteredAccout) {
            cout << ControlsNotEnteredInAccount;
            char command;
            cin >> command;
            switch(command) {
                case 'L':
                    if (users.size() == 0) {
                        cout << "No user accounts created" << endl;
                    } else {
                        cout << "Name: ";
                        string name = "";
                        cin >> name;
                        cout << "Password: ";
                        string password = "";
                        cin >> password;
                        const string accountPattern = "^" + name + ":" + hashPassword(password) + ":.*";
                        const regex accountPatternReg(accountPattern);
                        for (int i = 0; i < users.size(); i++) {
                            if (regex_match(users[i], accountPatternReg)) {
                                enteredAccout = true;
                                break;
                            }
                        }
                        if (!enteredAccout) cout << "Name or password is invalid" << endl;
                    }
                    break;
                case 'R': {
                    cout << "Name can only include latin letters or symbols" << endl;
                    string name = "";
                    bool nameFound = false;
                    while (!nameFound) {
                        string newName;
                        cout << "Name: ";
                        cin >> newName;
                        const string namePattern = "[a-zA-Z]+";
                        const regex nameReg(namePattern);
                        if (regex_match(newName, nameReg)) {
                            if (isNameUnique(users, newName)) {
                                name = newName;
                                nameFound = true;
                            } else {
                                cout << "Name is already taken" << endl;
                            }
                            
                        } else {
                            cout << "Invalid name" << endl;
                        }
                    }
                    cout << "Password contains only Latin letters, numbers and the symbols !@#$%^&* and must have at least 1 lowercase letter, 1 uppercase and 1 symbol, and the password must be at least 5" << endl;
                    string password = "";
                    bool passwordFound = false;
                    while (!passwordFound) {
                        string newPassword;
                        cout << "Password: ";
                        cin >> newPassword;
                        if (checkPasswortValidity(newPassword)) {
                            password = newPassword;
                            passwordFound = true;
                        } else {
                            cout << "Invalid password" << endl;
                        }
                    users.push_back(name + ":" + hashPassword(password) + ":0");
                    enteredAccout = true;
                    }
                    break;
                    }
                case 'Q':
                    shouldContinue = false;
                    break;
                default: 
                    cout << "Unknown command" << endl;
                    break;
            }
        } else {
            cout << ControlsEnteredInAccount;
            char command;
            cin >> command;
            switch(command) {
                case 'C':
                    break;
                case 'D':
                    break;
                case 'L':
                    enteredAccout = false;
                    break;
                case 'T':
                    break;
                case 'W':
                    break;
                default: 
                    cout << "Unknown command" << endl;
                    break;
            }
        }
    }
    return 0;
}