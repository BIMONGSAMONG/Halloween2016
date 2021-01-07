#include "Player.h"
#include "SpriteSheet.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y / 2 };
	size = 0;

	m_prev_pos = { 0, 0 };
	m_isClicked = 0;

	character = new SpriteSheet(L"Image/cat.png",d2d, 214, 160);
	timer = 0.0f;
	frame = 0;
	return S_OK;
}

void Player::Release()
{
	delete character;
}

void Player::Update()
{
	// 캐릭터 애니메이션 속도 조절
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	if (timer >= 0.07)
	{
		frame++;

		if (frame >= 29)
		{
			frame = 0;
		}
		timer = 0.0f;
	}
}

void Player::Render()
{
	character->Draw(frame , pos.x, pos.y);

	d2d->DrawLine(m_prev_pos, g_ptMouse, 0.5, 0.5, 0.0, 1.0);
}

void Player::Drawing()
{
	
}

void Player::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_isClicked == 0) {
		// 마우스가 클릭되었음을 설정한다.
		m_isClicked = 1;

		// 클릭된 위치를 기억한다. ( 선을 그릴때, 시작점으로 사용됨 )
		m_prev_pos.x = point.x ;
		m_prev_pos.y = point.y;
	}
}

void Player::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_isClicked) m_isClicked = 0;
}

void Player::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isClicked == 1) {
		D2D1_POINT_2F cur_pos;
		cur_pos.x = point.x;
		cur_pos.y = point.y;
		// 선을 그린다.
		d2d->DrawLine(m_prev_pos, cur_pos, 0.5, 0.5, 0.0, 1.0);
		// 현재 지점을 다음 선을 그릴때 시작점으로 사용하기 위해 저장한다.
		m_prev_pos = cur_pos;
	}
}



