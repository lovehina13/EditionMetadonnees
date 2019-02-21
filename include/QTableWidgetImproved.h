//==============================================================================
// Name        : QTableWidgetImproved.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (01/02/2019)
// Description : Header file of the QTableWidgetImproved class
//==============================================================================

#ifndef QTABLEWIDGETIMPROVED_H
#define QTABLEWIDGETIMPROVED_H

#include <QKeyEvent>
#include <QTableWidget>
#include <QWidget>

class QTableWidgetImproved : public QTableWidget
{
    Q_OBJECT

public:
    explicit QTableWidgetImproved(QWidget* parent = NULL);
    virtual ~QTableWidgetImproved();

protected:
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void deleteEvent();
    virtual void cutEvent();
    virtual void copyEvent();
    virtual void pasteEvent();
//    virtual void undoEvent();
//    virtual void redoEvent();
};

#endif /* QTABLEWIDGETIMPROVED_H */
