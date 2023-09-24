#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <QColor>
#include <qmath.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    r = QString::number(ui->red_slider->value());
    ui->red_text->setText(r);
    g = QString::number(ui->green_slider->value());
    ui->green_text->setText(g);
    b = QString::number(ui->blue_slider->value());
    ui->blue_text->setText(b);
    Upgrade("");
    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(button_pushed()));
    connect(ui->red_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_red_rgb()));
    connect(ui->green_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_green_rgb()));
    connect(ui->blue_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_blue_rgb()));
    connect(ui->red_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_red_rgb()));
    connect(ui->green_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_green_rgb()));
    connect(ui->blue_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_blue_rgb()));
    connect(ui->cyan_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_cyan_cmyk()));
    connect(ui->cyan_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_cyan_cmyk()));
    connect(ui->magenta_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_magenta_cmyk()));
    connect(ui->magenta_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_magenta_cmyk()));
    connect(ui->yellow_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_yellow_cmyk()));
    connect(ui->yellow_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_yellow_cmyk()));
    connect(ui->key_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_key_cmyk()));
    connect(ui->key_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_key_cmyk()));
    connect(ui->hue_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_hue_hsl()));
    connect(ui->hue_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_hue_hsl()));
    connect(ui->saturation_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_saturation_hsl()));
    connect(ui->saturation_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_saturation_hsl()));
    connect(ui->lightness_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_lightness_hsl()));
    connect(ui->lightness_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_lightness_hsl()));
    connect(ui->x_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_x_xyz()));
    connect(ui->x_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_x_xyz()));
    connect(ui->y_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_y_xyz()));
    connect(ui->y_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_y_xyz()));
    connect(ui->z_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_z_xyz()));
    connect(ui->z_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_z_xyz()));
    connect(ui->l_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_l_lab()));
    connect(ui->l_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_l_lab()));
    connect(ui->a_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_a_lab()));
    connect(ui->a_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_a_lab()));
    connect(ui->b_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_b_lab()));
    connect(ui->b_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_b_lab()));
    connect(ui->h_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_h_hsv()));
    connect(ui->h_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_h_hsv()));
    connect(ui->s_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_s_hsv()));
    connect(ui->s_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_s_hsv()));
    connect(ui->v_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(set_text_v_hsv()));
    connect(ui->v_text, SIGNAL(editingFinished()),
            this, SLOT(set_value_v_hsv()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_value_red_rgb()
{
    r = ui->red_text->text();
    int val = r.toInt();
    if(val > 255)
    {
        QMessageBox::warning(this, "Invalid data", "Value of RGB must be equal or less than 255!");
        r = "255";
        Upgrade("rgb");
        return;
    }
    ui->red_slider->setValue(val);
    Upgrade("rgb");
}

void MainWindow::set_value_green_rgb()
{
    g = ui->green_text->text();
    int val = g.toInt();
    if(val > 255)
    {
        QMessageBox::warning(this, "Invalid data", "Value of RGB must be equal or less than 255!");
        g = "255";
        Upgrade("rgb");
        return;
    }
    ui->green_slider->setValue(val);
    Upgrade("rgb");
}

void MainWindow::set_value_blue_rgb()
{
    b = ui->blue_text->text();
    int val = b.toInt();
    if(val > 255)
    {
        QMessageBox::warning(this, "Invalid data", "Value of RGB must be equal or less than 255!");
        b = "255";
        Upgrade("rgb");
        return;
    }
    ui->blue_slider->setValue(val);
    Upgrade("rgb");
}

void MainWindow::set_text_red_rgb()
{
    r = QString::number(ui->red_slider->value());
    ui->red_text->setText(r);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    Upgrade("rgb");
}

void MainWindow::set_text_green_rgb()
{
    g = QString::number(ui->green_slider->value());
    ui->green_text->setText(g);
    Upgrade("rgb");
}

void MainWindow::set_text_blue_rgb()
{
    b = QString::number(ui->blue_slider->value());
    ui->blue_text->setText(b);
    Upgrade("rgb");
}

void MainWindow::set_text_cyan_cmyk()
{
    auto value = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    r = QString::number(value[0]);
    Upgrade("cmyk");
    ui->cyan_text->setText(QString::number(ui->cyan_slider->value()));
}

void MainWindow::set_value_cyan_cmyk()
{
    QString c = ui->cyan_text->text();
    int val = c.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of CMYK must be equal or less than 100!");
        ui->cyan_text->setText("100");
        ui->cyan_slider->setValue(100);
        auto rgb = CMYK_to_RGB(100, ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
        r = QString::number(rgb[0]);
        Upgrade("cmyk");
        return;
    }
    ui->cyan_slider->setValue(val);
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    r = QString::number(rgb[0]);
    Upgrade("cmyk");
}

void MainWindow::set_text_magenta_cmyk()
{
    auto value = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    g = QString::number(value[1]);
    Upgrade("cmyk");
    ui->magenta_text->setText(QString::number(ui->magenta_slider->value()));
}

void MainWindow::set_value_magenta_cmyk()
{
    QString m = ui->magenta_text->text();
    int val = m.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of CMYK must be equal or less than 100!");
        ui->magenta_text->setText("100");
        ui->magenta_slider->setValue(100);
        auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
        g = QString::number(rgb[1]);
        Upgrade("cmyk");
        return;
    }
    ui->magenta_slider->setValue(val);
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    g = QString::number(rgb[1]);
    Upgrade("cmyk");
}

void MainWindow::set_text_yellow_cmyk()
{
    auto value = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    b = QString::number(value[2]);
    Upgrade("cmyk");
    ui->yellow_text->setText(QString::number(ui->yellow_slider->value()));
}

void MainWindow::set_value_yellow_cmyk()
{
    QString y = ui->yellow_text->text();
    int val = y.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of CMYK must be equal or less than 100!");
        ui->yellow_text->setText("100");
        ui->yellow_slider->setValue(100);
        auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
        b = QString::number(rgb[2]);
        Upgrade("cmyk");
        return;
    }
    ui->yellow_slider->setValue(val);
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    b = QString::number(rgb[2]);
    Upgrade("cmyk");
}

