//==============================================================================
// Name        : Settings.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (03/03/2020)
// Description : Source file of the Settings class
//==============================================================================

#include "Settings.h"
#include <QStringList>

Settings::Settings() :
        _dataFilePath(QString()), _mp3FilesDirPath(QString()), _bitRate(192), _encodeFiles(false),
                _clearMetadata(false), _writeMetadata(false), _orderFiles(false)
{
    clear();
}

Settings::Settings(const QString& dataFilePath, const QString& mp3FilesDirPath, const int& bitRate,
        const bool& encodeFiles, const bool& clearMetadata, const bool& writeMetadata,
        const bool& orderFiles) :
        Settings()
{
    set(dataFilePath, mp3FilesDirPath, bitRate, encodeFiles, clearMetadata, writeMetadata,
            orderFiles);
}

Settings::Settings(const Settings& settings) :
        Settings()
{
    copy(settings);
}

Settings::~Settings()
{

}

Settings& Settings::operator=(const Settings& settings)
{
    copy(settings);
    return *this;
}

bool Settings::operator==(const Settings& settings) const
{
    return equals(settings);
}

bool Settings::operator!=(const Settings& settings) const
{
    return !equals(settings);
}

const QString& Settings::getDataFilePath() const
{
    return _dataFilePath;
}

const QString& Settings::getMP3FilesDirPath() const
{
    return _mp3FilesDirPath;
}

const int& Settings::getBitRate() const
{
    return _bitRate;
}

const bool& Settings::getEncodeFiles() const
{
    return _encodeFiles;
}

const bool& Settings::getClearMetadata() const
{
    return _clearMetadata;
}

const bool& Settings::getWriteMetadata() const
{
    return _writeMetadata;
}

const bool& Settings::getOrderFiles() const
{
    return _orderFiles;
}

void Settings::setDataFilePath(const QString& dataFilePath)
{
    _dataFilePath = dataFilePath;
}

void Settings::setMP3FilesDirPath(const QString& mp3FilesDirPath)
{
    _mp3FilesDirPath = mp3FilesDirPath;
}

void Settings::setBitRate(const int& bitRate)
{
    _bitRate = bitRate;
}

void Settings::setEncodeFiles(const bool& encodeFiles)
{
    _encodeFiles = encodeFiles;
}

void Settings::setClearMetadata(const bool& clearMetadata)
{
    _clearMetadata = clearMetadata;
}

void Settings::setWriteMetadata(const bool& writeMetadata)
{
    _writeMetadata = writeMetadata;
}

void Settings::setOrderFiles(const bool& orderFiles)
{
    _orderFiles = orderFiles;
}

void Settings::clear()
{
    set(QString(), QString(), 192, false, false, false, false);
}

void Settings::set(const QString& dataFilePath, const QString& mp3FilesDirPath, const int& bitRate,
        const bool& encodeFiles, const bool& clearMetadata, const bool& writeMetadata,
        const bool& orderFiles)
{
    setDataFilePath(dataFilePath);
    setMP3FilesDirPath(mp3FilesDirPath);
    setBitRate(bitRate);
    setEncodeFiles(encodeFiles);
    setClearMetadata(clearMetadata);
    setWriteMetadata(writeMetadata);
    setOrderFiles(orderFiles);
}

void Settings::copy(const Settings& settings)
{
    set(settings.getDataFilePath(), settings.getMP3FilesDirPath(), settings.getBitRate(),
            settings.getEncodeFiles(), settings.getClearMetadata(), settings.getWriteMetadata(),
            settings.getOrderFiles());
}

bool Settings::equals(const Settings& settings) const
{
    if (getDataFilePath() != settings.getDataFilePath())
        return false;
    if (getMP3FilesDirPath() != settings.getMP3FilesDirPath())
        return false;
    if (getBitRate() != settings.getBitRate())
        return false;
    if (getEncodeFiles() != settings.getEncodeFiles())
        return false;
    if (getClearMetadata() != settings.getClearMetadata())
        return false;
    if (getWriteMetadata() != settings.getWriteMetadata())
        return false;
    if (getOrderFiles() != settings.getOrderFiles())
        return false;
    return true;
}

void Settings::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = fromString.split(sep);
    if (fromStringList.count() < 7)
        return;
    setDataFilePath(fromStringList.at(0));
    setMP3FilesDirPath(fromStringList.at(1));
    setBitRate(fromStringList.at(2).toInt());
    setEncodeFiles(static_cast<bool>(fromStringList.at(3).toInt()));
    setClearMetadata(static_cast<bool>(fromStringList.at(4).toInt()));
    setWriteMetadata(static_cast<bool>(fromStringList.at(5).toInt()));
    setOrderFiles(static_cast<bool>(fromStringList.at(6).toInt()));
}

const QString Settings::toString(const QChar& sep) const
{
    QString toString;
    toString += getDataFilePath() + sep;
    toString += getMP3FilesDirPath() + sep;
    toString += QString::number(getBitRate()) + sep;
    toString += QString::number(static_cast<int>(getEncodeFiles())) + sep;
    toString += QString::number(static_cast<int>(getClearMetadata())) + sep;
    toString += QString::number(static_cast<int>(getWriteMetadata())) + sep;
    toString += QString::number(static_cast<int>(getOrderFiles()));
    return toString;
}
