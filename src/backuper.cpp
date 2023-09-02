#include "backuper.h"

Backuper::Backuper(QWidget* parent)
    : QMainWindow(parent)
{
    this->resize(1600, 900);

    this->initUI();

}

void Backuper::initUI()
{
    QLabel qlSrcPath = QLabel(this);
    this->qlabelSrcPath.setText("源目录");
    this->qlabelSrcPath.move(10, 10);
    this->qlabelSrcPath.show();

    this->qlabelDstPath.setText("目的目录");
    this->qlabelDstPath.move(10, 30);
}

Backuper::~Backuper()
{
}