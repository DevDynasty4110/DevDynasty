#pragma once
#include <wx/wx.h>

// Name macros:
#define __APP_NAME "Sudoku"


// app declaration
// structure citation: https://docs.wxwidgets.org/latest/overview_helloworld.html
class SudokuApp : public wxApp
{
public:
    bool OnInit() override;
};


class SudokuFrame : public wxFrame
{
public:
    SudokuFrame();

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
};

enum
{
    ID_Hello = 1
};

bool SudokuApp::OnInit()
{
    SudokuFrame *frame = new SudokuFrame();
    frame->Show();
    return true;
}

SudokuFrame::SudokuFrame()
    : wxFrame(nullptr, wxID_ANY, __APP_NAME)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &SudokuFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &SudokuFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &SudokuFrame::OnExit, this, wxID_EXIT);
}

void SudokuFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void SudokuFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void SudokuFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}