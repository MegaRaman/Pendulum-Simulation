#ifndef __PENDULUM_H__
#define __PENDULUM_H__

#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct {
	float dev_theta;
	float vel_theta_dot;
	float acc_theta_ddot;
	int32_t pos_x, pos_y;
} pendulum_t;

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	pendulum_t p;
} simulation_t;

void draw_ball(simulation_t *sim);
void draw_rod(simulation_t *sim);
void pendulum_step(simulation_t *sim);

#endif // __PENDULUM_H__

