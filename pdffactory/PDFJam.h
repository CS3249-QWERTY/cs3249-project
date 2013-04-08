#ifndef PDFJAM_H
#define PDFJAM_H


class PDFJam//: public QThread
{
    //Q_OBJECT

public:
    PDFJam();

protected:
    void run();
private:
    volatile bool stopped;

};

#endif
