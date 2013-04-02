#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "QWidget"
#include "QSplitter"
#include "QVBoxLayout"
#include "QScrollArea"
#include "QPushButton"
#include "PDFPageWidget.h"
#include "QFrame"

class QPushButon;
class QWidget;
class QScrollArea;
class TableView: public QWidget
{
    Q_OBJECT
    public:
        TableView(QWidget *parent = 0);
        //QVector<PDFFile> files;
    protected:
    private:
        QScrollArea *scrollArea;
        QVBoxLayout *layout;
        QFrame *frame;
        QVBoxLayout *outerLayout;
        void paintEvent ( QPaintEvent * event );

};
#endif
