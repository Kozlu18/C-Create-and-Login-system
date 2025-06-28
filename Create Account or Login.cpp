#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>

using namespace std;

struct User{
    string email;
    string password;
    string first_name;
    string last_name;
    string user_name;
};
struct login{
    string email1;
    string password1;
};

bool is_valid_email(const string &email) {
    return email.find("gmail.com") != string::npos ||
           email.find("hotmail.com") != string::npos ||
           email.find("yahoo.com") != string::npos ||
           email.find("outlokk.com") != string::npos ||
           email.find("icloud.com") != string :: npos; 
}

bool is_valid_password(const string &password) {
    if(password.length() < 8) {
        cout << "Your password lenght < 8 characters" << endl;
        return false;
    }
    bool has_letter = false, has_digit = false;
    for(char c : password)
    {
        if(isalpha(c)) has_letter = true;
        if(isdigit(c)) has_digit = true;
    }
    return has_letter && has_digit;
}

void create_account(User &user, char &choice)
{
    cout << "Please write your first name : ";
    cin >> user.first_name;
    cout << "Please write your last name : ";
    cin >> user.last_name;
    cout << "Please write your username : ";
    cin >> user.user_name;
    do
    {
        cout << "Please write your email : ";
        cin >> user.email;
    } while (!is_valid_email(user.email));
    cout << "Email is correct" << endl;
    do{
        cout << "Please write your password. Your passwrod must be last 8 characters and use letter : ";
        cin >> user.password;
    }while(!is_valid_password(user.password));
    cout << "Your account has been created successfully" << endl;
}

bool login(const User& user) {
    string email_input, pass_input;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Please enter your email: ";
        cin >> email_input;
        cout << "Please enter your password: ";
        cin >> pass_input;

        if (email_input == user.email && pass_input == user.password) {
            cout << "🔓 Login successful!\n";
            return true;
        }

        cout << "❌ Incorrect credentials. Try again.\n";
        attempts++;
    }

    cout << "⏳ Too many failed attempts. Please wait 60 seconds.\n";
    this_thread::sleep_for(chrono::seconds(60));
    return false;
}

int main()
{
    User user;
    char choice;
    bool logged_in = false;
    cout << "Welcome RDJ program" << endl;
    while(logged_in == false)
    {
        cout << "İf you dont have account please enter 'c' to create account or you have account please enter 'L' to login : " << endl;
        cin >> choice;
        if(choice == 'c' || choice == 'C') 
            create_account(user, choice);
        else if(choice == 'l' || choice == 'L') 
            logged_in = login(user);
    }

    if(logged_in == true)
        cout << "Welcome " << user.first_name << " " << user.last_name << endl;
    else if(choice == 'l' || choice == 'L' && logged_in == false)
        cout << "Login failed. Please try again later." << endl;
}
