#include "landingpage.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
// #include <QPixmap>

LandingPage::LandingPage(QWidget *parent) : QWidget(parent) {
    setAutoFillBackground(true);

    // Setting background color
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(0, 29, 61));
    setPalette(palette);


    QVBoxLayout *layout = new QVBoxLayout(this);


    QLabel *title = new QLabel("Digit Recognition App", this);
    title->setStyleSheet(
        "font-size: 30px;"
        "color: #FFC300;"
        "font-weight: bold;"
        "margin-bottom: 10px;"
        );
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);


    QLabel *subtitle = new QLabel("Draw a digit and let the app recognize it!", this);
    subtitle->setStyleSheet(
        "font-size: 16px;"
        "color: #FFC300;"
        "margin-bottom: 20px;"
        );
    subtitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(subtitle);


    QPushButton *startButton = new QPushButton("Start Recognizing", this);
    startButton->setStyleSheet(
        "QPushButton {"
        "background-color: #FFC300;"
        "color: #001D3D;"
        "font-size: 18px;"
        "font-weight: bold;"
        "padding: 10px 25px;"
        "border-radius: 8px;"
        "margin-top: 20px;"
        "} "
        "QPushButton:hover {"
        "background-color: #FFB600;"
        "} "
        "QPushButton:pressed {"
        "background-color: #FF9900;"
        "}"
        );
    layout->addWidget(startButton, 0, Qt::AlignCenter);


    QLabel *footer = new QLabel("Instructions:\nDraw a digit (0-9) on the canvas and click submit to recognize.", this);
    footer->setStyleSheet(
        "font-size: 14px;"
        "color: #ebebeb;"
        "margin-top: 30px;"
        "text-align: center;"
        );
    footer->setAlignment(Qt::AlignCenter);
    layout->addWidget(footer);

    setLayout(layout);

    connect(startButton, &QPushButton::clicked, this, &LandingPage::startClicked);
}
