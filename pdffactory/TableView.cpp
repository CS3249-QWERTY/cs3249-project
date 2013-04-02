#include <QtGui>
#include "TableView.h"
#include "QWidget"
#include <assert.h>
#include "PDFPageWidget.h"

#include "PDFFileWidget.h"

PDFFileWidget* test[10];

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
    frame->adjustSize();
    loadFile("/home/navieh/test.pdf");
}

void TableView::loadFile ( QString  fileName ){

    filenames.append(fileName);
    Poppler::Document *doc = Poppler::Document::load(fileName);
    files.append(doc);
    PDFFileWidget *pfw = new PDFFileWidget();
    pfw->setAncestor(this);
    pfw->setDocument(doc,fileName);

    fileWidgets.append(pfw);
    layout->addWidget(pfw);
}
void TableView::paintEvent ( QPaintEvent * event ){
    frame->adjustSize();
    int newWidth = width() - 50;
    for (int i = 0; i < fileWidgets.size(); i++) {
        fileWidgets.at(i)->resize(newWidth,fileWidgets.at(i)->height());
    }
    frame->resize(newWidth,frame->height());
}
