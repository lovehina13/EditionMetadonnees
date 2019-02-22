//==============================================================================
// Name        : Settings.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (22/02/2019)
// Description : Source file of the Settings class
//==============================================================================

#include "Settings.h"
#include <QStringList>

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
    const QStringList fromStringList = fromString.split(sep);
    if (fromStringList.count() < 7)
        return;
    this->setDataFilePath(fromStringList.at(0));
    this->setMP3FilesDirPath(fromStringList.at(1));
    this->setBitRate(fromStringList.at(2).toInt());
    this->setEncodeFiles((bool) fromStringList.at(3).toInt());
    this->setClearMetadata((bool) fromStringList.at(4).toInt());
    this->setWriteMetadata((bool) fromStringList.at(5).toInt());
    this->setOrderFiles((bool) fromStringList.at(6).toInt());
}

const QString Settings::toString(const QChar& sep) const
{
    QString toString;
    toString += this->getDataFilePath() + sep;
    toString += this->getMP3FilesDirPath() + sep;
    toString += QString::number(this->getBitRate()) + sep;
    toString += QString::number((int) this->getEncodeFiles()) + sep;
    toString += QString::number((int) this->getClearMetadata()) + sep;
    toString += QString::number((int) this->getWriteMetadata()) + sep;
    toString += QString::number((int) this->getOrderFiles());
    return toString;
}

bool Settings::operator==(const Settings& settings) const
{
    return this->equals(settings);
}

bool Settings::operator!=(const Settings& settings) const
{
    return !(this->equals(settings));
}
