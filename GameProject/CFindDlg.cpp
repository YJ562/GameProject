// CFindDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GameProject.h"
#include "afxdialogex.h"
#include "CFindDlg.h"
#include "CSignUpDlg.h"

// CFindDlg 대화 상자

IMPLEMENT_DYNAMIC(CFindDlg, CDialogEx)

CFindDlg::CFindDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FindInfo, pParent)
{

}

CFindDlg::~CFindDlg()
{
}

void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	BOOL bopen = m_db.OpenEx(_T("DSN=mydb;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=0804; DATABASE=gameproject;"), CDatabase::noOdbcDialog);
	if (bopen) m_prs = new CRecordset(&m_db);

	//DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_Combo1); 
	DDX_Control(pDX, IDC_COMBO2, m_Combo2);
	DDX_Control(pDX, IDC_COMBO3, m_Combo3);

	//아이디 찾기 생일
	for (int i = 0; i <121; i++) {

		int year = 2021 - i;
		CString ylist;
		ylist.Format(L"%d", year);
		m_Combo1.InsertString(i, ylist);

	}

	for (int i = 0;i<12;i++) { // i가 1부터 시작하면 0의 인덱스값 x

		int month = i+1;
		CString mlist;
		mlist.Format(L"%d", month);
		m_Combo2.InsertString(i, mlist);

	}

	for (int i = 0; i < 31; i++) {

		int day = i+1;
		CString dlist;
		dlist.Format(L"%d", day);
		m_Combo3.InsertString(i, dlist);

	}

	//초기값 설정
	m_Combo1.SetCurSel(0);
	m_Combo2.SetCurSel(0);
	m_Combo3.SetCurSel(0); 


	//비밀번호 수정 처리
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICA2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICA3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NEWPW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_NEWPW2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_UPDATEPWERROR)->ShowWindow(SW_HIDE);
	

}


BEGIN_MESSAGE_MAP(CFindDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CFindDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_FORM, &CFindDlg::OnBnClickedForm)
	ON_BN_CLICKED(IDC_BUTTON2, &CFindDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFindDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CFindDlg 메시지 처리기


void CFindDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString name=_T("");
	CString phone1 = _T("");
	CString phone2 = _T("");
	CString phone3 = _T("");
	CString birthday = _T("");

	GetDlgItemText(IDC_EDIT1, name);
	GetDlgItemText(IDC_EDIT2, phone1);
	GetDlgItemText(IDC_EDIT3, phone2);
	GetDlgItemText(IDC_EDIT4, phone3);

	CString phone = phone1 +"-" + phone2 + "-" + phone3;

	CString year;
	m_Combo1.GetLBText(m_Combo1.GetCurSel(), year);

	CString month;
	m_Combo2.GetLBText(m_Combo2.GetCurSel(), month);

	CString day;
	m_Combo3.GetLBText(m_Combo3.GetCurSel(), day);
	
	birthday=year + "-" + month + "-" + day;

	//CString Test;
	//Test.Format(L"이름: %s, 휴대폰 번호: %s,  생일: %s", name, phone, birthday);
	//MessageBox(Test);

	FindAccountExisted(name, birthday, phone);

}

void CFindDlg::FindAccountExisted(CString name, CString birthday, CString phone) {

	CString query_str; //DB 쿼리문	
	CString m_idfound = _T("");

	query_str.Format(L"select ID from member where NAME = \'%s\' && BIRTHDAY = \'%s\' && PHONE = \'%s\' ;", name, birthday, phone);
	
	BOOL bopen = m_prs->Open(CRecordset::snapshot, query_str);

	{
		int row = 1;
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
				CString str;
				for (int col = 0; col < 1; col++) {
					m_prs->SetAbsolutePosition(row);
					m_prs->GetFieldValue(col, str);
					m_idfound = m_idfound + str;
					
				}
				m_idfound += "\n";
				row++;
			}
		}
		//AfxMessageBox(m_CompareID); 
		m_prs->Close();
	}

	CString message;
	if (m_idfound.IsEmpty() != TRUE) {
		message.Format(L"찾을 수 있는 아이디는 \n\n%s\n입니다.", m_idfound);
	}
	else message.Format(L"찾을 수 있는 아이디가 없습니다.");
	
	MessageBox(message);
}

void CFindDlg::OnBnClickedForm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFindDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString id;
	GetDlgItemText(IDC_EDIT5, id);

	CString phone, p1, p2, p3;
	GetDlgItemText(IDC_EDIT8, p1);
	GetDlgItemText(IDC_EDIT6, p2);
	GetDlgItemText(IDC_EDIT7, p3);

	phone.Format(p1+"-"+ p2+"-"+ p3);

	CString query_str; //DB 쿼리문	
	CString phone_Selected= _T("");

	query_str.Format(L"select PHONE from member where ID = \'%s\' ;", id);

	BOOL bopen = m_prs->Open(CRecordset::snapshot, query_str);

	{
		int row = 1;
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {

				for (int col = 0; col < 1; col++) {
					m_prs->SetAbsolutePosition(row);
					m_prs->GetFieldValue(col, phone_Selected);
				}
			}
		}
		//AfxMessageBox(m_CompareID); 
		m_prs->Close();
	}

	if (phone_Selected.Compare(phone) == 0) { //아이디 통해 찾은 휴대번호와 입력된 휴대번호가 같을 때

		ShowUpdatePW();
		m_ID_founded.Format(id);
		// MessageBox(m_ID_founded); //테스트
	}
	else MessageBox(L"정보를 다시 입력해주세요");
}


void CFindDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString newPW, checkPW;
	CString message;
	CString query_str;

	GetDlgItemText(IDC_NEWPW, newPW);
	GetDlgItemText(IDC_NEWPW2, checkPW);
	
	if (newPW.Compare(checkPW) == 0) { //비밀번호 서로 일치하면 비밀번호 업데이트

		//MessageBox(m_ID_founded);
		
		UpdatePW(checkPW,m_ID_founded);
		message.Format(L"비밀번호 수정이 완료되었습니다.\n\n비밀번호는 %s 입니다", checkPW);
		MessageBox(message);
		
		OnOK();
		OnOK();
} 

		else{
		GetDlgItem(IDC_UPDATEPWERROR)->ShowWindow(SW_SHOW);
	}

}

void CFindDlg::ShowUpdatePW() {
	GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICA)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICA2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATICA3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NEWPW)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NEWPW2)->ShowWindow(SW_SHOW);

}



void CFindDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnOK();
}

void CFindDlg::UpdatePW(CString newPW, CString m_ID_founded) {
	
	CString query_str;

	m_db.BeginTrans();
	try {
		query_str.Format(L"UPDATE member SET PW = \'%s\' where ID = \'%s\';", newPW, m_ID_founded);
		m_db.ExecuteSQL(query_str);
	}
	catch (CException* e) {
		e->ReportError();
	}
	m_db.CommitTrans();

}