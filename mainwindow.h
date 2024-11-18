#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QRect>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void clearCanvas();
    void submitCanvas();


private:
    Ui::MainWindow *ui;
    QImage image;
    QPoint lastPoint;
    QColor penColor;
    bool drawing;
    QRect drawingBoundary;
    void drawLineTo(const QPoint &endPoint);
};

#endif // MAINWINDOW_H
