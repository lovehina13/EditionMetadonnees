//==============================================================================
// Name        : MP3File.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (03/03/2020)
// Description : Header file of the MP3File class
//==============================================================================

#ifndef MP3FILE_H
#define MP3FILE_H

#include <QChar>
#include <QDate>
#include <QList>
#include <QMap>
#include <QString>

class MP3File
{
public:
    // Constructors and destructors
    MP3File();
    MP3File(const QString& filePath, const QString& title, const QString& artist,
            const QString& albumArtist, const QString& album, const QDate& date, const int& disc,
            const int& track, const QString& genre);
    MP3File(const MP3File& mp3File);
    virtual ~MP3File();

    // Operators
    MP3File& operator=(const MP3File& mp3File);
    bool operator==(const MP3File& mp3File) const;
    bool operator!=(const MP3File& mp3File) const;

    // Getters
    const QString& getFilePath() const;
    const QString& getTitle() const;
    const QString& getArtist() const;
    const QString& getAlbumArtist() const;
    const QString& getAlbum() const;
    const QDate& getDate() const;
    const int& getDisc() const;
    const int& getTrack() const;
    const QString& getGenre() const;

    // Setters
    void setFilePath(const QString& filePath);
    void setTitle(const QString& title);
    void setArtist(const QString& artist);
    void setAlbumArtist(const QString& albumArtist);
    void setAlbum(const QString& album);
    void setDate(const QDate& date);
    void setDisc(const int& disc);
    void setTrack(const int& track);
    void setGenre(const QString& genre);

    // Generic methods
    void clear();
    void set(const QString& filePath, const QString& title, const QString& artist,
            const QString& albumArtist, const QString& album, const QDate& date, const int& disc,
            const int& track, const QString& genre);
    void copy(const MP3File& mp3File);
    bool equals(const MP3File& mp3File) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Specific methods
    const QString getDateToString() const;
    const QString getDiscToString() const;
    const QString getTrackToString() const;
    void setDateFromString(const QString& date);
    void setDiscFromString(const QString& disc);
    void setTrackFromString(const QString& track);
    void encodeFile(const int& bitRate) const;
    void clearMetadata() const;
    void decodeMetadata();
    void encodeMetadata() const;
    void orderFile(const QString& dirPath);

private:
    // Class members
    QString filePath;
    QString title;
    QString artist;
    QString albumArtist;
    QString album;
    QDate date;
    int disc;
    int track;
    QString genre;
};

typedef MP3File* MP3FilePtr;
typedef QList<MP3File> MP3FilesList;
typedef QList<MP3FilePtr> MP3FilesPtrList;
typedef QMap<int, MP3File> MP3FilesIdMap;
typedef QMap<int, MP3FilePtr> MP3FilesPtrIdMap;
typedef QMap<QString, MP3File> MP3FilesNamesMap;
typedef QMap<QString, MP3FilePtr> MP3FilesPtrNamesMap;

#endif /* MP3FILE_H */
