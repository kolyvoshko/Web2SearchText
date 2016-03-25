#ifndef PROGRAM_LOGIC_H
#define PROGRAM_LOGIC_H

#include "urltree.h"
#include "t_ops.h"

class ProgramLogic
{
public:
    ProgramLogic();

    void start();
    void stop();
    void pause();

    int get_current_level() const;
    int get_process_bar_count() const;

    void set_number_threads_scan(int number);
    void set_number_threads_download(int number);
    void set_maximun_scan_url(int number);
    void set_start_url(std::string url);
    void set_research_text(std::string text);

    URLTree * tree;
    t_ops * ops;

private:

};

#endif // PROGRAM_LOGIC_H
