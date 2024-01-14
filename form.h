#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include <QRadioButton>
#include <QMap>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;
    QMap<QRadioButton*, QString> movieMap;

    void addMovie(const QString &imagePath, const QString &title, QRadioButton *radioButton);
};

#endif // FORM_H