void MainWindow::set_value_key_cmyk()
{
    QString k = ui->key_text->text();
    int val = k.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of CMYK must be equal or less than 100!");
        ui->key_text->setText("100");
        ui->key_slider->setValue(100);
        auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("cmyk");
        return;
    }
    ui->key_slider->setValue(val);
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("cmyk");
}

void MainWindow::set_text_key_cmyk()
{
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("cmyk");
    ui->key_text->setText(QString::number(ui->key_slider->value()));
}

void MainWindow::set_text_hue_hsl()
{
    auto value = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("hsl");
    ui->hue_text->setText(QString::number(ui->hue_slider->value()));
}

void MainWindow::set_value_hue_hsl()
{
    QString h = ui->hue_text->text();
    int val = h.toInt();
    if(val > 360)
    {
        QMessageBox::warning(this, "Invalid data", "Value of Hue must be equal or less than 360!");
        ui->hue_text->setText("360");
        ui->hue_slider->setValue(360);
        auto rgb = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("hsl");
        return;
    }
    ui->hue_slider->setValue(val);
    auto rgb = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("hsl");
}

void MainWindow::set_text_saturation_hsl()
{
    auto value = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("hsl");
    ui->saturation_text->setText(QString::number(ui->saturation_slider->value()));

}

void MainWindow::set_value_saturation_hsl()
{
    QString s = ui->saturation_text->text();
    int val = s.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of HSL must be equal or less than 100!");
        ui->saturation_text->setText("100");
        ui->saturation_slider->setValue(100);
        auto rgb = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("hsl");
        return;
    }
    ui->saturation_slider->setValue(val);
    auto rgb = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("hsl");
}

void MainWindow::set_text_lightness_hsl()
{
    auto value = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("hsl");
    ui->lightness_text->setText(QString::number(ui->lightness_slider->value()));
}

void MainWindow::set_value_lightness_hsl()
{
    QString l = ui->lightness_text->text();
    int val = l.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of HSL must be equal or less than 100!");
        ui->lightness_text->setText("100");
        ui->lightness_slider->setValue(100);
        auto rgb = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("hsl");
        return;
    }
    ui->lightness_slider->setValue(val);
    auto rgb = HSL_to_RGB(ui->hue_slider->value(), ui->saturation_slider->value(), ui->lightness_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("hsl");
}

void MainWindow::set_text_x_xyz()
{
    auto value = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
    if(value[3] == 0)
    {
        ui->x_slider->setValue(ui->x_text->text().toInt());
        return;
    }
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("xyz");
    ui->x_text->setText(QString::number(ui->x_slider->value()));
}

