#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "outputwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->creationDate->setDate(QDate::currentDate());
    ui->headerEdit->setVisible(false);

    connect(ui->name, SIGNAL(textChanged(QString)), this, SLOT(updateHeader()));
    connect(ui->checkHeader, SIGNAL(clicked(bool)), this, SLOT(updateHeader()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    if(ui->name->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Error"), tr("class name not filled"));
    }
    //test upper case ?
    else
    {
        m_generatedHpp = generateHpp();
        m_generatedCpp = generateCpp();

        OutputWindow* l_OutputWindow = new OutputWindow(m_generatedHpp, m_generatedCpp, this);
        l_OutputWindow->show();
    }
}

QString MainWindow::generateHpp()
{
    QString l_hCode;

    //comments
    if(ui->groupComments->isChecked())
    {
        l_hCode += "/*\n";
        l_hCode += "Author : " + ui->author->text() + "\n";
        l_hCode += "Creation date : " + ui->creationDate->date().toString() + "\n";
        l_hCode += "Role :\n" + ui->classRole->toPlainText() + "\n*/\n\n";
    }

    //Header
    if(ui->checkHeader->isChecked())
    {
        l_hCode += "#ifndef " + ui->name->text().toUpper() + "\n";//m_headerEdit.text() + "\n";
        l_hCode += "#define " + ui->name->text().toUpper() + "\n";//m_headerEdit.text() + "\n";
    }

    //class
    l_hCode += "class " + ui->name->text();

    if(!ui->motherClass->text().isEmpty())
    {
        l_hCode += " : public " + ui->motherClass->text();
    }

    l_hCode += "\n{\npublic:\n";
    if(ui->checkConstructor->isChecked())
    {
        l_hCode += "    " + ui->name->text() + "();\n";
    }
    if(ui->checkDestructor->isChecked())
    {
        l_hCode += "    ~" + ui->name->text() + "();\n";
    }

    l_hCode += "\n\n    protected:\n";
    l_hCode += "\n\n    private:\n";
    l_hCode += "};\n\n";

    //close header
    if(ui->checkHeader->isChecked())
    {
        l_hCode += "#endif //" + ui->name->text().toUpper() + "\n";//m_headerEdit.text() + "\n";
    }

    return l_hCode;
}

QString MainWindow::generateCpp()
{
    return "this will be the cpp";
}

void MainWindow::updateHeader()
{
    if( ui->checkHeader->isChecked() && !(ui->name->text().isEmpty()) )
    {
        ui->headerEdit->setText("HEADER_" + ui->name->text().toUpper());
    }
    else
    {
        ui->headerEdit->setText(QString());
    }
}

void MainWindow::saveCode()
{
    QString l_directoryName = QFileDialog::getExistingDirectory(this, tr("save file"), QString(), QFileDialog::ShowDirsOnly) + "/";

    QFile l_headerFile(l_directoryName + "/" + ui->name->text().toLower() + ".h");
    if(l_headerFile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&l_headerFile);
        stream << m_generatedHpp << endl;
        l_headerFile.close();
    }

    QFile l_sourceFile(l_directoryName + "/" + ui->name->text().toLower() + ".cpp");
    if(l_sourceFile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&l_sourceFile);
        stream << m_generatedCpp << endl;
        l_sourceFile.close();
    }
}
