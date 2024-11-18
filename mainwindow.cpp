#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "landingpage.h"
#include <QMouseEvent>
#include <QPainter>
#include <QToolBar>
#include<QFileDialog>
#include<QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), penColor(Qt::black), drawing(false) {
    ui->setupUi(this);

    QPushButton *submitButton = new QPushButton("Submit", this);
    submitButton->setGeometry(QRect(450, 500, 150, 40));
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::submitCanvas);

    this->setStyleSheet(
        "QMainWindow {"
        "background-color: #001D3D;"
        "}"
        );

    submitButton->setStyleSheet(
        "QPushButton {"
        "background-color: #FFC300;"
        "color: 001D3D;"
        "border: none;"
        "border-radius: 5px;"
        "font-size: 20px;"
        "padding: 5px;"
        "}"
        "QPushButton:hover {"
        "background-color: #D49B00;"
        "}"
        "QPushButton:pressed {"
        "background-color: #B57C00;"
        "}"
        );


    drawingBoundary = QRect(150, 50, 500, 400);

    // Initialization of the canvas to match the boundary size
    image = QImage(drawingBoundary.size(), QImage::Format_RGB32);
    image.fill(Qt::white);

    QToolBar *toolbar = addToolBar("Main Toolbar");

    toolbar->setStyleSheet(
        "QToolBar {"
        "background-color: #333333;"
        "border: none;"
        "padding: 5px;"
        "}"
        "QToolBar::separator {"
        "background-color: #4CAF50;"
        "height: 2px;"
        "margin: 0px 5px;"
        "}"
        "QToolBar::handle {"
        "background-color: #555555;"
        "border: none;"
        "width: 10px;"
        "}"
        );

    QPushButton *clearButton = new QPushButton("Clear", this);
    clearButton->setGeometry(QRect(200, 500, 150, 40));
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearCanvas);

    clearButton->setStyleSheet(
        "QPushButton {"
        "background-color: #FFC300;"
        "color: 001D3D;"
        "border: none;"
        "border-radius: 5px;"
        "font-size: 20px;"
        "padding: 5px;"
        "}"
        "QPushButton:hover {"
        "background-color: #D49B00;"
        "}"
        "QPushButton:pressed {"
        "background-color: #B57C00;"
        "}"
        );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Only start drawing if the click is within the boundary
    if (event->button() == Qt::LeftButton && drawingBoundary.contains(event->pos())) {
        lastPoint = event->pos() - drawingBoundary.topLeft();
        drawing = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (drawing && (event->buttons() & Qt::LeftButton) && drawingBoundary.contains(event->pos())) {
        drawLineTo(event->pos() - drawingBoundary.topLeft());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing && drawingBoundary.contains(event->pos())) {
        drawLineTo(event->pos() - drawingBoundary.topLeft());
        drawing = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    // Draw the boundary and the canvas inside it
    QPainter painter(this);
    painter.setPen(QPen(QColor(235, 235, 235), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(drawingBoundary);

    // Drawing inside the canvas area
    painter.drawImage(drawingBoundary.topLeft(), image);
}

void MainWindow::drawLineTo(const QPoint &endPoint) {
    QPainter painter(&image);
    painter.setPen(QPen(penColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    lastPoint = endPoint;
    update(drawingBoundary);
}

void MainWindow::clearCanvas() {
    image.fill(Qt::white);
    update(drawingBoundary);
}

// void MainWindow::submitCanvas() {
//     QString filePathOriginal = QFileDialog::getSaveFileName(this, "Save Original Image", "", "PNG Files (*.png)");
//     if (!filePathOriginal.isEmpty()) {
//         image.save(filePathOriginal, "PNG"); // Save the full-resolution image
//     }
void MainWindow::submitCanvas() {
    QString filePathOriginal = QFileDialog::getSaveFileName(this, "Save Original Image", "", "PNG Files (*.png)");
    if (!filePathOriginal.isEmpty()) {
        // Resizing the image to 24x24 pixels
        QImage resizedImage = image.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        resizedImage.save(filePathOriginal, "PNG");
    }
}

