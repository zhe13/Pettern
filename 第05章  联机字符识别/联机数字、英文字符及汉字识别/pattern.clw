; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPatternDlg
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pattern.h"

ClassCount=6
Class1=CPatternApp
Class2=CPatternDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PATTERN_DIALOG
Resource4=IDD_PATTERN_DIALOG (English (U.S.))
Class4=CPatternView
Resource5=IDD_ABOUTBOX (English (U.S.))
Class5=Inputdialog
Class6=Store
Resource6=IDD_DIALOG1
Resource7=IDR_MENU1

[CLS:CPatternApp]
Type=0
HeaderFile=pattern.h
ImplementationFile=pattern.cpp
Filter=N

[CLS:CPatternDlg]
Type=0
HeaderFile=patternDlg.h
ImplementationFile=patternDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_OPEN_MENU

[CLS:CAboutDlg]
Type=0
HeaderFile=patternDlg.h
ImplementationFile=patternDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_PATTERN_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CPatternDlg

[DLG:IDD_PATTERN_DIALOG (English (U.S.))]
Type=1
Class=CPatternDlg
ControlCount=10
Control1=IDC_EDIT1,edit,1353781444
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_BUTTON4,button,1342242816
Control6=IDC_EDIT2,edit,1219563716
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CPatternView]
Type=0
HeaderFile=PatternView.h
ImplementationFile=PatternView.cpp
BaseClass=CView
Filter=C

[DLG:IDD_DIALOG1]
Type=1
Class=Inputdialog
ControlCount=6
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:Inputdialog]
Type=0
HeaderFile=Inputdialog.h
ImplementationFile=Inputdialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:Store]
Type=0
HeaderFile=Store.h
ImplementationFile=Store.cpp
BaseClass=CEdit
Filter=W
LastObject=ID_ABOUT_MENU

[MNU:IDR_MENU1]
Type=1
Class=CPatternDlg
Command1=ID_OPEN_MENU
Command2=ID_SAVE_MENU
Command3=ID_EXIT_MENU
Command4=ID_ABOUT_MENU
CommandCount=4

