// CPlayFormView.cpp: 구현 파일
//

#include "pch.h"
#include "GameProject.h"
#include "GameProjectDoc.h"
#include "MainFrm.h"
#include "CPlayFormView.h"


BEGIN_MESSAGE_MAP(CPlayFormView, CFormView)
	ON_WM_SIZE()
	//ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CPlayFormView::OnmyEasy)
	ON_COMMAND(ID_32772, &CPlayFormView::OnmyNormal)
	ON_COMMAND(ID_32773, &CPlayFormView::OnmyHard)
	ON_COMMAND(ID_32774, &CPlayFormView::OnmyHell)
	ON_COMMAND(ID_32775, &CPlayFormView::OnShowRanking)
END_MESSAGE_MAP()

// CPlayFormView

IMPLEMENT_DYNCREATE(CPlayFormView, CFormView)

CPlayFormView::CPlayFormView()
	: CFormView(IDD_Play)
{
	level = 0;
	start = 0;
	x = 0;
	y = 0;
	step = 10;
	count = 0;
	gover = 0;
	m_winright = 0;
	m_winbottom = 0;

	BOOL bopen = m_db.OpenEx(_T("DSN=mydb;SERVER=127.0.0.1;PORT=3306;UID=root;PWD=0804; DATABASE=gameproject;"), CDatabase::noOdbcDialog);
	if (bopen) m_prs = new CRecordset(&m_db);

}

CPlayFormView::~CPlayFormView()
{
}

void CPlayFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


// CPlayFormView 진단

