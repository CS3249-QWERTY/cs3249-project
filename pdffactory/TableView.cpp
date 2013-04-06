#include <QtGui>

#include "TableView.h"
#include "PDFPageWidget.h"
#include "PDFFileWidget.h"

// Constructor
TableView::TableView(QWidget* parent) : QFrame(parent)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    outerLayout = new QVBoxLayout();
    outerLayout->setContentsMargins(0,0,0,0);

    // Spacer item
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    outerLayout->addWidget(spacer);

    setLayout(outerLayout);

    loadFile("/home/zuyetawarmatik/Desktop/imagewidget2.pdf");
}

void TableView::loadFile (QString fileName){
    fileNames.append(fileName);

    Poppler::Document *doc = Poppler::Document::load(fileName);
    files.append(doc);

    PDFFileWidget *pfw = new PDFFileWidget();
    pfw->setAncestor(this);
    pfw->setDocument(doc,fileName);

    fileWidgets.append(pfw);

    outerLayout->insertWidget(outerLayout->count() - 1, pfw);
}
