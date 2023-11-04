#include <stdlib.h>
#include <time.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#include "game.h"

static
void handle_events(sfRenderWindow *window)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
            return;
        }
    }
}

int main(void)
{
    game_t game = {
        .videoMode = { 800, 600, 32 },
        .videoStyle = sfClose,
        .window = NULL,
        .balls = NULL,
        .count = 0,
        .allocated = 0,
    };

    srand(time(NULL));
    game.window = sfRenderWindow_create(game.videoMode, "game", game.videoStyle, NULL);
    if (game.window == NULL)
        return EXIT_FAILURE;
    add_ball(&game);
    while (sfRenderWindow_isOpen(game.window)) {
        handle_events(game.window);
        sfRenderWindow_clear(game.window, sfBlack);
        balls_render(&game);
        sfRenderWindow_display(game.window);
    }
    sfRenderWindow_destroy(game.window);
    return EXIT_SUCCESS;
}
