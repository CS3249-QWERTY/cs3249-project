#include <QtGui>
#include "PDFFactory.h"

// Constructor

PDFFactory::PDFFactory()
{
    createWidgets();
    createActions();
    createToolBars();
    createRibbon();
    createStatusBar();
}


// Protected methods

void PDFFactory::closeEvent(QCloseEvent *event)
{
    event->accept();
}


// Create widgets, actions, menus, toolbars, status bar.

void PDFFactory::createWidgets()
{

    //setCentralWidget(textEdit);
    //setWindowIcon(QIcon(":/images/PDFFactory.png"));
    setGeometry(0, 0, 550, 650);
}


void PDFFactory::createActions()
{    
    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open an existing file"));
    //connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    
    exportAction = new QAction(tr("&Save"), this);
    exportAction->setIcon(QIcon(":/images/save.png"));
    exportAction->setShortcut(tr("Ctrl+S"));
    exportAction->setStatusTip(tr("Save the document to a file"));
    //connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    
    exportAllAction = new QAction(tr("Sa&ve as..."), this);
    exportAllAction->setIcon(QIcon(":/images/saveas.png"));
    exportAllAction->setShortcut(tr("Shift+Ctrl+S"));
    exportAllAction->setStatusTip(tr("Save the document to a new file"));
    //connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    cutAction = new QAction(tr("C&ut"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut selected contents to clipboard"));
    //connect(cutAction, SIGNAL(triggered()), textEdit, SLOT(cut()));
    
	copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("Copy selected contents to clipboard"));
    //connect(copyAction, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("Paste clipboard's contents into current"
                                 "selection"));
    //connect(pasteAction, SIGNAL(triggered()), textEdit, SLOT(paste()));
    
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show information about this PDFFactory"));
    //connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    
    // Other connections
    cutAction->setEnabled(false);
    //connect(textEdit, SIGNAL(copyAvailable(bool)),
            //cutAction, SLOT(setEnabled(bool)));
   // connect(textEdit->document(), SIGNAL(contentsChanged()),
            //this, SLOT(isModified()));
}

void PDFFactory::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(exportAction);
    fileToolBar->addAction(exportAllAction);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
}


void PDFFactory::createRibbon()
{

}


void PDFFactory::createStatusBar()
{
    statusBar()->showMessage(tr(""));
}

