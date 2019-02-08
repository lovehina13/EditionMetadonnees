//==============================================================================
// Name        : MainWindow.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
// Description : Source file of the MainWindow class
//==============================================================================

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DocumentationWindow.h"
#include "Settings.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    this->ui->tableWidget->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

void MainWindow::createNewData()
{
    const QString dirPath = QFileDialog::getExistingDirectory(this,
            QString::fromUtf8("Sélection d'un répertoire"),
            this->data.getSettings().getMP3FilesDirPath());
    if (dirPath.isEmpty())
        return;

    this->clearTableWidget();

    Settings settings;
    settings.setMP3FilesDirPath(dirPath);
    this->data.setSettings(settings);
    this->data.searchMP3Files();

    this->updateTableWidget();
    this->updateSettings();
}

void MainWindow::loadExistingData()
{
    const QString filePath = QFileDialog::getOpenFileName(this,
            QString::fromUtf8("Sélection d'un fichier de métadonnées"),
            this->data.getSettings().getDataFilePath(),
            QString::fromUtf8("Fichier de métadonnées (*.csv)"));
    if (filePath.isEmpty())
        return;

    this->clearTableWidget();

    this->data.loadData(filePath);

    this->updateTableWidget();
    this->updateSettings();
}

void MainWindow::saveCurrentData()
{
    const QString filePath = QFileDialog::getSaveFileName(this,
            QString::fromUtf8("Sélection d'un fichier de métadonnées"),
            this->data.getSettings().getDataFilePath(),
            QString::fromUtf8("Fichier de métadonnées (*.csv)"));
    if (filePath.isEmpty())
        return;

    this->data.saveData(filePath);
}

void MainWindow::processCurrentData()
{
    // First step: clear metadata
    if (this->ui->checkBoxClearMetadata->isChecked()
            || this->ui->checkBoxWriteMetadata->isChecked())
    {
        this->data.clearMetadata();
    }

    // Second step: re-encode files
    if (this->ui->checkBoxEncodeFiles->isChecked())
    {
        this->data.encodeFiles(this->data.getSettings().getBitRate());
    }

    // Third step: write metadata
    if (this->ui->checkBoxWriteMetadata->isChecked())
    {
        this->data.encodeMetadata();
    }

    // Fourth step: re-order files
    if (this->ui->checkBoxOrderFiles->isChecked())
    {
        this->data.orderFiles(this->data.getSettings().getMP3FilesDirPath());
    }
}

