#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include <QWidget>

class LandingPage : public QWidget {
    Q_OBJECT
public:
    explicit LandingPage(QWidget *parent = nullptr);

signals:
    void startClicked(); // Signal to notify the main application to switch to MainWindow
};

#endif // LANDINGPAGE_H
