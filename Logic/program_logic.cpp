#include "program_logic.h"


ProgramLogic::ProgramLogic()
{
    ops = new t_ops;
}

void ProgramLogic::start()
{
    ops->if_start = true;
    ops->if_pause = false;
    ops->if_stop = false;

    tree = new URLTree(ops);

    tree->start();
}

void ProgramLogic::stop()
{
    ops->if_start = false;
    ops->if_pause = false;
    ops->if_stop = true;
}

void ProgramLogic::pause()
{
    if (ops->if_pause == false)
    {
        ops->if_pause = true;
    }

    else
    {
        ops->if_pause = false;
    }
}

int ProgramLogic::get_current_level() const
{
    return this->ops->current_level;
}

int ProgramLogic::get_process_bar_count() const
{
    return (100*this->ops->current_scan_urls) / this->ops->maximun_scan_url;
}

void ProgramLogic::set_number_threads_scan(int number)
{
    this->ops->number_threads_scan = number;
}

void ProgramLogic::set_number_threads_download(int number)
{
    this->ops->number_threads_download = number;
}

void ProgramLogic::set_maximun_scan_url(int number)
{
    this->ops->maximun_scan_url = number;
}

void ProgramLogic::set_start_url(std::string url)
{
    this->ops->start_url = url;
}

void ProgramLogic::set_research_text(std::string text)
{
    this->ops->sub_string = text;
}
