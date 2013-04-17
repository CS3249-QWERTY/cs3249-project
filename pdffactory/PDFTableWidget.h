#ifndef PDFTABLEWIDGET_H
#define PDFTABLEWIDGET_H

#include <poppler-qt4.h>
#include <PDFJam.h>

#include <QFrame>
#include <QHash>
#include "PDFPageWidget.h"

class QImage;
class QVBoxLayout;
class QString;
class QScrollArea;
class QMouseEvent;
class QPoint;

class PDFFileWidget;

class PDFTableWidget: public QFrame
{
    Q_OBJECT
    public:
        PDFTableWidget(QWidget *parent = 0);
        void loadFile (QString fileName);
        void registerPage(PDFPageWidget *child);

    protected:
        PDFJam pdfJam;

    private:
        QVBoxLayout     *outerLayout;
        QScrollArea     *scrollArea;
        QWidget         *containerWidget;
        QVBoxLayout     *containerLayout;

        QVector<Poppler::Document*> files;
        QVector<QString>            fileNames;
        QVector<PDFFileWidget*>     fileWidgets;

        QHash<QString, PDFPageWidget*> pageChilds;

    signals:
        void previewUpdate(Poppler::Page*, Poppler::Page::Rotation);
        void checkPreviewUpdate(Poppler::Page*, Poppler::Page::Rotation);

    private slots:
        void fileRemoveButtonClicked(PDFFileWidget*);
        void pageClicked(PDFPageWidget*, QMouseEvent*, QString);
        void pageDropped(PDFPageWidget*, QDropEvent*, QString, QString);

        void fileClicked(PDFFileWidget*, QMouseEvent*);

    public slots:
        void rotateSelectedPages();

    private:
        QVector<PDFPageWidget*> selectedPages;
        QVector<PDFFileWidget*> selectedFiles;

        QVector<PDFPageWidget*> copiedPages;
    public:
        QVector<PDFFileWidget*> getSelectedFiles();
        QVector<int> getSelectedIndices();
        QVector<QString> getSelectedFileNames();

        //bool operator()(PDFPageWidget* e1, PDFPageWidget* e2);

    public:
        void moveSelectedPages(QString, QString);
        void moveSelectedPages(QString, PDFPageWidget* page);
        void deletePage(PDFPageWidget* pageWidget);
        void copyPage(PDFPageWidget* pageWidget);
        void pastePage(PDFFileWidget* fileWidget, int pageID);
        void rotatePage(PDFPageWidget* pageWidget);
        void cutPage(PDFPageWidget* pageWidget);
        bool hasClipboard(){ return copiedPages.size() > 0; }

};
#endif
