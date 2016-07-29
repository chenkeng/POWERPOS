/******************************************************/
/* InputBox.cpp */
/******************************************************/
#include <windows.h>

int WINAPI WndProc(HWND hWnd,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam);
BOOL _InitVar();
HWND _CreateWindow(HINSTANCE hInst);
int _Run(HWND hWnd);

HINSTANCE _hInstance=NULL;
char *_lpWndMsg="";
char *_lpWndTitle="";
char *_lpDefValue="";
int _xPos=0;
int _yPos=0;
char *_lpHelpFile="";
int _nHelpIndex=0;
HWND _hParent=NULL;
HWND _hDesktop=NULL;
HWND _hEdit=NULL, _hBtnOk=NULL, _hBtnCancel=NULL, _hBtnHelp=NULL;
HWND _hMsgText=NULL;
RECT _st_rcDesktop;
RECT _st_rcWnd;
HFONT _hWndFont=NULL;
char _szBuffer[256]={0};
char *_lpWndFontName = "����";
UINT _nMaxLine = 255;
UINT _nEditStyle = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL;



BOOL _InitInputBox(HWND hParent)
{
	if (!hParent) return FALSE;
	_hParent = hParent;
	if (!_hInstance) return _InitVar();
	return TRUE;
}

BOOL _InitVar()
{
	_hInstance = ::GetModuleHandle(NULL);
	_hDesktop = ::GetDesktopWindow();
	::GetWindowRect(_hDesktop,&_st_rcDesktop);
	if (!_xPos) _xPos = (_st_rcDesktop.right - 365) / 2;
	if (!_yPos)	_yPos = (_st_rcDesktop.bottom - 130) / 2;
	return TRUE;
}

int WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
HDC hWndDc;
WORD uBtnID;
	switch(uMsg) {
	case WM_DESTROY:
		if (_hWndFont) ::DeleteObject(_hWndFont);
		::PostQuitMessage(0);
		_hInstance=NULL;
		break;
	case WM_CREATE:
		_hMsgText = ::CreateWindowEx(0,"Static",_lpWndMsg,WS_CHILD | WS_VISIBLE,
						5,5,275,70,hWnd,(HMENU)1000,_hInstance,0);
		_hBtnOk = ::CreateWindowEx(0,"Button","ȷ��(&K)",WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
						285,5,65,20,hWnd,(HMENU)IDOK,_hInstance,0);
		_hBtnCancel = ::CreateWindowEx(0,"Button","ȡ��(&C)",WS_CHILD | WS_VISIBLE,
						285,30,65,20,hWnd,(HMENU)IDCANCEL,_hInstance,0);
		_hBtnHelp = ::CreateWindowEx(0,"Button","����(&H)",WS_CHILD | WS_VISIBLE,
						285,55,65,20,hWnd,(HMENU)IDHELP,_hInstance,0);
		_hEdit = ::CreateWindowEx(WS_EX_CLIENTEDGE,"Edit",_lpDefValue,_nEditStyle,
						5,80,350,20,hWnd,(HMENU)2000,_hInstance,0);
		::SendMessage(_hEdit,EM_SETLIMITTEXT,_nMaxLine,0);
		_hWndFont = ::CreateFont(12,6,0,0,12,0,0,0,GB2312_CHARSET,OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_lpWndFontName);
		if (!::lstrlen(_lpHelpFile)) ShowWindow(_hBtnHelp,SW_HIDE);
		hWndDc = ::GetDC(hWnd);
		::SelectObject(hWndDc,_hWndFont);
		::ReleaseDC(hWnd,hWndDc);
		::SendDlgItemMessage(hWnd,1000,WM_SETFONT,(WPARAM)_hWndFont,0);
		::SendDlgItemMessage(hWnd,2000,WM_SETFONT,(WPARAM)_hWndFont,0);
		::SendDlgItemMessage(hWnd,IDOK,WM_SETFONT,(WPARAM)_hWndFont,0);
		::SendDlgItemMessage(hWnd,IDCANCEL,WM_SETFONT,(WPARAM)_hWndFont,0);
		::SendDlgItemMessage(hWnd,IDHELP,WM_SETFONT,(WPARAM)_hWndFont,0);
		break;
	//case WM_KEYDOWN:
	case WM_CHAR:
		if (wParam == 0xd) ::SendMessage(hWnd,WM_COMMAND,IDOK,0);
		else if (wParam == 0x1b) ::SendMessage(hWnd,WM_COMMAND,IDCANCEL,0);
		break;
	case WM_SETFOCUS:
		::SetFocus(_hEdit);
		break;
	case WM_COMMAND:
		uBtnID = LOWORD(wParam);
		switch(uBtnID) {
		case IDOK:
			::GetDlgItemText(hWnd,2000,_szBuffer,256);
			::DestroyWindow(hWnd);
			break;
		case IDCANCEL:
			::DestroyWindow(hWnd);
			break;
		case IDHELP:
			::WinHelp(hWnd,_lpHelpFile,HELP_INDEX,_nHelpIndex);
			break;
		};
		break;
	default:
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return (TRUE);
}

