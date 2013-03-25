#ifndef PDFFACTORY_H
#define PDFFACTORY_H

#include <QMainWindow>

// Class declaration without loading .h files. Faster compilation.
class QAction;
class QToolBar;
class QTabWidget;
class QWidget;

class PDFFactory: public QMainWindow
{
    Q_OBJECT

public:
    PDFFactory();

    // Constant

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

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
};

#endif
