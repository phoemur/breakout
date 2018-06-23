#ifndef LEVEL1_H
#define LEVEL1_H

#include "gamestate.h"
#include "texture.h"
#include "audioobserver.h"
#include "collisionobserver.h"
#include "ball.h"
#include "player.h"
#include <vector>
#include <memory>


class MainWindow;

class Level1 : public GameState {
    MainWindow* win;
    Texture background;
    CollisionObserver colOb;
    AudioObserver audio;
    Ball b;
    Player p;
    std::vector<std::unique_ptr<Rect>> bricks;
public:
    Level1();
    virtual ~Level1() noexcept override = default;
    Level1(const Level1&) = delete;
    Level1& operator=(const Level1&) = delete;

    virtual void handle_events() override;
    virtual void logic() override;
    virtual void render() override;
};

#endif // LEVEL1_H
