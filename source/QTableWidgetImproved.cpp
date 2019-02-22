//==============================================================================
// Name        : QTableWidgetImproved.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (22/02/2019)
// Description : Source file of the QTableWidgetImproved class
//==============================================================================

#include "QTableWidgetImproved.h"
#include <QApplication>
#include <QClipboard>
#include <QDate>
#include <QKeySequence>
#include <QList>
#include <QString>
#include <QTableWidgetItem>
#include <QTableWidgetSelectionRange>
#include <QVariant>

QTableWidgetImproved::QTableWidgetImproved(QWidget* parent) :
        QTableWidget(parent)
{

}

QTableWidgetImproved::~QTableWidgetImproved()
{

}

void QTableWidgetImproved::keyPressEvent(QKeyEvent* event)
{
    QTableWidget::keyPressEvent(event);

    if (event->matches(QKeySequence::Delete))
    {
        this->deleteEvent();
    }
    else if (event->matches(QKeySequence::Cut))
    {
        this->cutEvent();
    }
    else if (event->matches(QKeySequence::Copy))
    {
        this->copyEvent();
    }
    else if (event->matches(QKeySequence::Paste))
    {
        this->pasteEvent();
    }
//    else if (event->matches(QKeySequence::Undo))
//    {
//        this->undoEvent();
//    }
//    else if (event->matches(QKeySequence::Redo))
//    {
//        this->redoEvent();
//    }
}

void QTableWidgetImproved::deleteEvent()
{
    const QList<QTableWidgetItem*> selectedItems = this->selectedItems();
    const int nbSelectedItems = selectedItems.count();
    for (int itSelectedItem = 0; itSelectedItem < nbSelectedItems; itSelectedItem++)
    {
        QTableWidgetItem* selectedItem = selectedItems.at(itSelectedItem);
        if (selectedItem->flags() & Qt::ItemIsEditable)
        {
            const QVariant data = selectedItem->data(Qt::DisplayRole);
            if (data.type() == QVariant::String)
            {
                selectedItem->setText(QString());
            }
            else if (data.type() == QVariant::Int)
            {
                selectedItem->setData(Qt::DisplayRole, 0);
            }
            else if (data.type() == QVariant::Date)
            {
                selectedItem->setData(Qt::DisplayRole, QDate());
            }
        }
    }
}

void QTableWidgetImproved::cutEvent()
{
    this->copyEvent();
    this->deleteEvent();
}

void QTableWidgetImproved::copyEvent()
{
    int topRow = -1, bottomRow = -1, leftColumn = -1, rightColumn = -1;
    const QList<QTableWidgetItem*> selectedItems = this->selectedItems();
    const int nbSelectedItems = selectedItems.count();
    for (int itSelectedItem = 0; itSelectedItem < nbSelectedItems; itSelectedItem++)
    {
        const QTableWidgetItem* selectedItem = selectedItems.at(itSelectedItem);
        const int selectedItemRow = selectedItem->row();
        const int selectedItemColumn = selectedItem->column();
        if (selectedItemRow < topRow || topRow == -1)
        {
            topRow = selectedItemRow;
        }
        if (selectedItemRow > bottomRow || bottomRow == -1)
        {
            bottomRow = selectedItemRow;
        }
        if (selectedItemColumn < leftColumn || leftColumn == -1)
        {
            leftColumn = selectedItemColumn;
        }
        if (selectedItemColumn > rightColumn || rightColumn == -1)
        {
            rightColumn = selectedItemColumn;
        }
    }

    QString clipboardText;
    for (int itRow = topRow; itRow <= bottomRow; itRow++)
    {
        for (int itColumn = leftColumn; itColumn <= rightColumn; itColumn++)
        {
            const QTableWidgetItem* item = this->item(itRow, itColumn);
            if (item->isSelected())
            {
                clipboardText += item->text();
            }
            if (itColumn < rightColumn)
            {
                clipboardText += QString("\t");
            }
        }
        if (itRow < bottomRow)
        {
            clipboardText += QString("\n");
        }
    }

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(clipboardText);
}

void QTableWidgetImproved::pasteEvent()
{
    const int nbRows = this->rowCount();
    const int nbColumns = this->columnCount();

    const QClipboard* clipboard = QApplication::clipboard();
    const QString clipboardText = clipboard->text();
    const int clipboardNbRows = clipboardText.count("\n") + 1;
    const int clipboardNbColumns = clipboardText.count("\t") / clipboardNbRows + 1;

    const QList<QTableWidgetSelectionRange> selectedRanges = this->selectedRanges();
    const int nbSelectedRanges = selectedRanges.count();
    for (int itSelectedRange = 0; itSelectedRange < nbSelectedRanges; itSelectedRange++)
    {
        const QTableWidgetSelectionRange& selectedRange = selectedRanges.at(itSelectedRange);
        const int selectedRangeTopRow = selectedRange.topRow();
        const int selectedRangeLeftColumn = selectedRange.leftColumn();
        for (int itRow = 0; itRow < clipboardNbRows; itRow++)
        {
            for (int itColumn = 0; itColumn < clipboardNbColumns; itColumn++)
            {
                const QString itemText = clipboardText.split("\n").at(itRow).split("\t").at(
                        itColumn);
                const int itemRow = selectedRangeTopRow + itRow;
                const int itemColumn = selectedRangeLeftColumn + itColumn;
                if (itemRow < nbRows && itemColumn < nbColumns)
                {
                    QTableWidgetItem* item = this->item(itemRow, itemColumn);
                    if (item->flags() & Qt::ItemIsEditable)
                    {
                        const QVariant data = item->data(Qt::DisplayRole);
                        if (data.type() == QVariant::String)
                        {
                            item->setText(itemText);
                        }
                        else if (data.type() == QVariant::Int)
                        {
                            item->setData(Qt::DisplayRole, itemText.toInt());
                        }
                        else if (data.type() == QVariant::Date)
                        {
                            item->setData(Qt::DisplayRole,
                                    QDate::fromString(itemText, "yyyy-MM-dd"));
                        }
                    }
                }
            }
        }
    }
}

//void QTableWidgetImproved::undoEvent()
//{
//    // TODO void QTableWidgetImproved::undoEvent()
//}
//
//void QTableWidgetImproved::redoEvent()
//{
//    // TODO void QTableWidgetImproved::redoEvent()
//}
