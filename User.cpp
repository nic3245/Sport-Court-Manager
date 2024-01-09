#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
#include "CourtSystem.h"
#include "Role.h"

using namespace std;

//the questions the program asks when it is ran
void User::startingQuestion() {
    string userType;
    cout << "Are you a player, coach, officer, or do you want to exit(player, coach, officer, or exit)?" << endl;
    cin >> userType;
    while (true) {
        if (userType == "player") {
            userQuestion(userType);
        }
	if (userType == "coach") {
            userQuestion(userType);
        }
	if (userType == "officer") {
            userQuestion(userType);
        }
	if (userType == "exit") {
            break;
        }
    }
}

//question after the user chooses a role
void User::userQuestion(const string &accountType) {
    string choice;
    while (true) {
        cout << "Do you want to create an account, login to an account, or exit(create, login, or exit)?";
        cin >> choice;
        if (choice == "create") {
            createAccount(accountType);
            cout << "create";
        } else if (choice == "login") {
            login(accountType);

        } else if (choice == "exit") {
            break;
        }
    }

}


void User::writeAccount(const string &userName, const string &password, const string &accountType) {
    string fileName = accountType + "_credentials.txt";
    ofstream credentials(fileName, ios::app);
    if (credentials.is_open()) {
        credentials << userName << ":" << password << endl;
    } else {
        cout << "Can't open file";
    }
    credentials.close();

}


void User::createAccount(const string &accountType) {
    string userName;
    string email;
    string password;
    int phone;

    while (true) {
        cout << "Type in the username:";
        cin >> userName;
        if (userNameExists(userName, "player") || userNameExists(userName, "coach") || userNameExists(userName, "officer")) {
            cout << "The username you typed already exists. Please type in another one" << endl;
        } else if (!userNameExists(userName, accountType)) {
            cout << "Type in a password:" << endl;
            cin >> password;
            writeAccount(userName, password, accountType);
            break;
        }
    }

}

bool User::userNameExists(const string &userName, const string &accountType) {
    string fileName = accountType + "_credentials.txt";
    string line;
    ifstream credentials(fileName);
    size_t posOfColon;
    if (credentials.is_open()) {
        while (getline(credentials, line)) {
            posOfColon = line.find(':');
            if (line.substr(0, posOfColon) == userName) {
                return true;
            }
        }
    }
    return false;
}

bool User::passwordCheck(const string &password, const string &userType, const string &userName) {
    string fileName = userType + "_credentials.txt";
    string line;
    size_t pos;
    size_t posOfUserName;
    ifstream credentials(fileName);
    if (credentials.is_open()) {
        while (getline(credentials, line)) {
            pos = line.find(':') + 1;//password
            posOfUserName = line.find(':');
            if (line.substr(0, posOfUserName) == userName) {
                if (line.substr(pos) == password) {
                    return true;
                }
            }
        }
        credentials.close();
    } else {
        cout << "Unable to open file";
    }
    return false;
}

void User::login(const string &accountType) {
    string userName;
    string password;

    while (true) {
        cout << "Type in the username:";
        cin >> userName;
        if (!userNameExists(userName, accountType)) {
            cout << "The username you entered is doesn't exist." << endl;
        }
        if (userNameExists(userName, accountType)) {
            while (true) {
                cout << "Type in the password:";
                cin >> password;
                if (passwordCheck(password, accountType, userName)) {
                    ROLE role;
                    if(accountType == "coach"){
                        role = COACH;
                    }else if(accountType == "officer"){
                        role = OFFICIAL;
                    }else{
                        role = PLAYER;
                    }
                    CourtSystem courtSystem;
                    courtSystem.runCourtSystem(userName, role);
                } else {
                    cout << "The password you typed in is incorrect" << endl;
                    password.clear();
                }
            }

            break;
        }
    }


}
