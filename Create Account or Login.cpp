#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

struct User{
    string email;
    string password;
    string first_name;
    string last_name;
    string user_name;
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

string name_file, lastname_file, mail_file, username_file, password_file;

bool login(const User& user) {
    string email_input, pass_input;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Please enter your email: ";
        cin >> email_input;
        cout << "Please enter your password: ";
        cin >> pass_input;

        ifstream users("users.txt");
        while(users >> name_file >> lastname_file >> username_file >> mail_file >> password_file)
        {
            if(email_input == mail_file && pass_input == password_file)
            {
                cout << "You entered true information. Welcome : " << username_file << endl;
                return true; 
            }
        }
        
        cout << "❌ Incorrect credentials. Try again.\n";
        attempts++;
    }

    cout << "⏳ Too many failed attempts. Please wait 30 seconds.\n";
    this_thread::sleep_for(chrono::seconds(30));
    return false;
}

bool check_password(const string &passw)
{
    if(password_file == passw)
        return true;
    return false;
};


void create_account(User &user)
{
    cout << "Please write your first name : ";
    cin >> user.first_name;
    cout << "Please write your last name : ";
    cin >> user.last_name;
    cout << "Please write your username : ";
    cin >> user.user_name;
    do{
        cout << "Please write your email : ";
        cin >> user.email;
    }
    while (!is_valid_email(user.email));
    cout << "Email is correct" << endl;
    do{
        cout << "Please write your password. Your passwrod must be last 8 characters and use letter : ";
        cin >> user.password;
    }while(!is_valid_password(user.password));
    ofstream users("users.txt", ios::app);
    users << user.first_name << " " << user.last_name << " " << user.user_name << " " << user.email << " " << user.password << endl;
    users.close();
    cout << "Your account has been created successfully" << endl;
}

void save_old_information(vector<string>& first, vector<string>& last, vector<string>& user, vector<string>& mail, vector<string>& password)
{
    ifstream file("users.txt");
    if(!file.is_open())
        cerr << "Error : Txt file not found." << endl;
    else{
        while(file >> name_file >> lastname_file >> username_file >> mail_file >> password_file)
            {
                first.push_back(name_file);
                last.push_back(lastname_file);
                user.push_back(username_file);
                mail.push_back(mail_file);
                password.push_back(password_file);
            }
    }
    file.close();
}

void change_information(string &filename, bool& logged_in)
{
    bool cexit = false;
    while(!cexit)
    {
        cout << "P : Change password : " << endl;
        cout << "U : Change username : " << endl;
        cout << "L : Change last name : " << endl;
        cout << "E : Exit the page : " << endl;

        char cact;
        cin >> cact;

        if(cact == 'P' || cact == 'p')
        {   string passw, passw2;
            do{ 
                cout << "Please enter old password : " << endl;
                cin >> passw;
            }while(!check_password(passw));
            int idx = 0;
            vector<string> first, last, username, mail, password;
            save_old_information(first, last, username, mail, password);
            
            do
            {
                cout << "Please enter new password : " << endl;
                cin >> passw2;
            } while (!is_valid_password(passw2));
            
            ofstream file("users.txt");
            for(int i = 0; i < username.size(); i++)
            {
                file << first[i] << " " << last[i] << " " << username[i] << " " << mail[i] << " ";
                if(password[i] == passw)
                    file << passw2 << endl;
                else
                    file << password[i];
            }
            file.close();
            logged_in = false;
            cexit = true;
        }
    }
}

int main()
{
    User user;
    char choice;
    bool logged_in = false;
    bool quit_p = true;
    cout << "Welcome RDJ program" << endl;
    while(quit_p == true)
    {
        cout << "IF you dont have account please enter 'C' to create account or you have account please enter 'L' to login : " << endl;
        cin >> choice;
        if(choice == 'c' || choice == 'C') 
            create_account(user);
        else if(choice == 'l' || choice == 'L')
            logged_in = login(user);
        if(logged_in == false)
            cout << "Login failed. Please try again." << endl;
        while(logged_in == true)
        {
            string filename = (username_file + "_data") + ".txt";
            cout << "Welcome" << " " << user.first_name << " " << user.last_name << " " << user.user_name << endl;
            cout << "T : Create text file" << endl;
            cout << "W : Write your text file" << endl;
            cout << "R : Read your text file" << endl;
            cout << "C : Change the personal information : " << endl;
            cout << "Q : Quit the program" << endl;

            char action;
            cin >> action;

            if(action == 'T' || action == 't')
            {
                ofstream myFile(filename);
                cout << "Your text file created." << endl;
            }
            else if(action == 'W' || action == 'w')
            {       
                ofstream myFile(filename, ios::app);
                if (myFile.is_open())
                {
                    cout << "Please enter the sentence : " << endl;
                    string sentence;
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, sentence);
                    myFile << sentence << endl;
                    myFile.close();
                }
            }
            else if(action == 'R' || action == 'r')
            {
                ifstream f(filename);
                if(!f.is_open())
                {
                    cerr << "Error : File is not found. Please create a file first." << endl;
                }
                string s;
                while(getline(f, s))
                {
                    cout << s << endl;
                }
                this_thread::sleep_for(chrono::seconds(1));
                cout << "File reading completed." << endl;
                f.close();
            }
            else if(action == 'C' || action == 'c')
                change_information(filename, logged_in);
            else if(action == 'Q' || action == 'q')
            {
                cout << "Thank you for using our program goodbye" << endl;
                logged_in = false;
                cout << endl;
            }
            else{
                cout << "You pressed wrong button please true button press" << endl;
            }
        }
    }
