#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class Highlighter:public QSyntaxHighlighter
{

public:
    Highlighter(QTextDocument *parent);
protected:
    void highlightBlock(const QString &text);
private:
    struct HighlightRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    //格式
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};


#endif // HIGHLIGHTER_H