HWND _CreateWindow(HINSTANCE hInst)
{
	WNDCLASSEX st_WndClass;
	HWND hWnd;
	::RtlZeroMemory(&st_WndClass,sizeof(st_WndClass));
	st_WndClass.cbSize = sizeof(st_WndClass);
	st_WndClass.hInstance = hInst;
	st_WndClass.hbrBackground = (HBRUSH)COLOR_BTNSHADOW;
	st_WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	st_WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	st_WndClass.hIconSm = st_WndClass.hIcon;
	st_WndClass.lpfnWndProc = (WNDPROC)&WndProc;
	st_WndClass.lpszClassName = "InputBox_Class";
	st_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	::RegisterClassEx(&st_WndClass);
//	hWnd = ::CreateWindowEx(0,"InputBox_Class",_lpWndTitle,WS_DLGFRAME | WS_SYSMENU | WS_VISIBLE,
	hWnd = ::CreateWindowEx(WS_EX_TOOLWINDOW,"InputBox_Class",_lpWndTitle,WS_POPUPWINDOW | WS_CAPTION | WS_TABSTOP,
				_xPos,_yPos,365,130,_hParent,0,hInst,0);
	return hWnd;
}

int _Run(HWND hWnd)
{
	MSG st_Msg;
	if (!hWnd) return 0;
	::ShowWindow(hWnd,SW_SHOW);
	::UpdateWindow(hWnd);
	while(::GetMessage(&st_Msg,0,0,0))
	{
/*		if (st_Msg.message == WM_KEYDOWN)
		{
			if (st_Msg.wParam == VK_RETURN||st_Msg.wParam == VK_ESCAPE)
				::SendMessage(hWnd,st_Msg.message,st_Msg.wParam,st_Msg.wParam);
		}
*/		if (st_Msg.message == WM_CHAR)
		{
			if (st_Msg.wParam == 0xd||st_Msg.wParam == 0x1b)
				::SendMessage(hWnd,st_Msg.message,st_Msg.wParam,st_Msg.wParam);
		}
		::TranslateMessage (&st_Msg) ;
		::DispatchMessage (&st_Msg) ;
	}
	return st_Msg.wParam;
}

char *_InputBox(char *lpWndMsg,
				char *lpWndTitle,
				char *lpDefValue,
				int xPos,
				int yPos,
				char *lpHelpFile,
				int nHelpIndex)
{
	_lpWndMsg = lpWndMsg;
	_lpWndTitle = lpWndTitle;
	_lpDefValue = lpDefValue;
	_xPos = xPos;
	_yPos = yPos;
	_lpHelpFile = lpHelpFile;
	_nHelpIndex = nHelpIndex;
	_szBuffer[0]=0;
	if (!_hInstance) _InitVar();
	_Run(_CreateWindow(_hInstance));
	return _szBuffer;
}

void _SetNumber(BOOL fIsNumber)
{
	if (fIsNumber) _nEditStyle |= ES_NUMBER;
}
void _SetLowerCase(BOOL fIsLowerCase)
{
	if (fIsLowerCase) _nEditStyle |= ES_LOWERCASE;
}
void _SetUpperCase(BOOL fIsUpperCase)
{
	if (fIsUpperCase) _nEditStyle |= ES_UPPERCASE;
}
void _SetMaxLine(unsigned int nLineSize)
{
	if (nLineSize)
		if (nLineSize < _nMaxLine) _nMaxLine = nLineSize;
}
