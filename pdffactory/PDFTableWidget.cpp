#include <QtGui>

#include "PDFTableWidget.h"
#include "PDFPageWidget.h"
#include "PDFFileWidget.h"
#include <QtAlgorithms>
#include "PDFJam.h"

// Constructor
PDFTableWidget::PDFTableWidget(QWidget* parent) : QFrame(parent)
{
    // Frame (Expanding with VBox) - Scroll Area (Expanding) - Container (Expanding with VBox) - Children

    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    outerLayout = new QVBoxLayout();
    outerLayout->setContentsMargins(0,0,0,0);

    scrollArea = new QScrollArea();
    scrollArea -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea -> setWidgetResizable(true);
    scrollArea -> setFrameStyle(QFrame::Plain);

    containerLayout = new QVBoxLayout();
    containerLayout -> setSpacing(10);
    containerWidget = new QWidget();
    containerWidget -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *spacer = new QWidget();
    spacer -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    containerLayout -> addWidget(spacer);
    containerWidget -> setLayout(containerLayout);

    scrollArea -> setWidget(containerWidget);

    outerLayout -> addWidget(scrollArea);

    setLayout(outerLayout);
}

void PDFTableWidget::loadFile(QString fileName){
    Poppler::Document *doc = Poppler::Document::load(fileName);
    files.append(doc);

    PDFFileWidget *fileWidget = new PDFFileWidget();
    fileWidget->setAncestor(this);
    fileWidget->setDocument(doc,fileName);
    pdfJam.loadFile(fileName,files.size()-1,doc);

    fileWidgets.append(fileWidget);
    fileNames.append(fileName);

    containerLayout->insertWidget(containerLayout->count() - 1, fileWidget);
    connect(fileWidget, SIGNAL(fileRemoveButtonClicked(PDFFileWidget*)), this, SLOT(fileRemoveButtonClicked(PDFFileWidget*)));
}

QVector<PDFFileWidget*> PDFTableWidget::getSelectedFiles() {
    return selectedFiles;
}

QVector<int> PDFTableWidget::getSelectedIndices() {
    QVector<int> retVector;
    for (int i = 0; i < selectedFiles.size(); i++) {
        retVector.append(fileWidgets.indexOf(selectedFiles.at(i)));
    }
    return retVector;
}

QVector<QString> PDFTableWidget::getSelectedFileNames() {
    QVector<QString> retVector;
    QVector<int> indices = getSelectedIndices();
    for (int i = 0; i < indices.size(); i++) {
        retVector.append(fileNames.at(indices.at(i)));
    }
    return retVector;
}

void PDFTableWidget::registerPage(PDFPageWidget* child){
    //come up with a new name here
    QString name = QString("/home/pdfpage").append(QString::number(pageChilds.size()));
    qDebug()<<"Registering name:";
    qDebug()<<name;
    pageChilds[name] = child;
    child->registerName(name);
}

void PDFTableWidget::fileClicked(PDFFileWidget* sender, QMouseEvent* event) {
    if (event->button() == Qt::LeftButton){
        if (event->modifiers() != Qt::ControlModifier) {
            for (int i = 0; i < selectedFiles.size(); i++) {
                selectedFiles.at(i)->setSelected(false);
            }

            selectedFiles.clear();

            if (!sender->isSelected()) {
                sender->setSelected(true);
                selectedFiles.append(sender);
            }
        } else {
            if (!sender->isSelected()) {
                sender->setSelected(true);
                selectedFiles.append(sender);
            } else {
                sender->setSelected(false);
                selectedFiles.remove(selectedFiles.indexOf(sender));
            }
        }
    }
}

void PDFTableWidget::fileRemoveButtonClicked(PDFFileWidget* sender) {
    selectedFiles.remove(selectedFiles.indexOf(sender));

    QVector<int> pagesToRemove;
    for (int i = 0; i < selectedPages.size(); i++) {
        if (selectedPages.at(i)->getFather() == sender) {
            pagesToRemove.append(i);
        }
    }

    for (int i = 0; i < pagesToRemove.size(); i++) {
        selectedPages.remove(pagesToRemove.at(i));
    }

    // Handle remove file

}

