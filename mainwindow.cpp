#include "mainwindow.h"

MainWindow::MainWindow() : dis(0, yFlaps - 1), scene(QApplication::desktop()->screenGeometry()), view(&scene),
    background(":/images/blue_sky.jpg")
{
    QPixmap allSymbols(":/images/flipboardletters.svg");
    std::array<QPixmap, 65> singleSymbols;

    auto i = 0;
    for (auto y = 0; y < 7; y++) {
        int xMax;
        if (y == 2) xMax = 9;
        else  if (y == 6) xMax = 6;
        else xMax = 10;
        for (auto x = 0; x < xMax; x++)
            singleSymbols[i++] = allSymbols.copy(x * 135, y * 182, 95, 150).scaled((scene.width() - 2 * xFlapBorder) / xFlaps,
                                                                                   scene.height() * 3 / (5 * yFlaps));
    }

    for (auto y = 0; y < yFlaps; y++) {
        for (auto x = 0; x < xFlaps; x++) {
            for (auto s = 0; s < symbolCount; s++) {
                auto item = scene.addPixmap(singleSymbols[s]);
                item->setPos(xFlapBorder + x * singleSymbols[s].width(), scene.height() / 5 + y * singleSymbols[s].height());
                flapStacks[y][x][s] = item;
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
}

void MainWindow::switchScreen()
{

    for (auto y = 0; y < yFlaps; y++) {

        for (auto x = 0; x < xFlaps; x++) {

        }
    }
}

