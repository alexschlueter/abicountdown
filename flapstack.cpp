#include "flapstack.h"
#include <QTextStream>

void FlapStack::init(unsigned int animTime, int halfFlapHeight)
{
    animationTime = animTime;

    rot_1.setAxis(Qt::XAxis);
    rot_1.setAngle(0);
    rot_1.setOrigin(QVector3D(0, halfFlapHeight, 0));
    rot_2.setAxis(Qt::XAxis);
    rot_2.setAngle(90);

    anim_1.setTargetObject(&rot_1);
    anim_1.setPropertyName("angle");
    anim_1.setStartValue(0);
    anim_1.setEndValue(90);
    anim_1.setDuration(animationTime);
    anim_2.setTargetObject(&rot_2);
    anim_2.setPropertyName("angle");
    anim_2.setStartValue(90);
    anim_2.setEndValue(0);
    anim_2.setDuration(animationTime);

    list_1.append(&rot_1);
    list_2.append(&rot_2);

    connect(&anim_1, SIGNAL(finished()), SLOT(halfFlip()));
    connect(&anim_2, SIGNAL(finished()), SLOT(flipFinished()));
}

void FlapStack::setGoalOffset(unsigned int newOffset)
{
    if (newOffset != offset) {
        goalOffset = newOffset;
        flipOne();
    }
}

void FlapStack::flipOne()
{
    _flaps.front().first->setTransformations(list_1);
    anim_1.start();
}

void FlapStack::halfFlip()
{
    (++(begin(_flaps)))->second->setTransformations(list_2);
    _flaps.front().second->setZValue(1);
    (++(begin(_flaps)))->second->setZValue(2);
    anim_2.start();
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
    _flaps.front().second->setTransformations(QList<QGraphicsTransform*>());
    (++(begin(_flaps)))->first->setZValue(1);

    rot_1.setAngle(0);
    rot_2.setAngle(90);

    offset = (offset + 1) % _flaps.size();
    if (offset != goalOffset) flipOne();
}
