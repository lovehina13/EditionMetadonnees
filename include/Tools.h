//==============================================================================
// Name        : Tools.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.0 (03/03/2020)
// Description : Header file of the Tools elements
//==============================================================================

#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QStringList>

int executeCommand(const QString& program, const QStringList& arguments, const bool& log = false);
const QStringList readFileLines(const QString& filePath);
void writeFileLines(const QString& filePath, const QStringList& lines);
void removeDirectory(const QString& dirPath);

#endif /* TOOLS_H */
