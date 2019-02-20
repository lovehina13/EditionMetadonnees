//==============================================================================
// Name        : Data.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
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
    Data();
    Data(const Settings& settings, const MP3FilesPtrNamesMap& mp3Files);
    Data(const Data& data);
    virtual ~Data();

    // Getters
    const Settings& getSettings() const;
    const MP3FilesPtrNamesMap& getMP3Files() const;

    // Setters
    void setSettings(const Settings& settings);
    void setMP3Files(const MP3FilesPtrNamesMap& mp3Files);

    // Generic methods
    void clear();
    void set(const Settings& settings, const MP3FilesPtrNamesMap& mp3Files);
    void copy(const Data& data);
    bool equals(const Data& data) const;
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
    Settings settings;
    MP3FilesPtrNamesMap mp3Files;
};

typedef Data* DataPtr;
typedef QList<Data> DataList;
typedef QList<DataPtr> DataPtrList;
typedef QMap<int, Data> DataIdMap;
typedef QMap<int, DataPtr> DataPtrIdMap;
typedef QMap<QString, Data> DataNamesMap;
typedef QMap<QString, DataPtr> DataPtrNamesMap;

#endif // DATA_H