void MainWindow::set_value_x_xyz()
{
    QString x = ui->x_text->text();
    int val = x.toInt();
    if(val > 109)
    {
        QMessageBox::warning(this, "Invalid data", "Value of XYZ must be equal or less than 109!");
        ui->x_text->setText(QString::number(ui->x_slider->value()));
        auto rgb = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("xyz");
        return;
    }
    auto rgb = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
    if(rgb[3] == 0)
    {
        ui->x_text->setText(QString::number(ui->x_slider->value()));
        return;
    }
    ui->x_slider->setValue(val);
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("xyz");
}

void MainWindow::set_text_y_xyz()
{
    auto value = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
    if(value[3] == 0)
    {
        ui->y_slider->setValue(ui->y_text->text().toInt());
        return;
    }
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("xyz");
    ui->y_text->setText(QString::number(ui->y_slider->value()));
}

void MainWindow::set_value_y_xyz()
{
    QString y = ui->y_text->text();
    int val = y.toInt();
    if(val > 109)
    {
        QMessageBox::warning(this, "Invalid data", "Value of XYZ must be equal or less than 109!");
        ui->y_text->setText(QString::number(ui->y_slider->value()));
        auto rgb = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("xyz");
        return;
    }
    auto rgb = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
    if(rgb[3] == 0)
    {
        ui->y_text->setText(QString::number(ui->y_slider->value()));
        return;
    }
    ui->y_slider->setValue(val);

    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("xyz");
}

void MainWindow::set_text_z_xyz()
{
    auto value = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
    if(value[3] == 0)
    {
        ui->z_slider->setValue(ui->z_text->text().toInt()-1);
        return;
    }
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("xyz");
    ui->z_text->setText(QString::number(ui->z_slider->value()));
}

void MainWindow::set_value_z_xyz()
{
    QString z = ui->z_text->text();
    int val = z.toInt();
    if(val > 109)
    {
        QMessageBox::warning(this, "Invalid data", "Value of XYZ must be equal or less than 109!");
        ui->z_slider->setValue(ui->z_text->text().toInt());
        auto rgb = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("xyz");
        return;
    }
    int var = ui->z_slider->value();
    ui->z_slider->setValue(val);
    auto rgb = XYZ_to_RGB(ui->x_slider->value(), ui->y_slider->value(), ui->z_slider->value());
    if(rgb[3] == 0)
    {
        ui->z_slider->setValue(var);
        return;
    }

    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("xyz");
}

void MainWindow::set_text_l_lab()
{
    auto value = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("lab");
    ui->l_text->setText(QString::number(ui->l_slider->value()));
}

void MainWindow::set_value_l_lab()
{
    QString l = ui->l_text->text();
    int val = l.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of LAB must be equal or less than 100!");
        ui->l_slider->setValue(100);
        ui->l_text->setText("100");
        auto rgb = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("lab");
        return;
    }
    ui->l_slider->setValue(val);
    auto rgb = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("lab");
}


void MainWindow::set_text_a_lab()
{
    auto value = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("lab");
    ui->a_text->setText(QString::number(ui->a_slider->value() - 128));
}

void MainWindow::set_value_a_lab()
{
    QString a = ui->a_text->text();
    int val = a.toInt();
    if(abs(val) > 128)
    {
        QMessageBox::warning(this, "Invalid data", "Value of LAB must be equal or less than 128!");
        ui->a_slider->setValue(128);
        ui->a_text->setText("0");
        auto rgb = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("lab");
        return;
    }
    ui->a_slider->setValue(128 + val);
    auto rgb = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("lab");
}

void MainWindow::set_text_b_lab()
{
    auto value = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("lab");
    ui->b_text->setText(QString::number(ui->b_slider->value() - 128));
}

void MainWindow::set_value_b_lab()
{
    QString bi = ui->b_text->text();
    int val = bi.toInt();
    if(abs(val) > 128)
    {
        QMessageBox::warning(this, "Invalid data", "Value of LAB must be equal or less than 128!");
        ui->b_slider->setValue(128);
        ui->b_text->setText("0");
        auto rgb = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("lab");
        return;
    }
    ui->b_slider->setValue(val + 128);
    auto rgb = LAB_to_RGB(ui->l_slider->value(), ui->a_slider->value() - 128, ui->b_slider->value() - 128);
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("lab");
}


