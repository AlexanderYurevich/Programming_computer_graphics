#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QImage>
#include <QImageWriter>
#include <QFileInfo>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    struct ImageInfo{
        QString name;
        QString size;
        int resolution;
        int depth;
        QString compr;
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ImageInfo exploreImage(QFileInfo file);
    bool checkFile(QFileInfo file);
    void fillTable(const QVector<ImageInfo>& info);

    QDir currentFolder;
    Ui::MainWindow *ui;



private slots:
    void on_open_clicked();
    void on_choose_clicked();
};
#endif // MAINWINDOW_H
