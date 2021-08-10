//==============================================================================
// Name        : MainWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (10/08/2021)
// Description : Source file of the MainWindow class
//==============================================================================

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DocumentationWindow.h"
#include "MP3File.h"
#include "QTableWidgetImproved.h"
#include "Settings.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDate>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QStringList>

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _ui->tableWidget->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::createNewData()
{
    const QString dirPath = QFileDialog::getExistingDirectory(this,
            QString::fromUtf8("Sélection d'un répertoire"),
            _data.getSettings().getMP3FilesDirPath());
    if (dirPath.isEmpty())
        return;

    clearTableWidget();

    Settings settings;
    settings.setMP3FilesDirPath(dirPath);
    _data.setSettings(settings);
    _data.searchMP3Files();

    updateTableWidget();
    updateSettings();
}

void MainWindow::loadExistingData()
{
    const QString filePath = QFileDialog::getOpenFileName(this,
            QString::fromUtf8("Sélection d'un fichier de métadonnées"),
            _data.getSettings().getDataFilePath(),
            QString::fromUtf8("Fichier de métadonnées (*.csv)"));
    if (filePath.isEmpty())
        return;

    clearTableWidget();

    _data.loadData(filePath);

    updateTableWidget();
    updateSettings();
}

void MainWindow::saveCurrentData()
{
    const QString filePath = QFileDialog::getSaveFileName(this,
            QString::fromUtf8("Sélection d'un fichier de métadonnées"),
            _data.getSettings().getDataFilePath(),
            QString::fromUtf8("Fichier de métadonnées (*.csv)"));
    if (filePath.isEmpty())
        return;

    _data.saveData(filePath);
}

void MainWindow::processCurrentData()
{
    // First step: clear metadata
    if (_ui->checkBoxClearMetadata->isChecked() || _ui->checkBoxWriteMetadata->isChecked())
    {
        _data.clearMetadata();
    }

    // Second step: re-encode files
    if (_ui->checkBoxEncodeFiles->isChecked())
    {
        _data.encodeFiles(_data.getSettings().getBitRate());
    }

    // Third step: write metadata
    if (_ui->checkBoxWriteMetadata->isChecked())
    {
        _data.encodeMetadata();
    }

    // Fourth step: re-order files
    if (_ui->checkBoxOrderFiles->isChecked())
    {
        _data.orderFiles(_data.getSettings().getMP3FilesDirPath());
    }
}

