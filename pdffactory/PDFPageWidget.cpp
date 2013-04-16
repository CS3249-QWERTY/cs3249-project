#include <QtGlobal>
#include <QtGui>
#include "PDFPageWidget.h"
#include "PDFTableWidget.h"

PDFPageWidget::PDFPageWidget(QWidget *parent) :
    QFrame(parent)
{
    selected = false;
    setAcceptDrops(true);

    this->resize(150, 150);
    this->setMinimumSize(150, 150);
    this->setMaximumSize(150, 150);
    this->setAutoFillBackground(true);

    this->setMouseTracking(true);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QHBoxLayout *topHBox = new QHBoxLayout();
    btnRotate = new QPushButton("", this);
    btnRotate->setObjectName("rotate");
    btnRotate->setIcon(QPixmap::fromImage(QImage("images/rotate.png")));
    btnRotate->hide();
    topHBox->addWidget(btnRotate, 0, Qt::AlignLeft);

    QHBoxLayout *bottomHBox = new QHBoxLayout();
    btnCut = new QPushButton("", this);
    btnCut->setObjectName("cut");
    btnCut->setIcon(QPixmap::fromImage(QImage("images/cut.png")));
    btnCut->hide();

    btnCopy = new QPushButton("", this);
    btnCopy->setObjectName("copy");
    btnCopy->setIcon(QPixmap::fromImage(QImage("images/copy.png")));
    btnCopy->hide();

    bottomHBox->addWidget(btnCut, 0, Qt::AlignLeft);
    bottomHBox->addWidget(btnCopy, 1, Qt::AlignRight);

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addLayout(topHBox);
    vbox->addStretch(1);
    vbox->addLayout(bottomHBox);
    vbox->setContentsMargins(0, 3, 0, 3);
    this->setLayout(vbox);
}

void PDFPageWidget::setAncestor(QWidget* ancestor){
    this->ancestor = ancestor;
    ((PDFTableWidget*)ancestor)->registerPage(this);
    connect(this, SIGNAL(previewUpdate(Poppler::Page*)), ancestor, SIGNAL(previewUpdate(Poppler::Page*)));
    connect(this, SIGNAL(pageClicked(PDFPageWidget*, QMouseEvent*, QString)), ancestor, SLOT(pageClicked(PDFPageWidget*, QMouseEvent*, QString)));
    connect(this, SIGNAL(pageDropped(PDFPageWidget*, QDropEvent*, QString, QString)), ancestor, SLOT(pageDropped(PDFPageWidget*, QDropEvent*, QString, QString)));
}

void PDFPageWidget::setFather(QWidget *father){
    this->father = father;
}

void PDFPageWidget::setPopplerPage(Poppler::Page* pp) {
    pPage = pp;
}

void PDFPageWidget::setThumbnail(QImage pageImage) {
    image = pageImage;
    pixmap = QPixmap::fromImage(image);
    pixmap = pixmap.scaled(size() - QSize(6, 6), Qt::KeepAspectRatio);

    update();
}

void PDFPageWidget::setSelected(bool select) {
    selected = select;
    update();
}

void PDFPageWidget::mousePressEvent(QMouseEvent *event) {
    if (pPage!=NULL){
        emit pageClicked(this, event, path);
        emit previewUpdate(pPage);
    }
}

void PDFPageWidget::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void PDFPageWidget::dropEvent(QDropEvent *event) {
    emit pageDropped(this, event, event->mimeData()->text(), path);
    event->acceptProposedAction();
}

void PDFPageWidget::leaveEvent(QEvent *event) {
    btnRotate->hide();
    btnCut->hide();
    btnCopy->hide();

    this->setFrameStyle(QFrame::Plain);
}

void PDFPageWidget::enterEvent(QEvent *event) {
    btnRotate->show();
    btnCut->show();
    btnCopy->show();

    this->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
}

void PDFPageWidget::paintEvent(QPaintEvent *event) {
    QPalette palette = this->palette();
    if (selected)
        palette.setColor( backgroundRole(), palette.color(QPalette::Highlight) );
    else
        palette.setColor( backgroundRole(), palette.color(QPalette::AlternateBase) );
    this->setPalette( palette );

    QFrame::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(QRect((size().width() - pixmap.width()) / 2, (size().height() - pixmap.height()) / 2, pixmap.width(), pixmap.height()), pixmap);
}

QSize PDFPageWidget::sizeHint() const {
    return size();
}
