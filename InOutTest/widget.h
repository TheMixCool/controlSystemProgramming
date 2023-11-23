#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QDateTime>
#include "qcustomplot.h"
#include "blocks/StateSpace/statespace.h"
#include "blocks/Discrete/discrete.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void update();

private:
    Ui::Widget *ui;
    QGridLayout *mainlayout;
    QCustomPlot *inputPlot;
    QCustomPlot *outputPlot;
	QPushButton* startButton;
	QPushButton* saveButton;

	qint64 startTime = 0;
	qint64 relativeTime = 0;
	qint64 dt;

    QTimer * timer;

    // --------------------------
    // Add pointer to the object here
    // --------------------------
    //StateSpace * m_stateSpace;
    Discrete * m_discrete;
    // --------------------------
    // Add pointer to the object here
    // --------------------------
};

#endif // WIDGET_H
