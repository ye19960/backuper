#pragma once
#include <QMainWindow>
#include<QLabel>
#include <QLineEdit>
#include<QPushButton>
#include<QFileDialog>
// #include<string>
#include<QString>
#include<QTextEdit>
#include<boost/filesystem.hpp>
#include<unordered_map>
#include<QStandardItemModel>
#include<QTreeView>

#include<iostream>
// #include<glo
#include"global.h"
#include"tools.h"

class Backuper : public QMainWindow {
    Q_OBJECT

// private slots:
//     void setFilePath(QLineEdit* qle);

private:
    QLabel* qlSrcPath;
    QLabel* qlDstPath;

    QLineEdit* qleSrcPath;
    QLineEdit* qleDstPath;

    QPushButton* qpbSrcPath;
    QPushButton* qpbDstPath;

    QPushButton* qpbScan;
    QPushButton* qpbBackup;
    QLabel* qlScanRes;
    QTreeView* scanResView;
    QStandardItemModel* scanResModel;
    // QStandardItemModel* filesTree;
    QTextEdit* msgBox;
    std::unordered_map<std::string, std::vector<std::string>> scanRes;
    std::unordered_map<std::string, fileSize_t> totalSize;
    // std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> scanRes;

    void initUI();
    void setFilePath(QLineEdit* qle);
    void scanFile();
    void backupFile();



public:
    Backuper(QWidget* parent = nullptr);
    ~Backuper();
};