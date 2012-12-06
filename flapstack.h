#ifndef FLAPSTACK_H
#define FLAPSTACK_H

#include <QtGui>
#include <QObject>

class MainWindow;

class FlapStack : public QObject
{
    Q_OBJECT

private:
    typedef std::list<std::pair<QGraphicsPixmapItem*, QGraphicsPixmapItem*> >  FlapStackT;

    unsigned int offset{0}, goalOffset{0}, animationTime;
    FlapStackT _flaps;

public:
    FlapStack() {}

    FlapStackT &flaps() { return _flaps; }
    void setAnimationTime(unsigned int animTime) { animationTime = animTime; }
    void setGoalOffset(unsigned int newOffset);

private slots:
    void flipOne();
    void halfFlip();
    void flipFinished();
};

#endif // FLAPSTACK_H
