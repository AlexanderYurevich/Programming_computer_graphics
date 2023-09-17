#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
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
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                "}");
    set_CMYK();
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
        ui->red_text->setText(r);
        ui->red_slider->setValue(255);
        ui->main_bg->setStyleSheet("QLabel{"
                                   "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                               "}");
        return;
    }
    ui->red_slider->setValue(val);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    set_CMYK();
}

void MainWindow::set_value_green_rgb()
{
    g = ui->green_text->text();
    int val = g.toInt();
    if(val > 255)
    {
        QMessageBox::warning(this, "Invalid data", "Value of RGB must be equal or less than 255!");
        g = "255";
        ui->green_text->setText("255");
        ui->green_slider->setValue(255);
        ui->main_bg->setStyleSheet("QLabel{"
                                   "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                               "}");
        return;
    }
    ui->green_slider->setValue(val);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    set_CMYK();
}

void MainWindow::set_value_blue_rgb()
{
    b = ui->blue_text->text();
    int val = b.toInt();
    if(val > 255)
    {
        QMessageBox::warning(this, "Invalid data", "Value of RGB must be equal or less than 255!");
        b = "255";
        ui->blue_text->setText("255");
        ui->blue_slider->setValue(255);
        ui->main_bg->setStyleSheet("QLabel{"
                                   "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                               "}");
        return;
    }
    ui->blue_slider->setValue(val);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    set_CMYK();
}

void MainWindow::set_text_red_rgb()
{
    r = QString::number(ui->red_slider->value());
    ui->red_text->setText(r);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    set_CMYK();
}

void MainWindow::set_text_green_rgb()
{
    g = QString::number(ui->green_slider->value());
    ui->green_text->setText(g);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    set_CMYK();
}

void MainWindow::set_text_blue_rgb()
{
    b = QString::number(ui->blue_slider->value());
    ui->blue_text->setText(b);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    set_CMYK();
}

void MainWindow::set_text_cyan_cmyk()
{
    auto value = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    r = QString::number(value[0]);
    ui->red_text->setText(r);
    ui->red_slider->setValue(r.toInt());
    ui->cyan_text->setText(QString::number(ui->cyan_slider->value()));
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
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
        ui->main_bg->setStyleSheet("QLabel{"
                                   "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                               "}");
        ui->red_slider->setValue(r.toInt());
        ui->red_text->setText(r);
        return;
    }
    ui->cyan_slider->setValue(val);
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    r = QString::number(rgb[0]);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    ui->red_slider->setValue(r.toInt());
    ui->red_text->setText(r);
}

void MainWindow::set_text_magenta_cmyk()
{
    auto value = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    g = QString::number(value[1]);
    ui->green_text->setText(g);
    ui->green_slider->setValue(g.toInt());
    ui->magenta_text->setText(QString::number(ui->magenta_slider->value()));
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
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
        ui->main_bg->setStyleSheet("QLabel{"
                                   "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                               "}");
        ui->green_slider->setValue(g.toInt());
        ui->green_text->setText(g);
        return;
    }
    ui->magenta_slider->setValue(val);
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    g = QString::number(rgb[1]);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    ui->green_slider->setValue(g.toInt());
    ui->green_text->setText(g);
}

void MainWindow::set_text_yellow_cmyk()
{
    auto value = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    b = QString::number(value[2]);
    ui->blue_text->setText(b);
    ui->blue_slider->setValue(b.toInt());
    ui->yellow_text->setText(QString::number(ui->yellow_slider->value()));
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
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
        ui->main_bg->setStyleSheet("QLabel{"
                                   "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                               "}");
        ui->blue_slider->setValue(b.toInt());
        ui->blue_text->setText(b);
        return;
    }
    ui->yellow_slider->setValue(val);
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    b = QString::number(rgb[2]);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    ui->blue_slider->setValue(b.toInt());
    ui->blue_text->setText(b);
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
        ui->main_bg->setStyleSheet("QLabel{"
                                   "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                               "}");
        ui->red_slider->setValue(r.toInt());
        ui->red_text->setText(r);
        ui->green_slider->setValue(g.toInt());
        ui->green_text->setText(g);
        ui->blue_slider->setValue(b.toInt());
        ui->blue_text->setText(b);
        return;
    }
    ui->key_slider->setValue(val);
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
    ui->red_slider->setValue(r.toInt());
    ui->red_text->setText(r);
    ui->green_slider->setValue(g.toInt());
    ui->green_text->setText(g);
    ui->blue_slider->setValue(b.toInt());
    ui->blue_text->setText(b);
}

void MainWindow::set_text_key_cmyk()
{
    auto rgb = CMYK_to_RGB(ui->cyan_slider->value(), ui->magenta_slider->value(), ui->yellow_slider->value(), ui->key_slider->value());
    r = QString::number(rgb[0]);
    g = QString::number(rgb[1]);
    b = QString::number(rgb[2]);
    ui->red_slider->setValue(r.toInt());
    ui->red_text->setText(r);
    ui->green_slider->setValue(g.toInt());
    ui->green_text->setText(g);
    ui->blue_slider->setValue(b.toInt());
    ui->blue_text->setText(b);
    ui->key_text->setText(QString::number(ui->key_slider->value()));
    ui->main_bg->setStyleSheet("QLabel{"
                               "background-color:rgb(" + r + ", "+ g + " ," + b + ");"
                                                           "}");
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
