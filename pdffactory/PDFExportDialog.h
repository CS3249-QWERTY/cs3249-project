#ifndef PDFEXPORTDIALOG_H
#define PDFEXPORTDIALOG_H

#include <QDialog>
#include "PDFFileWidget.h"

class QGridLayout;
class QGroupBox;
class QListWidget;
class QLineEdit;
class QCheckBox;

class PDFExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PDFExportDialog(QWidget *parent = 0);

private:
    QVector<PDFFileWidget*> fileWidgets;
    QVector<QString> fileNames;
    QVector<int> fileIndices;
    QVector<QVector<QVariant> > options;

private:
    QGroupBox *fileListBox, *landscapeBox, *nupBox, *offsetBox;

    QPushButton *btnSave, *btnSaveAll, *btnCancel;
    QGridLayout *mainLayout;

    QListWidget *fileList;
    QLineEdit *txtRow, *txtCol;
    QCheckBox *chkLandscape;
    QLineEdit *txtLeftOffset, *txtRightOffset;
    QCheckBox *chkTwoSideOffset;

public:
    void setFilesToExport(QVector<PDFFileWidget*> fileWidgets, QVector<QString> fileNames, QVector<int> fileIndices);

private slots:
    void btnSaveClicked();
    void btnSaveAllClicked();
    void btnCancelClicked();
};

#endif // PDFEXPORTDIALOG_H
