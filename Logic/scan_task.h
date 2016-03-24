#ifndef SCAN_TASK_H
#define SCAN_TASK_H

#include <Qt/qrunnable.h>
#include "urltree.h"

class ScanTask : public QRunnable
{
public:
    ScanTask(URLTree *tree, Node * node, std::string * sub_string)
        :tree(tree), node(node), sub_string(sub_string)
    {}

    void run()
    {
        tree->scan_node(node, sub_string);
    }

private:
    URLTree *tree;
    Node * node;
    std::string * sub_string;
};

#endif // SCAN_TASK_H
