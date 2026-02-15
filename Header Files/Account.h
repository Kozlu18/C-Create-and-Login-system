#pragma once
#include <wx/wx.h>
#include <string>
class Account
{
public :
	bool check_information(std::string ma, std::string pas);
	bool CheckMail(std::string mail3);
	bool CheckPass(std::string pass3);
	void SaveAccount(std::string use, std::string mail4, std::string pass4);
};

