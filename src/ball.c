#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <SFML/Graphics.h>

#include "SFML/Graphics/CircleShape.h"
#include "game.h"

ball_t *ball_create(uint32_t x)
{
    ball_t *ball = malloc(sizeof(ball_t));
    sfVector2f pos = { x, 20 };
    sfColor color = { 100, 250, 50, 255 };

    if (ball == NULL)
        return NULL;
    ball->circle = sfCircleShape_create();
    if (ball->circle == NULL)
        return free_ball(ball);
    ball->speed = 0.05;
    sfCircleShape_setPosition(ball->circle, pos);
    sfCircleShape_setRadius(ball->circle, 20);
    sfCircleShape_setFillColor(ball->circle, color);
    return ball;
}

void render_ball(ball_t *ball, sfRenderWindow *window)
{
    sfVector2f pos = sfCircleShape_getPosition(ball->circle);
    float radius = sfCircleShape_getRadius(ball->circle);

    if (pos.y + radius >= 600 || pos.y <= 0)
        ball->speed = -ball->speed;
    pos.y += ball->speed;
    sfCircleShape_setPosition(ball->circle, pos);
    sfRenderWindow_drawCircleShape(window, ball->circle, NULL);
}

null_t free_ball(ball_t *ball)
{
    if (ball == NULL)
        return NULL;
    if (ball->circle != NULL)
        sfCircleShape_destroy(ball->circle);
    free(ball);
    return NULL;
}
