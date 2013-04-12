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
        void previewUpdate(Poppler::Page*);

    private slots:
        void fileRemoveButtonClicked(PDFFileWidget*);
        void pageClicked(PDFPageWidget*, QMouseEvent*, QString);
        void pageDropped(PDFPageWidget*, QDropEvent*, QString, QString);

        void fileClicked(PDFFileWidget*, QMouseEvent*);

    private:
        QVector<PDFPageWidget*> selectedPages;
        QVector<PDFFileWidget*> selectedFiles;
};
#endif
