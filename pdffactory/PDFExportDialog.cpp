#include <QtGui>
#include <QtGlobal>
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
    connect(fileList, SIGNAL(currentRowChanged(int)), this, SLOT(fileListChanged(int)));
    fileListLayout->addWidget(fileList);
    fileListLayout->setContentsMargins(0, 20, 6, 6);
    fileListBox->setLayout(fileListLayout);
    mainLayout->addWidget(fileListBox, 0, 0, 4, 2);

    // is landscape
    landscapeBox = new QGroupBox("Landscape output");
    QVBoxLayout *landscapeLayout = new QVBoxLayout();
    chkLandscape = new QCheckBox("Landscape");
    connect(chkLandscape, SIGNAL(stateChanged(int)), this, SLOT(chkLandscapeChanged(int)));
    landscapeLayout->addWidget(chkLandscape);
    landscapeBox->setLayout(landscapeLayout);

    // n-up
    nupBox = new QGroupBox("N-up option");
    QGridLayout *nupLayout = new QGridLayout();
    QLabel *lblRow = new QLabel("Row:");
    QLabel *lblCol = new QLabel("Col:");
    txtRow = new QLineEdit("1");
    connect(txtRow, SIGNAL(textEdited(const QString &)), this, SLOT(txtRowChanged(const QString &)));
    txtCol = new QLineEdit("1");
    connect(txtCol, SIGNAL(textEdited(const QString &)), this, SLOT(txtColChanged(const QString &)));
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
    connect(txtLeftOffset, SIGNAL(textEdited(const QString &)), this, SLOT(txtLeftChanged(const QString &)));
    txtRightOffset = new QLineEdit("0");
    connect(txtRightOffset, SIGNAL(textEdited(const QString &)), this, SLOT(txtRightChanged(const QString &)));
    offsetLayout->addWidget(lblLeft, 0, 0, 1, 1);
    offsetLayout->addWidget(txtLeftOffset, 0, 1, 1, 2);
    offsetLayout->addWidget(lblRight, 1, 0, 1, 1);
    offsetLayout->addWidget(txtRightOffset, 1, 1, 1, 2);
    chkTwoSideOffset = new QCheckBox("Two Side Offset");
    connect(chkTwoSideOffset, SIGNAL(stateChanged(int)), this, SLOT(chkTwoSideChanged(int)));
    offsetLayout->addWidget(chkTwoSideOffset, 2, 0);
    offsetBox->setLayout(offsetLayout);

    QVBoxLayout *midLayout = new QVBoxLayout();
    midLayout->addWidget(landscapeBox);midLayout->addWidget(nupBox);midLayout->addWidget(offsetBox);
    midLayout->addStretch(1);
    midLayout->setSpacing(10);
    QFrame *midFrame = new QFrame();
    midFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    midFrame->setLayout(midLayout);
    mainLayout->addWidget(midFrame, 0, 2, 4, 2);

    // buttons
    QVBoxLayout *rightLayout = new QVBoxLayout();
    btnSave = new QPushButton("&Export...");
    connect(btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClicked()));
    rightLayout->addWidget(btnSave);
    btnSaveAll = new QPushButton("Export &all using\nthe same settings...");
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

void PDFExportDialog::fileListChanged(int row) {
    QVector<QVariant> option = options.at(row);
    chkLandscape->setChecked(option.at(0).toBool());
    txtRow->setText(QString::number(option.at(1).toInt()));
    txtCol->setText(QString::number(option.at(2).toInt()));
    txtLeftOffset->setText(QString::number(option.at(3).toInt()));
    txtRightOffset->setText(QString::number(option.at(4).toInt()));
    chkTwoSideOffset->setChecked(option.at(5).toBool());
}

void PDFExportDialog::txtRowChanged(const QString &txt) {
    bool ok;
    QVector<QVariant> option = options.at(fileList->currentRow());
    option.remove(1);
    option.insert(1, QVariant(txt.toInt(&ok)));
    options.remove(fileList->currentRow());
    options.insert(fileList->currentRow(), option);
}

void PDFExportDialog::txtColChanged(const QString &txt) {
    bool ok;
    QVector<QVariant> option = options.at(fileList->currentRow());
    option.remove(2);
    option.insert(2, QVariant(txt.toInt(&ok)));
    options.remove(fileList->currentRow());
    options.insert(fileList->currentRow(), option);
}

void PDFExportDialog::txtLeftChanged(const QString &txt) {
    bool ok;
    QVector<QVariant> option = options.at(fileList->currentRow());
    option.remove(3);
    option.insert(3, QVariant(txt.toInt(&ok)));
    options.remove(fileList->currentRow());
    options.insert(fileList->currentRow(), option);
}

void PDFExportDialog::txtRightChanged(const QString &txt) {
    bool ok;
    QVector<QVariant> option = options.at(fileList->currentRow());
    option.remove(4);
    option.insert(4, QVariant(txt.toInt(&ok)));
    options.remove(fileList->currentRow());
    options.insert(fileList->currentRow(), option);
}

void PDFExportDialog::chkLandscapeChanged(int state) {
    QVector<QVariant> option = options.at(fileList->currentRow());
    option.remove(0);
    option.insert(0, QVariant(chkLandscape->isChecked()));
    options.remove(fileList->currentRow());
    options.insert(fileList->currentRow(), option);
}

void PDFExportDialog::chkTwoSideChanged(int state) {
    QVector<QVariant> option = options.at(fileList->currentRow());
    option.remove(5);
    option.insert(5, QVariant(chkTwoSideOffset->isChecked()));
    options.remove(fileList->currentRow());
    options.insert(fileList->currentRow(), option);
}
