#ifndef BALL_H_
    #define BALL_H_

    #include <stdint.h>

    #include <SFML/Graphics.h>

typedef struct {
    sfCircleShape *circle;
    float speed;
} ball_t;

typedef struct {
    sfVideoMode videoMode;
    sfUint32 videoStyle;
    sfRenderWindow *window;
    ball_t *balls;
    uint32_t count;
    uint32_t allocated;
} game_t;

typedef void * null_t;

void add_ball(game_t *game);
void balls_render(game_t *game);

#endif /* BALL_H_ */
