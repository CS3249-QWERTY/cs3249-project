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
    void loadFile(QString fileName,int,int);
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
