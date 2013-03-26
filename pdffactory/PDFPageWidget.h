#ifndef PDFPAGEWIDGET_H
#define PDFPAGEWIDGET_H

#include <QWidget>

class QImage;
class QPixmap;
class QPaintEvent;

class PDFPageWidget : public QWidget
{
    Q_OBJECT

public:
    PDFPageWidget(QWidget *parent = 0);
    void setPageImage(QImage *pageImage);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QImage *image;
    QPixmap pixmap;
};

#endif // PDFPAGEWIDGET_H
