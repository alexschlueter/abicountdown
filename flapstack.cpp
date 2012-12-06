#include "flapstack.h"
#include <QTextStream>

void FlapStack::setGoalOffset(unsigned int newOffset)
{
    if (newOffset != offset) {
        goalOffset = newOffset;
        flipOne();
    }
}

void FlapStack::flipOne()
{
    QGraphicsRotation *rot = new QGraphicsRotation();
    rot->setAxis(Qt::XAxis);
    rot->setAngle(0);
    rot->setOrigin(QVector3D(0, _flaps.front().first->pixmap().height(), 0));
    QList<QGraphicsTransform*> tList;
    tList.append(rot);
    _flaps.front().first->setTransformations(tList);
    QPropertyAnimation *anim_1 = new QPropertyAnimation(rot, "angle");
    anim_1->setStartValue(0);
    anim_1->setEndValue(90);
    anim_1->setDuration(animationTime);
    anim_1->start();


    connect(anim_1, SIGNAL(finished()), SLOT(halfFlip()));

}

void FlapStack::halfFlip()
{
    QGraphicsRotation *rot_2 = new QGraphicsRotation();
    rot_2->setAxis(Qt::XAxis);
    rot_2->setAngle(90);
    QList<QGraphicsTransform*> tList_2;
    tList_2.append(rot_2);
    (++(begin(_flaps)))->second->setTransformations(tList_2);
    _flaps.front().second->setZValue(1);
    (++(begin(_flaps)))->second->setZValue(2);
    QPropertyAnimation *anim_2 = new QPropertyAnimation(rot_2, "angle");
    anim_2->setStartValue(90);
    anim_2->setEndValue(0);
    anim_2->setDuration(animationTime);
    anim_2->start();

    connect(anim_2, SIGNAL(finished()), SLOT(flipFinished()));
}

void FlapStack::flipFinished()
{
    _flaps.front().first->setZValue(0);
    _flaps.front().second->setZValue(0);
    _flaps.front().first->setTransformations(QList<QGraphicsTransform*>());

    _flaps.emplace_back(std::move(_flaps.front()));
    _flaps.pop_front();

    _flaps.front().first->setZValue(2);
    _flaps.front().second->setZValue(2);
    (++(begin(_flaps)))->first->setZValue(1);

    offset = (offset + 1) % _flaps.size();
    if (offset != goalOffset) flipOne();
}
