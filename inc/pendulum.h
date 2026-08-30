#ifndef __PENDULUM_H__
#define __PENDULUM_H__

#include <stdint.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "control.h"

typedef struct {
	double dev_theta;
	double vel_theta_dot;
	double acc_theta_ddot;
	float pend_x, pend_y;

} pendulum_t;

typedef struct {
	double acc_cart;
	double vel_cart;
	float cart_x, cart_y;
} cart_t;


typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	pendulum_t p;
	cart_t c;
	control_t control;

	bool pend_fallen;
} simulation_t;

void draw_ball(simulation_t *sim);
void draw_rod(simulation_t *sim);
void draw_cart(simulation_t *sim);
void move_cart(simulation_t *sim);
void pendulum_step(simulation_t *sim);

#endif // __PENDULUM_H__

