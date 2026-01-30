#include <SDL3/SDL.h>
#include <math.h>

#include "pendulum_conf.h"
#include "pendulum.h"

void draw_ball(simulation_t *sim) {
	SDL_SetRenderDrawColor(sim->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int i = -BALL_RADIUS; i < BALL_RADIUS; i++) {
		for (int j = -BALL_RADIUS; j < BALL_RADIUS; j++) {
			if (i * i + j * j <= BALL_RADIUS * BALL_RADIUS) {
				SDL_RenderPoint(sim->renderer, i + sim->p.pos_x, j + sim->p.pos_y);
			}
		}
	}
}

void draw_rod(simulation_t *sim) {
	SDL_SetRenderDrawColor(sim->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderLine(sim->renderer, TRAJ_CENTER_X, TRAJ_CENTER_Y, sim->p.pos_x, sim->p.pos_y);
}

void pendulum_step(simulation_t *sim) {
	sim->p.acc_theta_ddot = -g_FREEFALL / l_ROD_LENGTH * sin(sim->p.dev_theta);
	sim->p.vel_theta_dot += sim->p.acc_theta_ddot * SIM_PERIOD_S;
	sim->p.dev_theta += sim->p.vel_theta_dot * SIM_PERIOD_S;

	sim->p.pos_x = TRAJ_CENTER_X + l_ROD_LEN_PIX * sin(sim->p.dev_theta);
	sim->p.pos_y = TRAJ_CENTER_Y + l_ROD_LEN_PIX * cos(sim->p.dev_theta);
}

