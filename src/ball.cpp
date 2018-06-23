#include "ball.h"

Ball::Ball(double px, double py, double sx, double sy)
    : texture{},
      posData{px, py, 0.0},
      movData{sx, sy, 0.0, 0.0}
{
    texture.loadFromFile("./breakout_assets/ball.png");
    posData.radius = texture.getWidth() / 2;
}

void Ball::move()
{
    if (is_moving) {
        // Update position
        posData.pos_x += movData.speed_x;
        posData.pos_y += movData.speed_y;

        // Update Speed
        movData.speed_x += movData.accel_x;
        movData.speed_y += movData.accel_y;

        // Notify event
        notify(Event::SUBJECT_MOVED);
    }
}

void Ball::render()
{
    texture.render(static_cast<int>(posData.pos_x - posData.radius),
                   static_cast<int>(posData.pos_y - posData.radius));
}
