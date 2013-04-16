#ifndef PDFJAM_H
#define PDFJAM_H

#include <QThread>
#include <QMutex>
#include <poppler-qt4.h>
#include <QImage>
class PDFPageWidget;
class QImage;

class PDFJam: public QThread
{
    Q_OBJECT
public:
    PDFJam();
    void pushCommand(QString);
    void loadFile(QString fileName,int,Poppler::Document*);
    void exportFile(int ,int , QString , QSize , bool , bool, int ,int );
    void savePageAsImage(Poppler::Page pp, QString dest, double);
    void movePage(int , int , int , int , int , int );

    void pastePage(int ,int , int ,int);
    void copyPage(int ,int , int , int );
    void cutPage(int ,int , int ,int);

    bool removePage(int ,int , int );
    bool rotatePage(int,int,int);
    void makeFolder(QString);
protected:
    void run();
private:
    QVector<QString> cmdQueue;
    QString nextCommand();
    bool isQueueEmpty();
    QMutex mutex;

};

#endif
