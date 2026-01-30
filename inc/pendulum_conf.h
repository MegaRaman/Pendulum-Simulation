#ifndef __PENDULUM_CONF_H__
#define __PENDULUM_CONF_H__

#define WINDOW_WIDTH	(960)
#define WINDOW_HEIGHT	(720)

#define BALL_RADIUS		(20)
#define g_FREEFALL		(9.81)
#define l_ROD_LENGTH	(2)
#define l_ROD_SCALE		(50)
#define l_ROD_LEN_PIX	(l_ROD_LENGTH * l_ROD_SCALE)

#define TRAJ_CENTER_X	(WINDOW_WIDTH / 2)
#define TRAJ_CENTER_Y	(WINDOW_HEIGHT / 2 - l_ROD_LEN_PIX)

#define SIM_PERIOD_S	(0.01)
#define SIM_PERIOD_MS	(SIM_PERIOD_S * 1000)

#define START_ANGLE		(SDL_PI_F / 6)

#endif // __PENDULUM_CONF_H__
