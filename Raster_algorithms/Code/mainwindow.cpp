#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawingWidget = new DrawingWidget();
    ui->verticalLayout->addWidget(drawingWidget);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onComboBoxChanged()));
    connect(ui->clearButton, SIGNAL(clicked(bool)),
            this, SLOT(onClearPushed()));
    connect(ui->drawButton, SIGNAL(clicked(bool)),
            this, SLOT(onDrawPushed()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete drawingWidget;
}

void MainWindow::onComboBoxChanged(){
    if(ui->comboBox->currentIndex() == 3)
    {
        ui->label_x2->setText("Radius");
        ui->lineEdit_y2->setEnabled(false);
        ui->label_y2->setEnabled(false);
    }
    else
    {
        ui->label_x2->setText("x2");
        ui->lineEdit_y2->setEnabled(true);
        ui->label_y2->setEnabled(true);
    }
}

void MainWindow::onClearPushed(){
    drawingWidget->filledCells.clear();
    drawingWidget->update();
}

void MainWindow::onDrawPushed(){
    int value = ui->comboBox->currentIndex();
    switch(value){
    case 0:
        rasterizeLine((ui->lineEdit_x1->text()).toInt(), (ui->lineEdit_y1->text()).toInt(),
            (ui->lineEdit_x2->text()).toInt(), (ui->lineEdit_y2->text()).toInt());
        break;
    case 1:
        DDALine((ui->lineEdit_x1->text()).toInt(), (ui->lineEdit_y1->text()).toInt(),
                      (ui->lineEdit_x2->text()).toInt(), (ui->lineEdit_y2->text()).toInt());
        break;
    case 2:
        BrezenhamLine((ui->lineEdit_x1->text()).toInt(), (ui->lineEdit_y1->text()).toInt(),
                      (ui->lineEdit_x2->text()).toInt(), (ui->lineEdit_y2->text()).toInt());
        break;
    case 3:
        BrezenhamCircle((ui->lineEdit_x1->text()).toInt(), (ui->lineEdit_y1->text()).toInt(),
                      (ui->lineEdit_x2->text()).toInt());
        break;
    }
    drawingWidget->update();
}

void MainWindow::rasterizeLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    float k = static_cast<float>(dy) / dx;

    float b = y1 - k * x1;

    int step = (dx > 0) ? 1 : -1;

    int steps = abs(dx);

    for (int i = 0; i <= steps; ++i) {
        int x = x1 + i * step;
        int y = static_cast<int>(k * x + b + 0.5);

        drawingWidget->filledCells.push_back({x, y});
    }
}
void MainWindow::DDALine(int x1, int y1, int x2, int y2){
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));

    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; ++i) {
        drawingWidget->filledCells.push_back({static_cast<int>(x), static_cast<int>(y)});

        x += xIncrement;
        y += yIncrement;
    }

}

void MainWindow::BrezenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawingWidget->filledCells.push_back({x1, y1});

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

}

void MainWindow::BrezenhamCircle(int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        drawingWidget->filledCells.push_back({centerX + x, centerY - y});
        drawingWidget->filledCells.push_back({centerX - x, centerY - y});
        drawingWidget->filledCells.push_back({centerX + x, centerY + y});
        drawingWidget->filledCells.push_back({centerX - x, centerY + y});
        drawingWidget->filledCells.push_back({centerX + y, centerY - x});
        drawingWidget->filledCells.push_back({centerX - y, centerY - x});
        drawingWidget->filledCells.push_back({centerX + y, centerY + x});
        drawingWidget->filledCells.push_back({centerX - y, centerY + x});

        y++;

        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}
