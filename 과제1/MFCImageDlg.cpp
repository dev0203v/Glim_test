
// MFCImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCImage.h"
#include "MFCImageDlg.h"
#include "afxdialogex.h"
#include <ctime>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCImageDlg 대화 상자



CMFCImageDlg::CMFCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCIMAGE_DIALOG, pParent)
	, m_nX1(0)
	, m_nY1(0)
	, m_nX2(0)
	, m_nY2(0)
	, m_nRadius(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_nX1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_nY1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nX2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_nY2);

	DDV_MinMaxInt(pDX, m_nX1, 0, 650);
	DDV_MinMaxInt(pDX, m_nY1, 0, 450);
	DDV_MinMaxInt(pDX, m_nX2, 0, 700);
	DDV_MinMaxInt(pDX, m_nY2, 0, 500);
}

BEGIN_MESSAGE_MAP(CMFCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CMFCImageDlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMFCImageDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMFCImageDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACTTION, &CMFCImageDlg::OnBnClickedBtnActtion)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCImageDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCImageDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDCANCEL, &CMFCImageDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCImageDlg 메시지 처리기

BOOL CMFCImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCImageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCImageDlg::OnBnClickedBtnImage()
{
	int nWidth = 800;
	int nHeight = 600;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	

	UpdateDisplay();

}

CString g_strFileImage = _T("c:\\Users\\lms\\Desktop\\images\\save.bmp");

void CMFCImageDlg::OnBnClickedBtnSave()
{
	m_image.Save(g_strFileImage);
}


void CMFCImageDlg::OnBnClickedBtnLoad()
{
	if (m_image != NULL)
	{
		m_image.Destroy();
	}
	m_image.Load(g_strFileImage);

	UpdateDisplay();

}

void CMFCImageDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}



void CMFCImageDlg::OnBnClickedBtnActtion()
{
	for (int i = 0; i < 400; i++) {
		moveRect();
		/*Sleep(10);*/
	}
}

BOOL CMFCImageDlg::validimgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}


void CMFCImageDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	for (int j = y; j < nCenterY * 2; j++)
	{
		for (int i = x; i < nCenterX * 2; i++)
		{
			if (i >= 0 && i < nWidth && j >= 0 && j < nHeight)
			{
				if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
					fm[j * nPitch + i] = nGray;
			}
		}
	}

}
void CMFCImageDlg::moveRect()
{
	static int nSttX = m_nX1;
	static int nSttY = m_nY1;
	int nGray = 80;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nRadius = GetRadius();


	// 종료 좌표에 도달했을 때 더 이상 이동하지 않도록함
	if (nSttX == m_nX2 && nSttY == m_nY2) {
		return;
	}

	// x 좌표가 종료 지점보다 작은 경우 이동
	if (nSttX < m_nX2) {
		nSttX++;
	}
	else if (nSttX > m_nX2) { // x 좌표가 종료 지점보다 큰 경우 반대 방향으로 이동
		nSttX--;
	}

	// y 좌표가 종료 지점보다 작은 경우 이동
	if (nSttY < m_nY2) {
		nSttY++;
	}
	else if (nSttY > m_nY2) { // y 좌표가 종료 지점보다 큰 경우 반대 방향으로 이동
		nSttY--;
	}

	memset(fm, 0, nWidth * nHeight);
	drawCircle(fm, nSttX, nSttY, nRadius, nGray);

	CString strXY;
	strXY.Format(_T("(%d, %d)"), nSttX, nSttY);
	SetDlgItemText(IDC_STATIC_XY, strXY);

	CString strRadius;
	strXY.Format(_T("(%d)"), nRadius);
	SetDlgItemText(IDC_STATIC_RADIUS, strXY);

	UpdateDisplay();

	CString strFile;
	strFile.Format(_T("C:\\Users\\USER\\MFCImage\\image\\circle %d,%d,%d.jpg"), nSttX, nSttY, nRadius);
	m_image.Save(strFile);

}

bool CMFCImageDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius)
	{
		bRet = true;
	}

	return bRet;
}

void CMFCImageDlg::OnBnClickedBtnDraw()
{
	srand(time(NULL));
	UpdateData(TRUE);
	static int nSttX = m_nX1;
	static int nSttY = m_nY1;
	int nGray = 80;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	m_nRadius = rand() % 40 + 10;
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0, nWidth * nHeight);

	drawCircle(fm, nSttX, nSttY, m_nRadius, nGray);
	UpdateData(FALSE);

	CString strResult;
	strResult.Format(_T("(%d, %d)"), nSttX, nSttY);
	SetDlgItemText(IDC_STATIC_XY, strResult);

	CString strRadiusValue;
	strRadiusValue.Format(_T("(%d)"), m_nRadius);
	SetDlgItemText(IDC_STATIC_RADIUS, strRadiusValue);

	UpdateDisplay();
}

int CMFCImageDlg::GetRadius() {
	return m_nRadius;
}

void CMFCImageDlg::OnBnClickedButtonOpen()
{

	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	CString sPath = _T("C:\\Users\\USER\\MFCImage\\image/");

	dlg.m_ofn.lpstrInitialDir = sPath;
	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		if (m_image != NULL)
		{
			m_image.Destroy();
		}
		m_image.Load(strPathName);
		unsigned char* fm = (unsigned char*)m_image.GetBits();
		UpdateDisplay();

		CString temp;
		int retval = 0;

		retval = strPathName.Find(' ');
		temp = strPathName.Mid(retval + 1);
		temp = temp.Left(temp.Find('.'));

		CString strX, strY, strRadius;

		AfxExtractSubString(strX, temp, 0, ',');
		AfxExtractSubString(strY, temp, 1, ',');
		AfxExtractSubString(strRadius, temp, 2, ',');


		CString strResult;
		strResult.Format(_T("(%s, %s)"), strX, strY);
		SetDlgItemText(IDC_STATIC_XY, strResult);

		CString strRadiusValue;
		strRadiusValue.Format(_T("(%s)"), strRadius);
		SetDlgItemText(IDC_STATIC_RADIUS, strRadiusValue);

		int nRadius = _ttoi(strRadius);
		int nCenterX = _ttoi(strX) + nRadius;
		int nCenterY = _ttoi(strY) + nRadius;

		drawCenterX(nCenterX, nCenterY);


	}
}
void CMFCImageDlg::drawCenterX(int nCenterX, int nCenterY)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID, 2, RGB(255, 255, 255));
	CPen* pOldPen = dc.SelectObject(&pen);

	dc.MoveTo(nCenterX - 4, nCenterY - 4);
	dc.LineTo(nCenterX + 4, nCenterY + 4);

	dc.MoveTo(nCenterX + 4, nCenterY - 4);
	dc.LineTo(nCenterX - 4, nCenterY + 4);

	dc.SelectObject(pOldPen); 
}

void CMFCImageDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
