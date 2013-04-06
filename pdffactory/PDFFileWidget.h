#ifndef FILE_FRAME_H
#define FILE_FRAME_H

#include <vector>
#include <poppler-qt4.h>

#include <QWidget>

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

class PDFPageWidget;

class FileWidget : public QWidget {

    Q_OBJECT
public:
    FileWidget(QWidget *parent = 0);
    QSize sizeHint() const;

    void    addChild(QString name);
    void    addChild(QImage *image);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    std::vector<PDFPageWidget*>     child;

    QHBoxLayout*                    mainLayout;

    int     findClickEventChild(QPoint pos);
    int     findChildPositionInLayout(PDFPageWidget *child);
    int     getChildCount() const;
};

class PDFFileWidget : public QWidget {

    Q_OBJECT
    Q_PROPERTY(bool collapsed READ isCollapsed WRITE setCollapsed)

public:
    PDFFileWidget(QWidget *parent = 0);
    //QSize sizeHint() const;

public:
    void setAncestor(QWidget* ancestor) { this->ancestor = ancestor; }
    void setDocument(Poppler::Document* document, QString filename);

    bool isCollapsed(){ return collapsed; }
    void setCollapsed(bool collapsed);

protected:

private slots:
    void collapsedButtonClick();

private:
    QGridLayout     *topLayout;

    QLabel          *widgetName;
    QPushButton     *collapseButton;
    QScrollArea     *scrollArea;
    FileWidget      *mainChild;
    QWidget         *ancestor;
    bool            collapsed;
};

#endif
