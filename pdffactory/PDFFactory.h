#ifndef PDFFACTORY_H
#define PDFFACTORY_H

#include <QMainWindow>

class PDFTableWidget;
class PDFPreviewWidget;

class QAction;
class QWidget;
class QTabWidget;
class QScrollArea;
class QSplitter;
class QToolBar;

class PDFFactory: public QMainWindow
{
    Q_OBJECT

public:
    PDFFactory();

protected:
    //void closeEvent(QCloseEvent *event);

private slots:
    void openFile();
    void exportFile();
    void exportAllFiles();

private:
    void createWidgets();
    void createActions();
    void createToolBars();
    void createRibbon();
    void createStatusBar();

    QAction *openAction;
    QAction *exportAction;
    QAction *exportAllAction;
    QAction *cutAction;
	QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *rotateAction;
    QAction *aboutAction;

    QWidget *centralWidget;

    QTabWidget *ribbon;
    QSplitter *splitter;
    PDFTableWidget *pdfTableView;
    PDFPreviewWidget *pdfPreview;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *toolsToolBar;
    QToolBar *helpToolBar;
};

#endif
