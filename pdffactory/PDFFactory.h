#ifndef PDFFACTORY_H
#define PDFFACTORY_H

#include <QMainWindow>

class QAction;
class QWidget;
class QTabWidget;
class QScrollArea;

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
    QWidget *pdfTableView;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *helpToolBar;
};

#endif
