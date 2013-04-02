#ifndef FILE_FRAME_H
#define FILE_FRAME_H

#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

#include "FileWidget.h"

class FileFrameWidget : public QWidget{

    Q_OBJECT
    Q_PROPERTY(bool collapsed READ isCollapsed WRITE setCollapsed)

public:
    FileFrameWidget(QWidget *parent = 0);
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
