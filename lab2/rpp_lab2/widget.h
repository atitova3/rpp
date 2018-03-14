#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <vector>
using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void load();
    void vuvod(vector<vector<QString> >&);

private slots:
    void on_pushButton_clicked();

    void on_loading_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