QVector<int> MainWindow::CMYK_to_RGB(int c, int m, int y, int k)
{
    int r = 2.55*(100-c)*(100-k)/100.;
    int g = 2.55 * (100-m)*(100-k)/100.;
    int b = 2.55 * (100-y)*(100-k)/100.;
    return QVector<int>{r,g,b};
}
QVector<int> MainWindow::RGB_to_CMYK(int r, int g, int b)
{
    int k = qMin(qMin(100 - r/2.55, 100 - g/2.55), 100 - b/2.55);
    if(k == 100)
    {
        return QVector<int>{0,0,0,100};
    }
    int c = 100*(100-r/2.55 - k)/(100-k);
    int m = 100*(100-g/2.55-k)/(100-k);
    int y = 100*(100-b/2.55-k)/(100-k);
    return QVector<int>{c,m,y,k};
}

void MainWindow::set_RGB()
{
    ui->red_slider->setValue(r.toInt());
    ui->red_text->setText(r);
    ui->green_slider->setValue(g.toInt());
    ui->green_text->setText(g);
    ui->blue_slider->setValue(b.toInt());
    ui->blue_text->setText(b);
}
void MainWindow::set_CMYK()
{
    auto values = RGB_to_CMYK(r.toInt(), g.toInt(), b.toInt());
    ui->cyan_text->setText(QString::number(values[0]));
    ui->cyan_slider->setValue(values[0]);
    ui->magenta_text->setText(QString::number(values[1]));
    ui->magenta_slider->setValue(values[1]);
    ui->yellow_text->setText(QString::number(values[2]));
    ui->yellow_slider->setValue(values[2]);
    ui->key_text->setText(QString::number(values[3]));
    ui->key_slider->setValue(values[3]);
}

double MainWindow::Hue_to_RGB(double v1, double v2, double vH)
{
    if (vH < 0)
        vH += 1;

    if (vH > 1)
        vH -= 1;

    if ((6 * vH) < 1)
        return (v1 + (v2 - v1) * 6 * vH);

    if ((2 * vH) < 1)
        return v2;

    if ((3 * vH) < 2)
        return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

    return v1;
}
QVector<int> MainWindow::HSL_to_RGB(int h, int s, int l)
{
    int r, b, g;
    if (s == 0)
    {
        r = g = b = (l * 255);
    }
    else
    {
        double v1, v2;
        double hue = h / 360.;

        v2 = (l < 50) ? (l/100. * (1 + s/100.)) : ((l/100. + s/100.) - (l/100. * s/100.));
        v1 = 2 * l/100. - v2;

        r = (255 * Hue_to_RGB(v1, v2, hue + (1.0 / 3)));
        g = (255 * Hue_to_RGB(v1, v2, hue));
        b = (255 * Hue_to_RGB(v1, v2, hue - (1.0 / 3)));
    }
    return QVector<int>{r, g, b};
}

QVector<int> MainWindow::RGB_to_HSL(double r, double g, double b)
{
    double h, s, l;

    r /= 255;
    g /= 255;
    b /= 255;

    double max = qMax(qMax(r,g),b);
    double min = qMin(qMin(r,g),b);

    l = 100 * (max + min) / 2;

    if (max == min) {
        h = s = 0; // achromatic
    }
    else {
        float d = max - min;
        s = (l > 50) ? 100 * d / (2 - max - min) : 100 * d / (max + min);

        if (max == r) {
            h = 60 * (g - b) / d;
        }
        if (max == g) {
            h = 60 * (b - r) / d + 2 * 60;
        }
        if(max == b) {

            h = 60 * (r - g) / d + 4 * 60;
        }

    }
    if(h < 0)
        h+=360;
    return QVector<int>{h,s,l};
}

void MainWindow::set_HSL()
{
    auto values = RGB_to_HSL(r.toInt(), g.toInt(), b.toInt());
    ui->hue_text->setText(QString::number(values[0]));
    ui->hue_slider->setValue(values[0]);
    ui->saturation_text->setText(QString::number(values[1]));
    ui->saturation_slider->setValue(values[1]);
    ui->lightness_text->setText(QString::number(values[2]));
    ui->lightness_slider->setValue(values[2]);
}

