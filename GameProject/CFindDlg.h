#pragma once
#include "afxdialogex.h"
#include <afxdb.h>
#include "CSignUpDlg.h"

// CFindDlg 대화 상자

class CFindDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindDlg)

public:
	CFindDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFindDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FindInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	//CEdit m_edit;
	CComboBox m_Combo1;
	CComboBox m_Combo2;
	CComboBox m_Combo3;

	CDatabase m_db; //데이터 베이스 연동
	CRecordset* m_prs;
	void FindAccountExisted(CString name, CString birthday, CString phone);
	afx_msg void OnBnClickedForm();
	afx_msg void OnBnClickedButton2();
	
	void ShowUpdatePW();
	afx_msg void OnBnClickedButton3();

	CString m_ID_founded;
	virtual void OnOK();
	void UpdatePW(CString newPW, CString m_ID_founded);
};
