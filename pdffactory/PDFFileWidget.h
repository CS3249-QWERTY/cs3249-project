#ifndef FILE_FRAME_H
#define FILE_FRAME_H

#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QImage>
#include <QString>
#include <QPoint>

#include <vector>

#include "PDFPageWidget.h"

class FileWidget : public QWidget{
    Q_OBJECT
public:
    FileWidget(QWidget *parent = 0);
    QSize sizeHint() const;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    std::vector<PDFPageWidget*>     child;

    QHBoxLayout*                    mainLayout;

    void    addChild(QString name);
    int     findClickEventChild(QPoint pos);
    int     findChildPositionInLayout(PDFPageWidget *child);
    int     getChildCount() const;
};

class PDFFileWidget : public QWidget{

    Q_OBJECT
    Q_PROPERTY(bool collapsed READ isCollapsed WRITE setCollapsed)

public:
    PDFFileWidget(QWidget *parent = 0);
    QSize sizeHint() const;

public:
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
    FileWidget  *mainChild;

    bool            collapsed;
};

#endif
