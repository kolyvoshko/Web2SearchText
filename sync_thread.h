#ifndef RUN_THREAD_H
#define RUN_THREAD_H

#include <QThread>
#include <QTextBrowser>
#include <QPlainTextEdit>
#include <QProgressBar>

#include <Logic/t_ops.h>
#include "mainwindow.h"
#include <iostream>

class syncThread : public QThread
{
public:
    syncThread(Ui::MainWindow *ui, t_ops *ops)
        : ops(ops)
    {
        find_browser = ui->textBrowser_find;
        log_browser = ui->textBrowser_log;

        html_style = "<style>"
                     "p.find{color: green; margin: 0; padding: 0;}"
                     "p.error{color: red; margin: 0; padding: 0;}"
                     "</style>";

        format_find = "<p class=\"find\">%1</p>";
        format_error = "<p class=\"error\">%1</p>";
        format_url = "<a href=\"url\">%1</a>";

        find_browser->setHtml(html_style);
        log_browser->setHtml(html_style);
    }

    void run()
    {
        while(1) {
            this->msleep(20);
            std::queue<messgage_node*> *q = ops->read_buffer();
            while (!q->empty())
            {
                messgage_node* node = q->front();
                q->pop();

                QString message = QString::fromStdString(node->message);

                if (node->type == "success")
                    find_browser->append(html_style + format_find.arg(message));

                if (node->type == "success_log")
                    log_browser->append(html_style + format_find.arg(message));

                if (node->type == "error_log")
                    log_browser->append(html_style + format_error.arg(message));

                else
                    log_browser->append(message);
            }

            if (ops->if_stop){
                break;
                this->deleteLater();
            }
        }
    }

private:
    t_ops *ops;
    QTextBrowser *find_browser, *log_browser;

    QString html_style;
    QString format_find;
    QString format_error;
    QString format_url;
};

#endif // RUN_THREAD_H
