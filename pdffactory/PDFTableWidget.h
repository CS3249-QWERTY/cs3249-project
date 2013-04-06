#ifndef PDFTABLEWIDGET_H
#define PDFTABLEWIDGET_H

#include <poppler-qt4.h>

#include <QFrame>

class QVBoxLayout;
class QString;

class PDFFileWidget;

class PDFTableWidget: public QFrame
{
    Q_OBJECT
    public:
        PDFTableWidget(QWidget *parent = 0);
    protected:
    private:
        QVBoxLayout *outerLayout;
        void loadFile (QString fileName);

        QVector<Poppler::Document*> files;
        QVector<QString>            fileNames;
        QVector<PDFFileWidget *>    fileWidgets;
};
#endif
