#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "notebook.h"

#include <QMainWindow>
#include <QTreeView>
#include <QFileSystemModel>
#include <QMenu>
#include <QMdiArea>
#include <QDir>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void on_actionNew_triggered();
    //初始化文件树形图的右键菜单
    void initMenu();
    //初始化文件树形图
    void setupFileTree();
    //获取当前选中的窗口
    notebook *activeMdiChild();


    //树形图右键
    void on_treeView_customContextMenuRequested(const QPoint &pos);
    //右键打开
    void open();
    //右键删除
    void del();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

    void load();

    QMdiSubWindow *checkSubWindow(QString &fileName);



    void on_treeView_doubleClicked(const QModelIndex &index);

private:

    QFileSystemModel *model;
    QString path;
    //右键展开的menu
    QMenu *itemMenu;
    //记录右键文件的位置
    QString itemPath;
};

#endif // MAINWINDOW_H
