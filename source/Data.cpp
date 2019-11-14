//==============================================================================
// Name        : Data.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.2 (14/11/2019)
// Description : Source file of the Data class
//==============================================================================

#include "Data.h"
#include "Tools.h"
#include <QDir>
#include <QDirIterator>
#include <QStringList>

Data::Data() :
        settings(Settings()), mp3Files(MP3FilesPtrNamesMap())
{
    this->clear();
}

Data::Data(const Settings& settings, const MP3FilesPtrNamesMap& mp3Files) :
        Data()
{
    this->set(settings, mp3Files);
}

Data::Data(const Data& data) :
        Data()
{
    this->copy(data);
}

Data::~Data()
{
    this->clearMP3Files();
}

const Settings& Data::getSettings() const
{
    return this->settings;
}

const MP3FilesPtrNamesMap& Data::getMP3Files() const
{
    return this->mp3Files;
}

void Data::setSettings(const Settings& settings)
{
    this->settings = settings;
}

void Data::setMP3Files(const MP3FilesPtrNamesMap& mp3Files)
{
    this->mp3Files = mp3Files;
}

void Data::clear()
{
    this->set(Settings(), MP3FilesPtrNamesMap());
}

void Data::set(const Settings& settings, const MP3FilesPtrNamesMap& mp3Files)
{
    this->setSettings(settings);
    this->setMP3Files(mp3Files);
}

void Data::copy(const Data& data)
{
    this->set(data.getSettings(), data.getMP3Files());
}

bool Data::equals(const Data& data) const
{
    if (this->getSettings() != data.getSettings())
        return false;
    if (this->getMP3Files() != data.getMP3Files())
        return false;
    return true;
}

void Data::fromString(const QString& fromString, const QChar& sep)
{
    // TODO void Data::fromString(const QString& fromString, const QChar& sep)
    Q_UNUSED(fromString);
    Q_UNUSED(sep);
}

const QString Data::toString(const QChar& sep) const
{
    // TODO const QString Data::toString(const QChar& sep) const
    Q_UNUSED(sep);
    return QString();
}

void Data::loadData(const QString& filePath)
{
    MP3FilesPtrNamesMap mp3Files;
    const QStringList lines = readFileLines(filePath);
    const int nbLines = lines.count();
    for (int itLine = 0; itLine < nbLines; itLine++)
    {
        const QString& line = lines.at(itLine);
        if (itLine == 0)
        {
            Settings settings = this->getSettings();
            settings.fromString(line, QChar(';'));
            this->setSettings(settings);
        }
        else
        {
            MP3FilePtr mp3File = new MP3File();
            mp3File->fromString(line, QChar(';'));
            mp3Files.insert(mp3File->getFilePath(), mp3File);
        }
    }
    this->clearMP3Files();
    this->setMP3Files(mp3Files);
}

void Data::saveData(const QString& filePath)
{
    Settings settings = this->getSettings();
    settings.setDataFilePath(filePath);
    this->setSettings(settings);

    QStringList lines;
    lines.append(settings.toString(QChar(';')));
    const MP3FilesPtrNamesMap& mp3Files = this->getMP3Files();
    const QStringList mp3FilesPaths = mp3Files.keys();
    const int nbMP3Files = mp3Files.count();
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const QString& mp3FilePath = mp3FilesPaths.at(itMP3File);
        const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
        lines.append(mp3File->toString(QChar(';')));
    }
    writeFileLines(filePath, lines);
}

void Data::clearMP3Files()
{
    const MP3FilesPtrNamesMap& mp3Files = this->getMP3Files();
    const QStringList mp3FilesPaths = mp3Files.keys();
    const int nbMP3Files = mp3Files.count();
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const QString& mp3FilePath = mp3FilesPaths.at(itMP3File);
        const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
        delete mp3File;
    }
}

void Data::searchMP3Files()
{
    MP3FilesPtrNamesMap mp3Files;
    const Settings& settings = this->getSettings();
    const QString& mp3FilesDirPath = settings.getMP3FilesDirPath();
    QDirIterator mp3FilesPaths(mp3FilesDirPath, QStringList() << "*.mp3", QDir::Files,
            QDirIterator::Subdirectories);
    while (mp3FilesPaths.hasNext())
    {
        const QString mp3FilePath = mp3FilesPaths.next();
        MP3FilePtr mp3File = new MP3File();
        mp3File->setFilePath(mp3FilePath);
        mp3File->decodeMetadata();
        mp3Files.insert(mp3File->getFilePath(), mp3File);
    }
    this->clearMP3Files();
    this->setMP3Files(mp3Files);
}

void Data::encodeFiles(const int& bitRate) const
{
    const MP3FilesPtrNamesMap& mp3Files = this->getMP3Files();
    const QStringList mp3FilesPaths = mp3Files.keys();
    const int nbMP3Files = mp3Files.count();
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const QString& mp3FilePath = mp3FilesPaths.at(itMP3File);
        const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
        mp3File->encodeFile(bitRate);
    }
}

void Data::clearMetadata() const
{
    const MP3FilesPtrNamesMap& mp3Files = this->getMP3Files();
    const QStringList mp3FilesPaths = mp3Files.keys();
    const int nbMP3Files = mp3Files.count();
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const QString& mp3FilePath = mp3FilesPaths.at(itMP3File);
        const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
        mp3File->clearMetadata();
    }
}

void Data::decodeMetadata() const
{
    const MP3FilesPtrNamesMap& mp3Files = this->getMP3Files();
    const QStringList mp3FilesPaths = mp3Files.keys();
    const int nbMP3Files = mp3Files.count();
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const QString& mp3FilePath = mp3FilesPaths.at(itMP3File);
        const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
        mp3File->decodeMetadata();
    }
}

void Data::encodeMetadata() const
{
    const MP3FilesPtrNamesMap& mp3Files = this->getMP3Files();
    const QStringList mp3FilesPaths = mp3Files.keys();
    const int nbMP3Files = mp3Files.count();
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const QString& mp3FilePath = mp3FilesPaths.at(itMP3File);
        const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
        mp3File->encodeMetadata();
    }
}

void Data::orderFiles(const QString& dirPath) const
{
    const QString outDirPath = QString("%1_out").arg(dirPath);

    removeDirectory(outDirPath);

    const MP3FilesPtrNamesMap& mp3Files = this->getMP3Files();
    const QStringList mp3FilesPaths = mp3Files.keys();
    const int nbMP3Files = mp3Files.count();
    for (int itMP3File = 0; itMP3File < nbMP3Files; itMP3File++)
    {
        const QString& mp3FilePath = mp3FilesPaths.at(itMP3File);
        const MP3FilePtr mp3File = mp3Files.value(mp3FilePath);
        mp3File->orderFile(outDirPath);
    }
}
