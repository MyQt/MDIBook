#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    path = QDir::currentPath();//获取当前路径
    setupFileTree();//初始化文件树形图
    initMenu();//初始化文件树形图的右键菜单
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    notebook *child = new notebook;
    ui->mdiArea->addSubWindow(child);
    child->newFile();
    child->show();


}

void MainWindow::initMenu()
{
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);//设置这个才能添加右键菜单
    itemMenu = new QMenu(this);
    QAction *open;
    open = new QAction(tr("打开"),this);
    itemMenu->addAction(open);
    QAction *del;
    del = new QAction(tr("删除"),this);
    itemMenu->addAction(del);

    connect(open, SIGNAL(triggered()), this, SLOT(open()));
    connect(del, SIGNAL(triggered()), this, SLOT(del()));
}
void MainWindow::open(){
    path = itemPath;
    load();

}
void MainWindow::del(){
    QFile::remove(itemPath);
}


void MainWindow::setupFileTree()
{
    model = new QFileSystemModel();
    model->setRootPath(path);
    ui->treeView->setModel(model);
    QModelIndex index = model->index(path);

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    //展开到当前目录
    ui->treeView->expand(index);

    //滚动到当前目录
    ui->treeView->scrollTo(index);
    //设置列宽
    ui->treeView->resizeColumnToContents(0);

}






void MainWindow::on_actionSave_triggered()
{
    if(activeMdiChild()){
        activeMdiChild()->save();
    }
}
notebook *MainWindow::activeMdiChild()
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<notebook *>(activeSubWindow->widget());
    return 0;

}

void MainWindow::on_actionLoad_triggered()
{
//    QString fileName = QFileDialog::getOpenFileName(this,tr("打开文件"),"",tr("NB files(*.nb);;All Files(*)"));
    path = QFileDialog::getOpenFileName(this,tr("打开文件"),"",tr("NB files(*.nb);;All Files(*)"));
    if(path =="")return;
    load();
}

void MainWindow::load()
{
    //判断是否存在打开相同文件的子窗口
    QMdiSubWindow *existing = checkSubWindow(path);
    if (existing) {
        ui->mdiArea->setActiveSubWindow(existing);
        return;

    }

    notebook *child = new notebook;
    ui->mdiArea->addSubWindow(child);
    child->loadFile(path);
    child->show();

//    path = fileName;
//    qDebug() << path;


    setupFileTree();//更新树形图
}

QMdiSubWindow *MainWindow::checkSubWindow(QString &fileName)
{
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        //获取notebook
        notebook *noteBook = qobject_cast<notebook *>(window->widget());
        if(noteBook->windowTitle()==fileName)
            return window;
    }
    return 0;
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    //QModel可以通过index获取该节点文件的路径
    path =model->filePath(index);
    load();


}

void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{

    QModelIndex index = ui->treeView->indexAt(pos);
    itemPath = model->filePath(index);
    itemMenu->exec(QCursor::pos());
}
