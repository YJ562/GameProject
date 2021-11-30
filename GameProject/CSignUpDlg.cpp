// CSignUpDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GameProject.h"
#include "afxdialogex.h"
#include "CSignUpDlg.h"

#include <afxdb.h>
#include <atlstr.h>

// CSignUpDlg 대화 상자

IMPLEMENT_DYNAMIC(CSignUpDlg, CDialogEx)

CSignUpDlg::CSignUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SignUP, pParent)
	, m_SGender(0)
{
	
}

CSignUpDlg::~CSignUpDlg()
{
}

void CSignUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_SGender);
	
	BOOL bopen = m_db.OpenEx(_T("DSN=mydb;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=0804; DATABASE=gameproject;"), CDatabase::noOdbcDialog);
	if (bopen) m_prs = new CRecordset(&m_db);

	GetDlgItem(IDC_PWError)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IDError)->ShowWindow(SW_HIDE);

	DDX_Control(pDX, IDC_BIRTHDAY, m_datetime_date);
}


BEGIN_MESSAGE_MAP(CSignUpDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSignUpDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CSignUpDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSignUpDlg::OnBnClickedRadio2)

END_MESSAGE_MAP()


// CSignUpDlg 메시지 처리기


void CSignUpDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//입력 받을 정보
	CString Signup_ID = _T("");
	CString Signup_PW = _T("");
	CString Signup_PW2 = _T(""); //아이디 확인
	CString Signup_NICKNAME = _T("");
	CString Signup_NAME = _T("");
	CString Signup_GENDER = _T("");
	CString Signup_BIRTHDAY = _T("");
	CString Signup_PHONE = _T("");

	CString Signup_PHONE_NUM1 = _T("");
	CString Signup_PHONE_NUM2 = _T("");
	CString Signup_PHONE_NUM3 = _T("");


	
	//회원가입 다이얼로그에서 입력을 받아옴.
	GetDlgItemText(IDC_SID, Signup_ID);
	GetDlgItemText(IDC_SPW, Signup_PW);
	GetDlgItemText(IDC_PCHECK, Signup_PW2);
	GetDlgItemText(IDC_NICKNAME, Signup_NICKNAME);
	GetDlgItemText(IDC_NAME, Signup_NAME);
	GetDlgItemText(IDC_PHONE1, Signup_PHONE_NUM1);
	GetDlgItemText(IDC_PHONE2, Signup_PHONE_NUM2);
	GetDlgItemText(IDC_PHONE3, Signup_PHONE_NUM3);
	
	UpdateData(true);

	switch (m_SGender) {
	case 0:
		Signup_GENDER.Format(L"남성");
		break;
	case 1:
		Signup_GENDER.Format(L"여성");
	}
	

	CTime date;
	m_datetime_date.GetTime(date);
	Signup_BIRTHDAY = date.Format("%Y-%m-%d");
	
	Signup_PHONE = Signup_PHONE_NUM1 +"-" + Signup_PHONE_NUM2  +"-"+ Signup_PHONE_NUM3;

	//입력 확인 테스트
	//CString test =  Signup_ID + "\n" + Signup_PW + "\n" + Signup_PW2 + "\n" + Signup_NICKNAME + "\n" + Signup_NAME +"\n"+ Signup_GENDER;
	//MessageBox(test);

	if (Signup_ID.IsEmpty() != TRUE && Signup_PW.IsEmpty() != TRUE && Signup_PW2.IsEmpty() != TRUE && Signup_PHONE.IsEmpty() != TRUE && Signup_NICKNAME.IsEmpty() != TRUE && Signup_NAME.IsEmpty() != TRUE) {

		if (CheckDuplicatedID(Signup_ID) != 1) {

			if (Signup_PW.Compare(Signup_PW2) == 0) { //문자열 일치할 때, compare 함수가 0을 반환

				InsertData(Signup_ID, Signup_PW, Signup_NICKNAME, Signup_NAME, Signup_GENDER, Signup_BIRTHDAY, Signup_PHONE, 1);

				/*
				CString query_str;

				m_db.BeginTrans();
				try {

					query_str.Format(L"INSERT INTO member(ID,PW,NICKNAME,NAME,GENDER,BIRTHDAY,PHONE,EXIST) VALUES(\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%d\')",
						Signup_ID, Signup_PW, Signup_NICKNAME, Signup_NAME, Signup_GENDER, Signup_BIRTHDAY, Signup_PHONE,1);
					m_db.ExecuteSQL(query_str);
				}
				catch (CException* e) {
					e->ReportError();
				}

				m_db.CommitTrans();*/

				MessageBox(_T("회원 가입이 완료되었습니다."));
				GetDlgItem(IDC_PWError)->ShowWindow(SW_HIDE);

				OnOK(); //모달 종료

			}
			else {
				MessageBox(_T("비밀번호 확인해주세요."));
				GetDlgItem(IDC_PWError)->ShowWindow(SW_SHOW);
			}
		}
		else {
			MessageBox(_T("중복된 아이디 입니다."));
			GetDlgItem(IDC_IDError)->ShowWindow(SW_SHOW);
		}
	}
	else MessageBox(_T("빈 곳을 입력해주세요."));
	
	CDialogEx::OnOK();
}


void CSignUpDlg::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_SGender=0;
	UpdateData(false);

}


void CSignUpDlg::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_SGender = 1;
	UpdateData(false);
}



//DB에 데이터를 삽입 함수
void  CSignUpDlg::InsertData(CString Signup_ID, CString Signup_PW, CString Signup_NICKNAME, CString Signup_NAME, CString Signup_GENDER, CString Signup_BRITHDAY, CString Signup_PHONE, int exist){
	
	// 쿼리문
	CString query_str;

			m_db.BeginTrans();
			//try {

				query_str.Format(L"INSERT INTO member(ID,PW,NICKNAME,NAME,GENDER,BIRTHDAY,PHONE,EXIST) VALUES(\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%d\')",
					Signup_ID, Signup_PW, Signup_NICKNAME, Signup_NAME, Signup_GENDER, Signup_BRITHDAY, Signup_PHONE,1);
				m_db.ExecuteSQL(query_str);
		//	}
		//	catch (CException* e) {
		//		e->ReportError();
		//	}

			m_db.CommitTrans();

}

int  CSignUpDlg::CheckDuplicatedID(CString Enter_ID) {
	CString query_str; //DB 쿼리문	
	CString m_Exist;

	query_str.Format(L"select EXIST from member where ID = \'%s\';", Enter_ID);


	BOOL bopen = m_prs->Open(CRecordset::snapshot, query_str);

	{
		int row = 1;
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {

				for (int col = 0; col < 1; col++) {
					m_prs->SetAbsolutePosition(row);
					m_prs->GetFieldValue(col, m_Exist);
				}
			}
		}
		//AfxMessageBox(m_CompareID); 
		m_prs->Close();
	}

	if (m_Exist.Compare(L"1") == 0) return 1;
	else return 0;
}

void CSignUpDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnOK();
}
