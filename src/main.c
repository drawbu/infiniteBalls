#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <SFML/Audio.h>
#include <SFML/Config.h>
#include <SFML/Graphics.h>

#include "SFML/Graphics/RenderWindow.h"
#include "SFML/System/Clock.h"
#include "game.h"

static
void handle_fps(sfClock *clock)
{
    static sfUint64 last_fps_update = 0;
    static unsigned short frame_count = 0;
    sfTime time = sfClock_getElapsedTime(clock);
    sfUint64 ms = time.microseconds;
    sfUint64 elapsed = ms - last_fps_update;

    frame_count++;
    if (elapsed < 1000000)
        return;
    printf("[%llu µs] FPS: %hu\n", ms, frame_count);
    last_fps_update = ms;
    frame_count = 0;
}

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

static
void game_run(game_t *game)
{
    add_ball(game);
    while (sfRenderWindow_isOpen(game->window)) {
        handle_events(game->window);
        sfRenderWindow_clear(game->window, sfBlack);
        balls_render(game);
        sfRenderWindow_display(game->window);
        handle_fps(game->clock);
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
        .clock = sfClock_create()
    };

    if (!game.clock)
        return EXIT_FAILURE;
    srand(time(NULL));
    game.window = sfRenderWindow_create(game.videoMode, "game", game.videoStyle, NULL);
    if (game.window == NULL) {
        sfClock_destroy(game.clock);
        return EXIT_FAILURE;
    }
    game_run(&game);
    sfRenderWindow_destroy(game.window);
    sfClock_destroy(game.clock);
    return EXIT_SUCCESS;
}