QVector<int> MainWindow::RGB_to_XYZ(double r, double g, double b)
{
    r/=255;
    b/=255;
    g/=255;
    if(r>0.04045){
        r = qPow((r+0.055)/1.055, 2.4);
    }else{
        r/=12.92;
    }
    if(g>0.04045){
        g = pow((g+0.055)/1.055, 2.4);
    }else{
        g/=12.92;
    }
    if(b>0.04045){
        b = pow((b+0.055)/1.055, 2.4);
    }else{
        b/=12.92;
    }
    r*=100;
    g*=100;
    b*=100;
    int x =(int)(r * 0.4124 + g * 0.3576 + b * 0.1805);
    int y = (int)(r * 0.2126 + g * 0.7152 + b * 0.0722);
    int z = (int)(r * 0.0193 + g * 0.1192 + b * 0.9505);
    return QVector{x, y, z};
}

QVector<int> MainWindow::XYZ_to_RGB(double x, double y, double z)
{
    double r;
    double g;
    double b;
    int cond;
    x/=100;
    y/=100;
    z/=100;
    r = 3.2404542 * x - 0.4985314 * y - 0.4985314 * z;
    g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    b = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    if(r>=0.0031308){
        r = pow(r, 1/2.4)*1.055 - 0.055;
    }else{
        r *=12.92;
    }
    if(g>=0.0031308){
        g = pow(g, 1/2.4)*1.055 - 0.055;
    }else{
        g *=12.92;
    }
    if(b>=0.0031308){
        b = pow(b, 1/2.4)*1.055 - 0.055;
    }else{
        b *=12.92;
    }
    r = (int)(r*255);
    g = (int)(g*255);
    b = (int)(b*255);
    cond = 1;
    if(r < 0 || (r > 255))
        cond = 0;
    if(g < 0 || (g >255))
        cond = 0;
    if(b < 0 || (b > 255))
        cond = 0;
    return QVector<int>{r,g,b,cond};
}

void MainWindow::set_XYZ()
{
    auto values = RGB_to_XYZ(r.toInt(), g.toInt(), b.toInt());
    ui->x_text->setText(QString::number(values[0]));
    ui->x_slider->setValue(values[0]);
    ui->y_text->setText(QString::number(values[1]));
    ui->y_slider->setValue(values[1]);
    ui->z_text->setText(QString::number(values[2]));
    ui->z_slider->setValue(values[2]);
}

void MainWindow::set_LAB()
{
    auto values = RGB_to_LAB(r.toInt(), g.toInt(), b.toInt());
    ui->l_text->setText(QString::number(values[0]));
    ui->l_slider->setValue(values[0]);
    ui->a_text->setText(QString::number(values[1]));
    ui->a_slider->setValue(128 + values[1]);
    ui->b_text->setText(QString::number(values[2]));
    ui->b_slider->setValue(128 + values[2]);
}

void MainWindow::Upgrade(QString str)
{
    if(str != "rgb")
        set_RGB();
    if(str != "hsl")
        set_HSL();
    if(str != "cmyk")
        set_CMYK();
    if(str != "xyz")
        set_XYZ();
    if(str != "lab")
        set_LAB();
    if(str != "hsv")
        set_HSV();
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
}

void MainWindow::button_pushed()
{
    QColor color = QColorDialog::getColor(QColor{r.toInt(), g.toInt(),b.toInt()},this);
    r = QString::number(color.red());
    g = QString::number(color.green());
    b = QString::number(color.blue());
    Upgrade("");
}

double MainWindow::support_LAB(double x)
{
    if (x >= 0.008856)
    {
        x = pow(x, 1/3.0);
    }
    else
    {
        x = 7.787*x + 16/116;
    }
    return x;
}

QVector<int> MainWindow::RGB_to_LAB(double r, double g, double b)
{
    double xw = 95.047;
    double yw = 100;
    double zw = 108.883;
    r/=255;
    b/=255;
    g/=255;
    if(r>0.04045){
        r = pow((r+0.055)/1.055, 2.4);
    }else{
        r/=12.92;
    }
    if(g>0.04045){
        g = pow((g+0.055)/1.055, 2.4);
    }else{
        g/=12.92;
    }
    if(b>0.04045){
        b = pow((b+0.055)/1.055, 2.4);
    }else{
        b/=12.92;
    }
    r*=100;
    g*=100;
    b*=100;
    double x = (int)(r * 0.4124 + g * 0.3576 + b * 0.1805);
    double y = (int)(r * 0.2126 + g * 0.7152 + b * 0.0722);
    double z = (int)(r * 0.0193 + g * 0.1192 + b * 0.9505);
    return QVector<int>{(int)(116*support_LAB(y/yw) - 16), (int)(500*(support_LAB(x/xw) - support_LAB(y/yw))), 200*(support_LAB(y/yw) - support_LAB(z/zw))};
}

