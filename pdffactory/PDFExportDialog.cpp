#include <QtGui>
#include "PDFExportDialog.h"

PDFExportDialog::PDFExportDialog(QWidget *parent) :
    QDialog(parent)
{
    mainLayout = new QGridLayout();
    mainLayout->setSpacing(15);

    // File list
    fileListBox = new QGroupBox("Referenced names");
    //fileListBox->setStyleSheet("QGroupBox {border: 1px solid palette(dark);}");
    QVBoxLayout *fileListLayout = new QVBoxLayout();
    fileList = new QListView();
    fileList->setWordWrap(true);
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
    mainLayout->addWidget(landscapeBox, 0, 2, 1, 2);

    // n-up
    nupBox = new QGroupBox("N-up option");
    QGridLayout *nupLayout = new QGridLayout();
    QLabel *lblRow = new QLabel("Row:");
    QLabel *lblCol = new QLabel("Col:");
    txtRow = new QLineEdit();
    txtCol = new QLineEdit();
    nupLayout->addWidget(lblRow, 0, 0, 1, 1);
    nupLayout->addWidget(txtRow, 0, 1, 1, 2);
    nupLayout->addWidget(lblCol, 1, 0, 1, 1);
    nupLayout->addWidget(txtCol, 1, 1, 1, 2);
    nupBox->setLayout(nupLayout);
    mainLayout->addWidget(nupBox, 1, 2, 1, 2);

    // offsets
    offsetBox = new QGroupBox("Offset option");
    QGridLayout *offsetLayout = new QGridLayout();
    QLabel *lblLeft = new QLabel("Left Offset:");
    QLabel *lblRight = new QLabel("Right Offset:");
    txtLeftOffset = new QLineEdit();
    txtRightOffset = new QLineEdit();
    offsetLayout->addWidget(lblLeft, 0, 0, 1, 1);
    offsetLayout->addWidget(txtLeftOffset, 0, 1, 1, 2);
    offsetLayout->addWidget(lblRight, 1, 0, 1, 1);
    offsetLayout->addWidget(txtRightOffset, 1, 1, 1, 2);
    chkTwoSideOffset = new QCheckBox("Two Side Offset");
    offsetLayout->addWidget(chkTwoSideOffset, 2, 0);
    offsetBox->setLayout(offsetLayout);
    mainLayout->addWidget(offsetBox, 2, 2, 1, 2);

    // buttons
    QVBoxLayout *rightLayout = new QVBoxLayout();
    btnSave = new QPushButton("&Export...");
    rightLayout->addWidget(btnSave);
    btnCancel = new QPushButton("C&ancel");
    rightLayout->addWidget(btnCancel);

    mainLayout->addLayout(rightLayout, 0, 4);

    setLayout(mainLayout);
    setGeometry(400, 400, 800, 450);
    setWindowTitle("Export to file");
}
