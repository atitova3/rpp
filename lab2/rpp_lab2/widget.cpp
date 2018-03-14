#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <vector>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //load();//Load from log.txt
}

void Widget::on_loading_clicked()//пока все содрано с функции load()
{
    QFile file ("D:/rpp/rpp_lab2/CSV.txt");
    QByteArray reading;
    std::vector<std::vector<QString>> stroki;//в этом векторе хранятся слова
    QString line;
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Файл не открыт";
    }
    else
    {
        qDebug() << "Файл открыта";
        QTextStream textStream(&file);
        QString line;
        QString text;
        int chet;
        int kov;
        int zap;
        int flag;//отмечаем после " чтобы проверить на дальнейшие шаги
        for (int j = 0; !textStream.atEnd(); j++)
        {
           // qDebug() << "цикл";
            line = textStream.readLine();
            chet = 0;
            text = "";
            std::vector<QString> one_str;
            kov = 0;//
            zap = 0;//
            for (int i = 0; i < line.size(); i++)
            {
                //qDebug() << text;
                //kov = 0;
                //zap = 0;
                if ((line[i] == ',')&&((kov == 0)||(kov == 2)))//
                {
                    qDebug() << text << "...";//
                    one_str.push_back(text);//stroki.at(chet).push_back(text);//закидываем в вектор строки ОДНОЙ
                    text ="";
                    zap = 0;
                    kov = 0;
                    flag = 0;//
                }
                else
                {

                    if ((line[i] == '"')&&(flag ==  1))
                    {
                        text += line[i];
                        kov --;
                        qDebug() << "kov:_________" << kov;
                        flag = 0;//
                    }
                    else
                    {

                        if (line[i] == '"')
                        {
                            kov ++;
                            flag = 1; //
                        }
                        else
                        {
                            if((line[i] == '\n')||(line[i] == '\0'))
                            {

                            }
                            else
                            {
                                text += line[i];
                                flag = 0;
                            }
                            //text += line[i];
                            //flag=0;
                        }
                    }
                }

            }
            stroki.push_back(one_str);//вектор добовляет строку
          }
          file.close();
        }
        vuvod(stroki);//перепись записей из вектора в таблицу
        return;
    }

void Widget::vuvod(std::vector<std::vector<QString> > &mass)
{
    int max = mass.at(0).size();
    for (int i = 1; i < mass.size(); i++)//поиск ширины
    {
        if (max < mass.at(i).size())
        {
            max = mass.at(i).size();
        }
    }
    qDebug() << "max = " << max;//
    ui->tab->setColumnCount(max);//проблема
    ui->tab->setRowCount(mass.size());

    for (int i = 0; i < mass.size(); i++)//вывод
    {
        for (int j = 0; j < mass.at(i).size(); j ++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(mass.at(i).at(j));
            ui->tab->setItem(i,j,item);
        }
    }
    return;
}


void Widget::load()
{
    QFile file ("E:/Ania/rpp/rpp_lab2/log.txt");
    QByteArray reading;
    QString line;
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Файл не открыт";
    }
    else
    {
        QTextStream textStream(&file);

        int num = 0;
        int flag = 0;
        line = textStream.readLine();
        for (int i = 0; i <= line.size(); i++)
        {
            if ((line[i] >= '0')&&(line[i] <= '9'))
            {
                num = num*10 + line[i].digitValue();
            }
            else
            {
                if (flag == 0)
                {
                    ui->tab->setColumnCount(num);
                    flag ++;
                    num = 0;
                }
                else
                {
                    ui->tab->setRowCount(num);
                }
            }
        }

        for (int i = 0; !textStream.atEnd(); i++)
        {
            line = textStream.readLine();
            QString text = "";
            int y = 0;
            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] != ' ')
                {
                    text += line[j];
                }
                else
                {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setText(text);
                    ui->tab->setItem(i,y,item);
                    text = "";
                    y++;
                }
            }
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(text);
            ui->tab->setItem(i,y,item);
        }
        file.close();
    }
    return;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    close();
}
