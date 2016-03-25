#ifndef URLTREE_H
#define URLTREE_H

#include "t_ops.h"

#include <list>
#include <string>
#include <queue>

#include <Qt/qthreadpool.h>
#include "Qt/qfuturesynchronizer.h"

/**
 * @brief The Node struct has data of url page, all url in page
 * and bool Is find text?
 */
struct Node
{
    Node()
    {
        is_find_text = false;
        is_scan = false;
    }

    bool is_find_text;
    bool is_scan;

    std::string url;
    std::list<Node *> childs;
};


/**
 * @brief The URLTree class is a graph of Node (url pages)
 */
class URLTree : public QThread
{
public:
    URLTree(t_ops *ops);

    /**
     * @brief scan scaning all node in tree and add new url to tree
     * @param sub_string research string
     */
    void scan(std::string *sub_string);
    void run() { this->scan(&ops->sub_string); }

    void set_start_url(std::string url);

private:
    Node * root;
    t_ops * ops;
    QFutureSynchronizer<void> synchronizer;

    /**
     * @brief scan_node scan one node and all not find url to node->childs
     * @param node
     * @param sub_string research string
     */
    void scan_node(std::queue<Node *> *nextLevel,Node * node, std::string *sub_string);


    /**
     * @brief find_node find node that has url addres equal url
     * @param url url address
     * @return if find -> true
     */
    bool find_node(std::string *url);

    void scan_thread(std::string * sub_string);

};

#endif // URLTREE_H
