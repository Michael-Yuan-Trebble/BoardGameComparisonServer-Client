#pragma once

#include <QtWidgets/QMainWindow>
#include <qprocess.h>
#include <qdebug.h>
#include "ui_TestBothApplications.h"

class TestBothApplications : public QMainWindow
{
    Q_OBJECT

public:
    TestBothApplications(QWidget *parent = nullptr);
    ~TestBothApplications();

private:
    Ui::TestBothApplicationsClass ui;

    void startBoth();
};

