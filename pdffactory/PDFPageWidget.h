#ifndef PDFPAGEWIDGET_H
#define PDFPAGEWIDGET_H

#include <poppler-qt4.h>
#include <QFrame>

class QWidget;
class QPushButton;
class QImage;
class QPixmap;
class QEvent;
class QMouseEvent;
class QPaintEvent;
class QDragEnterEvent;
class QDropEvent;
class QSize;
class QString;

class PDFPageWidget : public QFrame
{
    Q_OBJECT

public:
    PDFPageWidget(QWidget *parent = 0);
    QSize sizeHint() const;

    void setThumbnail(QImage pageImage);
    void setPopplerPage(Poppler::Page*);
    void setAncestor(QWidget *ancestor);
    void setFather(QWidget *father);
    QWidget* getFather() const { return father;}
    void registerName(QString name) { path = name;}
    QString getName() { return path;}

    void setSelected(bool select);
    bool isSelected() {return selected;}

protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    //QVector<QPushButton> buttons;
    QString         path;
    QWidget         *ancestor;
    QWidget         *father;

    QImage           image;
    Poppler::Page   *pPage;
    QPixmap          pixmap;
    QPushButton     *btnRotate, *btnCut, *btnCopy;

    bool selected;

signals:
    void pageClicked(PDFPageWidget*, QMouseEvent*, QString);
    void pageDropped(PDFPageWidget*, QDropEvent*, QString, QString);
    void previewUpdate(Poppler::Page* );
};

#endif // PDFPAGEWIDGET_H
