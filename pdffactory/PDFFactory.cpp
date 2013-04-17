#include <QtGui>
#include <QtGlobal>
#include "PDFFactory.h"
#include "PDFExportDialog.h"
#include "PDFTableWidget.h"
#include "PDFPreviewWidget.h"
#include "PDFPageWidget.h"

PDFFactory::PDFFactory()
{
    createWidgets();
    createActions();
    createToolBars();
    createRibbon();
    createStatusBar();
}

void PDFFactory::createWidgets()
{
    // Set central widget to be the container root
    centralWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(2,2,2,2);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Create ribbon
    ribbon = new QTabWidget();
    ribbon->addTab(new QWidget(), tr("File"));
    ribbon->addTab(new QWidget(), tr("Edit"));
    ribbon->addTab(new QWidget(), tr("Tools"));
    ribbon->addTab(new QWidget(), tr("Help"));
    ribbon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ribbon->setFixedHeight(100);
    layout->addWidget(ribbon);

    // Create main area (table)

    pdfTableView = new PDFTableWidget();
    pdfPreview = new PDFPreviewWidget();
    pdfPreview->setMinimumWidth(100);
    splitter = new QSplitter();
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(pdfTableView);
    splitter->addWidget(pdfPreview);
    QList<int> splitterWidgetSizes;
    splitterWidgetSizes << 900 << 400;
    splitter->setSizes(splitterWidgetSizes);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 0.5);
    layout->addWidget(splitter);

    connect(pdfTableView, SIGNAL(previewUpdate(Poppler::Page*, Poppler::Page::Rotation)), pdfPreview, SLOT(previewUpdate(Poppler::Page*, Poppler::Page::Rotation)));
    connect(pdfTableView, SIGNAL(checkPreviewUpdate(Poppler::Page*, Poppler::Page::Rotation)), pdfPreview, SLOT(checkPreviewUpdate(Poppler::Page*, Poppler::Page::Rotation)));

    setWindowIcon(QIcon(":/images/pdffactory.png"));
    setWindowTitle(tr("PDF Factory"));
    setGeometry(0, 0, 1300, 650);
}


void PDFFactory::createActions()
{
    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open a PDF"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    exportAction = new QAction(tr("&Export a single file"), this);
    exportAction->setIcon(QIcon(":/images/export.png"));
    exportAction->setShortcut(tr("Ctrl+S"));
    exportAction->setStatusTip(tr("Export the selected file to a new PDF"));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportFile()));

    exportAllAction = new QAction(tr("Export all"), this);
    exportAllAction->setIcon(QIcon(":/images/exportall.png"));
    exportAllAction->setShortcut(tr("Shift+Ctrl+S"));
    exportAllAction->setStatusTip(tr("Export all to multiple PDF files"));
    //connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    cutAction = new QAction(tr("C&ut"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut selected contents to clipboard"));
    connect(cutAction, SIGNAL(triggered()), pdfTableView, SLOT(cutSelected()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("Copy selected contents to clipboard"));
    connect(copyAction, SIGNAL(triggered()), pdfTableView, SLOT(copySelected()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("Paste clipboard's contents into current selection"));
    //connect(pasteAction, SIGNAL(triggered()), textEdit, SLOT(paste()));

    rotateAction = new QAction(tr("&Rotate"), this);
    rotateAction->setIcon(QIcon(":/images/rotate.png"));
    rotateAction->setShortcut(tr("Ctrl+R"));
    rotateAction->setStatusTip(tr("Rotate selected pages"));
    connect(rotateAction, SIGNAL(triggered()), pdfTableView, SLOT(rotateSelectedPages()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setIcon(QIcon(":/images/about.png"));
    aboutAction->setStatusTip(tr("About this program"));
}

void PDFFactory::createToolBars()
{
    fileToolBar = new QToolBar(tr("File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(exportAction);
    fileToolBar->addAction(exportAllAction);
    fileToolBar->setIconSize(QSize(48, 48));

    editToolBar = new QToolBar(tr("Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->setIconSize(QSize(48, 48));

    toolsToolBar = new QToolBar(tr("Tools"));
    toolsToolBar->addAction(rotateAction);
    toolsToolBar->setIconSize(QSize(48, 48));

    helpToolBar = new QToolBar(tr("Help"));
    helpToolBar->addAction(aboutAction);
    helpToolBar->setIconSize(QSize(48, 48));
}

void PDFFactory::createRibbon()
{
    QWidget *tabFile = ribbon->widget(0);
    QVBoxLayout *layoutTabFile = new QVBoxLayout();
    layoutTabFile->setContentsMargins(2,0,2,0);
    layoutTabFile->addWidget(fileToolBar);
    tabFile->setLayout(layoutTabFile);

    QWidget *tabEdit = ribbon->widget(1);
    QVBoxLayout *layoutTabEdit = new QVBoxLayout();
    layoutTabEdit->setContentsMargins(2,0,2,0);
    layoutTabEdit->addWidget(editToolBar);
    tabEdit->setLayout(layoutTabEdit);

    QWidget *tabTools = ribbon->widget(2);
    QVBoxLayout *layoutTabTools = new QVBoxLayout();
    layoutTabTools->setContentsMargins(2,0,2,0);
    layoutTabTools->addWidget(toolsToolBar);
    tabTools->setLayout(layoutTabTools);

    QWidget *tabHelp = ribbon->widget(3);
    QVBoxLayout *layoutTabHelp = new QVBoxLayout();
    layoutTabHelp->setContentsMargins(2,0,2,0);
    layoutTabHelp->addWidget(helpToolBar);
    tabHelp->setLayout(layoutTabHelp);
}

void PDFFactory::createStatusBar()
{
    statusBar()->showMessage(tr(""));
}

void PDFFactory::openFile() {
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
        tr("Open PDF file"), ".",
        tr("PDF file (*.pdf)"));

    for (int i = 0; i < fileNames.size(); i++) {
        QString fileName = fileNames.at(i);
        if (!fileName.isEmpty()) {
            pdfTableView->loadFile(fileName);
        }
    }
}

void PDFFactory::exportFile() {
    PDFExportDialog *exportDialog = new PDFExportDialog();

    QVector<PDFFileWidget*> selectedFiles = pdfTableView->getSelectedFiles();
    if (selectedFiles.size() > 0) {
        exportDialog->setFilesToExport(selectedFiles, pdfTableView->getSelectedFileNames(), pdfTableView->getSelectedIndices());
        exportDialog->show();
    }

}
