#include <QtGui>
#include "TableView.h"
#include "QWidget"
#include <assert.h>
#include "PDFPageWidget.h"

#include "FileFrameWidget.h"

FileFrameWidget* test[10];

// Constructor
TableView::TableView(QWidget* parent) : QWidget(parent)
{
    outerLayout = new QVBoxLayout();
    scrollArea = new QScrollArea();
    frame = new QFrame(scrollArea);
    layout = new QVBoxLayout();
    setLayout(outerLayout);
    outerLayout->addWidget(scrollArea);
    scrollArea->setWidget(frame);
    frame->setLayout(layout);
    frame->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    int i =0;

    //TODO: page widget is placed for testing only
    //to remove pagewidget and add filewidgets later
    //use QVector<PDFFile> files to store files
    /*
    for (i = 0; i < 10; i++) {
        test[i] = new PDFPageWidget();
        test[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

        layout->addWidget(test[i]);
    }*/

    for (i = 0; i < 10; i++) {
        test[i] = new FileFrameWidget();
        //test[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);

        layout->addWidget(test[i]);
    }
    // end of TODO
    frame->adjustSize();

}

void TableView::paintEvent ( QPaintEvent * event ){
    frame->adjustSize();
    int newWidth = width();
    for (int i = 0; i < 10; i++) {
        test[i]->resize(newWidth,test[i]->height());
    }
    frame->resize(newWidth,frame->height());
}
