#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QPixmap pme("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\onePiece.jpg");
    if (pme.isNull()) {
        qDebug() << "Failed to load the image";
    } else {
        ui->lblMovie->setPixmap(pme.scaled(200,320));
    }
    QPixmap pmee("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\jujutsuKaisen.jpg");
    if (pmee.isNull()) {
        qDebug() << "Failed to load the image";
    } else {
        ui->lblMovie_2->setPixmap(pmee.scaled(200,320));
    }
    QPixmap pmeee("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\oppenheimer.jpg");
    if (pmeee.isNull()) {
        qDebug() << "Failed to load the image";
    } else {
        ui->lblMovie_3->setPixmap(pmeee.scaled(200,320));
    }
    addMovie("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\onePiece.jpg", "One Piece Red Movie", ui->radioButton);
    addMovie("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\jujutsuKaisen.jpg", "Jujutsu Kaisen", ui->radioButton_2);
    addMovie("C:\\Users\\msi\\Downloads\\QT_Project_on_Movie_Ticket_Booking\\QT_Project_On_Movie_Ticket_Booking\\img\\oppenheimer.jpg", "Oppenheimer", ui->radioButton_3);
}

Form
    ::~Form
    ()
{
    delete ui;
}

void Form
    ::addMovie(const QString &imagePath, const QString &title, QRadioButton *radioButton)
{
    QPixmap pixmap(imagePath);
    if (pixmap.isNull()) {
        qDebug() << "Failed to load the image" << imagePath;
        return;
    }

    // Store title in a map with corresponding radio button
    movieMap[radioButton] = title;
}


void Form::on_pushButton_clicked()
{
    QString selectedMovie;
    for (auto it = movieMap.begin(); it != movieMap.end(); ++it) {
        if (it.key()->isChecked()) {
            selectedMovie = it.value();
            break;
        }
    }

    if (!selectedMovie.isEmpty()) {
        // Pass the selected movie title to the main window
        MainWindow *mainWindow = new MainWindow(selectedMovie);
        mainWindow->show();
        this->hide();  // or this->close();
    } else {
        qDebug() << "No movie selected";
    }
}




