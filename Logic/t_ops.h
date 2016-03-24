#ifndef T_OPS_H
#define T_OPS_H

#include <string>

/**
 * @brief The t_ops struct has program general variables
 * neded to scanning web pages and working gui interface
 */
struct t_ops
{
    t_ops()
    {
        if_pause = false;
        if_start = false;
        if_stop = false;

        process_bar_count = 0;
        current_scan_urls = 0;
        current_level = 0;

        number_threads_scan = 1;
        number_threads_download = 1;

        maximun_scan_url = 2;
    }

    // for program control key
    bool if_start;
    bool if_pause;
    bool if_stop;

    // for status bar
    int process_bar_count;
    int current_scan_urls;
    int current_level;

    // string gui data
    std::string start_url;
    std::string research_text;

    // multithreading
    int number_threads_scan;
    int number_threads_download;

    // borders
    int maximun_scan_url;
};

#endif // T_OPS_H
