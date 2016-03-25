#include "urltree.h"
#include "url_util.h"
#include "Qt/qfuture.h"
#include "Qt/qtconcurrentrun.h"
#include <Qt/qtconcurrentmap.h>


#include <list>
#include <queue>
#include <string>


URLTree::URLTree(t_ops *ops)
{
    this->ops = ops;
    this->root = new Node;

    root->url = ops->start_url;

    QThreadPool::globalInstance()->setMaxThreadCount(ops->number_threads_scan);
}

void URLTree::scan(std::string * sub_string)
{
     scan_thread(sub_string);
}

void URLTree::scan_thread(std::string * sub_string)
{
    if (!root)
        return;

    std::queue<Node *> current, next;
    current.push(root);

    while (!current.empty())
    {
        if (ops->if_pause)
        {
            msleep(100);
            continue;
        }
        if (ops->if_stop) break;

        if (QThreadPool::globalInstance()->activeThreadCount() <
                QThreadPool::globalInstance()->maxThreadCount())
        {
            ops->current_scan_urls++;
            //std::cout << ops->current_scan_urls << std::endl;

            if (ops->current_scan_urls > ops->maximun_scan_url)
            {
                synchronizer.waitForFinished();
                synchronizer.clearFutures();
                break;
            }

            ops->process_bar_count = ops->get_process_bar_count();

            Node *current_node = current.front();
            current.pop();

            synchronizer.addFuture( QtConcurrent::run( this, &URLTree::scan_node, &next, current_node, sub_string) );
        }

        if (current.empty())
        {
            synchronizer.waitForFinished();
            synchronizer.clearFutures();
            std::swap(current, next);
        }
    }

    ops->if_start = false;
}

void URLTree::set_start_url(std::string url)
{
    root->url = url;
}

void URLTree::scan_node(std::queue<Node *> *nextLevel, Node *node, std::string * sub_string)
{
    if (node->is_scan)
        return;

    else node->is_scan = true;

    messgage_node * curl_message = new messgage_node;
    std::string html_code(download_html(node->url.c_str(), curl_message));
    node->is_find_text = find_string(&html_code, sub_string);

    std::string is_find = node->is_find_text ? "true" : "false";
    std::string log_type_message = node->is_find_text ? "success_log" : "log";

    if (curl_message->type == "error_log")
        log_type_message = "error_log";

    ops->write_to_bufer(log_type_message, "URL: " + node->url
                        + "\t"+ "Find text: " + is_find + "\n "
                        + curl_message->message);

    if (node->is_find_text){
        // out to stdout
        std::cout << std::boolalpha << "Find text \"" <<
              *sub_string << "\": "<< node->is_find_text << std::endl;

        std::cout << "URL: " << node->url << std::endl << std::endl;

        // redirect to gui text browsers
        ops->write_to_bufer("success", node->url);
    }

    std::list<std::string> urls = find_url(&html_code);

    for (auto it : urls)
    {
        bool is_find = this->find_node(&it);

        if (!is_find)
        {
            ops->write_to_bufer("Find new url: " + it);

            Node * add_node = new Node;
            add_node->url = it;
            node->childs.push_back(add_node);
        }
    }

    if (!node->childs.empty())
    {
        for (auto &it : node->childs)
            nextLevel->push(it);
    }
}

bool URLTree::find_node(std::string * url)
{
    if (!root)
        return false;

    std::queue<Node *> current, next;
    current.push(root);

    while (!current.empty())
    {
        Node *current_node = current.front();
        current.pop();

        if (current_node->url == *url)
            return true;

        if (!current_node->childs.empty())
        {
            for (auto &it : current_node->childs)
                next.push(it);
        }

        if (current.empty())
            std::swap(current, next);
    }

    return false;
}
