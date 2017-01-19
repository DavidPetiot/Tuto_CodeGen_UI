#include "outputwindow.h"
#include "ui_outputwindow.h"
#include "mainwindow.h"

OutputWindow::OutputWindow(QString &p_hCode, QString &p_cCode, QMainWindow *mainWindow) :
    ui(new Ui::OutputWindow)
{
    ui->setupUi(this);

    QTextEdit* hppOutput = ui->hppOutput;
    hppOutput->setPlainText(p_hCode);
    hppOutput->setReadOnly(true);
    hppOutput->setFont(QFont("courier"));
    hppOutput->setLineWrapMode(QTextEdit::NoWrap);

    QTextEdit* cppOutput = ui->cppOutput;
    cppOutput->setPlainText(p_cCode);
    cppOutput->setReadOnly(true);
    cppOutput->setFont(QFont("courier"));
    cppOutput->setLineWrapMode(QTextEdit::NoWrap);

    QObject::connect(ui->saveButton, SIGNAL(clicked()), mainWindow, SLOT(saveCode()));
}

OutputWindow::~OutputWindow()
{
    delete ui;
}
