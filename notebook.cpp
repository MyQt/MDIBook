#include "notebook.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDataStream>


notebook::notebook()
{
    QLabel *titleLabel = new QLabel(tr("标题"));
    titleEdit = new QLineEdit;
    dateEdit = new QDateEdit;
    contentEdit = new QTextEdit;

    //初始化日期
    QDate date = QDate::currentDate();
    dateEdit->setDate(date);
    //代码高亮
    highLightContent();
    //第一行
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(titleLabel);
    hLayout->addWidget(titleEdit);
    hLayout->addWidget(dateEdit);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(hLayout,0,0);
    mainLayout->addWidget(contentEdit,1,0);
    setLayout(mainLayout);

}

void notebook::newFile()
{
    static int sequenceNumber = 1;
    childFileName = tr("document%1.nb").arg(sequenceNumber++);
    setWindowTitle(childFileName + "*");
}

bool notebook::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("不能读取文件%1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QDataStream in(&file);
    in >> contacts;
    titleEdit->setText(contacts["title"]);
    QDate date = QDate::fromString(contacts["date"],"yyyy/MM/dd");
    dateEdit->setDate(date);
    contentEdit->setText(contacts["content"]);
    setWindowTitle(fileName);
    return true;
}



bool notebook::save()
{

    QString fileName = QFileDialog::getSaveFileName(this,tr("保存为"),childFileName,tr("NB files (*.nb);;All Files(*)"));
    if(fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("MDIBook"),
                              tr("%1写入错误:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }

    contacts.insert("title",titleEdit->text());
    contacts.insert("date",dateEdit->text());
    contacts.insert("content",contentEdit->toPlainText());



    QDataStream out(&file);
    out << contacts;


    setWindowTitle(fileName);
    return true;
}

void notebook::highLightContent()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    contentEdit->setFont(font);

    highlighter = new Highlighter(contentEdit->document());
}
