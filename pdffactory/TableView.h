#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <poppler-qt4.h>

#include <QWidget>

class QPushButon;
class QScrollArea;
class QVBoxLayout;
class QSplitter;
class QFrame;
class QPaintEvent;
class QString;

class PDFFileWidget;

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
        QVector<QString>            fileNames;
        QVector<PDFFileWidget *>    fileWidgets;
};
#endif
