//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: filechecklistbase.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "filechecklistbase.h"


// Declare the bitmap loading function
extern void wxCraftertLrKnvInitBitmapResources();

static bool bBitmapLoaded = false;


FileCheckListBase::FileCheckListBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCraftertLrKnvInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer1);
    
    m_caption = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer1->Add(m_caption, 0, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer3 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer1->Add(bSizer3, 1, wxEXPAND, 5);
    
    wxArrayString m_fileCheckListArr;
    m_fileCheckList = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxSize(400,300), m_fileCheckListArr, wxLB_SINGLE);
    
    bSizer3->Add(m_fileCheckList, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer4 = new wxBoxSizer(wxVERTICAL);
    
    bSizer3->Add(bSizer4, 0, wxEXPAND, 5);
    
    m_clearAll = new wxButton(this, wxID_ANY, _("C&lear All"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer4->Add(m_clearAll, 0, wxALL|wxEXPAND, 5);
    
    m_checkAllButton = new wxButton(this, wxID_ANY, _("Check &All"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer4->Add(m_checkAllButton, 0, wxALL|wxEXPAND, 5);
    
    m_selectedFilePath = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), wxTE_READONLY);
    #if wxVERSION_NUMBER >= 3000
    m_selectedFilePath->SetHint(wxT(""));
    #endif
    
    bSizer1->Add(m_selectedFilePath, 0, wxALL|wxEXPAND, 5);
    
    m_stdBtnSizer2 = new wxStdDialogButtonSizer();
    
    bSizer1->Add(m_stdBtnSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    
    m_buttonOK = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer2->AddButton(m_buttonOK);
    
    m_buttonCancel = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer2->AddButton(m_buttonCancel);
    m_stdBtnSizer2->Realize();
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_clearAll->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FileCheckListBase::OnClearAll), NULL, this);
    m_checkAllButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FileCheckListBase::OnCheckAll), NULL, this);
    
}

FileCheckListBase::~FileCheckListBase()
{
    m_clearAll->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FileCheckListBase::OnClearAll), NULL, this);
    m_checkAllButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FileCheckListBase::OnCheckAll), NULL, this);
    
}

FilesModifiedDlgBase::FilesModifiedDlgBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCraftertLrKnvInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* boxSizer26 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer26);
    
    m_staticText34 = new wxStaticText(this, wxID_ANY, _("Some files were modified outside of the editor.\nWhat would you like to do?"), wxDefaultPosition, wxSize(-1,-1), 0);
    wxFont m_staticText34Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText34Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText34->SetFont(m_staticText34Font);
    
    boxSizer26->Add(m_staticText34, 0, wxALL, 5);
    
    m_cmdLnkBtn30 = new wxCommandLinkButton(this, ID_BUTTON_LOAD, _("Reload."), _("Reload all the externally modified files"), wxDefaultPosition, wxSize(-1,-1), wxBU_LEFT);
    
    boxSizer26->Add(m_cmdLnkBtn30, 1, wxALL|wxEXPAND, 5);
    
    m_cmdLnkBtn28 = new wxCommandLinkButton(this, ID_BUTTON_CHOOSE, _("Choose."), _("Let me choose which file or files to reload"), wxDefaultPosition, wxSize(-1,-1), wxBU_LEFT);
    m_cmdLnkBtn28->SetFocus();
    
    boxSizer26->Add(m_cmdLnkBtn28, 1, wxALL|wxEXPAND, 5);
    
    m_cmdLnkBtnNone = new wxCommandLinkButton(this, ID_BUTTON_IGNORE, _("Ignore."), _("Don't reload any the externally modified files"), wxDefaultPosition, wxSize(-1,-1), wxBU_LEFT);
    
    boxSizer26->Add(m_cmdLnkBtnNone, 1, wxALL|wxEXPAND, 5);
    
    m_checkBoxRemember = new wxCheckBox(this, wxID_ANY, _("Remember my answer"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_checkBoxRemember->SetValue(false);
    
    boxSizer26->Add(m_checkBoxRemember, 0, wxALL, 5);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_cmdLnkBtn30->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FilesModifiedDlgBase::OnLoad), NULL, this);
    m_cmdLnkBtn28->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FilesModifiedDlgBase::OnChoose), NULL, this);
    m_cmdLnkBtnNone->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FilesModifiedDlgBase::OnIgnore), NULL, this);
    
}

FilesModifiedDlgBase::~FilesModifiedDlgBase()
{
    m_cmdLnkBtn30->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FilesModifiedDlgBase::OnLoad), NULL, this);
    m_cmdLnkBtn28->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FilesModifiedDlgBase::OnChoose), NULL, this);
    m_cmdLnkBtnNone->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FilesModifiedDlgBase::OnIgnore), NULL, this);
    
}
