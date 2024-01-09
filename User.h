#include <string>
#include <memory>
using namespace std;

class User {
public:
    // Using smart pointers for member variables
    unique_ptr<string> name;
    unique_ptr<string> email;
    unique_ptr<int> phone;
    unique_ptr<string> userId;

public:
    User(const string& name, const string& email, const int& phone, const string& userId) {
        this->name = unique_ptr<string>(new string(name));
        this->email = unique_ptr<string>(new string(email));
        this->phone = unique_ptr<int>(new int(phone));
        this->userId = unique_ptr<string>(new string(userId));
    }

    User()= default;

    static void startingQuestion();
    static void userQuestion(const string& accountType);
    static void createAccount(const string& accountType);
    static bool userNameExists(const string& userName, const string& accountType);
    static void writeAccount(const string& userName, const string& password, const string& accountType);
    static void login(const string& accountType);
    static bool passwordCheck(const string &password, const string& accountType, const string& userName);


};
