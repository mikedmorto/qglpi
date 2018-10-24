#ifndef DIAENTITIESLIST_H
#define DIAENTITIESLIST_H

#include <QDialog>

namespace Ui {
class DiaEntitiesList;
}

class DiaEntitiesList : public QDialog
{
    Q_OBJECT

public:
    explicit DiaEntitiesList(QWidget *parent = nullptr);
    ~DiaEntitiesList();

private:
    Ui::DiaEntitiesList *ui;
};

#endif // DIAENTITIESLIST_H
