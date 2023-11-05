#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <SFML/Graphics.h>

#include "game.h"

static
void ball_free(ball_t *ball)
{
    if (ball == NULL)
        return;
    if (ball->circle != NULL)
        sfCircleShape_destroy(ball->circle);
}

static
ball_t *ball_create(ball_t *ball, sfVector2f pos, sfColor color)
{
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
    sfColor color = {
        .r = rand() % 256,
        .g = rand() % 256,
        .b = rand() % 256,
        .a = 255,
    };

    if (game == NULL)
        return;
    pos.x = rand() % game->videoMode.width;
    pos.y = rand() % 20 + 1;
    game->count += 1;
    printf("%d\tballs\n", game->count);
    if (game->count > game->size) {
        game->size += 10;
        game->balls = reallocarray(game->balls, game->size, sizeof(ball_t));
    }
    ball_create(game->balls + game->count - 1, pos, color);
}

void render_balls(game_t *game)
{
    if (game == NULL || game->balls == NULL || game->window == NULL)
        return;
    for (uint32_t i = 0; i < game->count; i++)
        ball_render(i, game);
}

void free_balls(game_t *game)
{
    if (game == NULL || game->balls == NULL)
        return;
    for (uint32_t i = 0; i < game->count; i++)
        ball_free(game->balls + i);
    free(game->balls);
    game->count = 0;
    game->size = 0;
}
