//==============================================================================
// Name        : MP3File.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (03/03/2020)
// Description : Source file of the MP3File class
//==============================================================================

#include "MP3File.h"
#include "Tools.h"
#include <QDir>
#include <QFile>
#include <QStringList>

MP3File::MP3File(const QString& filePath, const QString& title, const QString& artist,
        const QString& albumArtist, const QString& album, const QDate& date, const int& disc,
        const int& track, const QString& genre) :
        _filePath(filePath), _title(title), _artist(artist), _albumArtist(albumArtist),
                _album(album), _date(date), _disc(disc), _track(track), _genre(genre)
{
}

const QString& MP3File::getFilePath() const
{
    return _filePath;
}

const QString& MP3File::getTitle() const
{
    return _title;
}

const QString& MP3File::getArtist() const
{
    return _artist;
}

const QString& MP3File::getAlbumArtist() const
{
    return _albumArtist;
}

const QString& MP3File::getAlbum() const
{
    return _album;
}

const QDate& MP3File::getDate() const
{
    return _date;
}

const int& MP3File::getDisc() const
{
    return _disc;
}

const int& MP3File::getTrack() const
{
    return _track;
}

const QString& MP3File::getGenre() const
{
    return _genre;
}

void MP3File::setFilePath(const QString& filePath)
{
    _filePath = filePath;
}

void MP3File::setTitle(const QString& title)
{
    _title = title;
}

void MP3File::setArtist(const QString& artist)
{
    _artist = artist;
}

void MP3File::setAlbumArtist(const QString& albumArtist)
{
    _albumArtist = albumArtist;
}

void MP3File::setAlbum(const QString& album)
{
    _album = album;
}

void MP3File::setDate(const QDate& date)
{
    _date = date;
}

void MP3File::setDisc(const int& disc)
{
    _disc = disc;
}

void MP3File::setTrack(const int& track)
{
    _track = track;
}

void MP3File::setGenre(const QString& genre)
{
    _genre = genre;
}

void MP3File::clear()
{
    *this = MP3File();
}

void MP3File::set(const QString& filePath, const QString& title, const QString& artist,
        const QString& albumArtist, const QString& album, const QDate& date, const int& disc,
        const int& track, const QString& genre)
{
    setFilePath(filePath);
    setTitle(title);
    setArtist(artist);
    setAlbumArtist(albumArtist);
    setAlbum(album);
    setDate(date);
    setDisc(disc);
    setTrack(track);
    setGenre(genre);
}

void MP3File::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = fromString.split(sep);
    if (fromStringList.count() < 9)
        return;
    setFilePath(fromStringList.at(0));
    setTitle(fromStringList.at(1));
    setArtist(fromStringList.at(2));
    setAlbumArtist(fromStringList.at(3));
    setAlbum(fromStringList.at(4));
    setDateFromString(fromStringList.at(5));
    setDiscFromString(fromStringList.at(6));
    setTrackFromString(fromStringList.at(7));
    setGenre(fromStringList.at(8));
}

const QString MP3File::toString(const QChar& sep) const
{
    QString toString;
    toString += getFilePath() + sep;
    toString += getTitle() + sep;
    toString += getArtist() + sep;
    toString += getAlbumArtist() + sep;
    toString += getAlbum() + sep;
    toString += getDateToString() + sep;
    toString += getDiscToString() + sep;
    toString += getTrackToString() + sep;
    toString += getGenre();
    return toString;
}

const QString MP3File::getDateToString() const
{
    return getDate().toString("yyyy-MM-dd");
}

const QString MP3File::getDiscToString() const
{
    return QString::number(getDisc());
}

const QString MP3File::getTrackToString() const
{
    return QString::number(getTrack());
}

void MP3File::setDateFromString(const QString& date)
{
    setDate(QDate::fromString(date, "yyyy-MM-dd"));
}

void MP3File::setDiscFromString(const QString& disc)
{
    setDisc(disc.toInt());
}

void MP3File::setTrackFromString(const QString& track)
{
    setTrack(track.toInt());
}

void MP3File::encodeFile(const int& bitRate) const
{
    const QString& inFilePath = getFilePath();
    const QString outFilePath = QString("%1.out.mp3").arg(inFilePath);
    const QString program = QString("ffmpeg");
    const QString arguments = QString("-y -i \"%1\" -map 0:0 -c:a libmp3lame -b:a %2k \"%3\"").arg(
            inFilePath, QString::number(bitRate), outFilePath);
    executeCommand(program, arguments.split(" "), true);
    QFile::remove(inFilePath);
    QFile::rename(outFilePath, inFilePath);
}

