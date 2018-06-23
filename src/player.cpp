#include "player.h"
#include "locator.hpp"
#include "mainwindow.h"

Player::Player(int x, int y)
    : Rect{x, y, 100, 15, SDL_Color{0,0,0,0xFF}, SDL_Color{0,0,0,0xFF}}, win{Locator<MainWindow>::get()}
{

}

void Player::handleEvents(SDL_Event& e)
{
    if (e.type == SDL_MOUSEMOTION) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        rect.x = x;

        if (rect.x < 0) {rect.x = 0;}
        else if (rect.x > win->getWidth() - rect.w) {rect.x = win->getWidth() - rect.w;}
    }
}
