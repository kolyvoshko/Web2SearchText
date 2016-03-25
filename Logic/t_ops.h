#ifndef T_OPS_H
#define T_OPS_H

#include <string>
#include <queue>

struct messgage_node
{
    std::string type;
    std::string message;
};


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

        outBuffer = new std::queue<messgage_node*>;
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
    std::string sub_string;

    // multithreading
    int number_threads_scan;
    int number_threads_download;

    // borders
    int maximun_scan_url;

    std::queue<messgage_node*> * outBuffer;

    void write_to_bufer(std::string message)
    {
        messgage_node * node = new messgage_node;
        node->type = "stdout";
        node->message = message;

        outBuffer->push(node);
    }

    void write_to_bufer(std::string type, std::string message)
    {
        messgage_node * node = new messgage_node;
        node->type = type;
        node->message = message;

        outBuffer->push(node);
    }

    std::queue<messgage_node*>* read_buffer()
    {
        return outBuffer;
    }

    int get_process_bar_count()
    {
        int count = 100*current_scan_urls/maximun_scan_url;

        if (count > 100)
            return 100;

        else
            return count;
    }
};

#endif // T_OPS_H
