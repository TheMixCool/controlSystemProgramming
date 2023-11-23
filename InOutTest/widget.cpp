#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <math.h>

// --------------------------
// Set stop time here
// --------------------------
#define ENDOFTIME 25
#define SAMPLINGTIMEMSEC 10
// --------------------------
// Set stop time here
// --------------------------

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

	// Create dir for logs
	if (!QDir("logs").exists()) {
		QDir().mkdir("logs");
	}

    // Set window size
	this->setMinimumSize(640, 480);

    // Add main layout with two plots
    mainlayout = new QGridLayout(this);
    inputPlot = new QCustomPlot(this);
    outputPlot = new QCustomPlot(this);
	mainlayout->addWidget(inputPlot, 0, 0);
	mainlayout->addWidget(outputPlot, 0, 1);
	inputPlot->addGraph();
	outputPlot->addGraph();

	startButton = new QPushButton("Start");
	connect(startButton, &QPushButton::clicked, this, [=](){
		startTime = 0;
		relativeTime = 0;
		inputPlot->graph(0)->data()->clear();
		outputPlot->graph(0)->data()->clear();
		timer->start();
	});
	mainlayout->addWidget(startButton, 1, 0);

	saveButton = new QPushButton("Save");
	connect(saveButton, &QPushButton::clicked, this, [=](){
		QString timestamp = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
		inputPlot->savePng(QString("./logs/%1_input.png").arg(timestamp));
		outputPlot->savePng(QString("./logs/%1_output.png").arg(timestamp));
	});
	mainlayout->addWidget(saveButton, 1, 1);

    // Give the axes some labels:
    inputPlot->xAxis->setLabel("t");
    inputPlot->yAxis->setLabel("input");
    outputPlot->xAxis->setLabel("t");
    outputPlot->yAxis->setLabel("output");

    // --------------------------
    // Change ranges if you need
    // --------------------------
    // Set axes ranges so see all data:
    inputPlot->xAxis->setRange(0, ENDOFTIME);
    inputPlot->yAxis->setRange(-5, 5);
    outputPlot->xAxis->setRange(0, ENDOFTIME);
    outputPlot->yAxis->setRange(-5, 5);

    // --------------------------
    // Create the object here
    // --------------------------
// -----------------------------    STATE_SPACE   ----------------------------------

//    std::vector<float> initial_conditions {0.0, 0.0, 0.0};
//    std::vector<std::vector<float>> matrix_A{{-2, -2, -1},{1, 0, 0},{0, 1, 0}};
//    std::vector<float> matrix_B {2, 0, 0};
//    std::vector<float> matrix_C {-0.5, -0.5, -0.5};
//    std::vector<float> matrix_D {1};
//    m_stateSpace = new StateSpace(initial_conditions, matrix_A, matrix_B, matrix_C, matrix_D);

    // -----------------------------DISCRETE   5 Hz    ----------------------------------

//    std::vector<float> initial_conditions {0.0, 0.0, 0.0};
//    std::vector<std::vector<float>> matrix_A{{0.6387, -0.3427, -0.1626},{0.1626, 0.9639, -0.0175},{0.0175, 0.1975, 0.9988}};
//    std::vector<float> matrix_B {0.3252, 0.0349, 0.0024};
//    std::vector<float> matrix_C {-0.5, -0.5, -0.5};
//    std::vector<float> matrix_D {1};
//    m_discrete = new Discrete(initial_conditions, matrix_A, matrix_B, matrix_C, matrix_D);

    // -----------------------------DISCRETE   30 Hz    ----------------------------------

//    std::vector<float> initial_conditions {0.0, 0.0, 0.0};
//    std::vector<std::vector<float>> matrix_A{{0.9344, -0.0650, -0.0322},{0.0322, 0.9989, -0.0005},{0.0005, 0.0333, 1.0000}};
//    std::vector<float> matrix_B {0.0645, 0.0011, 0.0000};
//    std::vector<float> matrix_C {-0.5, -0.5, -0.5};
//    std::vector<float> matrix_D {1};
//    m_discrete = new Discrete(initial_conditions, matrix_A, matrix_B, matrix_C, matrix_D);

    // -----------------------------DISCRETE   100   Hz    ----------------------------------

    std::vector<float> initial_conditions {0.0, 0.0, 0.0};
    std::vector<std::vector<float>> matrix_A{{0.9801, -0.0199, -0.0099},{0.0099, 0.9999, -0.0000},{0.0000, 0.0100, 1.0000}};
    std::vector<float> matrix_B {0.0198, 0.0001, 0.0000};
    std::vector<float> matrix_C {-0.5, -0.5, -0.5};
    std::vector<float> matrix_D {1};
    m_discrete = new Discrete(initial_conditions, matrix_A, matrix_B, matrix_C, matrix_D);

    // --------------------------
    // Create the object here
    // --------------------------

    timer = new QTimer(this);
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // --------------------------
    // Set sampling time here
    // --------------------------
	timer->setInterval(SAMPLINGTIMEMSEC);
    // --------------------------
    // Set sampling time here
    // --------------------------
}

Widget::~Widget()
{
    delete ui;
    delete inputPlot;
    delete outputPlot;
    delete timer;
    delete mainlayout;

    // --------------------------
    // Delete the object here
    // --------------------------
    //delete m_stateSpace;
    delete m_discrete;
    // --------------------------
    // Delete the object here
    // --------------------------
}

void Widget::update() {

	// --------------------------
	// Replace input signal with ours
	// --------------------------
    //double signal = std::sin(relativeTime / 1000.0);
    double signal = 2 * std::sin(2 * relativeTime/1000.0 + 1.047) - 2.0;
    //double signal = 10;
	// --------------------------
	// Replace input signal with ours
	// --------------------------

	// --------------------------
	// Plot initial values here
	// --------------------------
	if (startTime == 0) {
		// First step only plot initial values
		startTime = QDateTime::currentMSecsSinceEpoch();

		inputPlot->graph(0)->addData(0.0, 0);
		outputPlot->graph(0)->addData(0.0, 0);
		return;
	} else {
		dt = relativeTime;
		relativeTime = QDateTime::currentMSecsSinceEpoch() - startTime;
		dt = relativeTime - dt;
	}

    inputPlot->graph(0)->addData(relativeTime / 1000.0, signal);
    //outputPlot->graph(0)->addData(relativeTime / 1000.0, m_stateSpace->getOutput());
    outputPlot->graph(0)->addData(relativeTime / 1000.0, m_discrete->getOutput());

    inputPlot->replot();
    outputPlot->replot();

    // --------------------------
    // Update the object here
    // --------------------------
    //m_stateSpace->update(signal, dt/1000.0);
    m_discrete->update(signal);
    // --------------------------
    // Update the object here
    // --------------------------

	if (relativeTime / 1000.0 > ENDOFTIME) {
		timer->blockSignals(true);
		timer->stop();
		timer->blockSignals(false);
	}
}
