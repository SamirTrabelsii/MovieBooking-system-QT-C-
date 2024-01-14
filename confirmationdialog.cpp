#include "confirmationdialog.h"

// ... Existing code ...

ConfirmationDialog::ConfirmationDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    connectSignals();
}

void ConfirmationDialog::setupUI()
{
    setWindowTitle("Confirmation Dialog");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Custom widget for popcorn
    QWidget* popcornWidget = new QWidget(this);
    QHBoxLayout* popcornLayout = new QHBoxLayout(popcornWidget);
    QLabel* popcornImageLabel = new QLabel(popcornWidget);
    popcornImageLabel->setPixmap(QPixmap("C:/Users/msi/Downloads/popcorn.png").scaled(75, 75, Qt::KeepAspectRatio)); // Set the path to your popcorn image
    popcornImageLabel->setFixedSize(75, 75);  // Set the size of the image
    popcornCheckBox = new QCheckBox("Buy Popcorn ( 5$ )", popcornWidget);
    popcornCheckBox->setFont(QFont("Arial", 18)); // Set the font size here


    popcornLayout->addWidget(popcornImageLabel);
    popcornLayout->addWidget(popcornCheckBox);
    popcornWidget->setLayout(popcornLayout);
    mainLayout->addWidget(popcornWidget);

    // Custom widget for drink
    QWidget* drinkWidget = new QWidget(this);
    QHBoxLayout* drinkLayout = new QHBoxLayout(drinkWidget);
    QLabel* drinkImageLabel = new QLabel(drinkWidget);
    drinkImageLabel->setPixmap(QPixmap("C:/Users/msi/Downloads/juice.png").scaled(75, 75, Qt::KeepAspectRatio));  // Set the path to your drink image
    drinkImageLabel->setFixedSize(75, 75);  // Set the size of the image
    drinkCheckBox = new QCheckBox("Buy a Drink ( 3$ )", drinkWidget);
    drinkCheckBox->setFont(QFont("Arial", 18)); // Set the font size here



    drinkLayout->addWidget(drinkImageLabel);
    drinkLayout->addWidget(drinkCheckBox);
    drinkWidget->setLayout(drinkLayout);
    mainLayout->addWidget(drinkWidget);

    totalPriceLabel = new QLabel("Total Price: 10 Dinars", this);
    totalPriceLabel->setFont(QFont("Arial", 18)); // Set the font size here

    mainLayout->addWidget(totalPriceLabel);

    confirmButton = new QPushButton("Confirm Booking", this);
    mainLayout->addWidget(confirmButton);

    setLayout(mainLayout);
    connectSignals();
}


void ConfirmationDialog::connectSignals()
{
    connect(popcornCheckBox, &QCheckBox::stateChanged, this, &ConfirmationDialog::onPopcornCheckBoxChanged);
    connect(drinkCheckBox, &QCheckBox::stateChanged, this, &ConfirmationDialog::onDrinkCheckBoxChanged);
    connect(confirmButton, &QPushButton::clicked, this, &QDialog::accept);
}

bool ConfirmationDialog::isPopcornSelected() const
{
    return popcornCheckBox->isChecked();
}

bool ConfirmationDialog::isDrinkSelected() const
{
    return drinkCheckBox->isChecked();
}

double ConfirmationDialog::getTotalPrice() const
{
    double basePrice = 10.0;
    double popcornPrice = 5.0;
    double drinkPrice = 3.0;

    double totalPrice = basePrice;

    if (isPopcornSelected()) {
        totalPrice += popcornPrice;
    }
    if (isDrinkSelected()) {
        totalPrice += drinkPrice;
    }

    return totalPrice;
}

void ConfirmationDialog::onPopcornCheckBoxChanged()
{
    updateTotalPriceLabel();
}

void ConfirmationDialog::onDrinkCheckBoxChanged()
{
    updateTotalPriceLabel();
}

void ConfirmationDialog::updateTotalPriceLabel()
{
    double totalPrice = getTotalPrice();
    totalPriceLabel->setText(QString("Total Price: %1 Dinars").arg(totalPrice));
}
