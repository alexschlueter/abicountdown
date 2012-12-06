#include "mainwindow.h"
#include <QTextStream>

MainWindow::MainWindow() : dis(0, yFlaps - 1), scene(QApplication::desktop()->screenGeometry()), view(&scene),
    background(":/images/blue_sky.jpg")
{
    symbols = {{ 'A', 'B', 'C', 'D', 'F', 'E', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z', 'Ö', 'Ä', 'Ü', '1', '2', '3', '4', '5', '6', '7',
                 '8', '9', '0', '!', '?', '€', '$', '@', '%', '&', '/', '(', ')', '+', '-', '_', '.', ':',
                 ',', '£', '\"', '\'', '.', '\\', ';', '#', '*', '=', ' ' }}; // fix point in middle

    QPixmap allSymbols(":/images/flipboardletters.svg");
    std::array<std::pair<QPixmap, QPixmap>, symbolCount> singleSymbols;

    auto i = 0;
    auto scaledFlapWidth = (scene.width() - 2 * xFlapBorder) / xFlaps, scaledFlapHeight = scene.height() * 3 / (5 * yFlaps);
    for (auto y = 0; y < 7; y++) {
        int xMax;
        if (y == 2) xMax = 9;
        else  if (y == 6) xMax = 6;
        else xMax = 10;
        for (auto x = 0; x < xMax; x++) {
            singleSymbols[i].first = allSymbols.copy(x * 135, y * 182, 95, 75).scaled(scaledFlapWidth, scaledFlapHeight / 2);
            singleSymbols[i].second = allSymbols.copy(x * 135, y * 182 + 75, 95, 75).scaled(scaledFlapWidth, scaledFlapHeight / 2);
            i++;
        }
    }

    for (auto y = 0; y < yFlaps; y++) {
        for (auto x = 0; x < xFlaps; x++) {
            flapStacks[y][x].init(animationTime, scaledFlapHeight / 2);
            for (auto s = 0; s < symbolCount; s++) {
                auto item = std::make_pair(scene.addPixmap(singleSymbols[s].first), scene.addPixmap(singleSymbols[s].second));
                item.first->setPos(xFlapBorder + x * scaledFlapWidth, scene.height() / 5 + y * scaledFlapHeight);
                item.second->setPos(xFlapBorder + x * scaledFlapWidth, scene.height() / 5 + (y + 0.5) * scaledFlapHeight);
                if (s == 0) {
                    item.first->setZValue(2);
                    item.second->setZValue(2);
                } else if (s == 1) {
                    item.first->setZValue(1);
                    item.second->setZValue(1);
                }
                flapStacks[y][x].flaps().emplace_back(std::move(item));
            }
        }
    }

    scene.setBackgroundBrush(background);

    connect(&screenSwitchTimer, SIGNAL(timeout()), SLOT(switchScreen()));
    screenSwitchTimer.start(screenSwitchInterval);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "AbiCountdown 2013"));
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view.showFullScreen();

    switchScreen();
}

unsigned int MainWindow::findSymbolOffset(char c)
{
    for (auto i = 0; i < symbolCount; i++)
        if (symbols[i] == c) return i;
    throw -1;
}

void MainWindow::switchScreen()
{
    auto ourFlightPos = dis(gen);
    auto otherFlightsLeft(otherFlights);
    std::uniform_int_distribution<> gateCharDist(0, 25), digitDist(1,9);
    for (auto y = 0; y < yFlaps; y++) {
        std::string flight, gate, departure;
        if (y == ourFlightPos) {
            flight = "ABI13";
            gate = "G9";
            departure = "220313";
        } else {
            auto otherFlightPos = std::uniform_int_distribution<>(0, otherFlightsLeft.size() - 1)(gen);
            flight = otherFlightsLeft[otherFlightPos];
            otherFlightsLeft.erase(begin(otherFlightsLeft) + otherFlightPos);
            auto gateChar = 'A' + gateCharDist(gen);
            gate += gateChar;
            gate += '0' + digitDist(gen);
            for (auto i = 0; i < 6; i++) departure += '0' + digitDist(gen);
        }

        for (auto x = 0; x < xFlight; x++) {
            if (flight.empty()) flapStacks[y][x].setGoalOffset(findSymbolOffset(' '));
            else {
                flapStacks[y][x].setGoalOffset(findSymbolOffset(flight.front()));
                flight.erase(begin(flight));
            }

        }

        for (auto x = 0; x < xGate; x++) {
            if (gate.empty()) flapStacks[y][xFlight + x].setGoalOffset(findSymbolOffset(' '));
            else {
                flapStacks[y][xFlight + x].setGoalOffset(findSymbolOffset(gate.front()));
                gate.erase(begin(gate));
            }
        }

        for (auto x = 0; x < xDeparture; x++) {
            if (departure.empty()) flapStacks[y][xFlight + xGate + x].setGoalOffset(findSymbolOffset(' '));
            else {
                flapStacks[y][xFlight + xGate + x].setGoalOffset(findSymbolOffset(departure.front()));
                departure.erase(begin(departure));
            }
        }
    }
}

