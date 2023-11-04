#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <SFML/Graphics.h>

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
ball_t *ball_create(ball_t *ball, sfVector2f pos)
{
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
void ball_render(uint32_t index, game_t *game)
{
    sfVector2f pos;
    float radius;
    ball_t *ball = game->balls + index;

    if (ball == NULL || game == NULL)
        return;
    pos = sfCircleShape_getPosition(ball->circle);
    radius = sfCircleShape_getRadius(ball->circle);
    if (pos.y <= 0)
        ball->speed = -ball->speed;
    else if (pos.y + radius >= game->videoMode.height) {
        ball->speed = -ball->speed;
        add_ball(game);
        ball = game->balls + index;
    }
    pos.y += ball->speed;
    sfCircleShape_setPosition(ball->circle, pos);
    sfRenderWindow_drawCircleShape(game->window, ball->circle, NULL);
}

void add_ball(game_t *game)
{
    sfVector2f pos;

    if (game == NULL)
        return;
    pos.x = rand() % game->videoMode.width;
    pos.y = 1 + rand() % 20;
    game->count += 1;
    if (game->count > game->allocated) {
        game->allocated += 10;
        game->balls = reallocarray(game->balls, game->allocated, sizeof(ball_t));
    }
    if (game->balls == NULL)
        return;
    ball_create(game->balls + game->count - 1, pos);
}

void balls_render(game_t *game)
{
    if (game == NULL || game->balls == NULL || game->window == NULL)
        return;
    for (uint32_t i = 0; i < game->count; i++)
        ball_render(i, game);
}
