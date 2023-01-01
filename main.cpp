#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

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

int main() {
    const string controlsNotEnteredInAccount = "L - login\nR - register\nQ - quit\n";
    const string controlsEnteredInAccount = "C - cancel account\nD - deposit\nL - logout\nT - transfer\nW - withdraw\n";
    bool enteredAccout = false;
    bool shouldContinue = true;
    vector<string> users {};
    while (shouldContinue) {
        if (!enteredAccout) {
            cout << controlsNotEnteredInAccount;
            char command;
            cin >> command;
            switch(command) {
                case 'L':
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
                            name = newName;
                            nameFound = true;
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
        }
    }
    return 0;
}