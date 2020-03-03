//==============================================================================
// Name        : MainWindow.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (03/03/2020)
// Description : Header file of the MainWindow class
//==============================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Data.h"
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QVariant>
#include <QWidget>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

protected:
    void createNewData();
    void loadExistingData();
    void saveCurrentData();
    void processCurrentData();
    void clearTableWidget();
    void updateTableWidget();
    void updateSettings();
    void updateMP3File(const int& item, const int& metadata, const QVariant& value);

protected slots:
    void on_actionNew_triggered();
    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionProcess_triggered();
    void on_actionQuit_triggered();
    void on_actionDocumentation_triggered();
    void on_actionAbout_triggered();
    void on_tableWidget_itemChanged(QTableWidgetItem* item);
    void on_comboBoxBitRate_currentIndexChanged();
    void on_checkBoxEncodeFiles_stateChanged();
    void on_checkBoxClearMetadata_stateChanged();
    void on_checkBoxWriteMetadata_stateChanged();
    void on_checkBoxOrderFiles_stateChanged();

private:
    Ui::MainWindow* ui;
    Data data;

    enum tableWidgetColumns
    {
        C_FILE_PATH, C_TITLE, C_ARTIST, C_ALBUM_ARTIST, C_ALBUM, C_DATE, C_DISC, C_TRACK, C_GENRE
    };
};

#endif /* MAINWINDOW_H */
