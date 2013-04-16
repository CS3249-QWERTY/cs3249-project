#ifndef FILE_FRAME_H
#define FILE_FRAME_H

#include <poppler-qt4.h>
#include "ThumbGen.h"

#include <QWidget>
#include <QFrame>

class QImage;
class QHBoxLayout;
class QGridLayout;
class QScrollArea;
class QPushButton;
class QLabel;
class QString;
class QSize;
class QPoint;
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
class QPaintEvent;
class ThumbGen;

class PDFPageWidget;

class PagesContainerWidget : public QWidget {

    Q_OBJECT

    public:
        PagesContainerWidget(QWidget *parent = 0);
        QSize sizeHint() const;
        QVector<PDFPageWidget*>         pageWidgets;
        QHBoxLayout                    *mainLayout;

        void addPageWidget(PDFPageWidget *pageWidget);
        void setAncestor(QWidget* ancestor){ this-> ancestor = ancestor;}

    protected:
        void dragEnterEvent(QDragEnterEvent *event);
        void dropEvent(QDropEvent *event);

    private:
        int getPagesCount() const;
        QWidget *ancestor;
};

// ========================================

class PDFFileWidget : public QFrame {

    Q_OBJECT
        Q_PROPERTY(bool collapsed READ isCollapsed WRITE setCollapsed)

    public:
        PDFFileWidget(QWidget *parent = 0);

    public:
        void setAncestor(QWidget* ancestor);
        void setDocument(Poppler::Document* document, QString fileName);
        int removeChild(PDFPageWidget* child);
        int indexChild(PDFPageWidget* child);
        void insertChildAt(PDFPageWidget* child, int pos);

        void setSelected(bool select);
        bool isSelected() {return selected;}
        bool isCollapsed(){ return collapsed; }
        void setCollapsed(bool collapsed);

    protected:
        void mousePressEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);

    private slots:
        void removeButtonClicked();
        void collapsedButtonClicked();
        void updateThumbnail(QImage,PDFPageWidget*);

    public :
        PagesContainerWidget *pagesContainerWidget;
    private:
        ThumbGen        tgen;
        QGridLayout     *topLayout;

        QLabel          *fileNameLabel;
        QPushButton     *collapseButton;
        QPushButton     *removeButton;
        QScrollArea     *scrollArea;
        QWidget         *ancestor;

        bool            collapsed;
        bool            selected;

    signals:
        void fileRemoveButtonClicked(PDFFileWidget*);
        void fileClicked(PDFFileWidget*, QMouseEvent*);
};

#endif
