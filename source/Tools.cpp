//==============================================================================
// Name        : Tools.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (03/03/2020)
// Description : Source file of the Tools elements
//==============================================================================

#include "Tools.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QIODevice>
#include <QProcess>
#include <QTextStream>
#include <iostream>

int executeCommand(const QString& command, const bool& log)
{
    QProcess process;
    const int returnCode = process.execute(command);
    if (log)
    {
        std::cout << "Command: " << command.toStdString() << std::endl;
        std::cout << "ReturnCode: " << returnCode << std::endl;
    }
    return returnCode;
}

const QStringList readFileLines(const QString& filePath)
{
    QStringList lines;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            const QString line = stream.readLine();
            lines.append(line);
        }
        file.close();
    }
    return lines;
}

void writeFileLines(const QString& filePath, const QStringList& lines)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        const int nbLines = lines.count();
        for (int itLine = 0; itLine < nbLines; itLine++)
        {
            const QString& line = lines.at(itLine);
            stream << line << endl;
        }
        file.close();
    }
}

void removeDirectory(const QString& dirPath)
{
    QDir dir(dirPath);

    const QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    const int nbFiles = files.count();
    for (int itFile = 0; itFile < nbFiles; itFile++)
    {
        const QFileInfo& file = files.at(itFile);
        const QString filePath = file.absoluteFilePath();
        QFile::remove(filePath);
    }

    const QFileInfoList dirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    const int nbDirs = dirs.count();
    for (int itDir = 0; itDir < nbDirs; itDir++)
    {
        const QFileInfo& subDir = dirs.at(itDir);
        const QString subDirPath = subDir.absoluteFilePath();
        removeDirectory(subDirPath);
    }

    dir.rmdir(dirPath);
}
