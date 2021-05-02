
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "worm_game_mfc.h"
#include "ChildView.h"
#include "Map.h"
#include "Worm.h"
#include "WormBody.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	gameManager = NULL;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(&dc);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	memDc.SelectObject(&bitmap);
	
	//코드

	gameManager->map->drawMap(&memDc); // 맵그리기
	gameManager->playerWorm->draw(&memDc); // 벌레 그리기
	gameManager->food->draw(&memDc); // 음식 그리기
	
	if (gameManager->dead) {
		// 죽었을 경우
		memDc.TextOut(300, 300, _T("Game Over"));
	}
	memDc.TextOut(0, 0, _T("수홍이표 지렁이게임"));
	//
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDc, 0, 0, SRCCOPY); // 도화지 교체

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) {
	case VK_SPACE:
		//정보 리셋
		gameManager->initGame();
		Invalidate();
		break;
	case VK_LEFT:
		if (!gameManager->isGameStart && !gameManager->dead) {
			gameManager->isGameStart = true;
		}
		delete gameManager->dir;
		gameManager->dir = new CPoint(-gameManager->map->BLOCK_WIDTH, 0);
		break;
	case VK_RIGHT:
		if (!gameManager->isGameStart && !gameManager->dead) {
			gameManager->isGameStart = true;
		}
		delete gameManager->dir;
		gameManager->dir = new CPoint(gameManager->map->BLOCK_WIDTH, 0);
		break;
	case VK_UP:
		if (!gameManager->isGameStart && !gameManager->dead) {
			gameManager->isGameStart = true;
		}
		delete gameManager->dir;
		gameManager->dir = new CPoint(0, -gameManager->map->BLOCK_WIDTH);
		break;
	case VK_DOWN:
		if (!gameManager->isGameStart && !gameManager->dead) {
			gameManager->isGameStart = true;
		}
		delete gameManager->dir;
		gameManager->dir = new CPoint(0, gameManager->map->BLOCK_WIDTH);
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	srand((unsigned int)(time(NULL)));
	gameManager = new GameManager();
	gameManager->initGame(); // 게임 초기화

	SetTimer(1, 100, NULL); // 타이머 시작
	return 0;
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1) {
		if (gameManager->isGameStart) {
			WormBody head = gameManager->playerWorm->getHead();

			CPoint newLeftTop(head.leftTop.x + gameManager->dir->x, head.leftTop.y + gameManager->dir->y);				// 새로 움직일 좌표
			CPoint newRightBottom(head.rightBottom.x + gameManager->dir->x, head.rightBottom.y + gameManager->dir->y);	// 새로 움직일 좌표

			gameManager->playerWorm->move(newLeftTop, newRightBottom);

			if (gameManager->map->isCollision(newLeftTop, newRightBottom)) {
				// 벽과 충돌 시
				gameManager->isGameStart = false;
				gameManager->dead = true;
			}

			if (gameManager->playerWorm->isCollision(newLeftTop, newRightBottom)) {
				// 자기 자신 몸과 충돌 시
				gameManager->isGameStart = false;
				gameManager->dead = true;
			}

			if (gameManager->food->isCollision(newLeftTop, newRightBottom)) {
				//음식과 충돌 시
				gameManager->food->randomCreate(); // 새로 랜덤생성
				gameManager->playerWorm->eat(); // 음식 섭취
			}

			Invalidate();
		}
	}
	CWnd::OnTimer(nIDEvent);
}



