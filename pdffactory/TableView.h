#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "QWidget"
#include "QSplitter"
#include "QVBoxLayout"
#include "QScrollArea"
#include "QPushButton"
#include "PDFPageWidget.h"
#include "PDFFileWidget.h"
#include "QFrame"

#include <poppler-qt4.h>

class QPushButon;
class QWidget;
class QScrollArea;
class TableView: public QWidget
{
    Q_OBJECT
    public:
        TableView(QWidget *parent = 0);
    protected:
    private:
        QScrollArea *scrollArea;
        QVBoxLayout *layout;
        QFrame *frame;
        QVBoxLayout *outerLayout;
        void paintEvent ( QPaintEvent * event );
        void loadFile ( QString  fileName );

        QVector<Poppler::Document*> files;
        QVector<QString>            filenames;
        QVector<PDFFileWidget *>      fileWidgets;
};
#endif
