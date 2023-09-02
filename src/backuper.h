#pragma once
#include <QMainWindow>
#include<QLabel>
#include <QLineEdit>

class Backuper : public QMainWindow {
    Q_OBJECT
private:
    // QLabel qlSrcPath;
    // QLabel qlDstPath;

    QLineEdit qleSrcPath;
    QLineEdit qleDstPath;

    void initUI();

public:
    Backuper(QWidget* parent = nullptr);
    ~Backuper();
};