void MainWindow::clearTableWidget()
{
    this->ui->tableWidget->clearContents();
    this->ui->tableWidget->setRowCount(0);
    this->ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::updateTableWidget()
{
    this->clearTableWidget();

    const MP3FilesPtrList& mp3Files = this->data.getMP3Files();
    const int nbMP3Files = mp3Files.count();
    this->ui->tableWidget->setRowCount(nbMP3Files);
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const MP3FilePtr mp3File = mp3Files.at(itMP3File);
        QTableWidgetItem* filePathItem = new QTableWidgetItem(mp3File->getFilePath());
        QTableWidgetItem* titleItem = new QTableWidgetItem(mp3File->getTitle());
        QTableWidgetItem* artistItem = new QTableWidgetItem(mp3File->getArtist());
        QTableWidgetItem* albumArtistItem = new QTableWidgetItem(mp3File->getAlbumArtist());
        QTableWidgetItem* albumItem = new QTableWidgetItem(mp3File->getAlbum());
        QTableWidgetItem* dateItem = new QTableWidgetItem(mp3File->getDateToString());
        QTableWidgetItem* discItem = new QTableWidgetItem(mp3File->getDiscToString());
        QTableWidgetItem* trackItem = new QTableWidgetItem(mp3File->getTrackToString());
        QTableWidgetItem* genreItem = new QTableWidgetItem(mp3File->getGenre());
        this->ui->tableWidget->setItem(itMP3File, C_FILE_PATH, filePathItem);
        this->ui->tableWidget->setItem(itMP3File, C_TITLE, titleItem);
        this->ui->tableWidget->setItem(itMP3File, C_ARTIST, artistItem);
        this->ui->tableWidget->setItem(itMP3File, C_ALBUM_ARTIST, albumArtistItem);
        this->ui->tableWidget->setItem(itMP3File, C_ALBUM, albumItem);
        this->ui->tableWidget->setItem(itMP3File, C_DATE, dateItem);
        this->ui->tableWidget->setItem(itMP3File, C_DISC, discItem);
        this->ui->tableWidget->setItem(itMP3File, C_TRACK, trackItem);
        this->ui->tableWidget->setItem(itMP3File, C_GENRE, genreItem);
        filePathItem->setFlags(filePathItem->flags() ^ Qt::ItemIsEditable);
    }
    this->ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::updateSettings()
{
    const Settings& settings = this->data.getSettings();
    this->ui->comboBoxBitRate->setCurrentIndex(settings.getBitRate() / 32 - 1);
    this->ui->checkBoxEncodeFiles->setChecked(settings.getEncodeFiles());
    this->ui->checkBoxClearMetadata->setChecked(settings.getClearMetadata());
    this->ui->checkBoxWriteMetadata->setChecked(settings.getWriteMetadata());
    this->ui->checkBoxOrderFiles->setChecked(settings.getOrderFiles());
}

void MainWindow::updateMP3File(const int& item, const int& metadata, const QString& value)
{
    const MP3FilesPtrList& mp3Files = this->data.getMP3Files();
    const MP3FilePtr mp3File = mp3Files.at(item);
    if (metadata == C_TITLE)
    {
        mp3File->setTitle(value);
    }
    else if (metadata == C_ARTIST)
    {
        mp3File->setArtist(value);
    }
    else if (metadata == C_ALBUM_ARTIST)
    {
        mp3File->setAlbumArtist(value);
    }
    else if (metadata == C_ALBUM)
    {
        mp3File->setAlbum(value);
    }
    else if (metadata == C_DATE)
    {
        mp3File->setDateFromString(value);
    }
    else if (metadata == C_DISC)
    {
        mp3File->setDiscFromString(value);
    }
    else if (metadata == C_TRACK)
    {
        mp3File->setTrackFromString(value);
    }
    else if (metadata == C_GENRE)
    {
        mp3File->setGenre(value);
    }
}

void MainWindow::on_actionNew_triggered()
{
    this->createNewData();
}

void MainWindow::on_actionLoad_triggered()
{
    this->loadExistingData();
}

void MainWindow::on_actionSave_triggered()
{
    this->saveCurrentData();
}

void MainWindow::on_actionProcess_triggered()
{
    this->processCurrentData();
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

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem* item)
{
    const int row = item->row();
    const int column = item->column();
    const QString value = item->text();

    this->updateMP3File(row, column, value);

    this->ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_comboBoxBitRate_currentIndexChanged()
{
    Settings settings = this->data.getSettings();
    settings.setBitRate((this->ui->comboBoxBitRate->currentIndex() + 1) * 32);
    this->data.setSettings(settings);
}

void MainWindow::on_checkBoxEncodeFiles_stateChanged()
{
    Settings settings = this->data.getSettings();
    settings.setEncodeFiles(this->ui->checkBoxEncodeFiles->isChecked());
    this->data.setSettings(settings);
}

void MainWindow::on_checkBoxClearMetadata_stateChanged()
{
    Settings settings = this->data.getSettings();
    settings.setClearMetadata(this->ui->checkBoxClearMetadata->isChecked());
    this->data.setSettings(settings);
}

void MainWindow::on_checkBoxWriteMetadata_stateChanged()
{
    Settings settings = this->data.getSettings();
    settings.setWriteMetadata(this->ui->checkBoxWriteMetadata->isChecked());
    this->data.setSettings(settings);
}

void MainWindow::on_checkBoxOrderFiles_stateChanged()
{
    Settings settings = this->data.getSettings();
    settings.setOrderFiles(this->ui->checkBoxOrderFiles->isChecked());
    this->data.setSettings(settings);
}
