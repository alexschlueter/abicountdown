#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <array>
#include <random>
#include <chrono>
#include <QtGui>
#include <QDate>

class MainWindow : public QObject
{
    Q_OBJECT
    
public:
    MainWindow();
    
private:
    static constexpr auto ourFlight = "ABI13", ourGate = "G9";
    static constexpr auto screenSwitchInterval = 30, animationTime = 1, xFlaps = 20, yFlaps = 5, symbolCount = 65;
    static constexpr auto xFlapBorder = 40;

    std::array<char, symbolCount> symbols;
    std::mt19937 gen;
    std::uniform_int_distribution <> dis;


    QTimer screenSwitchTimer;

    typedef std::array<std::array<std::array<QGraphicsPixmapItem*, symbolCount>, xFlaps>, yFlaps> flapStacksT;

    flapStacksT flapStacks;

    QGraphicsScene scene;
    QGraphicsView view;
    QPixmap background;

private slots:
    void switchScreen();
};

#endif // MAINWINDOW_H
