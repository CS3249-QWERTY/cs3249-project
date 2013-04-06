#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <poppler-qt4.h>

#include <QFrame>

class QVBoxLayout;
class QString;

class PDFFileWidget;

class TableView: public QFrame
{
    Q_OBJECT
    public:
        TableView(QWidget *parent = 0);
    protected:
    private:
        QVBoxLayout *outerLayout;
        void loadFile (QString fileName);

        QVector<Poppler::Document*> files;
        QVector<QString>            fileNames;
        QVector<PDFFileWidget *>    fileWidgets;
};
#endif
