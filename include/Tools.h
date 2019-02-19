//==============================================================================
// Name        : Tools.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
// Description : Header file of the Tools elements
//==============================================================================

#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QStringList>

int executeCommand(const QString& command, const bool& log = false);
const QStringList readFileLines(const QString& filePath);
void writeFileLines(const QString& filePath, const QStringList& lines);
void removeDirectory(const QString& dirPath);

#endif /* TOOLS_H */
