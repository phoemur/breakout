#include "rect.h"
#include "locator.hpp"
#include "mainwindow.h"
#include "exception.h"

Rect::Rect(int x, int y, int w, int h)
    : gRenderer{Locator<SDL_Renderer>::get()}, border{SDL_Color{0,0,0,0xFF}},
      inside{SDL_Color{0xFF,0XFF,0XFF,0xFF}}, solid{false}, rect{}
{
    if (gRenderer == nullptr) {
        throw SDLException("Could not locate MainWindow renderer");
    }

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

Rect::Rect(int x, int y, int w, int h, const SDL_Color& b)
    : Rect(x, y, w, h)
{
    border = b;
}

Rect::Rect(int x, int y, int w, int h, const SDL_Color& b, const SDL_Color& i)
    : Rect(x, y, w, h, b)
{
    solid = true;
    inside = i;
}

Rect::Rect(const SDL_Rect& r)
    : Rect(r.x, r.y, r.w, r.h) {}

Rect::Rect(const SDL_Rect& r, const SDL_Color& b)
    : Rect(r)
{
    border = b;
}

Rect::Rect(const SDL_Rect& r, const SDL_Color& b, const SDL_Color& i)
    : Rect(r, b)
{
    solid = true;
    inside = i;
}

inline bool operator==(const SDL_Color& a, const SDL_Color& b)
{
    return a.r == b.r &&
           a.g == b.g &&
           a.b == b.b &&
           a.a == b.a;
}

void Rect::render()
{
    if (visible) {
        if (solid) {
            SDL_SetRenderDrawColor(gRenderer, inside.r, inside.g, inside.b, inside.a);
            SDL_RenderFillRect(gRenderer, &rect);

            if (inside == border) {
                return;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, border.r, border.g, border.b, border.a);
        SDL_RenderDrawRect(gRenderer, &rect);
    }
}

void Rect::move()
{
    // Update position
    rect.x += movData.speed_x;
    rect.y += movData.speed_y;

    // Update Speed
    movData.speed_x += movData.accel_x;
    movData.speed_y += movData.accel_y;

    // Notify event
    notify(Event::SUBJECT_MOVED);
}

void Rect::setSpeed(double spx, double spy, double acx, double acy) noexcept
{
    movData.speed_x = spx;
    movData.speed_y = spy;
    movData.accel_x = acx;
    movData.accel_y = acy;
}