#ifdef _DEBUG
void CPlayFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlayFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CPlayFormView::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	/*------------------아이디 및 회원정보 테스트-----------------------------------------------------------------------*/
	//CString str_login;
	//str_login.Format(_T("% s 님 환영합니다."), m_loginID_now); // m_loginID_now 전역변수 // 현재 로그인 아이디
	//dc.SetBkMode(TRANSPARENT);
	//dc.TextOutW(10, 30, str_login);

	getStates(); //로그인 된 아이디의 정보 구조체에 저장

	//CString str_states = player.m_pID + player.m_pPW + player.m_pNICKNAME;
	//MessageBox(str_states);
	
	CString stage;
	/*--------게임 over 판별, 난이도 -------------------------------------------------------------------*/
	if (gover == 0) {
		CDC memdc;
		CBitmap* p0ldBitmap, bitmap;

		memdc.CreateCompatibleDC(&dc);
		bitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
		p0ldBitmap = memdc.SelectObject(&bitmap);

		CBrush bs(RGB(255, 255, 255));
		memdc.SelectObject(&bs);
		memdc.Rectangle(0, 0, rect.right, rect.bottom);

		int delay;
		delay = rand() % 10 + 1;

		
		CString str, str2;

		if (level == 0)
			str2.Format(L"EASY");
		else if (level == 1)
			str2.Format(L"NORMAL");
		else if (level == 2)
			str2.Format(L"HARD");
		else if (level == 3)
			str2.Format(L"HELL");
		
		
		stage=str2;
		str.Format(L"\n 누르면 게임시작\n난이도는 % s입니다.", str2);

		if (start == 0) {
			MessageBox(str);
			start = !start;
		}

		SetTimer(0, 10, NULL);
		//easy , nomal , hard , hell


		switch (level) {


		case 0:
			if (delay == 5)
				for (int i = 0; i < 1; i++) {
					k.push_back(0);
					int r = rand() % 11 + 10;
					er.push_back(r);
					k[i].x = rand() % (rect.right - 99) + 50;
					k[i].y = -1 * (100 * (delay));
					e.push_back(k[i]);
					step_y.push_back(rand() % 2 + 4);
					if (e[i].y - er[i] >= rect.bottom)
						count++;
					else if (e[i].y - er[i] >= m_winbottom)
						return;
				}
			break;

		case 1:
			if (delay % 5 == 0)
				for (int i = 0; i < 1; i++) {
					k.push_back(0);
					int r = rand() % 11 + 10;
					er.push_back(r);
					k[i].x = rand() % (rect.right - 99) + 50;
					k[i].y = -1 * (100 * (delay));
					e.push_back(k[i]);
					step_y.push_back(rand() % 2 + 4);
					if (e[i].y - er[i] >= rect.bottom)
						count++;
					else if (e[i].y - er[i] >= m_winbottom)
						return;
				}
			break;

		case 2:
			if (delay % 3 == 0)
				for (int i = 0; i < 1; i++) {
					k.push_back(0);
					int r = rand() % 11 + 10;
					er.push_back(r);
					k[i].x = rand() % (rect.right - 99) + 50;
					k[i].y = -1 * (100 * (delay));
					e.push_back(k[i]);
					step_y.push_back(rand() % 2 + 4);
					if (e[i].y - er[i] >= rect.bottom)
						count++;
					else if (e[i].y - er[i] >= m_winbottom)
						return;
				}
			break;

		case 3:
			if (delay % 2 == 0)
				for (int i = 0; i < 1; i++) {
					k.push_back(0);
					int r = rand() % 11 + 10;
					er.push_back(r);
					k[i].x = rand() % (rect.right - 99) + 50;
					k[i].y = -1 * (100 * (delay));
					e.push_back(k[i]);
					step_y.push_back(rand() % 2 + 4);
					if (e[i].y - er[i] >= rect.bottom)
						count++;
					else if (e[i].y - er[i] >= m_winbottom)
						return;
				}
			break;
		}

		for (int i = 0; i < e.size(); i++) {
			CBrush bs(RGB(255, 255, 220));
			memdc.SelectObject(&bs);
			memdc.Ellipse(e[i].x - er[i], e[i].y - er[i], e[i].x + er[i], e[i].y + er[i]);
		}
		dc.BitBlt(0, 0, rect.right, rect.bottom, &memdc, 0, 0, SRCCOPY);

		str.Format(_T("점수 = %d"), count); //str에 저장
		dc.SetBkMode(TRANSPARENT);
		dc.TextOutW(10, 10, str);
		
		/*--------사람 비트맵-------------------------------------------------------------------*/
		CDC memDC;
		CBitmap bmp, * ob;
		memDC.CreateCompatibleDC(pDC);
		bmp.LoadBitmap(IDB_BITMAP1);
		ob = memDC.SelectObject(&bmp);
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);
		pDC->TransparentBlt(x + m_winright, y + m_winbottom, bmpInfo.bmWidth, bmpInfo.bmHeight, &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));

		memDC.SelectObject(ob);
		bmp.DeleteObject();
		memDC.DeleteDC();
		
	
		/*--------사각형-------------------------------------------------------------------*/
		/*
		CBrush bs1, * pbs1;
		CPen pen, * oldpen;
		// test_brush(RGB(0, 0, 0));

		bs1.CreateStockObject(NULL_BRUSH); //투명 사각형
		pen.CreatePen(PS_NULL, 0, RGB(255, 255, 255)); //선
		pbs1 = dc.SelectObject(&bs1);
		//pbs1 = dc.SelectObject(&test_brush);

		oldpen = dc.SelectObject(&pen);
		dc.Rectangle(x + m_winright + 10, y + m_winbottom, x + m_winright + 35, y + m_winbottom + 50);
		dc.SelectObject(pbs1);
		dc.SelectObject(oldpen);
		pen.DeleteObject();
		*/
		/*
		CDC memDc;
		CBitmap *pbmP, oldb;

		memDc.CreateCompatibleDC(&dc);
		oldb.CreateCompatibleBitmap(&dc, m_winright+35, m_winbottom+50);
		pbmP = memDc.SelectObject(&oldb);

		CBrush bs1(NULL_BRUSH);
		memDc.SelectObject(&bs1);
		memDc.Rectangle(m_winright + 10, m_winbottom, m_winright + 35, m_winbottom + 50);

		CPen pen(PS_NULL, 0, RGB(255, 255, 255));
		memDc.SelectObject(&pen);
		CBrush bs2(NULL_BRUSH);
		memDc.SelectObject(&bs2);
		memdc.Rectangle(x + m_winright + 10, y + m_winbottom, x + m_winright + 35, y + m_winbottom + 50);
		*/
		/*
		bs1.CreateStockObject(NULL_BRUSH); //투명 사각형
		pen.CreatePen(PS_NULL, 0, RGB(255, 255, 255)); //선
		pbs1 = dc.SelectObject(&bs1);
		//pbs1 = dc.SelectObject(&test_brush);

		oldpen = dc.SelectObject(&pen);
		dc.Rectangle(x + m_winright + 10, y + m_winbottom, x + m_winright + 35, y + m_winbottom + 50);
		dc.SelectObject(pbs1);
		dc.SelectObject(oldpen);
		pen.DeleteObject();
		*/
		/*
		if (x + m_winright > m_winright && x > m_winright)
			x = x * -1;
		else if (x + m_winright < m_winright && x < -m_winright)
			x = x * -1;
		*/
		if (x + m_winright > m_winright && x > m_winright) {
			x = x * -1;
			return;
		}
		if (x + m_winright < m_winright && x < -m_winright) {
			x = x * -1;
			return;
		}
		
		int dx, dy;
		double compile;
		for (int i = 0; i < e.size(); i++)
		{
			dx = e[i].x - (x + m_winright + 23);
			dy = e[i].y - (y + m_winbottom + 10);
			compile = sqrt(dx * dx + dy * dy);
			if (compile < er[i]) {
				gover = 1;
				Invalidate();
			}
		}

	}

	else {
	/*-------게임종료 시 화면-------------------------------------------------------------------*/
		KillTimer(0);
		e.clear();
		er.clear();
		step_y.clear();
		k.clear();
		start = 0;
		CDC mdc;
		CBitmap s_bit, * oldbit;
		mdc.CreateCompatibleDC(pDC);
		s_bit.LoadBitmap(IDB_BITMAP2);
		oldbit = mdc.SelectObject(&s_bit);
		int w, h;
		w = rect.right;
		h = rect.bottom;
		pDC->StretchBlt(w / 4, 100, 10 * w, 10 * h, &mdc, 0, 0, w, h, SRCCOPY);
		
		mdc.SelectObject(oldbit);
		s_bit.DeleteObject();
		mdc.DeleteDC();

		CString str;
		CFont font, * pOldFont;
		font.CreatePointFont(250, _T("궁서체"));
		pOldFont = (CFont*)dc.SelectObject(&font);
		str.Format(L"최종 점수 = %d ", count);
		dc.SetBkMode(TRANSPARENT);
		//dc.TextOut(w - 700, h - 500, str);
		dc.TextOut(w/2, h/8, str);

		Send_PlayRecord(player.m_pNICKNAME, count, level);

		gover = 0;
		count = 0;
		Sleep(2500);
		Invalidate();
	}
}



