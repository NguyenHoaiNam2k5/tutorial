#include "imgTimer.h"
#include "const.h"


ImpTimer::ImpTimer()
{
    start_tick_ = 0;
    paused_tick_ = 0;
    is_paused_ = 0;
    is_started_ = 0;
    level_up_time = 0;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
    is_started_ = 1;
    is_paused_ = 0;
    start_tick_ = SDL_GetTicks();
}

void ImpTimer::stop()
{
    is_paused_ = 0;
    is_started_ = 0;
}

void ImpTimer::paused()
{
    if(is_started_ == 1 && is_paused_ == 0)
    {
        is_paused_ = 1;
        paused_tick_ = SDL_GetTicks() - start_tick_ ;
    }
}

void ImpTimer::unpaused()
{
    if(is_paused_ == 1)
    {
        is_paused_ = 0;
        start_tick_ = SDL_GetTicks() - paused_tick_;
        paused_tick_ = 0;
    }
}

int ImpTimer::get_ticks()
{
    if(is_started_ == 1)
    {
        if(is_paused_ == 1)
        {
            return paused_tick_;
        }
        else
        {
            int get_ticks = SDL_GetTicks() - start_tick_ + level_up_time;
            return get_ticks;
        }
    }
    return 0;
}

bool ImpTimer::is_started()
{
    return is_started_;
}

bool ImpTimer::is_paused()
{
    return is_paused_;
}

