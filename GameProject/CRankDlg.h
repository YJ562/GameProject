#pragma once
#include "afxdialogex.h"


// CRankDlg 대화 상자

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRankDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CDatabase m_db; //데이터 베이스 연동
	CRecordset* m_prs;

	int m_SelectRecord;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio3();
	void selectRecord(CString query);
	CListCtrl m_list1;
	CListCtrl m_list2;
	CComboBox m_selectLevel;
	void selectQuery(int level);
	void showMyRecord1();
	void showMyRecord2();
	int m_selectList=0;
	CDateTimeCtrl m_start;
	CDateTimeCtrl m_end;
	CString st, ed;
};
