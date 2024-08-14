
// MFCImageDlg.h: 헤더 파일
//

#pragma once


// CMFCImageDlg 대화 상자
class CMFCImageDlg : public CDialogEx
{
private:
	CImage m_image;
	BOOL validimgPos(int x, int y);
// 생성입니다.
public:
	CMFCImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnImage();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	void UpdateDisplay();
	void moveRect();
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	afx_msg void OnBnClickedBtnActtion();
	int m_nX1;
	int m_nY1;
	int m_nX2;
	int m_nY2;
	int m_nRadius;
	int CMFCImageDlg::GetRadius();
	void CMFCImageDlg::drawCenterX(int nCenterX, int nCenterY);
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedCancel();
};
