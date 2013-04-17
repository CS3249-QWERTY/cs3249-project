#include <QtGui>
#include "PDFJam.h"
#include "PDFExportDialog.h"

PDFExportDialog::PDFExportDialog(QWidget *parent) :
    QDialog(parent)
{
    mainLayout = new QGridLayout();
    mainLayout->setSpacing(15);

    // File list
    fileListBox = new QGroupBox("Referenced names");
    QVBoxLayout *fileListLayout = new QVBoxLayout();
    fileList = new QListWidget();
    fileList->setSelectionRectVisible(false);
    fileListLayout->addWidget(fileList);
    fileListLayout->setContentsMargins(0, 20, 6, 6);
    fileListBox->setLayout(fileListLayout);
    mainLayout->addWidget(fileListBox, 0, 0, 4, 2);

    // is landscape
    landscapeBox = new QGroupBox("Landscape output");
    QVBoxLayout *landscapeLayout = new QVBoxLayout();
    chkLandscape = new QCheckBox("Landscape");
    landscapeLayout->addWidget(chkLandscape);
    landscapeBox->setLayout(landscapeLayout);

    // n-up
    nupBox = new QGroupBox("N-up option");
    QGridLayout *nupLayout = new QGridLayout();
    QLabel *lblRow = new QLabel("Row:");
    QLabel *lblCol = new QLabel("Col:");
    txtRow = new QLineEdit("1");
    txtCol = new QLineEdit("1");
    nupLayout->addWidget(lblRow, 0, 0, 1, 1);
    nupLayout->addWidget(txtRow, 0, 1, 1, 2);
    nupLayout->addWidget(lblCol, 1, 0, 1, 1);
    nupLayout->addWidget(txtCol, 1, 1, 1, 2);
    nupBox->setLayout(nupLayout);

    // offsets
    offsetBox = new QGroupBox("Offset option");
    QGridLayout *offsetLayout = new QGridLayout();
    QLabel *lblLeft = new QLabel("Left Offset:");
    QLabel *lblRight = new QLabel("Right Offset:");
    txtLeftOffset = new QLineEdit("0");
    txtRightOffset = new QLineEdit("0");
    offsetLayout->addWidget(lblLeft, 0, 0, 1, 1);
    offsetLayout->addWidget(txtLeftOffset, 0, 1, 1, 2);
    offsetLayout->addWidget(lblRight, 1, 0, 1, 1);
    offsetLayout->addWidget(txtRightOffset, 1, 1, 1, 2);
    chkTwoSideOffset = new QCheckBox("Two Side Offset");
    offsetLayout->addWidget(chkTwoSideOffset, 2, 0);
    offsetBox->setLayout(offsetLayout);

    QVBoxLayout *midLayout = new QVBoxLayout();
    midLayout->addWidget(landscapeBox);midLayout->addWidget(nupBox);midLayout->addWidget(offsetBox);
    midLayout->addStretch(1);
    mainLayout->addLayout(midLayout, 0, 2, 4, 2);

    // buttons
    QVBoxLayout *rightLayout = new QVBoxLayout();
    btnSave = new QPushButton("&Export...");
    connect(btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClicked()));
    rightLayout->addWidget(btnSave);
    btnSaveAll = new QPushButton("Export &all...");
    connect(btnSaveAll, SIGNAL(clicked()), this, SLOT(btnSaveAllClicked()));
    rightLayout->addWidget(btnSaveAll);
    btnCancel = new QPushButton("&Cancel");
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(btnCancelClicked()));
    rightLayout->addWidget(btnCancel);
    rightLayout->addStretch(1);
    mainLayout->addLayout(rightLayout, 0, 4, 2, 1);

    setLayout(mainLayout);
    setGeometry(400, 400, 800, 450);
    setWindowTitle("Export to file");
}

void PDFExportDialog::setFilesToExport(QVector<PDFFileWidget*> fileWidgets, QVector<QString> fileNames, QVector<int> fileIndices) {
    this->fileWidgets = fileWidgets;
    this->fileNames = fileNames;
    this->fileIndices = fileIndices;

    QStringList modelList;
    foreach (const QString str, fileNames) {
        modelList << str;

        QVector<QVariant> option; // Landscape, row, col, left, right, twosided
        bool ok;
        option.append(QVariant(chkLandscape->isChecked()));
        option.append(QVariant(txtRow->text().toInt(&ok)));
        option.append(QVariant(txtCol->text().toInt(&ok)));
        option.append(QVariant(txtLeftOffset->text().toInt(&ok)));
        option.append(QVariant(txtRightOffset->text().toInt(&ok)));
        option.append(QVariant(chkTwoSideOffset->isChecked()));

        options.append(option);
    }

    fileList->addItems(modelList);
}

void PDFExportDialog::btnSaveClicked() {
    PDFJam *pdfJam = new PDFJam();

    int selectedIndex = fileList->currentRow();

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save PDF file"), ".",
                                                    tr("PDF file (*.pdf)"));
    if (!fileName.isEmpty())
        pdfJam->exportFile(fileIndices.at(selectedIndex), fileWidgets.at(selectedIndex)->getChildCount(), fileName,
                           QSize(options.at(selectedIndex).at(1).toInt(), options.at(selectedIndex).at(2).toInt()),
                           options.at(selectedIndex).at(0).toBool(), options.at(selectedIndex).at(5).toBool(),
                           options.at(selectedIndex).at(3).toInt(), options.at(selectedIndex).at(4).toInt());
}

void PDFExportDialog::btnSaveAllClicked() {

}

void PDFExportDialog::btnCancelClicked() {

}
