#include <stdlib.h>

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
    sfVideoMode mode = {800, 600, 32};
    sfUint32 style = sfClose;
    sfRenderWindow* window = sfRenderWindow_create(mode, "game", style, NULL);
    ball_t *ball = ball_create(100);

    if (!window)
        return EXIT_FAILURE;
    while (sfRenderWindow_isOpen(window)) {
        handle_events(window);
        sfRenderWindow_clear(window, sfBlack);
        render_ball(ball, window);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}
