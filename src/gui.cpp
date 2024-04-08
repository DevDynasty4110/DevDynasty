#include <wx/wx.h>
#include <wx/grid.h>
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
    wxPanel* sudokuGridPanel;  // Panel for the Sudoku grid
    wxPanel* drawingPanel;

    void OnDrawPanel(wxPaintEvent& evt);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnEasy(wxCommandEvent& event);
    void OnMedium(wxCommandEvent& event);
    void OnHard(wxCommandEvent& event);
    void OnHint(wxCommandEvent& event);
    void OnSolve(wxCommandEvent& event);
    void OnSubmit(wxCommandEvent& event);
    void UpdateBoardDisplay();  // Update the GUI for the Sudoku board

    wxBoxSizer* sizer = nullptr;  // Sizer for buttons
    wxButton* btnEasy = nullptr;  // Button for 'Easy'
    wxButton* btnMedium = nullptr; // Button for 'Medium'
    wxButton* btnHard = nullptr;   // Button for 'Hard'
    wxButton* btnHint = nullptr;   // Button for 'Hint'
    wxButton* btnSubmit = nullptr; //Button for submit
    wxButton* btnSolve = nullptr; 
};

enum {
    ID_Easy = 0,
    ID_Medium,
    ID_Hard,
    ID_Hint,
    ID_Solve,
    ID_Submit
};

wxIMPLEMENT_APP(SudokuApp);

bool SudokuApp::OnInit() {
    SudokuFrame* frame = new SudokuFrame();
    frame->Show(true);
    return true;
}

SudokuFrame::SudokuFrame() : wxFrame(nullptr, wxID_ANY, "Sudoku by DevDynasty", wxDefaultPosition, wxSize(1920, 1080)) {
    // Show full screen
    ShowFullScreen(true);

    // Setup the drawing panel
    drawingPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1920, 1080)); 
//    drawingPanel->Bind(wxEVT_PAINT, &SudokuFrame::OnDrawPanel, this);

    // Setup menu
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

    // Setup buttons and sizer
    sizer = new wxBoxSizer(wxVERTICAL);
    btnEasy = new wxButton(this, ID_Easy, "Easy");
    btnMedium = new wxButton(this, ID_Medium, "Medium");
    btnHard = new wxButton(this, ID_Hard, "Hard");
    btnHint = new wxButton(this, ID_Hint, "Hint");
    btnSubmit = new wxButton(this, ID_Submit, "Submit");
    btnSolve = new wxButton(this, ID_Solve, "Solve");

    btnSubmit->Hide();
    btnHint->Hide();
    btnSolve->Hide();

    sizer->Add(btnSubmit, 0, wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(btnEasy, 0, wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(btnMedium, 0, wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(btnHard, 0, wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(btnHint, 0, wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(btnSolve, 0, wxALIGN_CENTER_HORIZONTAL, 10);

    this->SetSizer(sizer);
    this->Layout();  // Apply the layout changes

    // Event bindings
    Bind(wxEVT_BUTTON, &SudokuFrame::OnEasy, this, ID_Easy);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnMedium, this, ID_Medium);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnHard, this, ID_Hard);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnHint, this, ID_Hint);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnSolve, this, ID_Solve);
    Bind(wxEVT_MENU, &SudokuFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &SudokuFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &SudokuFrame::OnSubmit, this, ID_Submit);

    // Initialize the Sudoku grid panel
    sudokuGridPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(360, 360));
    sudokuGridSizer = new wxGridSizer(9, 9, 0, 0);
    sudokuGridPanel->SetSizer(sudokuGridSizer);
}

void SudokuFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void SudokuFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Sudoku Game", "About Sudoku Game", wxOK | wxICON_INFORMATION);
}

void SudokuFrame::OnEasy(wxCommandEvent& event) {
    game.startGame();
    game.setDifficulty(__EASY);
    game.board.generateBoard(0); // 0 = easy
    UpdateBoardDisplay();
    btnHint->Show();
    btnEasy->Hide();
    btnMedium->Hide();
    btnHard->Hide();
    btnSubmit->Show();
    btnSolve->Show();
    this->Layout();
}

void SudokuFrame::OnMedium(wxCommandEvent& event) {
    game.startGame();
    game.setDifficulty(__MEDIUM);
    game.board.generateBoard(1); // 1 = medium
    UpdateBoardDisplay();
    btnHint->Show();
    btnEasy->Hide();
    btnMedium->Hide();
    btnHard->Hide();
    btnSubmit->Show();
    btnSolve->Show();
    this->Layout();
}

void SudokuFrame::OnHard(wxCommandEvent& event) {
    game.startGame();
    game.setDifficulty(__HARD);
    game.board.generateBoard(2); // 2 = hard
    UpdateBoardDisplay();
    btnHint->Show();
    btnSubmit->Show();
    btnEasy->Hide();
    btnMedium->Hide();
    btnHard->Hide();
    btnSolve->Show();
    this->Layout();
}

void SudokuFrame::OnHint(wxCommandEvent& event) {
    // Hint button logic
    game.getHint(); // Get a hint
    UpdateBoardDisplay();
}

void SudokuFrame::OnSolve(wxCommandEvent& event) {
    game.solve(); 
    UpdateBoardDisplay();
}

void SudokuFrame::OnSubmit(wxCommandEvent& event) {
    game.submit();
    if (game.win) {
        wxString message;
        message.Printf("Congratulations! Correct!!.\nYour score: %d", game.finalScore);
        wxMessageBox(message, "Result", wxOK | wxICON_INFORMATION, this);
    } else {
        wxMessageBox("Sorry, incorrect :( \n Try a hint!");
    }
}


/*
void SudokuFrame::OnDrawPanel(wxPaintEvent& evt) {
    wxPaintDC dc(drawingPanel);
    dc.SetPen(wxPen(*wxBLACK, 3)); // Black pen with thickness 3
    int tileHeight = 38; // Height of one tile
    int lineThickness = 3; // Thickness of the lines
    int sectionHeight = (3 * tileHeight) + (2 * lineThickness); // Height of one section
    int width, height;
    drawingPanel->GetSize(&width, &height);
    for (int i = 1; i <= 2; ++i) {
        dc.DrawLine(width / 3 * i, 0, width / 3 * i, height);
        dc.DrawLine(0, sectionHeight * i, width, sectionHeight * i);
    }
}*/

void SudokuFrame::UpdateBoardDisplay() {
    sudokuGridSizer->Clear(true);  //Clear the existing grid
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            Tile tile = game.board.getTile(row, col);
            wxString value = tile.value != 0 ? wxString::Format(wxT("%d"), tile.value) : "";
            wxTextCtrl* cell = new wxTextCtrl(sudokuGridPanel, wxID_ANY, value, wxDefaultPosition, wxSize(40, 40), wxTE_CENTRE);
            sudokuGridSizer->Add(cell, 0, wxALL, 1);
        }
    }
    sudokuGridPanel->Layout();  //Update the layout of the Sudoku grid panel
}