void MainWindow::clearTableWidget()
{
    _ui->tableWidget->clearContents();
    _ui->tableWidget->setRowCount(0);
    _ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::updateTableWidget()
{
    clearTableWidget();

    const MP3FilesPtrNamesMap& mp3Files = _data.getMP3Files();
    const QStringList mp3FilesPaths = mp3Files.keys();
    const int nbMP3Files = mp3Files.count();
    _ui->tableWidget->setRowCount(nbMP3Files);
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const QString& mp3FilePath = mp3FilesPaths.at(itMP3File);
        const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
        QTableWidgetItem* filePathItem = new QTableWidgetItem(mp3File->getFilePath());
        QTableWidgetItem* titleItem = new QTableWidgetItem(mp3File->getTitle());
        QTableWidgetItem* artistItem = new QTableWidgetItem(mp3File->getArtist());
        QTableWidgetItem* albumArtistItem = new QTableWidgetItem(mp3File->getAlbumArtist());
        QTableWidgetItem* albumItem = new QTableWidgetItem(mp3File->getAlbum());
        QTableWidgetItem* dateItem = new QTableWidgetItem(/*mp3File->getDateToString()*/);
        QTableWidgetItem* discItem = new QTableWidgetItem(/*mp3File->getDiscToString()*/);
        QTableWidgetItem* trackItem = new QTableWidgetItem(/*mp3File->getTrackToString()*/);
        QTableWidgetItem* genreItem = new QTableWidgetItem(mp3File->getGenre());
        dateItem->setData(Qt::DisplayRole, mp3File->getDate());
        discItem->setData(Qt::DisplayRole, mp3File->getDisc());
        trackItem->setData(Qt::DisplayRole, mp3File->getTrack());
        _ui->tableWidget->setItem(itMP3File, C_FILE_PATH, filePathItem);
        _ui->tableWidget->setItem(itMP3File, C_TITLE, titleItem);
        _ui->tableWidget->setItem(itMP3File, C_ARTIST, artistItem);
        _ui->tableWidget->setItem(itMP3File, C_ALBUM_ARTIST, albumArtistItem);
        _ui->tableWidget->setItem(itMP3File, C_ALBUM, albumItem);
        _ui->tableWidget->setItem(itMP3File, C_DATE, dateItem);
        _ui->tableWidget->setItem(itMP3File, C_DISC, discItem);
        _ui->tableWidget->setItem(itMP3File, C_TRACK, trackItem);
        _ui->tableWidget->setItem(itMP3File, C_GENRE, genreItem);
        filePathItem->setFlags(filePathItem->flags() ^ Qt::ItemIsEditable);
    }
    _ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::updateSettings()
{
    const Settings& settings = _data.getSettings();
    _ui->comboBoxBitRate->setCurrentIndex(settings.getBitRate() / 32 - 1);
    _ui->checkBoxEncodeFiles->setChecked(settings.getEncodeFiles());
    _ui->checkBoxClearMetadata->setChecked(settings.getClearMetadata());
    _ui->checkBoxWriteMetadata->setChecked(settings.getWriteMetadata());
    _ui->checkBoxOrderFiles->setChecked(settings.getOrderFiles());
}

void MainWindow::updateMP3File(const int& item, const int& metadata, const QVariant& value)
{
    const MP3FilesPtrNamesMap& mp3Files = _data.getMP3Files();
    const QString mp3FilePath = _ui->tableWidget->item(item, C_FILE_PATH)->text();
    const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
    if (metadata == C_TITLE)
    {
        mp3File->setTitle(value.toString());
    }
    else if (metadata == C_ARTIST)
    {
        mp3File->setArtist(value.toString());
    }
    else if (metadata == C_ALBUM_ARTIST)
    {
        mp3File->setAlbumArtist(value.toString());
    }
    else if (metadata == C_ALBUM)
    {
        mp3File->setAlbum(value.toString());
    }
    else if (metadata == C_DATE)
    {
        mp3File->setDate(value.toDate());
    }
    else if (metadata == C_DISC)
    {
        mp3File->setDisc(value.toInt());
    }
    else if (metadata == C_TRACK)
    {
        mp3File->setTrack(value.toInt());
    }
    else if (metadata == C_GENRE)
    {
        mp3File->setGenre(value.toString());
    }
}

void MainWindow::on_actionNew_triggered()
{
    createNewData();
}

void MainWindow::on_actionLoad_triggered()
{
    loadExistingData();
}

void MainWindow::on_actionSave_triggered()
{
    saveCurrentData();
}

void MainWindow::on_actionProcess_triggered()
{
    processCurrentData();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
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
            QString::fromUtf8("EditionMetadonnees - Version 1.2.0 (10/08/2021).\n"
                    "Réalisée par Alexis Foerster (alexis.foerster@gmail.com)."), QMessageBox::Ok,
            this);
    messageBox->exec();
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem* item)
{
    const int row = item->row();
    const int column = item->column();
    const QVariant value = item->data(Qt::DisplayRole);

    // Note: fix to prevent automatic conversion to QDateTime after user input
    if (value.type() == QVariant::DateTime)
    {
        item->setData(Qt::DisplayRole, QDate());
        item->setData(Qt::DisplayRole, value.toDate());
    }

    updateMP3File(row, column, value);

    _ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_comboBoxBitRate_currentIndexChanged(int index)
{
    Settings settings = _data.getSettings();
    settings.setBitRate((index + 1) * 32);
    _data.setSettings(settings);
}

void MainWindow::on_checkBoxEncodeFiles_stateChanged(int state)
{
    Settings settings = _data.getSettings();
    settings.setEncodeFiles(state == Qt::Checked);
    _data.setSettings(settings);
}

void MainWindow::on_checkBoxClearMetadata_stateChanged(int state)
{
    Settings settings = _data.getSettings();
    settings.setClearMetadata(state == Qt::Checked);
    _data.setSettings(settings);
}

void MainWindow::on_checkBoxWriteMetadata_stateChanged(int state)
{
    Settings settings = _data.getSettings();
    settings.setWriteMetadata(state == Qt::Checked);
    _data.setSettings(settings);
}

void MainWindow::on_checkBoxOrderFiles_stateChanged(int state)
{
    Settings settings = _data.getSettings();
    settings.setOrderFiles(state == Qt::Checked);
    _data.setSettings(settings);
}