double MainWindow::support_LAB2(double x)
{
    if (x >= 0.008856)
    {
        x = pow(x, 3);
    }
    else
    {
        x = (x - 16/116)/7.787;
    }
    return x;
}
QVector<int> MainWindow::LAB_to_RGB(double l, double a, double b)
{
    double xw = 95.047;
    double yw = 100;
    double zw = 108.883;
    double x = support_LAB2(a/500 + ((l+16)/116)) * yw;
    double y = support_LAB2((l + 16)/116) * xw;
    double z = support_LAB2((l + 16)/116 - b/200) * zw;
    double r;
    double g;
    double bl;
    x/=100;
    y/=100;
    z/=100;
    r = 3.2404542 * x - 0.4985314 * y - 0.4985314 * z;
    g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    bl = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    if(r>=0.0031308){
        r = pow(r, 1/2.4)*1.055 - 0.055;
    }else{
        r *=12.92;
    }
    if(g>=0.0031308){
        g = pow(g, 1/2.4)*1.055 - 0.055;
    }else{
        g *=12.92;
    }
    if(b>=0.0031308){
        b = pow(b, 1/2.4)*1.055 - 0.055;
    }else{
        b *=12.92;
    }
    r = (int)(x*255);
    g = (int)(y*255);
    bl = (int)(z*255);

    return QVector<int>{r,g,bl};
}
QVector<int> MainWindow::HSV_to_RGB(int h, int s, int v)
{
    QColor c;
    c.setHsv(h,s * 2.55,v * 2.55);
    return QVector<int>{c.red(), c.green(), c.blue()};
}
void MainWindow::set_HSV()
{
    QColor c(r.toInt(), g.toInt(), b.toInt());
    int* h = new int();
    int *s = new int();
    int* v = new int();
    c.getHsv(h,s,v);
    ui->h_text->setText(QString::number(*h));
    ui->h_slider->setValue(*h);
    qDebug() << *v;
    int se = *s / 2.55;
    int va = *v / 2.55;
    ui->s_text->setText(QString::number(se));
    ui->s_slider->setValue(se);
    ui->v_text->setText(QString::number(va));
    ui->v_slider->setValue(va);
}

void MainWindow::set_text_h_hsv()
{
    auto value = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("hsv");
    ui->h_text->setText(QString::number(ui->h_slider->value()));
}

void MainWindow::set_value_h_hsv()
{
    QString h = ui->h_text->text();
    int val = h.toInt();
    if(val > 360)
    {
        QMessageBox::warning(this, "Invalid data", "Value of Hue must be equal or less than 360!");
        ui->h_text->setText("360");
        ui->h_slider->setValue(360);
        auto rgb = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("hsv");
        return;
    }
    ui->h_slider->setValue(val);
    auto rgb = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("hsv");
}

void MainWindow::set_text_s_hsv()
{
    auto value = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("hsv");
    ui->s_text->setText(QString::number(ui->s_slider->value()));

}

void MainWindow::set_value_s_hsv()
{
    QString s = ui->s_text->text();
    int val = s.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of HSV must be equal or less than 100!");
        ui->s_text->setText("100");
        ui->s_slider->setValue(100);
        auto rgb = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("hsv");
        return;
    }
    ui->s_slider->setValue(val);
    auto rgb = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("hsv");
}

void MainWindow::set_text_v_hsv()
{
    auto value = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
    r = QString::number(value[0]);
    g = QString::number(value[1]);
    b = QString::number(value[2]);
    Upgrade("hsv");
    ui->v_text->setText(QString::number(ui->v_slider->value()));
}

void MainWindow::set_value_v_hsv()
{
    QString l = ui->v_text->text();
    int val = l.toInt();
    if(val > 100)
    {
        QMessageBox::warning(this, "Invalid data", "Value of HSV must be equal or less than 100!");
        ui->v_text->setText("100");
        ui->v_slider->setValue(100);
        auto rgb = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
        r = QString::number(rgb[0]);
        g = QString::number(rgb[1]);
        b = QString::number(rgb[2]);
        Upgrade("hsv");
        return;
    }
    ui->v_slider->setValue(val);
    auto rgb = HSV_to_RGB(ui->h_slider->value(), ui->s_slider->value(), ui->v_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    Upgrade("hsv");
}
