//==============================================================================
// Name        : MainWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
// Description : Source file of the MainWindow class
//==============================================================================

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DocumentationWindow.h"
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionLoad_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionProcess_triggered()
{

}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionDocumentation_triggered()
{
    DocumentationWindow* documentationWindow = new DocumentationWindow(this);
    documentationWindow->exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox* messageBox = new QMessageBox(QMessageBox::Information,
            QString::fromUtf8("EditionMetadonnees"),
            QString::fromUtf8("EditionMetadonnees - Version 1.0.0 (01/02/2019).\n"
                    "Réalisée par Alexis Foerster (alexis.foerster@gmail.com)."), QMessageBox::Ok,
            this);
    messageBox->exec();
}
