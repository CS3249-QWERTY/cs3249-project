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
void PDFJam::cutPage(int fileIndex,int numPages, int pageIndex,int slot=0) {
    qDebug()<<"cuting page"<<fileIndex << " " << pageIndex;
    if ((pageIndex<0)||(pageIndex>=numPages)) {
        return ;
    }

    copyPage(fileIndex,numPages,pageIndex,slot);
    removePage(fileIndex,numPages,pageIndex);

}
void PDFJam::copyPage(int fileIndex,int numPages, int pageIndex,int slot=0){
    QString cpTemp = "cp /tmp/pdffactory/%1/%2.pdf /tmp/pdffactory/clipboard%3.pdf";
    QString cmd = cpTemp.arg(QString::number(fileIndex)).arg(QString::number(pageIndex)).arg(QString::number(slot));
    pushCommand(cmd);
}
void PDFJam::pastePage(int fileIndex,int numPages, int pageIndex, int slot=0){
    qDebug()<<"pasting page"<<fileIndex << " " << pageIndex<<slot;
    //TODO: check if clipboard file exists
    QString cmd = "";
    QString mvTemp = "mv /tmp/pdffactory/%1/%2.pdf /tmp/pdffactory/%3/%4.pdf ";
    for (int i = numPages-1; i >= pageIndex; i--) {
        cmd += mvTemp.arg(QString::number(fileIndex)).arg(QString::number(i)).arg(QString::number(fileIndex)).arg(QString::number(i+1));
        if (i>pageIndex) cmd+=" && ";
    }

    QString pasteTemp = "cp /tmp/pdffactory/clipboard%1.pdf /tmp/pdffactory/%2/%3.pdf ";
    cmd += " && " + pasteTemp.arg(QString::number(slot)).arg(QString::number(fileIndex)).arg(QString::number(pageIndex));
    pushCommand(cmd);

}
void PDFJam::movePage(int fromFileIndex, int fromFileNumPage, int fromPageIndex, int toFileIndex, int toFileNumPage, int toPageIndex ){
    //TODO:back up clipboard
    //if this is page moving within files, update to file Index.
    if (toFileIndex == fromFileIndex) {
        toFileNumPage--;
        if(toPageIndex>fromPageIndex)
            toPageIndex--;
        toPageIndex--;
    }
    cutPage(fromFileIndex,fromFileNumPage,fromPageIndex,0);
    pastePage(toFileIndex,toFileNumPage,toPageIndex,0);
}
void PDFJam::savePageAsImage(Poppler::Page pp, QString dest,double dpi = 72){

}
//to export file number "fileIndex" to destination
//supported n-up, orientation, offset options
void PDFJam::exportFile(int fileIndex,int numPages, QString dest, QSize nup = QSize(1,1), bool isLandscape = false, bool hasTwoSideOffset = false, int leftOffset=0, int rightOffset =0){

    QString cmd = "pdfjam ";
    QString temp = "/tmp/pdffactory/%1/%2.pdf '-' ";

    for (int i = 0; i < numPages; i++) {
        cmd += temp.arg(QString::number(fileIndex)).arg(QString::number(i));
    }
    QString orientation = isLandscape?" --landscape ": " --no-landscape ";
    cmd += orientation;
    if ((nup.width()==1)||(nup.height()!=1)) {
        QString nupTemp = " --nup '%1x%2' --frame true ";
        cmd += nupTemp.arg(QString::number(nup.width())).arg(QString::number(nup.height()));
    }


    QString outTemp = " --outfile %1 ";
    cmd += outTemp.arg(dest);
    pushCommand(cmd);
    //offset after this


}


void PDFJam::loadFile(QString fileName, int fileIndex,Poppler::Document* pd){
    int numPages = pd->numPages();
    QString path= "/tmp/pdffactory/%1/";
    path = path.arg(QString::number(fileIndex));
    makeFolder(path);

    QString temp = "pdfjam %1 %2 --outfile %3%4.pdf %5";
    QString cmd="";
    for (int i = 0; i < numPages; i++) {
        QString orientation = " --no-landscape ";
        QSizeF pageSize = pd->page(i)->pageSizeF();
        if(pageSize.width() > pageSize.height()){
            orientation = " --landscape ";
        }
        cmd += temp.arg(fileName).arg(QString::number(i+1)).arg(path).arg(QString::number(i)).arg(orientation) + " ; ";
    }
    pushCommand(cmd);

/*
    //test all backend functions
    rotatePage(0,5,270);
    movePage(0,numPages,5,0,numPages,10);
    //removePage(0,numPages,5);
    exportFile(0,numPages,"/home/navieh/Desktop/conco.pdf",QSize(2,2),true,true,1,0);
*/
    //end of test
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
        /*
            //qDebug() << "ERROR: Failed to execute " << cmd;
        //else
            //qDebug() << "SUCCESS: executed " << cmd;
            qDebug() << "SUCCESS: executed " << cmd;*/
    }
}
