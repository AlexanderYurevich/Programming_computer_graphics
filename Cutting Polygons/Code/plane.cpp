#include <QVector>
#include <QPair>
#include "plane.h"
#include <fstream>
#include<iostream>
#include <cmath>

plane::plane(QWidget *parent): QWidget(parent)
{
    readFile();
}

void plane::clipSegments(){
    QVector<QPair<QPointF, QPointF>> segments = this->segments;
    for (int i = 0; i < segments.size(); i++)
    {
        QPointF P1 = segments[i].first;
        QPointF P2 = segments[i].second;
        if (liangBarskyClip(P1, P2))
        {
            clippedSegments.push_back(qMakePair(P1, P2));
        }
    }
}
bool plane::liangBarskyClip(QPointF &P1, QPointF &P2)
{
    double t0 = 0.0;
    double t1 = 1.0;

    double dx = P2.x() - P1.x();
    double dy = P2.y() - P1.y();

    for (int i = 0; i < 4; ++i)
    {
        double p = 0.0, q;

        if (i == 0)
        {
            p = -dx;
            q = P1.x() - Xmin;
        }
        else if (i == 1)
        {
            p = dx;
            q = Xmax - P1.x();
        }
        else if (i == 2)
        {
            p = -dy;
            q = P1.y() - Ymin;
        }
        else if (i == 3)
        {
            p = dy;
            q = Ymax - P1.y();
        }

        if (p == 0 && q < 0)
        {
            return false;
        }

        double r = q / p;

        if (p < 0)
        {
            t0 = qMax(t0, r);
        }
        else if (p > 0)
        {
            t1 = qMin(t1, r);
        }

        if (t0 > t1)
        {
            return false;
        }
    }

    P1.setX(P1.x() + t0 * dx);
    P1.setY(P1.y() + t0 * dy);
    P2.setX(P1.x() + (t1 - t0) * dx);
    P2.setY(P1.y() + (t1 - t0) * dy);

    return true;
}

void plane::readFile()
{
    segments.clear();
    clippedSegments.clear();
    std::ifstream fin(filePath);
    int n;
    fin>>n;
    int x1,y1,x2,y2;
    QPointF p1, p2;
    for(int i = 0; i < n; i++){
        fin>>x1>>y1>>x2>>y2;
        p1.setX(x1);
        p1.setY(y1);
        p2.setX(x2);
        p2.setY(y2);
        segments.push_back(qMakePair(p1,p2));
    }
    fin>>Xmin>>Ymin>>Xmax>>Ymax;
    fin.close();
    clipSegments();
}
