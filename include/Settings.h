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
    Settings() = default;
    Settings(const QString& dataFilePath, const QString& mp3FilesDirPath, const int& bitRate,
            const bool& encodeFiles, const bool& clearMetadata, const bool& writeMetadata,
            const bool& orderFiles);

    // Operators
    bool operator==(const Settings& settings) const = default;
    bool operator!=(const Settings& settings) const = default;

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
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

private:
    // Class members
    QString _dataFilePath;
    QString _mp3FilesDirPath;
    int _bitRate { 192 };
    bool _encodeFiles { false };
    bool _clearMetadata { false };
    bool _writeMetadata { false };
    bool _orderFiles { false };
};

using SettingsPtr = Settings*;
using SettingsList = QList<Settings>;
using SettingsPtrList = QList<SettingsPtr>;
using SettingsIdMap = QMap<int, Settings>;
using SettingsPtrIdMap = QMap<int, SettingsPtr>;
using SettingsNamesMap = QMap<QString, Settings>;
using SettingsPtrNamesMap = QMap<QString, SettingsPtr>;

#endif /* SETTINGS_H */
