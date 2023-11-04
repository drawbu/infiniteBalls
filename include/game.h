#ifndef BALL_H_
    #define BALL_H_

    #include <stdint.h>

    #include <SFML/Graphics.h>

typedef struct {
    sfCircleShape *circle;
    float speed;
} ball_t;

typedef void * null_t;

ball_t *ball_create(uint32_t x);
void render_ball(ball_t *ball, sfRenderWindow *window);
null_t free_ball(ball_t *ball);

#endif /* BALL_H_ */