void MP3File::clearMetadata() const
{
    const QString& inFilePath = getFilePath();
    const QString outFilePath = QString("%1.out.mp3").arg(inFilePath);
    const QString program = QString("ffmpeg");
    const QString arguments = QString("-y -i \"%1\" -map_metadata -1 -c:a copy \"%2\"").arg(
            inFilePath, outFilePath);
    executeCommand(program, arguments.split(" "), true);
    QFile::remove(inFilePath);
    QFile::rename(outFilePath, inFilePath);
}

void MP3File::decodeMetadata()
{
    const QString& inFilePath = getFilePath();
    const QString outFilePath = QString("%1.out.txt").arg(inFilePath);
    const QString program = QString("ffmpeg");
    const QString arguments = QString("-y -i \"%1\" -f ffmetadata \"%2\"").arg(inFilePath,
            outFilePath);
    executeCommand(program, arguments.split(" "), true);

    const QStringList lines = readFileLines(outFilePath);
    const int nbLines = lines.count();
    for (int itLine = 0; itLine < nbLines; itLine++)
    {
        const QString& line = lines.at(itLine);
        QStringList lineItems = line.split("=");
        if (lineItems.count() < 2)
            continue;
        const QString metadata = lineItems.takeFirst();
        const QString value = lineItems.join("=");
        if (metadata == QString("title"))
        {
            setTitle(value);
        }
        else if (metadata == QString("artist"))
        {
            setArtist(value);
        }
        else if (metadata == QString("album_artist"))
        {
            setAlbumArtist(value);
        }
        else if (metadata == QString("album"))
        {
            setAlbum(value);
        }
        else if (metadata == QString("date"))
        {
            setDateFromString(value);
        }
        else if (metadata == QString("disc"))
        {
            setDiscFromString(value);
        }
        else if (metadata == QString("track"))
        {
            setTrackFromString(value);
        }
        else if (metadata == QString("genre"))
        {
            setGenre(value);
        }
    }

    QFile::remove(outFilePath);
}

void MP3File::encodeMetadata() const
{
    QString metadata;
    if (!getTitle().isEmpty())
        metadata += QString("-metadata TIT2=\"%1\" ").arg(getTitle());
    if (!getArtist().isEmpty())
        metadata += QString("-metadata TPE1=\"%1\" ").arg(getArtist());
    if (!getAlbumArtist().isEmpty())
        metadata += QString("-metadata TPE2=\"%1\" ").arg(getAlbumArtist());
    if (!getAlbum().isEmpty())
        metadata += QString("-metadata TALB=\"%1\" ").arg(getAlbum());
    if (getDate().isValid())
        metadata += QString("-metadata TDRC=\"%1\" ").arg(getDateToString());
    if (getDisc())
        metadata += QString("-metadata TPOS=\"%1\" ").arg(getDiscToString());
    if (getTrack())
        metadata += QString("-metadata TRCK=\"%1\" ").arg(getTrackToString());
    if (!getGenre().isEmpty())
        metadata += QString("-metadata TCON=\"%1\" ").arg(getGenre());

    const QString& inFilePath = getFilePath();
    const QString outFilePath = QString("%1.out.mp3").arg(inFilePath);
    const QString program = QString("ffmpeg");
    const QString arguments = QString("-y -i \"%1\" %2 -c:a copy \"%3\"").arg(inFilePath, metadata,
            outFilePath);
    executeCommand(program, arguments.split(" "), true);
    QFile::remove(inFilePath);
    QFile::rename(outFilePath, inFilePath);
}

void MP3File::orderFile(const QString& dirPath)
{
    const QString& inFilePath = getFilePath();
    const QString& albumArtist = getAlbumArtist();
    const QString& album = getAlbum();
    const QString& title = getTitle();
    const int& disc = getDisc();
    const int& track = getTrack();
    const QString number =
            (disc && track) ?
                    QString("%1-%2 - ").arg(QString::number(disc),
                            QString::number(track).rightJustified(2, '0')) :
            (track) ?
                    QString("%1 - ").arg(QString::number(track).rightJustified(2, '0')) : QString();
    const QString outDirPath = QString("%1/%2/%3").arg(dirPath, albumArtist, album);
    const QString outFilePath = QString("%1/%2%3.mp3").arg(outDirPath, number, title);

    const QDir outDir(outDirPath);
    if (!outDir.exists())
    {
        outDir.mkpath(outDirPath);
    }
    QFile::copy(inFilePath, outFilePath);
}
