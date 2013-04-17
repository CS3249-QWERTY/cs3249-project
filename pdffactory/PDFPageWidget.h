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
    void rotate90();
    Poppler::Page::Rotation getRotation();
    QWidget* getFather() const { return father;}
    void registerName(QString name) { path = name;}
    QString getName() { return path;}

    void setSelected(bool select);
    bool isSelected() {return selected;}

    Poppler::Page* getPage(){return pPage;}

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
    QPushButton     *btnRotate, *btnCut, *btnCopy, *btnDelete;

    int             rotation;

    bool selected;

signals:
    void pageClicked(PDFPageWidget*, QMouseEvent*, QString);
    void pageDropped(PDFPageWidget*, QDropEvent*, QString, QString);

private slots:
    void pageDelete();
    void pageCopy();
    void pageRotate();
    void pageCut();
};

#endif // PDFPAGEWIDGET_H
