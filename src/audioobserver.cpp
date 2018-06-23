#include "audioobserver.h"

AudioObserver::AudioObserver()
    : wall{"./breakout_assets/bounce.wav"},
      brick{"./breakout_assets/break.wav"},
      lost{"./breakout_assets/lost.wav"}
{

}

void AudioObserver::onNotify(Subject&, Event event)
{
    switch (event) {
        case Event::SUBJECT_WALL_COLLIDED:
        case Event::SUBJECT_PLAYER_COLLIDED:
            wall.play();
            break;
        case Event::SUBJECT_DIED:
            lost.play();
            break;
        case Event::SUBJECT_ENEMY_COLLIDED:
            brick.play();
            break;
        default:
            break;
    }
}
