#include <QApplication>
#include <QtGui>
#include <QGraphicsItemAnimation>
#include "Pixmap.h"
#include <array>
#include <random>
#include <time.h>

class View : public QGraphicsView
{
public:
    View(QGraphicsScene *scene) : QGraphicsView(scene) { }

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(animatedtiles);

    QApplication app(argc, argv);

    std::array<char, 26> symbols = {{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                            'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                            'U', 'F', 'W', 'X', 'Y', 'Z' }};
    std::array<std::pair<QPixmap, QPixmap>, 26> pixHalfs;
    /*for (int i = 0; i < 26; i++) {
        QPixmap full(QString(":/images/") + symbols[i] + ".png");
        pixHalfs[i] = std::make_pair(full.copy(0, 0, full.width(), full.height() / 2),
                                     full.copy(0, full.height() / 2, full.width(), full.height() / 2));
    }*/

    //const auto ourFlight = ""

    std::mt19937 gen(time(NULL));
    std::uniform_int_distribution<> dis(1,5);

    /*for (;;) {
        unsigned int posOurFlight = dis(gen);

    }*/

    QPixmap aPix(":/images/A.png");
    QPixmap bgPix(":/images/blue_sky.jpg");

    QGraphicsScene *scene = new QGraphicsScene(QApplication::desktop()->screenGeometry());
    scene->setBackgroundBrush(bgPix);

    scene->addRect(40, scene->height() / 5, scene->width() - 80, scene->height() * 3 / 5);
    //QList<QGraphicsItem*> items;
    aPix = aPix.scaled(QSize((scene->width() - 80) / 20, scene->height() * 3 / 25));
    QPixmap a_1(aPix.copy(0, 0, aPix.width(), aPix.height() / 2));
    QPixmap a_2(aPix.copy(0, aPix.height() / 2, aPix.width(), aPix.height() / 2));
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 20; i++) {
            QGraphicsPixmapItem *item = scene->addPixmap(a_1);
            item->setPos(40 + i * aPix.width(), j * aPix.height() + scene->height() / 5);
            item = scene->addPixmap(a_2);
            item->setPos(40 + i * aPix.width(), (j + 0.5) * aPix.height() + scene->height() / 5);
            //items.append(item);
        }
    }
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 20; i++) {
            QGraphicsPixmapItem *item = scene->addPixmap(a_1);
            item->setPos(40 + i * aPix.width(), j * aPix.height() + scene->height() / 5);

            QGraphicsRotation *rot = new QGraphicsRotation();
            rot->setAxis(Qt::XAxis);
            rot->setAngle(0);
            rot->setOrigin(QVector3D(0, a_1.height(), 0));
            QList<QGraphicsTransform*> tList;
            tList.append(rot);
            item->setTransformations(tList);
            QPropertyAnimation *anim_1 = new QPropertyAnimation(rot, "angle");
            anim_1->setStartValue(0);
            //anim->setKeyValueAt(0.5, 90);
            anim_1->setEndValue(90);
            anim_1->setDuration(500);
            anim_1->start();

            /*QPropertyAnimation *anim_2 = new QPropertyAnimation(rot, "angle");
            anim_2->setStartValue(0);
            anim_2->setEndValue(90);
            anim_2->setDuration(500);
            anim_2->start();*/

            QObject::connect(anim_1, SIGNAL(finished()), anim_1, SLOT(start()));

            item = scene->addPixmap(a_2);
            item->setPos(40 + i * aPix.width(), (j + 0.5) * aPix.height() + scene->height() / 5);
            //items.append(item);
        }
    }
    /*QGraphicsItemGroup *board = scene->createItemGroup(items);
    board->setPos(scene->sceneRect().width() / 2, scene->sceneRect().height() / 2);*/

    /*Pixmap *a_1 = new Pixmap(aPix.copy(0, 0, aPix.width(), aPix.height() / 2));
    Pixmap *a_2 = new Pixmap(aPix.copy(0, aPix.height() / 2, aPix.width(), aPix.height() / 2));
    QGraphicsRotation *rot = new QGraphicsRotation();
    rot->setAxis(Qt::XAxis);
    rot->setAngle(0);
    QList<QGraphicsTransform*> tList;
    tList.append(rot);
    a_2->setTransformations(tList);
    QPropertyAnimation *anim = new QPropertyAnimation(rot, "angle");
    anim->setStartValue(0);
    anim->setKeyValueAt(0.5, 90);
    anim->setEndValue(0);
    anim->setDuration(500);
    anim->start();

    scene->addItem(a_1);
    scene->addItem(a_2);*/

    // Ui
    View *view = new View(scene);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Animated Tiles"));
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->showFullScreen();

    return app.exec();
}
