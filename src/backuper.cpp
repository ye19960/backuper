#include "backuper.h"

Backuper::Backuper(QWidget* parent)
    : QMainWindow(parent)
{
    this->resize(1600, 900);

    this->initUI();

}

void Backuper::initUI()
{
    // source path
    this->qlSrcPath = new QLabel("源目录:", this);
    this->qlSrcPath->move(10, 10);

    this->qleSrcPath = new QLineEdit(this);
    this->qleSrcPath->move(100, 10);

    this->qpbSrcPath = new QPushButton("浏览", this);
    this->qpbSrcPath->move(300, 10);
    // connect(this->qpbSrcPath, SIGNAL(QPushButton::clicked(this->qpbSrcPath)), this, SLOT(this->setFilePath(this->qleSrcPath)));
    connect(this->qpbSrcPath, &QPushButton::clicked, this, [=](){this->setFilePath(this->qleSrcPath);});

    // destinate path
    this->qlDstPath = new QLabel("目的目录:", this);
    this->qlDstPath->move(10, 50);

    this->qleDstPath = new QLineEdit(this);
    this->qleDstPath->move(100, 50);

    this->qpbDstPath = new QPushButton("浏览", this);
    this->qpbDstPath->move(300, 50);
    connect(this->qpbDstPath, &QPushButton::clicked, this, [=](){this->setFilePath(this->qleDstPath);});


    // other funtion button
    this->qpbScan = new QPushButton("扫描", this);
    this->qpbScan->move(400, 10);
    connect(this->qpbScan, &QPushButton::clicked, this, &Backuper::scanFile);

    // debug message
    this->msgBox = new QTextEdit(this);
    this->msgBox->resize(400, 600);
    this->msgBox->move(600, 10);
}

void Backuper::setFilePath(QLineEdit* qle)
{
    // this->msgBox->append("scan button pushed.");
    QString filePath = QFileDialog::getExistingDirectory();
    qle->setText(filePath);
}

void Backuper::scanFile()
{
    QString rootPath = this->qleSrcPath->text();
    boost::filesystem::path root(rootPath.toStdString());
    boost::filesystem::recursive_directory_iterator rdi(root);
    for (auto& p: rdi)
    {
        if (boost::filesystem::is_directory(p.path()))
        {
            continue;
        }
        this->msgBox->append(p.path().filename().string().c_str());
    }
}

Backuper::~Backuper()
{
    delete this->qlSrcPath;
    delete this->qlDstPath;

    delete this->qleSrcPath;
    delete this->qleDstPath;

    delete this->qpbSrcPath;
    delete this->qpbDstPath;

    delete this->qpbScan;
}