#ifndef AUDIOOBSERVER_H
#define AUDIOOBSERVER_H

#include "observer.h"
#include "music.h"

class AudioObserver : public Observer {
    Sound wall, brick, lost;
public:
    AudioObserver();
    virtual void onNotify(Subject&, Event event) override;
};

#endif // AUDIOOBSERVER_H
