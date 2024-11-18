#include "landingpage.h"
#include "mainwindow.h"
#include <QApplication>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Creating a stacked widget to manage page transitions
    QStackedWidget stackedWidget;

    LandingPage *landingPage = new LandingPage;
    MainWindow *mainWindow = new MainWindow;

    // Adding both widgets to the stack
    stackedWidget.addWidget(landingPage);
    stackedWidget.addWidget(mainWindow);

    // Show the landing page initially
    stackedWidget.setCurrentWidget(landingPage);

    // Apply opacity effects to both pages
    QGraphicsOpacityEffect* landingPageOpacity = new QGraphicsOpacityEffect(landingPage);
    landingPage->setGraphicsEffect(landingPageOpacity);
    landingPageOpacity->setOpacity(1);

    QGraphicsOpacityEffect* mainWindowOpacity = new QGraphicsOpacityEffect(mainWindow);
    mainWindow->setGraphicsEffect(mainWindowOpacity);
    mainWindowOpacity->setOpacity(0); // Initially hidden

    // Create animations for both pages
    QPropertyAnimation* landingPageFadeOut = new QPropertyAnimation(landingPageOpacity, "opacity");
    landingPageFadeOut->setDuration(250);
    landingPageFadeOut->setStartValue(1);
    landingPageFadeOut->setEndValue(0);

    QPropertyAnimation* mainWindowFadeIn = new QPropertyAnimation(mainWindowOpacity, "opacity");
    mainWindowFadeIn->setDuration(500);
    mainWindowFadeIn->setStartValue(0);
    mainWindowFadeIn->setEndValue(1);

    // Connect the landing page to start the transition
    QObject::connect(landingPage, &LandingPage::startClicked, &stackedWidget, [landingPageFadeOut, mainWindowFadeIn, mainWindow, &stackedWidget]() {
        // Start fade-out animation for the landing page and fade-in for the main window
        landingPageFadeOut->start();
        mainWindowFadeIn->start();

        // Switch the current widget after the animation is finished
        QObject::connect(landingPageFadeOut, &QPropertyAnimation::finished, &stackedWidget, [mainWindow, &stackedWidget]() {
            stackedWidget.setCurrentWidget(mainWindow);
        });
    });

    // Show the stacked widget
    stackedWidget.resize(800, 600);
    stackedWidget.show();

    return app.exec();
}
