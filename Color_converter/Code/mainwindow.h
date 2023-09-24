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
    void button_pushed();

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

    void set_value_hue_hsl();
    void set_value_saturation_hsl();
    void set_value_lightness_hsl();
    void set_text_hue_hsl();
    void set_text_saturation_hsl();
    void set_text_lightness_hsl();

    void set_value_x_xyz();
    void set_text_x_xyz();
    void set_value_y_xyz();
    void set_text_y_xyz();
    void set_value_z_xyz();
    void set_text_z_xyz();

    void set_value_l_lab();
    void set_text_l_lab();
    void set_value_a_lab();
    void set_text_a_lab();
    void set_value_b_lab();
    void set_text_b_lab();

    void set_value_h_hsv();
    void set_value_s_hsv();
    void set_value_v_hsv();
    void set_text_h_hsv();
    void set_text_s_hsv();
    void set_text_v_hsv();
private:
    Ui::MainWindow *ui;
    QString r;
    QString g;
    QString b;
    QVector<int> CMYK_to_RGB(int c, int m, int y, int k);
    QVector<int> RGB_to_CMYK(int r, int g, int b);
    double Hue_to_RGB(double v1, double v2, double vH);
    QVector<int> RGB_to_LAB(double r, double g, double b);
    double support_LAB(double x);
    double support_LAB2(double x);
    QVector<int> LAB_to_RGB(double l, double a, double b);
    QVector<int> RGB_to_HSL(double r, double g, double b);
    QVector<int> HSL_to_RGB(int h, int s, int l);
    QVector<int> RGB_to_XYZ(double r, double g, double b);
    QVector<int> XYZ_to_RGB(double x, double y, double z);
    QVector<int> HSV_to_RGB(int h, int s, int v);
    void Upgrade(QString str);
    void set_RGB();
    void set_HSL();
    void set_CMYK();
    void set_XYZ();
    void set_LAB();
    void set_HSV();
};
#endif // MAINWINDOW_H
