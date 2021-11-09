// ------------------------------------------------------------
//
// CATALOGUE SCREEN
// Written by Jakob
//
// The "Catalogue", originally just supposed to be a screen
// to show the current books the library is holding, has
// evolved into the users home screen once they've logged in.
//
// It holds different screens in seperate tabs for easy
// maneuverability. It includes the Home tab, Catalogue tab,
// and Your account tab. Each tab has it's own buttons and
// functionality.
//
// HOME TAB:
// A home screen that displays any new books recently added
// within the last two days. It may also hold any updates
// an admin wants to write for every user to see.
//
// CATALOGUE TAB:
// Displays all books with a search bar. User can look for
// a book and click checkout, which will open a dialog window
// from "checkoutscreen.cpp".
//
// YOUR ACCOUNT TAB:
// The user can view their account details, picture or logout
// from the home screen. They may also update anything to do
// with their account/
//
// ------------------------------------------------------------

#include "catalogue.h"
#include "ui_catalogue.h"
#include "createfiles.h"
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QFormLayout>
#include <QFrame>
#include <QScrollArea>
#include <QGroupBox>

Catalogue::Catalogue(QWidget *parent, QString memID, QString memAvatar, QString memName, QString memEmail, QString memPhone) :
    QDialog(parent),
    ui(new Ui::Catalogue)
{
    ui->setupUi(this);

    // Setting private variables (this is for the search function)
    _memID = memID;
    _memName = memName;

    // Set users details
    QPixmap p(memAvatar);
    ui->profile_picture->setPixmap(p.scaled(120,120));
    ui->welcomeBack->setText("Welcome back, " + memName);

    ui->user_name->setText(memName);
    ui->user_email->setText("<b>Email:</b> " + memEmail);
    ui->user_phonenumber->setText("<b>Phone:</b> " + memPhone);
    ui->user_id->setText("<b>Your ID:</b> " + memID);

    // Array control
    QStringList catalogue = CreateFiles::GetFileData(CSVFiles::_Catalogue);
    const int arraySize = (catalogue.size() / 6) - 1;

    // LAYOUTS
    QGroupBox* groupBox = new QGroupBox;
    QFormLayout* formLayout = new QFormLayout();
    groupBox->setLayout(formLayout);

    QFrame* lines1[arraySize];
    QFrame* lines2[arraySize];
    QLabel* bookImage[arraySize];
    QLabel* bookName[arraySize];
    QLabel* bookAuthor[arraySize];
    QLabel* bookCopies[arraySize];
    QPushButton* checkoutButton[arraySize];
    CheckOutScreen* checkoutScreen[arraySize];

    int t = 6;
    // Initalize all widgets
    for (int row = 0; row < arraySize; row++)
    {
        // Book image
        QString imagePath = catalogue[t + 1]; // Skip the first spot of the list because it's the ID
        QPixmap p(imagePath);
        bookImage[row] = new QLabel;
        bookImage[row]->setPixmap(p.scaled(90, 120));

        // Book name
        bookName[row] = new QLabel;
        bookName[row]->setText("Book name: " + catalogue[t + 2]);

        // Book author
        bookAuthor[row] = new QLabel;
        bookAuthor[row]->setText("Author: " + catalogue[t + 3]);

        // Book copies
        bookCopies[row] = new QLabel;
        bookCopies[row]->setText("Copies: " + catalogue[t + 4]);

        // Checkout button
        const QSize btnSize = QSize(80, 25);
        checkoutButton[row] = new QPushButton;
        checkoutButton[row]->setText("Checkout");
        checkoutButton[row]->setFixedSize(btnSize);
        checkoutButton[row]->setStyleSheet("QPushButton { border: 1px solid black; }"
                                           "QPushButton:pressed { border-color: #e7e7e7; background-color: #f4f4f4; }");

        // Sending Book ID, Book Name, Member ID, Member Name, Date through CheckOutScreen constructor.
        checkoutScreen[row] = new CheckOutScreen(NULL, memName, memID, catalogue[t], catalogue[t + 2], catalogue[t + 3], catalogue[t + 4]);
        checkoutScreen[row]->setWindowTitle("Checkout a book");
        connect(checkoutButton[row], SIGNAL(clicked()), checkoutScreen[row], SLOT(exec()));

        // Horizontal Lines
        lines1[row] = new QFrame();
        lines1[row]->setLineWidth(1);
        lines1[row]->setFrameShape(QFrame::HLine);
        lines1[row]->setFrameShadow(QFrame::Sunken);

        lines2[row] = new QFrame();
        lines2[row]->setLineWidth(1);
        lines2[row]->setFrameShape(QFrame::HLine);
        lines2[row]->setFrameShadow(QFrame::Sunken);

        t = t + 6;
    }

    // Add all of the widgets into the layouts
    for (int row = 0; row < arraySize; row++)
    {
        formLayout->setWidget(row, QFormLayout::LabelRole, bookImage[row]);

        QVBoxLayout* verticalLayout = new QVBoxLayout();
        formLayout->setLayout(row, QFormLayout::FieldRole, verticalLayout);

        verticalLayout->addWidget(lines1[row]);
        verticalLayout->addWidget(bookName[row]);
        verticalLayout->addWidget(bookAuthor[row]);
        verticalLayout->addWidget(bookCopies[row]);
        verticalLayout->addWidget(checkoutButton[row]);
        verticalLayout->addWidget(lines2[row]);
        formLayout->setContentsMargins(10, 5, 0, 20);
        formLayout->setVerticalSpacing(30);
    }

    ui->scrollArea->setWidget(groupBox);
    qDebug() << "test group box";
    groupBox->setStyleSheet("background-color: white;");
}

