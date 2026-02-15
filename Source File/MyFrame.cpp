#include "MyFrame.h"
#include "Account.h"
#include <wx/wx.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

using namespace std;

enum ID {
    SingUp_ID = 1,
    Login_ID = 2,
    SingIn_ID = 3,
    Returnext_ID = 4,
    add_ID = 5,
};

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
    CreateControl();
    BindEventHandlers();
}

void MyFrame::CreateControl()
{
    wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 24)));

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    BSingUp = new wxButton(panel, SingUp_ID, "SingUp", wxPoint(325, 240));
    BLogin = new wxButton(panel, Login_ID, "Login", wxPoint(325, 200));

    Singin = new wxButton(panel, SingIn_ID, "SingIn", wxPoint(575, 340));
    rexit = new wxButton(panel, Returnext_ID, "Return", wxPoint(150, 340));

    Singin->Show(false);
    rexit->Show(false);

    BSingUp->SetMinSize(wxSize(100, 35));
    BLogin->SetMinSize(wxSize(100, 35));

}

void MyFrame::Login(wxCommandEvent& evt) {
    BSingUp->Show(false);
    BLogin->Show(false);

    mailtext2 = new wxStaticText(panel, wxID_ANY, "Mail", wxPoint(176, 175));
    Mailtext = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(175, 200), wxSize(500, 40));

    passwordtext2 = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(176, 250));
    PasswordText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(175, 275), wxSize(400, 40));

    Singin->Show(true);
    rexit->Show(true);

}

void MyFrame::SingUp(wxCommandEvent& evt)
{
    BSingUp->Show(false);
    BLogin->Show(false);

    user = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(176, 100));
    username = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(175, 125), wxSize(500, 40));

    mailtext2 = new wxStaticText(panel, wxID_ANY, "Mail", wxPoint(176, 175));
    Mailtext = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(175, 200), wxSize(500, 40));

    passwordtext2 = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(176, 250));
    PasswordText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(175, 275), wxSize(400, 40));

    add = new wxButton(panel, add_ID, "Add", wxPoint(575, 340));

    add->Show(true);
    rexit->Show(true);
}

void MyFrame::CheckSing(wxCommandEvent& evt)
{
    wxString mail2 = Mailtext->GetValue();
    wxString pass2 = PasswordText->GetValue();
    wxString username2 = username->GetValue();

    std::string mail5 = mail2.ToStdString();
    std::string pass5 = pass2.ToStdString();
    std::string username3 = username2.ToStdString();

    if (perror) { perror->Hide(); perror = nullptr; }
    if (serror) { serror->Hide(); serror = nullptr; }

    Account myaccount;

    bool tm = myaccount.CheckMail(mail5);
    if (!tm)
    {
        serror = new wxStaticText(panel, wxID_ANY, "Your mail is wrong", wxDefaultPosition);
        serror->Show();
    }
    else {
        bool tp = myaccount.CheckPass(pass5);
        if (tp)
        {
            if (perror) { perror->Destroy(); perror = nullptr; perror->Hide(); }
            if (serror) { serror->Destroy(); serror = nullptr; serror->Hide(); }
            myaccount.SaveAccount(username3, mail5, pass5);
            comp = new wxStaticText(panel, wxID_ANY, "Your account succesfully created. Please click return button", wxDefaultPosition);
        }
        else {
            perror = new wxStaticText(panel, wxID_ANY, "The password you entered does not meet the required criteria.", wxDefaultPosition);
            perror->Show();
        }
    }
}

void MyFrame::CheckAccount(wxCommandEvent& evt)
{
    ifstream user("users.txt");
    if (!user.is_open())
        error = new wxStaticText(panel, wxID_ANY, "Users file is not found. Please create account");
    else {
        wxString mail = Mailtext->GetValue();
        wxString password = PasswordText->GetValue();

        std::string mail_file2 = mail.ToStdString();
        std::string pass_file2 = password.ToStdString();

        Account myact;

        bool tf = false;
        tf = myact.check_information(mail_file2, pass_file2);
        if (tf)
        {
            Singin->Hide();
            Mailtext->Hide();
            mailtext2->Hide();
            PasswordText->Hide();
            passwordtext2->Hide();
            rexit->Show(true);

            tc = new wxStaticText(panel, wxID_ANY, "Login succesfuly.", wxPoint(275, 200));
            user.close();
        }
        else {
            fc = new wxStaticText(panel, wxID_ANY, "Your information is wrong please try again.", wxPoint(325, 50));
            user.close();
        }
    }
}

void MyFrame::OnReturn(wxCommandEvent& evt)
{
    if (mailtext2) { mailtext2->Destroy(); }
    if (Mailtext) { Mailtext->Destroy(); }

    if (passwordtext2) { passwordtext2->Destroy(); }
    if (PasswordText) { PasswordText->Destroy(); }

    if (user) { user->Hide(); user = nullptr; }
    if (username) { username->Hide(); username = nullptr; }

    if (Singin) { Singin->Hide(); }
    if (add) { add->Hide(); }
    if (rexit) { rexit->Show(false); }

    if (error) { error->Hide(); error = nullptr; }
    if (serror) { serror->Destroy(); serror = nullptr; }
    if (perror) { perror->Destroy(); perror = nullptr; }
    if (comp) { comp->Hide(); comp = nullptr; }

    if (tc) { tc->Hide(); }
    if (fc) { fc->Hide(); }

    if (BSingUp) BSingUp->Show();
    if (BLogin) BLogin->Show();
}

void MyFrame::BindEventHandlers()
{
    BSingUp->Bind(wxEVT_BUTTON, &MyFrame::SingUp, this);
    BLogin->Bind(wxEVT_BUTTON, &MyFrame::Login, this);
    Bind(wxEVT_BUTTON, &MyFrame::CheckAccount, this, SingIn_ID);
    Bind(wxEVT_BUTTON, &MyFrame::OnReturn, this, Returnext_ID);
    Bind(wxEVT_BUTTON, &MyFrame::CheckSing, this, add_ID);
}

