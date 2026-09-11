/***************************************************************
 * Name:      uFR_Readers_toolMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Digital Logic (support@d-logic.rs)
 * Created:   2019-03-14
 * Copyright: Digital Logic (www.d-logic.net)
 * License:
 **************************************************************/

//#ifdef __linux__
//#define DL_USE_STATIC_LIB
//#endif
//#ifdef _WIN32
//#define DL_USE_STATIC_LIB
//#endif
#include "uFR_Readers_toolMain.h"
#include <wx/msgdlg.h>
#include "ufr-lib/include/uFCoder.h"
//#include "ftd2xx.h"
#include <string.h>
#include <string>
#include <map>

#ifndef _WIN32
#include <unistd.h>
static inline void Sleep(unsigned int milliseconds)
{
    usleep(milliseconds * 1000);
}
#endif

UFR_STATUS status;
uint8_t red_light = 0;

/* std::map<int, uint32_t> baudRate;
baudRate[0] = 2400;
baudRate[1] = 4800;
baudRate[2] = 9600;
baudRate[3] = 19200;
baudRate[4] = 38400;
baudRate[5] = 57600;
baudRate[6] = 115200;
baudRate[7] = 230400;
baudRate[8] = 460800;
baudRate[9] = 500000;
baudRate[10] = 576000;
baudRate[11] = 921600;
baudRate[12] = 1000000;*/

/*
std::map<int, uint32_t> baudRate = {
                                    {0, 2400},
                                    {1, 4800},
                                    {2, 9600},
                                    {3, 19200},
                                    {4, 38400},
                                    {5, 57600},
                                    {6, 115200},
                                    {7, 230400},
                                    {8, 460800},
                                    {9, 500000},
                                    {10, 576000},
                                    {11, 921600},
                                    {12, 1000000}
                                   };
*/

void ConvertStringToUint8Array(std::string str, uint8_t *array)
{
    for(uint32_t i = 0; i < str.length(); i++)
    {
        char x = str.at(i);
        array[i] = (int)x;
    }
}

void uFR_Readers_toolFrame::setStatusColor(UFR_STATUS status)
{
    if(!status)
    {
        StatusLabel->SetForegroundColour(wxColor(0x00287C04));
    }
    else
    {
        StatusLabel->SetForegroundColour("red");
    }
}

//(*InternalHeaders(uFR_Readers_toolFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(uFR_Readers_toolFrame)
const long uFR_Readers_toolFrame::ID_BUTTON1 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON2 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON3 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON4 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON5 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON6 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT3 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL2 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT4 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL3 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT5 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL4 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT6 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL5 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON7 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT19 = wxNewId();
const long uFR_Readers_toolFrame::ID_COMBOBOX5 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON18 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT22 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL14 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT20 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL12 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT21 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL13 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON19 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT7 = wxNewId();
const long uFR_Readers_toolFrame::ID_COMBOBOX1 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT8 = wxNewId();
const long uFR_Readers_toolFrame::ID_COMBOBOX2 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON8 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON9 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON10 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON11 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT9 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL6 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT10 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON12 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT11 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL7 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT12 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON13 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT13 = wxNewId();
const long uFR_Readers_toolFrame::ID_COMBOBOX3 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT14 = wxNewId();
const long uFR_Readers_toolFrame::ID_COMBOBOX4 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON14 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT15 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL8 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT16 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL9 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON15 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT17 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL10 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON16 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT18 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL11 = wxNewId();
const long uFR_Readers_toolFrame::ID_BUTTON17 = wxNewId();
const long uFR_Readers_toolFrame::ID_TEXTCTRL1 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT1 = wxNewId();
const long uFR_Readers_toolFrame::ID_STATICTEXT2 = wxNewId();
const long uFR_Readers_toolFrame::idMenuQuit = wxNewId();
const long uFR_Readers_toolFrame::idMenuAbout = wxNewId();
const long uFR_Readers_toolFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(uFR_Readers_toolFrame,wxFrame)
    //(*EventTable(uFR_Readers_toolFrame)
    //*)
