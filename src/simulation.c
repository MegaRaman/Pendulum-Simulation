#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <math.h>
#include <stdio.h>

#include "util/random.h"
#include "pendulum_conf.h"
#include "pendulum.h"

double m = BALL_MASS;
double M = CART_MASS;
double l = l_ROD_LENGTH;
double g = g_FREEFALL;

void draw_ball(simulation_t *sim) {
	SDL_SetRenderDrawColor(sim->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int i = -BALL_RADIUS; i < BALL_RADIUS; i++) {
		for (int j = -BALL_RADIUS; j < BALL_RADIUS; j++) {
			if (i * i + j * j <= BALL_RADIUS * BALL_RADIUS) {
				SDL_RenderPoint(sim->renderer, i + sim->p.pend_x, j + sim->p.pend_y);
			}
		}
	}
}

void draw_rod(simulation_t *sim) {
	SDL_SetRenderDrawColor(sim->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderLine(sim->renderer, sim->c.cart_x + CART_WIDTH / 2, CART_START_Y, sim->p.pend_x, sim->p.pend_y);
}

void draw_cart(simulation_t *sim) {
	SDL_SetRenderDrawColor(sim->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_FRect cart_rect = {sim->c.cart_x, sim->c.cart_y, CART_WIDTH, CART_LEN};
	SDL_RenderFillRect(sim->renderer, &cart_rect);
}

void move_cart(simulation_t *sim) {
	double F = sim->control.u;
	double theta = sim->p.dev_theta;
	double theta_dot = sim->p.vel_theta_dot;

	sim->c.acc_cart = (F + m * l * theta_dot * theta_dot * 
			sin(theta) + m * g * sin(theta) * 
			cos(theta)) / (M + m * sin(theta) * sin(theta));
	sim->c.vel_cart += sim->c.acc_cart * SIM_PERIOD_S;
	sim->c.cart_x += sim->c.vel_cart * SIM_PERIOD_S;
}

void pendulum_step(simulation_t *sim) {
	double F = sim->control.u;
	double theta = sim->p.dev_theta;
	double theta_dot = sim->p.vel_theta_dot;

	double acc_prev = sim->p.acc_theta_ddot;
	double vel_prev = sim->p.vel_theta_dot;
	double pert = (double)get_rand_range(-RANDOM_PERT_MAGN, RANDOM_PERT_MAGN);
	pert *= RANDOM_PERT_SCALER;

	sim->p.acc_theta_ddot = (-g * sin(theta) * M - m * g * sin(theta) - F * 
			cos(theta) - m * l * theta_dot * theta_dot * sin(theta) * 
			cos(theta)) / (l * (M + m * sin(theta) * sin(theta))) + pert;
	sim->p.vel_theta_dot += acc_prev * SIM_PERIOD_S;
	sim->p.dev_theta += vel_prev * SIM_PERIOD_S;

	if (sim->p.dev_theta >= 2 * SDL_PI_F) {
		sim->p.dev_theta -= 2 * SDL_PI_F;
	}

	if (sim->p.dev_theta <= SDL_PI_F / 2 || sim->p.dev_theta >= 3 * SDL_PI_F / 2) {
		sim->pend_fallen = true;
		printf("PENDULUM HAS FALLEN: CONTROL FAILED\n");
	}

	sim->p.pend_x = sim->c.cart_x + (CART_WIDTH / 2) + l_ROD_LEN_PIX * sin(sim->p.dev_theta);
	sim->p.pend_y = sim->c.cart_y + l_ROD_LEN_PIX * cos(sim->p.dev_theta);
}

