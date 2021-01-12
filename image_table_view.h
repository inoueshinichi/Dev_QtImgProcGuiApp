#ifndef __IMAGE_TABLE_VIEW_H__
#define __IMAGE_TABLE_VIEW_H__

// 自作

// Standard

// Qt
#include <Qt>
#include <QObject>
#include <QModelIndex>
#include <QSortFilterProxyModel>
#include <QRegExp>

#include <QStandardItem>
#include <QStandardItemModel>
#include <QBrush>
#include <QImage>
#include <QPixmap>
#include <QIcon>

#include <QStyledItemDelegate>
#include <QTableView>
#include <QWidget>

class ImageTableView : public QTableView
{

public:
    // ImageTableView(QWidget* parent=nullptr) : QTableView(parent) {}
    // virtual ~ImageTableView() {}
    ImageTableView(QWidget* parent=nullptr);
    virtual ~ImageTableView();
};

#endif