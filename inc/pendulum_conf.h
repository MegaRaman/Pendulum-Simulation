#ifndef __PENDULUM_CONF_H__
#define __PENDULUM_CONF_H__

#define WINDOW_WIDTH	(960)
#define WINDOW_HEIGHT	(720)

#define BALL_RADIUS		(20) // radius in pixels, can be that cause doesn't impact the model

#define l_ROD_LENGTH	(2) // length in meters
#define l_ROD_SCALE		(50)
#define l_ROD_LEN_PIX	(l_ROD_LENGTH * l_ROD_SCALE) // length in pixels on screen

#define g_FREEFALL		(9.81)
#define AIR_FRICTION	(0.2)

#define TRAJ_CENTER_X	(WINDOW_WIDTH / 2)
#define TRAJ_CENTER_Y	(WINDOW_HEIGHT / 2 - l_ROD_LEN_PIX)

#define SIM_PERIOD_S	(0.01)
#define SIM_PERIOD_MS	(SIM_PERIOD_S * 1000)

#define START_ANGLE		(SDL_PI_F)

/* max magnitude of zero-centered uniform pert */
#define RANDOM_PERT_MAGN	(5)
/* RANDOM_PERT_MAGN scaler, needed to support '%' operation, which is only
 * defined for int*/
#define RANDOM_PERT_SCALER	(0.0001)

#endif // __PENDULUM_CONF_H__
