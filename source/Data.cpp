//==============================================================================
// Name        : Data.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
// Description : Source file of the Data class
//==============================================================================

#include "Data.h"

Data::Data() :
        settings(Settings()), mp3Files(MP3FilesPtrList())
{
    this->clear();
}

Data::Data(const Settings& settings, const MP3FilesPtrList& mp3Files) :
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

}

const Settings& Data::getSettings() const
{
    return this->settings;
}

const MP3FilesPtrList& Data::getMP3Files() const
{
    return this->mp3Files;
}

void Data::setSettings(const Settings& settings)
{
    this->settings = settings;
}

void Data::setMP3Files(const MP3FilesPtrList& mp3Files)
{
    this->mp3Files = mp3Files;
}

void Data::clear()
{
    this->set(Settings(), MP3FilesPtrList());
}

void Data::set(const Settings& settings, const MP3FilesPtrList& mp3Files)
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
    // TODO void Data::loadData(const QString& filePath)
    Q_UNUSED(filePath);
}

void Data::saveData(const QString& filePath)
{
    // TODO void Data::saveData(const QString& filePath)
    Q_UNUSED(filePath);
}

void Data::clearMP3Files()
{
    // TODO void Data::clearMP3Files()
}

void Data::searchMP3Files()
{
    // TODO void Data::searchMP3Files()
}

void Data::encodeFiles(const int& bitRate) const
{
    // TODO void Data::encodeFiles(const int& bitRate) const
    Q_UNUSED(bitRate);
}

void Data::clearMetadata() const
{
    // TODO void Data::clearMetadata() const
}

void Data::decodeMetadata() const
{
    // TODO void Data::decodeMetadata() const
}

void Data::encodeMetadata() const
{
    // TODO void Data::encodeMetadata() const
}

void Data::orderFiles(const QString& dirPath) const
{
    // TODO void Data::orderFiles(const QString& dirPath) const
    Q_UNUSED(dirPath);
}
