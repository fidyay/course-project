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

int getLastIndexOf(string str, char c) {
    for (int i = str.size() - 1; i >= 0; i--) {
        if (str[i] == c) return i;
    }
    return -1;
}

string sliceString(string str, int index) {
    string returnString = "";
    for (int i = 0; i <= index; i++) {
        returnString += str[i];
    }
    return returnString;
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

double getNumberFromAccount(string account) {
    int index = getLastIndexOf(account, ':');
    string numberString = "";
    for (int i = index + 1; i < account.size(); i++) {
        numberString += account[i];
    }
    return stod(numberString);
}

void showStatusAndControlsEnteredAccount(string account) {
    cout << "You have " << getNumberFromAccount(account) << " BGN. Choose one of the following options:\nC - cancel account\nD - deposit\nL - logout\nT - transfer\nW - withdraw\n";
}

double getAmountOfMoneyFromTerminal() {
    string amount = "";
    cout << "Amount: ";
    cin >> amount;
    int indexOfDot = getLastIndexOf(amount, '.');
    if (amount.size() - indexOfDot > 2 && indexOfDot != -1) {
        amount = sliceString(amount, indexOfDot + 2);
    }
    return stod(amount);
}

int main() {
    const string ControlsNotEnteredInAccount = "L - login\nR - register\nQ - quit\n";
    bool enteredAccout = false;
    bool shouldContinue = true;
    vector<string> users {};
    int currentAccount = -1;
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
                        const string accountPattern = name + ":" + hashPassword(password) + ":";
                        for (int i = 0; i < users.size(); i++) {
                            if (sliceString(users[i], getLastIndexOf(users[i], ':')) == accountPattern) {
                                currentAccount = i;
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
                    currentAccount = users.size();
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
            showStatusAndControlsEnteredAccount(users[currentAccount]);
            char command;
            cin >> command;
            switch(command) {
                case 'C':
                    users.erase(users.begin() + currentAccount);
                    enteredAccout = false;
                    currentAccount = -1;
                    break;
                case 'D':
                {
                    double numToAdd = getAmountOfMoneyFromTerminal();
                    if (numToAdd > 0) {
                        double balance = getNumberFromAccount(users[currentAccount]);
                        double sum = balance + numToAdd;
                        users[currentAccount] = sliceString(users[currentAccount], getLastIndexOf(users[currentAccount], ':')) + to_string(sum);
                    } else {
                        cout << "The amount should be bigger than 0." << endl;
                    }
                    break;
                }
                case 'L':
                    enteredAccout = false;
                    currentAccount = -1;
                    break;
                case 'T':
                    break;
                case 'W':
                    {
                    double balance = getNumberFromAccount(users[currentAccount]);
                    if (balance != -10000) {
                        double numToSubstr = getAmountOfMoneyFromTerminal();
                        if (numToSubstr > 0) {
                            double sum = balance - numToSubstr;
                            if (sum < -10000) sum = -10000;
                            users[currentAccount] = sliceString(users[currentAccount], getLastIndexOf(users[currentAccount], ':')) + to_string(sum);
                        } else {
                            cout << "The amount should be bigger than 0." << endl;
                        }
                    } else {
                        cout << "Denied. Max overdraft." << endl;
                    }
                    }
                    break;
                default: 
                    cout << "Unknown command" << endl;
                    break;
            }
        }
    }
    return 0;
}