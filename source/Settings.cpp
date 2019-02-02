//==============================================================================
// Name        : Settings.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
// Description : Source file of the Settings class
//==============================================================================

#include "Settings.h"

Settings::Settings() :
        dataFilePath(QString()), mp3FilesDirPath(QString()), bitRate(192), encodeFiles(false),
                clearMetadata(false), writeMetadata(false), orderFiles(false)
{
    this->clear();
}

Settings::Settings(const QString& dataFilePath, const QString& mp3FilesDirPath, const int& bitRate,
        const bool& encodeFiles, const bool& clearMetadata, const bool& writeMetadata,
        const bool& orderFiles) :
        Settings()
{
    this->set(dataFilePath, mp3FilesDirPath, bitRate, encodeFiles, clearMetadata, writeMetadata,
            orderFiles);
}

Settings::Settings(const Settings& settings) :
        Settings()
{
    this->copy(settings);
}

Settings::~Settings()
{

}

const QString& Settings::getDataFilePath() const
{
    return this->dataFilePath;
}

const QString& Settings::getMP3FilesDirPath() const
{
    return this->mp3FilesDirPath;
}

const int& Settings::getBitRate() const
{
    return this->bitRate;
}

const bool& Settings::getEncodeFiles() const
{
    return this->encodeFiles;
}

const bool& Settings::getClearMetadata() const
{
    return this->clearMetadata;
}

const bool& Settings::getWriteMetadata() const
{
    return this->writeMetadata;
}

const bool& Settings::getOrderFiles() const
{
    return this->orderFiles;
}

void Settings::setDataFilePath(const QString& dataFilePath)
{
    this->dataFilePath = dataFilePath;
}

void Settings::setMP3FilesDirPath(const QString& mp3FilesDirPath)
{
    this->mp3FilesDirPath = mp3FilesDirPath;
}

void Settings::setBitRate(const int& bitRate)
{
    this->bitRate = bitRate;
}

void Settings::setEncodeFiles(const bool& encodeFiles)
{
    this->encodeFiles = encodeFiles;
}

void Settings::setClearMetadata(const bool& clearMetadata)
{
    this->clearMetadata = clearMetadata;
}

void Settings::setWriteMetadata(const bool& writeMetadata)
{
    this->writeMetadata = writeMetadata;
}

void Settings::setOrderFiles(const bool& orderFiles)
{
    this->orderFiles = orderFiles;
}

void Settings::clear()
{
    this->set(QString(), QString(), 192, false, false, false, false);
}

void Settings::set(const QString& dataFilePath, const QString& mp3FilesDirPath, const int& bitRate,
        const bool& encodeFiles, const bool& clearMetadata, const bool& writeMetadata,
        const bool& orderFiles)
{
    this->setDataFilePath(dataFilePath);
    this->setMP3FilesDirPath(mp3FilesDirPath);
    this->setBitRate(bitRate);
    this->setEncodeFiles(encodeFiles);
    this->setClearMetadata(clearMetadata);
    this->setWriteMetadata(writeMetadata);
    this->setOrderFiles(orderFiles);
}

void Settings::copy(const Settings& settings)
{
    this->set(settings.getDataFilePath(), settings.getMP3FilesDirPath(), settings.getBitRate(),
            settings.getEncodeFiles(), settings.getClearMetadata(), settings.getWriteMetadata(),
            settings.getOrderFiles());
}

bool Settings::equals(const Settings& settings) const
{
    if (this->getDataFilePath() != settings.getDataFilePath())
        return false;
    if (this->getMP3FilesDirPath() != settings.getMP3FilesDirPath())
        return false;
    if (this->getBitRate() != settings.getBitRate())
        return false;
    if (this->getEncodeFiles() != settings.getEncodeFiles())
        return false;
    if (this->getClearMetadata() != settings.getClearMetadata())
        return false;
    if (this->getWriteMetadata() != settings.getWriteMetadata())
        return false;
    if (this->getOrderFiles() != settings.getOrderFiles())
        return false;
    return true;
}

void Settings::fromString(const QString& fromString, const QChar& sep)
{
    // TODO void Settings::fromString(const QString& fromString, const QChar& sep)
    Q_UNUSED(fromString);
    Q_UNUSED(sep);
}

const QString Settings::toString(const QChar& sep) const
{
    // TODO const QString Settings::toString(const QChar& sep) const
    Q_UNUSED(sep);
    return QString();
}

bool Settings::operator==(const Settings& settings) const
{
    // TODO bool Settings::operator==(const Settings& settings) const
    Q_UNUSED(settings);
    return false;
}

bool Settings::operator!=(const Settings& settings) const
{
    // TODO bool Settings::operator!=(const Settings& settings) const
    Q_UNUSED(settings);
    return false;
}
