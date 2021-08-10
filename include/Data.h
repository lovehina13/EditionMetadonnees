//==============================================================================
// Name        : Data.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (10/08/2021)
// Description : Header file of the Data class
//==============================================================================

#ifndef DATA_H
#define DATA_H

#include "MP3File.h"
#include "Settings.h"
#include <QChar>
#include <QList>
#include <QMap>
#include <QString>

class Data
{
public:
    // Constructors and destructors
    Data() = default;
    Data(const Settings& settings, const MP3FilesPtrNamesMap& mp3Files);

    // Operators
    bool operator==(const Data& data) const = default;
    bool operator!=(const Data& data) const = default;

    // Getters
    const Settings& getSettings() const;
    const MP3FilesPtrNamesMap& getMP3Files() const;

    // Setters
    void setSettings(const Settings& settings);
    void setMP3Files(const MP3FilesPtrNamesMap& mp3Files);

    // Generic methods
    void clear();
    void set(const Settings& settings, const MP3FilesPtrNamesMap& mp3Files);
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Specific methods
    void loadData(const QString& filePath);
    void saveData(const QString& filePath);
    void clearMP3Files();
    void searchMP3Files();
    void encodeFiles(const int& bitRate) const;
    void clearMetadata() const;
    void decodeMetadata() const;
    void encodeMetadata() const;
    void orderFiles(const QString& dirPath) const;

private:
    // Class members
    Settings _settings;
    MP3FilesPtrNamesMap _mp3Files;
};

using DataPtr = Data*;
using DataList = QList<Data>;
using DataPtrList = QList<DataPtr>;
using DataIdMap = QMap<int, Data>;
using DataPtrIdMap = QMap<int, DataPtr>;
using DataNamesMap = QMap<QString, Data>;
using DataPtrNamesMap = QMap<QString, DataPtr>;

#endif /* DATA_H */
