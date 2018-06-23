#ifndef COLLISIONOBSERVER_H
#define COLLISIONOBSERVER_H

#include "observer.h"

#include <SDL.h>

class Ball;
class Rect;

class CollisionObserver : public Observer {
    int max_x, max_y;
public:
    CollisionObserver(int x, int y);

    virtual void onNotify(Subject& entity, Event event) override;

protected:
    inline void checkBounds(Ball& b);
    void checkCollisions(Ball& b);
    bool collided(Ball& b, Subject* sub);
    void fix(Ball& b, Rect* r);
    void fix_speed(Ball& b, Rect* rec);

private:
    inline bool checkLeft(Ball& b);
    inline bool checkRight(Ball& b);
    inline bool checkLower(Ball& b);
    inline bool checkUpper(Ball& b);

};

#endif // COLLISIONOBSERVER_H
