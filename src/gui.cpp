#include "../include/gui.h"

#ifdef GUI // only compiles if "#define GUI" is uncommented

class SudokuApp : public wxApp {
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(SudokuApp);

class SudokuFrame : public wxFrame {
public:
    SudokuFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnEasy(wxCommandEvent& event);
    void OnMedium(wxCommandEvent& event);
    void OnHard(wxCommandEvent& event);
};

enum {
    ID_Hello = 1,
    ID_Easy,
    ID_Medium,
    ID_Hard
};

bool SudokuApp::OnInit() {
    SudokuFrame* frame = new SudokuFrame();
    frame->Show();
    return true;
}

SudokuFrame::SudokuFrame()
    : wxFrame(nullptr, wxID_ANY, __APP_NAME) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    // Adding buttons
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxButton* btnEasy = new wxButton(this, ID_Easy, "Easy");
    wxButton* btnMedium = new wxButton(this, ID_Medium, "Medium");
    wxButton* btnHard = new wxButton(this, ID_Hard, "Hard");
    sizer->Add(btnEasy, 0, wxALL, 10);
    sizer->Add(btnMedium, 0, wxALL, 10);
    sizer->Add(btnHard, 0, wxALL, 10);

    SetSizer(sizer);

    // Binding button events
    Bind(wxEVT_BUTTON, &SudokuFrame::OnEasy, this, ID_Easy);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnMedium, this, ID_Medium);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnHard, this, ID_Hard);
}

void SudokuFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void SudokuFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void SudokuFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}

void SudokuFrame::OnEasy(wxCommandEvent& event) {
    wxLogMessage("Easy mode selected!");
}

void SudokuFrame::OnMedium(wxCommandEvent& event) {
    wxLogMessage("Medium mode selected!");
}

void SudokuFrame::OnHard(wxCommandEvent& event) {
    wxLogMessage("Hard mode selected!");
}

#endif
