#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void set_value_red_rgb();
    void set_value_green_rgb();
    void set_value_blue_rgb();
    void set_text_red_rgb();
    void set_text_green_rgb();
    void set_text_blue_rgb();

    void set_value_cyan_cmyk();
    void set_value_magenta_cmyk();
    void set_value_yellow_cmyk();
    void set_value_key_cmyk();
    void set_text_cyan_cmyk();
    void set_text_magenta_cmyk();
    void set_text_yellow_cmyk();
    void set_text_key_cmyk();


private:
    Ui::MainWindow *ui;
    QString r;
    QString g;
    QString b;
    QVector<int> CMYK_to_RGB(int c, int m, int y, int k);
    QVector<int> RGB_to_CMYK(int r, int g, int b);
    void set_CMYK();
};
#endif // MAINWINDOW_H
