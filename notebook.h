#ifndef NOTEBOOK_H
#define NOTEBOOK_H
#include "highlighter.h"
#include <QWidget>
#include <QTextEdit>
#include <QMdiSubWindow>

#include <QTextEdit>
#include <QDateEdit>
#include <QLineEdit>

class notebook : public QWidget
{
    Q_OBJECT

public:
    notebook();

    void newFile();
    bool loadFile(const QString &fileName);
    bool save();

    //代码高亮
    void highLightContent();


private:
    //子窗口的文件名
    QString childFileName;
    QMap<QString,QString> contacts;
    QLineEdit *titleEdit;
    QDateEdit *dateEdit;
    QTextEdit *contentEdit;
    Highlighter *highlighter;


};

#endif // NOTEBOOK_H
