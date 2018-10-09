#ifndef MWSTART_H
#define MWSTART_H

#include <QMainWindow>

namespace Ui {
class MWStart;
}

class MWStart : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWStart(QWidget *parent = nullptr);
    ~MWStart();

private:
    Ui::MWStart *ui;
};

#endif // MWSTART_H
