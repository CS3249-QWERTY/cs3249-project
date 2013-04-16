#ifndef PDFEXPORTDIALOG_H
#define PDFEXPORTDIALOG_H

#include <QDialog>

class QGridLayout;
class QGroupBox;
class QListView;
class QLineEdit;
class QCheckBox;

class PDFExportDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PDFExportDialog(QWidget *parent = 0);
    
private:
    QGroupBox *fileListBox, *landscapeBox, *nupBox, *offsetBox;

    QPushButton *btnSave, *btnCancel;
    QGridLayout *mainLayout;

    QListView *fileList;
    QLineEdit *txtRow, *txtCol;
    QCheckBox *chkLandscape;
    QLineEdit *txtLeftOffset, *txtRightOffset;
    QCheckBox *chkTwoSideOffset;


public:
    void setFilesToExport(QVector<QString> fileNames, QVector<int> fileIndices, QVector<int> pageCounts);
};

#endif // PDFEXPORTDIALOG_H
