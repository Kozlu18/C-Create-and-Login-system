#include "MyFrame.h"
#include <wx/wx.h>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

bool check(wxString& email, wxString& pass)
{
    ifstream user("users.txt");
    string mail_file, pass_file;
    while (user >> mail_file >> pass_file)
    {
        if (mail_file == email && pass_file == pass)
            return true;
    }
    return false;
}

enum ID {
    SingUp_ID = 1,
    Login_ID = 2,
    SingIn_ID = 3,
    Returnext_ID = 4,
};

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600),wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
    CreateControl();
    BindEventHandlers(); 
}

void MyFrame::CreateControl()
{
    wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 24)));

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    BSingUp = new wxButton(panel, SingUp_ID, "SingUp", wxPoint(325,200));
    BLogin = new wxButton(panel, Login_ID, "Login", wxPoint(325,240));

    BSingUp->SetMinSize(wxSize(100, 35));
    BLogin->SetMinSize(wxSize(100, 35));

}

void MyFrame::SingUp(wxCommandEvent& evt) {
    BSingUp->Show(false);
    BLogin->Show(false);

    mailtext2 = new wxStaticText(panel, wxID_ANY, "Mail", wxPoint(176, 175));
    Mailtext = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(175, 200), wxSize(500, 40));

    passwordtext2 = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(176, 250));
    PasswordText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(175, 275), wxSize(400, 40));

    Singin = new wxButton(panel, SingIn_ID, "SingIn", wxPoint(575,340));
    rexit = new wxButton(panel, Returnext_ID, "Return", wxPoint(150, 340));
}

void MyFrame::Login(wxCommandEvent& evt)
{

}

void MyFrame::CheckAccount(wxCommandEvent& evt)
{
    ifstream user("users.txt");
    if (!user.is_open())
        error = new wxStaticText(panel, wxID_ANY, "Users file is not found. Please create account");
    else {
        wxString mail = Mailtext->GetValue();
        wxString password = PasswordText->GetValue();

        bool tf = false;
        tf = check(mail, password);
        if (tf)
        {
            Singin->Show(false);
            Mailtext->Show(false);
            mailtext2->Show(false);
            PasswordText->Show(false);
            passwordtext2->Show(false);
            rexit->Show(false);

            wxStaticText* tc = new wxStaticText(panel, wxID_ANY, "Sing-up succesfuly.", wxPoint(275, 200));
        }
        else {
            wxStaticText* fc = new wxStaticText(panel, wxID_ANY, "Your information is wrong please try again.", wxPoint(325, 200));
        }
    }
}

void MyFrame::OnReturn(wxCommandEvent& evt)
{
    if (mailtext2) { mailtext2->Destroy(); mailtext2 = nullptr; }
    if (Mailtext) { Mailtext->Destroy(); Mailtext = nullptr; }
    if (passwordtext2) { passwordtext2->Destroy(); passwordtext2 = nullptr; }
    if (PasswordText) { PasswordText->Destroy(); PasswordText = nullptr; }
    if (Singin) { Singin->Destroy(); Singin = nullptr; }
    if (rexit) { rexit->Destroy(); rexit = nullptr; }
    if (error) { error->Destroy(); error = nullptr; }

    if (BSingUp) BSingUp->Show(true);
    if (BLogin) BLogin->Show(true);
}

void MyFrame::BindEventHandlers()
{
    BSingUp->Bind(wxEVT_BUTTON, &MyFrame::SingUp, this);
    BLogin->Bind(wxEVT_BUTTON, &MyFrame::Login, this);
    Bind(wxEVT_BUTTON, &MyFrame::CheckAccount, this, SingIn_ID);
    Bind(wxEVT_BUTTON, &MyFrame::OnReturn, this, Returnext_ID);
}

