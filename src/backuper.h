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

    QTextEdit* msgBox;

    void initUI();
    void setFilePath(QLineEdit* qle);
    void scanFile();



public:
    Backuper(QWidget* parent = nullptr);
    ~Backuper();
};