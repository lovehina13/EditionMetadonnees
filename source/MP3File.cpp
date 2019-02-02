//==============================================================================
// Name        : MP3File.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
// Description : Source file of the MP3File class
//==============================================================================

#include "MP3File.h"
#include <QStringList>

MP3File::MP3File() :
        filePath(QString()), title(QString()), artist(QString()), albumArtist(QString()),
                album(QString()), date(QDate()), disc(0), track(0), genre(QString())
{
    this->clear();
}

MP3File::MP3File(const QString& filePath, const QString& title, const QString& artist,
        const QString& albumArtist, const QString& album, const QDate& date, const int& disc,
        const int& track, const QString& genre) :
        MP3File()
{
    this->set(filePath, title, artist, albumArtist, album, date, disc, track, genre);
}

MP3File::MP3File(const MP3File& mp3File) :
        MP3File()
{
    this->copy(mp3File);
}

MP3File::~MP3File()
{

}

const QString& MP3File::getFilePath() const
{
    return this->filePath;
}

const QString& MP3File::getTitle() const
{
    return this->title;
}

const QString& MP3File::getArtist() const
{
    return this->artist;
}

const QString& MP3File::getAlbumArtist() const
{
    return this->albumArtist;
}

const QString& MP3File::getAlbum() const
{
    return this->album;
}

const QDate& MP3File::getDate() const
{
    return this->date;
}

const int& MP3File::getDisc() const
{
    return this->disc;
}

const int& MP3File::getTrack() const
{
    return this->track;
}

const QString& MP3File::getGenre() const
{
    return this->genre;
}

void MP3File::setFilePath(const QString& filePath)
{
    this->filePath = filePath;
}

void MP3File::setTitle(const QString& title)
{
    this->title = title;
}

void MP3File::setArtist(const QString& artist)
{
    this->artist = artist;
}

void MP3File::setAlbumArtist(const QString& albumArtist)
{
    this->albumArtist = albumArtist;
}

void MP3File::setAlbum(const QString& album)
{
    this->album = album;
}

void MP3File::setDate(const QDate& date)
{
    this->date = date;
}

void MP3File::setDisc(const int& disc)
{
    this->disc = disc;
}

void MP3File::setTrack(const int& track)
{
    this->track = track;
}

void MP3File::setGenre(const QString& genre)
{
    this->genre = genre;
}

void MP3File::clear()
{
    this->set(QString(), QString(), QString(), QString(), QString(), QDate(), 0, 0, QString());
}

void MP3File::set(const QString& filePath, const QString& title, const QString& artist,
        const QString& albumArtist, const QString& album, const QDate& date, const int& disc,
        const int& track, const QString& genre)
{
    this->setFilePath(filePath);
    this->setTitle(title);
    this->setArtist(artist);
    this->setAlbumArtist(albumArtist);
    this->setAlbum(album);
    this->setDate(date);
    this->setDisc(disc);
    this->setTrack(track);
    this->setGenre(genre);
}

void MP3File::copy(const MP3File& mp3File)
{
    this->set(mp3File.getFilePath(), mp3File.getTitle(), mp3File.getArtist(),
            mp3File.getAlbumArtist(), mp3File.getAlbum(), mp3File.getDate(), mp3File.getDisc(),
            mp3File.getTrack(), mp3File.getGenre());
}

bool MP3File::equals(const MP3File& mp3File) const
{
    if (this->getFilePath() != mp3File.getFilePath())
        return false;
    if (this->getTitle() != mp3File.getTitle())
        return false;
    if (this->getArtist() != mp3File.getArtist())
        return false;
    if (this->getAlbumArtist() != mp3File.getAlbumArtist())
        return false;
    if (this->getAlbum() != mp3File.getAlbum())
        return false;
    if (this->getDate() != mp3File.getDate())
        return false;
    if (this->getDisc() != mp3File.getDisc())
        return false;
    if (this->getTrack() != mp3File.getTrack())
        return false;
    if (this->getGenre() != mp3File.getGenre())
        return false;
    return true;
}

void MP3File::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = fromString.split(sep);
    if (fromStringList.count() < 9)
        return;
    this->setFilePath(fromStringList.at(0));
    this->setTitle(fromStringList.at(1));
    this->setArtist(fromStringList.at(2));
    this->setAlbumArtist(fromStringList.at(3));
    this->setAlbum(fromStringList.at(4));
    this->setDateFromString(fromStringList.at(5));
    this->setDiscFromString(fromStringList.at(6));
    this->setTrackFromString(fromStringList.at(7));
    this->setGenre(fromStringList.at(8));
}

const QString MP3File::toString(const QChar& sep) const
{
    QString toString;
    toString += this->getFilePath() + sep;
    toString += this->getTitle() + sep;
    toString += this->getArtist() + sep;
    toString += this->getAlbumArtist() + sep;
    toString += this->getAlbum() + sep;
    toString += this->getDateToString() + sep;
    toString += this->getDiscToString() + sep;
    toString += this->getTrackToString() + sep;
    toString += this->getGenre();
    return toString;
}

bool MP3File::operator==(const MP3File& mp3File) const
{
    return this->equals(mp3File);
}

bool MP3File::operator!=(const MP3File& mp3File) const
{
    return !(this->equals(mp3File));
}

const QString MP3File::getDateToString() const
{
    return this->getDate().toString("dd/MM/yyyy");
}

const QString MP3File::getDiscToString() const
{
    return QString::number(this->getDisc());
}

const QString MP3File::getTrackToString() const
{
    return QString::number(this->getTrack());
}

void MP3File::setDateFromString(const QString& date)
{
    this->setDate(QDate::fromString(date, "dd/MM/yyyy"));
}

void MP3File::setDiscFromString(const QString& disc)
{
    this->setDisc(disc.toInt());
}

void MP3File::setTrackFromString(const QString& track)
{
    this->setTrack(track.toInt());
}

void MP3File::encodeFile(const int& bitRate) const
{
    // TODO void MP3File::encodeFile(const int& bitRate) const*
    Q_UNUSED(bitRate);
}

void MP3File::clearMetadata() const
{
    // TODO void MP3File::clearMetadata() const
}

void MP3File::decodeMetadata()
{
    // TODO void MP3File::decodeMetadata()
}

void MP3File::encodeMetadata() const
{
    // TODO void MP3File::encodeMetadata() const
}

void MP3File::orderFile(const QString& dirPath)
{
    // TODO void MP3File::orderFile(const QString& dirPath)
    Q_UNUSED(dirPath);
}
