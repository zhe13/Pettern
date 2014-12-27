; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBwView
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "bw.h"
LastPage=0

ClassCount=5
Class1=CBwApp
Class2=CBwDoc
Class3=CBwView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CBwApp]
Type=0
HeaderFile=bw.h
ImplementationFile=bw.cpp
Filter=N

[CLS:CBwDoc]
Type=0
HeaderFile=bwDoc.h
ImplementationFile=bwDoc.cpp
Filter=N

[CLS:CBwView]
Type=0
HeaderFile=bwView.h
ImplementationFile=bwView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_THREE


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_ONE
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=bw.cpp
ImplementationFile=bw.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_BLACK
Command2=ID_WHITE
Command3=ID_REG
Command4=ID_APP_EXIT
Command5=ID_ONE
Command6=ID_TWO
Command7=ID_THREE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_BLACK
Command2=ID_WHITE
Command3=ID_REG
Command4=ID_ONE
Command5=ID_TWO
Command6=ID_THREE
Command7=ID_APP_ABOUT
CommandCount=7

