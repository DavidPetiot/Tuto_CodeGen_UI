#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_generateButton_clicked();
    void saveCode();
    void updateHeader();

private:
    QString generateHpp();
    QString generateCpp();

private:
    Ui::MainWindow *ui;

    QString m_generatedHpp;
    QString m_generatedCpp;
};

#endif // MAINWINDOW_H
