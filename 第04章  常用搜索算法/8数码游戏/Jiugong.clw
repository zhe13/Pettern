; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CJiugongDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Jiugong.h"

ClassCount=6
Class1=CJiugongApp
Class2=CJiugongDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_INPUT
Class4=CDialogInput
Resource4=IDD_DIALOG_WAIT
Class5=CDlgWait
Resource5=IDD_JIUGONG_DIALOG
Class6=CDlgDepth
Resource6=IDD_DIALOG_DEPTH

[CLS:CJiugongApp]
Type=0
HeaderFile=Jiugong.h
ImplementationFile=Jiugong.cpp
Filter=N

[CLS:CJiugongDlg]
Type=0
HeaderFile=JiugongDlg.h
ImplementationFile=JiugongDlg.cpp
Filter=D
LastObject=CJiugongDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=JiugongDlg.h
ImplementationFile=JiugongDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[DLG:IDD_JIUGONG_DIALOG]
Type=1
Class=CJiugongDlg
ControlCount=28
Control1=IDC_PIC_INIT,static,1342177284
Control2=IDC_PIC_OBJ,static,1342177284
Control3=IDC_PIC_PROCESS,static,1342177284
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_RADIO_MAN,button,1342177289
Control8=IDC_RADIO_MAC,button,1342177289
Control9=IDC_STATIC,button,1342177287
Control10=IDC_BUTTON_UP,button,1342242816
Control11=IDC_BUTTON_LEFT,button,1342242816
Control12=IDC_BUTTON_RIGHT,button,1342242816
Control13=IDC_BUTTON_DOWN,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_BUTTON_SEARCH,button,1342242816
Control16=IDC_BUTTON_SHOW,button,1342242816
Control17=IDC_BUTTON_INPUT_INIT,button,1342242816
Control18=IDC_BUTTON_INPUT_OBJ,button,1342242816
Control19=IDC_EDIT_STATE,edit,1350633600
Control20=IDC_STATIC,static,1342308352
Control21=IDC_BUTTON_AUTO,button,1342242816
Control22=IDC_BUTTON_DEPTH,button,1342242816
Control23=IDC_STATIC,button,1342177287
Control24=IDC_BUTTON_HUIFU,button,1342242816
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_INPUT]
Type=1
Class=CDialogInput
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_EDIT5,edit,1350631552
Control8=IDC_EDIT6,edit,1350631552
Control9=IDC_EDIT7,edit,1350631552
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_EDIT9,edit,1350631552

[CLS:CDialogInput]
Type=0
HeaderFile=DialogInput.h
ImplementationFile=DialogInput.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_DIALOG_WAIT]
Type=1
Class=CDlgWait
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CDlgWait]
Type=0
HeaderFile=DlgWait.h
ImplementationFile=DlgWait.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgWait

[DLG:IDD_DIALOG_DEPTH]
Type=1
Class=CDlgDepth
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CDlgDepth]
Type=0
HeaderFile=DlgDepth.h
ImplementationFile=DlgDepth.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgDepth

