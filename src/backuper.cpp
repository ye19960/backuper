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

    this->qpbBackup = new QPushButton("备份", this);
    this->qpbBackup->move(400, 50);
    connect(this->qpbBackup, &QPushButton::clicked, this, &Backuper::backupFile);

    // show scan result
    // this->qlScanRes = new QLabel(this);
    // this->qlScanRes->resize(500, 500);
    // this->qlScanRes->move(10, 100);
    // this->qlScanRes->setFrameShape(QFrame::Box);
    // this->qlScanRes->setStyleSheet(lineBorder);

    this->scanResView = new QTreeView(this);
    this->scanResView->resize(500, 500);
    this->scanResView->move(10, 100);
    this->scanResModel = new QStandardItemModel(0, 3, this);
    this->scanResModel->setHeaderData(0, Qt::Horizontal, "后缀");
    // this->filesTree
    this->scanResModel->setHeaderData(1, Qt::Horizontal, "数量");
    this->scanResModel->setHeaderData(2, Qt::Horizontal, "总大小");
    this->scanResView->setModel(scanResModel);

    this->scanResModel->setRowCount(this->scanRes.size());
    
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
    this->scanRes.clear();
    this->totalSize.clear();
    for (auto& p: rdi)
    {
        if (boost::filesystem::is_directory(p.path()))
        {
            continue;
        }
        std::string curExtention = p.path().extension().string();
        if (this->scanRes.find(curExtention) != this->scanRes.end())
        {
            this->scanRes[curExtention].push_back(p.path().string());
            this->totalSize[curExtention] += boost::filesystem::file_size(p.path());
        }
        else
        {
            this->scanRes[curExtention] = std::vector<std::string>({p.path().string()});
            this->totalSize[curExtention] = boost::filesystem::file_size(p.path());
        }
    }
    this->scanResModel->removeRows(0, this->scanResModel->rowCount());
    int i = 0;
    for (auto& it: this->scanRes)
    {
        QStandardItem* curItem0 = new QStandardItem(it.first.c_str());
        curItem0->setCheckable(true);
        this->scanResModel->setItem(i, 0, curItem0);
        QStandardItem* curItem1 = new QStandardItem(QString::number(it.second.size()));
        this->scanResModel->setItem(i, 1, curItem1);
        std::string _ss = convertFileSize(this->totalSize[it.first]);
        this->msgBox->append(QString::fromStdString("==" + _ss + "=="));
        QStandardItem* curItem2 = new QStandardItem(QString::fromStdString(convertFileSize(this->totalSize[it.first])));
        this->scanResModel->setItem(i, 2, curItem2);
        ++i;
    }
}

void Backuper::backupFile()
{
    std::string dstRootStr = this->qleDstPath->text().toStdString();
    boost::filesystem::path dRootPath(dstRootStr);
    std::string srcRootStr = this->qleSrcPath->text().toStdString();
    boost::filesystem::path sRootPath(srcRootStr);
    int srcRootSize = srcRootStr.size();

    if (!boost::filesystem::exists(dRootPath)){
        if (!boost::filesystem::create_directories(dRootPath)){
            std::cout << "create destinate directory fail." << std::endl;
        }
    }

    for (auto& it: this->scanRes){
        for (auto& itStr: it.second){
            boost::filesystem::path curSrcFilePath(itStr);
            std::string curDstFilePathStr = dstRootStr + itStr.substr(srcRootSize, itStr.size() - srcRootSize);
            boost::filesystem::path curDstFilePath(curDstFilePathStr);
            boost::filesystem::path curParentPath = curDstFilePath.parent_path();
            if (!boost::filesystem::exists(curParentPath)){
                if (!boost::filesystem::create_directories(curParentPath)){
                    std::cout << "create directory fail : " << curParentPath.string() << std::endl;
                }
                boost::filesystem::copy_file(curSrcFilePath, curDstFilePath, boost::filesystem::copy_options::overwrite_existing);
            }else{
                if (boost::filesystem::exists(curDstFilePath)){
                    if (boost::filesystem::last_write_time(curDstFilePath) - boost::filesystem::last_write_time(curSrcFilePath) < 1){
                        continue;
                    }
                }
                boost::filesystem::copy_file(curSrcFilePath, curDstFilePath, boost::filesystem::copy_options::overwrite_existing);

            }

        }
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