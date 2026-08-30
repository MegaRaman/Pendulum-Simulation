#include <stdio.h>

#include "pendulum.h"
#include "util/matrix.h"
#include "control.h"

void init_control(control_t *control) {
	control_t dummy = {.A = LINEARIZED_PEND_A, .B = LINEARIZED_PEND_B, .K = K_MATRIX, .u = 0};
	*control = dummy;
}

void update_input(control_t *control) {
	double u[INPUT_DIM][INPUT_DIM];
	double x[STATE_DIM][1];
	simulation_t *sim = container_of(control, simulation_t, control);
	x[0][0] = sim->c.cart_x - CART_START_X;
	x[1][0] = sim->c.vel_cart;
	x[2][0] = sim->p.dev_theta - SDL_PI_F;
	x[3][0] = sim->p.vel_theta_dot;
	printf("1 %f 2 %f 3 %f 4 %f\n", sim->c.cart_x - CART_START_X, sim->c.vel_cart, sim->p.dev_theta, sim->p.vel_theta_dot);

	matrix_mul(INPUT_DIM, STATE_DIM, STATE_DIM, 1, control->K, x, u);
	control->u = -u[0][0];
}