BOOL CPlayFormView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return false;
}



BOOL CPlayFormView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->message == WM_KEYDOWN)
	{
		KeyDown(*pMsg);
	}

	//SetTimer(0, 10, NULL);

	Invalidate();

	return CFormView::PreTranslateMessage(pMsg);
}


void CPlayFormView::KeyDown(MSG pMsg) {

	switch (pMsg.wParam)
	{
	case VK_LEFT:
		x -= step; break;
	case VK_RIGHT:
		x += step;
	}

}

void CPlayFormView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	for (int i = 0; i < e.size(); i++) {
		e[i].y += step_y[i];
	}

	Invalidate();

	CFormView::OnTimer(nIDEvent);
}


void CPlayFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_winright = cx / 2;
	m_winbottom = cy - 50;


}

void CPlayFormView::OnmyEasy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(0);
	count = 0;
	level = 0;
	e.clear();
	er.clear();
	step_y.clear();
	k.clear();
	start = 0;
	Invalidate();
}


void CPlayFormView::OnmyNormal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(0);
	count = 0;
	level = 1;
	e.clear();
	er.clear();
	step_y.clear();
	k.clear();
	start = 0;
	Invalidate();
}




void CPlayFormView::OnmyHard()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(0);
	count = 0;
	level = 2;
	e.clear();
	er.clear();
	step_y.clear();
	k.clear();
	start = 0;
	Invalidate();
}




void CPlayFormView::OnmyHell()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(0);
	count = 0;
	level = 3;
	e.clear();
	er.clear();
	step_y.clear();
	k.clear();
	start = 0;
	Invalidate();
}

void CPlayFormView::getStates() {
	CString query_str;
	CString str;

	query_str.Format(L"select * from member where ID = \'%s\';", m_loginID_now);

	BOOL bopen = m_prs->Open(CRecordset::snapshot, query_str);
	{
		
		int row = 1;
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
				//int fieldc = m_prs->GetODBCFieldCount();
				//for (int i = 0; i < fieldc; i++) {
				//	CString info;
					m_prs->SetAbsolutePosition(row);
				//	m_prs->GetFieldValue(i, info);
				//	str = str + " " + info;
					m_prs->GetFieldValue(short(0), player.m_pID);
					m_prs->GetFieldValue(short(1), player.m_pPW);
					m_prs->GetFieldValue(short(2), player.m_pNICKNAME);
					m_prs->GetFieldValue(short(3), player.m_pNAME);
					m_prs->GetFieldValue(short(4), player.m_pGENDER);
					m_prs->GetFieldValue(short(5), player.m_pBIRTHDAY);
					m_prs->GetFieldValue(short(6), player.m_pPHONE);

				//} // for i
				//str += "\n";
			//	row++;


			} // for m_prs
		} // if 

		//AfxMessageBox(m_CompareID); 
		m_prs->Close();
	}

}


void CPlayFormView::Send_PlayRecord(CString nickname, int score, int leve){

	CString query_str;

	m_db.BeginTrans();
	try {
		query_str.Format(L"INSERT INTO play_record(nickname, score, level, date) VALUES(\'%s\', \'%d\', \'%d\', NOW())",
		nickname, score, level);
		m_db.ExecuteSQL(query_str);
	}
	catch (CException* e) {
		e->ReportError();
	}

	m_db.CommitTrans();

}

void CPlayFormView::OnShowRanking()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	if (rankingDlg == NULL)

	{
		rankingDlg = new CRankDlg(this);
		rankingDlg->Create(IDD_RANK, this);
		rankingDlg->ShowWindow(SW_SHOW);
	}

}
