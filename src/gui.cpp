#include <wx/wx.h>
#include <wx/grid.h>
#include <X11/Xlib.h>
#include "../include/sudoku.h"  
#include "../include/board.h"


class SudokuApp : public wxApp {
public:
    virtual bool OnInit();
};

class SudokuFrame : public wxFrame {
public:
    SudokuFrame();

private:
    Game game;  // Instance of Sudoku game
    wxGridSizer* sudokuGridSizer = nullptr;
    
    wxPanel* drawingPanel;

    void OnDrawPanel(wxPaintEvent& evt);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnEasy(wxCommandEvent& event);
    void OnMedium(wxCommandEvent& event);
    void OnHard(wxCommandEvent& event);
    void OnHint(wxCommandEvent& event);
    void UpdateBoardDisplay();  // method to ppdate the GUI 
    wxBoxSizer* sizer = nullptr;    // Sizer for buttons
    wxButton* btnEasy = nullptr;    // Button for Easy
    wxButton* btnMedium = nullptr;  // Button for Medium
    wxButton* btnHard = nullptr;    // Button for Hard
    wxButton* btnHint = nullptr;

    //Display* disp = XOpenDisplay(NULL);
    //Screen*  scrn = DefaultScreenOfDisplay(disp);
    //int height = scrn->height;
    //int width  = scrn->width;
};

enum {
    ID_Easy = 0,
    ID_Medium = 1,
    ID_Hard = 2,
    ID_Hint = 3
};

wxIMPLEMENT_APP(SudokuApp);

bool SudokuApp::OnInit() {
    SudokuFrame* frame = new SudokuFrame();
    frame->Show(true);
    return true;
}

SudokuFrame::SudokuFrame() : wxFrame(nullptr, wxID_ANY, "Sudoku by DevDynasty", wxDefaultPosition, wxSize(1920, 1080)) {
//, wxDEFAULT_FRAME_STYLE & ~(wxMAXIMIZE_BOX | wxRESIZE_BORDER)) {
    //gridline setup
    ShowFullScreen(true);
    drawingPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1920, 1080)); 
    drawingPanel->Bind(wxEVT_PAINT, &SudokuFrame::OnDrawPanel, this);
    //menu setup
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to Sudoku Game!");

    sizer = new wxBoxSizer(wxVERTICAL);

    btnEasy = new wxButton(this, ID_Easy, "Easy");
    btnMedium = new wxButton(this, ID_Medium, "Medium");
    btnHard = new wxButton(this, ID_Hard, "Hard");
    btnHint = new wxButton(this, ID_Hint, "Hint");

    btnHint->Hide();

    sizer->Add(btnEasy, 0, wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(btnMedium, 0, wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(btnHard, 0, wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(btnHint, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    this->SetSizer(sizer);
    this->Layout();  // Apply the layout changes

    //event bindings
    Bind(wxEVT_BUTTON, &SudokuFrame::OnEasy, this, ID_Easy);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnMedium, this, ID_Medium);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnHard, this, ID_Hard);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnHint, this, ID_Hint);
    Bind(wxEVT_MENU, &SudokuFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &SudokuFrame::OnExit, this, wxID_EXIT);

    // grid sizer for the Sudoku board
    sudokuGridSizer = new wxGridSizer(9, 9, 0, 0);
    this->SetSizer(sudokuGridSizer);
}

void SudokuFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void SudokuFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Sudoku Game", "About Sudoku Game", wxOK | wxICON_INFORMATION);
}
//event presses
void SudokuFrame::OnEasy(wxCommandEvent& event) {
    game.board.generateBoard(0); //generates board using the generateBoard function from the board class
    UpdateBoardDisplay(); //updates board display

    //hides buttons when they are pressed
    btnHint->Show();
    btnEasy->Hide();
    btnMedium->Hide();
    btnHard->Hide();
    this->Layout();
}
//
void SudokuFrame::OnMedium(wxCommandEvent& event) {
    game.board.generateBoard(1); //0 = easy, 1 = medium, 2 = hard
    UpdateBoardDisplay();

    btnHint->Show();
    btnEasy->Hide();
    btnMedium->Hide();
    btnHard->Hide();
    this->Layout();
}

void SudokuFrame::OnHard(wxCommandEvent& event) {
    game.board.generateBoard(2); 
    UpdateBoardDisplay();

    btnHint->Show();
    btnEasy->Hide();
    btnMedium->Hide();
    btnHard->Hide();
    this->Layout();
}

void SudokuFrame::OnHint(wxCommandEvent& event) {
    //place holder for now
    btnHint->Show();
}

void SudokuFrame::OnDrawPanel(wxPaintEvent& evt) {
    wxPaintDC dc(drawingPanel);
    dc.SetPen(wxPen(*wxBLACK, 3)); 

    int tileHeight = 38; // Height of one tile
    int lineThickness = 3; 
    int sectionHeight = (3 * tileHeight) + (2 * lineThickness); // Height of one section

    // Draw the 3x3 grid lines
    int width, height;
    drawingPanel->GetSize(&width, &height);

    for (int i = 1; i <= 2; ++i) {
        // Draw vertical line
        dc.DrawLine(width / 3 * i, 0, width / 3 * i, height);
        // Draw horizontal line
        dc.DrawLine(0, sectionHeight * i, width, sectionHeight * i);
    }
}

void SudokuFrame::UpdateBoardDisplay() {
    sudokuGridSizer->Clear(true);  // Clear the existing grid

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            Tile tile = game.board.getTile(row, col);
            wxString value = tile.value != 0 ? wxString::Format(wxT("%d"), tile.value) : "";
            wxTextCtrl* cell = new wxTextCtrl(this, wxID_ANY, value, wxDefaultPosition, wxSize(40, 40), wxTE_CENTRE);
            sudokuGridSizer->Add(cell, 0, wxALL, 1);
        }
    }

    this->Layout();  // Update the layout
}

