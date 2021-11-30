
// GameProjectView.cpp: CGameProjectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GameProject.h"
#endif

#include "GameProjectDoc.h"
#include "GameProjectView.h"
#include "CSignupDlg.h"
#include  "CPlayFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameProjectView

IMPLEMENT_DYNCREATE(CGameProjectView, CFormView)

BEGIN_MESSAGE_MAP(CGameProjectView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_SignUp, &CGameProjectView::OnBnClickedSignup)
	ON_BN_CLICKED(IDC_btn_Login, &CGameProjectView::OnBnClickedbtnLogin)
	ON_BN_CLICKED(IDC_FindInfo, &CGameProjectView::OnBnClickedFindinfo)
END_MESSAGE_MAP()

// CGameProjectView 생성/소멸

CGameProjectView::CGameProjectView() noexcept
	: CFormView(IDD_GAMEPROJECT_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BOOL bopen = m_db.OpenEx(_T("DSN=mydb; SERVER=127.0.0.1; PORT=3306; UID=anni20; PWD=0804; DATABASE=gameproject ;"), CDatabase::noOdbcDialog);
	if (bopen) m_prs = new CRecordset(&m_db);

}

CGameProjectView::~CGameProjectView()
{
}

void CGameProjectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CGameProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CGameProjectView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	//GetDlgItem(IDC_FindInfo)->EnableWindow(FALSE); // 아이디/비밀번호 찾기 비활성화

	// 화면 전환
	CRect rc;
	GetClientRect(&rc);
	//rc.left += 100;

	CCreateContext cc;

	CView* pView = (CView*)RUNTIME_CLASS(CPlayFormView)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD, rc, this, IDD_Play, &cc);
	pView->OnInitialUpdate();
	m_PlayView = pView;

}


// CGameProjectView 인쇄

BOOL CGameProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGameProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGameProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CGameProjectView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CGameProjectView 진단

#ifdef _DEBUG
void CGameProjectView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGameProjectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGameProjectDoc* CGameProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameProjectDoc)));
	return (CGameProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameProjectView 메시지 처리기


void CGameProjectView::OnBnClickedSignup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSignUpDlg SignUp_Screen; 
	int iRes = SignUp_Screen.DoModal(); // 회원 가입창 모달
	//SignUp_Screen.EndDialog(IDOK);
}


void CGameProjectView::OnBnClickedbtnLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//아이디, 비밀번호 입력
	CString m_Login_ID = _T("");
	CString m_Login_PW = _T("");
	
	
	GetDlgItemText(IDC_ID, m_Login_ID);
	GetDlgItemText(IDC_Password, m_Login_PW);

	//입력 테스트
	/*
	CString test = m_Login_ID +" " + m_Login_PW;
	MessageBox(test);
	*/

	if (m_Login_ID.Compare(_T("")) != 0 || m_Login_PW.Compare(_T("")) != 0) {
		int success = ComparePW(m_Login_ID, m_Login_PW);
		if (success == 1) {
			MessageBox(_T("로그인을 성공하였습니다."));
			m_PlayView->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_SignUp)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_btn_Login)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FindInfo)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ID)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_Password)->ShowWindow(SW_HIDE);
			
		}
		else MessageBox(_T("잘못된 아이디/비밀번호 입니다.\n다시 로그인을 시도해주세요."));
	}
	else MessageBox(_T("아이디/비밀번호를 입력해주세요."));
	
}

int CGameProjectView::ComparePW(CString  Enter_ID, CString Enter_PW) {

	CString query_str; //쿼리문
	CString m_ComparePW = _T(""); //DB에 있는 비밀번호와 비교

	query_str.Format(L"select PW from member where ID = \'%s\';", Enter_ID);


	BOOL bopen = m_prs->Open(CRecordset::snapshot, query_str);

	{
		int row = 1;
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
				
				for (int col = 0; col < 1; col++) {
					m_prs->SetAbsolutePosition(row);
					m_prs->GetFieldValue(col, m_ComparePW);
				} 
			} 
		}  
		//AfxMessageBox(m_ComparePW);  //알맞은 비밀번호
		m_prs->Close();
	}

	if (Enter_PW == m_ComparePW) return 1;
	else return 0;
}



void CGameProjectView::OnBnClickedFindinfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFindDlg Find_Screen;
	int iRes = Find_Screen.DoModal();
}
