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

	wxPanel* panel;
	wxButton* BSingUp;
	wxButton* BLogin;
	wxButton* Singin;
	wxButton* rexit;
	wxTextCtrl* Mailtext;
	wxTextCtrl* PasswordText;
	wxStaticText* mailtext2;
	wxStaticText* passwordtext2;
	wxStaticText* error;
};

