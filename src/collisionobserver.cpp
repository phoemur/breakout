#include "collisionobserver.h"
#include "ball.h"
#include "rect.h"
#include "subject.h"
#include "player.h"
#include "gamestate.h"

#include <cmath>
#include <iostream>

CollisionObserver::CollisionObserver(int x, int y)
    : max_x{x}, max_y{y} {}

void CollisionObserver::onNotify(Subject& entity, Event event)
{
    switch (event) {
        case Event::SUBJECT_MOVED:
            {
                auto& b = dynamic_cast<Ball&>(entity);
                checkBounds(b);
                checkCollisions(b);
            }
            break;
        case Event::SUBJECT_ENEMY_COLLIDED:
            if (observed_.size() <= 2) {GameState::next_state = GameStates::Won;}
            break;
        case Event::SUBJECT_DIED:
            GameState::next_state = GameStates::Lost;
            break;
        default:
            break;
    }
}

void CollisionObserver::checkBounds(Ball& b)
{
    if (!checkUpper(b)) {checkLower(b);}
    if (!checkLeft(b)) {checkRight(b);}
}

void CollisionObserver::checkCollisions(Ball& b)
{
    for (Subject* sub: observed_) {
        if (dynamic_cast<Ball*>(sub) == nullptr) { // not the ball
            if (collided(b, sub)) {
                auto p = dynamic_cast<Player*>(sub);
                if (p != nullptr) {
                    fix(b, p);
                    fix_speed(b, p);
                    b.notify(Event::SUBJECT_PLAYER_COLLIDED);
                }
                else {
                    auto r = dynamic_cast<Rect*>(sub);
                    fix(b, r);
                    r->visible = false;
                    r->removeObserver(this);
                    b.notify(Event::SUBJECT_ENEMY_COLLIDED);
                }
                break;
            }
        }
    }
}

void find_closer(Ball& b, Rect* rec, int& cX, int& cY)
{
    //Find closest x offset
    if(b.posData.pos_x < rec->rect.x) {
        cX = rec->rect.x;
    }
    else if(b.posData.pos_x > rec->rect.x + rec->rect.w ) {
        cX = rec->rect.x + rec->rect.w;
    }
    else {
        cX = static_cast<int>(b.posData.pos_x);
    }

    //Find closest y offset
    if(b.posData.pos_y < rec->rect.y) {
        cY = rec->rect.y;
    }
    else if( b.posData.pos_y > rec->rect.y + rec->rect.h ) {
        cY = rec->rect.y + rec->rect.h;
    }
    else {
        cY = static_cast<int>(b.posData.pos_y);
    }
}

bool CollisionObserver::collided(Ball& b, Subject* sub)
{
    auto rec = dynamic_cast<Rect*>(sub);

    //Closest point on collision box
    int cX, cY;
    find_closer(b, rec, cX, cY);

    return std::hypot(cX - b.posData.pos_x, cY - b.posData.pos_y) < b.posData.radius;
}

void CollisionObserver::fix(Ball& b, Rect* rec)
{
    int cX, cY;
    find_closer(b, rec, cX, cY);

    if (b.movData.speed_y > 0) {
        if (cY == rec->rect.y) { // collided from above
            b.movData.speed_y *= -1;
            b.posData.pos_y = cY - std::abs(b.posData.pos_y - cY);
        }
        else { // collided from side
            b.movData.speed_x *= -1;
            if (b.movData.speed_x > 0) { // from left side
                b.posData.pos_x = cX + std::abs(b.posData.pos_x - cX);
            }
            else { // from right side
                b.posData.pos_x = cX - std::abs(b.posData.pos_x - cX);
            }
        }
    }
    else {
        if (cY == rec->rect.y + rec->rect.h) { //collided from bellow
            b.movData.speed_y *= -1;
            b.posData.pos_y = cY + std::abs(b.posData.pos_y - cY);

        }
        else { // collided from side
            b.movData.speed_x *= -1;
            if (b.movData.speed_x > 0) { // from left side
                b.posData.pos_x = cX + std::abs(b.posData.pos_x - cX);
            }
            else { // from right side
                b.posData.pos_x = cX - std::abs(b.posData.pos_x - cX);
            }
        }
    }
}

void CollisionObserver::fix_speed(Ball& b, Rect* rec)
{
    auto offset = rec->rect.w / 3;

    if (b.movData.speed_x > 0) {
        if (b.posData.pos_x <= rec->rect.x + offset) {
            b.movData.speed_x *= 0.9;
        }
        else if (b.posData.pos_x >= rec->rect.x + 2*offset) {
            b.movData.speed_x *= 1.1;
        }
    }
    else {
        if (b.posData.pos_x <= rec->rect.x + offset) {
            b.movData.speed_x *= 1.1;
        }
        else if (b.posData.pos_x >= rec->rect.x + 2*offset) {
            b.movData.speed_x *= 0.9;
        }
    }
}


bool CollisionObserver::checkLeft(Ball& b)
{
    if (b.posData.pos_x > b.posData.radius) {
        return false;
    }

    // We have a collision
    b.posData.pos_x = b.posData.radius;
    b.movData.speed_x *= -1;
    b.movData.accel_x *= -1;

    b.notify(Event::SUBJECT_WALL_COLLIDED);
    return true;
}

bool CollisionObserver::checkRight(Ball& b)
{
    double right = max_x - b.posData.radius;

    if (b.posData.pos_x < right) {
        return false;
    }

    // Collision
    b.posData.pos_x = right;
    b.movData.speed_x *= -1;
    b.movData.accel_x *= -1;

    b.notify(Event::SUBJECT_WALL_COLLIDED);
    return true;
}

bool CollisionObserver::checkLower(Ball& b)
{
    auto top = max_y - b.posData.radius;

    if (b.posData.pos_y < top) {
        return false;
    }

    // Collision
    b.posData.pos_y = top;
    b.movData.speed_y *= -1;
    b.movData.accel_y *= -1;

    b.notify(Event::SUBJECT_DIED);
    return true;
}

bool CollisionObserver::checkUpper(Ball& b)
{
    if (b.posData.pos_y > b.posData.radius) {
        return false;
    }

    // We have a collision
    b.posData.pos_y = b.posData.radius;
    b.movData.speed_y *= -1;
    b.movData.accel_y *= -1;

    b.notify(Event::SUBJECT_WALL_COLLIDED);
    return true;
}
