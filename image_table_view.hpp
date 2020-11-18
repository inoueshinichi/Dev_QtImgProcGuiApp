#ifndef __IMAGE_TABLE_VIEW_HPP__
#define __IMAGE_TABLE_VIEW_HPP__

#include <QTableView>
#include <QWidget>


class ImageTableView : public QTableView
{
    Q_OBJECT

public:
    ImageTableView(QWidget *parent = nullptr);
    virtual ~ImageTableView();
};


#endif // __IMAGE_TABLE_VIEW_HPP__