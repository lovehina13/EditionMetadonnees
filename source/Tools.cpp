//==============================================================================
// Name        : Tools.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
// Description : Source file of the Tools elements
//==============================================================================

#include "Tools.h"
#include <QFile>
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
