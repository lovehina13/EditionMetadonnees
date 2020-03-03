//==============================================================================
// Name        : Settings.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (03/03/2020)
// Description : Header file of the Settings class
//==============================================================================

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QChar>
#include <QList>
#include <QMap>
#include <QString>

class Settings
{
public:
    // Constructors and destructors
    Settings();
    Settings(const QString& dataFilePath, const QString& mp3FilesDirPath, const int& bitRate,
            const bool& encodeFiles, const bool& clearMetadata, const bool& writeMetadata,
            const bool& orderFiles);
    Settings(const Settings& settings);
    virtual ~Settings();

    // Operators
    Settings& operator=(const Settings& settings);
    bool operator==(const Settings& settings) const;
    bool operator!=(const Settings& settings) const;

    // Getters
    const QString& getDataFilePath() const;
    const QString& getMP3FilesDirPath() const;
    const int& getBitRate() const;
    const bool& getEncodeFiles() const;
    const bool& getClearMetadata() const;
    const bool& getWriteMetadata() const;
    const bool& getOrderFiles() const;

    // Setters
    void setDataFilePath(const QString& dataFilePath);
    void setMP3FilesDirPath(const QString& mp3FilesDirPath);
    void setBitRate(const int& bitRate);
    void setEncodeFiles(const bool& encodeFiles);
    void setClearMetadata(const bool& clearMetadata);
    void setWriteMetadata(const bool& writeMetadata);
    void setOrderFiles(const bool& orderFiles);

    // Generic methods
    void clear();
    void set(const QString& dataFilePath, const QString& mp3FilesDirPath, const int& bitRate,
            const bool& encodeFiles, const bool& clearMetadata, const bool& writeMetadata,
            const bool& orderFiles);
    void copy(const Settings& settings);
    bool equals(const Settings& settings) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

private:
    // Class members
    QString dataFilePath;
    QString mp3FilesDirPath;
    int bitRate;
    bool encodeFiles;
    bool clearMetadata;
    bool writeMetadata;
    bool orderFiles;
};

typedef Settings* SettingsPtr;
typedef QList<Settings> SettingsList;
typedef QList<SettingsPtr> SettingsPtrList;
typedef QMap<int, Settings> SettingsIdMap;
typedef QMap<int, SettingsPtr> SettingsPtrIdMap;
typedef QMap<QString, Settings> SettingsNamesMap;
typedef QMap<QString, SettingsPtr> SettingsPtrNamesMap;

#endif /* SETTINGS_H */
