#include <stdint.h>
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
void handle_fps(game_t *game)
{
    static uint64_t last_fps_update = 0;
    static uint16_t frame_count = 0;
    sfTime time = sfClock_getElapsedTime(game->clock);
    unsigned long ms = time.microseconds;
    uint64_t elapsed = ms - last_fps_update;

    frame_count++;
    if (elapsed < 1000000)
        return;
    printf(
        "[%-9lu µs]\tFPS: %-5hu\tBALLS: %u\n",
        ms, frame_count, game->count
    );
    game->fps = frame_count;
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
        render_balls(game);
        sfRenderWindow_display(game->window);
        handle_fps(game);
    }
}

static
void free_game(game_t *game)
{
    if (game == NULL)
        return;
    if (game->clock != NULL)
        sfClock_destroy(game->clock);
    if (game->window != NULL)
        sfRenderWindow_destroy(game->window);
    if (game->balls != NULL)
        free_balls(game);
}

static
void init_game(game_t *game)
{
    if (game == NULL)
        return;
    *game = (game_t) {
        .videoMode = { 800, 600, 32 },
        .videoStyle = sfClose,
        .window = NULL,
        .balls = NULL,
        .count = 0,
        .size = 0,
        .fps = 0,
        .clock = sfClock_create()
    };
    game->window = sfRenderWindow_create(
        game->videoMode,
        "game",
        game->videoStyle,
        NULL
    );
}

int main(void)
{
    game_t game = { 0 };

    srand(time(NULL));
    init_game(&game);
    if (game.window == NULL || game.clock == NULL) {
        free_game(&game);
        return EXIT_FAILURE;
    }
    game_run(&game);
    free_game(&game);
    return EXIT_SUCCESS;
}
