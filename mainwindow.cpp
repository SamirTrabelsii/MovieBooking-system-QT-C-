#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "confirmationdialog.h"
#include "form.h"
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QRegularExpression>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>


MainWindow::MainWindow(const QString &movieTitle, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentMovieTitle(movieTitle)
{
    ui->setupUi(this);



    imageLabels = findChildren<QLabel*>(QRegularExpression("imageLabel\\d+"));
    cancelButtons = findChildren<QPushButton*>(QRegularExpression("cancelButton\\d+"));
    resetAllButton = findChild<QPushButton*>("resetAllButton");
    QList<QPushButton*> buttons = findChildren<QPushButton*>(QRegularExpression("pushButton\\d+"));
    for (int i = 0; i < buttons.size(); ++i) {
        connect(buttons[i], &QPushButton::clicked, this, [this, i]() {
            onButtonClicked(i);
        });
        connect(cancelButtons[i], &QPushButton::clicked, this, [this, i]() {
            onCancelButtonClicked(i);
        });
    }
    setWindowTitle("Booking for " + currentMovieTitle);

    seatBookedStatus.resize(imageLabels.size(), false);
    // Assuming you have a QLabel named lblImage
    QLabel* label_3 = ui->label_3;

    // Load the image dynamically
    QPixmap pixmap("C:/Users/msi/Downloads/screen.png");
    label_3->setPixmap(pixmap.scaled(300,150));
    if(currentMovieTitle=="Jujutsu Kaisen"){
        QLabel* label_4 = ui->label_4;
        QLabel* label_5 = ui->label_5;
        QPixmap pixmap("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\jujutsuKaisen.jpg");
        label_4->setPixmap(pixmap.scaled(101,141));
        label_5->setPixmap(pixmap.scaled(101,141));
    }else if(currentMovieTitle=="One Piece Red Movie"){
        QLabel* label_4 = ui->label_4;
        QLabel* label_5 = ui->label_5;
        QPixmap pixmap("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\onePiece.jpg");
        label_4->setPixmap(pixmap.scaled(101,141));
        label_5->setPixmap(pixmap.scaled(101,141));
    }else{
        QLabel* label_4 = ui->label_4;
        QLabel* label_5 = ui->label_5;
        QPixmap pixmap("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\oppenheimer.jpg");
        label_4->setPixmap(pixmap.scaled(101,141));
        label_5->setPixmap(pixmap.scaled(101,141));
    }
    connect(resetAllButton, &QPushButton::clicked, this, &MainWindow::onResetAllClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked(int index)
{
    if (index >= 0 && index < imageLabels.size() && !seatBookedStatus[index]) {
        QPixmap pixmap("C:/Users/msi/Downloads/booked.png");
        imageLabels[index]->setPixmap(pixmap.scaled(imageLabels[index]->size(), Qt::KeepAspectRatio));
        showConfirmationDialog(index);
        seatBookedStatus[index] = true; // Mark the seat as booked
        qDebug() << "Champ " << index + 1 << " réservé";

        // Disable the book button for the booked seat and set a different color
        QPushButton* bookButton = findChild<QPushButton*>(QString("pushButton%1").arg(index + 1));
        if (bookButton) {
            bookButton->setEnabled(false);
        }
    }
}


void MainWindow::showConfirmationDialog(int index)
{
    ConfirmationDialog confirmationDialog(this);
    confirmationDialog.resize(400, 500);

    // Afficher le dialogue
    if (confirmationDialog.exec() == QDialog::Accepted) {

        double totalPrice = confirmationDialog.getTotalPrice();

        qDebug() << "Total Price: " << totalPrice;
    }
}

double MainWindow::calculateTotalPrice(bool popcornSelected, bool drinkSelected)
{
    double basePrice = 10.0; // Example base price
    double popcornPrice = 5.0;
    double drinkPrice = 3.0;
    double totalPrice = basePrice;
    if (popcornSelected) {
        totalPrice += popcornPrice;
    }
    if (drinkSelected) {
        totalPrice += drinkPrice;
    }
    return totalPrice;
}

void MainWindow::onCancelButtonClicked(int index)
{
    if (index >= 0 && index < imageLabels.size() && seatBookedStatus[index]) {
        QPixmap pixmap("C:/Users/msi/Downloads/available.png");
        imageLabels[index]->setPixmap(pixmap.scaled(imageLabels[index]->size(), Qt::KeepAspectRatio));
        qDebug() << "Annulation de la réservation pour le champ " << index + 1;
        seatBookedStatus[index] = false; // Mark the seat as available

        // Disable the cancel button for the available seat and set a different style
        QPushButton* cancelButton = findChild<QPushButton*>(QString("cancelButton%1").arg(index + 1));
        if (cancelButton) {
            cancelButton->setEnabled(false);
        }
    }
}


void MainWindow::onResetAllClicked()
{
    for (QLabel* label : imageLabels) {
        label->setPixmap(QPixmap("C:/Users/msi/Downloads/available.png"));
    }
    for (int i = 0; i < seatBookedStatus.size(); ++i) {
        seatBookedStatus[i] = false;

        // Enable both book and cancel buttons and reset their styles
        QPushButton* bookButton = findChild<QPushButton*>(QString("pushButton%1").arg(i + 1));
        if (bookButton) {
            bookButton->setEnabled(true);
        }

        QPushButton* cancelButton = findChild<QPushButton*>(QString("cancelButton%1").arg(i + 1));
        if (cancelButton) {
            cancelButton->setEnabled(true);
        }
    }
    qDebug() << "Tous les champs réinitialisés.";

    // Mettez à jour l'interface ou effectuez d'autres actions nécessaires
}

void MainWindow::on_pushButton_clicked()
{
    Form *form = new Form();
    form->show();
    this->hide();  // or this->close();
}

