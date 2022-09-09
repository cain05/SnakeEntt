#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    Game game;
    while (!game.GetWindow()->is_done()) {
        game.Events();
        game.Update();
        game.Render();
        game.RestartClock();
    }

    return 0;
}