END_EVENT_TABLE()

uFR_Readers_toolFrame::uFR_Readers_toolFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(uFR_Readers_toolFrame)
    wxBoxSizer* BoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer15;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxMenuItem* MenuItem2;
    wxBoxSizer* BoxSizer13;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer11;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer16;
    wxStaticBoxSizer* StaticBoxSizer7;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer14;
    wxStaticBoxSizer* StaticBoxSizer8;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer9;
    wxMenuBar* MenuBar1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;
    wxStaticBoxSizer* StaticBoxSizer5;

    Create(parent, wxID_ANY, _("UFR READERS TOOL version 1.1"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Reader commands"));
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    btnReaderOpen = new wxButton(this, ID_BUTTON1, _("Reader open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer4->Add(btnReaderOpen, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnReaderReset = new wxButton(this, ID_BUTTON2, _("Reader Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer4->Add(btnReaderReset, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnReaderClose = new wxButton(this, ID_BUTTON3, _("ReaderClose"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer4->Add(btnReaderClose, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnReaderSoftRestart = new wxButton(this, ID_BUTTON4, _("Reader Soft Restart"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer4->Add(btnReaderSoftRestart, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnCheckConnection = new wxButton(this, ID_BUTTON5, _("Check connection"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer4->Add(btnCheckConnection, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    BoxSizer4->Add(38,20,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnFactoryReset = new wxButton(this, ID_BUTTON6, _("FACTORY RESET"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    wxFont btnFactoryResetFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    btnFactoryReset->SetFont(btnFactoryResetFont);
    BoxSizer4->Add(btnFactoryReset, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer1->Add(BoxSizer4, 0, wxALL|wxEXPAND, 3);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("reader type :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer5->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    ReaderTypeTB = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(44,21), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    wxFont ReaderTypeTBFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    ReaderTypeTB->SetFont(ReaderTypeTBFont);
    BoxSizer5->Add(ReaderTypeTB, 0, wxALL|wxEXPAND, 3);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("port name :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer5->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    PortNameTB = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(141,23), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    wxFont PortNameTBFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    PortNameTB->SetFont(PortNameTBFont);
    BoxSizer5->Add(PortNameTB, 0, wxALL|wxEXPAND, 3);
    PortInterfaceTB = new wxStaticText(this, ID_STATICTEXT5, _("port interface :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer5->Add(PortInterfaceTB, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    PortInterface = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(45,23), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    wxFont PortInterfaceFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    PortInterface->SetFont(PortInterfaceFont);
    BoxSizer5->Add(PortInterface, 0, wxALL|wxEXPAND, 3);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT6, _("additional :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer5->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    AdditionalTB = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(175,21), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    wxFont AdditionalTBFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    AdditionalTB->SetFont(AdditionalTBFont);
    BoxSizer5->Add(AdditionalTB, 1, wxALL|wxEXPAND, 3);
    btnReaderOpenEx = new wxButton(this, ID_BUTTON7, _("Reader Open Ex"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer5->Add(btnReaderOpenEx, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer1->Add(BoxSizer5, 0, wxALL|wxEXPAND, 3);
    BoxSizer1->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND, 3);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Baud rate settings"));
    StaticText17 = new wxStaticText(this, ID_STATICTEXT19, _("New baud rate: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    StaticBoxSizer7->Add(StaticText17, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    NewBaudCB = new wxComboBox(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX5"));
    NewBaudCB->SetSelection( NewBaudCB->Append(_("9600 bps")) );
    NewBaudCB->Append(_("19200 bps"));
    NewBaudCB->Append(_("38400 bps"));
    NewBaudCB->Append(_("57600 bps"));
    NewBaudCB->Append(_("115200 bps"));
    NewBaudCB->Append(_("234000 bps"));
    NewBaudCB->Append(_("460800 bps"));
    NewBaudCB->Append(_("500000 bps"));
    NewBaudCB->Append(_("1 Mbps"));
    StaticBoxSizer7->Add(NewBaudCB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    bEnterNewBaudRate = new wxButton(this, ID_BUTTON18, _("Enter new baud rate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON18"));
    StaticBoxSizer7->Add(bEnterNewBaudRate, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    BoxSizer16->Add(StaticBoxSizer7, 1, wxALL|wxEXPAND, 3);
    StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Baud rate reset"));
    StaticText20 = new wxStaticText(this, ID_STATICTEXT22, _("reader type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    StaticBoxSizer8->Add(StaticText20, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ReaderTypeResetBR = new wxTextCtrl(this, ID_TEXTCTRL14, wxEmptyString, wxDefaultPosition, wxSize(37,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL14"));
    StaticBoxSizer8->Add(ReaderTypeResetBR, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText18 = new wxStaticText(this, ID_STATICTEXT20, _("COM:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    StaticBoxSizer8->Add(StaticText18, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    COMResetBR = new wxTextCtrl(this, ID_TEXTCTRL12, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL12"));
    wxFont COMResetBRFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    COMResetBR->SetFont(COMResetBRFont);
    StaticBoxSizer8->Add(COMResetBR, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticText19 = new wxStaticText(this, ID_STATICTEXT21, _("port interface:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    StaticBoxSizer8->Add(StaticText19, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    PortInterfaceResetBR = new wxTextCtrl(this, ID_TEXTCTRL13, wxEmptyString, wxDefaultPosition, wxSize(37,24), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL13"));
    wxFont PortInterfaceResetBRFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    PortInterfaceResetBR->SetFont(PortInterfaceResetBRFont);
    StaticBoxSizer8->Add(PortInterfaceResetBR, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    bResetBaudRateToDefault = new wxButton(this, ID_BUTTON19, _("Reset baud rate to default"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON19"));
    StaticBoxSizer8->Add(bResetBaudRateToDefault, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    BoxSizer16->Add(StaticBoxSizer8, 1, wxALL|wxEXPAND, 3);
    BoxSizer2->Add(BoxSizer16, 0, wxALL|wxEXPAND, 0);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Reader signalization"));
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT7, _("Light :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer7->Add(StaticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    LightCB = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX1"));
    LightCB->SetSelection( LightCB->Append(_("None")) );
    LightCB->Append(_("Long green"));
    LightCB->Append(_("Long red"));
    LightCB->Append(_("Alternation"));
    LightCB->Append(_("Flash"));
    BoxSizer7->Add(LightCB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT8, _("Beep :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer7->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    BeepCB = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX2"));
    BeepCB->SetSelection( BeepCB->Append(_("None")) );
    BeepCB->Append(_("Short"));
    BeepCB->Append(_("Long"));
    BeepCB->Append(_("Double short"));
    BeepCB->Append(_("Triple short"));
    BeepCB->Append(_("Triple melody"));
    BoxSizer7->Add(BeepCB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer3->Add(BoxSizer7, 0, wxALL|wxEXPAND, 3);
    btnSetSignalization = new wxButton(this, ID_BUTTON8, _("Set signalization"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    StaticBoxSizer3->Add(btnSetSignalization, 0, wxALL|wxEXPAND, 2);
    btnTurnRedLight = new wxButton(this, ID_BUTTON9, _("Turn red light ON / OFF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    StaticBoxSizer3->Add(btnTurnRedLight, 0, wxALL|wxEXPAND, 2);
    BoxSizer6->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND, 3);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, this, _("Sleep mode"));
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    btnEnterSleepMode = new wxButton(this, ID_BUTTON10, _("Enter sleep mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    BoxSizer8->Add(btnEnterSleepMode, 1, wxALL|wxEXPAND, 3);
    btnLeaveSleepMode = new wxButton(this, ID_BUTTON11, _("Leave sleep mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    BoxSizer8->Add(btnLeaveSleepMode, 1, wxALL|wxEXPAND, 3);
    StaticBoxSizer4->Add(BoxSizer8, 0, wxALL|wxEXPAND, 0);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT9, _("Auto sleep after"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer9->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    SecondsSetTB = new wxTextCtrl(this, ID_TEXTCTRL6, _("0"), wxDefaultPosition, wxSize(61,21), wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    SecondsSetTB->SetMaxLength(3);
    wxFont SecondsSetTBFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    SecondsSetTB->SetFont(SecondsSetTBFont);
    BoxSizer9->Add(SecondsSetTB, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT10, _("seconds."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    BoxSizer9->Add(StaticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnSetAutoSleep = new wxButton(this, ID_BUTTON12, _("Set auto sleep"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    BoxSizer9->Add(btnSetAutoSleep, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer4->Add(BoxSizer9, 0, wxALL|wxEXPAND, 0);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT11, _("Auto sleep after"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    BoxSizer10->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    SleepGetTB = new wxTextCtrl(this, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(61,21), wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    wxFont SleepGetTBFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    SleepGetTB->SetFont(SleepGetTBFont);
    BoxSizer10->Add(SleepGetTB, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticText10 = new wxStaticText(this, ID_STATICTEXT12, _("seconds."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    BoxSizer10->Add(StaticText10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnGetAutoSleep = new wxButton(this, ID_BUTTON13, _("Get auto sleep seconds"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
    BoxSizer10->Add(btnGetAutoSleep, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer4->Add(BoxSizer10, 0, wxALL|wxEXPAND, 0);
    BoxSizer6->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND, 3);
    BoxSizer2->Add(BoxSizer6, 0, wxALL|wxEXPAND, 0);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, this, _("Communication speed (between reader and cards)"));
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    StaticText11 = new wxStaticText(this, ID_STATICTEXT13, _("TX :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    BoxSizer12->Add(StaticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    TXCB = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX3"));
    TXCB->SetSelection( TXCB->Append(_("106 kbps")) );
    TXCB->Append(_("212 kbps"));
    TXCB->Append(_("424 kbps"));
    BoxSizer12->Add(TXCB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT14, _("RX :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    BoxSizer12->Add(StaticText12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    RXCB = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_COMBOBOX4"));
    RXCB->SetSelection( RXCB->Append(_("106 kbps")) );
    RXCB->Append(_("212 kbps"));
    RXCB->Append(_("424 kbps"));
    BoxSizer12->Add(RXCB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnSetSpeedPermanently = new wxButton(this, ID_BUTTON14, _("Set speed"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON14"));
    BoxSizer12->Add(btnSetSpeedPermanently, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer5->Add(BoxSizer12, 1, wxALL|wxEXPAND, 3);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    StaticText13 = new wxStaticText(this, ID_STATICTEXT15, _("TX :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    BoxSizer13->Add(StaticText13, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    TXGet = new wxTextCtrl(this, ID_TEXTCTRL8, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    wxFont TXGetFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    TXGet->SetFont(TXGetFont);
    BoxSizer13->Add(TXGet, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticText14 = new wxStaticText(this, ID_STATICTEXT16, _("RX :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    BoxSizer13->Add(StaticText14, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    RXGet = new wxTextCtrl(this, ID_TEXTCTRL9, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    wxFont RXGetFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    RXGet->SetFont(RXGetFont);
    BoxSizer13->Add(RXGet, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnGetSpeed = new wxButton(this, ID_BUTTON15, _("Get speed"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON15"));
    BoxSizer13->Add(btnGetSpeed, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer5->Add(BoxSizer13, 0, wxALL|wxEXPAND, 3);
    BoxSizer11->Add(StaticBoxSizer5, 1, wxALL|wxEXPAND, 3);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _("Reader keys"));
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    StaticText15 = new wxStaticText(this, ID_STATICTEXT17, _("Password (8 characters) :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    BoxSizer14->Add(StaticText15, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    LockPassTB = new wxTextCtrl(this, ID_TEXTCTRL10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
    LockPassTB->SetMaxLength(8);
    wxFont LockPassTBFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    LockPassTB->SetFont(LockPassTBFont);
    BoxSizer14->Add(LockPassTB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnLockKeys = new wxButton(this, ID_BUTTON16, _("Lock keys"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON16"));
    BoxSizer14->Add(btnLockKeys, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6->Add(BoxSizer14, 0, wxALL|wxEXPAND, 3);
    BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    StaticText16 = new wxStaticText(this, ID_STATICTEXT18, _("Password (8 characters) :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    BoxSizer15->Add(StaticText16, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    UnlockPassTB = new wxTextCtrl(this, ID_TEXTCTRL11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
    UnlockPassTB->SetMaxLength(8);
    wxFont UnlockPassTBFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    UnlockPassTB->SetFont(UnlockPassTBFont);
    BoxSizer15->Add(UnlockPassTB, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    btnUnlockKeys = new wxButton(this, ID_BUTTON17, _("Unlock keys"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON17"));
    BoxSizer15->Add(btnUnlockKeys, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer6->Add(BoxSizer15, 1, wxALL|wxEXPAND, 3);
    BoxSizer11->Add(StaticBoxSizer6, 1, wxALL|wxEXPAND, 3);
    BoxSizer2->Add(BoxSizer11, 1, wxALL|wxEXPAND, 0);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 0);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Reader informations"));
    InfoTB = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(418,177), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    wxFont InfoTBFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    InfoTB->SetFont(InfoTBFont);
    StaticBoxSizer2->Add(InfoTB, 1, wxALL|wxEXPAND, 3);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Status : "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    BoxSizer3->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StatusLabel = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont StatusLabelFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    StatusLabel->SetFont(StatusLabelFont);
    BoxSizer3->Add(StatusLabel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    StaticBoxSizer2->Add(BoxSizer3, 0, wxALL|wxEXPAND, 0);
    BoxSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 3);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnReaderOpenClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnReaderResetClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnReaderCloseClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnReaderSoftRestartClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnCheckConnectionClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnFactoryResetClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnReaderOpenExClick);
    Connect(ID_BUTTON18,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbEnterNewBaudRateClick);
    Connect(ID_BUTTON19,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbResetBaudRateToDefaultClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnSetSignalizationClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnTurnRedLightClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnEnterSleepModeClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnLeaveSleepModeClick);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnSetAutoSleepClick);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnGetAutoSleepClick);
    Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnSetSpeedPermanentlyClick);
    Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnGetSpeedClick);
    Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnLockKeysClick);
    Connect(ID_BUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnbtnUnlockKeysClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&uFR_Readers_toolFrame::OnAbout);
    //*)
}

uFR_Readers_toolFrame::~uFR_Readers_toolFrame()
{
    //(*Destroy(uFR_Readers_toolFrame)
    //*)
}

void uFR_Readers_toolFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void uFR_Readers_toolFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("uFR Readers Tool", _("Welcome to..."));
}

void uFR_Readers_toolFrame::OnbtnReaderOpenClick(wxCommandEvent& event)
{
    status = ReaderOpen();

    if(!status)
    {
        std::string description = GetReaderDescription();
        ReaderUISignal(1,1);
        InfoTB -> SetValue(description.substr(1));
    }
    else
    {
        InfoTB -> Clear();
    }

    setStatusColor(status);
    StatusLabel -> SetLabel("ReaderOpen() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnReaderResetClick(wxCommandEvent& event)
{
    status = ReaderReset();

    if(!status)
    {
        ReaderUISignal(1,1);
    }

    setStatusColor(status);
    StatusLabel -> SetLabel("ReaderReset() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnReaderCloseClick(wxCommandEvent& event)
{
    status = ReaderClose();

    setStatusColor(status);
    StatusLabel -> SetLabel("ReaderClose() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnReaderSoftRestartClick(wxCommandEvent& event)
{
    status = ReaderSoftRestart();

    setStatusColor(status);
    StatusLabel -> SetLabel("ReaderSoftRestart() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnCheckConnectionClick(wxCommandEvent& event)
{
    uint32_t connected;
    status = ReaderStillConnected(&connected);

    if(!status)
    {
        if(connected > 0)
        {
            wxMessageBox("Reader is connected to host");
        }
        else
        {
            wxMessageBox("Reader is not connected to host");
        }
    }

    setStatusColor(status);
    StatusLabel -> SetLabel("ReaderStillConnected() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnSetSignalizationClick(wxCommandEvent& event)
{
    uint8_t light = LightCB -> GetSelection();
    uint8_t beep = BeepCB -> GetSelection();
    status = ReaderUISignal(light, beep);

    setStatusColor(status);
    StatusLabel -> SetLabel("ReaderUISignal() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnTurnRedLightClick(wxCommandEvent& event)
{
    red_light = ~red_light;
    status = UfrRedLightControl(red_light);

    setStatusColor(status);
    StatusLabel -> SetLabel("UfrRedLightControl() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnEnterSleepModeClick(wxCommandEvent& event)
{
    status = UfrEnterSleepMode();

    setStatusColor(status);
    StatusLabel -> SetLabel("UfrEnterSleepMode() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnLeaveSleepModeClick(wxCommandEvent& event)
{
    status = UfrLeaveSleepMode();

    setStatusColor(status);
    StatusLabel -> SetLabel("UfrLeaveSleepMode() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnSetAutoSleepClick(wxCommandEvent& event)
{
    wxString wxSeconds = SecondsSetTB -> GetValue();
    wxSeconds = wxSeconds.Trim();
    uint8_t seconds = wxAtoi(wxSeconds);
    status = AutoSleepSet(seconds);

    setStatusColor(status);
    StatusLabel -> SetLabel("AutoSleepSet() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnGetAutoSleepClick(wxCommandEvent& event)
{
    uint8_t seconds = 0;
    status = AutoSleepGet(&seconds);

    if(!status)
    {
        wxString wxSeconds = "";
        wxSeconds << (int)seconds;
        SleepGetTB -> SetValue(wxSeconds);
    }
    else
    {
        SleepGetTB -> Clear();
    }

    setStatusColor(status);
    StatusLabel -> SetLabel("AutoSleepGet() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnSetSpeedPermanentlyClick(wxCommandEvent& event)
{
    uint8_t tx = TXCB -> GetSelection();
    uint8_t rx = RXCB -> GetSelection();
    status = SetSpeedPermanently(tx, rx);

    setStatusColor(status);
    StatusLabel -> SetLabel("SetSpeedPermanently() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnGetSpeedClick(wxCommandEvent& event)
{
    uint8_t tx, rx;
    std::map<int, std::string> speed;
    speed[0] = "106 kbps";
    speed[1] = "212 kbps";
    speed[2] = "424 kbps";

    status = GetSpeedParameters(&tx, &rx);

    if(!status)
    {
        TXGet -> SetValue(speed[tx]);
        RXGet -> SetValue(speed[rx]);
    }
    else
    {
        TXGet -> Clear();
        RXGet -> Clear();
    }

    setStatusColor(status);
    StatusLabel -> SetLabel("GetSpeedParameters() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnLockKeysClick(wxCommandEvent& event)
{
    wxString pass = LockPassTB -> GetValue();
    pass = pass.Trim();
    std::string passwordStr = (std::string)pass;
    uint8_t password[8];

    if(passwordStr.length() != 8)
    {
        wxMessageBox("Password must be 8 characters long");
    }
    else
    {
        ConvertStringToUint8Array(passwordStr, password);
        status = ReaderKeysLock(password);

        setStatusColor(status);
        StatusLabel -> SetLabel("ReaderKeysLock() -> " + (std::string)UFR_Status2String(status));
    }
}

void uFR_Readers_toolFrame::OnbtnUnlockKeysClick(wxCommandEvent& event)
{
    wxString pass = UnlockPassTB -> GetValue();
    pass = pass.Trim();
    std::string passwordStr = (std::string)pass;
    uint8_t password[8];

    if(passwordStr.length() != 8)
    {
        wxMessageBox("Password must be 8 characters long");
    }
    else
    {
        ConvertStringToUint8Array(passwordStr, password);
        status = ReaderKeysUnlock(password);

        setStatusColor(status);
        StatusLabel -> SetLabel("ReaderKeysUnlock() -> " + (std::string)UFR_Status2String(status));
    }
}

void uFR_Readers_toolFrame::OnbtnReaderOpenExClick(wxCommandEvent& event)
{
    wxString wxReaderType = ReaderTypeTB -> GetValue();
    wxString wxPortName = PortNameTB -> GetValue();
    wxString wxPortInterface = PortInterface -> GetValue();
    wxString wxAdditional = AdditionalTB -> GetValue();

    wxReaderType = wxReaderType.Trim();
    wxPortName = wxPortName.Trim();
    wxPortInterface = wxPortInterface.Trim();
    wxAdditional = wxAdditional.Trim();

    if(wxReaderType == "" || wxPortName == "" || wxPortInterface == "" || wxAdditional == "")
    {
        wxMessageBox("You have to fill all parameters for ReaderOpenEx");
        return;
    }

    uint32_t reader_type = wxAtoi(wxReaderType);

    c_string port_name = 0;

    if(wxPortName != "0")
    {
        port_name = wxPortName.c_str();
    }

    uint32_t port_interface;

    if(wxPortInterface == "T")
    {
        port_interface = 84;
    }
    else if(wxPortInterface == "U")
    {
        port_interface = 85;
    }
    else
    {
        port_interface = wxAtoi(wxPortInterface);
    }

    c_string additional = 0;

    if(wxAdditional != "0")
    {
       additional = wxAdditional.c_str();
    }

    status = ReaderOpenEx(reader_type, port_name, port_interface, (void *)additional);

    if(!status)
    {
        std::string description = GetReaderDescription();
        ReaderUISignal(1,1);
        InfoTB -> SetValue(description.substr(1));
    }
    else
    {
        InfoTB -> Clear();
    }

    setStatusColor(status);
    StatusLabel -> SetLabel("ReaderOpenEx() -> " + (std::string)UFR_Status2String(status));
}

void uFR_Readers_toolFrame::OnbtnFactoryResetClick(wxCommandEvent& event)
{
    InfoTB -> Clear();

    UFR_STATUS status[7];
    uint8_t userData[16];
    uint8_t key[6];
    uint8_t aes_key[16];
    memset(userData, 0, 16);
    memset(key, 255, 6);
    memset(aes_key, 0, 16);

        status[0] = UfrLeaveSleepMode();
        InfoTB -> AppendText("UfrLeaveSleepMode()  ->  " + (std::string)UFR_Status2String(status[0]) + "\n");
        Sleep(200);

        status[1] = AutoSleepSet(0);
        InfoTB -> AppendText("AutoSleepSet(0)  ->  " + (std::string)UFR_Status2String(status[1]) + "\n");
        Sleep(200);

        status[2] = TagEmulationStop();
        InfoTB -> AppendText("TagEmulationStop()  ->  " + (std::string)UFR_Status2String(status[2]) + "\n");
        Sleep(200);

        status[3] = DisableAntiCollision();
        InfoTB -> AppendText("DisableAntiCollision()  ->  " + (std::string)UFR_Status2String(status[3]) + "\n");
        Sleep(200);

        status[4] = WriteUserData(userData);
        InfoTB -> AppendText("WriteUserData()  ->  " + (std::string)UFR_Status2String(status[4]) + "\n");
        Sleep(200);

        for(uint8_t i = 0; i < 32; i++)
        {
            status[5] = ReaderKeyWrite(key, i);
            wxString wxIndex = "";
            wxIndex << (int)i;
            InfoTB -> AppendText("[Key index : " + wxIndex + ", key : 0xFFFFFFFFFFFF] ReaderKeyWrite()  ->  " + (std::string)UFR_Status2String(status[5]) + "\n");

            if(status[5])
            {
                break;
            }
            Sleep(200);
        }

        for(uint8_t i = 0; i < 16; i++)
        {
            status[6] = uFR_int_DesfireWriteAesKey(i, aes_key);
            wxString wxIndex = "";
            wxIndex << (int)i;
            InfoTB -> AppendText("[Aes key index : " + wxIndex + ", key : 0x00000000000000000000000000000000] ReaderKeyWrite()  ->  " + (std::string)UFR_Status2String(status[6]) + "\n");

            if(status[6])
            {
                break;
            }
            Sleep(200);
        }


        if(status[0] == UFR_OK && status[1] == UFR_OK && status[2] == UFR_OK && status[3] == UFR_OK && status[4] == UFR_OK && status[5] == UFR_OK && status[6] == UFR_OK)
        {
            setStatusColor(UFR_OK);
            StatusLabel -> SetLabel("FACTORY RESET -> UFR_OK");
            ReaderUISignal(4, 5);
            wxMessageBox("Reader successfully reset to factory settings");
        }
        else
        {
            setStatusColor((UFR_STATUS)1);
            StatusLabel -> SetLabel("FACTORY RESET -> FAILED");
            wxMessageBox("Unable to reset reader to factory settings. Check statuses in textbox.");
        }
}

void uFR_Readers_toolFrame::OnbEnterNewBaudRateClick(wxCommandEvent& event)
{
    uint32_t baud_rate[] = {9600, 19200, 38400, 57600, 115200, 230400, 460800, 500000, 1000000};

    uint8_t ver_major, ver_minor;
    status = GetReaderHardwareVersion(&ver_major, &ver_minor);

    if(status)
    {
        setStatusColor(status);
        StatusLabel -> SetLabel("ReaderChangeBaudrate() -> " + (std::string)UFR_Status2String(status));
        return;
    }

    uint32_t baud = NewBaudCB->GetSelection();

    status = SetUartSpeed(baud_rate[baud]);

    setStatusColor(status);
    StatusLabel -> SetLabel("SetUartSpeed() -> " + (std::string)UFR_Status2String(status));
    /*

    if(ver_minor == 24 || ver_minor == 34)
    {
        uint32_t baud = NewBaudCB->GetSelection();

        status = ReaderChangeBaudrate(baudRate[baud]);

        setStatusColor(status);
        StatusLabel -> SetLabel("ReaderChangeBaudrate() -> " + (std::string)UFR_Status2String(status));
    }
    else
    {
        wxMessageBox("Unsupported device type");
        setStatusColor((UFR_STATUS)1);
        StatusLabel -> SetLabel("ReaderChangeBaudrate() -> UNSUPPORTED DEVICE TYPE");
    }
    */
}

void uFR_Readers_toolFrame::OnbResetBaudRateToDefaultClick(wxCommandEvent& event)
{
    wxString wxCOM = COMResetBR->GetValue();
    wxCOM = wxCOM.Trim();
    c_string com_port = 0;
    if(wxCOM.c_str() != "0")
        com_port = wxCOM.c_str();

    wxString wxPortInterface = PortInterfaceResetBR->GetValue();
    wxPortInterface = wxPortInterface.Trim();
    uint32_t port_interface = wxAtoi(wxPortInterface);
    wxString wxReaderType = ReaderTypeResetBR->GetValue();
    wxReaderType = wxReaderType.Trim();
    uint32_t reader_type = wxAtoi(wxReaderType);

    if(wxCOM == "" || wxPortInterface == "")
    {
        wxMessageBox("You have to enter COM port name and port interface for setting baud rate to default value");
        return;
    }

    //status = uFR_set_default_baudrate(com_port, port_interface);
    status = SetDefaultUartSpeed(reader_type, port_interface, com_port);

    setStatusColor(status);
    StatusLabel -> SetLabel("uFR_set_default_baudrate() -> " + (std::string)UFR_Status2String(status));
}
