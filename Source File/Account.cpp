#include "Account.h"
#include <wx/wx.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool Account::check_information(const std::string ma, const std::string pas)
{
	ifstream user("users.txt");
	string username_file, mail_file, pass_file;
	while (user >> username_file >> mail_file >> pass_file)
	{
		if (mail_file == ma && pass_file == pas)
			return true;
	}
	return false;
}

bool Account::CheckMail(string mail3)
{
	return mail3.find("gmail.com") != string::npos ||
		mail3.find("hotmail.com") != string::npos;
}

bool Account::CheckPass(string pass3) {
	if (pass3.size() < 8)
		return false;
	bool has_digit = false, has_letter = false;
	for (auto c : pass3)
	{
		if (isalpha(c)) has_letter = true;
		if (isdigit(c)) has_digit = true;
	}
	return has_letter && has_digit;
}

void Account::SaveAccount(const string use, const string mail4, const string pass4)
{
	ofstream user("users.txt", ios::app);
	user << use << " " << mail4 << " " << pass4 << endl;
	user.close();
}