void PDFTableWidget::pageClicked(PDFPageWidget *sender, QMouseEvent* event, QString path){
    if (event->button() == Qt::LeftButton){
        // Handle selection
        if (selectedPages.size() > 0 && event->modifiers() != Qt::ControlModifier) {
            // Handle drag
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;

            mimeData->setText(path);
            drag->setMimeData(mimeData);
            drag->setPixmap(QPixmap(":/images/copy.png"));

            drag->exec();

        } else {
            if (!sender->isSelected()) {
                sender->setSelected(true);

                PDFFileWidget* senderF = (PDFFileWidget*)sender->getFather();
                int senderPID = senderF->indexChild(sender);
                int senderFID = fileWidgets.indexOf(senderF);

                int i = 0;
                for (i = 0;i<selectedPages.size();i++){
                    PDFPageWidget* target = selectedPages.at(i);
                    PDFFileWidget* targetF = (PDFFileWidget*)target->getFather();
                    int targetPID = targetF->indexChild(target);
                    int targetFID = fileWidgets.indexOf(targetF);

                    if (targetFID == senderFID && targetFID > senderFID)
                        break;

                    if (targetFID > senderFID)
                        break;
                }

                selectedPages.insert(i,sender);
            } else {
                sender->setSelected(false);
                selectedPages.remove(selectedPages.indexOf(sender));
            }
        }
    }

    if (event->button() == Qt::RightButton){
        for (int i = 0; i < selectedPages.size(); i++) {
                selectedPages.at(i)->setSelected(false);
            }
        selectedPages.clear();
    }
}

void PDFTableWidget::pageDropped(PDFPageWidget *sender, QDropEvent *event, QString pathFrom, QString pathTo){
    moveSelectedPages(pathFrom, pathTo);
}

void PDFTableWidget::moveSelectedPages(QString pathFrom, PDFPageWidget* page){
    moveSelectedPages(pathFrom, page->getName());
}

void PDFTableWidget::moveSelectedPages(QString pathFrom, QString pathTo){
    if (selectedPages.size() == 0)
        return;

    bool accept = false;
    for (int i = 0;i<selectedPages.size();i++)
        if (selectedPages.at(i)->getName() == pathFrom)
            accept=true;
    if (!accept)
        return;

    for (int i = 0;i<selectedPages.size();i++)
        if (selectedPages.at(i)->getName() == pathTo)
            return;

    PDFPageWidget* childTo  = pageChilds[pathTo];
    PDFFileWidget* fileTo   = (PDFFileWidget*) childTo->getFather();

    for (int i = selectedPages.size() - 1; i>=0 ;i--){
        PDFPageWidget* childFrom    = selectedPages[i];
        PDFFileWidget* fileFrom     = (PDFFileWidget*) childFrom->getFather();

        pdfJam.cutPage(
                fileWidgets.indexOf(fileFrom),
                fileFrom->pagesContainerWidget->pageWidgets.size(),
                fileFrom->indexChild(childFrom),
                i
                );

                fileFrom->removeChild(childFrom);

    }
    int posTo               = fileTo->indexChild(childTo);
    for (int i = selectedPages.size() - 1; i>=0 ;i--){
        pdfJam.pastePage(
                fileWidgets.indexOf(fileTo),
                fileTo->pagesContainerWidget->pageWidgets.size(),
                posTo,
                i
                );

        PDFPageWidget* childFrom    = selectedPages[i];
        PDFFileWidget* fileFrom     = (PDFFileWidget*) childFrom->getFather();
        fileTo->insertChildAt(childFrom, posTo);

                //fileFrom->insertChildAt(childTo, posFrom);
    }
}
