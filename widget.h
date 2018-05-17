#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_PreamBtn_clicked();

    void on_DelimBtn_clicked();

    void on_DestiBtn_clicked();

    void on_SourceBtn_clicked();

    void on_LengthBtn_clicked();

    void on_DataBtn_clicked();

    void on_CheckBtn_clicked();

    void on_ShowallBtn_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
