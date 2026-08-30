#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "pendulum_conf.h"

#define STATE_DIM			4 // x, x_dot, theta, theta_dot
#define INPUT_DIM			1 // control only x(position of a cart)

#define LINEARIZED_PEND_A	{ 	{0, 1, 0, 0}, \
								{0, 0, BALL_MASS * g_FREEFALL / CART_MASS, 0},\
								{0, 0, 0, 1},\
								{0, 0, g_FREEFALL * (BALL_MASS + CART_MASS) / (l_ROD_LENGTH * CART_MASS), 0} }

#define LINEARIZED_PEND_B 	{ \
							{0}, \
							{1.0f / CART_MASS}, \
							{0}, \
							{1.0f / (CART_MASS * l_ROD_LENGTH)} \
}

// >> Q = [1 0 0 0; 0 1 0 0; 0 0 10 0; 0 0 0 100]
// >> R = 1
#define K_MATRIX			{ {-1.0000, -5.6657, 260.4582, 113.5192} }

typedef struct {
	double A[STATE_DIM][STATE_DIM];
	double B[STATE_DIM][INPUT_DIM];
	double K[INPUT_DIM][STATE_DIM];

	double u;
} control_t;

void init_control(control_t *control);
void update_input(control_t *control);

#endif // __CONTROL_H__

