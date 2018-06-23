#ifndef BALL_H
#define BALL_H

#include "subject.h"
#include "texture.h"

struct Circle {
    double pos_x;
    double pos_y;
    double radius;
};

class Ball : public Subject  {
    Texture texture;
public:
    bool is_moving = false;
    Circle posData;
    MovementData movData;

    Ball(double px, double py, double sx, double sy);

    virtual void move() override;
    virtual void render() override;
};

#endif // BALL_H
