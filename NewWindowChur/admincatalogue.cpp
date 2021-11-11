#include "admincatalogue.h"
#include "ui_admincatalogue.h"
#include "createfiles.h"
#include "admineditbook.h"
#include <QWidget>
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QTableWidget>
#include <QStringList>
#include <QItemSelectionModel>
#include <QFormLayout>
#include <QFrame>
#include <QScrollArea>
#include <QGroupBox>
#include <QPushButton>

admincatalogue::admincatalogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admincatalogue)
{
    ui->setupUi(this);

    QPixmap Img(":/images/YoobeeLibraries.png");
    ui->img->setPixmap(Img.scaled(150, 150, Qt::KeepAspectRatio));

    QStringList booksData = CreateFiles::GetFileData(CSVFiles::_Catalogue);

    ui->adminCatalogue->setStyleSheet("QHeaderView::section { background-color: rgba(254, 222, 255, 0.3) }");
    // Because we have 5 columns, we insert a column 5 times
    for (int i = 0; i < 6; i++)
    {
       ui->adminCatalogue->insertColumn(ui->adminCatalogue->columnCount());
    }
    // We have headers in our CSV file, so I use them to set the labels for the table.
    ui->adminCatalogue->setHorizontalHeaderLabels({booksData[0], booksData[1], booksData[2], booksData[3], booksData[4], booksData[5]});
    ui->adminCatalogue->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->adminCatalogue->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->adminCatalogue->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->adminCatalogue->setSelectionMode(QHeaderView::NoSelection);
    // Create the rows of the QTableWidget
    int i = 6;
    int rowCount = (booksData.size() / 6) - 1;
    for (int row = 0; row < rowCount; row++)
    {
        ui->adminCatalogue->insertRow(ui->adminCatalogue->rowCount());
        for (int col = 0; col < 6; col++)
        {
            if (booksData[i].contains(":/images")){
                ui->adminCatalogue->verticalHeader()->setSectionResizeMode(row, QHeaderView::Stretch);
                QWidget* item = new QWidget(ui->adminCatalogue);
                QString imagePath = booksData[i];
                QPixmap p(imagePath);
                QLabel* l = new QLabel(item);
                l->setPixmap(p.scaled(60,90));
                ui->adminCatalogue->setCellWidget(row, col, item);
            }
            else if (col == 5){
                QWidget* item = new QWidget(ui->adminCatalogue);
                QPushButton* push = new QPushButton(item);
                push->setText("Edit");
                push->resize(QSize(40,20));
                connect(push, SIGNAL(clicked()), this, SLOT(mySlot()));
                ui->adminCatalogue->setCellWidget(row, col, item);


            }
            else {
             QTableWidgetItem *item = new QTableWidgetItem(QString(booksData[i]));
             ui->adminCatalogue->setItem(row, col, item);
            }
            i++;
        }
    }
}

admincatalogue::~admincatalogue()
{
    delete ui;
}

void admincatalogue::on_back_clicked()
{
    close();
    emit ClosedAdminHome();
}



