#ifndef PDFFACTORY_H
#define PDFFACTORY_H

#include <QMainWindow>
#include <TableView.h>

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
    //void openFile();
    //bool exportFile();
    //bool exportAllFiles();

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
    QAction *aboutAction;

    QWidget *centralWidget;

    QTabWidget *ribbon;
    QScrollArea *scrollArea;
    TableView *pdfTableView;
    QSplitter *splitter;
    QWidget *pdfPreview;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *helpToolBar;
};

#endif
