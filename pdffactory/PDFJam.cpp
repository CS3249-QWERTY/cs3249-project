#include <QtGlobal>
#include <QtGui>
#include <unistd.h>
#include "stdlib.h"
#include "PDFJam.h"

PDFJam::PDFJam()
{

}
//to make sure this folder exists
void PDFJam::makeFolder(QString path){
    QString temp = "mkdir -p %1 && rm %2*";
    int value = system(temp.arg(path).arg(path).toStdString().c_str());
    /*if (value != 0 )
        qDebug() << "ERROR: Failed to make " << path;*/
}

void PDFJam::pushCommand(QString cmd){
    mutex.lock();
    cmdQueue.push_back(cmd);
    mutex.unlock();
    if(!isRunning()) start();

}
//to rotate a page in a pdf file, clockwise direction
bool PDFJam::rotatePage(int fileIndex,int rotatedPageIndex,int degree){
    if ((degree!=90) && (degree!=180) && (degree!=270)){
        return false;
    }

    QString rtTemp = "pdf%1 /tmp/pdffactory/%2/%3.pdf --outfile /tmp/pdffactory/%4/%5.pdf ";
    QString cmd = rtTemp.arg(QString::number(degree)).arg(QString::number(fileIndex)).arg(QString::number(rotatedPageIndex)).arg(QString::number(fileIndex)).arg(QString::number(rotatedPageIndex));
    pushCommand(cmd);

}
//to remove a page in a pdf file
bool PDFJam::removePage(int fileIndex,int numPages, int deletedPageIndex){
    if ((deletedPageIndex<0)||(deletedPageIndex>=numPages)) {
        return false;
    }
    //QString temp = "file1.pdf '-' file2.pdf '1,2' file3.pdf '2-' --outfile output.pdf"
    QString rmTemp = "rm /tmp/pdffactory/%1/%2.pdf ";
    QString cmd = rmTemp.arg(QString::number(fileIndex)).arg(QString::number(deletedPageIndex));
    QString temp = "mv /tmp/pdffactory/%1/%2.pdf /tmp/pdffactory/%3/%4.pdf ";

    for (int i = deletedPageIndex+1; i < numPages; i++) {
        cmd += "&& " + temp.arg(QString::number(fileIndex)).arg(QString::number(i)).arg(QString::number(fileIndex)).arg(QString::number(i-1));
    }
    pushCommand(cmd);

}
//to export file number "fileIndex" to destination
void PDFJam::exportFile(int fileIndex,int numPages, QString dest){
    QString cmd = "pdfjam ";
    QString temp = "/tmp/pdffactory/%1/%2.pdf '-' ";

    for (int i = 0; i < numPages; i++) {
        cmd += temp.arg(QString::number(fileIndex)).arg(QString::number(i));
    }
    QString outTemp = "--outfile %1";
    cmd += outTemp.arg(dest);
    pushCommand(cmd);

}

void PDFJam::loadFile(QString fileName, int fileIndex,int numPages){
    QString path= "/tmp/pdffactory/%1/";
    path = path.arg(QString::number(fileIndex));
    makeFolder(path);

    QString temp = "pdfjam %1 %2 --outfile %3%4.pdf";
    QString cmd="";
    for (int i = 0; i < numPages; i++) {
        cmd += temp.arg(fileName).arg(QString::number(i+1)).arg(path).arg(QString::number(i)) + ";";
    }
    pushCommand(cmd);
}
QString PDFJam::nextCommand(){

    QString cmd;
    mutex.lock();
    cmd = cmdQueue.first();
    cmdQueue.pop_front();
    mutex.unlock();
    return cmd;
}
bool PDFJam::isQueueEmpty(){
    return (cmdQueue.size()==0);
}

void PDFJam::run(){
    while(!isQueueEmpty()){
        QString cmd = nextCommand();
        int value = system(cmd.toStdString().c_str());
        if (value != 0 )
            qDebug() << "ERROR: Failed to execute " << cmd;
        else
            qDebug() << "SUCCESS: executed " << cmd;
    }
}
