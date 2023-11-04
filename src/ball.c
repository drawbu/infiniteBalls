#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <SFML/Graphics.h>

#include "SFML/Graphics/CircleShape.h"
#include "game.h"

static
void ball_free(ball_t *ball)
{
    if (ball == NULL)
        return;
    if (ball->circle != NULL)
        sfCircleShape_destroy(ball->circle);
    free(ball);
    return;
}

static
ball_t *ball_create(ball_t *ball, uint32_t x)
{
    sfVector2f pos = { x, 20 };
    sfColor color = { 100, 250, 50, 255 };

    if (ball == NULL)
        return NULL;
    ball->circle = sfCircleShape_create();
    if (ball->circle == NULL) {
        ball_free(ball);
        return NULL;
    }
    ball->speed = 0.05;
    sfCircleShape_setPosition(ball->circle, pos);
    sfCircleShape_setRadius(ball->circle, 20);
    sfCircleShape_setFillColor(ball->circle, color);
    return ball;
}

static
void ball_render(ball_t *ball, game_t *game)
{
    sfVector2f pos = sfCircleShape_getPosition(ball->circle);
    float radius = sfCircleShape_getRadius(ball->circle);

    if (pos.y <= 0)
        ball->speed = -ball->speed;
    else if (pos.y + radius >= game->videoMode.height) {
        ball->speed = -ball->speed;
        add_ball(game);
    }
    pos.y += ball->speed;
    sfCircleShape_setPosition(ball->circle, pos);
    sfRenderWindow_drawCircleShape(game->window, ball->circle, NULL);
}

void add_ball(game_t *game)
{
    if (game == NULL)
        return;
    game->count += 1;
    if (game->count > game->allocated) {
        game->allocated += 10;
        if (game->balls == NULL)
            game->balls = malloc(game->allocated * sizeof(ball_t));
        else
            game->balls = realloc(game->balls, game->allocated * sizeof(ball_t));
    }
    if (game->balls == NULL)
        return;
    ball_create(game->balls + game->count - 1, 100);
}

void balls_render(game_t *game)
{
    if (game == NULL || game->balls == NULL || game->window == NULL)
        return;
    for (uint32_t i = 0; i < game->count; i++)
        ball_render(game->balls + i, game);
}