Catalogue::~Catalogue()
{
    delete ui;
}

void Catalogue::on_yourAccount_logout_clicked()
{
    close();
    emit OpenMainMenu();
}

// Search bar functionality
void Catalogue::on_searchBar_textChanged(const QString &arg1)
{
    QStringList foundData;

    if (CreateFiles::_catalogue.open(QIODevice::ReadOnly))
    {
        QTextStream in(&CreateFiles::_catalogue);
        while(!in.atEnd())
        {
            QString line = CreateFiles::_catalogue.readLine().replace("\r\n","");
            if (line != "BOOK ID, IMAGE, BOOK NAME, AUTHOR, COPIES") // These are the headers of the CSV file. This just skips over it.
            {
                if (line.toLower().contains(arg1.toLower()))
                {
                    foundData.append(line.split(','));
                }
            }
        }
    }
    CreateFiles::_catalogue.close();

    // Array control
    const int arraySize = (foundData.size() / 5) - 1;

    // LAYOUTS
    QGroupBox* groupBox = new QGroupBox;
    QFormLayout* formLayout = new QFormLayout();
    groupBox->setLayout(formLayout);

    QFrame* lines1[arraySize];
    QFrame* lines2[arraySize];
    QLabel* bookImage[arraySize];
    QLabel* bookName[arraySize];
    QLabel* bookAuthor[arraySize];
    QLabel* bookCopies[arraySize];
    QPushButton* checkoutButton[arraySize];
    CheckOutScreen* checkoutScreen[arraySize];

    int t = 5;
    // Initalize all widgets
    for (int row = 0; row < arraySize; row++)
    {
        // Book image
        QString imagePath = foundData[t + 1];
        QPixmap p(imagePath);
        bookImage[row] = new QLabel;
        bookImage[row]->setPixmap(p.scaled(90, 120));

        // Book name
        bookName[row] = new QLabel;
        bookName[row]->setText("Book name: " + foundData[t + 2]);

        // Book authour
        bookAuthor[row] = new QLabel;
        bookAuthor[row]->setText("Author: " + foundData[t + 3]);

        // Book copies
        bookCopies[row] = new QLabel;
        bookCopies[row]->setText("Copies: " + foundData[t + 4]);

        // Checkout button
        const QSize btnSize = QSize(80, 25);
        checkoutButton[row] = new QPushButton;
        checkoutButton[row]->setText("Checkout");
        checkoutButton[row]->setFixedSize(btnSize);
        checkoutButton[row]->setStyleSheet("QPushButton { border: 1px solid black; }"
                                           "QPushButton:pressed { border-color: #e7e7e7; background-color: #f4f4f4; }");

        // Sending Book ID, Book Name, Member ID, Member Name, Date through CheckOutScreen constructor.
        checkoutScreen[row] = new CheckOutScreen(NULL, _memName, _memID, foundData[t], foundData[t + 2], foundData[t + 3], foundData[t + 4]);
        connect(checkoutButton[row], SIGNAL(clicked()), checkoutScreen[row], SLOT(exec()));

        // Horizontal Lines
        lines1[row] = new QFrame();
        lines1[row]->setLineWidth(1);
        lines1[row]->setFrameShape(QFrame::HLine);
        lines1[row]->setFrameShadow(QFrame::Sunken);

        lines2[row] = new QFrame();
        lines2[row]->setLineWidth(1);
        lines2[row]->setFrameShape(QFrame::HLine);
        lines2[row]->setFrameShadow(QFrame::Sunken);

        t = t + 5;
    }

    // Add all of the widgets into the layouts
    for (int row = 0; row < arraySize; row++)
    {
        formLayout->setWidget(row, QFormLayout::LabelRole, bookImage[row]);

        QVBoxLayout* verticalLayout = new QVBoxLayout();
        formLayout->setLayout(row, QFormLayout::FieldRole, verticalLayout);

        verticalLayout->addWidget(lines1[row]);
        verticalLayout->addWidget(bookName[row]);
        verticalLayout->addWidget(bookAuthor[row]);
        verticalLayout->addWidget(bookCopies[row]);
        verticalLayout->addWidget(checkoutButton[row]);
        verticalLayout->addWidget(lines2[row]);
        formLayout->setContentsMargins(10, 5, 0, 20);
        formLayout->setVerticalSpacing(30);
    }

    ui->scrollArea->setWidget(groupBox);
    groupBox->setStyleSheet("background-color: white;");
}

void Catalogue::on_yourAccount_update_clicked()
{

}


void Catalogue::on_yourAccount_updatePic_clicked()
{

}

