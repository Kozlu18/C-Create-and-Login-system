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

/*void change_personal_information(User &user)
{
    string new_first_name, new_last_name, new_user_name, new_password, old_password;
    cout << "Please enter your new first_name : ";
    cin >> new_first_name;
    user.first_name = new_first_name;
    cout << "Please enter your new last name : ";
    cin >> new_last_name;
    user.last_name = new_last_name;
    cout << "Please enter new username : ";
    cin >> new_user_name;
    user.user_name = new_user_name;
    cout << "Please old password : ";
    cin >> old_password;
    while(old_password != user.password)
    {
        cout << "Your old password is incorrect. Please try again : ";
        cin >> old_password;
    }
    
    do{
        cout << "Please enter your new password : ";
        cin >> new_password;
    }while(!is_valid_password(new_password));
    cout << "Your personal information has been changed successfully" << endl;
    user.password = new_password;
}

void show_information(User &user)
{
    cout << "Your first name and last name : " << user.first_name << " " << user.last_name << endl;
    cout << "Your username : " << user.user_name << endl;
    cout << "Your email : " << user.email << endl;
    string s;
    cout << "İf you see password enter your password : ";
    cin >> s;
    int check = 0;
    while(user.password != s)
    {
        cout << "Your password is wrong please try again : ";
        cin >> s;
        check += 1;
        if(check >= 3)
        {
            cout << "You wrong password writed 3 and most 3 attemps please wait 60 seconds...";
            this_thread::sleep_for(chrono::seconds(60));
            check = 0;
            cout << "Please try again : ";
            cin >> s;
        }
    }
    cout << "Your password : " << user.password << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

void delete_information(User &user, bool &logged_in)
{
    string st;
    while(st != "DELETE")
    {
        cout << "Are you right delete your personal information please write 'DELETE' " << endl;
        cin >> st;
        if(st != "DELETE")
            cout << "You wrong writed delete. Please try again" << endl;
    }

    if(st == "DELETE")
    {
        user.first_name = "";
        user.last_name = "";
        user.user_name = "";
        user.password = "";
        user.email = "";
        cout << "Your personal information is deleting...";
        this_thread::sleep_for(chrono::seconds(3));
        cout << endl << "Your personal information is deleted." << endl;
        logged_in = false;
    }
}
*/
int main()
{
    User user;
    char choice;
    bool logged_in = false;
    bool quit_p = true;
    cout << "Welcome RDJ program" << endl;
    while(logged_in == false && quit_p == true)
    {
        cout << "IF you dont have account please enter 'C' to create account or you have account please enter 'L' to login : " << endl;
        cin >> choice;
        if(choice == 'c' || choice == 'C') 
            create_account(user);
        else if(choice == 'l' || choice == 'L')
            logged_in = login(user);
        if(logged_in == false)
            cout << "Login failed. Please try again." << endl;
        if(logged_in == true)
            quit_p = false;
        while(logged_in == true && quit_p == false)
        {
            cout << "Welcome" << " " << user.first_name << " " << user.last_name << " " << user.user_name << endl;
            //cout << "F : Change personel information" << endl;
            //cout << "S : Show the personal information" << endl;
            cout << "T : Create text file" << endl;
            cout << "W : Write your text file" << endl;
            cout << "R : Read your text file" << endl;
            //cout << "D : Delete your personal information" << endl;
            cout << "Q : Quit the program" << endl;
            char action;
            cin >> action;
            /*if(action == 'F' || action == 'f')
                change_personal_information(user);
            else if(action == 'S' || action == 's')
                show_information(user);
            */if(action == 'T' || action == 't')
            {
                ofstream myFile("user_data.txt");
                cout << "Your text file creating...";
                this_thread::sleep_for(chrono::seconds(2));
                cout << endl;
                cout << "Your text file created." << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            else if(action == 'W' || action == 'w')
            {       
                ofstream myFile("user_data.txt");
                if (myFile.is_open())
                {
                    cout << "How much word use : ";
                    int w;
                    cin >> w;
                    for(int i = 0; i < w; i++)
                    {
                        vector<string> text(w, "");
                        cout << "Write your idea : ";
                        cin >> text[i];
                        myFile << text[i] << " ";
                    }
                    myFile.close();
                }
            }
            else if(action == 'R' || action == 'r')
            {
                ifstream f("user_data.txt");
                if(!f.is_open())
                {
                    cout << "File not found. Please create a file first." << endl;
                }
                string s;
                while(getline(f, s))
                {
                    cout << s << endl;
                }
                this_thread::sleep_for(chrono::seconds(2));
                cout << "File reading completed." << endl;
                f.close();
            }
            //else if(action == 'D' || action == 'd')
                //delete_information(user, logged_in);
            else if(action == 'Q' || action == 'q')
            {
                cout << "Thank you for using our program goodbye" << endl;
                cout << "Exiting the program...";
                this_thread::sleep_for(chrono::seconds(3));
                quit_p = true;
                logged_in = false;
                cout << endl;
            }
            else{
                cout << "You pressed wrong button please true button press" << endl;
            }
        }
    }
}
