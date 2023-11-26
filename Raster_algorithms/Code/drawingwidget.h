#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class DrawingWidget : public QWidget
{
public:
    DrawingWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
    }

    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);
        drawGrid(painter);
        drawAxes(painter);
        drawFilledCells(painter);
    }

public:
    struct Cell
    {
        int x;
        int y;
    };

    QList<Cell> filledCells;

    void drawGrid(QPainter &painter)
    {
        painter.setPen(Qt::gray);

        for (int x = 0; x < width(); x += 20)
            painter.drawLine(x, 0, x, height());

        for (int y = 0; y < height(); y += 20)
            painter.drawLine(0, y, width(), y);
    }

    void drawAxes(QPainter &painter)
    {
        painter.setPen(Qt::black);
        painter.drawLine(width() / 2, 0, width() / 2, height());
        painter.drawLine(0, height() / 2, width(), height() / 2);

        painter.setPen(Qt::black);
        int scale = 20;
        for (int x = 0; x <= width(); x += scale)
        {
            painter.drawLine(x, height() / 2 - 5, x, height() / 2 + 5);
            if (x % (scale * 5) == 0)
                painter.drawText(x - 5, height() / 2 + 15, QString::number((x - width() / 2) / scale));
        }

        for (int y = 0; y <= height(); y += scale)
        {
            painter.drawLine(width() / 2 - 5, y, width() / 2 + 5, y);
            if (y % (scale * 5) == 0)
                painter.drawText(width() / 2 + 10, y + 5, QString::number((height() / 2 - y) / scale));
        }
    }

    void drawFilledCells(QPainter &painter)
    {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::black);

        int cellSize = 20;

        for (const Cell &cell : filledCells)
            painter.drawRect(width() / 2 + cell.x * cellSize, height() / 2 - (cell.y + 1) * cellSize, cellSize, cellSize);
    }

    void fillCell(int x, int y)
    {
        // Добавляем координаты закрашенной ячейки
        Cell cell = {x, y};
        filledCells.append(cell);

        update(); // Обновляем виджет для отображения изменений
    }
};


#endif // DRAWINGWIDGET_H
