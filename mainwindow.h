#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <array>
#include <random>
#include <chrono>
#include <QtGui>
#include <QDate>
#include "flapstack.h"

class MainWindow : public QObject
{
    Q_OBJECT
    
public:
    MainWindow();


    static constexpr auto ourFlight = "ABI13", ourGate = "G9";
    static constexpr auto screenSwitchInterval = 60000, animationTime = 200, xFlight = 10, xGate = 4, xDeparture = 9;
    static constexpr auto yFlaps = 7, symbolCount = 65;
    static constexpr auto xFlapBorder = 40, xFlaps = xFlight + xGate + xDeparture;
    
private:
    std::array<char, symbolCount> symbols;
    std::vector<std::string> otherFlights = { "AIRBERLIN", "PERDUNAIR", "BLUESKY", "SPANAIR", "LUFTHANSA", "EUROFLY" };
    std::mt19937 gen;
    std::uniform_int_distribution <> dis;


    QTimer screenSwitchTimer;
    QDateTime abiDate;

    typedef std::array<std::array<FlapStack, xFlaps>, yFlaps> flapStacksT;

    flapStacksT flapStacks;

    QGraphicsScene scene;
    QGraphicsView view;
    QPixmap background;

    unsigned int findSymbolOffset(char c);

private slots:
    void switchScreen();
};

#endif // MAINWINDOW_H
