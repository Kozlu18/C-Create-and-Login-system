#pragma once
#include <wx/wx.h>
class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title);
private :
	void BindEventHandlers();
	void CreateControl();
	void SingUp(wxCommandEvent& evt);
	void Login(wxCommandEvent& evt);
	void CheckAccount(wxCommandEvent& evt);
	void OnReturn(wxCommandEvent& evt);
	void CheckSing(wxCommandEvent& evt);

	wxPanel* panel;
	wxButton* BSingUp;
	wxButton* BLogin;
	wxButton* Singin;
	wxButton* rexit;
	wxButton* add;
	wxTextCtrl* Mailtext;
	wxTextCtrl* PasswordText;
	wxTextCtrl* username;
	wxStaticText* mailtext2;
	wxStaticText* passwordtext2;
	wxStaticText* error;
	wxStaticText* tc;
	wxStaticText* fc;
	wxStaticText* serror;
	wxStaticText* perror;
	wxStaticText* comp;
	wxStaticText* user;
};

