#ifndef PDFFILE_H
#define PDFFILE_H

#include <QObject>
#include <poppler-qt4.h>

class QString;
class QImage;

class PDFFile: public QObject
{
    Q_OBJECT

public:
    PDFFile(const QString &fileName);
    QImage* getPageImage(int pageNumber);

private:
    Poppler::Document *document;
    QString fileName;

};

#endif // PDFFILE_H
