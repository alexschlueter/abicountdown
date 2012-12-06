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
    QGraphicsRotation rot_1, rot_2;
    QPropertyAnimation anim_1, anim_2;
    QList<QGraphicsTransform*> list_1, list_2;

public:
    FlapStack() {}
    void init(unsigned int animTime, int halfFlapHeight);

    FlapStackT &flaps() { return _flaps; }
    void setGoalOffset(unsigned int newOffset);

private slots:
    void flipOne();
    void halfFlip();
    void flipFinished();
};

#endif // FLAPSTACK_H
