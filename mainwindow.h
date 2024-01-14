#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &movieTitle, QWidget *parent = nullptr);
    ~MainWindow();
    void showConfirmationDialog(int index);  // Declare the function
    double calculateTotalPrice(bool popcornSelected, bool drinkSelected);  // Declare the function



private slots:
    void onButtonClicked(int index);
    void onCancelButtonClicked(int index);
    void onResetAllClicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QLabel*> imageLabels; // Labels pour afficher les images
    QVector<QPushButton*> cancelButtons;
    QPushButton* resetAllButton;
    QString currentMovieTitle;  // Add member variable to store the current movie title
    QVector<bool> seatBookedStatus; // To track the booking status of each seat


};

#endif // MAINWINDOW_H
