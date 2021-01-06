#include "TimerManager.h"
#include "Timer.h"

HRESULT TimerManager::Init()
{
    timer = new Timer();
    timer->Init();

    return S_OK;
}

void TimerManager::Release()
{
    delete timer;
}

void TimerManager::Update()
{
    if (timer)
        timer->Tick();
}

void TimerManager::Render()
{
   // if (timer)
   // {
   //     wsprintf(szText, "FPS : %d", timer->GetFPS());
   //     TextOut(d2d, WINSIZE_X - 150, 20, szText, strlen(szText));
   // }
}

float TimerManager::GetElapsedTime()
{
    return timer->GetElapsedTime();
}
