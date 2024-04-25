#pragma once

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void paused();
    void unpaused();
    void set_level_up(){level_up_time += 120000;}

    int get_ticks();

    bool is_started();
    bool is_paused();
private:
    int start_tick_;
    int paused_tick_;

    int level_up_time;

    bool is_paused_;
    bool is_started_;
};
