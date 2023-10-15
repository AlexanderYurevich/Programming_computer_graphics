#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->currentFolder = QDir(QDir::currentPath());
    ui->lineEdit->setText(currentFolder.currentPath());
    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(on_open_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)),
            this, SLOT(on_choose_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::ImageInfo MainWindow::exploreImage(QFileInfo file)
{
    ImageInfo info;
    info.name = file.fileName();
    QImage img(file.absoluteFilePath());
    info.size = QString::number(img.width()) + "x" + QString::number(img.height());
    info.resolution = img.dotsPerMeterY()*0.0254;
    info.depth = img.bitPlaneCount();
    QImageWriter temp(file.absoluteFilePath());
    info.compr = temp.compression();
    return info;
}

void MainWindow::fillTable(const QVector<ImageInfo> &info)
{
    ui->tableWidget->setRowCount(0);
    for(int i = 0; i < info.size(); ++i)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(info[i].name));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(info[i].size));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(info[i].resolution)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(info[i].depth)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem("-1"));
    }
}
bool MainWindow::checkFile(QFileInfo file)
{
    QString str = file.filePath();
    int i = str.lastIndexOf('.');
    if (i == -1) {
        return false;
    }
    QString resolution = str.mid(i);
    if (resolution != ".jpg" && resolution != ".gif" && resolution != ".tif" && resolution != ".bmp" &&
        resolution != ".png" && resolution != ".pcx" && resolution != ".BMP") {
        return false;
    }
    return true;
}

void MainWindow::on_open_clicked()
{
    QDir temp(ui->lineEdit->text());
    if (temp.exists()) {
        currentFolder.setPath(ui->lineEdit->text());
        auto infoList = currentFolder.entryInfoList(QDir::Files);
        QVector<ImageInfo> info{};
        for (QFileInfo file : infoList)
        {
            if(!checkFile(file))
                continue;
            info.push_back(exploreImage(file));
        }
        fillTable(info);
    }
    else{
        QMessageBox::warning(this, "Wrong directory", "Ops! You chose wrong directory.");
    }
}

void MainWindow::on_choose_clicked()
{
    QFileDialog *files = new QFileDialog;
    files->setWindowTitle("Откройте файлы");
    QList<QUrl> list = files->getOpenFileUrls();
    QVector<ImageInfo> info{};
    for(QUrl url : list)
    {
        QFileInfo file(url.toLocalFile());
        if(!checkFile(file))
            continue;
        info.push_back(exploreImage(file));
        ui->lineEdit->setText(file.path());
    }
    fillTable(info);
}
