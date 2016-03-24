#include "urltree.h"
#include "url_util.h"
#include "Qt/qfuture.h"
#include "Qt/qtconcurrentrun.h"

#include <list>
#include <queue>
#include <string>


URLTree::URLTree(t_ops *ops)
{
    this->ops = ops;
    this->root = new Node;

    root->url = ops->start_url;
}

void URLTree::scan(std::string * sub_string)
{
//    for (int n=0; n < ops->number_threads_scan; n++)
//        QtConcurrent::run(this, &URLTree::scan_thread, sub_string);
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
        ops->current_scan_urls++;
        if (ops->current_scan_urls > ops->maximun_scan_url)
            break;

        if (ops->if_pause) continue;
        if (ops->if_stop) break;

        Node *current_node = current.front();
        current.pop();

        scan_node(&next, current_node, sub_string);

        if (current.empty())
            std::swap(current, next);
    }
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

    std::string html_code(download_html(node->url.c_str()));
    node->is_find_text = find_string(&html_code, sub_string);

    if (node->is_find_text){
        std::cout << std::boolalpha << "Find text \"" <<
              *sub_string << "\": "<< node->is_find_text << std::endl;

        std::cout << "URL: " << node->url << std::endl << std::endl;
    }

    std::list<std::string> urls = find_url(&html_code);

    for (auto it : urls)
    {
        // std::cout << "Find " << it << " url.";
        bool is_find = this->find_node(&it);
        // std::cout << std::boolalpha << "Find is tree: "<< is_find << std::endl;

        if (!is_find)
        {
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
