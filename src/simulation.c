#include <SDL3/SDL.h>
#include <math.h>

#include "pendulum_conf.h"
#include "pendulum.h"

unsigned int isqrt(unsigned int x) {
    unsigned int res = 0;
    unsigned int bit = 1u << 30;  // highest power of 4 <= 2^32

    while (bit > x)
        bit >>= 2;

    while (bit != 0) {
        if (x >= res + bit) {
            x -= res + bit;
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }
    return res;
}

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
	// sim->p.dev_theta += sim->p.vel_theta_dot * SIM_PERIOD_S;
	// sim->p.vel_theta_dot += sim->p.acc_theta_ddot * SIM_PERIOD_S;
	sim->p.dev_theta += sim->p.vel_theta_dot * SIM_PERIOD_S;
	sim->p.vel_theta_dot += sim->p.acc_theta_ddot * SIM_PERIOD_S;
	SDL_Log("%f %f %f\n", sim->p.dev_theta, sim->p.vel_theta_dot, sim->p.acc_theta_ddot);

	sim->p.pos_x = TRAJ_CENTER_X + l_ROD_LEN_PIX * sin(sim->p.dev_theta);
	// TODO: check if the equation of circle works nicer
	// sim->p.pos_y = TRAJ_CENTER_Y - isqrt(l_ROD_LENGTH * l_ROD_LENGTH -
 			// (sim->p.pos_x - TRAJ_CENTER_X) * (sim->p.pos_x - TRAJ_CENTER_X));
	sim->p.pos_y = TRAJ_CENTER_Y + l_ROD_LEN_PIX * cos(sim->p.dev_theta);

}

