#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class ConfirmationDialog : public QDialog
{
    Q_OBJECT

public:
    ConfirmationDialog(QWidget *parent = nullptr);

    bool isPopcornSelected() const;
    bool isDrinkSelected() const;
    double getTotalPrice() const;

public slots:
    void onPopcornCheckBoxChanged();
    void onDrinkCheckBoxChanged();

private:
    QCheckBox *popcornCheckBox;
    QCheckBox *drinkCheckBox;
    QPushButton *confirmButton;
    QLabel *totalPriceLabel;

    void setupUI();
    void connectSignals(); // Declaration added
    void updateTotalPriceLabel();
};

#endif // CONFIRMATIONDIALOG_H

