#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QDialog>
#include <QMainWindow>

namespace Ui {
class OutputWindow;
}

class OutputWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OutputWindow(QString &p_hCode, QString &p_cCode, QMainWindow *mainWindow = 0);
    ~OutputWindow();

private:
    Ui::OutputWindow *ui;
};

#endif // OUTPUTWINDOW_H
