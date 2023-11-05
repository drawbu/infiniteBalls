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
    uint32_t size;
    sfClock *clock;
    uint32_t fps;
} game_t;

void add_ball(game_t *game);
void render_balls(game_t *game);
void free_balls(game_t *game);

#endif /* BALL_H_ */
