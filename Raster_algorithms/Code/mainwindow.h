#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawingwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onComboBoxChanged();
    void onClearPushed();
    void onDrawPushed();
private:
    Ui::MainWindow *ui;
    DrawingWidget* drawingWidget;
    void rasterizeLine(int x0, int y0, int x1, int y1);
    void DDALine(int x0, int y0, int x1, int y1);
    void BrezenhamLine(int x0, int y0, int x1, int y1);
    void BrezenhamCircle(int x, int y, int r);
};

#endif // MAINWINDOW_H
