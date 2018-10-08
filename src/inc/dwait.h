#ifndef DWAIT_H
#define DWAIT_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class DWait;
}

class DWait : public QDialog
{
    Q_OBJECT

public:
    explicit DWait(QWidget *parent = 0);
    ~DWait();
    void start(const QString &text, bool progress = false);
    void stop();
    bool tryStopState();

private:
    Ui::DWait *ui;
    bool isStoped;
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);
private slots:
    void slotCancel();
public slots:
    void setProgress(qint64 currentstatus, qint64 maxstatus);
signals:
    void sigCancel();
};

#endif // DWAIT_H
